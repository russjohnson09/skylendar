/***************************************************************************
 *   Copyright (C) 2004 by Christophe Gros                                 *
 *   skylendar@yahoo.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "solarsyschart.h"
#include "astrochart.h"

SolarSysChart::SolarSysChart(ChartBaseParams* cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = SolarSys;
    Cm = GraphicMode;
    DualChart = false;
    It = Click;
    NbPM = 1;
		AstroRestrictions* ar = ~*First;
    Helio = ar->Heliocentric;
		ar->Heliocentric = true;
    ar->Restrict(The_Earth, false);
    First->GetAstroChart()->UpdateRestrict(ar);
    First->Recompute();
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
}


SolarSysChart::~SolarSysChart()
{
	AstroRestrictions* ar = ~*First;
	ar->Heliocentric = Helio;
	First->GetAstroChart()->UpdateRestrict(ar);
	First->Recompute();
}

bool SolarSysChart::Redisplay()
{
    AstroHM hm;
    double maxdist = 0.0;
    int w;
		AstroRestrictions* ar = ~*First;
    //GetFS();
		Ag->TextMetrics("X", &w, &H);
    Size = Ag->GetSize();
    W = Size * 50;
    Ag->FontSize(AstroGraphics::Tiny, true);
    Ag->FontSize(AstroGraphics::Tiny, false);
    const AstroObjs& a = *First;
    for (int i = Sun; i <= Pluto ; i++)
        if (a == i && i != Moon && (*a[i])[2] > maxdist) maxdist = (*a[i])[2];
    for (int i = The_Earth; i <= Vesta ; i++)
        if (a == i && (*a[i])[2] > maxdist) maxdist = (*a[i])[2];
    if (a == XPoint && (*a[XPoint])[2] > maxdist) maxdist = (*a[XPoint])[2];
    if (ar->IfExtra())
        for (int i = First_Extra; i <= Asr->LastExtra ; i++)
            if (a == i && (*a[i])[2] > maxdist) maxdist = (*a[i])[2];
    LMax =  log10f(maxdist + 1.0);
    for (int i = Sun; i <= Pluto ; i++)
        if (a == i && i != Moon) DrawObj((enum Objs)i);
    for (int i = The_Earth; i <= Vesta ; i++)
        if (a == i) DrawObj((enum Objs)i);
    if (a == XPoint) DrawObj(XPoint);
    if (ar->IfExtra())
        for (int i = First_Extra; i <= Asr->LastExtra ; i++)
            if (a == i) DrawObj((enum Objs)i);
    if (a == XPoint)
    {
        AstroString as;
        Ag->Move(W, W);
        Ag->Fore();
        double dist = (*a[XPoint])[2], angle = a * XPoint;
        hm = angle;
        Ag->Text(Sprintf(i18n("Angle: %a Dist: %f UA"), &as, &hm.Get(as, HM_Degrees), dist));
    }
    Init(false, W + 2 * Size);
    DrawInfo(a, First->GetRing());
    if (Cbp->DisplayComment)
        DrawComment(a);
		SetWidth(W);
    SetHeight(W + 2 * Size + GetSizeLines());
    
    return true;
}

void SolarSysChart::DrawObj(enum Objs o)
{
    int x, y, l, w, h, m = W / 2, mxy = m + W / 25;
    const AstroObjs& a = *First;
    float angle = DEGRAD(a * o);
    l = int((log10f((*a[o])[2] + 1.0) * m) / LMax);
    x = int(l * cosf(angle));
    y = int(l * sinf(angle));
    char c = a.GetObjChar(o);
    if (c)
    {
        Ag->GlyphMetrics(c, &w, &h);
        Ag->Move(-x - w / 2 + mxy, y + h / 2 + mxy);
        Ag->Color(a.GetObjColor(o));
        Ag->Glyph(c);
    }
    else
    {
        Ag->TextMetrics(a < o, &w, &h);
        Ag->Move(-x - w / 2 + mxy, y + h / 2 + mxy);
        Ag->Color(a.GetObjColor(o));
        Ag->Text(a < o);
    }
}

void SolarSysChart::GetCoord(int x, int y, double*rx, double* ry) const
{
    int m = W / 2, mxy = m + W / 25, dx = -x + mxy, dy = y - mxy  - H / 4;
    float angle = (dy < 0) ? TWOPI + atan2f(dy, dx) : atan2f(dy, dx), dist = powf(10.0, sqrtf(dx * dx + dy * dy) * LMax / m) - 1.0;
    if (rx) *rx = RADDEG(angle);
    if (ry) *ry = dist;
}
