/***************************************************************************
                          astrosigns.cpp  -  description
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

#include "astrosigns.h"
#include "astroresources.h"
#include "astroparams.h"
#include "astrographics.h"
#include "astrodefs.h"

AstroSigns::AstroSigns()
{
    int i, *k = Asr->Rulers;
    struct Ruling *r = RulersTable;
    Sc = CSC(char *, SIGNCHARS);
    for (i = Aries; i <= Pisces; i++, r++)
    {
        r->Ruler    = (enum Objs)*k++;
        r->Co_Ruler = (enum Objs)*k++;
        r->Fall     = (enum Objs)*k++;
        r->Co_Fall  = (enum Objs)*k++;
        r->Exalt    = (enum Objs)*k++;
        r->Debil    = (enum Objs)*k++;
    }
}

AstroSigns::~AstroSigns() {
}

const AstroString& AstroSigns::operator << (int i) const
{
    if (i < 0 || i > 11)
        return *Asr->SignsError;
    return *Asr->SignsNames[i];
}

const AstroString& AstroSigns::operator < (int i) const
{
    if (i < 0 || i > 11)
        return *Asr->SignsError;
    return *Asr->SignsShortNames[i];
}

/** Returns the Element of the given sign */
enum Elements AstroSigns::GetElement(enum Signs s) const
{
    switch (s)
    {
    case Aries:
    case Leo:
    case Sagittarius:
        return Fire;
    case Taurus:
    case Virgo:
    case Capricorn:
        return Earth;
    case Gemini:
    case Libra:
    case Aquarius:
        return Air;
    case Cancer:
    case Scorpio:
    case Pisces:
        return Water;
    default:
        return Undefined_Element;
    }
    return Undefined_Element;
}

/** This method returns The ruled signs structure for the given object (planet, etc...) */
void AstroSigns::GetRuled(struct RuledSigns& r, enum Objs o, bool south) const
{
    r.Ruled =  Undefined_Sign;
    for (int i = Aries; i <= Pisces; i++)
        if (GetRulers((enum Signs)i, south).Ruler == o)
        {
            r.Ruled = (enum Signs)i;
            break;
        }
    r.Co_Ruled = Undefined_Sign;
    for (int i = Aries; i <= Pisces; i++)
        if (GetRulers((enum Signs)i, south).Co_Ruler == o)
        {
            r.Co_Ruled = (enum Signs)i;
            break;
        }
    r.Fall = Undefined_Sign;
    for (int i = Aries; i <= Pisces; i++)
        if (GetRulers((enum Signs)i, south).Fall == o)
        {
            r.Fall = (enum Signs)i;
            break;
        }
    r.Co_Fall = Undefined_Sign;
    for (int i = Aries; i <= Pisces; i++)
        if (GetRulers((enum Signs)i, south).Co_Fall == o)
        {
            r.Co_Fall = (enum Signs)i;
            break;
        }
    r.Exalt = Undefined_Sign;
    for (int i = Aries; i <= Pisces; i++)
        if (GetRulers((enum Signs)i, south).Exalt == o)
        {
            r.Exalt = (enum Signs)i;
            break;
        }
    r.Debil = Undefined_Sign;
    for (int i = Aries; i <= Pisces; i++)
        if (GetRulers((enum Signs)i, south).Debil == o)
        {
            r.Debil = (enum Signs)i;
            break;
        }
}

const AstroColor& AstroSigns::GetColor(enum Signs s) const
{
    enum Elements e = GetElement(s);
    switch (e)
    {
    case Fire  :
        return COL[Asr->FireColor ];
        break;
    case Air   :
        return COL[Asr->AirColor  ];
        break;
    case Water :
        return COL[Asr->WaterColor];
        break;
    case Earth :
        return COL[Asr->EarthColor];
        break;
    case Undefined_Element :
        return COL[Asr->OtherColor];
    }
    return COL[Asr->OtherColor];
}

enum Signs AstroSigns::GetSign(double angle) const
{
    int i = (int)angle / 30;
    if (i < 0 || i > 11) return Undefined_Sign;
    return (enum Signs)(Aries + i);
}

char AstroSigns::GetChar(enum Signs s, const ChartParams& cp) const
{
    if (s == Capricorn && cp.EuropCapr)
        return'<';
    return *(Sc + s);
}

const struct Ruling& AstroSigns::South(int i) const
    {
        i += 6;
        if (i > 11) i -= 10;
        return RulersTable[i];
    }

