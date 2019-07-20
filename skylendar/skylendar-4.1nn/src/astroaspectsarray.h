/***************************************************************************
                          astroaspectsarray.h  -  description
                             -------------------
    begin                : sam ao 9 2003
    copyright            : (C) 2003 by Christophe Gros
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

#ifndef ASTROASPECTSARRAY_H
#define ASTROASPECTSARRAY_H

#include "astrographics.h"
#include "astrochartbase.h"
#include "astroaspects.h"

/**This class displays an array of aspects/midpoints
  *@author Christophe Gros
  */

class AstroAspectsArray : public GraphicChartBase  {

	Q_DECLARE_TR_FUNCTIONS(AstroAspectsArray)

public:

    AstroAspectsArray(ChartBaseParams*, ObjsVector*);
    ~AstroAspectsArray();

    /** Overloaded */
    const AstroFoundAspectsTable* GetAspectsTable() const {
        return &Afat;
    }

    /** Overloaded */
    inline const AstroMidPoints* GetMidPoints() const {
        return Afat.GetAmp();
    }

    bool Redisplay();

private:

    int Px, Py, S, C1, C2, W, H;
    void DrawPlanet(int x, int y, enum Objs);
    void DrawAspect(int x, int y, const AspectFound&);
    void DrawMidpoint(int x, int y, float);
    AstroFoundAspectsTable Afat;
    AstroAspects* Aa;
};

#endif
