/***************************************************************************
                          astrochartbase.h  -  description
                             -------------------
    begin                : Sat Oct 14 2000
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

#ifndef ASTROCHARTBASE_H
#define ASTROCHARTBASE_H

#include "astroobjs.h"
#include "astroaspects.h"
#include "astrotransfer.h"

#ifdef QT
# include <QObject>
class QWidget;
#endif

#define ACB (*Acb)
#define PMSET(i, n, b) Apm[i].Name = new AstroString(n); Apm[i].B = &cbp->b

typedef AstroObjs* ObjsVector[NBDATA];

class AstroGraphics;
class AstroFoundAspectsList;
class DataLineBase;
class EphemLine;
class AspConfList;
class AstroMidPoints;
class ScanClient;
class StopScan;
class AspScan;
class AstroDir;
class ScanclientAdaptor;
class AstroSpot;

/** This class provides additional params for the displayed charts,
    such as the as the AstroInterface pointer */

class ChartBaseParams : public ChartParams
{
public:

    inline ChartBaseParams(ChartParams* cp, AstroInterface* aif = Asf) : ChartParams(*cp)
    {
        Qw = 0L;
        Ag = 0L;
        Aif = aif;
        AFirst = 0;
    }

    AstroInterface* Aif;
    AstroGraphics*  Ag;
    AstroObjs* AFirst;
#ifdef QT
    QWidget*        Qw;
#endif
};


struct AstroPopupMenu
{
    inline void Set(const AstroString& name, bool* b) {
        Name = new AstroString(name);
        B = b;
    }
    AstroString* Name;
    bool* B;
};

/**This classs is the base class for all the charts
  *@author Christophe Gros
  */
class AstroChartBase : public QObject
{
    Q_OBJECT

public:

    friend class AstroChart;
    friend class AstroWindow;
    friend class AstroChartList;
    friend class AspScan;
    friend class AstroDir;
    friend class StopScan;
    friend void CloseServices();

    enum SearchType { SingleOnly, NonSingle, Any };

    // Types of graphic chart interactivity
    enum Interactivity { Inactive, Click, Buttons };

    // if true, the chart MUST have at least 2 AstroObjs available.
    bool DualChart = false;

    // If true, the aspects are computed
    bool IfAspects;

    // If true, this chart has its own title
    bool IfOwnTitle = false;

    /** Constructor */
    AstroChartBase(ChartBaseParams *cbp, ObjsVector* ov);

    /** Destructor */
    virtual ~AstroChartBase();

    /** Returns the ith AstroObjs pointer */
    inline AstroObjs* operator[](int i) const {
        return (*Ob)[i];
    }

    /** Returns the number of active AstroObjs */
    int Count() const;

    /** The abstract method that will redisplay the page 'page'
    	of the current chart */
    virtual bool Redisplay() = 0;

    /** Post recomputing routine */
    virtual inline bool PostRecompute() {
        return true;
    }

    /** Gives the chart's window title */
    const AstroString& GetTitle(AstroString& as) const;

    /** Sets this chart's own title */
    void SetOwnTitle(const AstroString &);

    /** Initialize First and Second AstroObjs */
    void GetFS();

    /** Return the referencing AstroObjs, actually First or AFirst */
    inline const AstroObjs& GetRef(bool afirst = false) const {
        return afirst ? *Cbp->AFirst : *First;
    }

    /** Says if the AstroObjs i is available */
    bool operator == (int i) const;

    /** Search for the i th ring having the conditions st and visible
        @param i the start ring (0..NBDATA)
        @param if Single only, non-single or any
        @param visible, visible  rings only
        @return the corresponding ring (0..NBDATA) )or -1
    */
    int Search(int r = 0, enum SearchType st = Any, bool visible = true) const;

    /** Returns an aspects list, if any */
    inline virtual const AstroFoundAspectsList* GetAspectsList() const {
        return nullptr;
    }

    /** Returns the AstroMidPoints table, 0 if not exists */
    inline virtual const AstroMidPoints* GetMidPoints() const {
        return nullptr;
    }

    /** void Compute Aspects Configurations
      @param acl reference to a list of AspConfData*/
    void CompAspConfig(AspConfList& acl) const;

    /** Returns the chart rx, ry coordinates corresponding to the x, y display positions */
    virtual inline void GetCoord(int x, int y, double* rx, double* ry) const {
        *rx = -1.0;
        *ry = -1.0;
    }

    /** Returns the corresponding AspData,(if any) for the clicked active line */
    virtual inline const DataLineBase* GetCoord(int x, int y) const {
        return nullptr;
    }

    /** If one active line contains more than one AspData, returns the ith following one*/
    virtual inline  const DataLineBase* GetNext(const DataLineBase* ref, unsigned int i) const {
        return nullptr;
    }

    virtual inline const EphemLine* GetEphemLine(int day, int month, int year) const {
        return nullptr;
    }

    /** Return the ith arabic part */
    virtual inline double GetPart(int i) const {
        return NOVALUE;
    }

    /** Returns the chart type */
    inline enum ChartType GetCt() const {
        return Ct;
    }

    /** Returns the chart draw mode */
    inline enum ChartMode GetCm() const {
        return Cm;
    }

    /** returns the chart interactivity */
    inline enum Interactivity GetIt() const {
        return It;
    }

    bool IfPage = false, Large = false;

    struct AstroPopupMenu* GetPm(int i) const {
            return (Apm && i >= 0 && i < NbPM) ? &Apm[i] : 0;
        }

    bool NoSpot = false;
    bool PlaceSpot(const AstroObjs& a, enum Objs o, int x, int y, int size, const AstroColor& ac);
    bool PlaceSpot(enum Signs s, int x, int y, int size, const AstroColor& ac);
    void HideAll();

    int NbPM = 0;

signals:

    void NewPage();

protected:

    enum ChartType Ct = Unknown_ChartType;
    enum ChartMode Cm;
    enum Interactivity It = Inactive;
    bool Running = false;
    AstroPopupMenu* Apm = nullptr;
    ChartBaseParams *Cbp;
    AstroString OwnTitle;
    AstroObjs *First, *Second;
		void Clean();
    /** Executed after any SetData
        @param i the index of the added AstroData
    */
    virtual void PostSetData(int i);

private:

    ObjsVector* Ob;
#ifdef QT
        QHash<int, AstroSpot*> Spots;
#endif
};

class EmptyChart : public AstroChartBase
{
public:

    inline EmptyChart(ChartBaseParams *cbp, ObjsVector* ov) : AstroChartBase(cbp, ov) {
        Ct = NullChart;
        Cm = TextMode;
        DualChart = false;
    }
    inline bool Redisplay() {
        return true;
    }
};

class TensorFlowChart : public AstroChartBase
{
public:
    friend class AstroGetValues;
    inline TensorFlowChart(ChartBaseParams *cbp, ObjsVector* ov) : AstroChartBase(cbp, ov) {
        Ct = TensorFlow;
        Cm = TextMode;
        DualChart = false;
    }
    inline bool Redisplay() { return true; }


    bool PostRecompute();

    inline const AstroFoundAspectsList* GetAspectsList() const {
        return &Afal;
    }

private:
    AstroFoundAspectsList Afal;
};

/** This class handles more complex chart, which can ask for parameters */
class ParamListBase : public DataLineList
{

public:

    friend class AstroMainWindow;

    ParamListBase() {
        Sci = nullptr;
        Ss = nullptr;
    }

    ParamListBase(AspScan* as);

    ParamListBase(AstroDir* ad);

    virtual ~ParamListBase();

    virtual inline bool EditParams() {
        return true;
    }

    const AstroString ScServer() const;

protected:

    StopScan* Ss;
    ScanClient* Sci;
    AspScan* As;
    AstroDir* Ad;
    ScanclientAdaptor* Sca;
    Index TblIdx;
    bool EditScSp(AspScanParams& asp, bool mp = false);
    void ShowSs(bool dual = false);
    void HideSs();
    virtual inline void Finish() {}
    void Progress(int i);
};
#endif
