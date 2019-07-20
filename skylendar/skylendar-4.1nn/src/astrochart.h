/***************************************************************************
                          astrochart.h  -  description
                             -------------------
    begin                : Mon Oct 16 2000
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

#ifndef ASTROCHART_H
#define ASTROCHART_H

#include "astrochartbase.h"
#include "astrodata.h"
#include "astrolist.h"

class AstroFoundAspectsList;

/**This class is the effective chart class.

  *@author Christophe Gros
  */

class AstroChart
{
	Q_DECLARE_TR_FUNCTIONS(AstroChart)

public:

    friend class AstroChartList;
    friend class AstroObjs;
    friend class SearchData;
    friend class AstroWindow;

    /** Constructor
     @param owninterface if true this chart has its own computing process
    */
    AstroChart(bool owninterface = true);

    /** Destructor */
    virtual ~AstroChart();

    /** Just returns a pointer to the wanted AstroObjs */
    inline AstroObjs* operator[] (int i) const {
        return (Acb && i >= 0 && i < NBDATA) ? Ov[i] : 0;
    }

    /** Sets the Chart Type */
    inline void SetCt(enum ChartType ct) {
        Ct = ct;
    }

    /** Gets the chart type */
    inline enum ChartType GetCt() const {
        return Acb ? Acb->GetCt() : Unknown_ChartType;
    }

    /** Locks the chart */
    inline virtual bool LockChart() {
        if (Acb->Running) return false;
        Acb->Running = true;
        return true;
    }

    /** Unlocks the chart */
    inline virtual void UnlockChart() {
        Acb->Running = false;
    }

    /** If chart locked */
    inline bool IfLocked() const {
        return Acb->Running;
    }

    /** This method displays the chart according to the Chart Type */
    virtual bool Display(bool redraw = true);

    /** Sets the subtype of the ith ring */
    bool SetSubType(ChartSubType cst, int i);

    /** Sets the data of the ith AstroObjs */
    virtual void SetData(AstroData*, int i, bool placeonly = false);

    /** Tests if ad is present in Ov. If true, return its index, otherwise -1 */
    int IfData(const AstroData* ad, bool placeonly = false) const;

    /** Says if ad is present in the AstroObjs set */
    virtual bool UpdateData(AstroData* ad, bool placeonly = false);

    /** update the zoneinfo file if CountryIdx = idx */
    bool UpdateZif(Index idx, const char* zif);

    /** Tests if ar is present in Ov. If true, return its index, otherwise -1 */
    int IfRestrict(const AstroRestrictions* ar) const;

    /** Sets the restriction data for the ith AstroObjs */
    void SetRestrict(AstroRestrictions* ar, int i);

    /** Says if ar is present in the AstroObjs set */
    bool UpdateRestrict(AstroRestrictions *ar);

    /** Edit the ChartParams and update all the  AstroObjs */
    bool EditChartParams();

    /** Returns computed chart's title */
    inline const AstroString& GetTitle(AstroString& as) const {
        return Acb ? Acb->GetTitle(as) : as;
    }

    /** Saves the chart into the database */
    bool Save();

    /** Sets the alternative first, i = ring*/
    void SetAFirst(int ring);

    /** Sets the altrnative referenced state, i = ring*/
    bool SetASecond(int ring);

    inline AstroChartBase* operator !() const {
        return Acb;
    }

    AstroChartBase *Acb = nullptr;

protected:

    /** Extracts and save AstroObjs id i
    @param i AstroObjs index (1..4)
    @param oldidx the object Idx before saving
    @param createnew if a new astrobj has been created
    @return actual (or saved) AstroObjs Idx
    */
    Index ExtractandSave(int i, Index& oldidx, bool& createnew, const AstroFoundAspectsList* afal = 0);

    virtual void Repaint(bool b = false);

    ChartBaseParams* Cbp;

    Index Idx = 0;

private:

// The current chart type
    enum ChartType Ct;

    ObjsVector Ov;

    /** This method creates an acb according to ct */
    void CreateChart(bool redraw);

    /** Shows/Hides the ith ring of the chart. Returns false if not successful */
    bool Show(int i);

    /** Gives the number of single rings */
    int NbSingle() const;

    virtual inline void PreRedraw(bool b) {}

    virtual inline void PostRedraw() {}
};

/** This class manages a linked list of AstroCharts */
class AstroChartList: public AstroList<AstroChart>
{
public:

    /** Constructor */
    inline AstroChartList() {}

    /** Changes the index for all the AstroObjs of all the AstroCharts
        if Index == oldidx
    */
    void ChangeIdx(Index oldidx, Index newidx);

    /** Modifies the data of all the AstroObjs of all the AstroCharts
        if index of ad == AstroObjs' inedx
        @param placeonly only modifies the place data
    */
    void UpdateData(AstroData* ad, bool placeonly = false);

    /** Changes the AstroRestrictions pointer of all the AstroObjs */
    void UpdateRestrict(AstroRestrictions* ar);

    /** Changes the zoneinfo filename for all the AstroObjs with Index idx */
    void UpdateZif(Index idx, const char* zif);

    /** Tells if AstroObjs with index idx is present in the list */
    bool CheckIdx(Index idx);

    /** Tells if AstroObjs'place with index idx is present in the list
        @param country, AstroObjs with country index idx only, instead of place */
    bool CheckPlaceIdx(Index idx, bool country = false);

    /** Loads the chart from the Database
    @param the chart idx
    @param An empty AstroChart
    */
    bool Load(Index idx, AstroChart& ac);

    /** Delete the corresponding chart into the database */
    void Delete(Index idx);
};
#endif
