/***************************************************************************
                          astrointerface.h  -  description
                             -------------------
    begin                : Fri May 18 2001
    copyright            : (C) 2001 by Christophe Gros
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

#ifndef ASTROINTERFACE_H
#define ASTROINTERFACE_H

#include "astroresources.h"
#include "astrotransfer.h"

#include "astrodefs.h"
#include "astrostring.h"
#include "astroprocessinterface.h"

class AstroRestrictions;
class ParamListBase;

#ifdef QT
#include <QEvent>
class AstroEvent: public QEvent
{
public:
    AstroEvent(unsigned short code, ParamListBase* plb) : QEvent(SC(QEvent::Type, code)) {
        Plb = plb;
    }
    ParamListBase* Plb;
};
#endif

/** This class provides an interface to the astro calculation process */
class AstroInterface: public OrgSkylendarSkyserviceInterface
{

public:

    /** Constructor
        @param app the server name
        @param id the served class id
    */
    AstroInterface(AstroString app, AstroString id);

    /** Destructor */
    ~AstroInterface();

    /** Returns the day, month, year, hour from the given julian day */
    void RevJul(double jd, bool greg, unsigned char* day, unsigned char* month, short* year, double* hm);

    /** Compute the horizontal (azimut and altitude) of the objects */
    void Azalt(double jd, const Double3& geopos, const Double3& xin, Double3& xout);

		/** Same as above, but for polygons */
		void Azalt(double jd, const Double3& geopos,  const ConstData* pin, ConstData* pout);
    /** Computes helical events
    @param julday, the date of the start of the search
    @param geopos longitude, latitude, altitude
    @param if the planet's id (enum Objs)
    @param he HelRising, HelSetting, etc...
    @param xout start visibility, optimum visibility, end os visibility
    */
    void Heliacal(double julday, const Double3& geopos, enum Objs o, enum AspKind ak, Double3& xout);

    /** Converts the given longitude and latitude into rectascension and declination
    @param ecl the value of the ecliptic
    @return and D3 with ra as d1 and decl as d2
     */
    void Convert(double* angle, double* dec, double ecl);

    /** Sets timezone file */
    void SetTZ(const char* file = 0, bool set = true);

    /** Sets the restriction group */
    void SetRestrict(const AstroRestrictions* ar, int restr = 0);

    /** Returns the error text line if any */
    void GetError(AstroString&);

    /** Returns the name of the ith object */
    const AstroString& GetPlaName(int i, AstroString&);

    /** Returns zoneinfo buffer (internal use only */
    inline const char *GetZib() const {
        return ZoneInfoBuf;
    }

    void GetApsides(double julday, int index, int flags, Apsides& apsides);

    void OaPole(int slot, double lon, double lat, double ecl, double* pole, double* oa, bool* eastern);

private:

    char ZoneInfoBuf[BUFSIZE];
    DateTime Dat;
    Double3 D3;
};

/** Dynamically creates an interface */
AstroInterface* CreateInterface();

#endif


