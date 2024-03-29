/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -m -a astroprocessadaptor -i astroprocess.h -l AstroComputing /skylendar/builds/ubuntu/src/astroprocess.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "astroprocessadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class SkyserviceAdaptor
 */

SkyserviceAdaptor::SkyserviceAdaptor(AstroComputing *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

SkyserviceAdaptor::~SkyserviceAdaptor()
{
    // destructor
}

int SkyserviceAdaptor::ComputeEclPos(double julday, int flags)
{
    // handle method call org.skylendar.skyservice.ComputeEclPos
    return parent()->ComputeEclPos(julday, flags);
}

int SkyserviceAdaptor::ComputeGlobEclipse(double julday, int flags, bool direction, bool lunar)
{
    // handle method call org.skylendar.skyservice.ComputeGlobEclipse
    return parent()->ComputeGlobEclipse(julday, flags, direction, lunar);
}

int SkyserviceAdaptor::ComputeLocEclipse(double julday, int flags, double latitude, double longitude, double altitude, bool direction)
{
    // handle method call org.skylendar.skyservice.ComputeLocEclipse
    return parent()->ComputeLocEclipse(julday, flags, latitude, longitude, altitude, direction);
}

QByteArray SkyserviceAdaptor::DBusAzalt(double jd, int flags, const QByteArray &geopos, const QByteArray &xin)
{
    // handle method call org.skylendar.skyservice.DBusAzalt
    return parent()->DBusAzalt(jd, flags, geopos, xin);
}

QByteArray SkyserviceAdaptor::DBusAzaltP(double jd, int flags, const QByteArray &geopos, const QByteArray &xin)
{
    // handle method call org.skylendar.skyservice.DBusAzaltP
    return parent()->DBusAzaltP(jd, flags, geopos, xin);
}

QByteArray SkyserviceAdaptor::DBusConvert(double lon, double lat, double ecl)
{
    // handle method call org.skylendar.skyservice.DBusConvert
    return parent()->DBusConvert(lon, lat, ecl);
}

QByteArray SkyserviceAdaptor::DBusGetApsides(double julday, int index, int flags, int method)
{
    // handle method call org.skylendar.skyservice.DBusGetApsides
    return parent()->DBusGetApsides(julday, index, flags, method);
}

QString SkyserviceAdaptor::DBusGetError()
{
    // handle method call org.skylendar.skyservice.DBusGetError
    return parent()->DBusGetError();
}

QString SkyserviceAdaptor::DBusGetPlaName(int i)
{
    // handle method call org.skylendar.skyservice.DBusGetPlaName
    return parent()->DBusGetPlaName(i);
}

QByteArray SkyserviceAdaptor::DBusHeliacal(double juday, const QByteArray &geopos, int id, int type)
{
    // handle method call org.skylendar.skyservice.DBusHeliacal
    return parent()->DBusHeliacal(juday, geopos, id, type);
}

QByteArray SkyserviceAdaptor::DBusRevJul(double jd, bool greg)
{
    // handle method call org.skylendar.skyservice.DBusRevJul
    return parent()->DBusRevJul(jd, greg);
}

double SkyserviceAdaptor::Date_Conversion(uchar day, uchar month, short year, double utime, bool greg)
{
    // handle method call org.skylendar.skyservice.Date_Conversion
    return parent()->Date_Conversion(day, month, year, utime, greg);
}

int SkyserviceAdaptor::Day_of_Week(double jd)
{
    // handle method call org.skylendar.skyservice.Day_of_Week
    return parent()->Day_of_Week(jd);
}

double SkyserviceAdaptor::Gauquelin(double julday, double geolat, double latitude, double longitude)
{
    // handle method call org.skylendar.skyservice.Gauquelin
    return parent()->Gauquelin(julday, geolat, latitude, longitude);
}

double SkyserviceAdaptor::GetEclipseValue(int i)
{
    // handle method call org.skylendar.skyservice.GetEclipseValue
    return parent()->GetEclipseValue(i);
}

QByteArray SkyserviceAdaptor::GetHousePos(int slot)
{
    // handle method call org.skylendar.skyservice.GetHousePos
    return parent()->GetHousePos(slot);
}

double SkyserviceAdaptor::GetMagnitude(int i)
{
    // handle method call org.skylendar.skyservice.GetMagnitude
    return parent()->GetMagnitude(i);
}

double SkyserviceAdaptor::GetObliquity(double julday)
{
    // handle method call org.skylendar.skyservice.GetObliquity
    return parent()->GetObliquity(julday);
}

double SkyserviceAdaptor::GetRiseSet(double julday, int index, double latitude, double longitude, double altitude, int ca)
{
    // handle method call org.skylendar.skyservice.GetRiseSet
    return parent()->GetRiseSet(julday, index, latitude, longitude, altitude, ca);
}

double SkyserviceAdaptor::GetSunStep(double jd)
{
    // handle method call org.skylendar.skyservice.GetSunStep
    return parent()->GetSunStep(jd);
}

QByteArray SkyserviceAdaptor::GetValues(int slot)
{
    // handle method call org.skylendar.skyservice.GetValues
    return parent()->GetValues(slot);
}

double SkyserviceAdaptor::GetVersion()
{
    // handle method call org.skylendar.skyservice.GetVersion
    return parent()->GetVersion();
}

bool SkyserviceAdaptor::IfParts()
{
    // handle method call org.skylendar.skyservice.IfParts
    return parent()->IfParts();
}

void SkyserviceAdaptor::InitRestricts(const QByteArray &art)
{
    // handle method call org.skylendar.skyservice.InitRestricts
    parent()->InitRestricts(art);
}

void SkyserviceAdaptor::Kill()
{
    // handle method call org.skylendar.skyservice.Kill
    parent()->Kill();
}

bool SkyserviceAdaptor::LoadParts(const QByteArray &dbv, int size)
{
    // handle method call org.skylendar.skyservice.LoadParts
    return parent()->LoadParts(dbv, size);
}

double SkyserviceAdaptor::Local2Mean(double j)
{
    // handle method call org.skylendar.skyservice.Local2Mean
    return parent()->Local2Mean(j);
}

int SkyserviceAdaptor::LunarOccult(double julday, int i, int flags, double latitude, double longitude, double altitude, bool direction, bool local)
{
    // handle method call org.skylendar.skyservice.LunarOccult
    return parent()->LunarOccult(julday, i, flags, latitude, longitude, altitude, direction, local);
}

bool SkyserviceAdaptor::Recompute(const QByteArray &dct)
{
    // handle method call org.skylendar.skyservice.Recompute
    return parent()->Recompute(dct);
}

void SkyserviceAdaptor::ScanAsp(const QByteArray &dct, double origjd, const QString &scserver, bool dual, bool mp, bool tosecond, bool ap)
{
    // handle method call org.skylendar.skyservice.ScanAsp
    parent()->ScanAsp(dct, origjd, scserver, dual, mp, tosecond, ap);
}

void SkyserviceAdaptor::ScanDir(int first, int second, const QString &scserver, uchar house, uchar dirtype, uchar statkey, double dval, int flags)
{
    // handle method call org.skylendar.skyservice.ScanDir
    parent()->ScanDir(first, second, scserver, house, dirtype, statkey, dval, flags);
}

void SkyserviceAdaptor::SetExtraData(bool utc, const QString &swepaths, double temp, double press, uchar humid, int nbstars, const QByteArray &eit, const QByteArray &sti)
{
    // handle method call org.skylendar.skyservice.SetExtraData
    parent()->SetExtraData(utc, swepaths, temp, press, humid, nbstars, eit, sti);
}

void SkyserviceAdaptor::SetRestrict(const QByteArray &art, int i)
{
    // handle method call org.skylendar.skyservice.SetRestrict
    parent()->SetRestrict(art, i);
}

void SkyserviceAdaptor::SetXPoint(double angle, double lat, double dist, int ring)
{
    // handle method call org.skylendar.skyservice.SetXPoint
    parent()->SetXPoint(angle, lat, dist, ring);
}

double SkyserviceAdaptor::SidTime(double jd)
{
    // handle method call org.skylendar.skyservice.SidTime
    return parent()->SidTime(jd);
}

void SkyserviceAdaptor::StopScan()
{
    // handle method call org.skylendar.skyservice.StopScan
    parent()->StopScan();
}


#include "astroprocessadaptor.moc"
