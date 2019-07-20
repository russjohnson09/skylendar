/***************************************************************************
                          astroobjs.h  -  description
                             -------------------
    begin                : Sat Sep 23 2000
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

#ifndef ASTROOBJS_H
#define ASTROOBJS_H

#include "astrodata.h"
#include "astrorestrictions.h"
#include "astrointerface.h"
#include "astrosigns.h"

class AstroColor;
class AstroChart;
class AstroChartBase;
class AstroConstellations;

/**This class is the basic class which can, from the AstroData data,
compute the objects (planets, stars, etc...) parameters
  *@author Christophe Gros
  */

class AstroObjs : public AstroData, public ChartParams
{

	Q_DECLARE_TR_FUNCTIONS(AstroObjs)

public:

    friend class AstroSubChart;
    friend class AstroAspects;
    friend class AstroFoundAspectsBase;
    friend class AstroFoundAspectsList;
    friend class AstroMidPoints;

    struct PlanetRank {
        enum Objs planet;
        int score;
    };

    /** Constructor */
    AstroObjs(AstroInterface *aif = 0);

    /** Constructor */
    AstroObjs(AstroInterface *aif, AstroChart *ac, int ring = 0);

    /** Constructor */
    AstroObjs(const AstroData& ad, AstroChart* ac, int ring = 0, enum ChartSubType cst = Single);

    /** Destructor */
    virtual ~AstroObjs();

    // If the AstroObjs is shown or not
    bool Show = true;

    /** These methods and ops are simply the ones from Ad */
    inline bool operator==(int i) const
    {
        return *Ar == i && (Accuracy < 0 ? (i != Fortune && i != Vertex && i != East_Point) : true) && Vals.Get(i) != NOVALUE;
    }

    inline bool IfHouses()        const {
        return Ar->IfHouses() && Accuracy > -1;
    }
    inline bool IfExtra()        const {
        return Ar->IfExtra();
    }
    inline bool IfStars()         const {
        return Ar->IfStars();
    }
    inline bool IfMinor()         const {
        return Ar->IfMinor();
    }
    inline int CountObjs()        const {
        return Ar->CountObjs();
    }

    /** Gets the ecliptical longitude of the object index */
    inline double operator * (int index) const {
        return Vals.Get(index);
    }

    /** Returns the 6 values array for th ith object */
    inline const DataValues* operator[](int index) const
    {
        return *Ar == index ? &Vals[index] : 0;
    }

    inline const DataValues& GetXPoint() const {
        return Vals[XPoint];
    }

    void SetSubChart(enum ChartSubType cst);
    inline enum ChartSubType GetSubType() const {
        return Cst;
    }

    inline enum ChartSubType operator-() const {
        return Cst;
    }

    /** Returns the long name of the corresponding subchart */
    const AstroString& GetSubTypeName() const;

    /** Returns the short name of the corresponding subchart */
    const AstroString& GetSubTypeShortName() const;

    /** Sets the restrictions group */
    void SetRestrict(AstroRestrictions* ar);

    /** Returns a constant pointer to current AstroRestrictions */
    inline const AstroRestrictions& operator ()() const {
        return *Ar;
    }

		inline AstroRestrictions* operator~() const {
			return Ar;
		}

    /** Returns the current AstroChartBase, if any */
    AstroChartBase* GetAcb() const;

    /** Returns the string value of the objet index, i.e. "12Cap45 R"
    @param index, the object's index
    @param as The returned string
    @return true if ok
    */
    bool GetValStr(int index, AstroString& as) const;

    /** Returns the reference to a static AstroString
      containing the text value (a.k.a "12Cap45")
      of the given object index */
    const AstroString& operator % (int index) const;

    /** Returns the object name */
    inline const AstroString& operator << (int index) const {
        return ObjName(index);
    }

    /** Returns the short name of the corresponding object */
    inline const AstroString& operator < (int index) const {
        return ObjShortName(index);
    }

    const DataComp& GetDataComp() const {
        return Dc;
    }

    /** Just compute the data */
    bool Compute();

    /** Compute the data and return its values */
    bool Recompute();

    /** Returns the given object's element */
    enum Elements GetObjElement(int index) const;

    /** Returns the object's color */
    const AstroColor& GetObjColor(int index) const;

    /** Returns the character for the corresponding object glyph, otherwise 0 */
    char GetObjChar(int index) const;

    /** Counts the number of objects in fire/air/water/earth triplicity */
    void CountFAWE(int* fire, int* air, int* water, int* earth) const;

    /**Counts the number of objects in cardinal/fixed/mutable quadruplicity */
    void CountCfm(int *cardinal, int *fixed, int *mutab) const;

    /**Counts the number of objects in angular/succeedent/cadent quadruplicity */
    void CountAsc(int *angular, int *succeedent, int *cadent) const;

    /** Returns the number of the house where the object index dwells in */
    int InHouse(int index, double *f = 0) const;

    /** Puts obj in house
    @param index obj index
    @param house house number
    @param f in-house position in 1/1000.0
    */
    void PutInHouse(int index, int house, double f);

    /** Returns the ring's index */
    inline int GetRing() const {
        return Ring;
    }

    /** Returns the master of the given object o
    @param o object id
    @param co_ruler if true, gives co-ruler instaed of ruler
    @return master (ruler) of o
    */
    enum Objs MasterOf(enum Objs o, bool co_ruler = false) const;

    /** Computes the planets ranks if aspects between current planets
    @return if false, can't compute */
    bool GetPlanetsRank(AstroFoundAspectsList* afal);

    /** returns object rise or set */
    double GetRiseSet(enum Objs o, enum ConjAngles ca = Rising) const;

    inline const struct PlanetRank* operator / (int i) const {
            return (i >= 0 && i < 10 && IfRank) ? &Rank[i] : 0;
        }

    /** Gets the computing mode */
    inline enum CompModes GetCms() const {
        return Cms;
    }

    /** Sets the computing mode */
    void SetCms(enum CompModes cms);

    /** Returns the index of the object's Sabian degree */
    int SabianDegree(enum Objs o) const;

    /** Returns the current AstroChart */
    inline AstroChart* GetAstroChart() const {
        return Ac;
    }

    /** Gets the current planetary hour */
    enum Objs GetPlaHour() const;

    /** Returns the value of the ith arabic part */
    double Part(int i) const;

    /** Returns the subchart state Master, slave, etc... */
    enum SubTypeState GetState() const;

    /** Returns true if Southern birth, i.e. negative ecliptical latitudes */
    inline bool IsSouthern() const {
        return Ar->Southern && Vals.Southern;
    }

    inline const struct Ruling& GetRulers(enum Signs s) const
        {
            return Asg->GetRulers(s, IsSouthern());
        }

    inline void GetRuled(struct RuledSigns& r, enum Objs o) const
    {
        Asg->GetRuled(r, o, IsSouthern());
    }

		/** Returns Ref to boundaries table */
		inline AstroConstellations* GetAct() const { return Act; }

		/** Compute the boundaries for local horizon */
		void SetConstel(bool b);

    /** Return the planet governing the term of o */
    enum Objs GetTerm(enum Objs o) const;

    /** Return the planet ruling the decan where planet o dwells in */
    enum Objs GetDecan(enum Objs o) const;

    /** Returns ID.a unique identifier */
    inline int GetID() const { return ID;}

    // Angle value for AddAngle or MulAngle
    double Angle = 0.0;

    // Default swe flags
    int DefSweFlags = SEFLG_SPEED;

    /** If references the alternative fist */
    bool ARef = false;

    bool XPDec = false;

private:

		//void Init();
    AstroChart* Ac = nullptr;
    int Ring = 0, ID;
    enum ChartSubType Cst = Single;
    enum CompModes Cms = Ecliptical;
    AstroRestrictions* Ar = Drs;
    DataComp Dc;
    bool IfRank = false, IfConstell = false;		/** if compute boundaries */
    mutable bool IfParts;
    // Ranked planets
    struct PlanetRank Rank[10];
    mutable double CurrJd = -1.0, CurrSunRise;


// The Zodiac longitudes array
    Values Vals;
		AstroConstellations* Act = nullptr;

    // The pointer of characters table for the astrofont glyphs

    char *PlaChars = CSC(char *, PLACHARS);

};

#endif

