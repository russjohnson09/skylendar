/***************************************************************************
                          astroaspects.h  -  description
                             -------------------
    begin                : Mon Feb 7 2001
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

#ifndef ASTROASPECTS_H
#define ASTROASPECTS_H

#include "../config.h"

#include "astrodefs.h"
#include "astrolist.h"
#include "astrostring.h"
#include "astroresources.h"
#include "astrotable.h"

#define AL(a, b) AspTable.Get(a, b)

class AstroObjs;
class AstroRestrictions;
class _AstroRestrictions;
class Values;
class AspectFound;
class AstroMidPoints;

struct AspectsConstants
{
    double Angle;
    enum AspectKind Kind;
    int Harmonic;
};

struct AspectRestrictions
{
    bool Rest;
    double Orb;
    int Color, Influence;
};

extern const struct AspectsConstants*  AspConstVector;
#define I enum Aspects i

/* The accuracy of an aspect
     Exact - Good: less than or equal 30% of the orb
     Medium      : less than of equal 60% of the orb
     Poor        : more than 60% of the orb
  */
enum AspectAccuracy { Exact, Good, Medium, Poor, Applying, Separating };

/* Aspect way: leftward, rightward or neutral for exact aspects */
enum AspectWay { LeftAspect, RightAspect, NeutralAspect };

enum AspFlags { IfSamePlanet = 1, Ha = 2, Hb = 4, MPa = 8, MPb = 16, Mutual = 32, Pta = 64, Ptb = 128, PMut = 256, Reverse = 512 };

typedef unsigned char asp;


typedef AstroTable<asp> ATable;

class _AstroAspects
{
public:

    friend class AspectFound;
    friend class AstroFoundAspectsBase;

    _AstroAspects(const _AstroRestrictions* ar);
    inline double operator * (I)   const {
        return AspConstVector[i].Angle;
    }
    inline enum AspectKind Kind(I) const {
        return AspConstVector[i].Kind;
    }
    inline int Harmonic(I)         const {
        return AspConstVector[i].Harmonic;
    }
    inline bool operator == (I)    const {
        return !Asprst[i].Rest;
    }
    inline double operator / (I)   const {
        return Asprst[i].Orb;
    }
    inline int Color(I)            const {
        return Asprst[i].Color;
    }
    inline int Influence(I)        const {
        return Asprst[i].Influence;
    }
    inline const struct Rest* GetRest() const {
            return Restr;
        }

    enum Aspects IsAspect(enum Objs oa, const Values& a,
                          enum Objs ob, const Values& b, int flags) const;

    enum Aspects IsAspect(float mp, enum Objs ob, const Values& b, int flags) const;

    void IsExtraAspect(enum Objs oa, const Values& a, enum Objs ob, const Values& b, int flags, float* results) const;

protected:

    struct Rest* Restr;
    struct AspectRestrictions* Asprst;
    double MPOrbSub;
    bool IsMinor;
};

/** This class manages the aspects data */
class AstroAspects : public _AstroAspects
{
public:

    AstroAspects(AstroRestrictions* ar);

    inline const AstroString& operator << (I) const
    {
        return *Asr->AspectNames[i];
    }
    inline const AstroString& operator  < (I) const
    {
        return *Asr->AspectShortNames[i];
    }
    char GetAspChar(I) const;

    /** Returns the Aspect if objs oa and ob are in the corresponding aspect.
    @param oa Object a
    @param ob Object b
    @param a AstroObjs a
    @param n AstroObjs b
    */
    enum Aspects IsAspect(enum Objs oa, const AstroObjs& a,
                          enum Objs ob, const AstroObjs& b, int flags) const;

    enum Aspects IsAspects(float mp, enum Objs ob, const AstroObjs& b, int flags) const;

    /** Returns possible extra aspects (parallels, antiscias)
    @param oa Object a
    @param ob Object b
    @param a AstroObjs a
    @param n AstroObjs b
    @param results a pointer to an array of 4 bools, for parallel, antiparallel, antiscias and contra-antiscias. true if aspect.
    */
    void IsExtraAspect(enum Objs oa, const AstroObjs& a,
                       enum Objs ob, const AstroObjs& b, int flags, float* results) const;

private:

    bool IsMinor;
    char *AspChars;
};

/** class provided by  AstroAspectsList
    It contains the values of a found aspect
    Angle_a, Angle_b: angles (in degrees) of the objs Oa and Ob.
    Strength: the power of the aspect (Positive number) */

class AspectFound
{
public:
    inline AspectFound(enum Aspects asp, enum Objs oa, enum Objs ob) {
        Asp = asp;
        Oa = oa;
        Ob = ob;
    }
    /** Constructors */
    AspectFound(const _AstroAspects& aa, enum Aspects asp, enum Objs oa, enum Objs oc, float mp, enum Objs ob, const Values& b, int flags);

    AspectFound(const _AstroAspects& aa, enum Aspects asp, enum Objs oa, const Values& a, enum Objs ob, const Values& b, int flags, float orb = -1.0);

    enum Aspects Asp; // Found aspect.
    enum Objs Oa, Ob, Oc; // Involved objects, If Oc != Undefined_Obj, aspect between midpoint Oa/oc and Ob.

    double Angle_a, Angle_b, Orb, ExtraOrb; // Angles of involved objects + actual orb + extraorb for parallels and antisces.

    /** Returns the accuracy of the aspect
      @return AspectAccuracy
    */
    enum AspectAccuracy GetAccuracy() const;

    /** Returns the influence (power) of an aspect */
    int GetInfluence() const;

    /** return true if Midpoint */
    inline bool IFMp() const {
        return Oc != Undefined_Obj ? true : false;
    }

    /** Returns true if aspect to Arabic part */
    inline bool IFpart() const {
        return Ifp;
    }

    // If an aspect is exact, applying or separating
    enum AspectAccuracy AspectSide;

    enum AspectWay AspWay;

private:

    bool Ifp;
    void GetSide(float v1, float v2, int flags);

    _AstroAspects* Aa; // Aspects table pointer.
};
#include <cstdio>
CONST inline bool AspectFoundSort(const AspectFound* a, const AspectFound* b)
{
    return a->GetInfluence() > b->GetInfluence();
}

typedef AstroList<AspectFound> AlAf;

class AstroFoundAspectsBase
{
public:

    /** Constructor */
    AstroFoundAspectsBase() {
        Max_x = Max_y = Sun;
        Amp = 0;
        Flags = 0;
        Tp = 0;
        NbParts = 0;
    }

    /** Destructor */
    virtual ~AstroFoundAspectsBase();

    /** Sets the arabic part table */
    inline void SetParts(struct ThePart* tp, int nbparts) {
        Tp = tp;
        NbParts = nbparts;
        Flags |= Pta;
    }

    /** Returns the AstroMidpoint pointer */
    const AstroMidPoints* GetAmp() const {
        return Amp;
    }

    /** Returns the maximum ojects indexes */
    inline void GetBounds(int* max_x, int* max_y) const {
        *max_x = Max_x;
        *max_y = Max_y;
    }


    /** Computes aspects between a/b
    @param aa _AstroAspects table
    @param a values for a
    @param b values for b
    @param ifsameplanet if true, computes aspects between same planets if a and b
    @param mp if true computes midpoints (see mutual below), and aspects to midpoints
    */
    void GetAspects(const _AstroAspects& aa, const Values& a, const Values& b, const _AstroRestrictions& ar, const _AstroRestrictions& br, int flags);

    /** Same as above, but with AstroObjs */
    void GetAspects(const AstroAspects& aa, const AstroObjs& oa, const AstroObjs& ob, int flags);

    inline int GetFlags() const {
        return Flags;
    }

protected:

    void TestAspects(const _AstroAspects& aa, const Values& a, const Values& b,
                     const _AstroRestrictions& ar, const _AstroRestrictions& br);

    void TestAspects(const _AstroAspects& aa, const Values& b, const _AstroRestrictions& ar, const _AstroRestrictions& br, bool parts = false);

    virtual void Reset(const _AstroRestrictions& br) = 0;

    virtual void PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                           const Values& a, enum Objs ob, const Values& b, float orb = -1.0) = 0;

    virtual void PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                           enum Objs oc, float mp, enum Objs ob, const Values& b) = 0;

    virtual bool Already(enum Objs oa, enum Objs ob, enum Aspects a = Unknown_Aspect) const = 0;

    int Flags, NbParts;
    enum Objs Max_x, Max_y;
    AstroMidPoints* Amp;
    struct ThePart* Tp;
};

/** This class is the base class for the aspects computing. It only maintains
	a table of found aspects */
class AstroFoundAspectsTable:  public AstroFoundAspectsBase, public ATable
{
public:

    /** constructor */
    AstroFoundAspectsTable() {}

    /** destructor */
    virtual ~AstroFoundAspectsTable();

    /** Recomputes aspects without having to recompute the midpoints */
    void RegetAspects(const _AstroAspects& aa, const Values& a, const Values& b, const _AstroRestrictions& ar, const _AstroRestrictions& br, int flags);

    /** Return the reference to table of aspects midpoints/object i,  */
    inline const ATable& operator [] (int i) const {
        return Tbl[i];
    }

    /** Returns a reference to PTbl */
    inline const ATable& operator !() const {
        return PTbl;
    }


private:

    void Reset(const _AstroRestrictions& br);

    void PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                   const Values& a, enum Objs ob, const Values& b, float orb = -1.0);

    void PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                   enum Objs oc, float mp, enum Objs ob, const Values& b);

    inline bool Already(enum Objs oa, enum Objs ob, enum Aspects a = Unknown_Aspect) const {
        return Get(oa, ob) == a;
    }

    void Clean();

    ATable Tbl[Last_Star + 1], PTbl;
    // Doesn't work !
    //AstroTable<ATable> Tbl;
};

/** This class maintains a list of found aspects between AstroObjs a and b */
class AstroFoundAspectsList: public AstroFoundAspectsBase, public AlAf
{
public:

    /** Constructor */
    AstroFoundAspectsList() {}

    /** Destructor */
    ~AstroFoundAspectsList();

    /** Constructor.
     @param a ref to first objects set
     @param b ref to second objects set
     @param ifsameplanet If true regard the possible aspects between the same planet, (e.g. Venus in both a and b)
       @param mp if true, also compute midpoints */
    AstroFoundAspectsList(const AstroAspects& aa, const AstroObjs& a, const AstroObjs& b, int flags);

    /** Search for a given aspect according to following parameters :
    @param o1 an aspect with obj o1. if Undefined_Obj, any obj
    @param asp 2 objs with aspect asp. If Unknown_Aspect, any aspect
    @param o2 an aspect with obj o2. if Undefined_Obj, any obj
    @param af starts the search from af. If 0, from the first aspect
    @param next if true, starts with the next item after af
      @param mp if true, search for midpoint o1/o3 and o2
      @param o3 an aspect with obj o1. if Undefined_Obj, any obj
    @return pointer to matching aspect, 0 if none.*/

    const AspectFound* Search(enum Objs o1 = Undefined_Obj, enum Aspects asp = Unknown_Aspect, enum Objs o2 = Undefined_Obj, const AspectFound* af = 0, bool next = false, bool mp = false, enum Objs o3 = Undefined_Obj) const;

    /** Sorts all the aspects lists */
    inline void SortAspects() {
        Sort(AspectFoundSort);
        AspMP.Sort(AspectFoundSort);
    }

    /** Return the reference to the list of aspects midpoints/objs */
    inline AlAf& operator~ () {
        return AspMP;
    }

private:

    void Reset(const _AstroRestrictions& br);

    void PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                   const Values& a, enum Objs ob, const Values& b, float orb = -1.0);

    void PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                   enum Objs oc, float mp, enum Objs ob, const Values& b);

    bool Already(enum Objs oa, enum Objs ob, enum Aspects a = Unknown_Aspect) const;

    AlAf AspMP;
};

#endif
