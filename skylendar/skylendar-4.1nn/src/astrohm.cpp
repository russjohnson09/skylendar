/***************************************************************************
                          astrohm.cpp  -  description
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

#include "astrodefs.h"
#include "astrohm.h"
#include <cstdlib>
#include <ctime>
#include "astroregexp.h"
#include <cstdio>
#include "astrosigns.h"

int AstroHM::Set(int hour, int minute, int second, HM_Mode m)
{
    if (m == HM_Time && (hour < 0 || hour > 23))
        return ASTROHM_WRONG_HOUR;
    if (m == HM_Latitude && (hour < -89 || hour > 89))
        return ASTROHM_WRONG_HOUR;
    if (m == HM_Longitude && (hour < -179 || hour > 179))
        return ASTROHM_WRONG_HOUR;
    if (minute < 0 || minute > 59)
        return ASTROHM_WRONG_MINUTE;
    if (second < 0 || second > 59)
        return ASTROHM_WRONG_SECOND;
    Hm = DegToDec(RHM(hour, minute, second));
    return 0;
}

void AstroHM::Set(int h, int min, int s, bool neg, HM_Mode m)
{
    if (m == HM_HMS)
    {
// The total number of second
        int z;
        double x;
        z = s + (60 * min) + (3600 * abs(h));
//  86400 = the number of seconds in a day
        x = (double)z * 360.0 / 86400.0;
        h = int(x);
        min = int(fmod(x, 1.0) * 10000.0);
        s = min % 100;
        min /= 100;
        Hm = h + min / 100.0 + s / 10000.0;
        return;
    }
    if (m == HM_Time && neg)
    {
        if (h < 11) h += 12;
        neg = false;
    }
    Hm = DegToDec(neg ? -RHM(h, min, s) : RHM(h, min, s));
}

enum Sep { None, Deg, Min, Sec, Col, Sep1, Sep2, Sgn, Other};

static enum Sep CheckSep(const AstroString& as, const AstroString& sep1, const AstroString& sep2, HM_Mode m, int *sign = 0)
{
    if (m == HM_Sign)
        for (int i = 0; i < 12; i++)
            if (Asr->SignsShortNames[i]->toLower() == as && sign)
            {
                *sign = i;
                return Sgn;
            }
    if (as == "") return None;
    else if (as == DEGCHAR)
    {
        if (m == HM_Time) return Other;
        return Deg;
    }
    else if (as == "'")
    {
        if (m == HM_Time) return Other;
        return Min;
    }
    else if (as == "\"")
    {
        if (m == HM_Time) return Other;
        return Sec;
    }
    else if (as == ":") return Col;
    else if (as == sep1) return Sep1;
    else if (as == sep2) return Sep2;
    else return Other;
}

int AstroHM::Set(AstroString as, HM_Mode m)
{
    int h, min = 0, s = 0, i1, i2, sign;
    AstroString sep1, sep2, pat;
    switch (m)
    {
    case HM_Time:
        i1 =    0;
        i2 =  23;
        sep1 = "am";
        sep2 = "pm";
        break;
    case HM_Latitude:
        i1 =  -89;
        i2 =  90;
        sep1 =  "n";
        sep2 =  "s";
        break;
    case HM_Longitude:
        i1 = -179;
        i2 = 180;
        sep1 =  "e";
        sep2 =  "w";
        break;
    case HM_HMS:
        i1 =  -11;
        i2 =  12;
        sep1 =  "e";
        sep2 =  "w";
        break;
    case HM_Degrees:
        i1 =    0;
        i2 = 359;
    case HM_Sign:
        i1 = 0;
        i2 = 29;
    };
    AstroRegExp are("-?(\\d+)(\\D+)?(\\d+)?(\\D+)?(\\d+)?(\\D+)?");
    as = as.Low().trimmed();
    if (are < as)
    {
        bool ok, neg = false, fneg = false, deg = false, col = false, sp1 = false, sp2 = false, sgn = false;
        if ((are / 0)[0] == "-") neg = fneg = true;
        h = (are / 1).Int(&ok);
        if (!ok || h < i1 || h > i2) return ASTROHM_WRONG_HOUR;
        switch (CheckSep(are / 2, sep1, sep2, m, &sign))
        {
        case None:
            Set(h, min, s, neg, m);
            return 0;
        case Deg:
            deg = true;
            break;
        case Col:
            col = true;
            break;
        case Sep1:
            if (fneg) return ASTROHM_WRONG_HOUR;
            sp1 = true;
            break;
        case Sep2:
            if (fneg) return ASTROHM_WRONG_HOUR;
            sp2 = neg = true;
            break;
        case Sgn:
            sgn = true;
            break;
        default:
            return ASTROHM_WRONG_HOUR;
        };
        if (fneg && sp2) return ASTROHM_WRONG_HOUR;
        if ((are / 3) == "")
        {
            if (m == HM_Sign)
                Hm = DegToDec(sign * 30.0 + RHM(h, min, s));
            else
                Set(h, min, s, neg, m);
            return 0;
        }
        min = (are / 3).Int(&ok);
        if (!ok || min < 0 || min > 59) return ASTROHM_WRONG_MINUTE;
        switch (CheckSep(are / 4, sep1, sep2, m))
        {
        case None:
            if (!sgn)
            {
                Set(h, min, s, neg, m);
                return 0;
            }
            break;
        case Min:
            if (!deg && !sgn) return ASTROHM_WRONG_MINUTE;
            break;
        case Col:
            break;
        case Sep1:
            if (sp1 || sp2 || deg) return ASTROHM_WRONG_MINUTE;
            sp1 = true;
            break;
        case Sep2:
            if (fneg || sp1 || sp2 || deg) return ASTROHM_WRONG_MINUTE;
            sp2 = neg = true;
            break;
        default:
            return ASTROHM_WRONG_MINUTE;
        };
        if ((are / 5) == "")
        {
            if (m == HM_Sign)
                Hm = DegToDec(sign * 30.0 + RHM(h, min, s));
            else
                Set(h, min, s, neg, m);
            return 0;
        }
        s = (are / 5).Int(&ok);
        if (!ok || s < 0 || s > 59) return ASTROHM_WRONG_SECOND;
        switch (CheckSep(are / 6, sep1, sep2, m))
        {
        case None:
            if (!sgn)
            {
                Set(h, min, s, neg, m);
                return 0;
            }
        case Sec:
            if (!deg && !sgn) return ASTROHM_WRONG_SECOND;
            break;
        case Sep1:
            if (sp1 || sp2 || deg) return ASTROHM_WRONG_SECOND;
            break;
        case Sep2:
            if (fneg || sp1 || sp2 || deg) return ASTROHM_WRONG_SECOND;
            neg = true;
            break;
        default:
            return ASTROHM_WRONG_SECOND;
        };
        if (m == HM_Sign)
            Hm = DegToDec(sign * 30.0 + RHM(h, min, s));
        else
            Set(h, min, s, neg, m);
        return 0;
    }
    return ASTROHM_WRONG_HOUR;
}

AstroHM& AstroHM::operator = (double d)
{
    Hm = DegToDec(d);
    return *this;
}
#define ARG(x) arg(x, 2, 10, QChar('0'))

const AstroString& AstroHM::Get(AstroString& result, HM_Mode m, bool locale, bool seconds) const
{
    int h, min, sec;
    char buf[12];
    result = (char)0;
    bool neg = Hm < 0.0;
    if (locale && m == HM_Time)
    {
#ifdef QT
        HMR(DecToDeg(Hm), h, min, sec);
        const struct tm tm = { seconds ? sec : 0, min, h, 0, 0, 0, 0, 0, 0,
#ifdef __WINNT
        };
#else
            0, 0
        };
#endif
        char buf1[BUFSIZE];
        Asr->TimeFormat.Data(buf1);
        strftime(buf, 12, buf1, &tm);
        result = buf;
        return result;
#endif
    }
    if (m != HM_HMS)
        Hmr(DecToDeg(Hm), h, min, sec, seconds ? false : true);
#ifdef QT
    switch (m)
    {
    case HM_Time     :
        result = seconds ? QString("%1:%2:%3").arg(h).ARG(min).ARG(sec) : QString("%1:%2").arg(h).ARG(min);
//         if (seconds) sprintf(buf, "%d:%.2d:%.2d", h, min, sec);
//         else sprintf(buf, "%d:%.2d", h, min);
        break;
    case HM_Latitude :
        result = seconds ? QString("%1%2%3:%4").arg(abs(h)).arg(neg ? 'S' : 'N').ARG(min).ARG(sec) : QString("%1%2%3").arg(abs(h)).arg(neg ? 'S' : 'N').ARG(min);
//         if (seconds) sprintf(buf, "%d%c%.2d:%.2d", abs(h), neg ? 'S' : 'N', min, sec);
//         else sprintf(buf, "%d%c%.2d", abs(h), neg ? 'S' : 'N', min);
        break;
    case HM_Longitude:
        result = seconds ? QString("%1%2%3:%4").arg(abs(h)).arg(neg ? 'W' : 'E').ARG(min).ARG(sec) : QString("%1%2%3").arg(abs(h)).arg(neg ? 'W' : 'E').ARG(min);
//         if (seconds) sprintf(buf, "%d%c%.2d:%.2d", abs(h), neg ? 'W' : 'E', min, sec);
//         else sprintf(buf, "%d%c%.2d", abs(h), neg ? 'W' : 'E', min);
        break;
    case HM_HMS:
        HMConvert(&h, &min, &sec);
        result = QString("%1%2%3:%4").arg(abs(h)). arg(neg ? 'W' : 'E'). ARG(min).ARG(sec);
//         sprintf(buf, "%d%c%.2d:%.2d", abs(h), neg ? 'W' : 'E', min, sec);
        break;
    case HM_Degrees:
			result = seconds ? QString("%1%2%3'%4\"").arg(abs(h)).arg(DEGCHAR).ARG(min).ARG(sec) : QString("%1%2%3'").arg(abs(h)).arg(DEGCHAR).ARG(min);
//         if (seconds) sprintf(buf, "%d\x00B0%.2d'%.2d\"", abs(h), min, sec);
//         else sprintf(buf, "%d\x00B0%.2d'", abs(h), min);
        break;
    case HM_Sign:
    {
        int h1, r1;
        h1 = h / 30;
        r1 = h % 30;
        result = seconds ? QString("%1%2%3'%4").arg(abs(r1)).arg((*Asg) < h1).ARG(min).ARG(sec) : QString("%1%2%3").arg(abs(r1)).arg((*Asg) < h1).ARG(min);
        if (h < 0) result += 'R';
        // 	if (seconds) sprintf(buf, "%d\x00B0%.2d'%.2d\"", abs(h), min, sec);
//         else sprintf(buf, "%d\x00B0%.2d'", abs(h), min);
    }
    }
#endif
//    result = buf;
    return result;
}

/** This method convert the hm value in hour
minute, second */
void AstroHM::HMConvert(int* h, int* m, int* s) const
{
    int i, j, k;
    double sign, x = Hm, angle;
    sign = x < 0.0 ? -1.0 : 1.0;
    x = fabs(x) * 86400.0 / 360.0;
    i = (int)x;
    j = i / 3600;
    angle = (double)j + 0.01;
    *h = (int)(floor(angle) * sign);
    k = (i - (j * 3600));
    *m = k / 60;
    *s = k % 60;
}




