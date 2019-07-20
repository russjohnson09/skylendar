/***************************************************************************
                          astrodata.cpp  -  description
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

#include "astrosql.h"
#include "astrodata.h"
#include "astroresources.h"
#include "editastrodata.h"
#include "astrowindow.h"
#include "astroprocess.h"
#include "tz.h"

#ifdef QT
#include <QTimer>
#include <QSqlError>
#endif
#include <cstdlib>

AstroData::AstroData(AstroInterface* aif) : AstroDate(aif)
{
    Gender = Neutral;
    ChartType = 1;
    PlaceIdx = CountryIdx = 1;
    Latitude = Longitude = Altitude = 0.0;
}

AstroData::AstroData(const AstroDate& ad, Index countryidx, enum Gender gender, unsigned int charttype, const AstroString& name) : AstroDate(ad)
{
    Gender = gender;
    ChartType = charttype;
    Name = name;	
    DbPlaceFetch(countryidx);
}

Index AstroData::DbSave()
{
    char g;
    Index idx, saveidx;
    AstroString time, as, savename;
    if (Default)
    {
			Day = Month = 1;
			Year = 2000;
			Hm = 0.0;
			Name = "#" + Asr->DbUser;
    }
    switch (Gender)
    {
    case Male:
        g = 'M';
        break;
    case Female:
        g = 'F';
        break;
    case Neutral:
        g = 'N';
        break;
    default:
        g = 'S';
    };
    AstroRequest arq;
    Get(time, HM_Time, false, To_Second);
		if(arq.Exec("SELECT EXISTS(SELECT Idx FROM Data WHERE Idx = %d)", Idx) && arq.GetBool("exists", false))
			arq.Exec("UPDATE Data SET Name = '%a', BirthDay = TIMESTAMP '%a', BirthTime = '%a', Gender = '%c', ChartType = %d, TimeZone = %f, Dst = %f, PlaceIdx = %d, Keywords = '%a', Accuracy = %d, Preload = %b, Automatic = %b, ToSecond = %b, TrueSolarTime = %b WHERE Idx = %d", &Name, &SQLDate(as, false), &time, g, ChartType, GetOffset(), GetDaylight(), PlaceIdx, &Keywords, Accuracy, Preload, Automatic, To_Second, TrueSolarTime, Idx);
		else
		{
        idx = arq.NextId("Data");
        arq.Exec("INSERT INTO Data (Idx, Name, BirthDay, BirthTime, Gender, ChartType, Dst, TimeZone, PlaceIdx, Keywords, Accuracy, Preload, Automatic, ToSecond, TrueSolarTime) VALUES(%d, '%a', TIMESTAMP '%a', '%a', '%c', %d, %f, '%f', %d, '%a', %d, %b, %b, %b, %b)", idx, &Name, &SQLDate(as, false), &time, g, ChartType, GetDaylight(), GetOffset(), PlaceIdx, &Keywords, Accuracy, Preload, Automatic, To_Second, TrueSolarTime);
        Idx = idx;
    }	
    arq.SetComment(Comment, Idx);
    Modified = false;
    if (Default)
    {
        Name = i18n("Default Data");
        Now();
    }
		if(!arq.Effective()) AstroMessage(i18n("You probably don't have sufficient privileges to do that"));
    return Idx;
}

enum DateSystem AstroData::CheckDate(int day, int month, int year, int hour, int minute, int second)
{
    int offset;
    double j = Aif->Date_Conversion(day, month, year, RHM(hour, minute, second), IsGreg());
    return GuessDateSystem(j, offset);
}

bool AstroData::DbFetch(Index idx)
{
    char g;
    int h, m, s;
    double offset, daylight;
    AstroString as;
    AstroStringList asl;
    AstroRequest arq;
    if (!arq.Exec("SELECT EXTRACT(Day FROM Birthday) AS day, EXTRACT(Month FROM Birthday) AS month, EXTRACT(Year FROM Birthday) AS year, EXTRACT(Hour FROM BirthTime) AS hour, EXTRACT(Minute FROM BirthTime) AS minute, EXTRACT(Second FROM BirthTime) AS second FROM Data WHERE Idx = %d", idx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch birth date"));
        return false;
    }
    Day = arq.GetInt("day", 0);
    Month = arq.GetInt("month", 0);
    Year = arq.GetInt("year", 0);
    h = arq.GetInt("hour", 0);
    m = arq.GetInt("minute", 0);
    s = arq.GetInt("second", 0);

    if (!arq.Exec("SELECT * FROM Data WHERE Idx = %d", idx) || !arq.Valid())
    {
        AstroMessage(i18n("Can't fetch data record !"));
        return false;
    }
    Idx = arq.GetInt("Idx");
    Name = arq < "Name";
    Set(h, m, s);
    g = arq.GetChar("Gender");
    switch (g)
    {
    case 'M' :
        Gender = Male;
        break;
    case 'F' :
        Gender = Female;
        break;
    case 'N' :
        Gender = Neutral;
        break;
    default:
        Gender = Situation;
    };
    ChartType = arq.GetInt("ChartType");
    offset    = arq.GetDouble("TimeZone");
    daylight  = arq.GetDouble("Dst");
    SetOffDay(offset, daylight);
    Comment = arq < "Comment";
    PlaceIdx = arq.GetInt("PlaceIdx");
    Keywords = arq < "Keywords";
    Accuracy = arq.GetInt("Accuracy", 0);
    Preload  = arq.GetBool("Preload", false);
    Automatic = arq.GetBool("Automatic", false);
    To_Second = arq.GetBool("ToSecond", false);
    TrueSolarTime = arq.GetBool("TrueSolarTime", true);
    if (!DbPlaceFetch(PlaceIdx))
        return false;
    SetDate(Day, Month, Year, h, m, s);
    return Recompute();
}

bool AstroData::DbFetch(const AstroString& name)
{
    AstroRequest arq;
    if (!arq.Exec("SELECT Idx FROM Data WHERE Name = '%a'", &name) || !arq.Valid(true))
        return false;
    return DbFetch(arq.GetInt("Idx"));
}

bool AstroData::DbPlaceFetch(Index idx)
{
    AstroRequest arq;
    if (!arq.Exec("SELECT * FROM Place WHERE Idx = %d", idx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch place record !"));
        return false;
    }
    PlaceName = arq < "Name";
    Latitude = arq.GetDouble("Latitude");
    Longitude  = arq.GetDouble("Longitude");
    Altitude   = arq.GetDouble("Altitude");
    CountryIdx = arq.GetInt("CountryIdx");
    GetCountryName();
    return DbExtraFetch(arq, idx);
}

bool AstroData::DbExtraFetch(AstroRequest& arq, Index idx)
{
    int j = 0;
    char buf[BUFSIZE];
    arq.Clear();
    if (!arq.Exec("SELECT TzFile, EXTRACT(Day FROM J2g) AS day, EXTRACT(Month FROM J2g) AS month, EXTRACT(Year FROM J2g) AS year FROM Country WHERE Idx = %d", CountryIdx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch database record !"));
        return false;
    }
    (arq < "TzFile").Data(buf);
    SetTZ(buf);
    SetJ2g(arq.GetInt("day", 4), arq.GetInt("month", 10), arq.GetInt("year", 1582));
    arq.Clear();
    for (int i = 0; i < 3; i++) Corr1901[i].julday = MINCORR;
    if (!arq.Exec("SELECT EXTRACT(Day FROM Date) AS Day, EXTRACT(Month FROM Date) AS Month, EXTRACT(Year FROM Date) AS Year, Seconds FROM D1901 WHERE Idx = %d ORDER BY Date ASC", CountryIdx))
    {
        AstroMessage(i18n("Can't Access Table D1901"));
        return false;
    }
    if (arq.Valid())
        do
        {
            Corr1901[j].julday = Aif->Date_Conversion(arq.GetInt("Day", 0), arq.GetInt("Month", 0), arq.GetInt("Year", 0), 0.0, true);
            Corr1901[j].seconds = arq.GetInt("Seconds", 0);
        }
        while (arq.Next() && j++ < 4);
    return true;
}
void AstroData::GetCountryName()
{
    AstroRequest arq;
    if (!arq.Exec("SELECT Name FROM Country WHERE Idx = %d", CountryIdx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't find country record !"));
        return;
    }
    CountryName = arq < "Name";
}

bool AstroData::Edit()
{
    EditAstroData ead(*this);
#ifdef QT
    return ead.exec() ==  QDialog::Accepted;
#endif
}

bool AstroData::FetchZoneInfoFile(char *c, Index countryidx)
{
    AstroRequest arq;
    if (!arq.Exec("SELECT TzFile FROM Place WHERE Idx = %d", countryidx) || !arq.Valid())
    {
        AstroMessage(i18n("Can't fetch place record !"));
        return false;
    }
    (arq < "TZFile").Data(c);
    return true;
}

Index AstroData::FetchCountryIdx(const char *c)
{
    AstroRequest arq;
    if (!arq.Exec("SELECT Idx FROM Country WHERE Name = '%s'", c) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch country index !"));
        return 0;
    }
    return arq.GetInt("Idx");
}

double AstroData::GetSidTime() const
{
    double x = AstroDate::GetSidTime(), l = Longitude.Get(true);
    int h, m, s;
    if (l < 0.0) l += 360.0;
    l *= (24.0 * 3600.0) / 360.0;
    s = int(l);
    m = s / 60;
    s %= 60;
    h = m / 60;
    m %= 60;
    x += DegToDec(h + m / 100.0 + s / 10000.0);
    if (x < 0.0) x += 24.0;
    if (x >= 23.999722) x -= 24.00;
    return DecToDeg(x);
}

AstroDataList::AstroDataList()
{
    AstroRequest arq;
    AstroData* ad;
    Max = BOUND;
    auto an = new AstroNow();
    Append(an);
    Now = an;
    if (arq.Exec("SELECT Idx FROM Data WHERE Preload = 't'") && arq.Valid())
        do
        {
            ad = new AstroData;
            if(!ad->DbFetch(arq.GetInt("Idx"))) return;
            AddData(ad);
        }
        while (arq.Next());
}

void AstroDataList::UpdatePlace(const AstroData& a)
{
    AstroData* ad;
    foreach(*this, AstroDataList)
    {
        ad = (*it);
        if (ad->PlaceIdx == a.PlaceIdx)
        {
            ad->Latitude = a.Latitude;
            ad->Longitude = a.Longitude;
            ad->HMS_Format = a.HMS_Format;
            ad->CountryIdx = a.CountryIdx;
            ad->Recompute();
        }
    }
}

void AstroDataList::AddData(AstroData* ad)
{
    if (ad->Idx == 0)
        ad->Idx = ++Max;
    Append(ad);
}

AstroData* AstroDataList::Get(Index idx) const
{
    foreachc(*this, AstroDataList)
    if ((!it)->Idx == idx)
        return CSC(AstroData*, !it);
    return 0;
}

bool AstroDataList::CheckIdx(Index idx, bool country) const
{
    foreachc(*this, AstroDataList)
    if (country ? (!it)->CountryIdx : (!it)->PlaceIdx == idx)
        return true;
    return false;
}

bool AstroDataList::RemoveFromDb(Index idx)
{
    AstroRequest arq;
    AstroString as;
    //Remove(Get(idx));
    if (idx >= BOUND)
        return true;
    if (!arq.Exec("DELETE FROM Data WHERE Idx = %d", idx))
        AstroMessage(i18n("Problem in data deletion"));
    as = Asq->Error();
    if (!as.isEmpty() && as != " ")
    {
        AstroMessage(as);
        return false;
    }
    Remove(Get(idx));
    return true;
}

AstroNow::AstroNow()
{
	AstroRequest arq;
	AstroString as = "#" + Asr->DbUser;
	Default = true;
	if (arq.Exec("SELECT Idx FROM Data WHERE Name = '%a'", &as) && arq.Valid())
		DbFetch(arq.GetInt("Idx", 1));
	else
	{
		DbSave();
		DbPlaceFetch(PlaceIdx);
	}
	Name = i18n("Now");
    Gender = Neutral;
    ChartType = 0;
    Modified = true;
    Now();
#ifdef QT
    Timer = new QTimer;
    connect(Timer, SIGNAL(timeout()), this, SLOT(Done()));
    Timer->start(1000);
#endif
}

void AstroNow::Done()
{
    Now();
}

AstroNow::~AstroNow()
{
#ifdef QT
    Timer->stop();
    delete Timer;
#endif
}

double AstroData::ComputeLocalTime(double julday, double& e) const
{
    int h, m, s;
    e = Aif->Local2Mean(julday);
    Longitude.HMConvert(&h, &m, &s);
    if (e == MAX_DOUBLE) return MINCORR;
    return h + m / 100.0 + s / 10000.0;

}
