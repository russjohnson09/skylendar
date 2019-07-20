//
// C++ Interface: tzlist.h
//
// Description:
//
//
// Author: C.Gros <skylendar@yahoo.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef TZLIST_H
#define TZLIST_H
#include "tz.h"
#define _TM_DEFINED
#include "astrostring.h"
#include "astrolist.h"

class AstroTzList: public AstroList<Tz>
{

public:

    AstroTzList();
    const Tz* Search(const char *, bool inc = true);
    void Remove(const Tz*);
};
#endif
