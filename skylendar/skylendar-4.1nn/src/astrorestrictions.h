/***************************************************************************
                          astrorestrictions.h  -  description
                             -------------------
    begin                : Wed Apr 18 2001
    copyright            : (C) 2001 by Christophe Gros
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

#ifndef ASTRORESTRICTIONS_H
#define ASTRORESTRICTIONS_H

#include "astrodefs.h"
#include "astrolist.h"
#include "astroaspects.h"
#include <functional>

class AstroRequest;

typedef std::function<void(int)> fun;
//typedef std::function<void(int)->bool> fun for future use

struct Rest
{
    bool Rest;
    double OrbAdd;
    int Influence;
};

/** Restrictions set class
 (whether a planet or aspect is computed or not, orbs, etc...)
*/
class _AstroRestrictions
{
public:

    friend class _AstroAspects;
    friend class EditRestrictions;
    friend class AstroComputing;

    /** Returns true if index is NOT restricted, false otherwise */
    bool operator == (int index) const;

    /** Returns true if index is restricted, false otherwise */
    bool operator != (int index) const;

    /** Sets the restriction flag of the index object to b */
    void Restrict(int index, bool b);

    /** Count the number of non-restricted objects */
    inline int CountObjs() const {
        return Count;
    }

    /** If the houses are restricted */
    inline bool IfHouses() const {
        return Houses;
    }

    /** If the extra object are restricted */
    inline bool IfExtra() const {
        return Extra;
    }

    /** If the Stars are restricted */
    inline bool IfStars() const {
        return Stars;
    }

    inline bool IfMinor() const {
        return Minor;
    }

    /** (Un)restrict all the houses */
    inline void RestHouses(bool b) {
        Houses = b;
        CountObjects();
    }

    /** (Un)restrict all the extra objects */
    inline void RestExtra(bool b) {
        Extra = b;
        CountObjects();
    }

    /** (Un)restrict all the stars */
    inline void RestStars(bool b) {
        Stars = b;
        CountObjects();
    }

    inline void RestMinor(bool b) {
        Minor = b;
    }

    /** If aspect index is restricted */
    inline bool Asp(int index) const {
        return (index < 0 || index >= Unknown_Aspect) ? true : Asprst[index].Rest;
    }

    /** Sets the aspects restriction flag of the index object to b */
    void AspRestrict(int index, bool b);

    void SetHousesSys(enum House, bool hide = true);
    inline enum House GetHouse() const {
        return House;
    }

    /** Returns the value of the ith ith score */
    inline int operator / (int i) const {
        return (i < 0 || i >= NBSCORES) ? -1 : Scores[i];
    }
    /** Returns the ith Asprst */
    inline const struct AspectRestrictions* operator * (int i) const {
            return (i >= 0 && i < Unknown_Aspect) ? &Asprst[i] : nullptr;
        }

		/** Execute f over all the available objets */
		bool operator()(fun f) const;
 
		/** Execute f over all the available objets */
		bool Iterate(fun f, bool extras = true, bool houses = true, bool stars = true) const;

		/** Iterator for loops. Returns the next index after i */
		int operator+ (int i) const;

    Index Idx;             // The current2 database index

    bool Modified;         // If modified
    bool Heliocentric;     // heliocentricaspects
    bool Equatorial;       // equatorial positions

    bool TrueNode;	 // If the Nodes are true instead of mean.
    bool Dnpf;             // Day/Night part of fortune
    bool Southern;	// For specific southern hemisphere
    enum Sidereal Sidereal; // Sidereal charts system.
    enum Objs LastExtra;
    double ProgFact;
    short Threshold;

protected:

    // Objects restrictions
    struct Rest Restr[Last_Star + 1];
    bool Houses, Extra, Stars, Minor;
    struct AspectRestrictions Asprst[Unknown_Aspect];
    double MPOrbSub;
    enum House House;	 // The default house system.
    void CountObjects();
    int Count, Scores[NBSCORES];
};

class AstroRestrictions: public _AstroRestrictions
{
   	Q_DECLARE_TR_FUNCTIONS(AstroRestrictions)

public:

    /** Constructor */
    AstroRestrictions();

    /** Opens an edit dialog box
      	@return true if clicked OK, false otherwise
      */
    bool Edit();

    /** Initializes with the Rest set idx
     	@param idx the database rest set index
     	@return bool true if found and loaded
     */
    bool DbFetch(Index idx);

    /** Initializes with the Rest set name name
     	@param name the database rest set name
     	@return bool true if found and loaded
     */
    bool DbFetch(const AstroString& name);

    /** Store the rest set into the database
     	@return the rest set database record index */
    Index DbSave();

    /** Restricts all the planet, houses, stars, etc... */
    void RestrictAll();

    /** Restricts all the aspects */
    void RestrictAllAsps();

    AstroString Name;

    bool Preload, Default;

private:

    void ObjIU(AstroRequest& arq, int f, int l, bool update = false);
};

class AstroRestrictionsList: public AstroList<AstroRestrictions>
{

	Q_DECLARE_TR_FUNCTIONS(AstroRestrictionsList)

public:

    /** Constructor */
    AstroRestrictionsList();

    /** Destructor */
    ~AstroRestrictionsList();

    /** Adds a restrictions set */
    void AddRestrictions(AstroRestrictions* ar);

    /** Gets a restrictions set from ites index */
    AstroRestrictions* Get(Index) const;

		/** Gets the default restrictions set */
    AstroRestrictions* GetDefault() const;

    /** Removes a restrictions set from database, knowing its index */
    bool RemoveFromDb(Index idx);

    /** Checks if the name already exists in the list */
    bool CheckName(const AstroString&, Index idx);

private:

    Index Max;
};

#endif

