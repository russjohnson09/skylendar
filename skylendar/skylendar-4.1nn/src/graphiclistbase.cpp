/***************************************************************************
                          graphiclistbase.cpp  -  description
                             -------------------
    begin                : mer ao 21 2002
    copyright            : (C) 2002 by Christophe Gros
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

#include "graphiclistbase.h"
#include <cstdio>
#include <iostream>

#ifdef QT
# include <QPixmap>
#endif

#define MAXBTN 50

GraphicListBase::GraphicListBase(DataLineList* dll, ChartBaseParams* cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Dll = dll;
    Cm = GraphicMode;
    DualChart = false;
    End = false;
}

void GraphicListBase::Init()
{
    TabList = 0;
    End = false;
    Ag->TextMetrics("O", &Ow, 0);
    Ag->TextMetrics(" 000", &Four0, 0);
    Ag->GlyphMetrics('7', &Seven, 0);
    Ag->SetWidth(Ag->GetWidth() + Ag->GetWidth() / 2);
    GraphicChartBase::Init(true);
}

GraphicListBase::~GraphicListBase()
{
}

void GraphicListBase::DrawButton()
{
    if (Nl()) return;
    Ag->RMove(-2 * Ow);
    Ag->Color(COL[3]);
    Ag->Text(IfPage ? " " : "X");
    Ag->Fore();
    Ag->RMove(2 * Ow);
}

int GraphicListBase::Pos() const
{
    return Ag->GetY() - Lh / 2;
}

const DataLineBase* GraphicListBase::GetCoord(int x, int y) const
{
    DataLineList& dll = *(DataLineList*)SC(const DataLineList*, Dll);
    foreachc(*Dll, DataLineList)
    {
        if (y > (!it)->y -2 && y < (!it)->y + 6) return (!it);
    }
    return 0;
}

const DataLineBase* GraphicListBase::GetNext(const DataLineBase* ref, unsigned int i) const
{
    DataLineList& dll = *(DataLineList*)SC(const DataLineList*, Dll);
    DataLineList::Const_Iterator it1(*Dll);
    foreachc(*Dll, DataLineList)
    {
        if ((!it)->y == ref->y)
        {
            it1 = it;
            for (unsigned int j = 1; j <= i && it1 == *Dll; j++, it1++) {}
            return ((!it1)->y == ref->y) ? (!it1) : 0;
        }
    }
    return 0;
}

const AstroString& GraphicListBase::Dbl(AstroString& as, double d, bool four, bool sci)
{
    char buf[12];
    if (four)
        sprintf(buf, sci ? "%.4e" : "%.4f", d);
    else
        sprintf(buf, sci ? "%.2e" : "%.2f", d);
    as = buf;
    return as;
}

void GraphicListBase::DrawDegSignMin(double val, bool retro)
{
    int l = TabList[Tab + 1] - TabList[Tab], x = Ag->Xi;
    if (Nl()) return;
    Ag->Xi -= Ow;
    Ag->DegSignMin(val, false, retro);
    Ag->Move(x + l, Ag->Yi);
    Tab++;
}

void GraphicListBase::SetTabList(const int *t, bool centered)
{
       TabList = CSC(int*, t);
       if(centered)
       {
          int last = -1, c;
          for(int i = 0; TabList[i] != -1; i++)
              last = TabList[i];
          Offs = (W - last) / 2;
          if(Offs < 0) Offs = 0;
       }
}

void GraphicListBase::DrawTabText(const AstroString& as)
{
    int l;
    if (Nl()) return;
    if(TabList[Tab + 1] == -1)
        Ag->TextMetrics(as, &l);
    else
        l = TabList[Tab + 1] - TabList[Tab];
    Ag->JustifText(as, GetJustif(), l, Four0);
    if(TabList[Tab] != -1) RightMost = Ag->Xi;
    Tab++;
}

void GraphicListBase::DrawTabGlyph(char c)
{
    if (Nl()) return;
    Ag->JustifGlyph(c, AstroGraphics::Center, Seven);
    Ag->RMove(Seven);
    Tab++;
}

void GraphicListBase::NewLine(bool horline)
{
   GraphicChartBase::NewLine();
   if(horline)
   {
       Ag->Move(Offs, Ag->Yi);
       Ag->Line(RightMost, Ag->Yi);
   }
   Ag->Move(Offs, Ag->Yi);
}


