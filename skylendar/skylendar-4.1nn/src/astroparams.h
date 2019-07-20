/***************************************************************************
                          astroparams.h  -  description
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


#ifndef ASTROPARAMS_H
#define ASTROPARAMS_H

#include "astrodefs.h"
#include "astrostring.h"

#ifdef KF5
class KConfig;
# include <KConfigCore/KConfigGroup>
#else
# include <QSettings>
#endif

class AstroColor;
class AstroColorList;
class AstroRestrictions;

/** This class contains the parameters which can be directely used by AstroObjs */
class ChartParams
{
public:

    // General
    bool DynamicResize;	 // if the chart is dynamically resized
    // Wheels
    bool LeftAscendant;	 // If ascendant on the leftmost point
    bool Sidebars;	 // If sidebars displayed
    bool DisplaySeconds; //If the seconds are displayed after H:M
    bool AspectsFrame; // If an aspect frame is displayed below the rings
    bool DisplayMidPoints; // If the Mid-Points are displayed
    bool CentralRing; // If a central ring of aspects lines is displayed
    bool EuropCapr; // If the european capricornus glyph is used
    bool EuropUran; // If the European uranus glyph is used
    bool EuropPlut; // If the European pluto glyph is used
    bool SortAsp;   // If the aspects list is sorted according to influence
    bool PlanetsRank; // If a table of planets ranking is displayed
    bool RiseSet;     // If objects rising/culminating/setting pos computed
    bool GlobEclipse;   // If next global eclipse data is compute
    bool AspectsConfig; // If Aspects Configuration are tracked
    bool InvBack;       // Inverse foreground/backgound
    bool BackImage;     // If background image*/
    bool Dnpf;          // Day/Night Part of fortune
    bool Southern;      // Southern births
    bool Grid;          // if displayed grid for astrograph chart
    bool Sabian;        // Displays Sabian degree
    bool Outlines;      // If wheels outlines
    bool DisplayComment;//If displayed comment
    bool Apsides;       // If planets' apsides are displayed
    bool Frameless;     // If true tarot cards displayed without colored frame
    bool DispTarotTable;// If true displays a table of spread tarot cards
    bool PlanetHour;    // If planetary hour is computed
    bool ArabicParts;   // If Arabic Parts are displayed
    bool Interpretation;// Interpretation of the natal objects
    bool InterpretTrans;// Interpretation of transiting objects
    bool Heliacal;      // Displays heliacal times of rising, settings, etc...
    bool DecTerms;      // Displays Rulers of decans and terms.
    bool Occultations;  // Displays occultations of ther planets by the moon.
    bool Borders;       // Displays the borders on the world map
    bool Constellations;// Display the boundaries of the constellations
    bool Sectors;       // Colored sectors on wheel chart
    enum Subring Subring; // Type of Subring, if any

    /** Edits the current parameters */
    bool Edit();

    /** Gets the current flags as an unsigned long bits field */
    Long GetFlags() const;

    /** Sets the flags from bitsfield */
    void SetFlags(Long bitsfield);
};

/**
*  This class manages the standard kastrolog parameters, such as the default
* latitude
*/
class AstroParams : public ChartParams
{
public:

    struct AspectData
    {
        double Angle, Orb;
        enum AspectKind Ak;
        int Color;
    };

    /** Constructor */
    AstroParams() {}

    /** Destructor */
    ~AstroParams();

    char ZPath[BUFSIZE];         // The zone info files path.
    double ExtraTime;            // Extra time to add to the "now" time.
    bool FirstNow;							 // If the first displayed chart is the "now" chart
    int  Rulers[12 * 6];         // Contains the rulers, falls, etc... for all the signs

    int Width, Height;           // The standard graphic width and height
    bool Antialias;
    int CardZoomFactor;          // The zoom factor when displaying tarots cards
    int NbLines;								 // The number of lines displayed in each section of text list.

    // The color indexes for the fire, air, water and earth elements, plus other for non specified, and color indexes for the asteroids + Chiron, and the extra objects.
    int FireColor, AirColor, WaterColor, EarthColor, OtherColor, AsteroColor, ExtraColor;

    // The database parameters
    AstroString DbName, DbUser, DbHost, DbPass, TextFont, Background;
    AstroString  SkyUser, SkyPass;
    bool IfBW;     // If prints in black & white
    bool CustomDT; // Custom date and time
    AstroString Astrologer; // Astrologer's name and address
    int IncDecGlyph; // and or remove IncDecGlyph to glyph size
    bool UTC; // Coordinated Universal Time
    bool StartInvBack; // Inverse Background at Startup
    bool RightDW; // Right Dock Widget
    float Temperature = 20.00, Pressure = 1023.0;
    char Humidity = 0;
    Long Id = 0;
    /** Load the parameters form the config file */
    bool Load();

    /** Saves these parameters into the config file */
    bool Save();

    /** Edit the parameters */
    bool Edit();

private:

    bool ConfFile;

    /**
    *  Gets a numerical argument from init file. If not defined, return default
    */
    int GetArg(const char* ident, int Default);
    /**
    *  Gets a string argument from init file. If not defined, result = default
    */
    void GetArg(const char* ident, AstroString Default, char* result, int size);

    /** Gets a string argument from init file. If not defined, result = default
    */
    AstroString GetArg(const char* ident, const AstroString& Default);
    /**
    *  Gets a double argument from init file. If not defined, return default
    */
    double GetArg(const char* ident, double Default);

    /** Gets a bool argument from init file. If not defined return result */
    bool GetArg(const char* ident, bool Default);

    /** Initializes the color list from an array of 16 rgb triplets */
    void GetArg(const char* ident, AstroColorList&, const unsigned char *);

    /** Initializes an array of int with nb elems */
    void GetArg(const char* ident, int* result, const int* Default, int nb);

    /** Initializes an array of bool with nb elems */
    void GetArg(const char* ident, bool *result, const bool* Default, int nb);

    /** Initializes an array of double with nb elems */
    void GetArg(const char* ident, double *result, const double* Default, int nb);

    /** Initializes the AspData table */
    void GetArg(const char* ident, struct AspectData *result, const struct AspectData * Default);

    Long GetArg(const char* ident, Long Default);

    /** Sets the relevant arguments group */
    void SetGroup(const AstroString&);

    void SetArg(const char* ident, int);

    void SetArg(const char* ident, const AstroString&);

    void SetArg(const char* ident, const char*);

    void SetArg(const char* ident, double);

    void SetArg(const char* ident, bool);

    void SetArg(const char* ident, const int*, int nb);

    void SetArg(const char* ident, const AstroColorList&);

    void SetArg(const char* ident, const Long);

#ifdef KF5
    KConfig* KConf;
    KConfigGroup Kg;
#else
QSettings* Qs;
#endif
};

#endif
