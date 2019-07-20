/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -m -a astrogetvaluesadaptor -i astrogetvalues.h -l AstroGetValues /skylendar/builds/ubuntu/src/astrogetvalues.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "astrogetvaluesadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class ValsAdaptor
 */

ValsAdaptor::ValsAdaptor(AstroGetValues *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

ValsAdaptor::~ValsAdaptor()
{
    // destructor
}

QString ValsAdaptor::GetAspect(int i)
{
    // handle method call org.skylendar.vals.GetAspect
    return parent()->GetAspect(i);
}

QString ValsAdaptor::GetChartName()
{
    // handle method call org.skylendar.vals.GetChartName
    return parent()->GetChartName();
}

QString ValsAdaptor::GetDecan(const QString &obj, int ring)
{
    // handle method call org.skylendar.vals.GetDecan
    return parent()->GetDecan(obj, ring);
}

QString ValsAdaptor::GetEphemLine(int day, int month, int year)
{
    // handle method call org.skylendar.vals.GetEphemLine
    return parent()->GetEphemLine(day, month, year);
}

double ValsAdaptor::GetLong(int ring, const QString &obj)
{
    // handle method call org.skylendar.vals.GetLong
    return parent()->GetLong(ring, obj);
}

QString ValsAdaptor::GetMPAspect(int i)
{
    // handle method call org.skylendar.vals.GetMPAspect
    return parent()->GetMPAspect(i);
}

double ValsAdaptor::GetMidPoint(const QString &obj1, const QString &obj2)
{
    // handle method call org.skylendar.vals.GetMidPoint
    return parent()->GetMidPoint(obj1, obj2);
}

double ValsAdaptor::GetPart(int i, int ring)
{
    // handle method call org.skylendar.vals.GetPart
    return parent()->GetPart(i, ring);
}

QString ValsAdaptor::GetRingType(int i)
{
    // handle method call org.skylendar.vals.GetRingType
    return parent()->GetRingType(i);
}

QString ValsAdaptor::GetTerm(const QString &obj, int ring)
{
    // handle method call org.skylendar.vals.GetTerm
    return parent()->GetTerm(obj, ring);
}

double ValsAdaptor::GetVal(int ring, const QString &obj, int n)
{
    // handle method call org.skylendar.vals.GetVal
    return parent()->GetVal(ring, obj, n);
}

bool ValsAdaptor::IfObj(int ring, const QString &obj)
{
    // handle method call org.skylendar.vals.IfObj
    return parent()->IfObj(ring, obj);
}

bool ValsAdaptor::LockChart(int i)
{
    // handle method call org.skylendar.vals.LockChart
    return parent()->LockChart(i);
}

int ValsAdaptor::NbAspects()
{
    // handle method call org.skylendar.vals.NbAspects
    return parent()->NbAspects();
}

int ValsAdaptor::NbCharts()
{
    // handle method call org.skylendar.vals.NbCharts
    return parent()->NbCharts();
}

int ValsAdaptor::NbMPAspects()
{
    // handle method call org.skylendar.vals.NbMPAspects
    return parent()->NbMPAspects();
}

int ValsAdaptor::NbRings()
{
    // handle method call org.skylendar.vals.NbRings
    return parent()->NbRings();
}

int ValsAdaptor::SearchAspect(const QString &obj1, const QString &asp, const QString &obj2, int start, const QString &obj3)
{
    // handle method call org.skylendar.vals.SearchAspect
    return parent()->SearchAspect(obj1, asp, obj2, start, obj3);
}

int ValsAdaptor::TFGetAsp(int i)
{
    // handle method call org.skylendar.vals.TFGetAsp
    return parent()->TFGetAsp(i);
}

bool ValsAdaptor::TFNext()
{
    // handle method call org.skylendar.vals.TFNext
    return parent()->TFNext();
}

bool ValsAdaptor::TFReq(const QString &s)
{
    // handle method call org.skylendar.vals.TFReq
    return parent()->TFReq(s);
}

void ValsAdaptor::UnlockChart()
{
    // handle method call org.skylendar.vals.UnlockChart
    parent()->UnlockChart();
}


#include "astrogetvaluesadaptor.moc"
