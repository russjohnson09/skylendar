/***************************************************************************
                          astroprocess.h  -  description
                             -------------------
    begin                : Fri May 11 2001
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

#ifndef ASTROPROCESS_H
#define ASTROPROCESS_H

#define SKYSERVICE_VERSION 4.0

#include "../config.h"
#include "astrodefs.h"
#include "astrotransfer.h"
#include <cmath>
#include <ctime>
#define QT
#ifdef QT
#include <QtDBus/QtDBus>
#include <QObject>
#include <QString>
class AstroComputing;
class OrgSkylendarScanclientInterface;
#endif

#define MAX_DOUBLE 1.0E09

#define CONVERSE 1

class AstroInterface;
class _AstroRestrictions;
class Values;
class AstroComputing;
class AspScanList;
class ScanInterface;
class AstroChart;
class DirEngine;

class ComputeSubChart
{
public:

    ComputeSubChart(AstroComputing* ac) {
        Ac = ac;
    }
    virtual ~ComputeSubChart() {}
    virtual bool Compute(const DataComp& dc) const;

protected:

    Values& V(int i) const;
    const _AstroRestrictions& Ar(int i) const;
    void Direct(int i, const Values& vf, Values& vi, double armc, int ring, double ecl) const;
    AstroComputing* Ac;
};

class ComputeSubChartList
{
public:

    ComputeSubChartList();
    void Init(AstroComputing* ac);
    ~ComputeSubChartList();

    const ComputeSubChart* Get(int i) const {
        return Cscl[i];
    }

private:

    ComputeSubChart* Cscl[Last_SubType];
};

#ifdef QT

/** The computing class itself */
class AstroComputing: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.skylendar.skyservice")

public:

    friend class ComputeSubChart;

    /** Constructor */
    AstroComputing(QObject* parent);

    /** Destructor */
    ~AstroComputing();

    inline void SetSerr(const char* c) {
        strncpy(serr, c, 256);
    }

public Q_SLOTS:

    /** Gets the current version of this service */
    double GetVersion();

    /** Initialize some extra data */
    void SetExtraData(bool utc, QString swepaths, double temp, double press, uchar humid, int nbstars, QByteArray eit, QByteArray sti);

    /** Performs swe_date_conversion. If wrong returns MAX_DOUBLE + corrected julday */
    double Date_Conversion(unsigned char day, unsigned char month, short year, double utime, bool greg);

    /** Convert from local apparent to local mean time
    @return e. If return == MAX_DOUBLE, an error occured */
    double Local2Mean(double j);

    /** Returns the current obliquity */
    double GetObliquity(double julday);

    /** Returns a DateTime from the given julain day */

    QByteArray DBusRevJul(double jd, bool greg);

    /** returns a Double3 from Double3 gepos, xin */
    QByteArray DBusAzalt(double jd, int flags, QByteArray geopos, QByteArray xin);

		/** returns a QPolygonF from Double3 gepos, QPolygonF xin */
    QByteArray DBusAzaltP(double jd, int flags, QByteArray geopos, QByteArray xin);

    /** Converts the given longitude and latitude into rectascension and declination in a Double3
       	 @param ecl the value of the ecliptic
       	 @return and D3 with ra as d1 and decl as d2
    */
    QByteArray DBusConvert(double lon, double lat, double ecl);

    /** Gets the name of the ith object */
    QString DBusGetPlaName(int i);

    /** Gets the magnitude of a star */
    double GetMagnitude(int i);

    /** Returns Sidereal time from julday*/
    double SidTime(double jd);

    /** Return the day of week from jd */
    int Day_of_Week(double jd);

    /** Sets all the AstroRestrictions to art
    @param art The _AstroRestrictions transfert object */
    void InitRestricts(QByteArray art);

    /** Sets the _AstroRestrictions i to art content */
    void SetRestrict(QByteArray art, int i);

    /** Sets the XPoint values (longiture, latitude, distance in UA) for ring 'ring'*/
    void SetXPoint(double angle, double lat, double dist, int ring);

    /** Recomputes the objects values and puts results into slot i
    @param dct the DataComp object
    @return true if OK
    */
    bool Recompute(QByteArray dct);

    /** Retrieves the values from the slot slot
    @param slot the slot number 0..NBDATA
    @return The VTransfer values transfer object */
    QByteArray GetValues(int slot) const;

    QString DBusGetError();

    /** Kills the current process */
    void Kill();


    /** Scan all the aspects until julday
       @param dct DataComp */
    Q_NOREPLY void ScanAsp(QByteArray dct, double origjd, QString scserver, bool dual, bool mp, bool tosecond, bool ap);

    /** Scan all the primary directions up to the given year */
    Q_NOREPLY void ScanDir(int first, int second, QString scserver, uchar house, uchar dirtype, uchar statkey, double dval, int flags);

    /** Stops at once Aspects scan */
    Q_NOREPLY void StopScan();

    /** Gets Rise/Set of the current obj */
    double GetRiseSet(double julday, int index, double latitude, double longitude, double altitude, int ca);

    /** Computes the next or previous total eclipse parameters
       @param julday, the julian start date
       @param direction true if forward, false if backward
       @param flags computing flags
       @return status
    */
    int ComputeGlobEclipse(double julday, int flags, bool direction, bool lunar);

    /** Computes the next or previous local eclipse
    	@param julday, the julian start date
    	@param direction true if forward, false if backward
    	@param flags computing flags
    	@param latitude local latitude
    	@param longitude local longitude
    	@param lunar if true return lunar eclipse
    	@return status
    	*/

    int ComputeLocEclipse(double julday, int flags, double latitude, double longitude, double altitude, bool direction);

    /** Computes the position of the next/previous eclipse
    @param julday the julday exact date and time
    @param flags computing flags
    @return status
    */
    int ComputeEclPos(double julday, int flags);

    /** Computes the next/previous lunar occultation of obj i by moon
    @param julday the julday start
    @param i the ith objects
    @param flags ephem flags
    @param latitude, longitude, altitude observer's position
    @param direction false = backward, otherwise forward
    @param local local occult is true, otherwise global
    @return status
    */
    int LunarOccult(double julday, int i, int flags, double latitude, double longitude, double altitude, bool direction, bool local);

    /** Return the ith eclipse data value
    @param i 0 >= i <= 9
    @returnith value
    */
    double GetEclipseValue(int i);

    /** Gets Apsides
     @return Apsides
    */
    QByteArray DBusGetApsides(double julday, int index, int flags, int method);

    /** Returns the sun step for the given julday */
    double GetSunStep(double jd);

    /** Returns true if parts adat have been loaded */
    bool IfParts();

    /** Loads the parts data into skyservice */
    bool LoadParts(QByteArray dbv, int size);

    /** Return the position of the given planet in Gauquelin's sectors */
    double Gauquelin(double julday, double geolat, double latitude, double longitude);

    QByteArray GetHousePos(int slot);

    /** Compute heliacal events
    @param julday start date of the search
    @param geopos Double3 with longitude, latitude and altitude
    @param id the objectŝ number, i.e. 0 = Sun, 1 = Moon etc...
    @param type RISING/SETTINGS, etc...
    @return Double3 containing start visibility, optimum visibility and end of visibility
    */
    QByteArray DBusHeliacal(double juday, QByteArray geopos, int id, int type);

#endif

public:

    DataComp Dc[NBDATA];

private:

    time_t tt;
    char tzsave[80];
    mutable char serr[256];
		AstroString SWEPaths;
    bool IfScan;
    _AstroRestrictions* Ar[NBDATA];
    Values V[NBDATA];
    DateTime Dt;
    Double3 D3;
    struct Apsides Ap;
    ComputeSubChartList Cscl;
		int Sti[NBSTARS];
    //struct srt Srt[Last_Star + 1];
    bool _Compute(const DataComp&);
    bool Compute(const DataComp&);
    void TestAsp(const _AstroAspects& aa, const AstroFoundAspectsTable& afat1,
                 const AstroFoundAspectsTable& afat2, const Values& v1, const Values& v2,
                 double j1, double j2, const DataComp& dc, bool dual, bool mp, bool tosecond, bool ap);
    void Pass();
    bool Utc(DataComp& dc) const;
    void GetMax(const _AstroRestrictions& ar);
    void SearchDir(int i, const _AstroRestrictions& ar1);
    void SearchDir(int i, int j, const _AstroRestrictions& ar1);
    /** Compute the objects' poles and oblique ascension from slot slot
    @param slot the slot
    @param latitude, if latitude */
    bool GetOaPole(int slot, bool latitude);
    double EclData[20], Ecl;
    int NbParts, Max, NbStars;
    struct ThePart* Parts;
    bool UTC;
    mutable double aux;
    OrgSkylendarScanclientInterface* Sci;
    _AstroAspects* Aa;
    DirEngine* Dir;
		float Temperature, Pressure;
		uchar Humidity;
};

#endif
