/***************************************************************************
                          stdwheelchart.h  -  description
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

#ifndef STDWHEELCHART_H
#define STDWHEELCHART_H

#include "astrographics.h"
#include "astrochartbase.h"
#include "astroaspects.h"

class AstroRings;
class AstroSideBar;
class AstroAspectsFrame;

/** This class manages the standard wheel chart
    (concentric rings with zodiac, houses, up to 4 planets rings and aspects
*/
class StdWheelChart : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(StdWheelChart)

public:

    /** Constructor */
    StdWheelChart(ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~StdWheelChart();

    /** Overloaded redisplay method */
    bool Redisplay();

    /** Return the aspects list */
    inline const AstroFoundAspectsList* GetAspectsList() const {
        return &Afal;
    }

private:

    void DrawChart();
    void ComputeAspects();
    AstroRings *Ar;
    /** Returns the angle in degrees corresponding to x, y */
    void GetCoord(int x, int y, double*rx, double* ry) const;
    AstroSideBar *Asb, *Asb1;
    AstroAspectsFrame * Aaf;
    AstroFoundAspectsList Afal;
};
#endif
