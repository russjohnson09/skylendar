/***************************************************************************
                          astroutils.cpp  -  description
                             -------------------
    begin                : Fri Sep 15 2000
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

#include "../config.h"
#include "astroutils.h"
#include "astrosql.h"
#include "astrodata.h"
#include "validskif.h"
#include "editastrodata.h"
#include "astromainwindow.h"
#include <cstdarg>

#ifdef QT
#include <QApplication>
#include <QMessageBox>
#include <QRegExp>
#include <qdom.h>
#include <QFile>
#endif

#include <cstdlib>
#include <cctype>
#ifdef __WINNT
#include <winsock.h>
#else
#include <unistd.h>
#include <libintl.h>
#endif

#define SKIF "-//DTD skif 1.1//EN"
#define XML "<?xml version = \"1.0\" encoding=\"UTF-8\"?>\n"
#define ACC 6

#ifdef QT

QString Translate(const char *s)
{
	return QObject::tr(s);
}

QString i18n2(const char *index, const char* fallback)
{
	return QCoreApplication::translate("QObject", index, fallback);
}
#endif

bool in(char c, const char *s)
{
    const char *RESTR p = s;
    if (!s)
        return false;
    for (; *p; p++)
        if (*p == c)
            return true;
    return false;
}

double DegToDec(double d)
{
    double si = SIGN(d);
    d = fabs(d);
    double t =  fmod(d, 1.0) * 100 + 1e-10;
    int j = (int) t;
    t = fmod(t, 1.0) * 100 + 1e-10;
    return si * ((int)d + j / 60.0 + t / 3600.0);
}

double DecToDeg(double d)
{
    double si = SIGN(d);
    d = fabs(d);
    int h = (int)d, m, s;
    d = fabs(d);
    d -= fabs(h);
    d *= 60;
    m = (int)d;
    d -= m;
    d *= 60;
    s = (int)d;
    if (d - s > 0.5) s++;
    if (s == 60)
    {
        s = 0;
        m++;
        if (m == 60)
        {
            m = 0;
            h++;
        }
    }
    return si * (h + m / 100.0 + s / 10000.0);
}

void Hmr(double r, int& h, int& m, int& s, bool roundup)
{
    double f = fabs(r), r1 = fmod(f, 1.0);
    h = SIGN(r) * (int)f;
    int i = abs((int)((r1 + 1e-5) * 10000.0));
    m = i / 100;
    s = i % 100;
    if (roundup)
    {
        r1 = fmod(r1 * 100000.0, 10.0);
        if (r1 >= 5.0)
        {
            s++;
            if (s == 60)
            {
                s = 0;
                m++;
                if (m == 60)
                {
                    m = 0;
                    h++;
                }
            }
        }
    }
}

double Normalize(double x)
{
    double y;
    y = fmod(x, 360.0);
    if (fabs(y) < 1e-13) y = 0.0;
    if (y < 0.0) y += 360.0;
    return y;
}

void Split(const AstroString& str, const AstroString& pat, AstroStringList* asl)
{
    asl->Clear();
    int i = 0, j;
    while ((j = str.Find(pat, i)) != -1)
    {
        asl->Append(new AstroString(str.Mid(i, j - i)));
        i = j + pat.Len();
    }
    asl->Append(new AstroString(str.Mid(i, str.Len() - i)));
}

void Split(const AstroString& str, AstroRegExp& pat, AstroStringList* asl)
{
    asl->Clear();
    int i = 0, j;
    while ((j = str.Find(pat, i)) != -1)
    {
        asl->Append(new AstroString(str.Mid(i, j - i)));
        i = j + 1;
    }
    asl->Append(new AstroString(str.Mid(i, str.Len() - i)));
}

const char *rebuf(int i)
{
    static char buf[12];
    (void)sprintf(buf, "%d", i);
    return buf;
}

int AstroString::Find(AstroRegExp& pat, int i) const
{
#ifdef QT
    return indexOf(pat, i);
#endif
}


bool AstroQuestion(const AstroString& quest)
{
#ifdef QT
	return (QMessageBox::question(0, QT_TRANSLATE_NOOP("nc", "Question"), quest) == QMessageBox::Yes);
#endif
}

int AstroQuestion3(const AstroString& quest)
{
#ifdef QT
	int i = QMessageBox::question(0, QT_TRANSLATE_NOOP("nc", "Question"), quest, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Cancel);
    switch (i)
    {
    case QMessageBox::Yes :
        return 1;
        break;
    case QMessageBox::No  :
        return 2;
        break;
    default:
        ;
    }
    return 0;
#endif
}

void AstroMessage(const AstroString& s, bool error)
{
#ifdef QT
    if (error)
			QMessageBox::critical(0, QString(), s);
    else
			QMessageBox::information(0, QString(), s);
#endif
}

AstroString& Sprintf(const AstroString& format, AstroString* abuf, ...)
{
#ifdef QT
    QString conv;
    va_list vl;
    abuf->clear();
    va_start(vl, abuf);
    for (int i = 0; i < format.length(); i++)
    {
        QChar q = format.at(i);
        if (q != '%')
        {
            if (q == '\\') q = format.at(++i);
            abuf->append(q);
        }
        else
        {
            q = format.at(++i);

            switch (q.toLatin1())
            {
            case 'c' :
                abuf->append(char(va_arg(vl, long)));
                break;
            case 's' :
                abuf->append(va_arg(vl, char*));
                break;
            case 'd' :
                abuf->append(conv.setNum(int(va_arg(vl, long))));
                break;
            case 'f' :
                abuf->append(conv.setNum(va_arg(vl, double), 'f'));
                break;
            case 'a' :
                abuf->append(*va_arg(vl, AstroString*));
                break;
            case 'l':
#if __SIZEOF_LONG__ == 8
                abuf->append(conv.setNum(va_arg(vl, long)));
#else
                abuf->append(conv.setNum(va_arg(vl, long long)));
#endif
                break;
            default:
                ;
            };
        }
    }
    va_end(vl);
    return *abuf;
#endif
}

/** Extract the year part of the given julday */
static int GetYear(double julday, int* month, int gregflag)
{
#define SE_GREG_CAL 1
    double u0,u1,u2,u3,u4;
    u0 = julday + 32082.5;
    if (gregflag == SE_GREG_CAL) {
        u1 = u0 + floor (u0/36525.0) - floor (u0/146100.0) - 38.0;
        if (julday >= 1830691.5) u1 +=1;
        u0 = u0 + floor (u1/36525.0) - floor (u1/146100.0) - 38.0;
    }
    u2 = floor (u0 + 123.0);
    u3 = floor ( (u2 - 122.2) / 365.25);
    u4 = floor ( (u2 - floor (365.25 * u3) ) / 30.6001);
    *month = (int) (u4 - 1.0);
    if (*month > 12) *month -= 12;
    return (int) (u3 + floor ( (u4 - 2.0) / 12.0) - 4800);
}

#define BISS(i) ((i % 4 == 0) && (i % 100 != 0)) ^ (i % 400 == 0)

/** Returns the number of bissextile years between source and dest */
static int NbBissYears(short source, short dest)
{
    int cnt = 0;
    if (source < dest)
    {
        for (int i = source; i <= dest; i++)
            if (BISS(i)) cnt++;
    }
    else if (source > dest)
        for (int i = dest; i >= source; i--)
            if (BISS(i)) cnt++;
    return cnt;
}

static int GetMonths(int start, int nb, bool biss)
{
    static const unsigned char dm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int cnt = 0, j;
    if (!nb) return 0;
    if (nb > 0)
        for (int i = start; i < start + nb; i++)
        {
            j = i % 12;
            if (j == 0) j = 12;
            if (biss && j == 2) cnt++;
            cnt += dm[j - 1];
        }
    else
        for (int i = start; i > start + nb; i--)
        {
            j = i % 12;
            j--;
            if (j <= 0) j += 12;
            if (biss && j == 2) cnt--;
            cnt -= dm[j - 1];
        }
    return cnt;
}

double IncTime(double julday, int seconds, int minutes, int hours, int days, int months, int years)
{
    double d = floor(julday), r = julday - d, k;
    int start, y = GetYear(julday, &start, 1);
    days += NbBissYears(y, y + years);
    k = (seconds * ONESECOND) + (minutes * ONEMINUTE) + (hours * 60.0 * ONEMINUTE);// + ((hours + (6 * years)) * (60 * ONEMINUTE));
    r += k;
    return d + r + double(days + GetMonths(start, months, y % 4 == 0) + (365 * years));
}

double IncTime(int y, int m, int seconds, int minutes, int hours, int days, int months, int years)
{
    double k;
    days += NbBissYears(y, y + years);
    k = (seconds * ONESECOND) + (minutes * ONEMINUTE) + (hours * 60.0 * ONEMINUTE);// + ((hours + (6 * years)) * (60 * ONEMINUTE));
    return k + double(days + GetMonths(m, months, y % 4 == 0) + (365 * years));
}

double Progress(double julday, int years, int months, int days)
{
    // 1 year = 1 day = 86400 seconds
    int s = (int)(days * 236.712) + months * 7204.9215 + years * 86400, h = s / 3600, m;
    s %= 3600;
    m = s / 60;
    s %= 60;
    return IncTime(julday, s, m, h);
}

double Direct(double julday, int years, int months)
{
    // 1 year = 1 degree = 4 minutes = 240 seconds
    return julday + (239.0 * years + 19.91 * months) * ONESECOND;
}

double Lon2Ra(double lon, double e)
{
    double ra, x;
    if (lon == 90.0) return 90.0;
    if (lon == 270.0) return 270.0;
    x = RADDEG(atan(tan(DEGRAD(lon)) * cos(DEGRAD(e))));
    if (lon >= 0.0 && lon < 90.0) return x;
    if (lon > 90.0 && lon < 270.0) return Normalize(x + 180.0);
    return Normalize(x + 360.0);
}

double Ra2Lon(double ra, double e)
{
    double lon, x;
    if (lon == 90.0) return 90.0;
    if (lon == 270.0) return 270.0;
    x = RADDEG(atan(tan(DEGRAD(ra)) / cos(DEGRAD(e))));
    if (ra >= 0.0 && ra < 90.0) return x;
    if (ra > 90.0 && ra < 270.0) return Normalize(x + 180.0);
    return Normalize(x + 360.0);
}

void Diffs(double j, double j1, int& days, int& hours, int& minutes, int& seconds)
{
    double d = floor(j), d1 = floor(j1), r = j - d, r1 = j1 - d1, dr = r1 - r;
    int nb = int(dr / ONESECOND);
    days = int(d1 - d);
    hours = nb / 3600;
    minutes = nb % 3600;
    seconds = minutes % 60;
    minutes /= 60;
}

double DiffAngle(double a, double b)
{
    double d = fabs(a - b);
    return d > 180.0 ? 360.0 - d : d;
}

void Dhms(double d, int* h, int* m, int* s)
{
    int i, j;
    double p, r = modf(fabs(d), &p);
    *h = SIGN(d) * (int)p;
    i = (int)(r * 10000.0);
    *m = i / 100;
    j = i % 100;
    if (s)
        *s = j;
    else
    {
        if (j >= 30)
            *m++;
        if (*m == 60)
        {
            *m = 0;
            *h++;
        }
    }
}

double MidPoint(double a, double b)
{
    double c;
    if (a > b)
    {
        c = a;
        a = b;
        b = c;
    }
    c = fabs(a - b);
    if (c >= 180.0)
        return Normalize(a + 180.0 + (c / 2.0));
    return Normalize(a + c / 2.0);
}

void Pass()
{
#ifdef QT
    if (qApp->hasPendingEvents())
        qApp->processEvents(QEventLoop::AllEvents, 10);
#endif
}

static bool ReadDataSet(AstroData* ad, QDomNode& n)
{
    AstroRequest arq;
    AstroHM hm;
    int h, m, s, day, mo, y;
    double d, b;
    AstroString as, charttype, country, placename, name, cty, cou, plm;
    while (!n.isNull())
    {
        QDomElement e = n.toElement();
        if (!e.isNull())
        {
            name = e.tagName();
            if (name == "NAME")
                ad->Name = e.text();
            else if (name == "TYPE")
            {
                as = e.attribute("Gender", "n");
                const char c = *as.toUpper().toUtf8().data();
                switch (c)
                {
                case 'M':
                    ad->Gender = Male;
                    break;
                case 'F':
                    ad->Gender = Female;
                    break;
                case 'N':
                    ad->Gender = Neutral;
                    break;
                default:
                    ad->Gender = Situation;
                };
                charttype = e.text();
                if (arq.Exec("SELECT Name, Idx FROM TypeIcons WHERE Name = '%a'", &charttype) && arq.Valid())
                    ad->ChartType = arq.GetInt("Idx");
                else
                    cty = charttype;
            }
            else if (name == "DATE")
            {
                day = atoi(e.attribute("Day", "1").toUtf8().data());
                mo = atoi(e.attribute("Month", "1").toUtf8().data());
                y = atoi(e.attribute("Year", "0").toUtf8().data());
                hm.Set((AstroString)e.attribute("Hm", "0:0:0"));
                d = hm.Get();
                HMR(d, h, m, s);
                ad->SetDate(day, mo, y, h, m, s);
                ad->Accuracy = atoi(e.attribute("Accuracy", "0").toUtf8().data());
                hm.Set(e.attribute("Timezone", "0.0").toUtf8().data(), HM_Longitude);
                d = hm.Get();
                hm.Set(e.attribute("Daylight", "0.0").toUtf8().data(), HM_Longitude);
                b = hm.Get();
                ad->SetOffDay(d, b);
            }
            else if (name == "PLACE")
            {
                ad->Latitude.Set((AstroString)e.attribute("Latitude", "0:0:0"), HM_Latitude);
                ad->Longitude.Set((AstroString)e.attribute("Longitude", "0:0:0"), HM_Longitude);
                placename = (AstroString)e.text();
                if (arq.Exec("SELECT Name, Idx FROM Place WHERE Name = '%a'", &placename) && arq.Valid())
                {
                    ad->PlaceName = placename;
                    ad->PlaceIdx = arq.GetInt("Idx");
                }
                else
                    plm = placename;
            }
            else if (name == "COUNTRY")
            {
                as = e.attribute("ZoneInfoFile", "GMT");
                country = e.text();
                if (arq.Exec("SELECT Name, Idx FROM Country WHERE Name ~* '%a'", &country) && arq.Valid())
                    ad->CountryIdx = arq.GetInt("Idx");
                else
                    cou = country;
            }
            else if (name == "KEYWORDS")
                ad->Keywords = e.text();
            else if (name == "COMMENT")
                ad->Comment = e.text();
        }
        n = n.nextSibling();
    }
    if (cty != "" || plm != "" || cou != "")
    {
        ValidSKIF vs(cty, plm, cou, ad->Name);
        if (vs.exec())
        {
            if (cou != "" && arq.Exec("SELECT Name, Idx FROM COUNTRY WHERE Name = '%a'", &cou) && arq.Valid())
                ad->CountryIdx = arq.GetInt("Idx");
            if (cty != "" && arq.Exec("SELECT Name, Idx FROM TypeIcons WHERE Name = '%a'", &cty) && arq.Valid())
                ad->ChartType = arq.GetInt("Idx");
            EditAstroData ead(*ad, &placename);
            return ead.exec();
        }
        else
            return false;
    }
    return true;
}

static bool WriteDataSet(const AstroData* ad, QDomElement& ds, QDomDocument& xml)
{
    AstroString as;
    AstroRequest arq;
    int day, mo, y, h, m;
    AstroHM hm;
    QDomElement e = xml.createElement("NAME");
    QDomText t = xml.createTextNode(ad->Name);
    e.appendChild(t);
    ds.appendChild(e);
    e = xml.createElement("TYPE");
    switch (ad->Gender)
    {
    case Male:
        as = "M";
        break;
    case Female:
        as = "F";
        break;
    case Neutral:
        as = "N";
        break;
    default:
        ;
        as = "S";
    };
    e.setAttribute("Gender", as);
    t = xml.createTextNode(Ail->GetName(ad->ChartType));
    e.appendChild(t);
    ds.appendChild(e);
    e = xml.createElement("DATE");
    ad->GetDate(&day, &mo, &y, &h, &m);
    e.setAttribute("Day", day);
    e.setAttribute("Month", mo);
    e.setAttribute("Year", y);
    e.setAttribute("Accuracy", ad->Accuracy);
    e.setAttribute("Hm", ad->Get(as));
    hm = ad->GetOffset();
    e.setAttribute("Timezone", hm.Get(as));
    hm = ad->GetDaylight();
    e.setAttribute("Daylight", hm.Get(as));
    e.setAttribute("Julday", Sprintf("%f", &as, ad->GetJd()));
    ds.appendChild(e);
    e = xml.createElement("PLACE");
    e.setAttribute("Latitude", ad->Latitude.Get(as, HM_Latitude));
    e.setAttribute("Longitude", ad->Longitude.Get(as, HM_Longitude));
    t = xml.createTextNode(ad->PlaceName);
    e.appendChild(t);
    ds.appendChild(e);
    if (arq.Exec("SELECT Name, TzFile FROM Country WHERE Idx = %d", ad->CountryIdx) && arq.Valid())
        as = arq < "TzFile";
    else
        as = "GMT";
    e = xml.createElement("COUNTRY");
    e.setAttribute("ZoneInfoFile", as);
    t = xml.createTextNode(arq < "Name");
    e.appendChild(t);
    ds.appendChild(e);
    e = xml.createElement("KEYWORDS");
    t = xml.createTextNode(ad->Keywords);
    e.appendChild(t);
    ds.appendChild(e);
    e = xml.createElement("COMMENT");
    t = xml.createTextNode(ad->Comment);
    e.appendChild(t);
    ds.appendChild(e);
    return true;
}

void ReadSKIF(const AstroString& file)
{
    AstroData* ad;
    QDomDocument doc;
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&f))
    {
        f.close();
        return;
    }
    f.close();
    QDomElement docElem = doc.documentElement();
    QDomNode n1 = docElem.firstChild(), n;
    if (n1.isNull()) return;
    while (!n1.isNull())
    {
        ad = new AstroData;
        n = n1.firstChild();
        if (ReadDataSet(ad, n))
        {
            if (Amw)
                Amw->Aiw->AddData(ad);
            else
                Adl->AddData(ad);
        }
        else
            delete ad;
        n1 = n1.nextSibling();
    }
}

void WriteSKIF(const AstroString& file, AstroData* ad)
{
    AstroString as, datenow, timenow;
    char buf[30], user[30];
    QDomImplementation qdi;
    QDomDocument xml(qdi.createDocumentType("SKIF", SKIF, SKYSITE + "/dtd/skif.dtd"));
    gethostname(buf, 30);
#ifdef __WINNT
    DWORD d;
    GetUserNameA(user, &d);
#else
    cuserid(user);
#endif
    ::Now->GetDate(datenow);
    ::Now->GetTime(timenow);
    QDomComment com = xml.createComment(Sprintf(" Created by Skylendar %s, Author:%s@%s, Date:%a %a ",&as,
                                        VERSION, user, buf, &datenow, &timenow));
    xml.insertBefore(com, xml.firstChild());
    QDomElement skif = xml.createElement("SKIF"), ds;
    skif.setAttribute("Version", "1.1");
    xml.appendChild(skif);
    if (ad)
    {
        if (Amw->Aiw->Aib->Bt ==  DataButton)
        {
            ds = xml.createElement("DATASET");
            WriteDataSet(ad, ds, xml);
            skif.appendChild(ds);
        }
        else
        {
            AstroMessage(QT_TRANSLATE_NOOP("nc", "You must select a DataSet first"));
            return;
        }
    }
    else
        foreachc(*Adl, AstroDataList)
    {
        if ((!it)->Idx != 0)
        {
            ds = xml.createElement("DATASET");
            WriteDataSet(!it, ds, xml);
            skif.appendChild(ds);
        }
    }
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly))
    {
        AstroMessage(QT_TRANSLATE_NOOP("nc", "Can't write into file !"));
        return;
    }
    as = XML + xml.toString();
    const QByteArray qba = as.toUtf8();
    if (f.write(qba.data(), qba.length()) == -1)
    {
        f.close();
        AstroMessage(QT_TRANSLATE_NOOP("nc", "Can't write into file !"));
        return;
    }
    f.close();
}

enum Objs GetObjId(const AstroString& as)
{
    char buf[10];
    for (int i = 0; i <= Last_Planet; i++)
        if (*Asr->ObjShortNames[i] == as) return (enum Objs)i;
    for (int i = 0; i < NBEXTRA; i++)
        if (IfExtraObj(i + First_Extra) && *Asr->ExtraShortNames[i] == as) return (enum Objs)(i + First_Extra);
    for (int i = OBJNB; i < OBJNB + 16; i++)
        if (*Asr->ObjShortNames[i] == as) return (enum Objs)(i - OBJNB + XPoint);
    for (int i = 0; i < NbStars; i++)
        if (*Asr->StaNames[i].SName == as) return (enum Objs)(i + First_Star);
    if (as.isEmpty()) return Undefined_Obj;
    if (as == "*")    return ARABPART;
    as.Data(buf, 10);
    char *c = buf;
    while (*c)
        if (!isdigit(*c++)) return Undefined_Obj;
    int n = atoi(buf);
    if (n > Asr->NbParts) return Undefined_Obj;
    return (enum Objs)(-n + 1);
}

const AstroString& ObjName(int i, bool ap)
{
    if (ap)
    {
        if (i < 0 || i > Asr->NbParts) return *Asr->ObjError;
        return *Asr->PartsNames[i];
    }
    if (i < 0 || i >= Final_Star) return *Asr->ObjError;
    if (i >= First_Extra && i <= Asr->LastExtra) return *Asr->ExtraNames[i - First_Extra];
    if (i > Asr->LastExtra && i < XPoint) return *Asr->ObjError;
    if (i >= First_Star && i < Final_Star) return *Asr->StaNames[i - First_Star].Name;
    if (i >= XPoint) i -= XPoint - OBJNB;
    return *Asr->ObjNames[i];
}

const AstroString& ObjShortName(int i, bool ap)
{
    static AstroString as;
    if (ap)
    {
        if (i < 0 || i > Asr->NbParts) return *Asr->ObjShortError;
        return Sprintf("%d", &as, i);
    }
    if (i < 0 || i >= Final_Star) return *Asr->ObjShortError;
    if (i >= First_Extra && i <= Asr->LastExtra) return *Asr->ExtraShortNames[i - First_Extra];
    if (i > Asr->LastExtra && i < XPoint) return *Asr->ObjShortError;
    if (i >= First_Star && i < Final_Star) return *Asr->StaNames[i - First_Star].SName;
    if (i >= XPoint) i -= XPoint - OBJNB;
    return *Asr->ObjShortNames[i];
}

enum AspectAccuracy GetAspAppSep(double speed_a, double speed_b, bool before)
{

    const float sp = speed_b - speed_a;
    if (before)
        return sp > 0.0 ? Applying : Separating;
    else
        return sp < 0.0 ? Applying : Separating;
}

double CalcPart(const struct ThePart& tp, const Values& v, const _AstroRestrictions& ar)
{
    double x[3];
    enum Objs o;
    if (!tp.Use) return NOVALUE;
    static const struct ThePart ExP[3] =
    {
        { {{ Ascendant, TYPE_OBJ }, { Sun, TYPE_OBJ }, { Moon,TYPE_OBJ }}, true, true },
        { {{ Ascendant, TYPE_OBJ }, { Moon,TYPE_OBJ }, { Sun, TYPE_OBJ }}, true, true },
        { {{ Ascendant, TYPE_OBJ }, { Sun, TYPE_OBJ }, { Moon,TYPE_OBJ }}, true, true }
    };
    for (int i = 0; i < 3; i++)
    {
        const struct ObjPart& op = tp.Op[i];
        switch (op.obj)
        {
        case House_1:
            o = (ar == House_1)  ? House_1  : Ascendant;
            break;
        case House_4:
            o = (ar == House_4)  ? House_4  : FC;
            break;
        case House_7:
            o = (ar == House_7)  ? House_7  : Descendant;
            break;
        case House_10:
            o = (ar == House_10) ? House_10 : MC;
            break;
        default:
            o = (enum Objs)op.obj;
        };
        switch (op.type)
        {
        case TYPE_OBJ:
            if (op.type == TYPE_OBJ && ar != o) return NOVALUE;
            x[i] = v.Get(o);
            break;
        case TYPE_VAL:
            x[i] = op.obj;
            break;
        case TYPE_EXTRA:
            x[i] = CalcPart(ExP[op.obj - 1], v, ar);
            break;
        default:
            return NOVALUE;
        };
        if (x[i] == NOVALUE) return NOVALUE;
    }
    return Normalize(tp.Night && Diurnal(v.Get(Ascendant), v.Get(Sun)) ? x[0] + x[2] - x[1] : x[0] + x[1] - x[2]);
}

#ifdef IFEXCEPT
void Exception(const AstroException& ae)
{
    AstroString as;
    switch (ae.Et)
    {
    case DbException:
        AstroMessage(Sprintf(QT_TRANSLATE_NOOP("nc", "The Database returned\n%a\nSorry, this SQL request can't be completed!\nRetry or contact your system administator."), &as, &ae.Text));
    case OtherException:
        AstroMessage(Sprintf(QT_TRANSLATE_NOOP("nc", "Another error occured\n%a"), &as, &ae.Text));
        break;
    default:
        ;
    }
}

#endif

