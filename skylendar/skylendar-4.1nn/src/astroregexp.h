/***************************************************************************
 *   Copyright (C) 2006 by Christophe Gros                                 *
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
#ifndef ASTROREGEXP_H
#define ASTROREGEXP_H
#include "../config.h"

#include "astrostring.h"

#ifdef QT
#include <QRegExp>
#endif

/**
This class implements an easy to use regular edpression pattern marching

@author Christophe Gros
*/
class AstroRegExp :
#ifdef QT
            public QRegExp
#endif
{
public:

    /** Constructor */
    inline AstroRegExp() {}

    /** Constructor */
    inline AstroRegExp(const AstroString& pat)
#ifdef QT
            :
            QRegExp(pat)
#endif
    {}

    /** Sets the wanted pattern */
    inline void operator = (const AstroString& pat)
    {
#ifdef QT
        setPattern(pat);
#endif
    }
    /** Performs the pattern search */
    inline bool operator < (const AstroString& text) const
    {
#ifdef QT
        return (indexIn(text) == -1) ? false : true;
#endif
    }

    /** Performs pattern search and return pos of first match */
    inline int operator <= (const AstroString& text) const
    {
#ifdef QT
        return indexIn(text);
#endif
    }


    /** Returns the ith captured substring */
    inline const AstroString operator / (int i)
    {
#ifdef QT
        return AstroString(cap(i));
#endif
    }
};

#endif
