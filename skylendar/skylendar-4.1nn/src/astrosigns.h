/***************************************************************************
                          astrosigns.h  -  description
                             -------------------
    begin                : Sat Sep 30 2000
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

#ifndef ASTROSIGNS_H
#define ASTROSIGNS_H

// Just a forward declaration to avoid problems
class AstroSigns;
class AstroColor;
class ChartParams;

#include "astrostring.h"
#include "astrodefs.h"

/**This class provides all the information about the 12 signs,
such as name, master, etc...
  *@author Christophe Gros
  */
struct Ruling
{
    enum Objs Ruler, Co_Ruler, Fall, Co_Fall, Exalt, Debil;
};

struct RuledSigns
{
    enum Signs Ruled, Co_Ruled, Fall, Co_Fall, Exalt, Debil;
};

struct TermDeg
{
    enum Objs o;
    unsigned char deg;
};

typedef struct TermDeg SignTerms[5];

/** The signs management class */
class AstroSigns {
public:

    /** Constructor */
    AstroSigns();

    /** Destructor */
    ~AstroSigns();

    /** Returns the name of the given sign */
    const AstroString& operator << (int) const;

    /** Returns the short name of the given sign */
    const AstroString& operator < (int) const;

    /** This method and op return a reference of the ruling structure for a given sign */
    inline const struct Ruling& GetRulers(enum Signs s, bool south) const
        {
            return south ? South(s) : RulersTable[s];
        }

    /* inline const struct Ruling& operator * (enum Signs s) const */
    /* 		{ */
    /* 			return Ao->IsSouthern() ? South(s) : RulersTable[s]; */
    /* 		} */

    /** This method returns The ruled signs structure for the given object (planet, etc...) */
    void GetRuled(struct RuledSigns& r, enum Objs o, bool south) const;

    /** Returns the Element of the given sign */
    enum Elements GetElement(enum Signs) const;

    /** Returns the color of the given sign */
    const AstroColor& GetColor(enum Signs) const;

    /** returns the sign of the position at an angle of "angle" */
    enum Signs GetSign(double angle) const;

    /** Returns the character from ASTROFONT corresponding to the given sign */
    char GetChar(enum Signs s, const ChartParams&) const;

private:

    char *Sc;
    struct Ruling RulersTable[12];
    const struct Ruling& South(int i) const;
};

#endif
