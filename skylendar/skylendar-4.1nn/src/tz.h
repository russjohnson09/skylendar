/***************************************************************************
                          tz.h  -  description
                             -------------------
    begin                : TUE Feb 2 2005
    copyright            : (C) 2005 by Christophe Gros
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

/*
	This code id inspired from the tz package found in ftp://elsie.nci.nih.gov/pub
	Thanks to these Timezone Caballeros who've made major contributions to the
time conversion package:  Keith Bostic; Bob Devine; Paul Eggert; Robert Elz;
Guy Harris; Mark Horton; John Mackin; and Bradley White.  Thanks also to
Michael Bloom, Art Neilson, Stephen Prince, John Sovereign, and Frank Wales
for testing work, and to Gwillim Law for checking local mean time data.
None of them are responsible for remaining errors.
*/

#ifndef TZ_H
#define TZ_H

#include <float.h>
#define LG int

#if defined(__WINNT) && !defined(_TIME_H_)
#define _TM_DEFINED
#define _TIME_T_DEFINED
struct tm
{
    int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
    int tm_min;			/* Minutes.	[0-59] */
    int tm_hour;			/* Hours.	[0-23] */
    int tm_mday;			/* Day.		[1-31] */
    int tm_mon;			/* Month.	[0-11] */
    int tm_year;			/* Year	- 1900.  */
    int tm_wday;			/* Day of week.	[0-6] */
    int tm_yday;			/* Days in year.[0-365]	*/
    int tm_isdst;			/* DST.		[-1/0/1]*/
    LG tm_gmtoff;		/* Seconds east of UTC.  */
    const char *tm_zone;	/* Timezone abbreviation.  */
};
//typedef long int time_t;
#else
#include <ctime>
#endif

#define TM_GMTOFF tm_gmtoff

#ifndef true
#define false 0
#define true 1
#endif

#define BIGGEST(a, b)	(((a) > (b)) ? (a) : (b))
#define TZ_MAX_TIMES   370
#define TZ_MAX_TYPES    20
#define TZ_MAX_CHARS    50
#define TZ_MAX_LEAPS    50
#define MY_TZNAME_MAX	 255
#define TZ_STRLEN_MAX  255

#define lclptr		(&lclmem)
#define gmtptr		0

struct ttinfo {				/* time type information */
    LG		tt_gmtoff;	/* UTC offset in seconds */
    int		tt_isdst;	/* used to set tm_isdst */
    int		tt_abbrind;	/* abbreviation list index */
    int		tt_ttisstd;	/* true if transition is std time */
    int		tt_ttisgmt;	/* true if transition is UTC */
};

struct lsinfo {				/* leap second information */
    time_t		ls_trans;	/* transition time */
    LG		ls_corr;	/* correction to apply */
};

extern const char gmt[4];

struct state {
    int		leapcnt;
    int		timecnt;
    int		typecnt;
    int		charcnt;
    time_t		ats[TZ_MAX_TIMES];
    unsigned char	types[TZ_MAX_TIMES];
    struct ttinfo	ttis[TZ_MAX_TYPES];
    char		chars[BIGGEST(BIGGEST(TZ_MAX_CHARS + 1, sizeof gmt),
                        (2 * (MY_TZNAME_MAX + 1)))];
    struct lsinfo	lsis[TZ_MAX_LEAPS];
};

class Tz
{
public:

    Tz(const char *path);
    ~Tz();
    bool loadTz(const char *);
    struct tm* localTime(const time_t * const timep, struct tm*) const;
    time_t mkTime(struct tm * const	tmp) const;
    inline Tz* operator++() {
        count++;
        return this;
    }
    inline Tz* operator--() {
        count--;
        if (count < 0) count = 0;
        return this;
    }
    inline int getCount() const {
        return count;
    }
    inline const char* getName() const {
        return lcl_TZname;
    }
    void GuessTz(int day, int month, int year, int hour, int minute, double* offset, double* dst) const;
    double getOffset(int offs) const;

private:

    int tzload(const char* name, struct state* const	sp);
    time_t time1(struct tm* const	tmp, bool local, LG offset) const;
    time_t time2(struct tm* const tmp, bool local, LG offset, int* okayp) const;
    struct tm* timesub(const time_t * timep, LG offset, const struct state * sp, struct tm * tmp) const;
    time_t time2sub(struct tm* tmp, bool local, LG offset, int* okayp, int do_norm_secs) const;
    int	normalize_overflow(int * tensptr, int * unitsptr, int base) const;
    int	increment_overflow(int * number, int delta) const;
    int long_normalize_overflow(LG * tensptr, int * unitsptr, int base) const;
    int	long_increment_overflow(LG * number, int delta) const;
    int	tmcomp(const struct tm * atmp, const struct tm * btmp) const;
    struct tm* gmtsub(const time_t * timep, LG offset, struct tm * tmp) const;
    struct tm* localsub(const time_t * timep, LG offset, struct tm * tmp) const;
    int	leaps_thru_end_of(int y) const;

//struct state*	lclptr;
    //struct state*	gmtptr;
    struct state	lclmem;
    //struct state	gmtmem;
    char lcl_TZpath[TZ_STRLEN_MAX + 1];
    char lcl_TZname[TZ_STRLEN_MAX + 1];
    int	 lcl_is_set;
    int count;
    mutable char* tzname[2];
};
#endif
