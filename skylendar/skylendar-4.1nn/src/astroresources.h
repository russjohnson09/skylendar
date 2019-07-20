/***************************************************************************
                          astroresources.h  -  description
                             -------------------
    begin                : Mon Oct 9 2000
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

#ifndef ASTRORESOURCES_H
#define ASTRORESOURCES_H

#include "astrostring.h"
#include "astrodefs.h"
#include "astroparams.h"
#include "astrolist.h"
#include <QtCore>

class AstroApp;

class AstroPixmap;
class AstroObjs;
class AstroRequest;

#ifdef QT
class QFont;
#endif

/**This class provides constants resources such as planets names, signs names , etc...
  *@author Christophe Gros
  */
class AspScanParams
{
public:

    AspScanParams();
    enum ScanSpan Ss;
    int NbYears;
    bool MP, DumpAsp, AP;
};

/** This class maintains a list of all the Indexes used by AspTbl for
discriminating the various dumps */
class AspIndexes: public AstroList<Index>
{
public:

    AspIndexes() {}
    inline ~AspIndexes() {
        Purge();
    }
    /** Gets a new Indexes
    @param a given AstroRequest
    @return Index new fresh index from the sequence
    */
    Index GetIdx(AstroRequest& arq);

    /** Deletes all the tuples with the given index */
    void Delete(Index idx, AstroRequest& arq);

    /** Destroys all the tuples from AspTbl with the present indexes*/
    void Purge();
};

struct ExtraId
{
    inline ExtraId() {
        memset(Data, 0, sizeof(int) * NBEXTRA);
        Last = 0;
    }
    inline int& operator[](int i) {
        return Data[i];
    }
    unsigned char Last;
    int Data[NBEXTRA];
};

#ifdef IFEXCEPT
enum ExceptionsType { DbException, SksException, ListException, OtherException };

// support for exceptions. It seems that the KDE team doesn't like the exceptions.
// So, let or remove the IFEXCEPT statement in configure.in

class AstroException
{
public:
    AstroException(enum ExceptionsType et, AstroString& text) {
        Et = et;
        Text = text;
    }

    enum ExceptionsType Et;
    AstroString Text;
};
#endif

class AstroResources: public AstroParams
{
	Q_DECLARE_TR_FUNCTIONS(AstroResources)

public:

    friend class AstroObjs;

    // The days and months names
    AstroString *DayNames[7], *DayShortNames[7], *MonthNames[12], *MonthShortNames[12];
    AstroString *HousesSystemNames[22], *SiderealSystemNames[30];

    // The names and short names (3 characters) of the standard objects
    AstroString *ObjNames[40], *ObjShortNames[40], *ObjError, *ObjShortError;

    // The names and short names (3 characters) of the astrological signs
    AstroString *SignsNames[12], *SignsShortNames[12], *SignsError;

				struct StNames
		{
			int Idx;
			AstroString *Name, *SName;
		} *StaNames;

				AstroString *StarsError;

    // The extra objects' names, shortnames
    AstroString *ExtraNames[NBEXTRA], *ExtraShortNames[NBEXTRA];

    // First, Second, Third abbreviations
    AstroString *NthAbbrev[12];

    // Aspects names and short names */
    AstroString *AspectNames[Unknown_Aspect], *AspectShortNames[Unknown_Aspect];

    // The tables of Elements for the given planets and houses
    enum Elements ElemPla[Last_Planet],  ElemHouses[House_12 - Ascendant + 1];


    // Names of the chart types
    AstroString* TypesNames[17];

    // Names of the rings subtypes
    AstroString *SubTypesNames[Last_SubType + 1];

    // Short names of the rings subtypes
    AstroString* SubTypesShortNames[Last_SubType + 1];

    // Names of Jump bases
    AstroString* JumpBaseNames[7];

    // Names of subrings
    AstroString* SubringsNames[6];

    // Names of aspects configuratrions
    AstroString* AspConfigNames[7];

    // Names of the various calendar and date systems
    AstroString* DateSysNames[7];

    // Names of the major tarots cards
    AstroString* MajTarots[23];

    // Names for Minor cards 1..10, servant, rider, queen, king
    AstroString* MinTarots[18];

    // Names of the subtype states
    AstroString *StateNames[Unknown_State + 1], *StateShortNames[Unknown_State + 1];

    // Names of the Arabic Parts
    AstroString **PartsNames, **InterTarots;

    // Array of Arabic Parts
    struct ThePart* Parts;

    // Number of parts
    int NbParts;

    // Various pixmaps
    AstroPixmap* MiscPixmaps[20];

    // Pixmaps for chart types
    AstroPixmap* TypePixmaps[16];

    AstroPixmap* TarotsPixmaps[78];

    // The default zone info file
    char DefZFile[BUFSIZE];

    AstroString SWEphems, IconsPath, DateFormat, DateShortFormat, TimeFormat, DateTimeFormat, STimeFormat, SDateTimeFormat; // Date and time format

    int ScanId; // The ScanClient ID

    int FontSize; // The text font size

    bool IfPrint; // If printing

    bool IfDebug; // If debug mode

    bool Shift, Ctrl; // true when shift or alt keys pressed

    QFont *Astro;

    ExtraId EId; // Local/real Ids for extra objects

    int TblId; // ID for AspScanList temporary table

    char Lang[3]; // locale lang code, e.g. 'en' for english;

    AspIndexes AspIdx;
    enum Objs LastExtra;
    void SetDefZFile();
    void InitExtraNames();
    bool SetTarotsPixmaps(bool load = true);
    bool LoadParts();
    bool LoadInterTarots(bool load = true);
    bool LoadStars();
    bool LoadInterpl();
    AstroString GetInterp(int) const;
    AstroResources();
    ~AstroResources();

private:

    int LoadCount, TaCount;
#ifdef QT
    QHash<int, AstroString*> Interpl;
#endif
#ifdef QT
    void fill(AstroString *t[], AstroString* c, ...);
#else
    void fill(AstroString *t[], char* c, ...);
#endif
    void fill(enum Elements *t, int e, ...);

    void fill(AstroPixmap *t[], const char* c, ...);

    AstroString SetDateFmt(AstroString* a, const AstroString b);

    void SetIT(char c, int n, AstroString as);

};

#endif
