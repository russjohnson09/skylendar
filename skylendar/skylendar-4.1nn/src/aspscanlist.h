/***************************************************************************
                          aspscanlist.h  -  description
                             -------------------
    begin                : sam oct 5 2002
    copyright            : (C) 2002 by Christophe Gros
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

#ifndef ASPSCANLIST_H
#define ASPSCANLIST_H

#include "graphiclistbase.h"
#include "astroresources.h"
#include <astrolist.h>

/**This class manages aspects scan lists, i.e.
lists of exact aspects between fixed and moving objects,
arising during a given time span.
  *@author Christophe Gros
*/
class ChartBaseParams;
class ScanClient;
class ScanclientAdaptor;
class StopScan;
class AstroRestrictions;


/** This class manages the Simple and Dual scan chart */

class AspScan : public ParamListBase
{

    friend class StopScan;
    friend class ScanClient;

public:

    AspScan(AstroChartBase* acb);

    ~AspScan();

    bool Run(bool stopscan);

    bool DumpAspects();

protected:

    bool Dual;
    AspScanParams Asp;
    AstroDate Orig, Orif;
    DataComp Dc;
    AstroRestrictions * Keep, *CurAr;

private:

    AstroChartBase *Acb;

    /** Records an aspect into the AspDataList
    @param i the ith object
    @param ipos its position
    @param j the jth object
    @param jpos its position
    @param julday the exact aspect date + time
    	@param ap if true, j and jpos are an arabic part.
    */
    void DrawDate(int i, double ipos, int j, double jpos, int asp, double julday, bool ap = false);

    /** Records an aspect to midpoints into the AspDataList
    @param i the ith mp object
    @param j the jth mp object
    @param pos the mp position
    @param k the kth object
    @param kpos its position
    @param julday the exact aspect date + time
    */
    void DrawMPDate(int i, int j, double pos, int k, double kpos, int aspect, double date);

    /** Records a sense change i.e. direct->retro or retro->direct
    @param i the object indexbeep
    @param sign the sign
    @param julday the exact change date + time
    */
    void DrawChange(int i, double ipos, double julday);

    /** Records an object sign change .i.e. whenever an object passes a
    	sign cusp
    @param i the obejct index
    @param ipos its position
    @param julday the exact sign change date + time
    */
    void DrawSignTrans(int i, int sign, double julday);

    /** Executed by Amw->customEvent() or Ascl->End() when scan list finished */
    void Finish();
};

class AspScanList : public GraphicListBase, public AspScan
{

	Q_DECLARE_TR_FUNCTIONS(AspscanList)

public:

    /** Constructor */
    AspScanList(ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~AspScanList() {};

    inline bool EditParams() {
        return EditScSp(Asp, true);
    };

    /** Overloaded redisplay method */
    bool Redisplay();

    /** Overloaded method, actual aspects scan computation */
    bool PostRecompute();

    /** Executed by Amw->customEvent() or Ascl->End() when scan list finished */

    //void Progress(int i) API;
};

#endif
