/***************************************************************************
                          astroobjs.cpp  -  description
                             -------------------
    begin                : Sat Sep 23 2000
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

#include "astroobjs.h"
#include "astrochart.h"
#include "astroresources.h"
#include "astrographics.h"
#include "astrotransfer.h"
#include "astroconstellations.h"

#define SCO(i) (*this)() / (i)
#define SCORE(obj, sco) Rank[(af->Oa != obj) ? af->Oa : af->Ob].score += (af->GetAccuracy() > Medium) ? (SCO(sco) / 2) : SCO(sco)
#define STEST(obj1, aspect, sco) for(const AspectFound* af = afal->Search(obj1, aspect); af; af = afal->Search(obj1, aspect, Undefined_Obj, af, true)) SCORE(obj1, sco)

AstroObjs::AstroObjs(AstroInterface* aif) : AstroData(aif), ChartParams(*Asr)
{
    ID = qrand();
}

AstroObjs::AstroObjs(AstroInterface *aif, AstroChart *ac, int ring) : AstroData(aif), ChartParams(*ac->Cbp)
{
    Ac = ac;
    Ring = ring;
    ID = qrand();
}

AstroObjs::AstroObjs(const AstroData& ad, AstroChart* ac, int ring, enum ChartSubType cst) : AstroData(ad), ChartParams(*ac->Cbp)
{
    Ac = ac;
    Ring = ring;
    Cst = cst;
    ID = qrand();
    Recompute();
}

void AstroObjs::SetCms(enum CompModes cms)
{
    Cms = cms;
    Recompute();
}

AstroObjs::~AstroObjs()
{
}

AstroChartBase* AstroObjs::GetAcb() const
{
    return Ac->Acb;
}

/** Returns the string value of the objet index, i.e. "12Cap45" */
bool AstroObjs::GetValStr(int index, AstroString& as) const
{
    double a;
    int s, deg, min, sec;
    as = "";
    if (index < Sun || index > Final_Star || !(*Ar == index))
    {
        as = *Asr->ObjError;
        return false;
    }
    a = Vals.Get(index);
    s = (int)a / 30;
    a -= (double)(s * 30);
    HMR(a, deg, min, sec);
    if (deg < 10)
        as = " ";
    as += deg;
    as += (*Asg < s);
    a = (double)min * 60.0 / 100.0 + ROUND;
    min = (int)a;
    if (min < 10)
        as += "0";
    as += min;
    as += Vals.Retro(index) ? " R" : "  ";
#ifndef QT
    as += '\0';
#endif
    return true;
}

/** Returns the object name */

const AstroString& AstroObjs::GetSubTypeName() const
{
    if (Cst < NoSt || Cst > Last_SubType)
        return *Asr->SubTypesNames[NoSt];
    return *Asr->SubTypesNames[Cst];
}

const AstroString& AstroObjs::GetSubTypeShortName() const
{
    if (Cst < NoSt || Cst > Last_SubType)
        return *Asr->SubTypesShortNames[NoSt];
    return *Asr->SubTypesShortNames[Cst];
}


void AstroObjs::SetRestrict(AstroRestrictions* ar)
{
    Ar = ar;
    Aif->SetRestrict(ar, Ring);
}

enum Elements AstroObjs::GetObjElement(int index) const
{
    if (index >= Sun && index <= Last_Planet)
        return Asr->ElemPla[index];
    if (index >= Ascendant && index <= House_12)
        return Asr->ElemHouses[index - Ascendant];
    return Undefined_Element;
}

const AstroColor& AstroObjs::GetObjColor(int index) const
{
    if (index >= Chiron && index <= Vesta)
        return COL[Asr->AsteroColor];
    if (index >= First_Extra && index <= Asr->LastExtra)
        return COL[Asr->ExtraColor];
    switch (GetObjElement(index))
    {
    case Fire  :
        return COL[Asr->FireColor];
    case Air   :
        return COL[Asr->AirColor];
    case Water :
        return COL[Asr->WaterColor];
    case Earth :
        return COL[Asr->EarthColor];
    default    :
        return COL[Asr->OtherColor];
    }
}

char AstroObjs::GetObjChar(int index) const
{
    if (index > (int)strlen(PlaChars))
        return 0;
    if (EuropUran && index == Uranus)
        return ALTURA;
    if (EuropPlut && index == Pluto)
        return ALTPLU;
    return PlaChars[index] != ' ' ? PlaChars[index] : 0;
}

void AstroObjs::CountFAWE(int* fire, int* air, int* water, int* earth) const
{
	enum Signs s;
	*fire = *air = *water = *earth = 0;
	for (int i = Sun; i <= Ar->LastExtra; i++)
		if (*this == i)
			switch (s = Asg->GetSign(*this * i))
			{
			case Aries:
			case Leo:
			case Sagittarius:
				(*fire)++;
				break;
			case Capricorn:
			case Taurus:
			case Virgo:
				(*earth)++;
				break;
			case Cancer:
			case Scorpio:
			case Pisces:
				(*water)++;
				break;
			case Libra:
			case Aquarius:
			case Gemini:
				(*air)++;
				break;
			default:;
			}
}

void AstroObjs::CountCfm(int *cardinal, int *fixed, int *mutab) const
{
    enum Signs s;
    *cardinal = *fixed = *mutab = 0;
    for (int i = Sun; i <= Ar->LastExtra; i++)
        if (*this == i)
            switch (s = Asg->GetSign(*this * i))
            {
            case Aries:
            case Cancer:
            case Libra:
            case Capricorn:
                (*cardinal)++;
                break;
            case Taurus:
            case Leo:
            case Scorpio:
            case Aquarius:
                (*fixed)++;
                break;
            case Gemini:
            case Virgo:
            case Sagittarius:
            case Pisces:
                (*mutab)++;
                break;
            default:
                ;
            }
}

int AstroObjs::InHouse(int i, double *f) const
{
    if (!(*this == i)) return 0;
    return Vals.InHouse(i, Ar->Threshold, f);
}

void AstroObjs::PutInHouse(int index, int house, double f)
{
    if (!(*this == index)) return;
    Vals.PutInHouse(index, house, f);
}

void AstroObjs::CountAsc(int *angular, int *succeedent, int *cadent) const
{
    int j;
    *angular = *succeedent = *cadent = 0;
    for (int i = Sun; i <= Asr->LastExtra; i++)
        if (*this == i)
            switch (j = InHouse(i, 0))
            {
            case 1:
            case 4:
            case 7:
            case 10:
                (*angular)++;
                break;
            case 2:
            case 5:
            case 8:
            case 11:
                (*succeedent)++;
                break;
            case 3:
            case 6:
            case 9:
            case 12:
                (*cadent)++;
                break;
            }
}

bool AstroObjs::Compute()
{
    enum ChartType ct = NullChart;
    if (GetAcb()) ct = GetAcb()->GetCt();
    Dc.julday = GetJd();
    if (Dc.julday >= MAXJD || Dc.julday <= MINJD) return false;
    Dc.ring = Ring;
    if (GetAcb())
    {
        Dc.first = &GetAcb()->GetRef() ? GetAcb()->GetRef().Ring : Ring;
        Dc.afirst = &GetAcb()->GetRef(true) ? GetAcb()->GetRef(true).Ring : NOAFIRST;
    }
    Dc.ct = Ac ? Ac->Ct : ct;
    Dc.cst = Cst;
    Dc.latitude  = Latitude.Get(true);
    Dc.longitude = Longitude.Get(true);
    Dc.altitude  = Altitude;
    Dc.extraflags = DefSweFlags;
    Dc.gethouses = (Accuracy > -1 && ct != Gauquelin);
    const AstroObjs* a = (*Ac)[Dc.first];
    Dc.gethousesfirst = a ? (a->Accuracy > -1) : Dc.gethouses;
    Dc.angle = Angle;
    Dc.gauquelin = (Cms == Gauq);
    Dc.aref = ARef;
    Dc.j2g = Asr->UTC ? GetJ2g() : 0.0;
    return Aif->Recompute(Get1<DataComp>(Dc));
}

enum Objs AstroObjs::MasterOf(enum Objs o, bool co_ruler) const
{
    const struct Ruling& r = GetRulers(Asg->GetSign((*this) * o));
    return co_ruler ? r.Co_Ruler : r.Ruler;
}

void AstroObjs::SetSubChart(enum ChartSubType cst)
{
    Cst = cst;
    Dc.first = (GetAcb() && &GetAcb()->GetRef()) ? GetAcb()->GetRef().Ring : Ring;
}

void AstroObjs::SetConstel(bool b)
{
    if(b)
		{
			IfConstell = true;
			if(!Act)
				Act = new AstroConstellations(this);
			Act->Compute();
		}
		else
		{
			delete Act;
			IfConstell = false;
		}
			
}

bool AstroObjs::Recompute()
{
    bool b = Compute();
    if (!b)
    {
        AstroString as, buf;
        Aif->GetError(as);
        AstroMessage(Sprintf(i18n("Error: the computing server returned\n\n%a"), &buf, &as));
        return false;
    }
		switch(Cms)
		{
		  case HousePos: Put<Values>(Aif->GetHousePos(Ring), Vals); break;
          case Local: Put<Values>(Aif->GetValues(Ring), Vals); if(Act && IfConstell) Act->Compute(); break;
          default: Put<Values>(Aif->GetValues(Ring), Vals);
		}
    return true;
}

double AstroObjs::GetRiseSet(enum Objs o, enum ConjAngles ca) const
{
    double jd = GetJd(), r = jd - floor(jd);
    jd = (r >= 0.5) ? floor(jd) : floor(jd) -0.5;
    return Aif->GetRiseSet(jd, o, Latitude.Get(), Longitude.Get(), Altitude, ca);
}

int AstroObjs::SabianDegree(enum Objs o) const
{
    double d = Vals.Get(o);
    return int(floor(d)) + 1;
}

extern "C"
{
    static int compar(const void *v1, const void *v2)
    {
        const struct AstroObjs::PlanetRank *pr1 = (const struct AstroObjs::PlanetRank*)v1,
                            *pr2 = (const struct AstroObjs::PlanetRank*)v2;
        if (pr1->score > pr2->score)
            return -1;
        else if (pr1->score == pr2->score)
            return 0;
        else
            return 1;
    }
}

bool AstroObjs::GetPlanetsRank(AstroFoundAspectsList* afal)
{
    struct RuledSigns r;
    if (!afal)
    {
        IfRank = false;
        return true;
    }
    for (int i = Sun; i <= Pluto; i++)
    {
        Rank[i].planet = (enum Objs)i;
        Rank[i].score  = 0;
    }
    STEST(Ascendant, Conjunction, 0);
    STEST(MC,   Conjunction, 0);
    STEST(Descendant, Conjunction, 1);
    STEST(FC,   Conjunction, 1);
    STEST(Sun, Conjunction, 0);
    STEST(North_Node, Conjunction, 1);
    STEST(South_Node, Conjunction, 3);
    STEST(Black_Moon, Conjunction, 6);
    const AspectFound* af = afal->Search(Sun, Conjunction, Mercury);
    if (af && af->Orb > 2.0) Rank[Mercury].score -= SCO(0);
    const AspectFound* af1 = afal->Search(Sun, Conjunction, Venus);
    if (af1 && af1->Orb > 2.0) Rank[Venus].score -= SCO(0);
    const enum Objs masc = MasterOf(Ascendant), cmasc = MasterOf(Ascendant, true), mmc = MasterOf(MC), cmmc = MasterOf(MC, true);
    STEST(masc, Conjunction, 4);
    STEST(cmasc, Conjunction, 4);
    STEST(mmc, Conjunction, 4);
    STEST(cmmc, Conjunction, 4);
    Rank[masc].score += SCO(2);
    Rank[cmasc].score += SCO(2);
    Rank[mmc].score += SCO(2);
    Rank[cmmc].score += SCO(2);
    for (int i = Sun; i <= Pluto; i++)
    {
        const enum Objs o = (enum Objs)i;
        GetRuled(r, o);
        enum Signs s = Asg->GetSign(Vals.Get(i));
        if (s == r.Ruled)    Rank[i].score += SCO(3);
        if (s == r.Co_Ruled) Rank[i].score += SCO(3);
        if (s == r.Fall)     Rank[i].score -= SCO(3);
        if (s == r.Co_Fall)  Rank[i].score -= SCO(3);
        if (s == r.Exalt)    Rank[i].score += SCO(7);
        if (s == r.Debil)    Rank[i].score -= SCO(7);
        Rank[MasterOf(o)].score += SCO(5);
        STEST(o, Unknown_Aspect, 6);
        if (MasterOf(Sun) == o) Rank[i].score += SCO(0);
        if (GetDecan(o) == o) Rank[i].score += SCO(8);
        if (GetTerm(o) == o)  Rank[i].score += SCO(8);
    }
    int l = 10000;
    for (int i = Sun; i <= Pluto; i++)
        if (Rank[i].score  < l) l = Rank[i].score;
    if (l < 0)
    {
        for (int i = Sun; i <= Pluto; i++)
            Rank[i].score -= l;
    }
    qsort(Rank, 10, sizeof(struct PlanetRank), compar);
    IfRank = true;
    return true;
}

enum Objs AstroObjs::GetPlaHour() const
{
    extern const enum Objs* DaysMasters;
    extern const enum Objs* OrdMastHours;
    double l = Longitude.Get(true) / 360.0, jd = Julday + l;
    if (int(CurrJd) != int(Julday))
    {
        CurrJd = Julday;
        CurrSunRise = GetRiseSet(Sun, Rising) + l;
    }
    int day = Aif->Day_of_Week(Julday), idx, j = 0;
    enum Objs m = DaysMasters[day];
    for (int i = 0; i < 7; i++)
        if (OrdMastHours[i] == m)
        {
            idx = i;
            break;
        }
    for (double d = CurrSunRise; d < CurrSunRise + 1.0; d += (1.0 / 24.0), j++)
        if (jd >= d && jd < d + (1.0 / 24.0))
            return OrdMastHours[(idx + j) % 7];
    return Undefined_Obj;
}

double AstroObjs::Part(int i) const
{
    if (i < 0 || i >= Asr->NbParts) return NOVALUE;
    return CalcPart(Asr->Parts[i], Vals, *Ar);
}

enum SubTypeState AstroObjs::GetState() const
{
    const AstroChartBase* acb = Ac->Acb;
    if (acb == nullptr) return Unknown_State;
    if (acb->GetRef().Ring == Ring)
        return Master;
    else if (&acb->GetRef(true) && acb->GetRef(true).Ring == Ring)
        return AMaster;
    else if (ARef)
        return ASlave;
    return Slave;
}

enum Objs AstroObjs::GetTerm(enum Objs o) const
{
	  extern const SignTerms* TermsVector;
    double a = Vals.Get(o);
    int deg = a;
    deg %= 30;
    deg++;
    enum Signs s = Asg->GetSign(a);
    const SignTerms& t = TermsVector[s];
    if (deg >= 1 && deg <= t[0].deg) return t[0].o;
    for (int i = 0; i < 4; i++)
        if (deg > t[i].deg && deg <= t[i + 1].deg) return t[i + 1].o;
    return Undefined_Obj;
}

enum Objs AstroObjs::GetDecan(enum Objs o) const
{
    extern const enum Objs* DecansVector;
    return DecansVector[int(floor(Vals.Get(o) / 10.0))];
}
