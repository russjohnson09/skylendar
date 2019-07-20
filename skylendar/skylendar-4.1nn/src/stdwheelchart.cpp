/***************************************************************************
                          stdwheelchart.cpp  -  description
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

#include "stdwheelchart.h"
#include "astrorings.h"
#include "astrodefs.h"
#include "astroresources.h"

#define HEIGHT 40

StdWheelChart::StdWheelChart(ChartBaseParams *cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ar = nullptr;
    Asb = Asb1 = nullptr;
    Aaf = nullptr;
    Ct = StdWheels;
    Cm = GraphicMode;
    DualChart = true;
    It = Click;
    NbPM = 12;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Central Aspects Ring"), CentralRing);
    PMSET(2, i18n("Aspects Frame"), AspectsFrame);
    PMSET(3, i18n("Displays Seconds"), DisplaySeconds);
    PMSET(4, i18n("Ascendant on the Left"), LeftAscendant);
    PMSET(5, i18n("Side Bars"), Sidebars);
    PMSET(6, i18n("Sort Aspects List"), SortAsp);
    PMSET(7, i18n("Planets Rank"), PlanetsRank);
    PMSET(8, i18n("Outlines"), Outlines);
    PMSET(9, i18n("Comment"), DisplayComment);
    PMSET(10, i18n("Planetary Hour"), PlanetHour);
    PMSET(11, i18n("Colored Sectors"), Sectors);
}

StdWheelChart::~StdWheelChart()
{
    delete Ar;
    delete Asb;
    delete Asb1;
    delete Aaf;
}

void StdWheelChart::DrawChart()
{
    int w, s, size = Ag->GetSize(), h = size * HEIGHT,  y = Cbp->Sidebars ? 105 * h / 100 : 135 * (h + size) / 100;
    AstroString as;
    Large = (Second ? ((First->IfStars() || Second->IfStars())) : (First->IfStars()));
    delete Ar;
    delete Asb;
    delete Asb1;
    delete Aaf;
    if (Cbp->Sidebars)
    {
        if (Count() > 1)
        {
            Asb = new AstroSideBar(Ag, 0, size , size * 15, h - size, Cbp, this, Second);
            w = Asb->GetWidth();
            Ar = new AstroRings(Ag, w, size, h, Cbp, this, Afal, First, Second);
            w += Ar->GetWidth();
            Asb1 = new AstroSideBar(Ag, w, size, size * 15, h - size, Cbp, this, First);
            w += Asb1->GetWidth();
        }
        else
        {
            Ar = new AstroRings(Ag, 0, size, h, Cbp, this, Afal, First, Second);
            w = Ar->GetWidth();
            Asb = new AstroSideBar(Ag, Ar->GetWidth(), size, size * 15, h - size, Cbp, this, First->Show ? First : Second);
            w += Asb->GetWidth();
            Asb1 = nullptr;
        }
    }
    else
    {
        Ar =  new AstroRings(Ag, 0, size, h, Cbp, this, Afal, First, Second);
        w = Ar->GetWidth();
        Asb = Asb1 = nullptr;
    }
    if (Cbp->AspectsFrame)
    {
        Aaf = new AstroAspectsFrame(Ag, 0, y, w, 0, Cbp, this, &Afal, First, Second);
    }
    else
        Aaf = nullptr;
    y += (4 * size) + (Cbp->AspectsFrame ? Aaf->GetHeight() : 0);
    SetWidth(w);
    Init(false, y);
    if (Cbp->DisplayComment)
        DrawComment(*First);
    SetHeight(y + GetSizeLines());
}

void StdWheelChart::ComputeAspects()
{
    AstroAspects aa(Second ? ~(*Second) : ~(*First));
    Afal.GetAspects(aa, Second ? *Second : *First, *First, Second ? IfSamePlanet : 0);
    if (Cbp->SortAsp)
        Afal.Sort(AspectFoundSort);
}

bool StdWheelChart::Redisplay()
{
		HideAll();
    ComputeAspects();
    DrawChart();
    if (Cbp->PlanetsRank)
        First->GetPlanetsRank((Count() == 1) ? &Afal : 0);
    Ar->Repaint();
    if (Asb)  Asb->Repaint();
    if (Asb1) Asb1->Repaint();
    if (Aaf) Aaf->Repaint();
    return true;
}

void StdWheelChart::GetCoord(int x, int y, double *rx, double* ry) const
{
    *rx =  Ar->GetAngle(x, y);
    *ry = -1.0;
}

