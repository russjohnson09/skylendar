/***************************************************************************
                          astroprocess.cpp  -  description
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
#include "../config.h"
#include "astroprocess.h"
#include "astrostring.h"
#include "astroresources.h"
#include "astrointerface.h"
#include "astroutils.h"
#include "astrorestrictions.h"
#include "astrochartbase.h"
#include "astrochart.h"
#include "astroaspects.h"
#include "aspscanlist.h"
#include "astromidpoints.h"
#include "scaninterface.h"
#include "scanclient.h"
#include "direngine.h"

#ifdef QT
#include <QApplication>
#include "scanclientinterface.h"
#include "astroprocessadaptor.h"
//#include "skyserviceadaptor.h"
#endif
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define E 0.414225
#define SINE 0.40248
#define COSE 0.915429
#define cotg(x) (1.0 / tan(x))
#define FIRST (dc.aref ? dc.afirst : dc.first)

extern const char* HousesCodes;
#ifdef __WINNT
#undef LONG
#endif
extern "C"
{
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include "swephexp.h"
}

#define TOMIN ((24 * 60) / 4)
#define TOSEC (24 / 4)

#define GETDIR(a, b) for(int i = a; i <= b; i++) { if(ar == i) { SearchDir(i, ar1); if(!IfScan) break; p = (i * 100) / Max; if(p >= progr + 20) { progr = p; sci.Progress(p); }}}

static ExtraId EId;

struct GetHousesStruct
{
    double cusps[13], asc, mc, fc, desc, vertex, east_point;
};

static const double SignsAngles[] = { 0.0, 30.0, 60.0, 90.0, 120.0, 150.0, 180.0, 210.0,
                                      240.0, 270.0, 300.0, 330.0, 360.0
                                    };

inline double Average(double a, double b)
{
    return (a < b) ? a + (b - a) / 2.0 : b + (a - b) / 2.0;
} CONST

#undef interface
AstroComputing::AstroComputing(QObject* parent): QObject(parent)
{
    Cscl.Init(this);
	new SkyserviceAdaptor(this);
	auto sb = QDBusConnection::sessionBus();
	if(!sb.registerObject(SKYSERVICE, this))
		qDebug() << "not reg";
    QDBusConnectionInterface *bus = sb.interface();
	bus->registerService(QString("org.skyservice-") + QString::number(QCoreApplication::applicationPid()));
}

AstroComputing::~AstroComputing()
{
    for (int i = 0; i < NBDATA; i++)
        delete Ar[i];
}

static void Convert(double* angle, double* decl, double ecl)
{
    double xpo[3] = { *angle, *decl, 1.0 }, xpn[3];
    swe_cotrans(xpo, xpn, ecl);
    *angle = xpn[0];
    *decl = xpn[1];
}

static void GetHouses(const DataComp& dc, double aux, char housecode, struct GetHousesStruct *ghs)
{
    double ascmc[10];
    bool b = dc.extraflags & SEFLG_EQUATORIAL;
    (void)swe_houses_ex(aux, dc.extraflags, dc.latitude, dc.longitude, (int)housecode, ghs->cusps, ascmc);
    ghs->asc        = ascmc[b ? 4 : 0];
    ghs->mc         = ascmc[b ? 2 : 1];
    ghs->fc         = Normalize(ascmc[b ? 2 : 1] + 180.0);
    ghs->desc       = Normalize(ascmc[b ? 4 : 0] + 180.0);
    ghs->vertex     = ascmc[3];
    ghs->east_point = ascmc[4];
}

static bool GetPlanet(int index, const DataComp& dc, const struct GetHousesStruct& ghs, double *array, char *serr, const _AstroRestrictions& arr, double obliquity, bool dnpf, bool *retro = 0)
{
    double Su, Mo;
    int i = index, index1 = index;
    long l;
    if (dc.gauquelin) goto gau;
    if (index == North_Node || index == South_Node)
        index = (arr.TrueNode) ? SE_TRUE_NODE : SE_MEAN_NODE;
    if (index >= Fortune && index <= East_Point && dc.gethouses)
    {
        switch (index)
        {
        case Fortune:
            swe_calc_ut(dc.julday, Sun, dc.extraflags, array, serr);
            Su = *array;
            swe_calc_ut(dc.julday, Moon, dc.extraflags, array, serr);
            Mo = *array;
            *array = Normalize((dnpf && !Diurnal(ghs.asc, Su)) ? ghs.asc - Mo + Su : ghs.asc - Su + Mo);
            break;
        case Vertex:
            *array = ghs.vertex;
            break;
        case East_Point:
            *array = ghs.east_point;
            break;
        }
        *(++array) = *(++array) = *(++array) = *(++array) = *(++array) = 0.0;
        if (retro)
            *retro = false;
        return true;
    }
    if (index > Black_Moon && index < Fortune)
        index1 = ++index;
    if (index >= First_Extra && index <= arr.LastExtra) index1 = EId[index  - First_Extra];
    if (i == South_Node) index1 = North_Node;
gau:
    l = swe_calc_ut(dc.julday, index1, dc.extraflags, array, serr);
    if (l < 0) return false;
    if (dc.gauquelin)
    {
        double xp[2] = { array[0], array[1] };
        double g = swe_house_pos(swe_sidtime(dc.julday) * 15.0, dc.latitude, obliquity, 'G', xp, serr);
        *array = (g - 1.0) * 10.0;
        array[1] = g;
        array[2] = array[3] = array[4]  = 0;
        array[5] = xp[0];
        return true;
    }
    if (i == South_Node) *array = Normalize(*array + 180.0);
    if (retro)
    {
        if (i == South_Node)
        {
            *retro = true;
            return true;
        }
        *retro = array[3] < 0.0;
    }
    return true;
}

bool AstroComputing::_Compute(const DataComp& dc)
{
    const ComputeSubChart* csc = Cscl.Get(dc.cst);
    return csc ? csc->Compute(dc) : false;
}

bool AstroComputing::Recompute(QByteArray dct)
{
    DataComp dc;
    Put<DataComp>(dct, dc);
    Dc[dc.ring] = dc;
    if (Ar[dc.ring]->Equatorial) Dc[dc.ring].extraflags |= SEFLG_EQUATORIAL;
    if (dc.extraflags & SEFLG_TOPOCTR)
        swe_set_topo(dc.longitude, dc.latitude, dc.altitude);
    return _Compute(dc);
}

double AstroComputing::GetVersion()
{
    return SKYSERVICE_VERSION;
}

static bool IsSouthern(double lat, double longi, double jd, AstroComputing& ac)
{
    double in[3] = { longi, lat, 1.0 }, out[3];
    swe_cotrans(in, out, ac.GetObliquity(jd));
    return out[1] < 0.0;
}

bool AstroComputing::Compute(const DataComp& dc)
{
    double array[6], obl = 0.0;
    bool retro, ret = true;
    char buf[30], serr1[256];
    long l;
    DataComp dcl = dc;
    struct GetHousesStruct ghs;
    const _AstroRestrictions& Arr = *Ar[dcl.ring];
    Values& Vals = V[dcl.ring];
    Vals.Julday = dcl.julday;
    Vals.Latitude = dcl.latitude;
    Vals.Longitude = dcl.longitude;
    if (!Utc(dcl)) return false;
    if (Arr.Southern) Vals.Southern = IsSouthern(dcl.latitude, dcl.longitude, dcl.julday, *this);
    if (dc.gauquelin) obl = GetObliquity(dc.julday);
    if (Arr.Sidereal > Tropical)
    {
        dcl.extraflags |= SEFLG_SIDEREAL;
        swe_set_sid_mode(Arr.Sidereal, 0, 0);
    }
    if (Arr.Heliocentric) dcl.extraflags |= SEFLG_HELCTR;
    if (Arr.Equatorial)   dcl.extraflags |= SEFLG_EQUATORIAL;
    const double geopos[3] = { dcl.longitude, dcl.latitude, dcl.altitude};
    if (dcl.gethouses)
    {
        GetHouses(dcl,  aux, HousesCodes[Arr.GetHouse()], &ghs);
        Vals.Set(Ascendant, ghs.asc, false, 0.0, 0.0, 360.0);
        Vals.Set(MC, ghs.mc, false, 0.0, 0.0, 360.0);
        Vals.Set(FC, ghs.fc, false, 0.0, 0.0, 360.0);
        Vals.Set(Descendant, ghs.desc, false, 0.0, 0.0, 360.0);
        for (int i = House_1; i <= House_12; i++)
            Vals.Set(i, ghs.cusps[i - House_1 +1], false, 0.0, 0.0, 360.0);
        if (Arr == Vertex)
            Vals.Set(Vertex, ghs.vertex, false, 0.0, 0.0, 360.0);
        if (Arr == East_Point)
            Vals.Set(East_Point, ghs.east_point, false, 0.0, 0.0, 360.0);
    }
    for (int i = Sun; i <= Fortune; i++)
    {
        if (Arr == i)
        {
            if (GetPlanet(i, dcl, ghs, array, serr1, Arr, obl, Arr.Dnpf, &retro))
            {
                if(dcl.ct == LocalHorizon)
                {
                    double out[3];
                    swe_azalt(dcl.julday, dcl.extraflags, (double*)geopos, Pressure, Temperature, array, out);
                    memcpy(array, out, sizeof(double) * 3);
                }
                Vals.Set(i, Normalize(array[0]), retro, array[1], array[2], array[3], array[4], array[5]);
            }
            else
            {
                strncpy(serr, serr1, 255);
                Vals.Set(i, NOVALUE);
                ret = false;
            }
        }
    }
    if (Arr.IfExtra())
    {
        for (int i = First_Extra; i <= Arr.LastExtra; i++)
        {
            if (Arr == i)
                if (GetPlanet(i, dcl, ghs, array, serr1, Arr, obl, Arr.Dnpf, &retro))
                {
                    if(dcl.ct == LocalHorizon)
                    {
                        double out[3];
                        swe_azalt(dcl.julday, dcl.extraflags, (double*)geopos, Pressure, Temperature, array, out);
                        memcpy(array, out, sizeof(double) * 3);
                    }
                    Vals.Set(i, array[0], retro, array[1], array[2], array[3], array[4], array[5]);
                }
                else
                {
                    strncpy(serr, serr1, 255);
                    Vals.Set(i, NOVALUE);
                    ret = false;
                }
        }
    }
    if (Arr.IfStars())
			{
        for (int i = First_Star; i < Final_Star; i++)
            if (Arr == i)
            {
                sprintf(buf, "%d", Sti[i - First_Star] + 1); 
                l = swe_fixstar_ut(buf, dcl.julday, dcl.extraflags, array, serr1);
                if(l < 0)
                {
                    strncpy(serr, serr1, 255);
                    Vals.Set(i, NOVALUE);
                    ret = false;
                }
                else
                {
                    if(dcl.ct == LocalHorizon)
                    {
                        double out[3];
                        swe_azalt(dcl.julday, dcl.extraflags, (double*)geopos, Pressure, Temperature, array, out);
                        memcpy(array, out, sizeof(double) * 3);
                    }
                    Vals.Set(i, array[0], false, array[1], array[2], array[3], array[4], array[5]);
                }
            }
    }
    return ret;
}

double AstroComputing::GetMagnitude(int i)
{
    double d;
    char buf[50];
    sprintf(buf, "%d", i - First_Star + 1);
    long l = swe_fixstar_mag(buf, &d, serr);
    return d;
}

void AstroComputing::SetXPoint(double angle, double lat, double dist, int ring)
{
    Values& Vals = V[ring];
    Vals.Set(XPoint, angle, false, lat, dist);
}

QByteArray AstroComputing::GetValues(int slot) const
{
    return Get1<Values>(V[slot]);
}

void AstroComputing::SetRestrict(QByteArray art, int i)
{
    if (i < 0 || i >= NBDATA) return;
    Put<_AstroRestrictions>(art, *Ar[i]);
}

QString AstroComputing::DBusGetError()
{
    return serr;
}

void AstroComputing::InitRestricts(QByteArray art)
{
    _AstroRestrictions ar;
    Put<_AstroRestrictions>(art, ar);
    for (int i = 0; i < NBDATA; i++)
    {
        Ar[i] = new _AstroRestrictions(ar);
    }
}

void AstroComputing::Kill()
{
    exit(0);
}

void AstroComputing::ScanAsp(QByteArray dct, double origjd, QString scserver, bool dual, bool mp, bool tosecond, bool ap)
{
    int flags = 0, progr = 0, p;
    DataComp dc;
    double j1, j2, last;
    Values v1;
    AstroFoundAspectsTable afat1, afat2, *afp1, *afp2, *afp3;
#ifdef QT
    const QString s1 = ORGSKYLENDAR, s2 = scserver.section(' ', 1);
    OrgSkylendarScanclientInterface sci(s1 + ".scanclient"/*s1 + scserver.section(' ', 0, 0)*/, s2, QDBusConnection::sessionBus(), this);
    Sci = &sci;
    Put<DataComp>(dct, dc);
#endif
    IfScan = true;
    dc.extraflags |= SEFLG_SPEED;
    const Values& orig = V[FIRST];
    const _AstroAspects aa(Ar[dc.ring]);
    const _AstroRestrictions &ar1 = *Ar[FIRST], &ar2 = *Ar[dc.ring];
    const int mins = tosecond ? TOSEC  : TOMIN;
    last = dc.julday;
    afp1 = &afat1;
    afp2 = &afat2;
    j1 = origjd;
    v1 = V[dc.ring];
    j2 = IncTime(j1, 0, mins, 0, 0, 0, 0);
    dc.julday = j2;
    if (dc.gethousesfirst) flags |= Ha;
    if (dc.gethouses)      flags |= Hb;
    if (!_Compute(dc)) return;
    if (mp) flags |= MPa;
    if (ap) flags |= Pta;
    if (dual)
    {
        afp1->GetAspects(aa, V[dc.ring], V[dc.ring], ar1, ar2, flags);
        afp2->GetAspects(aa, orig, V[dc.ring], ar1, ar2, flags);
    }
    else
    {
        afp1->GetAspects(aa, orig, V[dc.ring], ar1, ar2, flags | IfSamePlanet);
        afp2->GetAspects(aa, orig, V[dc.ring], ar1, ar2, flags | IfSamePlanet);
    }
    v1 = V[dc.ring];
    j1 = j2;
    while (j2 < last)
    {
        p = int((j2 - origjd)  * 100.0 / (last - origjd));
        if (p >= progr + 4)
        {
            progr = p;
            sci.Progress(p);
        }
        j2 = IncTime(j1, 0, mins, 0, 0, 0, 0);
        if (j2 > last) j2 = last;
        dc.julday = j2;
        if (!_Compute(dc)) return;
        if (dual)
            afp2->RegetAspects(aa, V[dc.ring], V[dc.ring], ar1, ar2, flags);
        else
            afp2->RegetAspects(aa, orig, V[dc.ring], ar1, ar2, IfSamePlanet | flags);
        TestAsp(aa, *afp1, *afp2, v1, V[dc.ring], j1, j2, dc, dual, mp, tosecond, ap);
        if (!IfScan) break;
        v1 = V[dc.ring];
        j1 = j2;
        afp3 = afp1;
        afp1 = afp2;
        afp2 = afp3;
    }
    sci.EndScan();
}

void AstroComputing::TestAsp(const _AstroAspects& aa, const AstroFoundAspectsTable& afat1,
                             const AstroFoundAspectsTable& afat2, const Values& v1, const Values& v2,
                             double j1, double j2, const DataComp& dc, bool dual, bool mp, bool tosecond, bool ap)
{
    int max_x, max_y, m;
    //double r, v, vo, dv, x, p1, p2, po1, po2, px, pox;
    const double mins = (tosecond ?  TOSEC : TOMIN) * ONEMINUTE;
    const _AstroRestrictions &ar1 = *Ar[FIRST], &ar2 = *Ar[dc.ring];
    //enum Aspects a1, a2;
    //bool change, change1;
    const Values &orig = V[FIRST];
    afat1.GetBounds(&max_x, &m);
    afat2.GetBounds(&m, &max_y);
    struct rdp
		{
			int b : 1;
		} __attribute__((packed));
    struct rdp rd[max_y];
    if (dual)
    {
        memset(rd, 0, sizeof(rd));
#ifdef _OPENMP
# pragma omp parallel for
#endif
        for (int i = 0; i <= 12; i++)
        {
            double p1, p2, v, x;
            bool change;
            const double& sa = SignsAngles[i];
            Pass();
            for (int j = Sun; j < max_y; j++)
            {
                if (ar2 != j) continue;
                if ((j >= Ascendant && j <= House_12) || j == Fortune) continue;
                p1 = v1.Get(j);
                p2 = v2.Get(j);
                bool dif = fabs(p2 -p1) < 1e-07;
                change = (v1.Retro(j) + v2.Retro(j)) == 1;
                if (p2 < p1 && !v2.Retro(j) && !change) {
                    if (dif) continue;
                    p2 += 360.0;
                }
                if (p2 > p1 && v2.Retro(j) && !change)  p1 += 360.0;
                if (p1 <= sa && p2 >= sa)
                {
                    v = (p2 - p1) / mins;
                    x = j1 + ((sa - p1) / v);
                    Sci->GetSignTrans(j, (i == 12) ? 0 : i, x);
                }
            }
        }
    }
#ifdef _OPENMP
# pragma omp parallel for
#endif
    for (int i = Sun; i < max_x; i++)
    {
        Pass();
        if (ar1 != i) continue;
        double r, x, px, pox, p1, p2, v, vo, po1, po2, dv;
        //int rd = -1;
        bool change, change1;
        for (int j = Sun; j < max_y; j++)
        {
            if (ar2 != j) continue;
            enum Aspects a1 = (enum Aspects)afat1.Get(i, j), a2 = (enum Aspects)afat2.Get(i, j);
            if (a1 != Unknown_Aspect && a2 != Unknown_Aspect && a1 == a2)
            {
                p1 = v1.Get(j);
                p2 = v2.Get(j);
                change = (v1.Retro(j) + v2.Retro(j)) == 1;
                if (p2 < p1 && !v2.Retro(j) && !change) p2 += 360.0;
                if (p2 > p1 && v2.Retro(j) && !change)  p1 += 360.0;
                if (dual)
                {
                    if (change && rd[j].b == false)
                    {
                        double s1 = v1.Get(j, 3), acc = (v2.Get(j, 3) - s1) / (tosecond ? .0042 : 0.252), z = -s1 / acc;
                        Sci->GetRetro(j, s1 >= 0.0 ? -p1 : p1, j1 + z);
                        rd[j].b = true;
                    }
                    if ((j >= Ascendant && j <= House_12) || (j >= Fortune && j <= East_Point)) continue;
                    if ((i >= Ascendant && i <= House_12) || (i >= Fortune && i <= East_Point)) continue;
                    if (i == North_Node && j == South_Node && a1 == Opposition) continue;
                    if (j == North_Node && i == South_Node && a1 == Opposition) continue;
                    po1 = v1.Get(i), po2 = v2.Get(i);
                    change1 = (v1.Retro(i) + v2.Retro(i)) == 1;
                    if (po2 < po1 && !v2.Retro(i) && !change1) po2 += 360.0;
                    if (po2 > po1 && v2.Retro(i) && !change1)  po1 += 360.0;
                    vo = (po2 - po1) /mins;
                    v = (p2 - p1) / mins, dv = v - vo;
                    r = Normalize(po1 - p1 - (aa * a1));
                    x = j1 + r / dv;
                    if (x >= j1 && x <= j2)
                    {
                        px = p1 + (v * r / dv);
                        if (px >= 360.0) px -= 360.0;
                        if (px < 0.0) px += 360.0;
                        pox = po1 + (v * r / dv);
                        if (pox >= 360.0) pox -= 360.0;
                        if (pox < 0.0) pox += 360.0;
                        Sci->GetAspect(j, px * (v1.Retro(j) ? -1.0 : 1.0), i, pox * (v1.Retro(i) ? -1.0 : 1.0), a1, x);
                    }
                    else
                    {
                        r = -Normalize(p1 - po1 + (aa * a1));
                        if (r > 0.0)
                            r -= 360.0;
                        x = j1 + r / dv;
                        px = p1 + (v * r / dv);
                        if (px >= 360.0) px -= 360.0;
                        if (px < 0.0) px += 360.0;
                        pox = po1 + (v * r / dv);
                        if (pox >= 360.0) pox -= 360.0;
                        if (pox < 0.0) pox += 360.0;
                        if (x >= j1 && x <= j2)
                            Sci->GetAspect(j, px * (v1.Retro(j) ? -1.0 : 1.0), i, pox  * (v1.Retro(i) ? -1.0 : 1.0), a1, x);
                    }
                    continue;
                }
                if ((j >= Ascendant && j <= House_12) || (j >= Fortune && j <= East_Point)) continue;
                r = Normalize(orig.Get(i) - (aa * a1));
                if (p2 >= r && p1 <= r)
                {
                    v = (p2 - p1) / mins;
                    x = j1 + ((r - p1) / v);
                    if (r >= 360.0) r = 0.001;
                    Sci->GetAspect(j, r * (v1.Retro(j) ? -1.0 : 1.0), i, orig.Get(i) * (orig.Retro(i) ? -1.0 : 1.0), a1, x);
                }
                else
                {
                    r = Normalize(orig.Get(i) + (aa * a1));
                    if (p2 >= r && p1 <= r)
                    {
                        v = (p2 - p1) / mins;
                        x = j1 + (r - p1) / v;
                        if (r >= 360.0) r = 0.001;
                        Sci->GetAspect(j, r * (v1.Retro(j) ? -1.0 : 1.0), i, orig.Get(i) * (orig.Retro(i) ? -1.0 : 1.0), a1, x);
                    }
                }
            }
        }
    }

    if (mp)
    {
        const AstroMidPoints& origamp = *afat1.GetAmp();
#ifdef _OPENMP
# pragma omp parallel for
#endif
        for (int i = Sun; i < max_y; i++)
        {
            Pass();
            double p1, p2, r, v, x;
            bool change;
            if ((i >= Ascendant && i <= House_12) || (i >= Fortune && i <= East_Point)) continue;
            if (ar2 != i) continue;
            const ATable &at1 = afat1[i], &at2 = afat2[i];
            for (int j = Sun; j < max_x; j++)
                for (int k = j; k < max_x; k++)
                {
                    //if((ar1 != j) || (ar1 != k)) continue;
                    enum Aspects a1 = (enum Aspects)at1.Get(j, k), a2 = (enum Aspects)at2.Get(j, k);
                    if (a1 != Unknown_Aspect && a2 != Unknown_Aspect && a1 == a2)
                    {
                        p1 = v1.Get(i);
                        p2 = v2.Get(i);
                        change = (v1.Retro(i) + v2.Retro(i)) == 1;
                        if (p2 < p1 && !v2.Retro(i) && !change) p2 += 360.0;
                        if (p2 > p1 && v2.Retro(i) && !change)  p1 += 360.0;
                        //if((i >= Ascendant && i <= House_12) || i == Fortune) continue;
                        r = Normalize(origamp.Get(j, k) - (aa * a1));
                        if (p2 >= r && p1 <= r)
                        {
                            v = (p2 - p1) / mins;
                            x = j1 + ((r - p1) / v);
                            //if(r >= 360.0) r = 0.001;
                            Sci->GetMPAspect(j, k, origamp.Get(j, k), i, r * (v2.Retro(i) ? -1.0 : 1.0), a1, x);
                        }
                        else
                        {
                            r = Normalize(origamp.Get(j, k) + (aa * a1));
                            if (p2 >= r && p1 <= r)
                            {
                                v = (p2 - p1) / mins;
                                x = j1 + (r - p1) / v;
                                //if(r >= 360.0) r = 0.001;
                                Sci->GetMPAspect(j, k, origamp.Get(j, k), i, r * (v2.Retro(i) ? -1.0 : 1.0), a1, x);
                            }
                        }
                    }
                }
        }
    }

    if (ap)
    {
#ifdef _OPENMP
# pragma omp parallel for
#endif
        for (int i = 0; i < NbParts; i++)
        {
            Pass();
            double p1, p2, r, v, x;
            bool change;
            double z = CalcPart(Parts[i], orig, ar1);
            if (z == NOVALUE) continue;
            for (int j = Sun; j < max_y; j++)
            {
                if (ar2 != j) continue;
                enum Aspects a1 = (enum Aspects)!afat1.Get(j, i), a2 = (enum Aspects)!afat2.Get(j, i);
                if (a1 != Unknown_Aspect && a2 != Unknown_Aspect && a1 == a2)
                {
                    p1 = v1.Get(j);
                    p2 = v2.Get(j);
                    change = (v1.Retro(j) + v2.Retro(j)) == 1;
                    if (p2 < p1 && !v2.Retro(j) && !change) p2 += 360.0;
                    if (p2 > p1 && v2.Retro(j) && !change)  p1 += 360.0;
                    if ((j >= Ascendant && j <= House_12) || (j >= Fortune && j <= East_Point)) continue;
                    r = Normalize(z - (aa * a1));
                    if (p2 >= r && p1 <= r)
                    {
                        v = (p2 - p1) / mins;
                        x = j1 + ((r - p1) / v);
                        //if(r >= 360.0) r = 0.001;
                        Sci->GetAspect(j, r * (v1.Retro(j) ? -1.0 : 1.0), i, z, a1, x, true);
                    }
                    else
                    {
                        r = Normalize(z + (aa * a1));
                        if (p2 >= r && p1 <= r)
                        {
                            v = (p2 - p1) / mins;
                            x = j1 + (r - p1) / v;
                            //if(r >= 360.0) r = 0.001;
                            Sci->GetAspect(j, r * (v1.Retro(j) ? -1.0 : 1.0), i, z, a1, x, true);
                        }
                    }
                }
            }
        }
    }
}

void AstroComputing::StopScan()
{
    IfScan = false;
}

double AstroComputing::GetRiseSet(double julday, int index, double latitude, double longitude, double altitude, int ca)
{
    int i, j;
    char str[6]{0,}, *ptr = 0;
    double pos[3] = { longitude, latitude, altitude }, ret;
    switch (ca)
    {
    case Rising:
        j = SE_CALC_RISE;
        break;
    case Setting:
        j = SE_CALC_SET;
        break;
    case Culminating:
        j = SE_CALC_MTRANSIT;
        break;
    case AtNadir:
        j = SE_CALC_ITRANSIT;
    };
    if (index >= First_Star && index <= Final_Star) { snprintf(str, 5, "%d", index - First_Star + 1); ptr = str; }
    if ((i = swe_rise_trans_true_hor(julday, index, ptr, 0, j, pos, Pressure, Temperature, altitude, &ret, serr)) < 0)
        return -1.0;
    return ret;
}

int AstroComputing::ComputeGlobEclipse(double julday, int flags, bool direction, bool lunar)
{
    return lunar ? swe_lun_eclipse_when(julday, flags, 0, EclData, !direction, serr) : swe_sol_eclipse_when_glob(julday, flags, 0, EclData, !direction, serr);
}

int AstroComputing::ComputeLocEclipse(double julday, int flags, double latitude, double longitude, double altitude, bool direction)
{
    double pos[3] = { longitude, latitude, 0.0}, ret[10];
    int r = swe_sol_eclipse_when_loc(julday, flags, pos, ret, EclData, direction, serr);
    if (r != -1)
    {
        for (int i = 0; i < 8; i++) EclData[i + 7] = EclData[i];
        for (int i = 0; i < 7; i++) EclData[i] = ret[i];
    }
    return r;
}

int AstroComputing::ComputeEclPos(double julday, int flags)
{
    double geopos[2];
    int r = swe_sol_eclipse_where(julday, flags, geopos, EclData, serr);
    EclData[8] = geopos[0];
    EclData[9] = geopos[1];
    return r;
}

int AstroComputing::LunarOccult(double julday, int i, int flags, double latitude, double longitude, double altitude, bool direction, bool local)
{
    double pos[3] = { longitude, latitude, altitude }, attr[20];
    char buf[10] = "";
    if (i >= First_Star)
    {
        sprintf(buf, "%d", i - First_Star + 1);
        i = -1;
    }
    return local ?  swe_lun_occult_when_loc(julday, i, buf, flags, pos, EclData, attr, direction, serr)
           : swe_lun_occult_when_glob(julday, i, buf, flags, SE_ECL_TOTAL | SE_ECL_CENTRAL | SE_ECL_NONCENTRAL, EclData, direction, serr);
}

double AstroComputing::GetEclipseValue(int i)
{
	return (i < 0 || i > 9) ? NOVALUE : EclData[i];
}

bool AstroComputing::IfParts()
{
    return NbParts ? true : false;
}

bool AstroComputing::LoadParts(QByteArray dbv, int size)
{
    Parts = new ThePart[size];
    Put<ThePart>(dbv, *Parts, sizeof(ThePart) * size);
    NbParts = size;
    return true;
}

ScanInterface::ScanInterface(AstroString service, AstroString path)
#ifdef QT
        :
	OrgSkylendarScanclientInterface(QString(ORGSKYLENDAR) + ".scanclient", "/scanclient", QDBusConnection::sessionBus(), this)
#endif
{
}

bool ComputeSubChart::Compute(const DataComp& dc) const
{
    return Ac->Compute(dc);
}

Values& ComputeSubChart::V(int i) const
{
    return Ac->V[i];
}

const _AstroRestrictions& ComputeSubChart::Ar(int i) const
{
    return *Ac->Ar[i];
}

class ComputeProgression: public ComputeSubChart
{
public:

    ComputeProgression(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        const _AstroRestrictions& ar = Ar(dc.ring);
        double jd = V(FIRST).Julday, d = dc.julday - jd, d1 = jd + d / ar.ProgFact;
        V(dc.ring).Julday = d1;
        DataComp dc1 = dc;
        dc1.julday = d1;
        return ComputeSubChart::Compute(dc1);
//         int  y = 0, mo = 0, d, h, m, s;
//         double jd = V(FIRST).Julday;
//         DataComp dc1 = dc;
//         Diffs(jd, dc.julday, d, h, m, s);
//         dc1.julday = Progress(jd, y, mo, d);
//         V(dc.ring).Julday = dc.julday;
//         return ComputeSubChart::Compute(dc1);
    }
};

class ComputeDirection: public ComputeSubChart
{
public:

    ComputeDirection(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        const _AstroRestrictions& ar = Ar(dc.ring);
        const Values& vf = V(FIRST);
        Values& vi = V(dc.ring);
        double j = dc.julday;
        double inc = (j - vf.Julday) / ar.ProgFact;
				auto f = [&](int i) { vi.CSet(i, vf.Get(i) + inc); };
				ar(f);
        return true;
    }
};

class ComputeAddAngle: public ComputeSubChart
{
public:

    ComputeAddAngle(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        const _AstroRestrictions& ar = Ar(dc.ring);
        const Values& v = V(FIRST);
        Values &vi = V(dc.ring);
				auto f = [&](int i) { vi.CSet(i, Normalize(v.Get(i) + dc.angle), v.Retro(i)); };
				ar(f);
        return true;
    }
};

class ComputeMulAngle: public ComputeSubChart
{
public:

    ComputeMulAngle(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        const _AstroRestrictions& ar = Ar(dc.ring);
        const Values& v = V(FIRST);
        Values& vi = V(dc.ring);
				auto f = [&](int i) { vi.CSet(i, Normalize(v.Get(i) * dc.angle), v.Retro(i)); };
				ar(f);
        return true;
    }
};

class ComputeComposite: public ComputeSubChart
{
public:

    ComputeComposite(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        const _AstroRestrictions& ar = Ar(dc.ring), &arf = Ar(FIRST);
        Values& vi = V(dc.ring);
        const Values& vf = V(FIRST);
				auto f = [&](int i) { vi.CSet(i, ar == i && arf == i ? MidPoint(vf.Get(i), vi.Get(i)) : NOVALUE, vi.Retro(i)); };
        if (!ComputeSubChart::Compute(dc)) return false;
				ar(f);
        return true;
    }
};

class ComputeTimeSpace: public ComputeSubChart
{
public:

    ComputeTimeSpace(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        DataComp dc1 = dc;
        dc1.julday = Average(Ac->Dc[FIRST].julday, dc1.julday);
        dc1.latitude = Average(Ac->Dc[FIRST].latitude, dc1.latitude);
        dc1.longitude = Average(Ac->Dc[FIRST].longitude, dc1.longitude);
        V(dc.ring).Julday = dc1.julday;
        return ComputeSubChart::Compute(dc1);
    }
};

class ComputeSolarArc: public ComputeSubChart
{
public:

    ComputeSolarArc(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        int  y, mo, d, h, m, s;
        const _AstroRestrictions& ar = Ar(dc.ring);
        const Values& v = V(FIRST);
        Values &vi = V(dc.ring);
        double p, jd = v.Julday;
        Diffs(jd, dc.julday, d, h, m, s);
        p = Ac->GetSunStep(jd) * (d / ar.ProgFact / 12.0 + d / 365.0);
				auto f = [&](int i) { vi.CSet(i, Normalize(v.Get(i) + p), v.Retro(i)); };
				ar(f);
        return true;
    }
};

class ComputeProfection: public ComputeSubChart
{
public:

    ComputeProfection(AstroComputing* ac): ComputeSubChart(ac) {}

    bool Compute(const DataComp& dc) const
    {
        int  y, mo, d, h, m, s;
        double p;
        DataComp dc1 = dc;
        const _AstroRestrictions& ar = Ar(dc.ring);
        const Values& v = V(FIRST);
        Values &vi = V(dc.ring);
				auto f = [&](int i) { vi.CSet(i, Normalize(v.Get(i) + p), v.Retro(i)); };
        Diffs(v.Julday, dc.julday, d, h, m, s);
        y = d / 365;
        d %= 365;
        mo = d / 30;
        d %= 30;
        p = Profect(y, mo, d);
				ar(f);
        return true;
    }
};

ComputeSubChartList::ComputeSubChartList()
{
    for (int i = NoSt; i <= Last_SubType; i++)
        Cscl[i] = 0;
}

void ComputeSubChartList::Init(AstroComputing* ac)
{
    Cscl[Single]      = new ComputeSubChart(ac);
    Cscl[Transit]     = new ComputeSubChart(ac);
    Cscl[Progression] = new ComputeProgression(ac);
    Cscl[Direction]   = new ComputeDirection(ac);
    Cscl[AddAngle]    = new ComputeAddAngle(ac);
    Cscl[MulAngle]    = new ComputeMulAngle(ac);
    Cscl[Composite]   = new ComputeComposite(ac);
    Cscl[TimeSpace]   = new ComputeTimeSpace(ac);
    Cscl[SolarArc]    = new ComputeSolarArc(ac);
    Cscl[Profection]  = new ComputeProfection(ac);
}

ComputeSubChartList::~ComputeSubChartList()
{
    for (int i = NoSt; i <= Last_SubType; i++)
        delete Cscl[i];
}

void AstroComputing::Pass()
{
#ifdef QT
    //#pragma omp single
    //{
    if (qApp->hasPendingEvents())
        qApp->processEvents(QEventLoop::AllEvents, 10);
    //}
#endif
}

double AstroComputing::Date_Conversion(unsigned char day, unsigned char month, short year, double utime, bool greg)
{
    double jd;
    if (UTC)
    {
        int h, m, s;
        double d[2];
        HMR(DecToDeg(utime), h, m, s);
        bool b = swe_utc_to_jd(year, month, day, h, m, s, greg, d, serr) == ERR;
        return b ? d[0] + MAX_DOUBLE : d[0];
    }
    return (swe_date_conversion(year, month, day, utime, greg ? 'g' : 'j', &jd) == ERR) ? jd + MAX_DOUBLE : jd;
}

double AstroComputing::Local2Mean(double j)
{
    double e;
    int ret = swe_time_equ(j, &e, serr);
    return ret == ERR ? MAX_DOUBLE : e;
}

double AstroComputing::GetObliquity(double julday)
{
    double array[6];
    swe_calc_ut(julday, SE_ECL_NUT, 0, array, serr);
    return array[0];
}

QByteArray AstroComputing::DBusRevJul(double jd, bool greg)
{
    if (UTC)
    {
        int hour, min, s;
        double sec;
        swe_jdet_to_utc(jd, greg, &Dt.year, &Dt.month, &Dt.day, &hour, &min, &sec);
        Dt.hm = RHM(hour, min, int(sec));
    }
    else
        swe_revjul(jd, (int)greg, &Dt.year, &Dt.month, &Dt.day, &Dt.hm);
    return Get1<DateTime>(Dt);
}

QByteArray AstroComputing::DBusAzalt(double jd, int flags, QByteArray geopos, QByteArray xin)
{
    Double3 dgp, dxi;
    Put<Double3>(geopos, dgp), Put<Double3>(xin, dxi);

    swe_azalt(jd, flags, dgp.d3, Pressure, Temperature, dxi.d3, D3.d3);
    return Get1<Double3>(D3);
}

QByteArray AstroComputing::DBusAzaltP(double jd, int flags, QByteArray geopos, QByteArray xin)
{
	Double3 dgp, dpi;
	int size = xin.size() / sizeof(ConstData);
	ConstData *cd = new ConstData[size];
	Put<Double3>(geopos, dgp);
	Put<ConstData>(xin, *cd, size * sizeof(ConstData));
	for(ConstData *RESTR c = cd; c->x != 1000.0; c++)
		{
			dpi[0] = c->x;
			dpi[1] = c->y;
			dpi[2] = dgp[2];
			swe_azalt(jd, flags, dgp.d3, Pressure, Temperature, dpi.d3, D3.d3);
			c->x = /*180.0 -*/ D3[0];
			c->y = D3[1];
		}
	QByteArray xout = Get1<ConstData>(*cd, size * sizeof(ConstData));
	delete cd;
	return xout;
}

QByteArray AstroComputing::DBusConvert(double lon, double lat, double ecl)
{
    Convert(&lon, &lat, ecl);
    D3[0] = lon;
    D3[1] = lat;
    return Get1<Double3>(D3);
}

QString AstroComputing::DBusGetPlaName(int i)
{
    char buf[80];
    return swe_get_planet_name(i, buf);
}

double AstroComputing::SidTime(double jd)
{
    return swe_sidtime(jd);
}

int AstroComputing::Day_of_Week(double jd)
{
    return swe_day_of_week(jd);
}

QByteArray AstroComputing::DBusGetApsides(double julday, int index, int flags, int method)
{
    swe_nod_aps_ut(julday, index, flags, method, Ap.Nasc.d6, Ap.Ndsc.d6, Ap.Peri.d6, Ap.Aphe.d6, serr);
    return Get1<Apsides>(Ap);
}

double AstroComputing::GetSunStep(double jd)
{
    double array[6], d;
    swe_calc_ut(jd, Sun, 0, array, serr);
    d = array[0];
    swe_calc_ut(jd + 1.0, Sun, 0, array, serr);
    return array[0] - d;
}

double AstroComputing::Gauquelin(double julday, double geolat, double latitude, double longitude)
{
    double xp[2] = {longitude, latitude };
    return swe_house_pos(swe_sidtime(julday) * 15.0, geolat, GetObliquity(julday), 'G', xp, serr);
}

QByteArray AstroComputing::GetHousePos(int slot)
{
    Values& v = V[slot];
    double armc/* = swe_sidtime(v.Julday * 15.0)*/, xp[2], obl = GetObliquity(v.Julday), cusps[13], ascmc[10];
    const _AstroRestrictions& Arr = *Ar[slot];
    char h = HousesCodes[Arr.GetHouse()];
		auto f = [&](int i)
		{
			xp[0] = v.Get(i);
			xp[1] = v.Get(i, 1);
			double d = swe_house_pos(armc, v.Latitude, obl, h, xp, serr);
			if (d == 0.0)
				v.CSet(i, NOVALUE);
			else
			{
				double d1 = d;
				d -= 1.0;
				d *= 30.0;
				v.CSet(i, d);
			}
		};
    swe_houses_ex(v.Julday, 0, v.Latitude, v.Longitude, h, cusps, ascmc);
    armc = ascmc[2];
		Arr(f);
    return Get1<Values>(v);
}

void AstroComputing::SetExtraData(bool utc, QString swepaths, double temp, double press, uchar humid, int nbstars, QByteArray eit, QByteArray sti)
{
    UTC = utc;
		SWEPaths = swepaths;
		swe_set_ephe_path(SWEPaths.toUtf8().data());
		Temperature = temp;
		Pressure = press;
		Humidity = humid;
		NbStars = nbstars;
        Final_Star = First_Star + NbStars;
        Put<ExtraId>(eit, EId);
        Put<int[NBSTARS]>(sti, Sti, sizeof(int) * NbStars);
}

bool AstroComputing::Utc(DataComp& dc) const
{
    int day, month, year, hour, min, s, greg;
    double hms, ret[2];
    if (dc.j2g == 0.0)
    {
        aux = dc.julday;
        return true;
    }
    greg = (dc.julday >= dc.j2g) ? 1 : 0;
    if (UTC)
    {
        int hour, min;
        double sec;
        swe_jdet_to_utc(dc.julday, greg, &year, &month, &day, &hour, &min, &sec);
        s = int(sec);
    }
    else
    {
        swe_revjul(dc.julday, greg, &year, &month, &day, &hms);
        HMR(DecToDeg(hms), hour, min, s);
    }
    if (swe_utc_to_jd(year, month, day, hour, min, s, greg, ret, serr) == ERR)
        return false;
    dc.julday = ret[0];
    aux       = ret[1];
    return true;
}

void AstroComputing::ScanDir(int first, int second, QString scserver, uchar house, uchar dirtype, uchar statkey, double dval, int flags)
{
    int progr = 0, p;
    Values& v = V[first];
    const _AstroRestrictions &ar = *Ar[first], &ar1 = *Ar[second];
    //Ecl = -GetObliquity(v.Julday);
    Dir = new DirEngine(v, ar1, (enum House)house, (enum DirType)dirtype, (enum StatKey)statkey, dval, flags & CONVERSE);
#ifdef QT
    const QString s1 = ORGSKYLENDAR, s2 = scserver.section(' ', 1);
    OrgSkylendarScanclientInterface sci(s1 + ".scanclient"/*+ scserver.section(' ', 0, 0)*/, s2, QDBusConnection::sessionBus(), this);
    Sci = &sci;
#endif
    _AstroAspects aa(&ar1);
		auto f = [&](int i)
		{
			if(i == East_Point) return;
			if(!IfScan) return;
			SearchDir(i, ar1);
			p = (i * 100) / Max;
			if(p >= progr + 20)
			{
				progr = p;
				sci.Progress(p);
			}
		};
    Aa = &aa;
    IfScan = true;
    P;
    GetMax(ar);
    P;
    ar(f);
    delete Dir;
    sci.EndScan();
}

void AstroComputing::GetMax(const _AstroRestrictions& ar)
{
    Max = 0;
    auto f = [&](int i) { Max++; };
    ar(f);
}

void AstroComputing::SearchDir(int i, const _AstroRestrictions& ar1)
{
	auto f = [&](int j) { SearchDir(i, j, ar1); };
	ar1(f);
}

void AstroComputing::SearchDir(int i, int j, const _AstroRestrictions& ar1)
{
    if (i == Ascendant || i == Descendant || i == MC || i == FC) return;
    for (int k = Conjunction; k < Inconjunct; k++)
        if (!ar1.Asp(k))
        {
            if (i == j && k == Conjunction) continue;
            double time, arc = Dir->ArcDir((enum Objs)i, (enum Objs)j, (enum Aspects)k);
            if (arc == NOVALUE || ( !Dir->IfConverse() && arc < 0.0)) continue;
            time = Dir->ArcDate(arc);
            if (time != NOVALUE) Sci->GetDirection(i, 0.0, j, arc, k, time, arc < 0.0);
            if (k == Conjunction || k == Opposition) continue;
            arc = Dir->ArcDir((enum Objs)i, (enum Objs)j, (enum Aspects)k, true);
            if (arc == NOVALUE || ( !Dir->IfConverse() && arc < 0.0)) continue;
            time = Dir->ArcDate(arc);
            if (time != NOVALUE) Sci->GetDirection(i, 0.0, j, arc, k, time, arc < 0.0);
        }
    P;
    if (ar1.IfMinor())
        for (int k = Inconjunct; k < Antiscion; k++)
            if (!ar1.Asp(k))
            {
                double time, arc = Dir->ArcDir((enum Objs)i, (enum Objs)j, (enum Aspects)k);
                if (arc == NOVALUE || ( !Dir->IfConverse() && arc < 0.0)) continue;
                time = Dir->ArcDate(arc);
                if (time != NOVALUE) Sci->GetDirection(i, 0.0, j, arc, k, time, arc < 0.0);
                arc = Dir->ArcDir((enum Objs)i, (enum Objs)j, (enum Aspects)k, true);
                if (arc == NOVALUE || ( !Dir->IfConverse() && arc < 0.0)) continue;
                time = Dir->ArcDate(arc);
                if (time != NOVALUE) Sci->GetDirection(i, 0.0, j, arc, k, time, arc < 0.0);
            }
    P;
}


QByteArray AstroComputing::DBusHeliacal(double julday, QByteArray geopos, int id, int type)
{
    int pla = -1;
    Double3 dgp;
    double datm[4] = {Pressure, Temperature, Humidity, 0}, dobs[3] = {20, 1, 0 }, out[50];
    static const char* const names [] = { "sun", "venus", "mars", "mercur", "jupiter", "saturn", "uranus", "neptun", "moon" };
    static const enum Objs codes[] = { Sun, Venus, Mars, Mercury, Jupiter, Saturn, Uranus, Neptune, Moon };
    for (int i = 0; i <= 8; i++)
        if (codes[i] == id)
        {
            pla = i;
            break;
        }
    if (pla == -1)
    {
        D3.Init();
        return Get1<Double3>(D3);
    }
    Put<Double3>(geopos, dgp);
    int ret = swe_heliacal_ut(julday, dgp.d3, datm, dobs, CSC(char*, names[pla]), type, SE_HELFLAG_HIGH_PRECISION, D3.d3, serr);
    if (ret == ERR)
    {
        D3.Init();
    }
    return Get1<Double3>(D3);
}

API int Skyservice(int argc, char *argv[])
{
	// if(argc < 2)
	// 	{
	// 		std::cout << "This program shouldn't be executed alone." << std::endl;
	// 		return 1;
	// 	}
#ifdef QT
	QApplication qa(argc, argv);
	AstroComputing Ac(&qa);
	return qa.exec();
#endif
}

#undef E
