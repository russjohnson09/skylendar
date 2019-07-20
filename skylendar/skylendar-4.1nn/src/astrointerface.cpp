/***************************************************************************
 *   Copyright (C) 2004 by Christophe Gros                                 *
 *   skylendar@yahoo.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "astrointerface.h"
#include "astroprocess.h"
#include "astroutils.h"
#include "astroresources.h"
#include "astroutils.h"
#include "astrorestrictions.h"
#include "astrochartbase.h"
#include "astrochart.h"
#include "astroaspects.h"
#include "aspscanlist.h"
#include "stopscan.h"
#include "astromidpoints.h"
#include "astroephemeris.h"
#include "scanclient.h"
#include "astromainwindow.h"
#include "astrodirections.h"
#ifdef QT
#include <QProcess>
#include "scanclientadaptor.h"
#include "astrogetvaluesadaptor.h"
#endif
#include <iostream>
#include <unistd.h>

void OaPole(int slot, int i, double ecl, bool latitude, double* pole, double* oa, bool* eastern);

AstroInterface::AstroInterface(AstroString app, AstroString id) :
#ifdef QT
        OrgSkylendarSkyserviceInterface(app, id, QDBusConnection::sessionBus(), 0)
#endif
{
    ZoneInfoBuf[0] = 0;
}

AstroInterface::~AstroInterface()
{
    Kill();
}

AstroInterface* CreateInterface()
{
    qint64 pid;
    AstroInterface* aif;
		 QStringList arg;
		 int *sti = new int[NbStars];
     for(int i = 0; i < NbStars; i++)
       sti[i] = Asr->StaNames[i].Idx;
		 if(!QProcess::startDetached("skyservice", arg, QString(), &pid))
		 {
			 std::cout << "Starting skyservice failed" <<  std::endl;
        return nullptr;
		 }
		 AstroString as = AstroString("org.skyservice-") + pid;
		 QDBusConnectionInterface *bus = QDBusConnection::sessionBus().interface();
		 while(!bus->isServiceRegistered(as))
			 QThread::msleep(100);
		 aif = new AstroInterface(as, SKYSERVICE);
		 if (!aif || !aif->isValid()) return nullptr;
         aif->SetExtraData(Asr->UTC, Asr->SWEphems, Asr->Temperature, Asr->Pressure, Asr->Humidity, NbStars, Get1<ExtraId>(Asr->EId), Get1<int>(*sti, sizeof(int) * NbStars));
    aif->InitRestricts(Get1<_AstroRestrictions>(*SC(_AstroRestrictions*, Drs)));
		delete [] sti;
    return aif;
}


void AstroInterface::SetTZ(const char *file, bool)
{
    char buf[BUFSIZE];
    if (strcmp(file, ZoneInfoBuf))
    {
        strncpy(buf, Asr->ZPath, BUFSIZE);
        strncat(buf, file, BUFSIZE);
        //KDESetTZ(buf, set);
        if (file)
            strncpy(ZoneInfoBuf, file, BUFSIZE);
    }
}

void AstroInterface::SetRestrict(const AstroRestrictions* ar, int i)
{
    if (i < 0 || i >= NBDATA) return;
    const _AstroRestrictions& _ar = *ar;
    OrgSkylendarSkyserviceInterface::SetRestrict(Get1<_AstroRestrictions>(_ar), i);
}

void AstroInterface::GetError(AstroString& as)
{
    as = AstroString(DBusGetError());
}

void AstroInterface::RevJul(double jd, bool greg, unsigned char* day, unsigned char* month, short* year, double* hm)
{
    DateTime Dat;
    Put<DateTime>(DBusRevJul(jd, greg), Dat);
    *day = Dat.day;
    *month = Dat.month;
    *year = Dat.year;
    *hm = Dat.hm;
}

void AstroInterface::Azalt(double jd, const Double3& geopos, const Double3& xin, Double3& xout)
{
    Put<Double3>(DBusAzalt(jd, SE_ECL2HOR, Get1<Double3>(geopos), Get1<Double3>(xin)), xout);
}

void AstroInterface::Azalt(double jd, const Double3& geopos, const ConstData* pin, ConstData* pout)
{
	int size = CDSize(CSC(ConstData*, pin)) * sizeof(ConstData);
	QByteArray vout = DBusAzaltP(jd, 1 /*SE_EQU2HOR*/, Get1<Double3>(geopos), QByteArray::fromRawData(RC(const char*, pin), size));
		memcpy(pout, vout.constData(), size);
}

void AstroInterface::Convert(double* angle, double* dec, double ecl)
{
    Double3 d;
    Put<Double3>(DBusConvert(*angle, *dec, ecl), d);
    *angle = d[0];
    *dec = d[1];
}

void AstroInterface::GetApsides(double julday, int index, int flags, Apsides& apsides)
{
    Put<Apsides>(DBusGetApsides(julday, index, flags, 1), apsides);
}

const AstroString& AstroInterface::GetPlaName(int i, AstroString& as)
{
    as = AstroString(DBusGetPlaName(i));
    return as;
}

void AstroInterface::Heliacal(double julday, const Double3& geopos, enum Objs o, enum AspKind ak, Double3& xout)
{
    int type;
    switch (ak)
    {
    case HelRising:
        type = 1;
        break;
    case HelSetting:
        type = 2;
        break;
    case EveningFirst:
        type = 3;
        break;
    case MorningLast:
        type = 4;
        break;
    default:
        ;
    };
    Put<Double3>(DBusHeliacal(julday, Get1<Double3>(geopos), int(o), type), xout);
    P;
}

void Values::Set(int i, double d, bool r, double d1, double d2, double d3, double d4, double d5)
{
    if (i < 0 || i > (Final_Star + 1)) return;
    DataValues& v = Data[i];
    v.V[0] = d;
    v.V[1] = d1;
    v.V[2] = d2;
    v.V[3] = d3;
    v.V[4] = d4;
    v.V[5] = d5;
    v.Retro = r;
}

void Values::CSet(int i, double d, bool r)
{
    if (i < 0 || i > (Final_Star + 1)) return;
    double *v = Data[i].V;
    v[0] = d;
    Data[i].Retro = r;
}

AstroGetValues::AstroGetValues()
{
    Ac = nullptr;
    new ValsAdaptor(this);
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerObject("/Vals", this);
		dbus.interface()->registerService(QString(ORGSKYLENDAR) + ".vals");
}

AstroGetValues::~AstroGetValues()
{
}

int AstroGetValues::NbCharts()
{
    return Ahl->Count();
}

int AstroGetValues::NbRings()
{
    return Ac ? Ac->Acb->Count(): 0;
}

QString AstroGetValues::GetRingType(int i)
{
    if (Ac)
    {
        const AstroObjs* ao = (*Ac)[i];
        if (ao)
        {
            if (ao->GetSubType() == Single) return "Sgl";
            return ao->GetSubTypeShortName();
        }
    }
    return "";
}

bool AstroGetValues::IfObj(int ring, QString obj)
{
    enum Objs o = GetObjId(SC(const AstroString&, obj));
    if (o < 0) return false;
    return GetRingType(ring) != "" && (*(*Ac)[ring]) == o;
}

QString AstroGetValues::GetChartName()
{
    AstroString as;
    if (Ac)
    {
        as = !(*Ac) ? Ac->Acb->GetTitle(as) : "";
        return as;
    }
    return "";
}

bool AstroGetValues::LockChart(int i)
{
    if (i < 0 || i > Ahl->Count() -1) return false;
    AstroChart* ac = (*Ahl)[i];
    if (!ac->IfLocked())
    {
        Ac = ac;
        Ac->LockChart();
        return true;
    }
    return false;
}

void AstroGetValues::UnlockChart()
{
    if (Ac)
    {
        Ac->UnlockChart();
        Ac = nullptr;
    }
}

double AstroGetValues::GetVal(int ring, QString obj, int val)
{
    if (!Ac->IfLocked()) return -1;
    auto o = GetObjId(SC(const AstroString&, obj));
    if (o < 0) return NOVALUE;
    const AstroObjs* ao = Ac ? (*Ac)[ring] : 0;
    return ao ? (*(*ao)[o])[val] : NOVALUE;
}

double AstroGetValues::GetLong(int ring, QString obj)
{
    if (!Ac->IfLocked()) return -1;
    auto o = GetObjId(SC(const AstroString&, obj));
    if (o < 0) return NOVALUE;
    const AstroObjs* ao = Ac ? (*Ac)[ring] : 0;
    return ao ? (*ao) * o  : NOVALUE;
}

int AstroGetValues::NbAspects()
{
    if (!Ac->IfLocked()) return -1;
    auto afal = Ac ? CSC(AstroFoundAspectsList*, Ac->Acb->GetAspectsList()) : 0;
    return afal ? afal->Count() : 0;
}

QString AstroGetValues::GetAspectFound(const AspectFound& af)
{
    AstroObjs* ao = nullptr;
    if (!Ac->IfLocked()) return "";
    if (Ac)
        for (int j = 0; j < NBDATA; j++)
            if ((*Ac)[j])
            {
                ao = (*Ac)[j];
                break;
            }
    if (ao)
    {
        AstroString as1, s, a, as;
        if (af.Oc != Undefined_Obj)
        {
            if (af.Oc == ARABPART)
                Sprintf("\"%a\" %a %a %s", &as, Asr->PartsNames[af.Oa], Asr->AspectShortNames[af.Asp], &((*ao) < af.Ob), ((*(*ao)[af.Ob]).Retro ? ". " : " "));
            else
                as = ((*ao) < af.Oa) + "/" + ((*ao) < af.Oc) + " " + *Asr->AspectShortNames[af.Asp] + " "
                     + ((*ao) < af.Ob) + ((*(*ao)[af.Ob]).Retro ? ". " : " ");
        }
        else
            as = ((*ao) < af.Oa) + ((*(*ao)[af.Oa]).Retro ? ". " : " ") +	*Asr->AspectShortNames[af.Asp] + " "
                 + ((*ao) < af.Ob) + ((*(*ao)[af.Ob]).Retro ? ". " : " ");
        switch (af.AspectSide)
        {
        case Exact:
            s = i18n("Exact");
            break;
        case Applying:
            s = i18n("Applying");
            break;
        case Separating:
            s = i18n("Separating");
            break;
        default:
            ;
        };
        switch (af.GetAccuracy())
        {
        case Exact:
            a = i18n("Exact");
            break;
        case Good:
            a = i18n("Good");
            break;
        case Medium:
            a = i18n("Medium");
            break;
        case Poor:
            a = i18n("Poor");
            break;
        default:
            ;
        }

        return as + Sprintf("%f (%a) %a", &as1, af.ExtraOrb, &a, &s);
    }
    return "";
}

QString AstroGetValues::GetAspect(int i)
{
    if (!Ac || !Ac->IfLocked()) return "";
    auto afal = Ac ? CSC(AstroFoundAspectsList*, Ac->Acb->GetAspectsList()) : nullptr;
    const AspectFound* af = afal ? (*afal)[i - 1] : 0;
    return af ? GetAspectFound(*af) : "";
}

int AstroGetValues::NbMPAspects()
{
    if (!Ac || !Ac->IfLocked()) return -1;
    auto afal = Ac ? CSC(AstroFoundAspectsList*, Ac->Acb->GetAspectsList()) : nullptr;
    return afal ? (~(*afal)).Count() : 0;
}

QString AstroGetValues::GetMPAspect(int i)
{
    if (!Ac->IfLocked()) return "";
    auto afal = Ac ? CSC(AstroFoundAspectsList*, Ac->Acb->GetAspectsList()) : nullptr;
    if (afal)
    {
        AlAf& asmp = ~(*afal);
        AspectFound* af = asmp[i - 1];
        return af ? GetAspectFound(*af) : "";
    }
    return "";
}

int AstroGetValues::SearchAspect(QString obj1, QString asp, QString obj2, int start, QString obj3)
{
    if (!Ac->IfLocked()) return -1;
    auto afal = Ac ? CSC(AstroFoundAspectsList*, Ac->Acb->GetAspectsList()) : nullptr;
    if (!afal) return -1;
    auto o1 = GetObjId(SC(const AstroString&, obj1)), o2 = GetObjId(SC(const AstroString&, obj2)), o3 = GetObjId(SC(const AstroString&, obj3));
    if ((!obj1.isEmpty() && o1 == Undefined_Obj) || (!obj2.isEmpty() && o2 == Undefined_Obj) || (!obj3.isEmpty() && o3 == Undefined_Obj)) return 0;
    AlAf& asmp = ~(*afal);
    bool mp = (obj3 != "" && o3 != ARABPART);
    if (o3 == ARABPART && (o1 >= 0 && o1 != Undefined_Obj)) return 0;
    if (o1 < 0) o1 = (enum Objs)-o1;
    AspectFound* af = start > 0 ? (mp ? asmp[start - 1] : (*afal)[start - 1]) : 0;
    enum Aspects n = Unknown_Aspect;
    for (int j = 0; j < Unknown_Aspect; j++)
        if (*Asr->AspectShortNames[j] == asp) {
            n = (enum Aspects)j;
            break;
        }
    const AspectFound* af1 = mp ? afal->Search(o2, n, o1, af, true, mp, o3) : afal->Search(o1, n, o2, af, true, mp, o3);//Undefined_Obj);
    if (af1)
        return (mp ? asmp.indexOf(CSC(AspectFound*, af1)) : afal->indexOf(CSC(AspectFound*, af1))) + 1;
    return 0;
}

double AstroGetValues::GetMidPoint(QString obj1, QString obj2)
{
    AstroString as;
    if (!Ac->IfLocked()) return -1.0;
    auto o1 = GetObjId(SC(const AstroString&, obj1)), o2 = GetObjId(SC(const AstroString&, obj2));
    if (o1 == Undefined_Obj || o2 == Undefined_Obj) return NOVALUE;
    if (Ac)
    {
        const AstroMidPoints& amp = *Ac->Acb->GetMidPoints();
        return o1 < amp.GetX() && o2 < amp.GetY() ? amp.Get(o1, o2) : NOVALUE;
    }
    return NOVALUE;
}

static AstroString GetValStr(double a)
{
    int s, deg, min, sec;
    AstroString as;
    bool r = a < 0.0;
    a = fabs(a);
    s = (int)a / 30;
    a -= (double)(s * 30);
    Hmr(DecToDeg(a), deg, min, sec, true);
    if (deg < 10)
        as = " ";
    as += deg;
    as += (*Asg < s);
    /*a = (double)min * 60.0 / 100.0 + ROUND;
    min = (int)a;*/
    if (min < 10)
        as += "0";
    as += min;
    if (r) as += "R";
    return as;
}

QString AstroGetValues::GetEphemLine(int day, int month, int year)
{
    auto ae = SC(AstroEphemeris*, Ac->Acb);
    if (!ae || (Ac && !Ac->IfLocked())) return "";
    auto el = ae->GetEphemLine(day, month, year);
    if (!el) return "";
    AstroString as;
    for (int i = 0; i < 12; i++)
    {
        as += GetValStr(el->val[i]) + " ";
    }
    return as;
}

double AstroGetValues::GetPart(int i, int ring)
{
    if (Ac && !Ac->IfLocked()) return -1.0;
    if (!(*Ac)[ring]) return NOVALUE;
    return (*Ac)[ring]->Part(i);
}

QString AstroGetValues::GetDecan(QString obj, int ring)
{
    auto o = GetObjId(SC(const AstroString&, obj));
    if ((Ac && !Ac->IfLocked()) || o == Undefined_Obj) return "";
    const AstroObjs* ao = Ac ? (*Ac)[ring] : nullptr;
    return ao ? ObjShortName(ao->GetDecan(o))  : "";
}

QString AstroGetValues::GetTerm(QString obj, int ring)
{
    auto o = GetObjId(SC(const AstroString&, obj));
    if (o == Undefined_Obj || (Ac && !Ac->IfLocked())) return "";
    const AstroObjs* ao = Ac ? (*Ac)[ring] : nullptr;
    return ao ? ObjShortName(ao->GetTerm(o))  : "";
}

bool AstroGetValues::TFReq(QString s)
{
    if (Ac->GetCt() != TensorFlow || (Ac && !Ac->IfLocked())) return false;
    s = "SELECT Idx FROM Data WHERE " + s;
    auto tfc = DC(TensorFlowChart*, Ac->Acb);
    if(tfc)
    {
        if(!Arq.Exec(s.toLocal8Bit().data()) || !Arq.isValid()) return false;
        AstroObjs& a = *(*tfc)[0];
        return a.DbFetch(Arq.GetInt("Idx"));
        tfc->PostRecompute();
    }
    return false;
}


bool AstroGetValues::TFNext()
{
  if ((Ac->GetCt() != TensorFlow) || (Ac && !Ac->IfLocked())) return false;
    auto tfc = DC(TensorFlowChart*, Ac->Acb);
    if(tfc)
    {
      if(!Arq.Next()) return false;
      AstroObjs& a = *(*tfc)[0];
      if(!a.DbFetch(Arq.GetInt("Idx"))) return false;
      tfc->PostRecompute();
      return true;
    }
  return false;
}

int AstroGetValues::TFGetAsp(int i)
{
    if ((Ac->GetCt() != TensorFlow) || (Ac && !Ac->IfLocked())) return -1;
    auto afal = Ac ? CSC(AstroFoundAspectsList*, Ac->Acb->GetAspectsList()) : nullptr;
    const AspectFound* af = afal ? (*afal)[i - 1] : nullptr;
    return af ? (af->Oa +1000 *af->Asp + 1000* af->Ob) : -1;
}

int Values::InHouse(int i, short threshold, double *f) const
{
    double x = Data[i][0], x1, x2, x3;
    for (int j = 0; j < 12; j++)
    {
        x1 = Data[j + House_1][0];
        x2 = Data[j + House_1 + 1][0];
        if (x2 < x1)
        {
            x2 += 360.0;
            x3 = x + 360.0;
            if (x3 >= x1 && x3 <= x2)
                x = x3;
        }
        if (x >= x1 && x <= x2)
        {
            if (f)
                *f = 1000.0 * (x - x1) / (x2 - x1);
            j++;
            if(x >= x2 - threshold) j++;
            if(j > 12) j = 1;
            return j;
        }
    }
    return 0;
}

void Values::PutInHouse(int index, int house, double f)
{
    double x1, x2;
    x1 = Data[house + House_1 - 1][0];
    x2 = Data[house + House_1][0];
    if (x2 < x1)
    {
        x2 += 360.0;
    }
    f = Normalize(x1 + (f * (x2 - x1) / 1000.0));
    Data[index].V[0] = f;
}

ScanClient::ScanClient(QObject* parent, AspScan* asc, int id) : QObject(parent)
{
    AstroString as = SCANCLIENT;
    Asc = asc;
    Ad = nullptr;
    Id = id;
    as += Id;
    new ScanclientAdaptor(this);
    QDBusConnection::sessionBus().registerObject(as, this);
		if(!QDBusConnection::sessionBus().interface()->isServiceRegistered(QString(ORGSKYLENDAR) + ".scanclient").value())
			QDBusConnection::sessionBus().interface()->registerService(QString(ORGSKYLENDAR) + ".scanclient");
		
}

ScanClient::ScanClient(QObject* parent, AstroDir* ad, int id) : QObject(parent)
{
    AstroString as = SCANCLIENT;
    Ad = ad;
    Asc = nullptr;
    Id = id;
    as += Id;
    new ScanclientAdaptor(this);
    QDBusConnection::sessionBus().registerObject(as, this);
		if(!QDBusConnection::sessionBus().interface()->isServiceRegistered(QString(ORGSKYLENDAR) + ".scanclient").value())
			QDBusConnection::sessionBus().interface()->registerService(QString(ORGSKYLENDAR) + ".scanclient");
}

ScanClient::~ScanClient()
{
    AstroString as = SCANCLIENT;
    as += Id;
    QDBusConnection::sessionBus().unregisterObject(as);
}

void ScanClient::GetAspect(int i, double ipos, int j, double jpos, int asp, double date, bool ap)
{
#ifdef _OPENMP
# pragma omp single
#endif
    Asc->DrawDate(i, ipos, j, jpos, asp, date, ap);
}

void ScanClient::GetMPAspect(int i, int j, double pos, int k, double kpos, int aspect, double date)
{
#ifdef _OPENMP
# pragma omp single
#endif
    Asc->DrawMPDate(i, j, pos, k, kpos, aspect, date);
}

void ScanClient::GetDirection(int i, double ipos, int j, double jpos, int aspect, double date, bool converse)
{
#ifdef _OPENMP
# pragma omp single
#endif
    Ad->DrawDir(i, ipos, j, jpos, aspect, date, converse ? ExCDir : ExDir);
}

void ScanClient::EndScan()
{
#ifdef QT
    if (Amw)
    {
        auto ae = new AstroEvent(1234, Asc ? SC(ParamListBase*, Asc) : SC(ParamListBase*, Ad));
        qApp->postEvent(Amw, ae);
    }
    else
    {
        if (Asc)
            Asc->Finish();
        else
            Ad->Finish();
    }
#endif
}

void ScanClient::GetRetro(int i, double ipos, double date)
{
#ifdef _OPENMP
# pragma omp single
#endif
    Asc->DrawChange(i, ipos, date);
}

void ScanClient::Progress(int i)
{
    if (Asc)
        emit Asc->Progress(i);
    else
        emit Ad->Ss->Set(i);
}

void ScanClient::GetSignTrans(int i, int sign, double date)
{
#ifdef _OPENMP
# pragma omp single
#endif
    Asc->DrawSignTrans(i, sign, date);
}

