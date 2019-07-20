/***************************************************************************
                          astrorings.cpp  -  description
                             -------------------
    begin                : Sat Dec 30 2000
    copyright            : (C) 2000 by Christophe Gros
    email                : skylendar@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "astrorings.h"
#include "astrodefs.h"
#include "astrochartbase.h"
#include "astrostring.h"
#include "astroresources.h"
#include "astroaspects.h"
#include "astrowindow.h"

#include <cmath>
#include <cstdio>
#define PREV(x) ((x) ? (x) - 1 : NbSlots - 1)
#define NEXT(x) (((x) >= NbSlots - 1) ? 0 : (x) + 1)
#define ITEM 19

extern const enum Objs* DecansVector;

static const int PSectors[14] = { 1, 2, 3, 9, 10, 11, 12, 18, 19, 20, 27, 28, 29, 36 };
// A table of sizes, numbers of slots and corresponding chars sizes
static const struct RingType
{
    int Thickness, NbSlots, MaxNbObj;
    AstroGraphics::SizeChars Sc;
}
Sct[3] =
{
    { 15,  50,  28, AstroGraphics::Large  },
    { 18,  90,  61, AstroGraphics::Medium },
    { 28, 160,  82, AstroGraphics::Tiny   }
};

AstroRings::AstroRings(AstroGraphics *parent, int x, int y, int size, ChartParams* cp, AstroChartBase* acb, AstroFoundAspectsList& afal, AstroObjs* first, AstroObjs* second) : AstroGraphics(parent, x, y, size, size)
{
    int count = 0;
    AstroString test("0");
    Size = size;
    Acb = acb;
    Cp = cp;
    Afal = &afal;
    First = first;
    Second = second;
    Sv = 0;
    for (int i = 0; i < NBDATA; i++)
        if (ACB == i && ACB[i]->Show)
            count += ACB[i]->CountObjs();
    RingX = RingY = Cp->Sidebars ? 2 + (Size - 4) / 2 : 2 * (Size - 2) / 3;
    TextMetrics(test, &Size0, &Height0);
    SelectSizeClass(count);
    NbRings = Acb->Count();
    Narrow = (NbRings > 2 || count > 50);
    Init();
    SetWidth(Cp->Sidebars ? Size : 135 * Size / 100);
    SetHeight(GetWidth());
}

void AstroRings::Init()
{
    RingRadius = Cp->Sidebars ? (Size - (Size / 25)) / 2 :  67 * (Size - (Size / 25)) / 100;
    Angle0 = (First->IfHouses() && Cp->LeftAscendant) ? -DEGRAD((*First) * Ascendant) : 0.0;
    Circle(RingX, RingY, RingRadius);
}

double AstroRings::GetAngle(int x, int y) const
{
    const double x1 = x - RingX - PosX, y1 = y - RingY - PosY;
    double a = RADDEG(atan(-y1 / x1));
    if (x1 < 0.0)
        a += 180.0;
    else if (y1 >= 0.0)
        a += 360.0;
    return Normalize(a + 180.0 - RADDEG(Angle0));
}

void AstroRings::SelectSizeClass(int i)
{
    int j = 0, nb;
    nb = Sct[j].MaxNbObj;
    nb += nb / 2;
    if (i > nb)
        j = 1;
    nb = Sct[1].MaxNbObj;
    nb += nb / 2;
    if (i > nb)
        j = 2;
    Thickness = Sct[j].Thickness;
    NbSlots   = Sct[j].NbSlots;
    Sc        = Sct[j].Sc;
    MaxNbObj  = Sct[j].MaxNbObj;
    Halfthick = Size / (2 * Thickness);
    delete Sv;
    Sv = new struct Slot[NbSlots];
    for (j = 0; j < NbSlots; j++)
        Sv[j].IfSlot = Sv[j].Inc = false;
}

void AstroRings::PushBack(int i)
{
    int s = i;
    while (Sv[s].IfSlot)
        s = PREV(s);
    Sv[s].IfSlot = true;
    Sv[s].Inc = false;
    for (int j = s; j != i; j = NEXT(j))
        Sv[j] = Sv[NEXT(j)];
    Sv[i].IfSlot = false;
}

void AstroRings::PushForw(int i)
{
    int s = i;
    while (Sv[s].IfSlot)
        s = NEXT(s);
//     Sv[s].IfSlot = true;
//     Sv[s].Inc = false;
    for (int j = s; j != i; j = PREV(j))
        Sv[j] = Sv[PREV(j)];
    Sv[i].IfSlot = false;
}

static AstroString Shorten(const AstroString& as, int level)
{
    static const char Max0LengthText[] = { 27, 23, 20, 13, 0, 0, 7, 3, 3, 2 };
    int l = as.Len(), l1 = Max0LengthText[level - 1];
    return (l > l1) ? as.Left(l1) : as;
}

void AstroRings::Cuspide(double angle, int i, int i1)
{
    double v;
    int x, y, x1, y1;
    v = cos(angle);
    x = int(i1 * v);
    x1 = int(i * v);
    v = sin(angle);
    y = int(i1 * v);
    y1 = int(i * v);
    Move(RingX + x1, RingY - y1);
    Line(RingX + x, RingY - y);
}

#define RXY Rx = GetX(); Ry = GetY()

void AstroRings::CornerText(const AstroString& as, int line, enum Corner corner)
{
    int h, w, h1;
    TextMetrics(as, &w, &h);
    h = 4 * h / 5;
    h1 = Height - (2 * h / 5);
    if (line < 1 || line > 7) return;
    if (line >= 5) line += 3;
    switch (corner)
    {
    case Top_Left     :
        Move(Size0, line * h);
        RXY;
        Text(Shorten(as, line));
        break;
    case Top_Right    :
        Move(Width - w, line * h);
        RXY;
        Text(Shorten(as, line));
        break;
    case Bottom_Left  :
        Move(Size0, h1 - ((line - 1) * h));
        RXY;
        Text(Shorten(as, line));
        break;
    case Bottom_Right :
        Move(Width - w, h1 - ((line - 1) * h));
        RXY;
        Text(Shorten(as, line));
    };
}

void AstroRings::CornerPixmap(const AstroPixmap& ap, enum Corner corner)
{
    int w, h, h1, wi = (ap.width() * GetWidth()) / Asr->Height,
                  he = (ap.height() * GetHeight()) / Asr->Height;
    TextMetrics(" ", &w, &h);
    h = 4 * h / 5;
    h1 = Height - (2 * h / 5);
    h *= 9;
    h /= 2;
    switch (corner)
    {
    case Top_Right:
        Move(Width - wi, h);
        break;
    case Top_Left:
        Move(Size0, h);
        break;
    case Bottom_Right:
        Move(Width - wi, h1 - h - he);
        break;
    case Bottom_Left:
        Move(Size0, h1 - h - he);
    };
    DrawPixmap(ap, float(GetSize() * 50) / Asr->Width);
}

void AstroRings::CornerInfo(const AstroObjs& a, int i)
{
    AstroString as, as1, hour, acc;
    enum Corner c;
    int col;
    enum SubTypeState sts;

    switch (i)
    {
    case 0:
        c = Top_Right;
        break;
    case 1:
        c = Top_Left;
        break;
    case 2:
        c = Bottom_Left;
        break;
    case 3:
        c = Bottom_Right;
        break;
    default:
        return;
    };
    FontSize(Tiny);
    CornerText(Shorten(a.Name, 1), 1, c);
    if (a.GetSubType() != TimeSpace)
    {
        a.GetDate(as1);
        CornerText(as1, 2, c);
        CornerText(a.PlaceName.Left(20), 3, c);
        if (a.Accuracy > -1)
        {
            a.GetTime(as1, a.Accuracy > -1 ? a.Accuracy : 0, a.To_Second);
            CornerText(as1, 4, c);
        }
    }
    else
        CornerText(i18n("No time"), 4, c);
    CornerPixmap(*(*Ail)[a.ChartType], c);
    CornerText(a.GetSubTypeShortName(), 5, c);
    Color(COL[12]);
    CornerText(Sprintf("(%d)", &as, i + 1), 6, c);
    switch ((sts = a.GetState()))
    {
    case Slave:
        col = 3;
        break;
    case AMaster:
        col = 1;
        break;
    case ASlave:
        col = 6;
        break;
    default:
        ;
    };
    if (sts != Unknown_State && sts != Master)
    {
        Color(COL[col]);
        CornerText(*Asr->StateShortNames[sts], 7, c);
    }
    Fore();
    if (Cp->Outlines)
    {
        Rx += (i == 1 || i == 2) ? 2 * Size0 : -Size0 / 3;
        Ry -= Height0 / 4;
        float x1 = Rx - RingX, y1 = RingY - Ry, an = atanf(y1 / x1), o = (i == 1 || i == 2) ? -OutlRings[i] : OutlRings[i];
        y1 = RingY - o * sinf(an);
        x1 = RingX + o * cosf(an);
        Grey();
        Dash(3 - i);
        Move(int(x1), int(y1));
        Line(Rx, Ry);
        Dash(0);
        Back();
    }
}

void AstroRings::RingSigns()
{
    int i, x, y, x1, y1, rr = RingRadius, rs, thick;
    double c;
    const double a = TWOPI / 12;
    Fore();
    FontSize(Narrow ? Medium : Large, true);
    thick = (Narrow ? 14 :  8) * Sct[0].Thickness / 10;
    RingRadius -= Size / thick;
    Circle(RingX, RingY, RingRadius);
    for (i = 1, c = Angle0; i <= 12; i++, c += a)
    {
        if (c > TWOPI) c -= TWOPI;
        Cuspide(c, rr, RingRadius);
    }
    rs = RingRadius + Size / (thick * 2);
    for (i = 0, c = Angle0 + TWOPI / 24 + PI; i < 12; i++, c += a)
    {
        if (c > TWOPI) c -= TWOPI;
        GlyphMetrics(Asg->GetChar((enum Signs) i, *Cp), &x1, &y1);
        x = int(rs * cos(c)) - x1 / 2;
        y = int(rs * sin(c)) - (y1 / 3);
        if(Acb->NoSpot)
        {
            Move(RingX + x, RingY - y);
            Color(Asg->GetColor((enum Signs) i));
            Sign((enum Signs) i);
        }
        else
          Acb->PlaceSpot((enum Signs)i, RingX + x + PosX, RingY - y - (Narrow ? (2 * PosY / 5) : PosY), Narrow ? Medium : Large, Asg->GetColor((enum Signs) i));

    }
}

void AstroRings::DegreesRing()
{
    int i, thick, rr = RingRadius, rs;
    double c;
    const double a = TWOPI / 360.0;
    thick = (Narrow ? 5 : 3) * Sct[0].Thickness;
    RingRadius -= Size / thick;
    rs = RingRadius + (rr - RingRadius) / 2;
    Fore();
    AstroString as;
    for (i = 1, c = Angle0; i <= 360; i++, c += a)
    {
        if (c > TWOPI) c -= TWOPI;
        Cuspide(c, rr, ((i -1) % 5) ? rs : RingRadius);
    }
    RingRadius = rs;
}

void AstroRings::HousesRing(const AstroObjs& a)
{
    int i, x, y, x1, y1, rr = RingRadius, thick;
    double c, rs;
    AstroString House;
    if (!a.IfHouses()) return;
    enum House h = a().GetHouse();
    bool hide = (h == Vehlow || h == Azimuthal) ? false : true;
    thick = Narrow ? 28 : 12 * Sct[0].Thickness / 10;
    RingRadius -= Size / thick;
    rs = RingRadius + (rr - RingRadius) / 2;
    FontSize(Narrow ? Tiny : Medium);
    if(Cp->Sectors)
    {
        const QRectF r(PosX + RingX - rr, PosY + RingY - rr, 2 * rr, 2 * rr);
        QRadialGradient myGradient(RingX + PosX, RingY + PosY, rr);
        for (i = House_1; i <= House_12; i++)
        {
            int j = (i == House_12) ? House_1 : i + 1;
            double t1 = RADDEG(Angle0) + a *i + 180.0, t2 = a * j - (a * i), t3;
            if(t2 < 0.0) t2 = 360.0 + t2;
            t3 = t1 + t2 / 2.0;
            if(t3 < 0.0) t3 = 360.0 + t3;
            c = DEGRAD(t3);
            if (c > TWOPI) c -= TWOPI;
            QPainterPath myPath;
            myGradient.setColorAt(0, a.GetObjColor(i));
            myGradient.setColorAt(1, a.GetObjColor(i).GetLighter());
            //myPath.addRect(r);
            myPath.moveTo(RingX + PosX, RingY + PosY);
            myPath.arcTo(r, t1, t2);
            Qp->setBrush(myGradient);
            Qp->drawPath(myPath);
            Grey();
            House = i - House_1 + 1;
            TextMetrics(House, &x1, &y1);
            x = int(rs * cos(c) - x1 / 2.0);
            y = int(rs * sin(c) - y1 / 3.0);
            Move(RingX + x, RingY - y);
            Text(House);

        }
    }
    else
        for (i = House_1; i <= House_12; i++)
        {
            c = Angle0 + DEGRAD(a * i) + PI;
            if (c > TWOPI) c -= TWOPI;
            Grey();
            Cuspide(c, rr, 0);
            if (!(hide && (i == House_1 || i == House_4 || i == House_7 || i == House_10)))
            {
                House = i - House_1 + 1;
                TextMetrics(House, &x1, &y1);
                x = int(rs * cos(c) - x1 / 2.0);
                y = int(rs * sin(c) - y1 / 3.0);
                Move(RingX + x, RingY - y);
                Color(a.GetObjColor(i));
                Text(House);
            }
        }
    RingRadius = int(rs);
}

void AstroRings::GauquelinRing(bool hp)
{
    int x, y, x1, y1, rr = RingRadius, thick;
    double c, rs;
    AstroString House;
    thick = Narrow ? 28 : 12 * Sct[0].Thickness / 10;
    RingRadius -= Size / thick;
    rs = RingRadius + (rr - RingRadius) / 2;
    RingRadius = int(rs -  Size / thick / 2.0);
    FontSize(Narrow ? Tiny : Medium);
    for (int i = 0; i < (hp ? 12 : 36); i++)
    {
			c = (hp ? DEGRAD((i + 1)* 30.0) : -DEGRAD(i * 10.0)) + PI;
        if (c > TWOPI) c -= TWOPI;
        Fore();
        Cuspide(c, rr, RingRadius);
        House = i + 1;
        TextMetrics(House, &x1, &y1);
        if (!hp)
            c -= DEGRAD(5.0);
        else
            c -= DEGRAD(15.0);
        x = int(rs * cos(c) - x1 / 2.0);
        y = int(rs * sin(c) - y1 / 3.0);
        Move(RingX + x, RingY - y);
        Color(COL[4]);
        if (!hp)
        {
            for (int j = 0; j < 14; j++)
                if ((i + 1) == PSectors[j])
                {
                    Color(COL[3]);
                    break;
                }
        }
        Text(House);
    }
    Fore();
    Circle(RingX, RingY, RingRadius);
}

void AstroRings::SubRing(const AstroObjs& a)
{
    int max, x, y, xc, yc, rr = RingRadius, thick;
    double c, rs;
    AstroString House;
    if (Cp->Subring == No_Subring) return;
    thick = Narrow ? 18 : 9 * Sct[0].Thickness / 10;
    if (Cp->Subring == Solar_Houses && !(a == Sun)) return;
    if (Cp->Subring == Lunar_Houses && !(a == Moon)) return;
    if (Cp->Subring == Nodal_Houses && !(a == North_Node)) return;
    RingRadius -= Size / thick;
    rs = RingRadius + Size / (thick * 2);
    FontSize(Narrow ? Very_Tiny : Tiny, Cp->Subring == Decans || Cp->Subring == Terms);
    c = Angle0 + PI;
    if (Cp->Subring == Terms)
		 {
			  extern const SignTerms* TermsVector;
        for (int i = 0; i < 12; i++) 
        {
					  const SignTerms& t = TermsVector[i];
            double g = ((rr - RingRadius) * 28) / 100;
            for (int j = 0; j < 5; j++)
            {
                const char s = a.GetObjChar(t[j].o);
                double sp = DEGRAD((j == 0) ? t[j].deg : (t[j].deg - t[j - 1].deg)), c1 = c + (sp / 2.0);
                Grey();
                Cuspide(c, rr, RingRadius);
                GlyphMetrics(s, &xc, &yc);
                x = int((rs + g) * cos(c1) - xc / 2.0);
                y = int((rs + g)* sin(c1) - yc / 3.0);
                Move(RingX + x, RingY - y);
                Color(a.GetObjColor(t[j].o));
                Glyph(s);
                c += sp;
                if (c > TWOPI) c -= TWOPI;
            }
        }
        RingRadius = int(rs);
        Fore();
        Circle(RingX, RingY, RingRadius);
        return;
    }
    switch (Cp->Subring)
    {
    case Decans      :
        max = 36;
        break;
    case Solar_Houses:
        c = Normalize(c + DEGRAD(a * Sun));
        max = 12;
        break;
    case Lunar_Houses:
        c = Normalize(c + DEGRAD(a * Moon));
        max = 12;
        break;
    case Nodal_Houses:
        c = Normalize(c + DEGRAD(a * North_Node));
        max = 12;
        break;
    default:
        ;
    };
    const double d = TWOPI / max, g = ((rr - RingRadius) * 28) / 100;
    for (int i = 0; i < max; i++, c += d)
    {
        if (c > TWOPI) c -= TWOPI;
        Grey();
        Cuspide(c, rr, RingRadius);
        const double c1 = c + (d / 2.0);
        if (Cp->Subring == Decans)
        {
            const char s = a.GetObjChar(DecansVector[i]);
            GlyphMetrics(s, &xc, &yc);
            x = int((rs + g) * cos(c1) - xc / 2.0);
            y = int((rs + g)* sin(c1) - yc / 3.0);
            Move(RingX + x, RingY - y);
            Color(a.GetObjColor(DecansVector[i]));
            Glyph(s);
        }
        else
        {
            House = i  + 1;
            TextMetrics(House, &xc, &yc);
            x = int((rs + g) * cos(c1) - xc / 2.0);
            y = int((rs + g) * sin(c1) - yc / 3.0);
            Move(RingX + x, RingY - y);
            Color(a.GetObjColor(i + House_1));
            Text(House);
        }
    }
    RingRadius = int(rs);
    Fore();
    Circle(RingX, RingY, RingRadius);
}

void AstroRings::Insert(enum Objs o, double angle)
{
    if (angle == NOVALUE) return;
    auto s = new Slot;
    s->O = o;
    s->Angle = angle;
    Sl.Append(s);
}

void AstroRings::PutRing(const AstroObjs& a, int dlinelen, int ring)
{
    int size;
    struct Slot *RESTR ps;
    double slotangle, rs, lrs, lrs2;
		const AstroRestrictions& r = *~a;
		auto f = [&](int i) { Insert((enum Objs) i, a * i); };
    Sl.Clear();
    size = Size / Thickness;
    if (Thickness == Sct[1].Thickness)
        size = 9 * size / 10;
    RingRadius -= size;
    rs = RingRadius + Halfthick;
    lrs = RingRadius - Halfthick;
    lrs2 = lrs - (dlinelen * size);
    OutlRings[ring] = int(lrs);
    if (Cp->Outlines)
    {
        Grey();
        Dash(3 - ring);
        Circle(RingX, RingY, int(lrs));
        Dash(0);
    }
    for (int i = 0; i < NbSlots; i++)
        Sv[i].IfSlot = Sv[i].Inc = false;
		r(f);
    Sl.Sort([](const struct Slot* a, const struct Slot* b){  return a->Angle < b->Angle; });
    foreachc(Sl, AstroList<Slot>)
    {
        slotangle = (!it)->Angle * NbSlots / 360.0;
        //int i = int(round(slotangle));
				int i = int(slotangle);
        if(i == NbSlots) i = 0;
        ps = &Sv[i];
        if (ps->IfSlot)
        {
            while(Sv[i].IfSlot)
            {
                i = NEXT(i);
                if(i == 0 || i == NbSlots -1)
                {
                    i = NbSlots -1;
                    PushBack(i);
                    break;
								}
            }
            ps = &Sv[i];
        }
        ps->IfSlot = true;
        ps->Angle  = (!it)->Angle;
        ps->O      = (!it)->O;
    }
    for (int i = NbSlots - 1; i >= 0; i--)
			{
				if (Sv[i].IfSlot &&  (i * 360.0 / NbSlots) - Sv[i].Angle > (0.4 * 360.0 / NbSlots))
					PushBack(i);
				if (Sv[i].IfSlot &&  Sv[i].Angle - (i * 360.0 / NbSlots) > 1.7 * 360.0 / NbSlots)
					PushForw(i);
			}
		
    for (int i = 0; i < NbSlots; i++)
        if (Sv[i].IfSlot)
        {
            slotangle = i * 360.0 / NbSlots;
            if (!a.GetObjChar(Sv[i].O) && Sv[PREV(i)].IfSlot && !Sv[PREV(i)].Inc)
                Sv[i].Inc = true;
            PutObj(a, &Sv[i], slotangle, rs, lrs, lrs2);
        }
}

void AstroRings::PutObj(const AstroObjs& a, const struct Slot *sl, double angle, double rs, double lrs, double lrs2)
{
    int x, y, lx1, ly1, lx2, ly2, xc, yc;
    double c, lc;
    char s;
    c = Gau ? -DEGRAD(angle + 10.0) - PI : Angle0 + PI + DEGRAD(angle);
    c += DEGRAD(360.0 / (NbSlots * 2.0));
    if (c > TWOPI) c -= TWOPI;
    if (c < 0.0) c += TWOPI;
    s = a.GetObjChar(sl->O);
    if (s)
    {
			FontSize(Sc, true);
			GlyphMetrics(s, &xc, &yc);
        xc /= 2;
        yc /= 3;
        x = int(rs * cos(c) - xc);
        y = int(rs * sin(c) - yc);
        if(Acb->NoSpot)
        {
            Move(RingX + x, RingY - y);
            Color(a.GetObjColor(sl->O));
            Glyph(s);
        }
        else
            Acb->PlaceSpot(a, sl->O, RingX + x + PosX, RingY - y - PosY, Sc, a.GetObjColor(sl->O));
    }
    else
    {
        const AstroString& Obj = a < sl->O;
        double x1 = c;
        if (x1 >= PI)
            x1 -= PI;
        if (x1 >= (PI / 6.0) && x1 <= (5.0 * PI / 6.0) && sl->Inc)
            rs  -= Halfthick;
        FontSize((AstroGraphics::SizeChars)(Sc - 2));
        TextMetrics(Obj, &xc, &yc);
        xc /= 2;
        yc /= 3;
        x = int(rs * cos(c) - xc);
        y = int(rs * sin(c) - yc);
        if(Acb->NoSpot)
        {
            Move(RingX + x, RingY - y);
            Color(a.GetObjColor(sl->O));
            Text(Obj);
        }
        else
            Acb->PlaceSpot(a, sl->O, RingX + x + PosX, RingY - y - PosY, Sc-2, a.GetObjColor(sl->O));

    }
    lc = Gau ? -DEGRAD(sl->Angle) -PI : Angle0 + PI + DEGRAD(sl->Angle);
    if (lc > TWOPI) lc -= TWOPI;
    if (lc < 0.0) lc += TWOPI;
    lx1 = x + xc;
    ly1 = y + yc;
    lx2 = int(lrs * cos(lc));
    ly2 = int(lrs * sin(lc));
    lx1 += (lx2 - lx1) / 2;
    ly1 += (ly2 - ly1) / 2;
    Grey();
    Move(RingX + lx1, RingY - ly1);
    Line(RingX + lx2, RingY - ly2);
    if (lrs2 && Cp->CentralRing)
    {
        lx2 = int(lrs2 * cos(lc));
        ly2 = int(lrs2 * sin(lc));
        Grey();
        Dash(3);
        Line(RingX + lx2, RingY - ly2);
        Dash(0);
    }
    Fore();
    DrawDot();
}

void AstroRings::AscMidH(const AstroObjs& a)
{
    int x, y, rs = Size / 2;
    double c;
    if (a == Ascendant)
    {
        c = Angle0 + PI + DEGRAD(a * Ascendant);
        if (c > TWOPI) c -= TWOPI;
        x = int(rs * cos(c));
        y = int(rs * sin(c));
        Fore();
        //SetLineWidth(3);
        Move(RingX + x, RingY - y);
        Line(RingX - x, RingY + y);
        //SetLineWidth(1);
    }
    if (a == MC)
    {
        c = Angle0 + PI + DEGRAD(a * MC);
        if (c > TWOPI) c -= TWOPI;
        x = int(rs * cos(c));
        y = int(rs * sin(c));
        Fore();
        Move(RingX + x, RingY - y);
        Line(RingX - x, RingY + y);
    }
}

void AstroRings::ObjectsRings()
{
    int rr, l = 0, size = Size / Thickness;
    if (Thickness == Sct[1].Thickness)
        size = 9 * size / 10;
    for (int i = NBDATA -1; i; i--)
        if (ACB[i] && ACB[i]->Show)
        {
            l = i;
            break;
        }
    for (int i = 0; i < NBDATA; i++)
        if (ACB == i && ACB[i]->Show)
        {
            PutRing(*ACB[i], l - i, i);
            CornerInfo(*ACB[i], i);
            rr = RingRadius;
        }
        else
            RingRadius -= size;
    RingRadius = rr;
}

void AstroRings::Repaint()
{
    Fore();
    Sl.Clear();
    bool hp = Acb->GetCt() == House_Pos;
    Gau = Acb->GetCt() == Gauquelin;
    Init();
    if (Gau || hp)
    {
			  Angle0 = hp ? 0.0 : PI;
        DegreesRing();
        GauquelinRing(hp);
        ObjectsRings();
        if (Cp->CentralRing)
            Aspects(Second ? Second : First);
        return;
    }
    RingSigns();
    SubRing(*First);
    DegreesRing();
    if (First->Accuracy > -1)
        HousesRing(*First);
    ObjectsRings();
    if (First->Accuracy > -1)
        AscMidH(*First);
    if (Cp->CentralRing)
        Aspects(Second ? Second : First);
    FontSize(Medium, true);
    FontSize(Medium, false);
}

void AstroRings::Aspects(AstroObjs* ao)
{
    int x, y, x1, y1;
    double xa, xb;
    AstroAspects aa(~(*ao));
    RingRadius -= Size / Thickness / 2 + Thickness / 4;
    foreachc(*Afal, AstroFoundAspectsList)
    {
        const AspectFound* af = !it;
        Color(COL[aa.Color(af->Asp)]);
        xa = Gau ? -DEGRAD(af->Angle_a) -PI : DEGRAD(af->Angle_a) + Angle0 + PI;
        if (xa > TWOPI) xa -= TWOPI;
        if (xa < 0.0)   xa += TWOPI;
        xb = Gau ? -DEGRAD(af->Angle_b) -PI : DEGRAD(af->Angle_b) + Angle0 + PI;
        if (xb > TWOPI) xb -= TWOPI;
        if (xb > 0.0)   xb += TWOPI;
        x = int(RingRadius * cos(xa));
        y = int(RingRadius * sin(xa));
        x1 = int(RingRadius * cos(xb));
        y1 = int(RingRadius * sin(xb));
        Move(RingX + x, RingY - y);
        switch (af->GetAccuracy())
        {
        case Exact:
        case Good:
            Dash(0);
            break;
        case Medium:
            Dash(2);
            break;
        case Poor:
            Dash(3);
        default:
            ;
        }
        Line(RingX + x1, RingY - y1);
    }
    Dash(0);
}

AstroTextFrame::AstroTextFrame(AstroGraphics* parent, int x, int y, int w, int h, ChartParams* cp, AstroChartBase* acb) :AstroGraphics(parent, x, y, w, h)
{
    int height;
    Acb = acb;
    Cp = cp;
    Fore();
    FontSize(Tiny);
    TextMetrics("0", &Size0, &height);
    CharHeight = (4 * height) / 5;
    OrigWidth = LineWidth  = w + (Cp->DisplaySeconds ? 3 : 2) * Size0;
    Init();
}

AstroSideBar::AstroSideBar(AstroGraphics *parent, int x, int y, int w, int h, ChartParams* cp, AstroChartBase* acb, AstroObjs* ao) : AstroTextFrame(parent, x, y, w, h, cp, acb)
{
    AstroString as;
    Ao = ao;
    Gauq = Acb->GetCt() == Gauquelin;
    Sprintf(i18n("%d%a house:  "), &as, 12, Asr->NthAbbrev[11]);
    TextMetrics(as, &W);
}

int AstroSideBar::GetWidth() const
{
    int i = NbLines(), j = i / MaxNbLines;
    if (i % MaxNbLines)
        j++;
    return j * LineWidth;
}

void AstroTextFrame::Init()
{
    int h = GetHeight();
    FontSize(Tiny, true);
    FontSize(Tiny);
    XCurs = Size0;
    YCurs = 1;
    SetWidth(GetWidth());
    SetHeight(h);
    MaxNbLines = (h / CharHeight);
    NbWidth = 1;
    Move(XCurs, CharHeight);
}

void AstroTextFrame::TextLine(const AstroString as, bool newline)
{
    Text(as, true);
    if (newline)
        NewLine();
}

void AstroTextFrame::NewLine()
{
    if (YCurs == MaxNbLines)
    {
        XCurs += LineWidth;
        YCurs = 1;
        Move(XCurs, CharHeight);
    }
    else
    {
        Yi += CharHeight;
        Move(XCurs, Yi - PosY);
        YCurs++;
    }
}

void AstroSideBar::Repaint()
{
    Init();
    Fore();
		const _AstroRestrictions& ar = (*Ao)();

    for (int i = 0; i < NBDATA; i++)
        if (Ao == ACB[i])
            StdHeader(i);
    NewLine();
    if (Ao->IfHouses() && !Gauq && Acb->GetCt() != House_Pos)
    {
        for (int i = 1; i <= 12; i++)
            HouseLine(i);
        NewLine();
    }
		if(Gauq)
		{
			for (int i = Sun; i <= East_Point; i++)
        ObjLine(i);
			return;
		}
		else
		{
			auto f = [&](int i) { ObjLine(i); };
			ar(f);
		}
    NewLine();
    Fawe();
    NewLine();
    Cfm();
    NewLine();
    if (Ao->Accuracy > -1)
    {
        Asc();
        NewLine();
    }
    if (Cp->PlanetsRank && (*Ao) / 0)
    {
        NewLine();
        NewLine();
        RankLines();
    }
    Grey();
}

void AstroSideBar::StdHeader(int i)
{
    AstroString as, hms, hms1, hms2;
    const AstroObjs& ao = *Ao;
    AstroHM hm = ao.GetDaylight(), hm1 = ao.GetOffset();
    double d = hm.Get(), d1 = hm1.Get();
    Color(COL[12]);
    TextLine(Sprintf("(%d)", &as, i + 1), false);
    Fore();
    TextLine(Sprintf(i18n("  %a %a"), &as, &ao.Longitude.Get(hms, HM_Longitude, false, ao.To_Second), &ao.Latitude.Get(hms1, HM_Latitude, false, ao.To_Second)));
    TextLine(Sprintf(i18n("GMT%c%a, ST%c%a"), &as, d1 < 0.0 ? 0 : '+', &hm1.Get(hms, HM_Time, false, ao.To_Second), d < 0.0 ? 0 : '+', &hm.Get(hms2, HM_Time, false, ao.To_Second)));
    TextLine(ao.CountryName);
    if (Gauq) return;
    TextLine(Sprintf(i18n("%a Houses"), &as, Asr->HousesSystemNames[ao().GetHouse()]));
    TextLine(*Asr->SiderealSystemNames[ao().Sidereal + 1] + AstroString((ao().Heliocentric ? i18n(" Heliocentric") : i18n(" Geocentric"))));
    if (ao().Equatorial)
        TextLine(i18n("Equatorial positions"));
    TextLine(ao().Name);
    if (ao.GetSubType() != TimeSpace)
    {
        hm = ao.GetSidTime();
        if (ao.Accuracy > -1)
            TextLine(Sprintf(i18n("Sidereal time: %a"), &as, &hm.Get(hms, HM_Time, false, ao.To_Second)));
        TextLine(Sprintf(i18n("Julian date: %f"), &as, ao.GetJd()));
    }
    if ((*Acb)[i] == &Acb->GetRef() && Cp->Subring != No_Subring)
        TextLine(Sprintf(i18n("%a subring"), &as, Asr->SubringsNames[Cp->Subring]));
    if (ao.GetSubType() == AddAngle)
        TextLine(Sprintf(i18n("Add Factor: %f"), &as, ao.Angle));
    else if (ao.GetSubType() == MulAngle)
        TextLine(Sprintf(i18n("Mul factor: %f"), &as, ao.Angle));
    if (Cp->PlanetHour)
    {
        Fore();
        Text(i18n("Planetary Hour: "), true);
        enum Objs o = ao.GetPlaHour();
        Color(ao.GetObjColor(o));
        Glyph(ao.GetObjChar(o));
        Fore();
        NewLine();
    }
    if (Asr->Southern)
    {
        const AstroString& ns = ao.IsSouthern() ? i18n("Southern") : i18n("Northern");
        TextLine(Sprintf(i18n("%a ecliptic"), &as, &ns));
    }
}

void AstroSideBar::HouseLine(int house)
{
    AstroString as;
    int hs = House_1 + house - 1;
    double angle = (*Ao) * hs;
    if (house < 1 || house > 12) return;
    Sprintf(i18n("%d%a house:  "), &as,  house, Asr->NthAbbrev[house - 1]);
    Color(Ao->GetObjColor(hs));
    JustifText(as, Right, W);
    Color(Asg->GetColor(Asg->GetSign(angle)));
    DegSignMin(DecToDeg(angle), false, false, Cp->DisplaySeconds);
    NewLine();
}

void AstroSideBar::ObjLine(int i)
{
    double v;
    int h, m, s;
    AstroString as;
    char c;
    const AstroObjs& ao = *Ao;
    bool hp = Acb->GetCt() == House_Pos;

    if (ao == i)
    {
        if (Gauq)
        {
            Color(ao.GetObjColor(i));
            c = ao.GetObjChar(i);
            JustifGlyph(c ? c : ' ', Left, Size0 * 2);
            JustifText(ao < i, Left, Size0 * 3);
            v = DecToDeg((*ao[i])[5]);
            Color(Asg->GetColor(Asg->GetSign(int(v))));
            DegSignMin(v, false, ao[i]->Retro, Cp->DisplaySeconds);
            Grey();
            TextLine(Sprintf("%f", &as, (*ao[i])[1]));
            return;
        }
        Color(ao.GetObjColor(i));
        c = ao.GetObjChar(i);
        JustifGlyph(c ? c : ' ', Left, Size0 * 2);
        JustifText(ao < i, Left, Size0 * 3);
        if (hp)
        {
            v = ((ao * i) / 30.0) + 1.0;
            if (v < 0.0)
                v += 12.0;
            HMR(DecToDeg(v), h, m, s);
            if (h == 0) h = 12;
        }
        else
            v = DecToDeg(ao * i);
        if (v >= 360.0) v -= 360.0;
        if (hp)
            TextLine(Sprintf(i18n("  %d%s %d%a house"), &as,  m / 2, DEGCHAR, h, Asr->NthAbbrev[h - 1]));
        else
        {
            Color(Asg->GetColor(Asg->GetSign(int(v))));
            DegSignMin(v, false, ao[i]->Retro, Cp->DisplaySeconds);
            if (!Cp->DisplaySeconds)
                TextLine("  ", false);
            Grey();
            Hms(DecToDeg((*ao[i])[1]), DEGCHAR);//"\x00B0");
            NewLine();
        }
    }
}

void AstroSideBar::DrawLabelNb(const AstroString& label, int size, int nb)
{
    int w = Size0 * 2;
    AstroString as;
    as = nb;
    JustifText(label, Left, size);
    Text(":", true);
    JustifText(as, Right, w);
    RMove(w / 2);
}

void AstroSideBar::Fawe()
{
    int fire, air, water, earth, w = (Size0 * 11) / 2;
    Ao->CountFAWE(&fire, &air, &water, &earth);
    Grey();
    DrawLabelNb(i18n("Fire"), w, fire);
    DrawLabelNb(i18n("Air"), w, air);
    NewLine();
    DrawLabelNb(i18n("Water"), w, water);
    DrawLabelNb(i18n("Earth"), w, earth);
}

void AstroSideBar::Cfm()
{
    int cardinal, fixed, mutab, w = (Size0 * 38) / 10;
    Ao->CountCfm(&cardinal, &fixed, &mutab);
    Grey();
    DrawLabelNb(i18n("Car"), w, cardinal);
    DrawLabelNb(i18n("Fix"), w, fixed);
    DrawLabelNb(i18n("Mut"), w, mutab);
}

void AstroSideBar::Asc()
{
    int angular, succeedent, cadent, w = (Size0 * 38) / 10;
    Ao->CountAsc(&angular, &succeedent, &cadent);
    Grey();
    DrawLabelNb(i18n("Ang"), w, angular);
    DrawLabelNb(i18n("Suc"), w, succeedent);
    DrawLabelNb(i18n("Cad"), w, cadent);
}

void AstroSideBar::RankLines()
{
    int s = 2 * Size0;
    AstroString as;
    for (int i = 0; i < 10; i++)
    {
        const struct AstroObjs::PlanetRank* pr = (*Ao) / i;
        Color(Ao->GetObjColor(pr->planet));
        JustifGlyph(Ao->GetObjChar(pr->planet), AstroGraphics::Center, s);
    }
    NewLine();
    FontSize(Very_Tiny);
    Text(" ", true);
    for (int i = 0; i < 10; i++)
    {
        const struct AstroObjs::PlanetRank* pr = (*Ao) / i;
        Color(Ao->GetObjColor(pr->planet));
        as = pr->score;
        JustifText(as, AstroGraphics::Center, s);
    }
    FontSize(Tiny);
    Grey();
    NewLine();
}


int AstroSideBar::NbLines() const
{
    int i = Ao->CountObjs();
    if (Cp->Subring != No_Subring) i++;
    if (Cp->PlanetsRank && (*Ao) / 0) i += 3;
    i += Ao->Accuracy < 0 ? 10 : 10 + ITEM;
    if (Ao->GetSubType() == AddAngle || Ao->GetSubType() == MulAngle) i++;
    return i;
}

AstroAspectsFrame::AstroAspectsFrame(AstroGraphics* parent, int x, int y, int w, int h, ChartParams* cp, AstroChartBase* acb, AstroFoundAspectsList* afal, AstroObjs* first, AstroObjs* second) : AstroTextFrame(parent, x, y, w, h, cp, acb)
{
    Afal = afal;
    First = first;
    Second = second;
    LineWidth = 17 * Size0;
}

int AstroAspectsFrame::GetHeight() const
{
    int count = Afal->Count(), l = GetWidth() / (17 * Size0), l1 = count / l;
    return CharHeight * (20 + count % l ? l1 + 1 : l1);
}

void AstroAspectsFrame::Repaint()
{
    AstroAspects aa(Second ? ~(*Second) : ~(*First));
    Init();
    Fore();
    Move(0, 0);
    Line(GetWidth(), 0);
    Move(XCurs, CharHeight);
    foreachc(*Afal, AstroFoundAspectsList)
    DrawAspectFound(*(!it), aa);
}

void AstroAspectsFrame::DrawAspectFound(const AspectFound& af, const AstroAspects& aa)
{
    AstroString as;
    char c;
    const AstroObjs& s = Second ? *Second : * First;
    Color(First->GetObjColor(af.Oa));
    if ((c = First->GetObjChar(af.Oa)))
        JustifGlyph(c, Center, Size0 * 4);
    else
        JustifText((*First) < af.Oa, Left, Size0 * 4);
    Color(COL[aa.Color(af.Asp)]);
    JustifText(af.AspWay == LeftAspect ? "." : " ", Center, (Size0 * 2) / 7);
    JustifGlyph(aa.GetAspChar(af.Asp), Center, (Size0 * 18) / 10);
    JustifText(af.AspWay == LeftAspect ? " " : ".", Center, (Size0 * 2) / 7);
    Color(s.GetObjColor(af.Ob));
    if ((c = s.GetObjChar(af.Ob)))
        JustifGlyph(c, Center, Size0 * 4);
    else
        JustifText(s < af.Ob, Right, Size0 * 4);
    Fore();
    switch (af.AspectSide)
    {
    case Exact:
        as = "=";
        break;
    case Applying:
        as = "<";
        break;
    case Separating:
        as = ">";
        break;
    default:
        ;
    };
    JustifText(as, Right, (Size0 * 3 ) / 2);
    RMove(-Size0);
    double da = (af.Asp >= Parallel/*af.Asp == Parallel || af.Asp == Antiparallel*/ ? af.ExtraOrb : DiffAngle(af.Angle_a, af.Angle_b));
    Hms(DecToDeg(fabs(da - (aa * af.Asp))), DEGCHAR);
    NewLine();

}
