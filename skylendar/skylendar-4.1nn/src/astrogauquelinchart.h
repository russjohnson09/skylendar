/***************************************************************************
                          astrogauquelinchart.h  -  description
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

#ifndef ASTROGAUQUELINCHART_H
#define  ASTROGAUQUELINCHART_H

#include "astrographics.h"
#include "astrochartbase.h"

class AstroRings;
class AstroSideBar;
class AstroRestrictions;

class AstroGauquelinChart : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(AstroGauquelinChart)

public:

    /** Constructor */
    AstroGauquelinChart(ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~AstroGauquelinChart();

    /** Overloaded redisplay method */
    bool Redisplay();

private:

    AstroRings *Ar;
    AstroSideBar *Asb;
    AstroRestrictions *Keep, *CurAr;
    AstroFoundAspectsList Afal;
    enum CompModes Cms;
};

#endif
