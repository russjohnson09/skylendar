//
// C++ Implementation: tzlist.cpp
//
// Description:
//
//
// Author: C.Gros <skylendar@yahoo.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "tzlist.h"
#include "astroresources.h"

AstroTzList::AstroTzList()
{
}

const Tz* AstroTzList::Search(const char* s, bool inc)
{
    Tz* tz;
    foreach(*this, AstroTzList)
    {
        Tz* tz = *it;
        if (!strcmp(tz->getName(), s)) return inc ? ++(*tz) : tz;
    }
    tz = new Tz(Asr->ZPath);
    if (tz->loadTz(s))
    {
        Append(tz);
        return inc ? ++(*tz) : tz;
    }
    delete tz;
    return 0;
}

void AstroTzList::Remove(const Tz* tz)
{
    int c = Count(), i = 1;
    foreach(*this, AstroTzList)
    {
        Tz* t = *it;
        if (t == tz)
        {
            if ((--(*t))->getCount() == 0)
                AstroList<Tz>::Remove(t);
        }
        if (i++ > c) break;
    }
}
