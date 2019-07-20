/***************************************************************************
                          aspconflist.h  -  description
                             -------------------
    begin                : mer oct 15 2003
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

#ifndef ASPCONFLIST_H
#define ASPCONFLIST_H

#include "astrodefs.h"
#include "astrolist.h"
#include "astroaspects.h"

#define NBO 10
/**This class manages a list of
Aspects configurations
  *@author Christophe Gros
  */

class AstroChartBase;

class AspConfData
{
public:

    inline AspConfData() {}
    AspConfData(enum AspConfig ac, unsigned char n, enum Objs o, enum Objs o1, enum Objs o2,
                enum Objs o3 = Undefined_Obj, enum Objs o4 = Undefined_Obj, enum Objs o5 = Undefined_Obj);
    enum AspConfig Ac;
    enum Objs O[NBO];
    unsigned char NbObjs;
} __attribute__((packed));

class AspConfList: public AstroList<AspConfData>
{
public:

    AspConfList();
    ~AspConfList();
    void Compute(const AstroChartBase*);
    unsigned char NbObjs(enum AspConfig ac) const;

private:

    void GetGrand_Trine();
    void GetT_Square();
    void GetStellium();
    void GetGrand_Cross();
    void GetYod();
    void GetMyst_Rectangle();
    void GetDavid_Star();
    bool Already(const AspConfData& acd);
    bool AlreadyTS(const AspConfData& acd);
    inline AspectFound* Search(enum Objs o1, enum Aspects asp = Unknown_Aspect, enum Objs o2 = Undefined_Obj, const AspectFound* af = 0) const
    {
        return CSC(AspectFound*, Afal->Search(o1, asp, o2, af, true));
    }


    AstroFoundAspectsList* Afal;
    AstroChartBase* Acb;
};

#endif
