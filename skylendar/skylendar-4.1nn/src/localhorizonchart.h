/***************************************************************************
                          localhorizonchart.h  -  description
                             -------------------
    begin                : lun jun 2 2003
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

#ifndef LOCALHORIZONCHART_H
#define LOCALHORIZONCHART_H

#include <astrographics.h>
#include "astrotable.h"

class AstroObjs;
class AstroConstellations;

/**This class manages the local horizon graphic chart
  *@author Christophe Gros
  */

class LocalHorizonChart : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(LocalHorizonChart)

public:
    LocalHorizonChart(ChartBaseParams*, ObjsVector*);
    ~LocalHorizonChart();

    bool Redisplay();

    struct Pos
    {
        short x, y, px, py;
        unsigned short o;
    };

private:

    void ReCoord(short& x, short& y) const;
    void Place(int i, int j);
    inline bool CheckDist(short x, short y, short x1, short y1, short dist) const
    {
        short dx = x1 - x, dy = y1 - y;
        short d = short(sqrtf(dx * dx + dy * dy));
        return d >= dist ? true : false;
    }
    inline void Angle(short& x, short& y, short r, float angle) const
    {
        angle = DEGRAD(Normalize(angle + 270.0));
        y -= short(r * sinf(angle));
        x += short(r * cosf(angle));
    }
		void DisplayCons();
    Pos Pos[Last_Star];
    int Size, SizeX, SizeY, SizeOOO, W, H, T, U;
    enum CompModes Cms;
		bool h;
#ifdef QT
		QRegion Mask;
#endif

};

#endif
