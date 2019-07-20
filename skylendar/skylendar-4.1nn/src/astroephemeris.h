/***************************************************************************
                          astroephemeris.h  -  description
                             -------------------
    begin                : lun sep 22 2003
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

#ifndef ASTROEPHEMERIS_H
#define ASTROEPHEMERIS_H

#include <graphiclistbase.h>
#include "astrolist.h"

class StopScan;
class AstroData;
class DataLineBase;

class EphemLine : public DataLineBase
{

public:

    unsigned char day, month;
    unsigned int year;
    float val[12];
};


/**This class manages an ephemeris table
  *@author Christophe Gros
  */

class AstroEphemeris : public GraphicListBase, public ParamListBase
{

	Q_DECLARE_TR_FUNCTIONS(AstroEphemeris)

public:

    friend class StopScan;

    AstroEphemeris(ChartBaseParams*, ObjsVector*);
    ~AstroEphemeris();

    /** Overloaded redisplay method */
    bool Redisplay();

    /** Overloaded method, actual ephemeris computation */
    bool PostRecompute();

    /** Returns the nbth line of the ephemeris table*/
    const EphemLine* GetEphemLine(int day, int month, int year);

    inline bool EditParams() {
        return EditScSp(Asp);
    }

private:

    void DisplayMonth(Iterator& it);

    StopScan* Ss;
    AspScanParams Asp;
};

#endif
