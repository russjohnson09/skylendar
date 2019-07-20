/***************************************************************************
                          astroconstellations.h  -  description
                             -------------------
    begin                : sat april 18 2015
    copyright            : (C) 2015 by Christophe Gros
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

#ifndef ASTROCONSTELLATIONS_H
#define ASTROCONSTELLATIONS_H

#define NBC 89

#include "astrostring.h"
#include "astrotransfer.h"

class AstroObjs;

class AstroConstellations
{
 public:

	AstroConstellations(AstroObjs* ao);
	inline ~AstroConstellations() { for(int i = 0; i < NBC; i++) { delete Src[i]; delete Des[i]; }}
  void Compute();
	AstroString Names[NBC];
  ConstData *Src[NBC], *Des[NBC];

 private:

	AstroObjs* Ao;
	
};

#endif
