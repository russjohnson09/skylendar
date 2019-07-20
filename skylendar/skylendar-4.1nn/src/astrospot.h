
/***************************************************************************
                          astrohousepos.h  -  description
                             -------------------
    begin                : Sat Feb 4 2017
    copyright            : (C) 2017 by Christophe Gros
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

#ifndef ASTROSPOT_H
#define  ASTROSPOT_H
#include "astrodefs.h"
#include "astrographics.h"
#include <QWidget>

class AstroObjs;
#include <QDebug>
class AstroSpot: public QWidget, public AstroGraphics
{
	Q_OBJECT

 public:

    AstroSpot(QWidget* parent, AstroGraphics* ag, const AstroObjs& a, enum Objs o, int x, int y, int size, const AstroColor& ac);
    AstroSpot(QWidget* parent, AstroGraphics* ag, enum Signs s, int x, int y, int size, const AstroColor& ac);

    ~AstroSpot() {}
    void RePos(int x, int y, int size);
 
 private:

	AstroObjs *A = nullptr;
	enum Objs O = Undefined_Obj;
	int X, Y, W, H;
	char C;
	enum AstroGraphics::SizeChars Sc;
	AstroColor* Col;

	void paintEvent(QPaintEvent *);

};
#endif
