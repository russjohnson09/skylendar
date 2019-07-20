/***************************************************************************
                          astroephemeris.cpp  -  description
                             -------------------
    begin                : lun sep 22 2003
    copyright            : (C) 2003 by Christophe Gros
    email                : skylendar@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any laterersion.                                   *
 *                                                                         *
 ***************************************************************************/

#include "astroephemeris.h"
#include "stopscan.h"
#include "scanspan.h"

AstroEphemeris::AstroEphemeris(ChartBaseParams* cbp, ObjsVector* ov) : GraphicListBase(this, cbp, ov)
{
    Ct = Ephemeris;
    Cm = GraphicMode;
    It = Buttons;
    DualChart = false;
    NbPM = 1;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
}

AstroEphemeris::~AstroEphemeris()
{
}

void AstroEphemeris::DisplayMonth(Iterator& it)
{
    auto el = SC(EphemLine*, *it);
    unsigned char month = el->month, d = 0;
    AstroString as;
    SetTextStyle(Title);
    DrawText(Sprintf("%a %d", &as, Asr->MonthNames[month], el->year));
    NewLine();
    SetTextStyle(TabText);
    Ag->FontSize(AstroGraphics::Very_Tiny);
    DrawTabText(i18n("Day"));
    DrawTabText(i18n("Planet_Sun"));
    DrawTabText(i18n("Moon"));
    DrawTabText(i18n("Mercury"));
    DrawTabText(i18n("Venus"));
    DrawTabText(i18n("Mars"));
    DrawTabText(i18n("Jupiter"));
    DrawTabText(i18n("Saturn"));
    DrawTabText(i18n("Uranus"));
    DrawTabText(i18n("Neptune"));
    DrawTabText(i18n("Pluto"));
    DrawTabText(i18n("N Node"));
    DrawTabText(i18n("B Moon"));
    NewLine();
    NewLine();
    Ag->FontSize(AstroGraphics::Very_Tiny, true);
    do
    {
        DrawButton();
        DrawTabText(Sprintf("%d", &as, el->day));
        for (int i = 0; i < 12; i++)
        {
            float f = el->val[i];
            if (f != NOVALUE)
                DrawDegSignMin(DecToDeg(fabs(f)), f < 0.0);
            else
                DrawTabText("    -    ");
        }
        el->y = Pos();
        NewLine();
        d = el->day;
        ++it;
        el = SC(EphemLine*, *it);
    }
    while (it == *this && month == el->month);
    while (d++ <= 31) NewLine();
}

#define L(i) l * i - l2

bool AstroEphemeris::Redisplay()
{
    Init();
    int l = W / 8, l2 = l / 2;
    const int tab[] = { 0, L(1), L(2), L(3), L(4), L(5), L(6), L(7), L(8), L(9), L(10), L(11), L(12), L(13) };
    W = L(13);
#ifdef	IFEXCEPT
    try
    {
#endif
        SetTabList(tab);
        SetTextStyle(MainTitle);
        DrawText(i18n("Ephemeris Table at 0h, GMT"));
        NewLine();
        DataLineList::Iterator it(*this);
        while (it == *this)
            DisplayMonth(it);
        NewLine();
        End = true;
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        Ex = false;
        NewLine();
        //Exception(ae);
    }
#endif
    return true;
}

bool AstroEphemeris::PostRecompute()
{
    int c = 0, d, m, y, h, min, sec;
    double begin, end;
    AstroObjs orig(*First);
    if (!Asr->Ctrl && !EditParams()) return false;
    orig.GetDate(&d, &m, &y, &h, &min, &sec);
    Clear();
    h = min = 0;
    if (!orig.DbFetch("ZeroGMT"))
    {
        AstroMessage(i18n("Can't find the DataSet named 'ZeroGMT'"));
        return false;
    }
    orig.SetDate(d, m, y, h, min, sec);
    switch (Asp.Ss)
    {
    case Current_Day   :
        break;
    case Current_Month :
        d = 1;
        break;
    case Current_Year  :
    case Years         :
        d = 1;
        m = 1;
    };
    orig.SetDate(d, m, y, h, min, sec);
    begin = orig.GetJd();
    if (Asp.Ss == Current_Month)
    {
        int m1 = m, y1 = y, i;
        for (i = 28; i <= 32; i++)
        {
            orig.SetDate(i, m, y1, h, min, sec);
            orig.GetDate(&d, &m, &y1, &h, &min, &sec);
            if (m != m1) break;
        }
        d = i - 1;
        m = m1;
        h = min = sec = 0;
    }
    else if (Asp.Ss == Current_Year)
    {
        m = 12;
        d = 32;
    }
    else if (Asp.Ss == Years)
    {
        y += Asp.NbYears;
        m = 12;
        d = 32;
    }
    orig.SetDate(d, m, y, h, min, sec);
    end = orig.GetJd();
    double span = end - begin, bb1 = begin;
    orig.SetJd(begin);
    orig.Recompute();
    orig.GetDate(&d, &m, &y, &h, &min, &sec);
    Ss = new StopScan(this);
    Ss->Set(0);
    do
    {
        auto el = new EphemLine;
        el->jd = begin;
        el->ak = EphemDay;
        el->y = Pos();
        el->day = d;
        el->month = m - 1;
        el->year = y;
        for (int i = Sun; i <= Pluto; i++)
					el->val[i] = (orig() == i) ? (orig * i) * (orig[i]->Retro ? -1.0 : 1.0) : NOVALUE;
        el->val[10] = (orig() == North_Node) ? orig * North_Node : NOVALUE;
        el->val[11] = (orig() == Black_Moon) ? orig * Black_Moon : NOVALUE;
        Append(el);
        begin += 1.0;
        orig.SetJd(begin);
        orig.Recompute();
        orig.GetDate(&d, &m, &y, &h, &min, &sec);
        if (c++ % 20) P;
        Ss->Set(int((begin - bb1) * 100.0 / span));
    } while (begin < end);
    First->Recompute();
    delete Ss;
    return true;
}

const EphemLine* AstroEphemeris::GetEphemLine(int day, int month, int year)
{
    month--;
    foreachc(*this, DataLineList)
    {
        auto el = SC(const EphemLine*, (!it)/*dl*/);
        if (el->year == year && el->month == month && el->day == day)
            return el;
    }
    return 0;
}

