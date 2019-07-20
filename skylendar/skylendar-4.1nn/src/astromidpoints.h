/***************************************************************************
                          astromidpoints.h  -  description
                             -------------------
    begin                : lun f�v 2 2004
    copyright            : (C) 2004 by Christophe Gros
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

#ifndef ASTROMIDPOINTS_H
#define ASTROMIDPOINTS_H

#include <astrotable.h>
#include "astroobjs.h"

/**This class manages an array of midpoints
  *@author Christophe Gros
  */

class AstroMidPoints : public AstroTable<float>
{
public:

    AstroMidPoints() {}

    AstroMidPoints(const Values& v1, const _AstroRestrictions& ar1, const Values& v2, const _AstroRestrictions& ar2, bool ifsame = false)
    {
        ComputeMP(v1, ar1, v2, ar2, ifsame);
    }

    AstroMidPoints(const AstroObjs& a, const AstroObjs& b, bool ifsame = false)
    {
			ComputeMP(a.Vals, a(), b.Vals, b(), ifsame);
    }

    void ComputeMP(const Values& v1, const _AstroRestrictions& ar1, const Values& v2, const _AstroRestrictions& ar2, bool ifsame = false);

    void ComputeMP(const AstroObjs& a, const AstroObjs& b, bool ifsame = false)
    {
			ComputeMP(a.Vals, a(), b.Vals, b(), ifsame);
    }

    ~AstroMidPoints();
};

#endif
