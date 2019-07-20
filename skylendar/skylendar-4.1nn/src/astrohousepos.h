/***************************************************************************
                          astrohousepos.h  -  description
                             -------------------
    begin                : Wed Jan 6 2010
    copyright            : (C) 2010 by Christophe Gros
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

#ifndef ASTROHOUSEPOS_H
#define  ASTROHOUSEPOS_H

#include "astrographics.h"
#include "astrochartbase.h"

class AstroRings;
class AstroSideBar;
class AstroRestrictions;

class AstroHousePos : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(AstroHousePos)

public:

    /** Constructor */
    AstroHousePos(ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~AstroHousePos();

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
