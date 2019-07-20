/***************************************************************************
 *   Copyright (C) 2005 by Christophe Gros                                 *
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

#include "squared.h"
#include "astroobjs.h"

AstroSquare::AstroSquare(AstroGraphics* parent, const AstroObjs& ao, int i, int x, int y, int w, bool fulline) : AstroGraphics(parent, x, y, w, w)
{
    AstroString as;
    TextMetrics("0", &Size0, &Lh);
    double angle = ao * i;
    Fore();
    Move(0, 0);
    Line(Width, 0);
    Line(Width, Height);
    if (fulline)
        Line(0, Height);
    else
    {
        Line(Size0 * 11, Height);
        Move(0, Height);
    }
    Line(0, 0);
    Move(1, -(3 * Lh) / 6);
    Background(COL[7]);
    DrawRect(Size0 * 11, 5 * Lh / 6);
    Background(Cpr->InvBack ? *Acl->Fore : *Acl->Back);
    Move(1, Lh / 6);
    Color(ao.GetObjColor(i));
    Text(Sprintf(" %d:", &as, i - House_1 + 1), true);
    Color(Asg->GetColor(Asg->GetSign(angle)));
    DegSignMin(DecToDeg(angle));
    LposX = Size0;
    LposY = 0;
}

void AstroSquare::AddPlanets(const AstroObjs& ao, int house)
{
    //if (!(ao == house)) return;
    for (int i = Sun; i <= Pluto; i++)
        if (ao.InHouse(i) == house)
            AddPlanet(ao, i);
    if (ao.IfExtra())
        for (int i = First_Extra; i <= Asr->LastExtra; i++)
            if (ao.InHouse(i) == house)
                AddPlanet(ao, i);
    if (ao.IfStars())
        for (int i = First_Star; i < Final_Star; i++)
            if (ao.InHouse(i) == house)
                AddPlanet(ao, i);
}

void AstroSquare::AddPlanet(const AstroObjs& ao, int i)
{
    double v;
    char c;
    if (ao == i)
    {
        if (LposY + Lh > Height - Lh)
        {
            if (LposX > Size0) return;
            LposX += Size0 * 13;
            LposY = 0;
        }
        LposY += Lh;
        Move(LposX, LposY);
        Color(ao.GetObjColor(i));
        c = ao.GetObjChar(i);
        JustifGlyph(c ? c : ' ', Left, Size0 * 2);
        JustifText(ao < i, Left, 5 * Size0 / 2);
        v = DecToDeg(ao * i);
        if (v >= 360.0) v-= 360.0;
        Color(Asg->GetColor(Asg->GetSign(int(v))));
        DegSignMin(v, false, ao[i]->Retro, false);
    }
}

SquaredChart::SquaredChart(ChartBaseParams* cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = Squared;
    Cm = GraphicMode;
    DualChart = false;
    NbPM = 2;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Comment"), DisplayComment);
    for (int i = 0; i < 12; i++)
        Squ[i] = 0;
}

SquaredChart::~SquaredChart()
{
    for (int i = 0; i< 12; i++)
        delete Squ[i];
}

bool SquaredChart::Redisplay()
{
    int p;
    //GetFS();
    Size = Ag->GetSize();
    W = Size * 16;
    const AstroObjs & ao = *First;
    for (int i = 0; i< 12; i++) delete Squ[i];
    if (!ao().IfHouses()) return false;
    Ag->FontSize(AstroGraphics::Tiny);
    Ag->FontSize(AstroGraphics::Tiny, true);
    Squ[0] = new AstroSquare(Ag, ao, House_1, Size, Size + 2 * W, W);
    Squ[0]->AddPlanets(ao, 1);
    for (int i = 0; i < 4; i++)
    {
        p = House_2 + i;
        Squ[1 + i] = new AstroSquare(Ag, ao, p, Size + i * W, Size + 3 * W, W);
        Squ[1 + i]->AddPlanets(ao, 2 + i);
    }
    for (int i = 0; i < 3; i++)
    {
        p = House_6 + i;
        Squ[5 + i] = new AstroSquare(Ag, ao, p,  Size + 3 * W, Size + (2 - i) * W, W, false);
        Squ[5 + i]->AddPlanets(ao, 6 + i);
    }
    for (int i = 0; i < 3; i++)
    {
        p = House_9 + i;
        Squ[8 + i] = new AstroSquare(Ag, ao, p, Size + (2 * W) - (i * W), Size, W);
        Squ[8 + i]->AddPlanets(ao, 9 + i);
    }
    Squ[11] = new AstroSquare(Ag, ao, House_12, Size, Size + W, W, false);
    Squ[11]->AddPlanets(ao, 12);
    SetWidth(Size + 4 * W);
    SetHeight(2 * Size + 4 * W);
    Init(true, Size + 2 * W - W / 5);
    XMargin += Size * 8;
    Ag->RMove(Size * 8);
    DrawInfo(ao);
    if (Cbp->DisplayComment)
    {
        XMargin += Size * 2;
        Ag->Move(XMargin, 2 * Size + 4 * W);
        NewLine();
        DrawComment(*First);
    }
    return true;
}
