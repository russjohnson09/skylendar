/***************************************************************************
                          astroutils.h  -  description
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

#ifndef ASTROUTILS_H
#define ASTROUTILS_H

#include "astrodefs.h"
#include "astroparams.h"
#include "astrostring.h"
#include "astrolist.h"
#include "astroaspects.h"
#include "astroregexp.h"

#define UTILS_NUMERROR 10000

class AstroData;

QString Translate(const char* s);
QString i18n2(const char *index, const char* fallback);

/** Swaps p1 and p2 */
template<typename t> void Swap(t&& p1, t&& p2)
{
	t&& p3 = p1;
	p2 = p1;
	p1 = p3;
}

/**
* return true if char c is in string s
*/
bool in(char c, const char *s);

/** split r in h the real part, and m, the fractional part
	@param r input value
	@param  h hour value
	@param m minute value
	@param s second value
	@param roundup if true, rounds the second upward
*/
void Hmr(double r, int& h, int& m, int& s, bool roundup = true);

/** Convert an inputed fractional degrees/minutes value to a true decimal
 degree quantity. For example, the user enters the decimal value "10.30"
 to mean 10 degrees and 30 minutes; this will return 10.5, i.e. 10
 degrees and 30 minutes expressed as a floating point degree value.      */

double DegToDec(double);

inline double operator "" _deg (const char *s) { return DegToDec(atof(s)); }

/** This is the inverse of the above function. Given a true decimal value
 for a zodiac degree, adjust it so the degrees are in the integer part
 and the minute expressed as hundredths, e.g. 10.5 degrees -> 10.30
*/

double DecToDeg(double x);

/** Returns a normalized angle. iF the given angle is greater than 359.59
	returns the corresponding value within the range 0.0 .. 359.59 */

double Normalize(double x);

/** This function splits the string str according to the pattern pat, and fills up the given AstroStringList with the plitted str parts.
@param str the source string
@param pat the split pattern
@param asl the AstroStringList
*/
void Split(const AstroString& str, const AstroString& pat, AstroStringList* asl);

/** This function splits the string str according to the pattern pat, and fills up the given AstroStringList with the plitted str parts.
@param str the source string
@param pat the regexp pattern
@param asl the AstroStringList
*/
void Split(const AstroString& str, AstroRegExp& pat, AstroStringList* asl);

/** Displays a message on screen
@param error if true, displays an error message */
void AstroMessage(const AstroString&, bool error = true);

/** Displays a question on a dialog box with Yes and No as the possible answers
@param quest the question string
@return if true, the user clicked on yes
 */
bool AstroQuestion(const AstroString& quest);

/** Displays a question on a dialog box with Yes, No and Cancel as the possible answers
@param quest the question string
@return 0, 1, 2 for Cancel, Yes and No */
int AstroQuestion3(const AstroString& quest);

/** A sprintf-like function, with the format string in second position. Accepts %c %s %d %f
 and %a, for AstroString pointers
 @param format the printf-like format string
 @param buf, a pointer to the string buffer
 @return returns a ref to *buf
 */
AstroString& Sprintf(const AstroString& format, AstroString* buf, ...);

/** Returns the days, hours and minutes differences between the julian j and j1 */
void Diffs(double j, double j1, int& days, int& hours, int& minutes, int& seconds);

/** Increment (or decrement) the julian day with minutes + days + months + years */
double IncTime(double julday, int seconds, int minutes, int hours, int days = 0, int months = 0, int years = 0);

/** Same as above, but demands julday's year and month instead, in order to avoid discrepancies
@param y the current year
@param m the current month
@return the DIFFERENCE TO ADD to the current julday */
double IncTime(int y, int m, int seconds, int minutes, int hours, int days = 0, int months = 0, int years = 0);

/** Progresses the julday with years + months + days */
double Progress(double julday, int years, int months, int days);

/** Profects, i.e. 30° = 1 year . Return the number of degrees to direct */
CONST inline double Profect(int years, int months, int days) {
    return 30.0 * years + 2.5 * months + (1.0 / 12.0) * days;
}

/** Directs the julday with years + months */
double Direct(double julday, int years, int months);

/** Return true if a is within the interval b1, b2
*/
inline bool IfIn(double a, double b1, double b2)
{
    if (b2 < b1)
    {
        double b = b2;
        b2 = b1;
        b1 = b;
    }
    if (b2 - b1 >= 180.0)
        return (a <= b1 || a >= b2);// ? true : false;
    else
        return (a >= b1 && a <= b2);// ? true : false;
}

/** Converts longitude to right ascension
@param lon longitude in degrees
@param e angle of ecliptic
@return ra in degrees */
double Lon2Ra(double lon, double e);

/** Converts right ascension to longitude
@param ra right ascension in degrees
@param e angle of ecliptic
@return longitude in degrees */
double Ra2Lon(double ra, double e);

/** Converts logitude to declination
@param lon longitude in degrees
@param e angle of ecliptic
@return dec in degrees */
CONST inline double Lon2Dec(double lon, double e) {
    return RADDEG(asin(sin(DEGRAD(lon)) * sin(DEGRAD(e))));
}

/** Ascensional difference.
@param decl declination in degrees
@param lat latitude of place in degrees */
CONST inline double Ad(double decl, double lat) {
    return RADDEG(asin(tan(DEGRAD(decl)) * tan(DEGRAD(lat))));
}

/** Ascensional difference
@param decl declination in degree
@param pole planet's pole in degrees */
CONST inline double AscDif(double decl, double pole) {
    return RADDEG(asin(tan(DEGRAD(decl)) * tan(DEGRAD(pole))));
}

/** Same as above, but with latitude of place in degrees */
CONST inline double Ad2(double dec, double lat) {
    dec = asin(tan(DEGRAD(dec)) / tan(DEGRAD(lat)));
    return RADDEG(dec);
}


/** Returns the angular difference between a and b, with repect to the 360.0 gap */
double DiffAngle(double a, double b);

/** Tells if 2 planets are applying or separating */

enum AspectAccuracy GetAspAppSep(double speed_a, double speed_b, bool before);

/** Returns a,b mid-point */
double MidPoint(double a, double b);

/** Read a SKIF file
 @param fle the file name
*/
void ReadSKIF(const AstroString& file);

/** Writes a SKIF file
@param file the file name
@param ad if ad != 0, put only this ad into file, otherwise all the Ahl, minus now
*/
void WriteSKIF(const AstroString& file, AstroData* ad = 0);

/** Given an object short name, return its id */
enum Objs GetObjId(const AstroString&);

/** Tells if the extra object i is available */
inline bool IfExtraObj(int i) {
    return Asr->EId[i - First_Extra] ? true : false;
}

/** Tells if day of night */
CONST inline bool Diurnal(double asc, double sun)
{
    if (asc < sun)
    {
        if (sun - asc >= 0.0)
            return (sun - asc) > 180.0;// ? true : false;
        else
            return (asc + 360.0 - sun) < 180.0;// ? true : false;
    }
    else
    {
        if (asc - sun <= 0.0)
            return (asc - sun) < 180.0;// ? true : false;
        else
            return (sun + 360.0 - asc) > 180.0;// ? true : false;
    }
    /* 		return (asc + 360.0 - sun) >= 180.0 ? false : true; */
    /* 	return (sun - asc) >= 180.0 ? true  : false; */
}

/** Returns the name of the ith object, or Error
@param ap if true, returns the name of the ith arabic part */
const AstroString& ObjName(int i, bool ap = false);

/** Returns the short name of the ith object, or Error
@param ap if true, returns the decimal value of the ith arabic part */
const AstroString& ObjShortName(int i, bool ap = false);

/** Gives the angle of the part referenced vy tp, from values v
@param tp, the part description
@param v the values
@return the part's position */
double CalcPart(const struct ThePart& tp, const Values& v, const _AstroRestrictions&);

#ifdef IFEXCEPT
/** Manages an exception */
void Exception(const AstroException& ae);
#endif

#endif
