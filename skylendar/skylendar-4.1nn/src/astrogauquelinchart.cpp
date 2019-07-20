/***************************************************************************
                          astrogauquelinchart.cpp  -  description
                             -------------------
    begin                : Wed Nov 26 2008
    copyright            : (C) 2008 by Christophe Gros
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

#include "astrogauquelinchart.h"
#include "astrorings.h"

#define HEIGHT 40

AstroGauquelinChart::AstroGauquelinChart(ChartBaseParams* cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = Gauquelin;
    Cm = GraphicMode;
    DualChart = false;
    NbPM = 3;
    Ar = 0;
    Asb = 0;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Central Aspects Ring"), CentralRing);
    PMSET(2, i18n("Side Bars"), Sidebars);
    Keep = ~(*First);
    CurAr = new AstroRestrictions(*Keep);
    //CurAr->RestrictAll();
    CurAr->RestHouses(false);
    CurAr-> RestStars(false);
    for (int i = North_Node; i < Chiron;i++)
        CurAr->Restrict(i, true);
    for (int i = Fortune; i <= East_Point; i++)
        CurAr->Restrict(i, true);
    for (int i = XPoint; i <= Descendant; i++)
        CurAr->Restrict(i, true);
    Cms = First->GetCms();
}

AstroGauquelinChart::~AstroGauquelinChart()
{
    delete Ar;
    delete Asb;
    delete CurAr;
    First->SetRestrict(Keep);
    First->SetCms(Cms);
}

bool AstroGauquelinChart::Redisplay()
{
    int w, s, size = Ag->GetSize(), h = size * HEIGHT,  y = Cbp->Sidebars ? 105 * h / 100 : 135 * (h + size) / 100;
    AstroString as;
    AstroObjs& a = *First;
    delete Ar;
    delete Asb;
    a.SetRestrict(CurAr);
    a.SetCms(Gauq);
    AstroAspects aa(~a);
    Afal.GetAspects(aa, a, a, 0);
    if (Cbp->SortAsp)
        Afal.Sort(AspectFoundSort);
    if (Cbp->Sidebars)
    {
        Ar = new AstroRings(Ag, 0, size, h, Cbp, this, Afal, &a, Second);
        w = Ar->GetWidth();
        Asb = new AstroSideBar(Ag, Ar->GetWidth(), size, size * 15, h - size, Cbp, this, &a);
        w += Asb->GetWidth();
    }
    else
    {
        Ar =  new AstroRings(Ag, 0, size, h, Cbp, this, Afal, &a, Second);
        w = Ar->GetWidth();
        Asb = 0;
    }
    y += 4 * size;
    SetWidth(w);
    Init(false, y);
    if (Cbp->DisplayComment)
        DrawComment(a);
    SetHeight(y + GetSizeLines());
    Ar->Repaint();
    if (Asb)  Asb->Repaint();
    return true;
}
