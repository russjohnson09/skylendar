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

#ifndef SCANCLIENT_H
#define SCANCLIENT_H

#include "../config.h"
#include "astrodefs.h"
#include "astrotransfer.h"
#include <cmath>

#ifdef QT
#include <QtDBus/QtDBus>
#include <QObject>
#include <QString>
#endif

class AspScan;
class AstroDir;

/** This class manages a aspects scan receiver client */
class ScanClient: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.skylendar.scanclient")

public:

    friend class AspScan;

    /** Constructors */
    ScanClient(QObject* parent, AspScan* asc, int id);

    ScanClient(QObject* parent, AstroDir* ad, int id);

    /** Destructor */
    ~ScanClient();

    int Id;

public Q_SLOTS:

    /** Gets a found aspect
    	@param i the ith natal object
    	@param ipos ith object position. ipos < 0 = retro
    	@param j the jth moving object
    	@param jpos the object position, jpos < 0 = retro
    	@param aspect the given aspect
    	@param date the exact aspect date
    		@param ap if true j and jpos are for arabic part
    */
    Q_NOREPLY void GetAspect(int i, double ipos, int j, double jpos, int aspect, double date, bool ap = false);

    /** Gets a found aspect between midpoint/moveing object
    	@param i the ith mp object
    	@param j the jth mp object (for i/j midpoint)
    	@param pos mp position. ipos < 0 = retro
    	@param k the kth moving object
    	@param kpos the object position, kpos < 0 = retro
    	@param aspect the given aspect
    	@param date the exact aspect date
    */
    Q_NOREPLY void GetMPAspect(int i, int j, double pos, int k, double kpos, int aspect, double date);

    /** Gets an object's direction change date
       @param i the ith moving object
       @param ipos the ith object position, ipos < 0 = retro
       @param date the direction change exact date
    */
    Q_NOREPLY void GetRetro(int i, double ipos, double date);

    /** Gets a sign transited by a moving object
       @param i the ith moving object
       @param sign the passed sign
       @param date the sign transited
    */
    Q_NOREPLY void GetSignTrans(int i, int sign, double date);

    /** Same as GetAspect, but for primary directions */
    Q_NOREPLY void GetDirection(int i, double ipos, int j, double jpos, int aspect, double date, bool converse);

    /** Gets a progression percentage for the progression bar
       @param i the percentage
    */
    Q_NOREPLY void Progress(int i);

    /** Received when scan finished */
    Q_NOREPLY void EndScan();


private:

    AspScan* Asc;
    AstroDir* Ad;
};

#endif
