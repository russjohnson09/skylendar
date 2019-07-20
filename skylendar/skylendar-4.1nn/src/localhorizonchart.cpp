/***************************************************************************
                          localhorizonchart.cpp  -  description
                             -------------------
    begin                : lun jun 2 2003
    copyright            : (C) 2003 by Christophe Gros
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

#include "localhorizonchart.h"
#include "astroobjs.h"
#include "astrochartbase.h"
#include "astroconstellations.h"

#define MAXX 24
#define MAXY 18

class PolyAg : public AstroGraphics
{
public:

	inline void DrawPolygon(const QPolygon& a, int index = 0, int npoints = -1) {
        Qp->drawPolygon(a);
    }
};

LocalHorizonChart::LocalHorizonChart(ChartBaseParams* cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = LocalHorizon;
    Cm = GraphicMode;
    DualChart = false;
    SizeX = MAXX;
    SizeY = MAXY;
    NbPM = 3;
    Cms = First->GetCms();
		First->SetCms(Local);
		AstroRestrictions& ar = *~(*First);
		h = ar.IfHouses();
		ar.RestHouses(false);
		Mask = Cbp->Qw->mask();
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Comment"), DisplayComment);
		PMSET(2, i18n("Display constellations"), Constellations);
}

LocalHorizonChart::~LocalHorizonChart()
{
    First->SetCms(Cms);
		Cbp->Qw->setMask(Mask);
		AstroRestrictions& ar = *~(*First);
		ar.RestHouses(h);
}

extern "C"
{
    static int comparhor(const void* a, const void* b)
    {
        const struct LocalHorizonChart::Pos *pa = (const struct LocalHorizonChart::Pos *)a, *pb = (const struct LocalHorizonChart::Pos *)b;
        if (pa->y == pb->y) return 0;
        if (pa->y < pb->y) return -1;
        return 1;
    }
}

bool LocalHorizonChart::Redisplay()
{
    int j = 0, w, h, d, e;
    AstroString as, as1, hour, acc;
		const _AstroRestrictions& ar = (*First)();
    Ag->FontSize(AstroGraphics::Tiny);
    Ag->TextMetrics("OOO", &w, &h);
    SizeOOO = w;
    Size = Ag->GetSize();
    W = Size * 50;
    H = Size * 40;
    T = W / 72;
    U = H / 36;
    W = T * 72;
    H = U * 36;
    W += T;
    H += U;
    d = 2 * T;
    e = U;
    First->SetConstel(Cbp->Constellations);
    if(Cbp->Constellations)
    {
        DisplayCons();
    }
    Ag->Fore();
    Ag->Move(T, U);
    Ag->Line(W, U);
    Ag->Line(W, H);
    Ag->Line(T, H);
    Ag->Line(T, U);
    Ag->Move(T, U + 18 * e);
    Ag->Line(W, U + 18 * e);
    Ag->Move(T + 18 * d, U);
    Ag->Line(T + 18 * d, H);
    for (int i = T, k = 0; i <= W; i += d, k += 5)
    {
        Ag->Move(i, U);
        Ag->Line(i, !(k % 30) ? U + (U / 2) : U + (U / 3));
        Ag->Move(i, H);
        Ag->Line(i, !(k % 30) ? H - (U / 2) : H - (U / 3));
    }
    for (int i = U, k = 0; i <= H; i += e, k += 5)
    {
        Ag->Move(T, i);
        Ag->Line(!(k % 30) ? T + (T / 2) : T + (T / 3), i);
        Ag->Move(W, i);
        Ag->Line(!(k % 30) ? W - (T / 2) : W - (T / 3), i);
    }
    Ag->Grey();
    Ag->Move(T + 9 * d, U);
    Ag->Line(T + 9 * d, H);
    Ag->Move(T + 27 * d, U);
    Ag->Line(T + 27 * d, H);
    Ag->TextMetrics(i18n("E"), &w, &h);
    Ag->Move(T + 9 * d - w / 2, H + U);
    Ag->Text(i18n("E"));
    Ag->TextMetrics(i18n("S"), &w, &h);
    Ag->Move(T + 18 * d - w / 2, H + U);
    Ag->Text(i18n("S"));
    Ag->TextMetrics(i18n("W"), &w, &h);
    Ag->Move(T + 27 * d - w / 2, H + U);
    Ag->Text(i18n("W"));
    Ag->Fore();
    Ag->FontSize(AstroGraphics::Large, true);
    auto f = [&](int i)
    {
        if(i >= Ascendant && i <= House_12) return;
        auto x =(*(*First)[i])[0], y = (*(*First)[i])[1];
        Pos[j].x = int(x);
        Pos[j].y = int(y);
        Pos[j++].o = SC(enum Objs, i);
    };
    ar(f);
    for (int i = 0; i < j; i++)
			ReCoord(Pos[i].x, Pos[i].y);
    qsort(Pos, j, sizeof(struct Pos), comparhor);
    for (int i = 0; i < j; i++)
        Place(i, j);
    for (int i = 0; i < j; i++)
    {
        int gw, gh;
        const struct Pos& p = Pos[i];
        const char c = First->GetObjChar(p.o);
        if (c)
        {
            Ag->GlyphMetrics(c, &gw, &gh);
            Ag->Move(p.px - gw / 2, p.py);
            Ag->Color(First->GetObjColor(p.o));
            Ag->Glyph(c);
            Ag->Move(p.x, p.y);
            Ag->Fore();
            Ag->DrawDot();
            Ag->Grey();
            const int xx = abs(p.px /*- gw / 2*/) - p.x, yy = abs(p.py - gh / 2) - p.y;
            Ag->Line((xx / 2) + p.x, (yy / 2) + p.y);
            Ag->Fore();
        }
        else
        {
            Ag->TextMetrics((*First) < p.o, &gw, &gh);
            Ag->Move(p.px - gw / 2, p.py);
            Ag->Color(First->GetObjColor(p.o));
            Ag->JustifText((*First) < p.o, AstroGraphics::Center, SizeOOO);
            Ag->Move(p.x, p.y);
            Ag->Fore();
            Ag->DrawDot();
            Ag->Grey();
            const int xx = abs(p.px /*+ gw / 2*/) - p.x, yy = abs(p.py /*-gh / 2*/) - p.y;
            Ag->Line((xx / 2) + p.x, (yy / 2) + p.y);
            Ag->Fore();
        }
    }
    Init(false, H + 3 * h);
    DrawInfo(*First, First->GetRing());
    if (Cbp->DisplayComment)
        DrawComment(*First);
		SetWidth(W);
    SetHeight(H + 3 * h + GetSizeLines());
		Cbp->Qw->setMask(QRegion(T, U, W - (W / 72), Ag->GetHeight()));
    return true;
}

void LocalHorizonChart::ReCoord(short& x, short& y) const
{
    int w, h;
    w = T + (int)(W * (x + 180.0) / 360.0);
    if (w > W) w -= W;
    if (w < T) w += W - T;
    h = U + (int)((H * (90.0 - y)) / 180.0);
    if (h > H) h -= H;
    if (h < U) h += H - U;
    x = w;
    y = h;
}

void LocalHorizonChart::Place(int i, int j)
{
    struct Pos& p = Pos[i];
    short x, y, d = SizeOOO;
    if (i == 0)
    {
        p.px = p.x;
        p.py = p.y + d;
        return;
    }
    while (d <= 3 * SizeOOO)
    {
        for (float f = 0.0; f <= 360.0; f += 22.5)
        {
            bool b = true;
            x = p.x;
            y = p.y;
            Angle(x, y, d, f);
            for (int k = 0; k < i; k++)
            {
                const struct Pos& p1 = Pos[k];
                if (!CheckDist(x, y, p1.px, p1.py, SizeOOO))
                {
                    b = false;
                    break;
                }
            }
            if (b)
            {
                for (int k = 0; k < j; k++)
                {
                    const struct Pos& p1 = Pos[k];
                    if (!CheckDist(x, y, p1.x, p1.y, SizeOOO) && p1.o != p.o)
                    {
                        b = false;
                        break;
                    }
                }
            }
            if (b && x >= T && y >= U)
            {
                p.px = x;
                p.py = y;
                return;
            }
        }
        d += SizeOOO / 3;
    }
}

void LocalHorizonChart::DisplayCons()
{
	auto pag = SC(PolyAg*, Ag);
	pag->Grey();
	pag->FontSize(AstroGraphics::Very_Tiny);
	for(int i = 0; i < NBC; i++)
	{
		QPolygon qp;
		const AstroConstellations* Ac = First->GetAct();
		int cx = 0, cy = 0, j = 0;
		for(ConstData* cd = Ac->Des[i]; cd->x != 1000.0; j++, cd++)
		{
			bool ltx = false;
			short x = cd->x, y = cd->y, t = 2 * W / 3;
			y = U + int((H * (90.0 - cd->y)) / 180.0);
			x = T + int(W * (cd->x + 180.0) / 360.0);
			x -= (W -T) / 2;

			if (!qp.isEmpty() && (x - qp.last().x()) > t)
			{
				x = T - (x - W);
			}
			if(!qp.isEmpty() && (qp.last().x() - x) > t)
			{
				x = W + (x - T);
			}
			qp << QPoint(x, y);
			cx += x;
			cy += y;
		}
		if(j)
		{
			int w, h;
			cx /= j;
			cy /= j;
			pag->Grey();
			pag->DrawPolygon(qp);
			pag->TextMetrics(Ac->Names[i], &w, &h);
			cx -= w /2;
			cy += h /2;
			if(cx + w  > W) cx -= (cx + w - W + (w /Ac->Names[i].Len()));
			if(cx < T) cx += (T - cx + w /Ac->Names[i].Len());
			pag->Move(cx, cy);
			pag->Color(COL[10]);
			pag->Text(Ac->Names[i]);
		}
	}
}

#undef MAXY
