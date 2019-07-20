/***************************************************************************
                          astrodate.cpp  -  description
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

#include "astrodate.h"
#include "astroutils.h"
#include "astroresources.h"
#include "astroprocess.h"
#include "tzlist.h"
#include <cstdlib>
#include <cstdio>
#define TM_YEAR_BASE 1900
#define L1901 2415731.514410
#define L2038 2465442.521991

inline void subst(char* dest, const char* src)
{
		for(int i = 0; i < BUFSIZE && src[i]; i++)
			dest[i] = (src[i] == '/') ? '\\' : src[i];
}

double AstroDate::MdyToJulian(bool greg)
{
    double j1, hour;
    J12 = Aif->Date_Conversion(Day, Month, Year, 12.00, greg);
    j1 = floor(J12 + ROUND);
    if (j1 >= MAX_DOUBLE)
    {
        j1 -= MAX_DOUBLE;
        Aif->RevJul(j1, greg, &Day, &Month, &Year, &hour);
    }
    return j1;
}

void AstroDate::JulianToMdy(double jd)
{
    bool greg = jd < J2g ? false : true;
    double hour;
    Aif->RevJul(jd, greg, &Day, &Month, &Year, &hour);
}

double AstroDate::GetJulday(bool greg)
{
    double x = Hm + DegToDec(-Offset) - DegToDec(Daylight);
    return MdyToJulian(greg) + x / 24.0 - 0.5;
}

double AstroDate::GetSidTime() const
{
    return Aif->SidTime(Julday);
}

void AstroDate::SetJd(double jd)
{
    double e = 0.0;
    Julday = jd;
    if (Automatic)
    {
        double o = Offset, d = Daylight;
        int offset;
        Offset = Daylight = 0.0;
        Ds = GuessDateSystem(Julday, offset);
        switch (Ds)
        {
        case Julian:
        case Localhour:
            Offset = ComputeLocalTime(Julday, e);
            break;
        case D1901:
            if (offset != NOOFFS && Tzon)
                Offset = -Tzon->getOffset(offset);
            break;
        case Timezone:
        {
            int h, m, s;
            HMR(Get(), h, m, s);
            if (Tzon)
            {
                unsigned char d, mo;
                short y;
                bool greg = jd < J2g ? false : true;
                double hour;
                Aif->RevJul(jd, greg, &d, &mo, &y, &hour);
                Tzon->GuessTz(d, mo, y, h, m, &Offset, &Daylight);
            }
        }
        break;
        case D2038:
            Offset = o;
            Daylight = d;
            break;
        default:
            ;
        }
    }
    jd += 0.5 - (TrueSolarTime ? e : 0.0);
    double x = -DegToDec(Daylight) + DegToDec(-Offset), fra = jd - floor(jd), it = jd - fra;
    Hm = (fra * 24.0) - x;
    if (Hm	>=24.00)
    {
        Hm -= 24.00;
        it++;
    }
    if (Hm >= 23.999722)
    {
        Hm = 0.0;
        it++;
    }
    if (Hm < 0.0)
    {
        Hm += 24.00;
        it--;
    }
    JulianToMdy(it);
    if (Automatic) Julday = GetJulday(IsGreg()) + (TrueSolarTime ? e : 0.0);
}

void AstroDate::Now()
{
    struct tm tm, *tmptr;
    double lt, j, hm;
    time_t t;
    (void)time(&t);
    tmptr = gmtime(&t);
    tm = *tmptr;
    lt = DegToDec(RHM(tm.tm_hour, tm.tm_min, tm.tm_sec));
    Day      = tm.tm_mday;
    Month    = tm.tm_mon + 1;
    Year     = tm.tm_year + TM_YEAR_BASE;
    if (Tzon)
        Tzon->GuessTz(Day, Month, Year, tm.tm_hour, tm.tm_min, &Offset, &Daylight);
    else
        Offset = Daylight = 0.0;
    lt += DegToDec(Asr->ExtraTime) - DegToDec(-Offset) + DegToDec(Daylight);
    if ((j = Aif->Date_Conversion(Day, Month, Year, DecToDeg(lt), true)) >= MAX_DOUBLE)
    {
        Aif->RevJul(j - MAX_DOUBLE, true, &Day, &Month, &Year, &hm);
        lt = DegToDec(hm);
    }
    Hm     = lt;
    Julday = GetJulday(true);
}

AstroDate::AstroDate(AstroInterface* aif)
{
    Aif = aif;
    SetTZ(Asr->DefZFile, false);
    Daylight = Offset = 0.0;
}

void AstroDate::SetTZ(const char* c, bool set)
{
    if (set)
    {
        if (strcmp(ZoneInfoFile, c) == 0) return;
        if (Tzon)
        {
            Atl->Remove(Tzon);
            Tzon = 0;
        }
    }
#ifdef __WINNT
		subst(ZoneInfoFile, c);
#else
    strncpy(ZoneInfoFile, c, BUFSIZE);
#endif
    if (!(Tzon = CSC(Tz*, Atl->Search(c))))
    {
        AstroString as;
        AstroMessage(Sprintf(i18n("Zoneinfo file %s can't be found"), &as, c));
        Offset = Daylight = 0.0;
    }
}

AstroDate::AstroDate(int day, int month, int year, int hour, int minute, int second, AstroInterface* aif)
{
    Aif = aif;
    SetTZ(Asr->DefZFile, false);
    SetDate(day, month, year, hour, minute, second);
}

AstroDate::AstroDate(int day, int month, int year, int hour, int minute, int second, const char* zonefile, double zoneoffset, double dl, AstroInterface* aif)
{
    Aif = aif;
    Day    = day;
    Month  = month;
    Year   = year;
    Set(hour, minute, second);
    Aif->SetTZ(zonefile ? zonefile : Asr->DefZFile);
    if (zonefile && Tzon)
        AstroDate::Recompute();
    else
    {
        int offset;
        Offset = zoneoffset;
        Daylight = dl;
        Julday = GetJulday(IsGreg());
        Ds = GuessDateSystem(Julday, offset);
    }
}

/** Sets the current date with the given parameters */
bool AstroDate::SetDate(int day, int month, int year, int hour, int minute, int second)
{
    Day    = day;
    Month  = month;
    Year   = year;
    Set(hour, minute, second);
    return AstroDate::Recompute();
}

/** Recompute the julian day form the Day, Mont, etc... class members */
bool AstroDate::Recompute()
{
    double e = 0.0;
    bool greg = IsGreg();
    if (Automatic)
    {
        double j = Aif->Date_Conversion(Day, Month, Year, Get(), greg), o = Offset, d = Daylight;
        int offset;
        Offset = Daylight = 0.0;
        switch ((Ds = GuessDateSystem(j, offset)))
        {
        case Julian:
        case Localhour:
            Offset = ComputeLocalTime(j, e);
            break;
        case D1901:
            if (offset != NOOFFS && Tzon)
                Offset = -Tzon->getOffset(offset);
            break;
        case Timezone:
        {
            int h, m, s;
            HMR(Get(), h, m, s);
            if (Tzon)
                Tzon->GuessTz(Day, Month, Year, h, m, &Offset, &Daylight);
        }
        break;
        case D2038:
            Offset = o;
            Daylight = d;
            break;
        default:
            ;
        }
    }
    Julday = GetJulday(greg) + (TrueSolarTime ? e : 0.0);
    return true;
}

const AstroString& AstroDate::DayName() const
{
    return *Asr->DayNames[Aif->Day_of_Week(J12)];
}

const AstroString& AstroDate::DayShortName() const
{
    return *Asr->DayShortNames[Aif->Day_of_Week(J12)];
}

const AstroString& AstroDate::GetDate(AstroString& as, bool short_format) const
{
    return DateFmt(short_format ? Asr->DateShortFormat : Asr->DateFormat, as);
}

const AstroString& AstroDate::GetTime(AstroString& as, int accuracy, bool tosecond) const
{
    DateFmt(tosecond ? Asr->STimeFormat : Asr->TimeFormat, as);
    if (accuracy > 0)
    {
			  as += u8"\u00B1"; //"\x00B1" =  "±";
        as += accuracy;
    }
    return as;
}

const AstroString& AstroDate::GetDateTime(AstroString& as, int accuracy, bool tosecond) const
{
    DateFmt(tosecond ? Asr->SDateTimeFormat : Asr->DateTimeFormat, as);
    if (accuracy > 0)
    {
        as += "";
        as += accuracy;
    }
    return as;
}

void AstroDate::SetJ2g(int day, int month, int year)
{
    J2gDay = day;
    J2gMonth = month;
    J2gYear = year;
    J2g = Aif->Date_Conversion(J2gDay, J2gMonth, J2gYear, 0.0, true);
}

enum DateSystem AstroDate::GuessDateSystem(double julday, int& offset) const
{
    offset = NOOFFS;
    if (julday >= MAX_DOUBLE) return Invalid_date;
    if (julday < J2g) return Julian;
    if (julday < Corr1901[0].julday) return Localhour;
    if (julday >= L2038) return D2038;
    if (julday >= L1901) return Timezone;
    for (int i = 0; i < 3 && Corr1901[i].julday != MINCORR; i++)
    {
        double cj = Corr1901[i].julday;
        if (julday >= cj) offset = Corr1901[i].seconds;
    }
    return D1901;
}

const AstroString& AstroDate::DateFmt(const AstroString& fmt, AstroString& as) const
{
    AstroString as1;
    int h, m, s;
    as = "";
    HMR(Get(), h, m, s);
    for (int i = 0; i < fmt.Len(); i++)
    {
        QChar q = fmt.at(i);
        if (q != '%')
            as.append(q);
        else
        {
            q = fmt.at(++i);
            switch (q.toLatin1())
            {
            case 'a' :
                as += DayShortName();
                break;
						case 'd' :
            case 'e' :
                as += Sprintf("%d", &as1, Day);
                break;
            case 'b' :
                as += *Asr->MonthShortNames[Month - 1];
                break;
            case 'm' :
                as += Sprintf("%d", &as1, Month);
                break;
						case 'y' :
            case 'Y' :
                as += Sprintf("%d", &as1, Year);
                break;
            case 'k' :
                as += Sprintf("%d", &as1, h);
                break;
            case 'M' :
                if (m < 10) as += '0';
                as += Sprintf("%d", &as1, m);
                break;
            case 'S' :
                if (s < 10) as += '0';
                as += Sprintf("%d", &as1, s);
                break;
            case 'I' :
                as += Sprintf("%d", &as1, h > 11 ? h -12 : h);
                break;
            case 'p' :
                as += h > 11 ? "PM" : "AM";
                break;
            case 'P' :
                as += h > 11 ? "pm" : "am";
                break;
            default:
                ;
            }
        }
    }
    return as;
}

const AstroString& AstroDate::SQLDate(AstroString& as, bool time) const
{
    if (time)
    {
        int h, m, s;
        HMR(Get(), h, m, s);
        return Sprintf("%d-%d-%d %d:%d:%d%s", &as, abs(Year), Month, Day, h, m, s, (Year < 0) ? " BC" : "");
    }
    return Sprintf("%d-%d-%d%s", &as, abs(Year), Month, Day, (Year < 0) ? " BC" : "");
}
