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
#ifndef SOLARSYSCHART_H
#define SOLARSYSCHART_H

#include "astrographics.h"

/**
This class displays a view of the solar system, straight from above the sun, with a logarithmic scale of the distances

@author Christophe Gros
*/
class SolarSysChart : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(SolarSysChart)

public:
    SolarSysChart(ChartBaseParams*, ObjsVector*);

    ~SolarSysChart();

    bool Redisplay();

private:

    void DrawObj(enum Objs o);
    void GetCoord(int x, int y, double*rx, double* ry) const;
    int W, H, Size;
    float LMax;
		bool Helio;

};

#endif
