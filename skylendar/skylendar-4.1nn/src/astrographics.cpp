/***************************************************************************
                          astrographics.cpp  -  description
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

#include "astrographics.h"
#include "astroutils.h"
#include "astrohm.h"
#include "astroresources.h"
#include <cstdio>

#ifdef QT
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QImage>
#include <QStringList>
#include <QRegExp>
#endif

static const struct
{
    enum AstroGraphics::SizeChars Sc; //{ Very_Tiny, Tiny, Medium, Large, Huge };
    enum AstroGraphics::Justif J; //  { Left, Right, Center, Dot };
} Styles[] =
{
    { AstroGraphics::Tiny,   AstroGraphics::Left }, // PlainText
    { AstroGraphics::Large,  AstroGraphics::Center }, // MainTitle
    { AstroGraphics::Medium, AstroGraphics::Center }, // Title
    { AstroGraphics::Tiny,   AstroGraphics::Center }, // SubTitle
    { AstroGraphics::Tiny,   AstroGraphics::Left }, // TabText
    { AstroGraphics::Tiny,   AstroGraphics::Right}, // TabRight
    { AstroGraphics::Tiny,   AstroGraphics::Dot} // TabDot
};

extern void Dhms(double d, int* h, int* m, int* s);

AstroPixmap::AstroPixmap(const AstroString& file, const AstroString& path)
{
#ifdef QT
    load(QString(path) + QString(file));
#endif
}

AstroColor AstroColor::GetLighter() const
{
    QColor c = lighter(200);
   return AstroColor(c.red(), c.green(), c.blue());
}

AstroGraphics::AstroGraphics(AstroGraphics* parent, int x, int y, int w, int h)
{
    charbuf[1] = 0;
#ifdef QT
    if (parent)
    {
        Qp    = parent->Qp;
        Pen   = parent->Pen;
        astro = parent->astro;
        text  = parent->text;
        Size  = parent->Size;
        Base  = parent->Base;
        Cpr   = parent->Cpr;
        ScT   = parent->ScT;
        ScA   = parent->ScA;
    }
    Width  = w;
    Height = h;
    PosX   = x;
    PosY   = y;
    Xi =  Yi = 0;
    ScT = ScA = Tiny;
#endif
}

void AstroGraphics::Move(int x, int y)
{
#ifdef QT
    Xi = x + PosX;
    Yi = y + PosY;
#endif
}

void AstroGraphics::Line(int x, int y)
{
#ifdef QT
    Qp->drawLine(Xi, Yi, PosX + x, PosY + y);
    Xi = x + PosX;
    Yi = y + PosY;
#endif
}

void AstroGraphics::DrawDot()
{
    const int r = Size / 10, r2 = r * 2;
#ifdef QT
    const QBrush bref = Qp->brush(), b(Qt::SolidPattern);
    Qp->setBrush(b);
    Qp->drawEllipse(Xi - r, Yi - r, r2, r2);
    Qp->setBrush(bref);
#endif
}

void AstroGraphics::DrawRect(int w, int h)
{
#ifdef QT
    const QBrush bref = Qp->brush(), b(Qp->background().color(), Qt::SolidPattern);
    Qp->setBrush(b);
    Back();
    Qp->drawRect(Xi, Yi, w, h);
    Fore();
    Qp->setBrush(bref);
    Xi = w + PosX;
    Yi = h + PosY;
#endif
}

void AstroGraphics::Circle(int x, int y, int r, bool filled)
{
#ifdef QT
    const QBrush bref = Qp->brush(), b(Qp->pen().color(), Qt::SolidPattern), b1(QColor(0, 0, 0, 0));
    const int r2 = r * 2;
    Qp->setBrush(filled ? b : b1);
    Qp->drawEllipse(x - r + PosX, y - r + PosY, r2, r2);
    if (filled)
        Qp->setBrush(bref);
#endif
}

void AstroGraphics::Color(const AstroColor& ac)
{
#ifdef QT
    if (Asr->IfPrint)
    {
        if (Asr->IfBW)
            Pen->setColor(&ac != Acl->Back ? *Acl->Black : *Acl->White);
        else
            Pen->setColor(&ac == Acl->Back && !Cpr->InvBack ? *Acl->White : ac);
    }
    else
        Pen->setColor(ac);
    Qp->setPen(*Pen);
#endif
}

void AstroGraphics::DrawPixmap(const AstroPixmap& pm, float zoom, enum PixPos pp)
{
#ifdef QT
// 		const AstroPixmap& pm1 = (Asr->IfPrint && Asr->IfBW) ?
// 		SC(const AstroPixmap&, AstroPixmap::fromImage(pm.toImage().convertToFormat(QImage::Format_Mono))) : pm;
    if (pp != Straight)
    {
        QTransform qf;
        qf.rotate((pp == Lying) ? 90.0 :  180.0);
        if (zoom == 1.0)
            Qp->drawPixmap(Xi, Yi, pm.transformed(qf));
        else
            Qp->drawPixmap(Xi, Yi, pm.scaled(int(pm.width() * zoom), int(pm.height() * zoom)).transformed(qf));
    }
    else
    {
        if (zoom == 1.0)
            Qp->drawPixmap(Xi, Yi, pm);
        else
            Qp->drawPixmap(Xi, Yi, pm.scaled(int(pm.width() * zoom), int(pm.height() * zoom)));
    }
#endif
}

void AstroGraphics::Background(const AstroColor& ac)
{
#ifdef QT
    QBrush qb(ac);
    Qp->setBackground(qb);
#endif
}

void AstroGraphics::Dash(int d)
{
#ifdef QT
    Qt::PenStyle ps;
    switch (d)
    {
    case 0:
        ps = Qt::SolidLine;
        break;
    case 1:
        ps = Qt::DashLine;
        break;
    case 2:
        ps = Qt::DashDotLine;
        break;
    case 3:
        ps = Qt::DotLine;
        break;
    default:
        ps = Qt::SolidLine;
    };
    Pen->setStyle(ps);
    Qp->setPen(*Pen);
#endif
}

void AstroGraphics::SetLineWidth(int w)
{
#ifdef QT
    Pen->setWidth(w);
    Qp->setPen(*Pen);
#endif
}
void AstroGraphics::FontSize(enum AstroGraphics::SizeChars sc, bool isastro)
{
    int x, g = isastro ? Asr->IncDecGlyph : 0;
    switch (sc)
    {
    case Very_Tiny :
        x = (Size * 7 * Asr->FontSize) / 100 + g;
        break;
    case Tiny   :
        x = Size * Asr->FontSize / 10 + g;
        break;
    case Medium :
        x = (Size * 14 * Asr->FontSize) / 100 + g;
        break;
    case Large  :
        x = (Size * 20 * Asr->FontSize) / 100 + g;
        break;
    case Huge   :
        x = (Size * 28 * Asr->FontSize) / 100 + g;
        break;
    }
#ifdef QT
    if (isastro)
        astro->setPointSize(x);
    else
        text->setPointSize(x);
#endif
    if (isastro)
        ScA = sc;
    else
        ScT = sc;
}

void AstroGraphics::Text(const AstroString& as, bool movex)
{
#ifdef QT
    Qp->setFont(*text);
    Qp->drawText(Xi, Yi, as);
#endif
    if (movex)
    {
        int w, h;
        TextMetrics(as, &w, &h);
        RMove(w);
    }
}

void AstroGraphics::JustifText(const AstroString& as, enum Justif j, int len, int l2)
{
    int w, h, i1, i2;
    char c;
    AstroString as1;
    TextMetrics(as, &w, &h);
    i1 = (len - w) / 2;
    i2 = len - w - i1;
    switch (j)
    {
    case Left:
        Text(as);
        RMove(len);
        break;
    case Right:
        RMove(len - w);
        Text(as, true);
        break;
    case Center:
        RMove(i1);
        Text(as);
        RMove(i2 + w);
        break;
    case Dot:
        c = as.contains(',') ? ',' : '.';
        as1 = as.section(c, 0, 0);
        TextMetrics(as1, &w, &h);
        i1 = Xi - PosX;
        RMove(l2 - w);
        Text(as1, true);
        Text(QString(c), true);
        as1 = as.section(c , 1);
        Text(as1);
        Move(i1 + len, Yi - PosY);
        break;
    };
}

void AstroGraphics::Sign(enum Signs s)
{
    Glyph(Asg->GetChar(s, *Cpr));
}

void AstroGraphics::Glyph(char c)
{
    charbuf[0] = c;
#ifdef QT
    Qp->setFont(*astro);
    Qp->drawText(Xi, Yi, charbuf);
#endif
}

void AstroGraphics::JustifGlyph(char c, enum Justif justif, int len)
{
    int w, h, i1, i2;
    GlyphMetrics(c, &w, &h);
    i1 = (len - w) / 2;
    i2 = len - w - i1;
    switch (justif)
    {
    case Left:
        Glyph(c);
        RMove(len);
        break;
    case Right:
        RMove(len -w);
        Glyph(c);
        RMove(w);
        break;
    case Center:
        RMove(i1);
        Glyph(c);
        RMove(i2 + w);
        break;
    default:
        ;
    };
    const QBrush bref = Qp->brush(), b(Cpr->InvBack ? *Acl->Fore : *Acl->Back, Qt::SolidPattern);
}

void AstroGraphics::TextMetrics(const AstroString& as, int* width, int* height)
{
#ifdef QT
    Qp->setFont(*text);
    if (width)  *width  = Qp->fontMetrics().width(as);
    if (height) *height = Qp->fontMetrics().height();
#endif
}

void AstroGraphics::GlyphMetrics(char c, int* width, int* height)
{
#ifdef QT
    Qp->setFont(*astro);
    if (width) *width  = Qp->fontMetrics().width(QChar(c));
    if (height) *height = Qp->fontMetrics().height();
#endif
}

void AstroGraphics::DegSignMin(double d, bool name, bool retro, bool seconds)
{
    int a, i, w, w1, h, se, m, m1;
    double x, flx;
    char buf[6], c;
    AstroString as = "000";
    TextMetrics(as, &w, &h);
    i = (int)d / 30;
    x = d - (double)(i * 30);
    flx = floor(x);
    a = (int)flx;
    m = (int)((x - flx) * 10000.0);
    m1 = m / 100;
    //se = ((m % 100) * 60) / 100;
    se = m % 100;
    if (!seconds)
    {
        if (se >= 30)
            m1++;
        if (m1 == 60)
        {
            m1 = 0;
            a++;
        }
        if (a == 30)
        {
            a = 29;
            m1 = 59;
        }
    }
    as = a;
    JustifText(as, Right, w);
    GlyphMetrics(Asg->GetChar(Scorpio, *Cpr), &w1, &h);
    enum Signs s = (enum Signs)(Aries + i);
    if (s > 11) s = Aries;
    c = Asg->GetChar(s, *Cpr);
    JustifGlyph(c, Center, w1);
    sprintf(buf, "%02d'", m1);
    JustifText(buf, Right, (w * 5) / 6);
    if (seconds)
    {
        sprintf(buf, "%02d\"", se);
        as = buf;
        JustifText(as, Right, w);
    }
    if (retro)
        JustifGlyph('!', Left, (w * 2) / 3);
    else
        JustifText("  ", Left, (w * 2) / 3);
}

void AstroGraphics::Hms(double d, const AstroString& sep, bool second)
{
    int h, m, w, s;
    char buf[3];
    AstroString as;
    TextMetrics("0", &w, &h);
    Dhms(d, &h, &m, &s);
    as = (d < 0.0 && h == 0) ? "-" : "";
    as += h;
    JustifText(as, Right, 3 * w);
    Text(sep, false);
    RMove(w, 0);
    sprintf(buf, "%02d", m);
    JustifText(buf, Left, 2 * w + (w / 2));
    if (second)
    {
        as = "\"";
        sprintf(buf, "%02d", s);
        as += buf;
        JustifText(as, Right, w * 2);
    }
}

void AstroGraphics::TextAngle(AstroString& a, float angle)
{
    int w, h;
    if (angle >= PI)
        angle -= PI;
    if (angle <= (PI / 4.0))
    {
        for (int i = 0; i < a.Len(); i++)
        {
            const AstroString& b = a[i];
            TextMetrics(b, &w, &h);
            Text(b);
            RMove(w, - (int)(sinf(angle) * (float)w));
        }
    } else if (angle <= (PI / 2.0))
    {
        for (int i = 0; i < a.Len(); i++)
        {
            const AstroString& b = a[i];
            TextMetrics(b, &w, &h);
            Text(b);
            h /= 2;
            RMove((int)(cosf(angle) * (float)h), - h);
        }
    } else if (angle <= (3.0 * PI / 4.0))
    {
        for (int i = a.Len() -1; i >= 0 ; i--)
        {
            const AstroString& b = a[i];
            TextMetrics(b, &w, &h);
            Text(b);
            h /= 2;
            RMove((int)(cosf(angle) * (float)h), - h);
        }
    } else
    {
        for (int i = a.Len() - 1; i >=  0; i--)
        {
            const AstroString& b = a[i];
            TextMetrics(b, &w, &h);
            Text(b);
            RMove(-w, -(int)(sinf(angle) * (float)w));
        }
    }
}

AstroColorList::AstroColorList()
{
    Fore  = &Ac[0];
    Back  = &Ac[15];
    Grey  = &Ac[7];
// bug ? in color mangement. when Fore = (0,0,0) = pure black  displays light grey text
//because bug above
		if(Fore->red() == 0 && Fore->green() == 0 && Fore->blue() == 0) { Fore = new AstroColor(0 ,0 ,1); }
		Black = new AstroColor(0, 0, 0);
    White = new AstroColor(255, 255, 255);
    for (int i = 0; i < 16; i++)
        ColorPixmaps[i] = new AstroPixmap(80, 60);
}

AstroColorList::AstroColorList(unsigned const char *s)
{
    for (int i = 0; i < 16; i++)
        Ac[i].SetRgb(*s++, *s++, *s++);
    Fore  = &Ac[0];
    Back  = &Ac[15];
    Grey  = &Ac[7];
    Black = new AstroColor(0, 0, 0);
    White = new AstroColor(255, 255, 255);
    for (int i = 0; i < 16; i++)
    {
        ColorPixmaps[i] = new AstroPixmap(80, 60);
        ColorPixmaps[i]->fill(Ac[i]);
    }
}

AstroColorList::~AstroColorList()
{
    for (int i = 0; i < 16; i++)
        delete ColorPixmaps[i];
    //delete Grey;
    delete Black;
    delete White;
}

void AstroColorList::SetColor(AstroColor& ac, int i)
{
    if (i >= 0 && i < 16)
    {
        Ac[i] = ac;
        ColorPixmaps[i]->fill(ac);
    }
}

void AstroColorList::SetColor(unsigned char red, unsigned char green, unsigned char blue, int i)
{
    if (i >= 0 && i < 16)
    {
        Ac[i].SetRgb(red, green, blue);
        ColorPixmaps[i]->fill(Ac[i]);
    }
}

void AstroGraphics::SetWidth(int i)
{
    if (Base->GetWidth() < PosX + i)
        Base->Width = PosX + i;
    Width = i;
}

enum AstroGraphics::Justif GraphicChartBase::GetJustif() const
{
    return Styles[Ts].J;
}

void AstroGraphics::SetHeight(int i)
{
    if (Base->GetHeight() < PosY + i)
        Base->Height = PosY + i;
    Height = i;
}

void AstroGraphics::DrawRing(int ring)
{
    int w, h;
    AstroString as;
    if (ring < 0 || ring >= NBDATA) return;
    Sprintf("%d", &as, ring);
    TextMetrics(as, &w, &h);
    Color(COL[12]);
    Circle(Xi - PosX + w / 2, Yi - PosY - h * 10 / 30, w + w / 3, true);
    Back();
#ifdef QT
    int ps = text->pointSize();
    QFont::StyleStrategy ss = text->styleStrategy();
    text->setBold(true);
    text->setPointSize(ps + 2);
    text->setStyleStrategy(QFont::NoAntialias);
    Text(as, true);
    text->setBold(false);
    text->setPointSize(ps);
    text->setStyleStrategy(ss);
#endif
    RMove(w / 2);
    Fore();
}

GraphicChartBase::GraphicChartBase(ChartBaseParams *cbp, ObjsVector* ov, AstroGraphics *ag) : AstroChartBase(cbp, ov)
{
    Ag = ag;
    Ag->Cpr = cbp;
    FirstLine = 0;
    LastLine = Asr->NbLines;
    Ex = true;
}

void GraphicChartBase::DrawInfo(const AstroObjs& a, int i)
{
    AstroString as, date, time = i18n("No time"), hms, lat, longi, dayl, offs;
    AstroHM hm = a.GetDaylight();
    if (hm.Get() >= 0.0) dayl = "+";
    dayl += hm.Get(as, HM_Time, false, a.To_Second);
    hm = a.GetOffset();
    if (hm.Get() >= 0.0) offs = "+";
    offs += hm.Get(as, HM_Time, false, a.To_Second);
    if (a.Accuracy > -1)
    {
        a.GetTime(time);
        if (a.Accuracy > 0)
            time += Sprintf("%d", &as, a.Accuracy);
    }
    SetTextStyle(SubTitle);
    if (i != -1)
        DrawText(Sprintf("%d: %a, %a, %a, %a", &as, i + 1, &a.GetDate(date), &time, &a.PlaceName, &a.CountryName));
    else
        DrawText(Sprintf("%a, %a, %a, %a", &as, &a.GetDate(date), &time, &a.PlaceName, &a.CountryName));
    NewLine();
    a.Longitude.Get(longi, HM_Longitude, false, a.To_Second);
    a.Latitude.Get(lat, HM_Latitude, false, a.To_Second);
    DrawText(Sprintf(i18n("ST%a, GMT%a, %a %a"), &as, &dayl, &offs, &longi, &lat));
    NewLine();
    enum SubTypeState sts = a.GetState();
    if (sts != Master)
        DrawText(Sprintf(i18n("%a Houses, %a, Geocentric, State: %a"), &as, Asr->HousesSystemNames[(~a)->GetHouse()], Asr->SiderealSystemNames[(~a)->Sidereal + 1], Asr->StateNames[sts]));
    else
        DrawText(Sprintf(i18n("%a Houses, %a, Geocentric"), &as, Asr->HousesSystemNames[(~a)->GetHouse()], Asr->SiderealSystemNames[(~a)->Sidereal + 1]));
    NewLine();
    hm = a.GetSidTime();
    if (a.Accuracy > -1)
    {
        DrawText(Sprintf(i18n("Sidereal time: %a"), &as, &hm.Get(hms, HM_Time, false, a.To_Second)));
        NewLine();
    }
    if (a.GetSubType() != Single && Cbp->Subring != No_Subring)
    {
        DrawText(Sprintf(i18n("%a subring"), &as, Asr->SubringsNames[Cbp->Subring]));
        NewLine();
    }
    if (a.GetSubType() == AddAngle)
        DrawText(Sprintf(i18n("Add Factor: %f"), &as, a.Angle));
    else if (a.GetSubType() == MulAngle)
        DrawText(Sprintf(i18n("Mul factor: %f"), &as, a.Angle));
    NewLine();
}

void GraphicChartBase::Init(bool page, int y)
{
    int size = (5 * Ag->Size) / 2;
    Lines = Tab = CurLine = 0;
    SetTextStyle(PlainText);
    Ag->TextMetrics(" ", 0, &Lh);
    XMargin = YMargin = size;
    W = Ag->Size * 50 - 2 * XMargin;
    H = page ? Ag->GetHeight() - 2 * YMargin : Ag->GetHeight();
    Ag->Move(XMargin, y == -1 ? YMargin : y);
    Ag->Fore();
}

void GraphicChartBase::DrawText(const AstroString& as)
{
    if (Nl()) return;
    Ag->JustifText(as, Styles[Ts].J, W);
}

bool GraphicChartBase::NewLine()
{
    int h, l;
    Tab = 0;
    Ag->TextMetrics(" ", 0, &h);
    CurLine++;
    l = Ag->Yi + h;
#ifdef IFEXCEPT
    if (CurLine >= LastLine)
    {
        AstroString as;
        if (!Ex)
        {
            Ex = true;
            SetHeight(l);
        }
        else
            throw AstroException(ListException, as);
    }
    Lines += h;
#endif
    if (Nl()) return false;
    if (l >= H)
    {
        if (IfPage)
        {
            emit NewPage();
            l = YMargin + h;
            Lines = 0;
        }
        else
            SetHeight(l);
    }
    Ag->Move(XMargin, l);
    return true;
}

void GraphicChartBase::SetTextStyle(enum TextStyle ts)
{
    Ts = ts;
    Ag->FontSize(Styles[Ts].Sc);
    Ag->FontSize(Styles[Ts].Sc, true);
}

void GraphicChartBase::DrawMultiLineText(const AstroString& as)
{
#ifdef QT
    int i = 0, j = 0;
    const QRegExp r("( |\t)+");
    while ((j = as.indexOf('\n', i)) != -1)
    {
        DrawParagraph(SC(AstroString, as.mid(i, j - i)), r);
        //NewLine();
        i = ++j;
    }
    DrawParagraph(SC(AstroString, as.mid(i, as.Len() - j)), r);
#endif
}

void GraphicChartBase::DrawComment(const AstroObjs& ao)
{
    DrawMultiLineText(ao.Comment);
}

void GraphicChartBase::DrawParagraph(const AstroString& as, const QRegExp& r)
{
#ifdef QT
    int nbspace = 0, s = 0, w, h, h1, spw;
    bool rt = false;
    const QStringList qsl = as.split(r);
    QStringList::const_iterator it, p1;
    Ag->TextMetrics(" ", &spw, &h1);
    for (it = p1 = qsl.begin(); it != qsl.end(); it++)
    {
        Ag->TextMetrics(SC(const AstroString&, *it), &w, &h);
        if (s + w <= W)
        {
            s += w + spw;
            nbspace++;
        }
        else
        {
            nbspace--;
            s -= spw;
            int t = (spw * nbspace) + (W - s), sp = t / nbspace, mo = t % nbspace;
            while (p1 != it)
            {
                LText(SC(const AstroString&, *p1), true);
                if (mo)
                {
                    Ag->RMove(sp + 1);
                    mo--;
                }
                else
                    Ag->RMove(sp);
                p1++;
            }
            p1 = it;
            s = w + spw;
            nbspace = 1;
            NewLine();
        }
    }
    while (p1 != qsl.end())
    {
        LText(SC(const AstroString&, *p1), true);
        Ag->RMove(spw);
        p1++;
        rt = true;
    }
    if (rt) NewLine();
#endif
}

int GraphicChartBase::GetSizeLines() const
{
    return Lines - 1;
}

void GraphicChartBase::LText(const AstroString& as, bool movex)
{
    if (Nl()) return;
    Ag->Text(as, movex);
}
