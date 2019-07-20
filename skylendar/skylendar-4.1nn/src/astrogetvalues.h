/***************************************************************************
 *   Copyright (C) 2004 by Christophe Gros                                 *
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

#ifndef ASTROGETVALUES_H
#define ASTROGETVALUES_H

#include "../config.h"
#include "astrodefs.h"
#include "astrotransfer.h"
#include "astrosql.h"

#ifdef QT
#include <QtDBus/QtDBus>
#include <qobject.h>
#include <qstring.h>
#endif

class AspectFound;
class AstroChart;

/** DCOP interface for data retrieving */
class AstroGetValues: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.skylendar.vals")

public:

    /** Constructor */
    AstroGetValues();

    /** Destructor */
    ~AstroGetValues();

public Q_SLOTS:

    /** returns number of charts */
    int NbCharts();

    /** Returns name of locked chart */
    QString GetChartName();

    /** Locks chart i. first chart = 0 */
    bool LockChart(int i);

    /* Unlocks current chart */
    void UnlockChart();

    /** returns number of active rings in current chart */
    int NbRings();

    /** Return ring type if ring i exists */
    QString GetRingType(int i);

    /** returns true if ring exists and obj non-restricted
       @param ring ring id (0..3)
       @param obj obj short name
    */
    bool IfObj(int ring, QString obj);

    /** returns nth values for obj in ring
       @param ring ring id (0..3)
       @param obj obj short name
       @param n nth obj values (0..5)
       */
    double GetVal(int ring, QString obj, int n);

    /** Returns longitude of obj in ring
       @param obj obj short name
       @param ring ring id. between 0..3
       */
    double GetLong(int ring, QString obj);

    /** gets the number of aspects */
    int NbAspects();

    /** returns ith aspects as a string. if string empty, non aspects or aspect out of bounds
       @param i ith aspect of the list. First = 0
       @return string as "obj1 asp obj2 diffangle accuracy aspect_direction"
       */
    QString GetAspect(int i);

    /** returns the number of aspects involving midpoints */
    int NbMPAspects();

    /** returns ith aspects as a string. if string empty, non aspects or aspect out of bounds
       @param i ith aspect of the list. First = 0
       @return string as "obj1/obj2 asp obj3 diffangle accuracy aspect_direction"
       */
    QString GetMPAspect(int i);

    /** */
    int SearchAspect(QString obj1, QString asp, QString obj2, int start, QString obj3);

    /** returns the longitudinal value of the midpoint between obj1 and obj2
       @return midp in decimal value
       */
    double GetMidPoint(QString obj1, QString obj2);

    /** returns the ephemeris values for the given day, month, year
    @return string
    */
    QString GetEphemLine(int day, int month, int year);

    /** Returns the ith arabic part of ring ring*/
    double GetPart(int i, int ring);

    /** Returns Ruler of obj's decan in ring */
    QString GetDecan(QString obj, int ring);

    /** Returns Ruler of obj's term in ring */
    QString GetTerm(QString obj, int ring);

    bool TFReq(QString s);
    bool TFNext();
    int TFGetAsp(int i);

private:

    QString GetAspectFound(const AspectFound&);
    AstroChart* Ac;
    AstroRequest Arq;
};

#endif
