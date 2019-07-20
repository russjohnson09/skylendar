/***************************************************************************
                          astromidpoints.cpp  -  description
                             -------------------
    begin                : lun f� 2 2004
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

#include "astromidpoints.h"

AstroMidPoints::~AstroMidPoints()
{
}

void AstroMidPoints::ComputeMP(const Values& v1, const _AstroRestrictions& ar1, const Values& v2, const _AstroRestrictions& ar2, bool ifsame)
{
    int x = Last_Planet, y = Last_Planet;
    float v = NOVALUE;
    if (ar1.IfExtra())  x = ar1.LastExtra;
    if (ar1.IfHouses()) x = House_12;
    if (ar2.IfExtra())  y = ar2.LastExtra;
    if (ar2.IfHouses()) y = House_12;
    x++;
    y++;
    Create(x, y, &v);
    for (int i = Sun; i < x; i++)
    {
        if (i > House_12 && i < First_Extra) continue;
        if (ar1 == i)
        {
            for (int j = Sun; j < y; j++)
            {
                if (j > House_12 && j < First_Extra) continue;
                if (ar2 == j)
                {
                    if (!ifsame)
                    {
                        if (i == j) continue;
                        Get(i, j) = Get(j, i) = MidPoint(v1.Get(i), v2.Get(j));
                    }
                    else
                    {
                        Get(i, j) = MidPoint(v1.Get(i), v2.Get(j));
                        Get(j, i) = MidPoint(v2.Get(i), v1.Get(j));
                    }
                }
            }
        }
    }
}
