/***************************************************************************
                          astrodata.h  -  description
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

#ifndef ASTRODATA_H
#define ASTRODATA_H

#include "astrodate.h"
#include "astrohm.h"
#include "astrostring.h"
#include "astrolist.h"
#include <qobject.h>

enum Gender { Male, Female, Neutral, Situation };
class QTimer;

/**This class is an extention of AstroDate,
an contains explicit time, place and name data.
  *@author Christophe Gros
  */

class AstroData : public AstroDate
{

	Q_DECLARE_TR_FUNCTIONS(AstroData)

public:

    friend class EditAstroData;

    /** Constructor */
    AstroData(AstroInterface* aif = Asf);

    /** Constructor */
    AstroData(const AstroDate& ad, Index countryidx = 1, enum Gender gender = Neutral, unsigned int charttype = 1, const AstroString& name = "");

    /** Destructor */
    virtual ~AstroData() {}

    /** The data and place names, + data comment */
    AstroString Name, PlaceName, CountryName, Comment, Keywords;

    /** If the Chart is for a male being, a female being or for a neutral thing or event, situation, etc ... */
    enum Gender Gender;

    /** Type of the chart: 0 = now, 1 = birth chart, 2 = death chart, etc...*/
    unsigned int ChartType;

    /** The current data, place and country indexes */
    Index Idx = 0, PlaceIdx, CountryIdx;

    /** if true, expressses the longitude in H:M:S */
    bool HMS_Format = false;

    /** Accuracy of time in minutes. If Accuracy == -1, Unknown time. Range 0..90, and the extract id */
    int Accuracy = 0, ExtractID = 0;

    /** if the data has been modified without having been saved */
    bool Modified = false;

    /** If preload dataset */
    bool Preload = false;

		/** If default dataset */
		bool Default = false;
    /** Where the latitude and longitude are stored */
    AstroHM Latitude, Longitude;

    double Altitude;

    /** Retrieves the chart data + place + country from the database
     * @param idx the data database index
     * @return true if found
     */
    bool DbFetch(Index idx);

    /** Retrieves the chart data + place + country from the database
     * @param name the data name
     * @return true if found
     */
    bool DbFetch(const AstroString& name);

    /** Access the database for retrieving the data place from the given name
    * @param idx the unique idx of the database record containing the wanted
    * data place
    * @return true if found
    */
    bool DbPlaceFetch(Index idx);

    bool DbExtraFetch(AstroRequest& arq, Index idx);

    /** Opens a dialog box for the data edition */
    bool Edit();

    /** Saves into the database, automatic selection of INSERT or UPDATE
     @param asdefault if true, save into Default Data
     @return the new or current row index
    */
    Index DbSave();

    /** Produces the zone info file for the given country index
        @param c the zone info filename buffer
        @param countryidx the country index
    */
    static bool FetchZoneInfoFile(char *c, Index countryidx);

    /** Returns the index of the given country name */
    static Index FetchCountryIdx(const char *c);

    /** Returns the local sidereal time in H.M format*/
    double GetSidTime() const;

    /** checks the validity of the given day, month, year and returns the calendat type
    @param day the day
    @param month the month
    @param year the year
    @param hour the hour
    @param minute the minute
    @return Julian, localhour, timezone or invalid
     */
    enum DateSystem CheckDate(int day, int month, int year, int hour, int minute, int second);

private:

    /** Initialize country name */
    void GetCountryName();
    double ComputeLocalTime(double julday, double& e) const;
};

/** This class manages a linked list of AstroData */
class AstroDataList: public AstroList<AstroData>
{

	Q_DECLARE_TR_FUNCTIONS(AstroDataList)

public:

    /** Constructor */
    AstroDataList();

    /** Adds am AstroData pointer */
    void AddData(AstroData*);

    /** Returns the pointer of an AstroData with a given Index */
    AstroData* Get(Index) const;

    /** Modifies all the place data whose the place index is the one from the
        given AstroData */
    void UpdatePlace(const AstroData&);

    /** Tells whether the AstroData of index idx is present into the list
        @param Country country or place
    */
    bool CheckIdx(Index idx, bool Country = false) const;

    /** Removes from database the dataset with index idx */
    bool RemoveFromDb(Index idx);

private:

    Index Max;
};

/** The specific AstroData giving the current time */
class AstroNow : public QObject, public AstroData
{
    Q_OBJECT

public:

    AstroNow();
    ~AstroNow();

private:

    QTimer* Timer;

private slots:

    void Done();
};
#endif
