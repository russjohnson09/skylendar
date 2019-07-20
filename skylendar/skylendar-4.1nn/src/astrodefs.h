/***************************************************************************
                          astrodefs.h  -  description
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

#ifndef ASTRODEFS_H
#define ASTRODEFS_H

#define BUFSIZE 80
#include "../config.h"
#include "astrostring.h"
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#define TWOPI (2.0 * PI)
#endif

#define cot(x) (1.0 / tan(x))
extern int NbStars, Final_Star;

class AstroSigns;
class AstroResources;
class AstroColorList;
class AstroAspectsTable;
class AstroInterface;
class AstroRestrictionsList;
class AstroDataList;
class AstroChartList;
class AstroIconsList;
class AstroData;
class AstroRestrictions;
class AstroMainWindow;
class AstroSQL;
class AstroWorldMap;
class AstroTzList;

#ifndef FAR
# define FAR
#endif
#ifndef PASCAL_CONV
# define PASCAL_CONV
#endif

#ifndef MSDOS
# define MSDOS 0
#endif

// C++ type conversion
#define SC(type, expr) static_cast<type>(expr)
#define CSC(type, expr) const_cast<type>(expr)
#define DC(type, expr) dynamic_cast<type>(expr)
#define RC(type, expr) reinterpret_cast<type>(expr)

#define RESTR __restrict__
#define API __attribute__ ((visibility("default")))
#define CONST __attribute__((const))

#if __SIZEOF_LONG__ == 8
    typedef long Long;
#else
    typedef long long Long;
#endif

class QString;
#ifdef LAN_CONTEXT
#define i18n(s) tr(s)
#define i18n2(s, f) tr(s, f)
#else
#define i18n(s) Translate(s)
QString i18n2(const char *index, const char* fallback);
#endif

#define DEGCHAR u8"\u00B0"

#ifdef QT
# define SKYSERVICE "/Skyservice"
# define SCANCLIENT "/Scanclient_"
# define ORGSKYLENDAR "org.skylendar"
#else
# define Q_CHECK_PTR(ptr)
#endif
#define SKYSITE QString("http://skylendar.org")

// The number of simultaneous datasets in a chart
#define NBDATA 4
// The maximum number of stars
#define NBSTARS 100
// The out of scope or illegal zodiacal longitude value
#define NOVALUE 400.0
// The number of standard objects
#define OBJNB 23

// Number of different scores + predefined scores
#define NBSCORES   9
#define CONJASCMC 10
#define CONJDESCFC 7
#define MASASCMC  10
#define OWNSIGN    5
#define CONJMAS    5
#define PERMAS     1
#define PERASP     1
#define EXALT      7
#define DECTERM    3

// Objects index
enum Objs
{
	  Undefined_Obj = -1,
    Sun, Moon, Mercury, Venus, Mars, Jupiter, Saturn, Uranus,
    Neptune, Pluto, North_Node, South_Node, Black_Moon, The_Earth,
    Chiron, Pholus, Ceres, Pallas, Juno, Vesta, Fortune, Vertex, East_Point,
    First_Extra, Last_Extra = 98, XPoint,
    Ascendant, MC, FC, Descendant,
    House_1, House_2, House_3, House_4, House_5, House_6, House_7, House_8,
    House_9, House_10, House_11, House_12,
    First_Star, Last_Star = First_Star + NBSTARS
};

#define ARABPART (enum Objs)-2
#define NBEXTRA (Last_Extra - First_Extra)
#define Last_Planet  East_Point
#define UO           Undefined_Obj
#define Last_Major   Sextile
#define First_Minor  Inconjunct
// Signs index
enum Signs
{
    Aries, Taurus, Gemini, Cancer, Leo, Virgo, Libra, Scorpio,
    Sagittarius, Capricorn, Aquarius, Pisces, Undefined_Sign
};

// Elements index
enum Elements { Fire, Air, Water, Earth, Undefined_Element };

// Triplicity index
enum Triplicity { Cardinal, Fixed, Mutable };

// Houses index
enum House
{
    Placidus, Koch, Porphyrius, Regiomontanus, Campanus, Equal, Vehlow, Meridian,
    Azimuthal, Topocentric, Alcabitus, Morinus, Whole, Krusinski, APC, Carter, EqualMC, SunShine,EqualAsc, PSD, PSR, Sripati
};

// Sidereal charts systems index
enum Sidereal { Tropical = -1, Fagan_Bradley,  Lahiri, Deluce, Raman, Ushashashi,
                Krishnamurti, Djwhal_Khul, Yukteshwar, Jn_Bhasin, Babyl_Kugler_1,
                Babyl_Kugler_2, Babyl_Kugler_3, Babyl_Huber, Babyl_Etpsc, Aldebaran_15Tau,
                Hipparchos, Sassanian, Galcent_0Sag, J2000, J1900, B_1950, Suryasiddhanta, Suryasiddhanta_Msun, Aryabhata, Aryabhata_Msun, SS_Revati, SS_Citra, True_Citra, True_Revati
              };

// Aspects index

enum Aspects { Conjunction, Opposition, Trine, Square, Sextile, Inconjunct,
               Semisextile, Semisquare, Sesquiquadrate, Quintile, Biquintile, Semiquintile,
               Septile, Novile, Binovile, Biseptile, Triseptile, Quatronovile, Parallel, Antiparallel, Antiscion, Contra_Antiscion, Unknown_Aspect
             };

// If an aspect is harmonic (trine), dissonant (square) or ambivalent (conjunction, oppos)
enum AspectKind { Harmonic, Dissonant, Ambivalent };

// Type of chart wheel, matrix, lists, etc...
enum ChartType { NullChart, StdWheels, GraphicList, AspScList, LocalHorizon, ObjectList, AspectsArray, Ephemeris, Astro_Graph, Squared, SolarSys, Tarots_Spreads, Directions, Gauquelin, House_Pos, Batch, TensorFlow, Unknown_ChartType };

// Aspects scan span
enum ScanSpan { Current_Day, Current_Month, Current_Year, Years, Solar_Rev, Lunar_Rev };

//Subtype of chart. If chart have 2 independant rings, transiting or progressing charts, etc...
enum ChartSubType { NoSt, Show_Hide, ExtrnSave, AFirst, ASecond, Single, Transit, Direction, Progression, AddAngle, MulAngle, Composite, TimeSpace, SolarArc, Profection };

enum SubTypeState { Master, Slave, AMaster, ASlave, Unknown_State };

#define Last_SubType Profection
#define Last_Type TensorFlow

// If the chart is an ASCII text, a drawing or an HTML page
enum ChartMode { TextMode, GraphicMode, HTMLMode };

// Type of Subring
enum Subring { No_Subring, Decans, Solar_Houses, Lunar_Houses, Nodal_Houses, Terms };

// When an object is conjunct to an angle
enum ConjAngles { Rising, Setting, Culminating, AtNadir };

// Computing modes
enum CompModes { Ecliptical, Equatorial, Local, Gauq, HousePos };

// types of scan events
enum AspKind { ExAsp, ChangeDir, ChangeSign, RiseSet, Eclipse, EphemDay, ExDir, ExCDir, GlobOccult, HelRising, HelSetting, EveningFirst, MorningLast, BatchAsp };

// Aspects configurations
enum AspConfig { Grand_Trine, T_Square, Stellium, Grand_Cross, Yod, Myst_Rect, David_Star };

// Type of calendar or date systems
enum DateSystem { Julian, Localhour, D1901, Timezone, D2038, Invalid_date };

// Types of Tarots Cards
enum TarotTypes { Major, Swords, Coins, Sticks, Cups };

// Known tarots spreads
enum TarotSpreads { Cross_Shaped, Horse_Shoe, Pyramid, Wheel, Celtic };

/** Type of primary direction */
enum DirType { Mundane, Zodiacal };

/* Type of static key */
enum StatKey { Ptolemy, Naibod, Simmonite, Placidian, Cardan, Synodic, Custom };

// Some default values

#define DEF_DAY           1
#define DEF_MONTH         1
#define DEF_YEAR          2000
#define DEF_TIME          12.00
#define DEF_LATITUDE      0.0
#define DEF_LONGITUDE     0.0
#define DEF_TIMEOFFSET    1.0
#define DEF_NAME          "no name"
#define DEF_DYNAMICRESIZE false
#define DEF_LEFTASCENDANT false
#define DEF_SECONDS       false
#define DEF_ASPECTS_BAR   true
#define DEF_CENTRAL_RING  true
#define DEF_PLANET_RANK   false
#define DEF_RISESET       false
#define DEF_GLOB_ECLIPSE  false
#define DEF_ASPECTS_CONFIG false
#define DEF_INVBACK       false
#define DEF_START_INVBACK false
#define DEF_GRID          true
#define DEF_SABIAN        false
#define DEF_SUBRING       No_Subring
#define DEF_MID_POINTS    false
#define DEF_EUROP_CAPR    false
#define DEF_SORT_ASP      false
#define EUROP_URAN        false
#define EUROP_PLUT        false
#define DEF_SIDEBARS      true
#define DEF_trueNODE      false
#define DEF_HELIOCENTRIC  false
#define DEF_EQUATORIAL    false
#define DEF_HOUSESYS      Placidus
#define DEF_TROPICAL_SIDEREAL Tropical
#define DEF_DATABASE      "skylendar"
#define DEF_DB_USER       "skylendar"
#ifdef __WINNT
#define DEF_DB_HOST       "127.0.0.1"
#else
#define DEF_DB_HOST       ""
#endif
#define DEF_TEXT_FONT     ""
#define DEF_SECONDS       false
#define DEF_PRINT_BW      false
#define DEF_CUSTOM_DT     false
#define DEF_DNPF          true
#define DEF_SOUTERN       false
#define DEF_INV_BACK      false
#define DEF_RIGHTDW       false
#define DEF_PROG_FACT     365.2422
#define DEF_THRESHOLD     0
#define DEF_ASTROLOGER    ""
#define DEF_INCDECGLYPH   0
#define DEF_UTC           false
#define DEF_OUTLINES      false
#define DEF_COMMENT       true
#define DEF_APSIDES				false
#define DEF_FRAMELESS     false
#define DEF_ARABIC_PARTS  false
#define DEF_INTERPRETATION false
#define DEF_INTERPRETTRANS false
#define DEF_HELIACAL      false
#define DEF_DECTERMS      false
#define DEF_OCCULTATIONS  false
#define DEF_BORDERS       true
#define DEF_CONSTELLATIONS false
#define DEF_SECTORS       false
#define DEF_DISPTAROTTABLE false
#define DEF_ZOOM_FACTOR   100
#define DEF_NBLINES				500
#define DEF_PLANET_HOUR     false
#define DEF_RESTRICTIONS  { \
 { /* Sun */ false, 1.0, 30 }, \
 { /* Moon */ false, 1.0, 25 }, \
 { /* Mercury */ false, 0.0, 10 }, \
 { /* Venus */ false, 0.0, 10 }, \
 { /* Mars */ false, 0.0, 10 }, \
 { /* Jupiter */ false, 0.0, 10 }, \
 { /* Saturn */ false, 0.0, 10 }, \
 { /* Uranus */ false, 0.0, 10 }, \
 { /* Neptune */ false, 0.0, 10 }, \
 { /* Pluto */ false, 0.0, 10 }, \
 { /* North Node */ false, 0.0, 5 }, \
 { /* South Node */ false, 0.0, 5 }, \
 { /* Black Moon */ false, 0.0, 5 }, \
 { /* Earth */ true, 0.0, 20 }, \
 { /* Chiron */ true, 0.0, 5 }, \
 { /* Pholus */ true, 0.0, 5 }, \
 { /* Ceres */ true, 0.0, 5 }, \
 { /* Pallas */ true, 0.0, 5 }, \
 { /* Juno */ true, 0.0, 5 }, \
 { /* Vesta */ true, 0.0, 5 }, \
 { /* Fortune */ false, 0.0, 5 }, \
 { /* Vertex */ true, 0.0, 5 }, \
 { /* East Point */ true, 0.0, 5 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { true, 0.0, 0 }, \
 { /* XPoint */    true,  0.0, 0 }, \
 { /* Ascendant */ false, 0.0, 20 }, \
 { /* Midheaven */ false, 0.0, 20 }, \
 { /* Nadir */ false, 0.0, 10 }, \
 { /* Descendant */ false, 0.0, 10 }, \
 { /* 1st House */ true, 0.0, 20 }, \
 { /* 2nd House */ true, 0.0, 5 }, \
 { /* 3rd House */ true, 0.0, 5 }, \
 { /* 4th House */ true, 0.0, 10 }, \
 { /* 5th House */ true, 0.0, 5 }, \
 { /* 6th House */ true, 0.0, 5 }, \
 { /* 7th House */ true, 0.0, 10 }, \
 { /* 8th House */ true, 0.0, 5 }, \
 { /* 9th House */ true, 0.0, 5 }, \
 { /* 10th House */ true, 0.0, 20 }, \
 { /* 11th House */ true, 0.0, 5 }, \
 { /* 12th House */ true, 0.0, 5 },}
#define DEF_HOUSES_COMP true
#define DEF_EXTRA_COMP false
#define DEF_STARS_COMP  false
#define DEF_MINOR_COMP  false
#define DEF_NOW_CHART   true
#define DEF_RULERS      {\
  Mars, UO, Venus, UO, Sun, Saturn,\
  Venus, UO, Pluto, Mars, Moon, Uranus,\
  Mercury, UO, Jupiter, UO, UO, Neptune,\
  Moon, UO, Saturn, UO, Jupiter, Mars,\
  Sun, UO, Uranus, Saturn, Neptune, Mercury,\
  Mercury, Ceres, Neptune, Jupiter, Pluto, Venus,\
  Venus, UO, Mars, UO, Saturn, Sun,\
  Pluto, Mars, Venus, UO, Uranus, Moon,\
  Jupiter, Neptune, Mercury, UO, UO, UO,\
  Saturn, Uranus, Moon, UO, Mars, Jupiter,\
  Uranus, Saturn, Sun, UO, Mercury, UO,\
  Neptune, Jupiter, Pallas, Mercury, Venus, Pluto\
}

#define DEF_GRAPHIC_WIDTH  600
#define DEF_GRAPHIC_HEIGHT 450
#define DEF_ANTIALIAS false
#define DEF_COLORS      {\
   0,   0,   0,\
 176,  48,  96,\
   0, 100,   0,\
 255,  65,   0,\
   0,   0, 139,\
 139,   0,   0,\
   0, 139, 139,\
 211, 211, 211,\
   0, 100,   0,\
 255,   0,   0,\
   0, 255,   0,\
 255, 255,   0,\
   0,   0, 255,\
 255,   0, 255,\
   0, 255, 255,\
 255, 255, 255\
}

#define DEF_FIRE_COLOR    9
#define DEF_AIR_COLOR    14
#define DEF_WATER_COLOR   4
#define DEF_EARTH_COLOR   1
#define DEF_OTHER_COLOR   8
#define DEF_ASTERO_COLOR 13
#define DEF_EXTRA_COLOR  1
#define DEF_ASPECTS_CONST {\
/* Angle, Kind, Harmonic */ \
{ /*Conjunction */   0.0, Ambivalent, 1 },\
{ /*Opposition */  180.0, Ambivalent,12 },\
{ /*Trine */       120.0, Harmonic,   6 },\
{ /*Square */       90.0, Dissonant,  4 },\
{ /*Sextile */      60.0, Harmonic,   6 },\
{ /*Inconjunct */  150.0, Ambivalent, 0 },\
{ /*Semisextile */  30.0, Harmonic,   6 },\
{ /*Semisquare */   45.0, Dissonant,  4 },\
{ /*Sesquiquadrat*/135.0, Dissonant,  4 },\
{ /*Quintile */     72.0, Harmonic,   5 },\
{ /*Biquintile */  144.0, Harmonic,   5 },\
{ /*Semiquintile */ 36.0, Harmonic,   5 },\
{ /*Septile */ 360.0/7.0, Harmonic,   7 },\
{ /*Novile */       40.0, Harmonic,   9 },\
{ /*Binovile */     80.0, Harmonic,   9 },\
{ /* Biseptil*/720.0/7.0, Harmonic,   7 },\
{ /*Trisepti*/1080.0/7.0, Harmonic,   7 },\
{ /*Quatronovile */160.0, Harmonic,   9 },\
{ /* Parallel */     0.0, Ambivalent, 1 },\
{ /* Anti-parallel */0.0, Ambivalent,12 },\
{ /* Antiscion */    0.0, Harmonic,   1 },\
{ /* Cnt Antiscio*/  0.0, Harmonic,   1 }\
}

#define DEF_ASPECTS_RESTRICTIONS {\
/* Rest, Orb, Color, Influence */ \
 { /* Conjunction */ false, 10.0, 11, 30 },\
 { /*Opposition */   false,  9.0, 12, 20 },\
 { /* Trine */       false,  7.0, 10, 15 },\
 { /* Square */      false,  7.0,  9, 15 },\
 { /* Sextile */     false,  6.0, 13, 10 },\
 { /*Inconjunct */   false,  4.0,  7,  5 },\
 { /*Semisextile */  false,  3.0,  6,  5 },\
 { /*Semisquare */   false,  3.0,  4,  5 },\
 { /*Sesquiquadrate*/false,  3.0,  1,  5 },\
 { /*Quintile */     false,  3.0, 14,  4 },\
 { /*Biquintile */   false,  2.0, 14,  2 },\
 { /*Semiquintile */ false,  2.0, 14,  2 },\
 { /*Septile */      false,  3.0, 13,  4 },\
 { /*Novile */       false,  3.0,  9,  4 },\
 { /*Binovile */     false,  2.0,  9,  2 },\
 { /*Biseptile*/     false,  2.0, 13,  2 },\
 { /*Triseptile */   false,  2.0, 13,  2 },\
 { /*Quatronovile */ false,  2.0,  9,  2 },\
 { /* Parallel */    false,  2.0, 11,  2 },\
 { /* Anti-parallel*/false,  2.0, 12,  2 },\
 { /* Antiscion */   false,  2.0, 11,  2 },\
 { /* Cnt Antiscio*/ false,  2.0, 11,  2 }\
}

#define DEF_DECANS \
{ Mars, Sun, Venus, \
  Mercury, Moon, Saturn, \
  Jupiter, Mars, Sun, \
  Venus, Mercury, Moon, \
  Saturn, Jupiter, Mars, \
  Sun, Venus, Mercury, \
  Moon, Saturn, Jupiter, \
  Mars, Sun, Venus, \
  Mercury, Moon, Saturn, \
  Jupiter, Mars, Sun, \
  Venus, Mercury, Moon, \
  Saturn, Jupiter, Mars }

// Default scores table
#define DEF_SCORES { CONJASCMC, CONJDESCFC, MASASCMC, OWNSIGN, CONJMAS, PERMAS, PERASP, EXALT, DECTERM }

// Masters of days. Monday = Moon, Tuesday = Mars, etc...
#define DEF_MASDAY { Moon, Mars, Mercury, Jupiter, Venus, Saturn, Sun }

// Order of masters of hours
#define DEF_ORMAH { Saturn, Jupiter, Mars, Sun, Venus, Mercury, Moon }

#define DEF_TERMS {{ {Jupiter, 6}, {Venus, 14}, {Mercury, 21}, {Mars, 26}, {Saturn, 30} },\
 { {Venus, 8}, {Mercury, 15}, {Jupiter, 22}, {Saturn, 26}, {Mars, 30} },\
 { {Mercury, 7}, {Jupiter, 14}, {Venus, 21}, {Saturn, 25}, {Mars, 30} },\
 { {Mars, 6}, {Jupiter, 13}, {Mercury, 20}, {Venus, 27}, {Saturn, 30} },\
 { {Saturn, 6}, {Mercury, 13}, {Venus, 19}, {Jupiter, 25}, {Mars, 30} },\
 { {Mercury, 6}, {Venus, 13}, {Jupiter, 18}, {Saturn, 24}, {Mars, 30} },\
 { {Saturn, 6}, {Venus, 11}, {Jupiter, 19}, {Mercury, 24}, {Mars, 30} },\
 { {Mars, 6}, {Jupiter, 14}, {Venus, 21}, {Mercury, 27}, {Saturn, 30} },\
 { {Jupiter, 8}, {Venus, 14}, {Mercury, 19}, {Saturn, 25}, {Mars, 30} },\
 { {Venus, 6}, {Mercury, 12}, {Jupiter, 19}, {Mars, 25}, {Saturn, 30} },\
 { {Saturn, 6}, {Mercury, 12}, {Venus, 20}, {Jupiter, 25}, {Mars, 30} },\
 { {Venus, 8}, {Jupiter, 14}, {Mercury, 20}, {Mars, 26}, {Saturn, 30} }}

// Standard path to the zone info files
extern QString SkyPath;
#ifdef __WINNT
#define ZPATH (SkyPath + "/zoneinfo")
#else
#define ZPATH "/usr/share/zoneinfo/"
#endif
#define STDZFILE "GMT"
#define SWEPATH "../"

// Font names
#define ASTROFONT "skylendar"
#define TEXTFONT "Times"

// Print factors
#define PRINTZOOMFACT 5
#define BOLDLINE 4

// The characters in ASTROFONT corresponding to the signs and planets glyphs
#define SIGNCHARS "0123456789:;"
#define ALTCAPR '<'
#define ALTPLU '_'
#define ALTURA '^'
#define PLACHARS "ABCDEFGHIJKLMNO QRSTUV                          "
#define ASPCHARS "abcdefghijklmnopqrstuv"
#define HOUSESCODES "PKORCAVXHTBMWUYFDINLQS"

// The julian day value of 1 minute;
#define ONEMINUTE  0.000694444444
// The julian day value of 1 second
#define ONESECOND 1.15740740740741e-05
// Number of minutes in a day
#define MINSINDAY   ((23 * 60) + 56)
// Number of hours in a year
#define HOURSINYEAR ((365 * 24) + 6)

// Returns an hour/minute value as double
#define MILLIROUND 0.005
#define RHM(h, m, s)((double)(h) + ((double)(m) / 100.0) + ((double)(s) / 10000.0))

extern void Hmr(double r, int& h, int& m, int& s, bool roundup);
#define HMR(r, h, m, s) Hmr(r, h, m, s, false)

#define ROUND 0.5
#define FRACT(r) ((r) - floor(r))
#define SIGN(r) ((r) < 0.0 ? -1 : ((r) > 0.0 ? 1 : 0))

// Degrees -> radians and radians -> degrees tranformation
#define DEGRAD(x) (TWOPI * (x) / 360.0)
#define RADDEG(x) (360.0 * (x) / TWOPI)

// The julian day of the julian->gregorian calendar shift
#define J2G 2299161.000000
// The maximum Julday managed by the swisseph
#define MAXJD 3697000.5
// Its minimum Julday
#define MINJD -254900.5

// database index type
typedef unsigned int Index;

// Default sizes
#define ASTRORINGSDEFSIZE 400
#define BOUND 2147483646

// Some swelib flags
#ifndef SEFLG_SPEED
# define SEFLG_SPEED 256L
#endif
#define SE_ECL2HOR    0
#define SE_ECL_CENTRAL          1
#define SE_ECL_NONCENTRAL       2
#define SE_ECL_TOTAL            4
#define SE_ECL_ANNULAR          8
#define SE_ECL_PARTIAL          16
#define SE_ECL_ANNULAR_TOTAL    32
#define SE_ECL_PENUMBRAL        64
#define SE_ECL_VISIBLE          128
#define SE_ECL_MAX_VISIBLE      256
#define SE_ECL_1ST_VISIBLE      512
#define SE_ECL_2ND_VISIBLE      1024
#define SE_ECL_3RD_VISIBLE      2048
#define SE_ECL_4TH_VISIBLE      4096

// Various extern objects
extern AstroSigns  *Asg;
extern AstroResources *Asr;
extern AstroColorList *Acl;
extern AstroAspectsTable *Aat;
extern AstroInterface* Asf;
extern AstroIconsList* Ail;
extern AstroRestrictionsList* Arl;
extern AstroDataList* Adl;
extern AstroChartList* Ahl;
extern AstroData* Now;
extern AstroRestrictions* Drs;
extern AstroMainWindow* Amw;
extern AstroSQL* Asq;
extern AstroWorldMap* Awm;
extern AstroTzList* Atl;
extern void Pass();

#define P Pass()
#define COL (*Acl)

#endif





