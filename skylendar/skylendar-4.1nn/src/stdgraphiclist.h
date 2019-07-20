/***************************************************************************
                          stdgraphiclist.h  -  description
                             -------------------
    begin                : mer ao 21 2002
    copyright            : (C) 2002 by Christophe Gros
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

#ifndef STDGRAPHICLIST_H
#define STDGRAPHICLIST_H

#include <graphiclistbase.h>
#include "astroaspects.h"
#include "aspconflist.h"

/**This class manages a tabulated list
of values + aspects list
  *@author Christophe Gros
  */

class AstroAspectsFrame;
class AstroRequest;

class StdGraphicList : public GraphicListBase, public DataLineList
{

	Q_DECLARE_TR_FUNCTIONS(StdGraphicList)

public:

    /** Constructor */
    StdGraphicList(ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~StdGraphicList();

    /** Overloaded method */
    bool Redisplay();

    /** Overloaded method, actual ephemeris computation */
    bool PostRecompute();

    /** Return the aspects list */
    inline const AstroFoundAspectsList* GetAspectsList() const {
        return &Afal;
    }

    /** returns the ith midpoint, 0 if not */
    inline const AstroMidPoints* GetMidPoints() const {
        return Afal.GetAmp();
    }

private:

    struct Ecl
    {
        int r;
        AstroString err;
        double d[10];
    };

    struct Occult
    {
        int r;
        double d[4];
        inline double& operator[](int i) {
            return d[i];
        }
    };

    void DisplayAspects();
    void DispMidPoints(const AstroObjs& a, const AstroObjs& b, bool ifsameplanet);
    void DisplayValues(const AstroObjs&);
    void DisplayValues(const AstroString&, const struct DataValues&);
    void DisplayRiseSet(const AstroObjs&);
    void SaveRiseSet(AstroDate& ad, int, enum ConjAngles);
    void SaveEclipse(double julday, bool local, bool lunar, double latitude = 0.0, double longitude = 0.0);
    void SaveHeliacal(AstroDate& ad, int i, int j, enum AspKind ak);
    void SaveOccult(double julday, enum Objs o, bool local, double latitude, double longitude);
    void DisplayEclipses(const AstroObjs&);
    void DisplayGlobEclipse(const AstroObjs&, bool direction, bool lunar);
    void DisplayLocEclipse(const AstroObjs&, bool direction);
    void DisplayRank(const AstroObjs&);
    void DisplayAspectsConfiguration(const AstroObjs& a);
    void LoadSabian();
    void DisplaySabianDegrees(const AstroObjs& a);
    void DisplayApsides(const AstroObjs& a);
    void GetEcl(struct Ecl& e, bool glob, bool dir, bool lun) const;
    void GetOccult(bool back, bool local);
    void DisplayParts(const AstroObjs& a);
    void DisplayInterp(const AstroObjs& a);
    void DisplayInterpTransit();
    void DisplayHeliacal(const AstroObjs& a);
    void DisplayDecTerms(const AstroObjs& a);
    void DisplayGlobOcculations(const AstroObjs& a);
    const AstroString GetTextInterp(const AstroString& code, AstroRequest& req) const;
    const AstroString GetPl(enum Objs pl, bool ifhouse, int nb) const;
    const AstroString GetAsp(enum Objs p1, enum Objs p2, enum Aspects asp, bool transiting = false) const;

    AstroFoundAspectsList Afal;
    AspConfList Acl;
    int fl, fl1, R, R1;
    struct Ecl SolGlobEcl[2], LunGlobEcl[2], SolLocEcl[2];
    double ValRS[4][Last_Star], *PartsVals;
    Double3 HelRis[9], HelSet[9], EveFirst[3], MorLast[3];
    struct Occult *PrevGlobOccult, *NextGlobOccult;
    Apsides Aps[Last_Extra];
    AstroString	SabList[360];
};

#endif
