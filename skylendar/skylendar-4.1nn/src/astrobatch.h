/***************************************************************************
                          atrobatch.h  -  description
                             -------------------
    begin                : thr nov 24 2011
    copyright            : (C) 2011 by Christophe Gros
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

#ifndef ASTROBATCH_H
#define ASTROBATCH_H

#include "graphiclistbase.h"
#ifdef QT
#include <QHash>
#endif

class BatchData : public DataLineBase
{
public:

    Index first, second;
    enum Objs a, b;
    enum Aspects asp;
    double apos, bpos, orb, extraorb;
    enum AspectAccuracy side;
    enum AspectWay way;
};

class AstroBatch : public GraphicListBase, public DataLineList
{

	Q_DECLARE_TR_FUNCTIONS(AstroBatch)

public:

    AstroBatch(ChartBaseParams* cbp, ObjsVector* ov);

    ~AstroBatch() {}

    bool EditParams();

    bool Redisplay();

    bool PostRecompute();

    bool DumpAspects();

private:

    AstroString Condition;
    bool Table, Vdv;
    AstroFoundAspectsList Afal;
    Index TblIdx;
#ifdef QT
    QHash<Index, AstroString> NDict;
#endif
};
#endif
