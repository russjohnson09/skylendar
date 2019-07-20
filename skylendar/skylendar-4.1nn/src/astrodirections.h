/***************************************************************************
 *   Copyright (C) 2007 by Christophe Gros                                 *
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
#ifndef ASTRODIRECTIONS_H
#define ASTRODIRECTIONS_H

#include <graphiclistbase.h>

/**
This class computes and displays primary directions occuring between first ring's date and second ring's date

	@author Christophe Gros <skylendar@yahoo.com>
*/

class ScanClient;
class ScanclientAdaptor;
class StopScan;

class AstroDir: public ParamListBase
{

    friend class StopScan;
    friend class ScanClient;

public:

    AstroDir(AstroChartBase* acb);

    ~AstroDir() {}

protected:

    enum House Hs;
    enum DirType Dt;
    enum StatKey Sk;
    double CustVal;
    bool Converse, Dump;
    bool DumpAspects();
    bool Run(bool stopscan);

private:

    void DrawDir(int i, double ipos, int j, double jpos, int asp, double julday, enum AspKind ak);
    void Finish();
    AstroChartBase *Acb;
};


class AstroDirections : public GraphicListBase, public AstroDir
{

	Q_DECLARE_TR_FUNCTIONS(AstroDirections)

	
    friend class EditDirections;
    friend class StopScan;
    friend class ScanClient;

public:

    AstroDirections(ChartBaseParams*, ObjsVector*);

    ~AstroDirections();

    bool Redisplay();

    bool PostRecompute();

    bool EditParams();

};

#endif
