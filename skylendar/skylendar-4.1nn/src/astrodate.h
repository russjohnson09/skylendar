/***************************************************************************
                          astrodate.h  -  description
                             -------------------
    begin                : Sat Sep 16 2000
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

#ifndef ASTRODATE_H
#define ASTRODATE_H

#include "astrodefs.h"
#include "astrohm.h"
#include "astrointerface.h"
# include <ctime>
#define MINCORR -1000000000.0
#define NOOFFS 1000000000

/**
* The AstroDate is the standard kastrolog date and time management class.
* It provides a day, month, year <-> julian day conversion, a "right now"
* setting, a time increasing and decreasing
* @version $Id: 0.1
* @author Christophe Gros
*/

class Tz;

class AstroDate: public AstroHM
{

	Q_DECLARE_TR_FUNCTIONS(AstroDate)

public:

    /** Constructor */
    inline AstroDate() {
        Aif = Asf;
        //Automatic = false;
    }

    /** Destructor */
    inline virtual ~AstroDate() {}

    /** The default consructor. Sets the current time for now */
    AstroDate(AstroInterface *aif);

    /** Yields a new date with usual parameters */
    AstroDate(int day, int month, int year, int hour, int minute, int second, AstroInterface* aif = Asf);

    /**
    * Same as above, plus the zone info arguments
    * @param zonefile The zone info file (e.g. "Europe/Brussels")
    * @param zoneoffset The time zone offset
    * @param daylight If daylight is active
    * If zonefile is null, the zoneoffset and daylight are used instead
    */
    AstroDate(int day, int month, int year, int hour, int minute, int second, const char* zonefile, double zoneoffset = 0.0, double daylight = 0.0, AstroInterface* aif = Asf);

    /** Sets the current computing interface */
    inline void SetInterface(AstroInterface* aif) {
        Aif = aif;
    }

    /** Returns the current computing interface */
    inline AstroInterface* GetInterface() const {
        return Aif;
    }

    /** Sets the current date with the given parameters */
    bool SetDate(int day, int month, int year, int hour, int minute, int second);

    /** Sets the time for now */
    void Now();

    /** Returns the sidereal time at 0h GMT, in decimal*/
    double GetSidTime() const;

    /** Sets the timezone file name
        @param c the timezone filename
        @param set also sets the tzfile in the current computing interface
    */
    void SetTZ(const char* c, bool set = true);

    /** Returns the name of the current day */
    const AstroString& DayName() const;

    /** Returns the short name of the current day */
    const AstroString& DayShortName() const;

    /** Recomputes the julian day form the Day, Month, etc... class members */
    virtual bool Recompute();

    /** Gets the current date + time */
    virtual inline void GetDate(int *day, int *month, int *year, int *hour, int* minute, int *second = 0) const
    {
        int s;
        HMR(Get(), *hour, *minute, second ? *second : s);
        *day = Day;
        *month = Month;
        *year = Year;
    }

    /** Returns the current date according to the current locales
    @param as the date is also returned in as
    @param short_format if true returns dd/mm/yy or akin */
    virtual const AstroString& GetDate(AstroString& as, bool short_format = false) const;

    /** Returns the current time according to the current locales
    @param as the formatted time also returned in as
    @param accuracy if != 0, prepend with +/- accuracy
    @param tosecond also prints second */
    virtual const AstroString& GetTime(AstroString& as, int accuracy = 0, bool tosecond = false) const;

    /** Returns the current date and time according to the current locale
    @param as the formatted time also returned in as
    @param accuracy if != 0, prepend with +/- accuracy
    @param tosecond also prints second */
    const AstroString& GetDateTime(AstroString& as, int accuracy = 0, bool tosecond = false) const;

    /** Returns the current julian day */
    virtual inline double GetJd() const {
        return Julday;
    }

    /** Returns the current time
        @param decimal if the return is decimal or minute */
    virtual inline double GetTime(bool decimal = false) const {
        return Get(decimal);
    }

    /** Returns the current timezone offset in hour.minute */
    virtual inline double GetOffset() const {
        return Offset;
    }

    /** Returns the current daylight offset in hour.minute */
    virtual inline double GetDaylight() const {
        return Daylight;
    }

    /** Sets the timezone offset and daylight */
    virtual inline void SetOffDay(double offset, double daylight) {
        Offset = offset;
        Daylight = daylight;
        Automatic = false;
    }

    /** Sets the julian day and computes the corresponding day, month, year and hour */
    void SetJd(double jd);

    /** Sets the change of the Julian to Gregorian calendar */
    void SetJ2g(int day, int month, int year);

    /** Returns the julian day of the Julian->Gregorian calendar change */
    inline double GetJ2g() const {
        return J2g;
    }

    /** Retrns the current date system */
    inline enum DateSystem GetDs() const {
        return Ds;
    }

    /** if true, automatically computes with time offset in Offset */
    bool Automatic = false;

    /** if true, computes or display to the second */
    bool To_Second = false;

    /** If true solar time instead of mean solar time */
    bool TrueSolarTime;

    /** Returns SQL formatted date date input */
    const AstroString& SQLDate(AstroString& as, bool time = true) const;

protected:

    AstroInterface* Aif;
    Tz* Tzon;
    unsigned char Day, J2gDay, Month, J2gMonth;
    short Year, J2gYear;
    double Julday, Offset, Daylight, J2g = J2G, J12;
    /** the corresponding zone info file */
    char ZoneInfoFile[BUFSIZE];

    struct Corr1901
    {
        double julday;
        int seconds;
    };
    Corr1901 Corr1901[3];
    enum DateSystem Ds = Timezone;

    /** Tries to guess the given date system. If during D1901, sets offset */
    enum DateSystem GuessDateSystem(double julday, int& offset) const;

    /** virtuallized method for computing the local jours dates */
    virtual inline double ComputeLocalTime(double, double&) const {
        return 0.0;
    }

    /** Returns true if gregorian calendar, false if julian */
    inline bool IsGreg() const {
        return (Year < J2gYear || (Year == J2gYear &&
                                   (Month < J2gMonth || (Month == J2gMonth && Day < J2gDay)))) ? false : true;
    }


private:

    double MdyToJulian(bool greg), GetJulday(bool greg);
    void JulianToMdy(double jd);

    /** strftime seems buggy for years
    	this substition routine accepts a e b m Y k M I p P, as conversion flags
    @param fmt the conversion format string
    @param as an AstroString buffer
    @return as */
    const AstroString& DateFmt(const AstroString& fmt, AstroString& as) const;
};

#endif
