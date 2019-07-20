#include "tz.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include "astroresources.h"

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
}

#define MONSPERYEAR    12

#define DAYSPERNYEAR   365
#define DAYSPERLYEAR   366
#define TZDEFAULT      "localtime"
#ifdef __WINNT
#define OPEN_MODE O_BINARY | O_RDONLY
#else
#define OPEN_MODE   O_RDONLY
#endif
#define WRONG	(-1)
#define SECSPERMIN     60
#define MINSPERHOUR 60
#define HOURSPERDAY 24
#define SECSPERHOUR    (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY     ((LG) SECSPERHOUR * HOURSPERDAY)
#define TM_YEAR_BASE   1900
#define EPOCH_YEAR     1970
#define TM_THURSDAY    4
#define EPOCH_WDAY     TM_THURSDAY
#define DAYSPERWEEK    7

#define TYPE_INTEGRAL(type) (((type) 0.5) != 0.5)
#define TYPE_BIT(type)        (sizeof (type) * CHAR_BIT)
#define TYPE_SIGNED(type) (((type) -1) < 0)
#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

struct rule {
    int		r_type;		/* type of rule--see below */
    int		r_day;		/* day number of rule */
    int		r_week;		/* week number of rule */
    int		r_mon;		/* month number of rule */
    LG		r_time;		/* transition time of rule */
};

struct tzhead {
    char    tzh_magic[4];           /* TZ_MAGIC */
    char    tzh_reserved[16];       /* reserved for future use */
    char    tzh_ttisgmtcnt[4];      /* coded number of trans. time flags */
    char    tzh_ttisstdcnt[4];      /* coded number of trans. time flags */
    char    tzh_leapcnt[4];         /* coded number of leap seconds */
    char    tzh_timecnt[4];         /* coded number of transition times */
    char    tzh_typecnt[4];         /* coded number of local time types */
    char    tzh_charcnt[4];         /* coded number of abbr. chars */
};


const char	gmt[] = "GMT";

static const int	mon_lengths[2][MONSPERYEAR] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static const int	year_lengths[2] = {
    DAYSPERNYEAR, DAYSPERLYEAR
};

static LG detzcode(char* const	codep)
{
    LG	result;
    int	i;

    result = (codep[0] & 0x80) ? ~0L : 0L;
    for (i = 0; i < 4; ++i)
        result = (result << 8) | (codep[i] & 0xff);
    return result;
}

bool Tz::loadTz(const char* c)
{
    return tzload(c, lclptr) ? false : true;
}

int Tz::tzload(const char*	name, struct state* const	sp)
{
    char *	p;
    int		i;
    int		fid;

    if (name == NULL && (name = TZDEFAULT) == NULL)
        return -1;
    {
        int	doaccess;
        /*
        ** Section 4.9.1 of the C standard says that
        ** "FILENAME_MAX expands to an integral constant expression
        ** that is the size needed for an array of char large enough
        ** to hold the longest file name string that the implementation
        ** guarantees can be opened."
        */
        char		fullname[FILENAME_MAX + 1];

        if (name[0] == ':')
            ++name;
        doaccess = name[0] == '/';
        if (!doaccess) {
            if ((p = const_cast<char *>(Asr->DefZFile)) == NULL)
                return -1;
            if ((strlen(p) + strlen(name) + 1) >= sizeof fullname)
                return -1;
            (void) strcpy(lcl_TZname, name);
            (void) strcpy(fullname, lcl_TZpath);;
            (void) strcat(fullname, "/");
            (void) strcat(fullname, name);
            /*
            ** Set doaccess if '.' (as in "../") shows up in name.
            */
            if (strchr(name, '.') != NULL)
                doaccess = true;
            name = fullname;
        }
        if (doaccess && access(name, R_OK) != 0)
            return -1;
        if ((fid = open(name, OPEN_MODE)) == -1)
            return -1;
    }
    {
        struct tzhead *	tzhp;
        union {
            struct tzhead	tzhead;
            char		buf[sizeof *sp + sizeof *tzhp];
        } u;
        int		ttisstdcnt;
        int		ttisgmtcnt;

        i = read(fid, u.buf, sizeof(u.buf));
        if (close(fid) != 0)
            return -1;
        ttisstdcnt = (int) detzcode(u.tzhead.tzh_ttisstdcnt);
        ttisgmtcnt = (int) detzcode(u.tzhead.tzh_ttisgmtcnt);
        sp->leapcnt = (int) detzcode(u.tzhead.tzh_leapcnt);
        sp->timecnt = (int) detzcode(u.tzhead.tzh_timecnt);
        sp->typecnt = (int) detzcode(u.tzhead.tzh_typecnt);
        sp->charcnt = (int) detzcode(u.tzhead.tzh_charcnt);
        p = u.tzhead.tzh_charcnt + sizeof u.tzhead.tzh_charcnt;
        if (sp->leapcnt < 0 || sp->leapcnt > TZ_MAX_LEAPS ||
                sp->typecnt <= 0 || sp->typecnt > TZ_MAX_TYPES ||
                sp->timecnt < 0 || sp->timecnt > TZ_MAX_TIMES ||
                sp->charcnt < 0 || sp->charcnt > TZ_MAX_CHARS ||
                (ttisstdcnt != sp->typecnt && ttisstdcnt != 0) ||
                (ttisgmtcnt != sp->typecnt && ttisgmtcnt != 0))
            return -1;
        if (i - (p - u.buf) < sp->timecnt * 4 +	/* ats */
                sp->timecnt +			/* types */
                sp->typecnt * (4 + 2) +		/* ttinfos */
                sp->charcnt +			/* chars */
                sp->leapcnt * (4 + 4) +		/* lsinfos */
                ttisstdcnt +			/* ttisstds */
                ttisgmtcnt)			/* ttisgmts */
            return -1;
        for (i = 0; i < sp->timecnt; ++i) {
            sp->ats[i] = detzcode(p);
            p += 4;
        }
        for (i = 0; i < sp->timecnt; ++i) {
            sp->types[i] = (unsigned char) *p++;
            if (sp->types[i] >= sp->typecnt)
                return -1;
        }
        for (i = 0; i < sp->typecnt; ++i) {
            register struct ttinfo *	ttisp;

            ttisp = &sp->ttis[i];
            ttisp->tt_gmtoff = detzcode(p);
            p += 4;
            ttisp->tt_isdst = (unsigned char) *p++;
            if (ttisp->tt_isdst != 0 && ttisp->tt_isdst != 1)
                return -1;
            ttisp->tt_abbrind = (unsigned char) *p++;
            if (ttisp->tt_abbrind < 0 ||
                    ttisp->tt_abbrind > sp->charcnt)
                return -1;
        }
        for (i = 0; i < sp->charcnt; ++i)
            sp->chars[i] = *p++;
        sp->chars[i] = '\0';	/* ensure '\0' at end */
        for (i = 0; i < sp->leapcnt; ++i) {
            struct lsinfo *	lsisp;

            lsisp = &sp->lsis[i];
            lsisp->ls_trans = detzcode(p);
            p += 4;
            lsisp->ls_corr = detzcode(p);
            p += 4;
        }
        for (i = 0; i < sp->typecnt; ++i) {
            struct ttinfo *	ttisp;

            ttisp = &sp->ttis[i];
            if (ttisstdcnt == 0)
                ttisp->tt_ttisstd = false;
            else {
                ttisp->tt_ttisstd = *p++;
                if (ttisp->tt_ttisstd != true &&
                        ttisp->tt_ttisstd != false)
                    return -1;
            }
        }
        for (i = 0; i < sp->typecnt; ++i) {
            struct ttinfo *	ttisp;

            ttisp = &sp->ttis[i];
            if (ttisgmtcnt == 0)
                ttisp->tt_ttisgmt = false;
            else {
                ttisp->tt_ttisgmt = *p++;
                if (ttisp->tt_ttisgmt != true &&
                        ttisp->tt_ttisgmt != false)
                    return -1;
            }
        }
        /*
        ** Out-of-sort ats should mean we're running on a
        ** signed time_t system but using a data file with
        ** unsigned values (or vice versa).
        */
        for (i = 0; i < sp->timecnt - 2; ++i)
            if (sp->ats[i] > sp->ats[i + 1]) {
                ++i;
                if (TYPE_SIGNED(time_t)) {
                    /*
                    ** Ignore the end (easy).
                    */
                    sp->timecnt = i;
                } else {
                    /*
                    ** Ignore the beginning (harder).
                    */
                    int	j;

                    for (j = 0; j + i < sp->timecnt; ++j) {
                        sp->ats[j] = sp->ats[j + i];
                        sp->types[j] = sp->types[j + i];
                    }
                    sp->timecnt = j;
                }
                break;
            }
    }
    return 0;
}

Tz::Tz(const char* path)
{
    count = 0;
    strncpy(lcl_TZpath, path, TZ_STRLEN_MAX + 1);
}

Tz::~Tz()
{
}

time_t Tz::mkTime(struct tm* const tmp) const
{
    return time1(tmp, true, 0L);
}

time_t Tz::time1(struct tm* const	tmp, bool local, LG offset) const
{
    time_t			t;
    struct state *	sp;
    int			samei, otheri;
    int			sameind, otherind;
    int			i;
    int			nseen;
    int				seen[TZ_MAX_TYPES];
    int				types[TZ_MAX_TYPES];
    int				okay;

    if (tmp->tm_isdst > 1)
        tmp->tm_isdst = 1;
    t = time2(tmp, local, offset, &okay);
#ifdef PCTS
    /*
    ** PCTS code courtesy Grant Sullivan (grant@osf.org).
    */
    if (okay)
        return t;
    if (tmp->tm_isdst < 0)
        tmp->tm_isdst = 0;	/* reset to std and try again */
#endif /* defined PCTS */
#ifndef PCTS
    if (okay || tmp->tm_isdst < 0)
        return t;
#endif /* !defined PCTS */
    /*
    ** We're supposed to assume that somebody took a time of one type
    ** and did some math on it that yielded a "struct tm" that's bad.
    ** We try to divine the type they started from and adjust to the
    ** type they need.
    */
    /*
    ** The (void *) casts are the benefit of SunOS 3.3 on Sun 2's.
    */
    sp = const_cast<struct state*>(local ? lclptr : gmtptr);
    /*sp = (const struct state *) (((void *) funcp == (void *) localsub) ?
    	lclptr : gmtptr);*/
#ifdef ALL_STATE
    if (sp == NULL)
        return WRONG;
#endif /* defined ALL_STATE */
    for (i = 0; i < sp->typecnt; ++i)
        seen[i] = false;
    nseen = 0;
    for (i = sp->timecnt - 1; i >= 0; --i)
        if (!seen[sp->types[i]]) {
            seen[sp->types[i]] = true;
            types[nseen++] = sp->types[i];
        }
    for (sameind = 0; sameind < nseen; ++sameind) {
        samei = types[sameind];
        if (sp->ttis[samei].tt_isdst != tmp->tm_isdst)
            continue;
        for (otherind = 0; otherind < nseen; ++otherind) {
            otheri = types[otherind];
            if (sp->ttis[otheri].tt_isdst == tmp->tm_isdst)
                continue;
            tmp->tm_sec += sp->ttis[otheri].tt_gmtoff -
                           sp->ttis[samei].tt_gmtoff;
            tmp->tm_isdst = !tmp->tm_isdst;
            t = time2(tmp, local, offset, &okay);
            if (okay)
                return t;
            tmp->tm_sec -= sp->ttis[otheri].tt_gmtoff -
                           sp->ttis[samei].tt_gmtoff;
            tmp->tm_isdst = !tmp->tm_isdst;
        }
    }
    return WRONG;
}

time_t Tz::time2(struct tm* const tmp, bool local, LG offset, int* okayp) const
{
    time_t	t;

    /*
    ** First try without normalization of seconds
    ** (in case tm_sec contains a value associated with a leap second).
    ** If that fails, try with normalization of seconds.
    */
    t = time2sub(tmp, local, offset, okayp, false);
    return *okayp ? t : time2sub(tmp, local, offset, okayp, true);
}

time_t Tz::time2sub(struct tm* tmp, bool local, LG offset, int* okayp, int do_norm_secs) const
{
    struct state *	sp;
    int			dir;
    int			i, j;
    int			saved_seconds;
    LG			li;
    time_t			lo;
    time_t			hi;
    LG				y;
    time_t				newt;
    time_t				t;
    struct tm			yourtm, mytm;

    *okayp = false;
    yourtm = *tmp;
    if (do_norm_secs) {
        if (normalize_overflow(&yourtm.tm_min, &yourtm.tm_sec,
                               SECSPERMIN))
            return WRONG;
    }
    if (normalize_overflow(&yourtm.tm_hour, &yourtm.tm_min, MINSPERHOUR))
        return WRONG;
    if (normalize_overflow(&yourtm.tm_mday, &yourtm.tm_hour, HOURSPERDAY))
        return WRONG;
    y = yourtm.tm_year;
    if (long_normalize_overflow(&y, &yourtm.tm_mon, MONSPERYEAR))
        return WRONG;
    /*
    ** Turn y into an actual year number for now.
    ** It is converted back to an offset from TM_YEAR_BASE later.
    */
    if (long_increment_overflow(&y, TM_YEAR_BASE))
        return WRONG;
    while (yourtm.tm_mday <= 0) {
        if (long_increment_overflow(&y, -1))
            return WRONG;
        li = y + (1 < yourtm.tm_mon);
        yourtm.tm_mday += year_lengths[isleap(li)];
    }
    while (yourtm.tm_mday > DAYSPERLYEAR) {
        li = y + (1 < yourtm.tm_mon);
        yourtm.tm_mday -= year_lengths[isleap(li)];
        if (long_increment_overflow(&y, 1))
            return WRONG;
    }
    for ( ; ; ) {
        i = mon_lengths[isleap(y)][yourtm.tm_mon];
        if (yourtm.tm_mday <= i)
            break;
        yourtm.tm_mday -= i;
        if (++yourtm.tm_mon >= MONSPERYEAR) {
            yourtm.tm_mon = 0;
            if (long_increment_overflow(&y, 1))
                return WRONG;
        }
    }
    if (long_increment_overflow(&y, -TM_YEAR_BASE))
        return WRONG;
    yourtm.tm_year = y;
    if (yourtm.tm_year != y)
        return WRONG;
    if (yourtm.tm_sec >= 0 && yourtm.tm_sec < SECSPERMIN)
        saved_seconds = 0;
    else if (y + TM_YEAR_BASE < EPOCH_YEAR) {
        /*
        ** We can't set tm_sec to 0, because that might push the
        ** time below the minimum representable time.
        ** Set tm_sec to 59 instead.
        ** This assumes that the minimum representable time is
        ** not in the same minute that a leap second was deleted from,
        ** which is a safer assumption than using 58 would be.
        */
        if (increment_overflow(&yourtm.tm_sec, 1 - SECSPERMIN))
            return WRONG;
        saved_seconds = yourtm.tm_sec;
        yourtm.tm_sec = SECSPERMIN - 1;
    } else {
        saved_seconds = yourtm.tm_sec;
        yourtm.tm_sec = 0;
    }
    /*
    ** Do a binary search (this works whatever time_t's type is).
    */
    if (!TYPE_SIGNED(time_t)) {
        lo = 0;
        hi = lo - 1;
    } else if (!TYPE_INTEGRAL(time_t)) {
        if (sizeof(time_t) > sizeof(float))
            hi = (time_t) DBL_MAX;
        else	hi = (time_t) FLT_MAX;
        lo = -hi;
    } else {
        lo = 1;
        for (i = 0; i < (int) TYPE_BIT(time_t) - 1; ++i)
            lo *= 2;
        hi = -(lo + 1);
    }
    for ( ; ; ) {
        t = lo / 2 + hi / 2;
        if (t < lo)
            t = lo;
        else if (t > hi)
            t = hi;
        if ((local ? localsub(&t, offset, &mytm) : gmtsub(&t, offset, &mytm)) == NULL) {
            //if ((*funcp)(&t, offset, &mytm) == NULL) {
            /*
            ** Assume that t is too extreme to be represented in
            ** a struct tm; arrange things so that it is less
            ** extreme on the next pass.
            */
            dir = (t > 0) ? 1 : -1;
        } else	dir = tmcomp(&mytm, &yourtm);
        if (dir != 0) {
            if (t == lo) {
                ++t;
                ++lo;
            } else if (t == hi) {
                --t;
                --hi;
            }
            if (lo > hi)
                return WRONG;
            if (dir > 0)
                hi = t;
            else	lo = t;
            continue;
        }
        if (yourtm.tm_isdst < 0 || mytm.tm_isdst == yourtm.tm_isdst)
            break;
        /*
        ** Right time, wrong type.
        ** Hunt for right time, right type.
        ** It's okay to guess wrong since the guess
        ** gets checked.
        */
        /*
        ** The (void *) casts are the benefit of SunOS 3.3 on Sun 2's.
        */
        sp = const_cast<struct state*>(local ? lclptr : gmtptr);
        /*sp = (const struct state *)
        (((void *) funcp == (void *) localsub) ?
        lclptr : gmtptr);*/
#ifdef ALL_STATE
        if (sp == NULL)
            return WRONG;
#endif /* defined ALL_STATE */
        for (i = sp->typecnt - 1; i >= 0; --i) {
            if (sp->ttis[i].tt_isdst != yourtm.tm_isdst)
                continue;
            for (j = sp->typecnt - 1; j >= 0; --j) {
                if (sp->ttis[j].tt_isdst == yourtm.tm_isdst)
                    continue;
                newt = t + sp->ttis[j].tt_gmtoff -
                       sp->ttis[i].tt_gmtoff;
                if ((local ? localsub(&newt, offset, &mytm) : gmtsub(&newt, offset, &mytm)) == NULL)
                    //if ((*funcp)(&newt, offset, &mytm) == NULL)
                    continue;
                if (tmcomp(&mytm, &yourtm) != 0)
                    continue;
                if (mytm.tm_isdst != yourtm.tm_isdst)
                    continue;
                /*
                ** We have a match.
                */
                t = newt;
                goto label;
            }
        }
        return WRONG;
    }
label:
    newt = t + saved_seconds;
    if ((newt < t) != (saved_seconds < 0))
        return WRONG;
    t = newt;
    if ((local ? localsub(&t, offset, tmp) : gmtsub(&t, offset, tmp)))
        //if ((*funcp)(&t, offset, tmp))
        *okayp = true;
    return t;
}

int	Tz::normalize_overflow(int * tensptr, int * unitsptr, int base) const
{
    int	tensdelta;

    tensdelta = (*unitsptr >= 0) ?
                (*unitsptr / base) :
                (-1 - (-1 - *unitsptr) / base);
    *unitsptr -= tensdelta * base;
    return increment_overflow(tensptr, tensdelta);
}

int Tz::long_normalize_overflow(LG * tensptr, int * unitsptr, int base) const
{
    int	tensdelta;

    tensdelta = (*unitsptr >= 0) ?
                (*unitsptr / base) :
                (-1 - (-1 - *unitsptr) / base);
    *unitsptr -= tensdelta * base;
    return long_increment_overflow(tensptr, tensdelta);
}

int	Tz::long_increment_overflow(LG * number, int delta) const
{
    LG	number0;

    number0 = *number;
    *number += delta;
    return (*number < number0) != (delta < 0);
}

int	Tz::increment_overflow(int * number, int delta) const
{
    int	number0;

    number0 = *number;
    *number += delta;
    return (*number < number0) != (delta < 0);
}

int	Tz::tmcomp(const struct tm * atmp, const struct tm * btmp) const
{
    int	result;

    if ((result = (atmp->tm_year - btmp->tm_year)) == 0 &&
            (result = (atmp->tm_mon - btmp->tm_mon)) == 0 &&
            (result = (atmp->tm_mday - btmp->tm_mday)) == 0 &&
            (result = (atmp->tm_hour - btmp->tm_hour)) == 0 &&
            (result = (atmp->tm_min - btmp->tm_min)) == 0)
        result = atmp->tm_sec - btmp->tm_sec;
    return result;
}

struct tm* Tz::gmtsub(const time_t * timep, LG offset, struct tm * tmp) const
    {
        return 0;
    }

struct tm* Tz::localsub(const time_t * timep, LG offset, struct tm * tmp) const
    {
        struct state *		sp;
        struct ttinfo *	ttisp;
        int			i;
        struct tm *		result;
        const time_t			t = *timep;

        sp = const_cast<struct state*>(lclptr);
#ifdef ALL_STATE
        if (sp == NULL)
            return gmtsub(timep, offset, tmp);
#endif /* defined ALL_STATE */
        if (sp->timecnt == 0 || t < sp->ats[0]) {
            i = 0;
            while (sp->ttis[i].tt_isdst)
                if (++i >= sp->typecnt) {
                    i = 0;
                    break;
                }
        } else {
            for (i = 1; i < sp->timecnt; ++i)
                if (t < sp->ats[i])
                    break;
            i = (int) sp->types[i - 1];
        }
        ttisp = &sp->ttis[i];
        /*
        ** To get (wrong) behavior that's compatible with System V Release 2.0
        ** you'd replace the statement below with
        **	t += ttisp->tt_gmtoff;
        **	timesub(&t, 0L, sp, tmp);
        */
        result = timesub(&t, ttisp->tt_gmtoff, sp, tmp);
        tmp->tm_isdst = ttisp->tt_isdst;
        tzname[tmp->tm_isdst] = &sp->chars[ttisp->tt_abbrind];
#ifdef TM_ZONE
        tmp->TM_ZONE = &sp->chars[ttisp->tt_abbrind];
#endif /* defined TM_ZONE */
        return result;
    }

struct tm* Tz::timesub(const time_t * timep, LG offset, const struct state * sp, struct tm * tmp) const
    {
        const struct lsinfo *	lp;
        time_t			tdays;
        int			idays;	/* unsigned would be so 2003 */
        LG			rem;
        int				y;
        const int *		ip;
        LG			corr;
        int			hit;
        int			i;

        corr = 0;
        hit = 0;
#ifdef ALL_STATE
        i = (sp == NULL) ? 0 : sp->leapcnt;
#endif /* defined ALL_STATE */
#ifndef ALL_STATE
        i = sp->leapcnt;
#endif /* State Farm */
        while (--i >= 0) {
            lp = &sp->lsis[i];
            if (*timep >= lp->ls_trans) {
                if (*timep == lp->ls_trans) {
                    hit = ((i == 0 && lp->ls_corr > 0) ||
                           lp->ls_corr > sp->lsis[i - 1].ls_corr);
                    if (hit)
                        while (i > 0 &&
                                sp->lsis[i].ls_trans ==
                                sp->lsis[i - 1].ls_trans + 1 &&
                                sp->lsis[i].ls_corr ==
                                sp->lsis[i - 1].ls_corr + 1) {
                            ++hit;
                            --i;
                        }
                }
                corr = lp->ls_corr;
                break;
            }
        }
        y = EPOCH_YEAR;
        tdays = *timep / SECSPERDAY;
        rem = *timep - tdays * SECSPERDAY;
        while (tdays < 0 || tdays >= year_lengths[isleap(y)]) {
            int		newy;
            time_t	tdelta;
            int	idelta;
            int	leapdays;

            tdelta = tdays / DAYSPERLYEAR;
            idelta = tdelta;
            if (tdelta - idelta >= 1 || idelta - tdelta >= 1)
                return NULL;
            if (idelta == 0)
                idelta = (tdays < 0) ? -1 : 1;
            newy = y;
            if (increment_overflow(&newy, idelta))
                return NULL;
            leapdays = leaps_thru_end_of(newy - 1) -
                       leaps_thru_end_of(y - 1);
            tdays -= ((time_t) newy - y) * DAYSPERNYEAR;
            tdays -= leapdays;
            y = newy;
        }
        {
            LG	seconds;

            seconds = (LG)(tdays * SECSPERDAY + 0.5);
            tdays = seconds / SECSPERDAY;
            rem += seconds - tdays * SECSPERDAY;
        }
        /*
        ** Given the range, we can now fearlessly cast...
        */
        idays = tdays;
        rem += offset - corr;
        while (rem < 0) {
            rem += SECSPERDAY;
            --idays;
        }
        while (rem >= SECSPERDAY) {
            rem -= SECSPERDAY;
            ++idays;
        }
        while (idays < 0) {
            if (increment_overflow(&y, -1))
                return NULL;
            idays += year_lengths[isleap(y)];
        }
        while (idays >= year_lengths[isleap(y)]) {
            idays -= year_lengths[isleap(y)];
            if (increment_overflow(&y, 1))
                return NULL;
        }
        tmp->tm_year = y;
        if (increment_overflow(&tmp->tm_year, -TM_YEAR_BASE))
            return NULL;
        tmp->tm_yday = idays;
        /*
        ** The "extra" mods below avoid overflow problems.
        */
        tmp->tm_wday = EPOCH_WDAY +
                       ((y - EPOCH_YEAR) % DAYSPERWEEK) *
                       (DAYSPERNYEAR % DAYSPERWEEK) +
                       leaps_thru_end_of(y - 1) -
                       leaps_thru_end_of(EPOCH_YEAR - 1) +
                       idays;
        tmp->tm_wday %= DAYSPERWEEK;
        if (tmp->tm_wday < 0)
            tmp->tm_wday += DAYSPERWEEK;
        tmp->tm_hour = (int) (rem / SECSPERHOUR);
        rem %= SECSPERHOUR;
        tmp->tm_min = (int) (rem / SECSPERMIN);
        /*
        ** A positive leap second requires a special
        ** representation.  This uses "... ??:59:60" et seq.
        */
        tmp->tm_sec = (int) (rem % SECSPERMIN) + hit;
        ip = mon_lengths[isleap(y)];
        for (tmp->tm_mon = 0; idays >= ip[tmp->tm_mon]; ++(tmp->tm_mon))
            idays -= ip[tmp->tm_mon];
        tmp->tm_mday = (int) (idays + 1);
        tmp->tm_isdst = 0;
#ifdef TM_GMTOFF
        tmp->TM_GMTOFF = offset;
#endif /* defined TM_GMTOFF */
        return tmp;
    }

int	Tz::leaps_thru_end_of(int y) const
{
    return (y >= 0) ?  (y / 4 - y / 100 + y / 400) :
           -(leaps_thru_end_of(-(y + 1)) + 1);
}

struct tm* Tz::localTime(const time_t * const	timep, struct tm* tm) const
    {
//printf("d = %d mo = %d y = %d h = %d m = %d\n", tm1.tm_mday, tm1.tm_mon, tm1.tm_year, tm1.tm_hour, tm1.tm_min);
        return Tz::localsub(timep, 0L, tm);
    }

double Tz::getOffset(int offs) const
{
    int zminute = offs / 60, zsecond = offs % 60, zheure = zminute / 60;
    zminute %= 60;
    return -double(zheure + zminute / 100.0 + zsecond / 10000.0);
// 	double zminute = floor(offs / 60.0), zheure = ceil(zminute / 60.0);
// 	zminute = floor(zminute - (zheure * 60.0));
// 	return -(zheure + zminute / 100.0);
}

void Tz::GuessTz(int day, int month, int year, int hour, int minute, double* offset, double* dst) const
{
    struct tm tm = {0, minute, hour, day, month - 1, year - 1900, 0, 0, 0, 0, 0 }, tm1;
    *dst = 0.0;
    time_t tt = mkTime(&tm);
    localTime(&tt, &tm1);
    *offset = -getOffset(tm1.tm_gmtoff);
    if (tm1.tm_isdst == 1)
    {
        struct tm tm2 = tm;
        tm2.tm_mon = 1;
        tt = mkTime(&tm2);
        localTime(&tt, &tm1);
        if (tm1.tm_isdst == 0)
        {
            double winter_off = -getOffset(tm1.tm_gmtoff);
            *dst = *offset - winter_off;
            *offset = winter_off;
        }
    }
}
