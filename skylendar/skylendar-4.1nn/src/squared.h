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
#ifndef SQUARED_H
#define SQUARED_H

#include "astrographics.h"
#include "astrochartbase.h"

class AstroObjs;
class AstroColor;

class AstroSquare : public AstroGraphics
{

	Q_DECLARE_TR_FUNCTIONS(AstroSquare)

public:

    AstroSquare(AstroGraphics* parent, const AstroObjs& ao, int i, int x, int y, int w, bool fulline = true);
    ~AstroSquare() {}

    void AddPlanets(const AstroObjs& ao, int house);

private:

    void AddPlanet(const AstroObjs& ao, int i);

    int LposX, LposY, Size0, Lh;

};

class SquaredChart : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(SquaredChart)

public:

    /** Constructor */
    SquaredChart(ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~SquaredChart();

    /** Overloaded redisplay method */
    bool Redisplay();

private:

    int Size, W;
    AstroSquare* Squ[12];
};

#endif
