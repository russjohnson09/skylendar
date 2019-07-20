/***************************************************************************
                          Astrohm.h  -  description
                             -------------------
    begin                : Fri Sep 15 2000
    copyright            : (C) 2000 by Christophe Gros
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

#ifndef ASTROHM_H
#define ASTROHM_H

#define ASTROHM_WRONG_HOUR      1
#define ASTROHM_WRONG_MINUTE    2
#define ASTROHM_WRONG_SECOND    3
#define ASTROHM_WRONG_SEPARATOR 4

#include "astroutils.h"
#include "astrostring.h"

enum HM_Mode { HM_Time, HM_Latitude, HM_Longitude, HM_HMS, HM_Degrees, HM_Sign };
/**
  The hour...minute delimiters
*/
#define DELIM ":"

/**This class implements an hour/minute value management with separate
* hour/minute and string input/output
*@author Christophe Gros
*/

class AstroHM {
public:

    inline AstroHM(double val = 0.0) {
        Hm = DegToDec(val);
    }
    /**
    *  Initialises hm with:
    *  @param hour the hour
    *  @param minute the minute
    */
    inline AstroHM(int hour, int minute, int second = 0, HM_Mode m = HM_Time) {
        (void)Set(hour, minute, second, m);
    }
    /**
    *  Initialises hm with an interpreted string (e.g. "12:42")
    *  hm is converted in decimal.
    *  @param an AstroString string value
    *  @param sep the string containing the diffreent separator between the hour and the minute
    *  @hms if true, accepts Hour/minute/second instead of degree/minute
    */
    inline AstroHM(AstroString as, HM_Mode m = HM_Time) {
        (void)Set(as, m);
    }

    /** Destructor */
    virtual inline ~AstroHM() {}
    /**
    * Sets Hm (converted in decimal) with checked hour/minute
    * @return 0 = OK, ASTROHM_WRONG_HOUR, ASTROHM_WRONG_MINUTE
    */
    int Set(int hour, int minute, int second = 0, HM_Mode m = HM_Time);
    /**
    *  Sets the an interpreted string(e.g. "12:42"), and converted in decimal
    *  @param an AstroString string value
    *  @param sep the string containing the different separator between the hour and the minute
    *  @param hms accepts Hour/minute/second instead of degree/minute (e.g. 3E)
    */
    int Set(AstroString as, HM_Mode m = HM_Time);

    /** Sets the value of Hm,
    @param d, value in degrees
    */
    AstroHM& operator = (double d);

    /** Sets the raw value of Hm */
    inline void Set(double d, bool decimal = true) {
        Hm = decimal ? d : DegToDec(d);
    }

    inline AstroHM& operator = (AstroString as) {
        Set(as);
        return *this;
    }

    /** Returns the Hm value in decimal
    	@param decimal if true deg:min, otherwise xx.yy
    */
    inline double Get(bool decimal = false) const {
        return decimal ? Hm : DecToDeg(Hm);
    }

    /** This method returns an AstroString string containing the AstroString
    formatted string value in hour/degree:minute
     	@param HM_Mode tells if time latitude or longitude format
     	@param locale if true and HM_Mode == HM_Time gets a locale formatted string
    	@param seconds if true, seconds are also displayed
    */
    virtual const AstroString& Get(AstroString&, HM_Mode m = HM_Time, bool locale = false, bool seconds = false) const;

    /** This method convert the hm value in hour
    minute, second
    @param h The pointer to the returned hour
    @param m The pointer to the returned minute
    @param s The pointer to the returned second
    */
    void HMConvert(int* h, int* m, int* s) const;

protected:

    double Hm;

private: // Private methods

    void Set(int h, int min, int s, bool neg, HM_Mode m);
};

#endif
