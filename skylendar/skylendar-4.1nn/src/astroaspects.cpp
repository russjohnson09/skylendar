/***************************************************************************
                          astroaspects.cpp  -  description
                             -------------------
    begin                : Mon Apr 30 2001
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

#include "astroaspects.h"
#include "astroresources.h"
#include "astroobjs.h"
#include "astromidpoints.h"

#define INC(i) i = (enum Objs)(i + 1)

_AstroAspects::_AstroAspects(const _AstroRestrictions* ar)
{
    Asprst   = CSC(AspectRestrictions*, ar->Asprst);
    Restr    = CSC(Rest*, ar->Restr);
    IsMinor  = ar->IfMinor();
    MPOrbSub = ar->MPOrbSub;
}

AstroAspects::AstroAspects(AstroRestrictions* ar) : _AstroAspects(SC(_AstroRestrictions*, ar))
{
    AspChars = CSC(char *, ASPCHARS);
}

enum Aspects _AstroAspects::IsAspect(enum Objs oa, const Values& a,
                                     enum Objs ob, const Values& b, int flags) const
{
    double orb;
    double angle, aasp;
    const bool nn = &a == &b && ((oa == North_Node && ob == South_Node) || (oa == South_Node && ob == North_Node));
    const double angle_a = a.Get(oa), angle_b = b.Get(ob), fa = fabs(angle_a - angle_b);
    if (angle_a == NOVALUE || angle_b == NOVALUE) return Unknown_Aspect;
    for (int i = Conjunction; i <= Last_Major; i++)
    {
        orb = Asprst[i].Orb + Restr[oa].OrbAdd + Restr[ob].OrbAdd;
        if (orb <= 0.0) continue;
        angle = fa;
        if (angle - orb > 180.0)
            angle = 360.0 - angle;
        aasp = (*this) * (enum Aspects)i;
        if (nn && i == Opposition) continue;
        if ((angle < aasp + orb) && (angle > aasp - orb) && (*this) == (enum Aspects)i)
            return (enum Aspects)i;
    }
    if (IsMinor)
    {
        for (int i = First_Minor; i < Unknown_Aspect; i++)
        {
            orb = Asprst[i].Orb;
            angle = fa;
            if (angle - orb > 180.0)
                angle = 360.0 - angle;
            aasp = (*this) * (enum Aspects)i;
            if ((angle < aasp + orb) && (angle > aasp - orb) && (*this) == (enum Aspects)i)
                return (enum Aspects)i;
        }
    }
    return Unknown_Aspect;
}

void _AstroAspects::IsExtraAspect(enum Objs oa, const Values& a,
                                  enum Objs ob, const Values& b, int flags, float* results) const
{
    double orb;
    const double angle_a = a.Get(oa), angle_b = b.Get(ob);
    bool para = (*this) == Parallel, apara = (*this) == Antiparallel, anti = (*this) == Antiscion, canti = (*this) == Contra_Antiscion;
    if (angle_a == NOVALUE || angle_b == NOVALUE) return;
    for (int i = First_Minor; i < Unknown_Aspect; i++)
    {
        orb = Asprst[i].Orb;
        if (orb <= 0.0) continue;
        if ((i == Parallel && para) || (i == Antiparallel && apara))
        {
            const double pa =  a.Get(oa, 1), pb = b.Get(ob, 1), pab = pa * pb, dp = fabs(fabs(pa) - fabs(pb));
            bool parcond = (oa <= Pluto || oa == Black_Moon || (oa >= Chiron && oa <= Vesta) || (oa >= First_Extra && oa <= Asr->LastExtra) || oa >= First_Star) && (ob <= Pluto || ob == Black_Moon || (ob >= Chiron && ob <= Vesta) || (ob >= First_Extra && ob <= Asr->LastExtra) || ob >= First_Star);
            if (i == Parallel && pab >= 0.0 && parcond && dp <= orb)  results[0] = dp;
            if (i == Antiparallel && pab < 0.0 && parcond && dp <= orb) results[1] = dp;
        }
        if ((i == Antiscion && anti) || (i == Contra_Antiscion && canti))
        {
            double d = 90.0 - angle_a;
            d = angle_a + 2.0 * d;
            d = fabs(angle_b - d);
            if (d <= orb) results[2] = d;
            d = 270.0 - angle_a;
            d = angle_a + 2.0 * d;
            d = fabs(angle_b - d);
            if (d <= orb) results[2] = d;
            if (fabs(360.0 - angle_b - angle_a) <= orb)  results[3] = fabs(360.0 - angle_b - angle_a);

        }
    }
}

enum Aspects _AstroAspects::IsAspect(float mp, enum Objs ob, const Values& b, int flags) const
{
    double orb;
    double angle, aasp;
    const double angle_a = mp, angle_b = b.Get(ob), fa = fabs(angle_a - angle_b);
    if (angle_a == NOVALUE || angle_b == NOVALUE) return Unknown_Aspect;
    for (int i = Conjunction; i <= Last_Major; i++)
    {
        if (Asprst[i].Rest) continue;
        orb = Asprst[i].Orb + MPOrbSub + Restr[ob].OrbAdd;
        if (orb <= 0.0) continue;
        angle = fa;
        if (angle - orb > 180.0)
            angle = 360.0 - angle;
        aasp = (*this) * (enum Aspects)i;
        if ((angle < aasp + orb) && (angle > aasp - orb) && (*this) == (enum Aspects)i)
            return (enum Aspects)i;
    }
    if (IsMinor)
    {
        for (int i = First_Minor; i < Unknown_Aspect; i++)
        {
            if (Asprst[i].Rest) continue;
            orb = MPOrbSub + Asprst[i].Orb;
            if (orb <= 0.0) continue;
            angle = fa;
            if (angle - orb > 180.0)
                angle = 360.0 - angle;
            aasp = (*this) * (enum Aspects)i;
            if ((angle < aasp + orb) && (angle > aasp - orb) && (*this) == (enum Aspects)i)
                return (enum Aspects)i;
        }
    }
    return Unknown_Aspect;
}

char AstroAspects::GetAspChar(I) const
{
    return AspChars[i];
}

enum Aspects AstroAspects::IsAspect(enum Objs oa, const AstroObjs& a,
                                    enum Objs ob, const AstroObjs& b, int flags) const
{
    return _AstroAspects::IsAspect(oa, a.Vals, ob, b.Vals, flags) ;
}

enum Aspects AstroAspects::IsAspects(float mp, enum Objs ob, const AstroObjs& b, int flags) const
{
    return _AstroAspects::IsAspect(mp, ob, b.Vals, flags) ;
}

void AstroAspects::IsExtraAspect(enum Objs oa, const AstroObjs& a,
                                 enum Objs ob, const AstroObjs& b, int flags, float* results) const
{
    _AstroAspects::IsExtraAspect(oa, a.Vals, ob, b.Vals, flags, results);
}

AstroFoundAspectsBase::~AstroFoundAspectsBase()
{
    delete Amp;
}

void AstroFoundAspectsBase::TestAspects(const _AstroAspects& aa, const Values& a, const Values& b,
                                        const _AstroRestrictions& ar, const _AstroRestrictions& br)
{
    const bool s = ar.IfStars() && br.IfStars(), sp = Flags & IfSamePlanet;

    /*#ifdef _OPENMP
    # pragma omp parallel for
    #endif*/
    for (int i = Sun; i <= Max_x; i++)
    {
        if (ar != i) continue;
        if (!(Flags & Ha) && ((i >= Ascendant && i <= House_12) || (i >= Fortune && i <= East_Point))) continue;
        for (int j = Sun; j <= Max_y; j++)
        {
            if ((br != j) || (i == j && !sp)) continue;
            if (!(Flags & Hb) && ((j >= Ascendant && j <= House_12) || (j >= Fortune && j <= East_Point))) continue;
            if (s && i >= First_Star && j >= First_Star) continue;
            if (!sp)
                if ((i == North_Node && j == South_Node) || (i >= Ascendant && i <= House_12 && j >= Ascendant && j <= House_12) || i == j)
                    continue;
            enum Objs oa = (enum Objs)i, ob = (enum Objs)j;
            enum Aspects asp = aa.IsAspect(oa, a, ob, b, Flags);
            if (asp != Unknown_Aspect && !Already(oa, ob, asp))
                PutAspect(aa, asp, oa, a, ob, b);
            if (aa.IsMinor)
            {
                float results[4] = { -1.0, -1.0, -1.0, -1.0 };
                aa.IsExtraAspect(oa, a, ob, b, Flags, results);
                for (int i = 0; i < 4; i++)
                    if (results[i] != -1.0 && !Already(oa, ob, SC(enum Aspects, Parallel + i)))
                        PutAspect(aa, SC(enum Aspects, Parallel + i), oa, a, ob, b, results[i]);
            }
        }
    }
}

void AstroFoundAspectsBase::TestAspects(const _AstroAspects& aa, const Values& v, const _AstroRestrictions& ar, const _AstroRestrictions& br, bool parts)
{
    int n = Flags & MPb ? Max_x : Max_y, n1 = (n == Max_x) ? Max_y : Max_x;
    const _AstroRestrictions& r = Flags & MPb ? ar : br, &r1 = Flags & MPb ? br : ar;
    if (n1 > House_12) n1 = House_12;
    if (parts)
    {
        /*#ifdef _OPENMP
        # pragma omp parallel for
        #endif*/
        for (int j = Sun; j <= n; j++)
            if (r == j)
                for (int i = 0; i < NbParts; i++)
                {
                    float p = CalcPart(Tp[i], v, r);
                    if (p == NOVALUE) continue;
                    enum Objs ob = (enum Objs)j;
                    enum Aspects asp = aa.IsAspect(p, ob, v, Flags);
                    if (asp != Unknown_Aspect)
                        PutAspect(aa, asp, (enum Objs)i, ARABPART, p, ob, v);
                }
        return;
    }
    /*#ifdef _OPENMP
    # pragma omp parallel for
    #endif*/
    for (int j = Sun; j <= n; j++)
    {
        if (r == j)
        {
            if ((j >= Ascendant && j <= House_12) || (j >= Fortune && j <= East_Point)) continue;
            for (int i = Sun; i <= n1; i++)
                for (int k = i; k <= n1; k++)
                {
                    if (r1 != i || r1 != k) continue;
                    if (!(Flags & IfSamePlanet) && (i == j || k == j)) continue;
                    float mp = Amp->Get(i, k);
                    if (mp != NOVALUE)
                    {
                        enum Objs oa = (enum Objs)i, oc = (enum Objs)k, ob = (enum Objs)j;
                        enum Aspects asp = aa.IsAspect(mp, ob, v, Flags);
                        if (asp != Unknown_Aspect) PutAspect(aa, asp, oa, oc, mp, ob, v);
                    }
                }
        }
    }
}

void AstroFoundAspectsBase::GetAspects(const _AstroAspects& aa, const Values& a, const Values& b, const _AstroRestrictions& ar, const _AstroRestrictions& br, int flags)
{
    Flags = flags;
    Max_x = Max_y = Last_Planet;
    if (ar.IfExtra()) Max_x = ar.LastExtra;
    if (br.IfExtra()) Max_y = br.LastExtra;
    if (ar.IfHouses() && (Flags & Ha)) Max_x = House_12;
    if (br.IfHouses() && (Flags & Hb)) Max_y = House_12;
    if (ar.IfStars())  Max_x = (enum Objs)Final_Star;
    if (br.IfStars())  Max_y = (enum Objs)Final_Star;
    INC(Max_x);
    INC(Max_y);
    Reset(br);
    TestAspects(aa, a, b, ar, br);
    if ((Flags & MPa) || (Flags & MPb) || (Flags & Mutual))
    {
        delete Amp;
        Amp = 0;
        if (Flags & MPa)
        {
            Amp = new AstroMidPoints(a, ar, a, ar, false);
            TestAspects(aa, b, ar, br);
        }
        else if (Flags & MPb)
        {
            Amp = new AstroMidPoints(b, br, b, br, false);
            TestAspects(aa, a, ar, br);
        }
        else
        {
            Amp = new AstroMidPoints(a, ar, b, br, true);
            TestAspects(aa, b, ar, br);
        }
    }
    if ((Flags & Pta) || (Flags & Ptb) || (Flags & PMut))
    {
        if (Flags & Pta) TestAspects(aa, b, ar, br, true);
        else if (Flags & Ptb) TestAspects(aa, a, ar, br, true);
        else TestAspects(aa, b, ar, br, true);
    }
}

void AstroFoundAspectsBase::GetAspects(const AstroAspects& aa, const AstroObjs& oa, const AstroObjs& ob, int flags)
{
    flags |= oa.Accuracy > -1 ? Ha : 0;
    flags |= ob.Accuracy > -1 ? Hb : 0;
    GetAspects(aa, oa.Vals, ob.Vals, oa(), ob(), flags);
}

static inline double dist(double a, double b)
{
    double c = a - b;
    if (c > 0.0)
    {
        if (c > 180.0)
            return 360.0 - a + b;
        else
            return -c;
    }
    if ( c < -180.0)
        return -(360.0 - b + a);
    else
        return -c;
}

void AspectFound::GetSide(float v1, float v2, int flags)
{
    double aasp = (*Aa) * Asp, a1 = Angle_a - aasp, a2 = Angle_a + aasp, b1 = Angle_b - a1, b2 = Angle_b - a2, d1, d2, diff;
    bool t = false;
    if (a2 >= 360.0) a2 -= 360.0;
    //a1 == sens ds aiguilles de la montre ( - )
    // d1 > 0, Angle_b  hors de a1
    d1 = dist(Angle_b, a1);
    d2 = dist(a2, Angle_b);
    if (fabs(d1) == fabs(d2))
        diff = (d1 < 0.0) ? d2 : d1; // ???
    else
        diff = (fabs(d1) < fabs(d2))  ? d1 : d2;
    // t = Angle_b interieur a1 ou a2
    //+
    if (diff == d2)
    {
        if (a2 < Angle_a)
            t = (Angle_b >= Angle_a && Angle_b < 360.0) || ( Angle_b >= 0 && Angle_b < a2);
        else
            t = Angle_b >= Angle_a && Angle_b < a2;
    }
    // -
    else
    {
        if (a1 < 0.0)
        {
            a1 += 360.0;
            t = (Angle_b >= a1 && Angle_b < 360.0) || (Angle_b >= 0 && Angle_b < Angle_a);
        }
        else
            t = Angle_b >= a1 && Angle_b < Angle_a;
    }
    double g = Angle_a - Angle_b;
    if (g <= -180.0) g = 360.0 - Angle_b;
    if (g >= 180.0) g = Angle_b - 360.0;
    if (fabs(diff) < 0.002)
    {
        AspectSide = Exact;
        AspWay   = NeutralAspect;
        return;
    }
    const bool s = diff > 0.0, s1 = SIGN(v1) > 0, s2 = SIGN(v2) > 0;
    if (!(flags & IfSamePlanet))
    {
        //if ((!t && diff > 0.0) || (t && diff < 0.0))
        if ((t && diff == d2) || (!t && diff == d1))
        {
            if (s1 && s2)        AspectSide = v1 < v2 ? Applying : Separating;
            else if (!s1 && !s2) AspectSide = v1 < v2 ? Separating : Applying;
            else if (s1 && !s2)  AspectSide = Separating;
            else                 AspectSide = Applying;
        }
        else
        {
            if (s1 && s2)        AspectSide = v1 < v2 ? Separating : Applying;
            else if (!s1 && !s2) AspectSide = v1 < v2 ? Separating : Applying;
            else if (s1 && !s2)  AspectSide = Applying;
            else                 AspectSide = Separating;
        }
    }
    else
    {
        if (s)
            AspectSide = !s1 ? Applying : Separating;
        else
            AspectSide =  s1 ? Applying : Separating;
    }
    AspWay = g > 0.0 ? LeftAspect : RightAspect;
}

void AstroFoundAspectsTable::Clean()
{
    for (int i = Sun; i < Final_Star; i++)
    {
        ATable& at = Tbl[i];
        if (!at) at.Empty();
    }
    Empty();
    PTbl.Empty();
}

AstroFoundAspectsTable::~AstroFoundAspectsTable()
{
    Clean();
}

void AstroFoundAspectsTable::Reset(const _AstroRestrictions& br)
{
    int m, l;
    bool b = false;
    asp unknown = Unknown_Aspect;
    if (Flags & MPa)
    {
        m = Max_y;
        l = Max_x;
        b = true;
    }
    else if ((Flags & MPb) || (Flags & Mutual))
    {
        m = Max_x;
        l = Max_y;
        b = true;
    }
    Clean();
    Create(Max_x, Max_y, &unknown);
    if (b)
    {
        for (int i = Sun; i <= m; i++)
            if (br == i) Tbl[i].Create(l, l, &unknown);
    }
    if (Flags & Pta && NbParts) PTbl.Create(Max_x, NbParts);
    else if (((Flags & Ptb) || (Flags & PMut)) && NbParts)  PTbl.Create(Max_y, NbParts);
}

void AstroFoundAspectsTable::RegetAspects(const _AstroAspects& aa, const Values& a, const Values& b, const _AstroRestrictions& ar, const _AstroRestrictions& br, int flags)
{
    Flags = flags;
    Max_x = Max_y = Last_Planet;
    if (ar.IfExtra())       Max_x = ar.LastExtra;
    if (br.IfExtra())       Max_y = br.LastExtra;
    if (ar.IfHouses() && (flags & Ha)) Max_x = House_12;
    if (br.IfHouses() && (flags & Hb)) Max_y = House_12;
    if (ar.IfStars())        Max_x = (enum Objs)Final_Star;
    if (br.IfStars())        Max_y = (enum Objs)Final_Star;
    INC(Max_x);
    INC(Max_y);
    Reset(br);
    TestAspects(aa, a, b, ar, br);
    if (Flags & MPa)
        TestAspects(aa, b, ar, br);
    else if ((Flags & MPb) || (Flags & Mutual))
        TestAspects(aa, a, ar, br);
    if (Flags & Pta) TestAspects(aa, b, ar, br, true);
    else if ((Flags & Ptb) || (Flags & PMut)) TestAspects(aa, a, ar, br);
}

void AstroFoundAspectsTable::PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa, const Values& a, enum Objs ob, const Values& b, float)
{
    Get(oa, ob) = asp;
    if (!(Flags & IfSamePlanet) && Valid(ob, oa)) Get(ob, oa) = asp;
}

void AstroFoundAspectsTable::PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                                       enum Objs oc, float mp, enum Objs ob, const Values& b)
{
    if (((Flags & Pta) || (Flags & Ptb) || (Flags & PMut)) && oc == ARABPART)
    {
        if (PTbl.Valid(ob, oa)) PTbl.Get(ob, oa) = asp;
    }
    else
    {
        ATable& at = Tbl[ob];
        at.Get(oa, oc) = asp;
        if (!(Flags & IfSamePlanet) && at.Valid(oc, oa)) at.Get(oc, oa) = asp;
    }
}

AstroFoundAspectsList::~AstroFoundAspectsList()
{
    Clear();
    AspMP.Clear();
}

void AstroFoundAspectsList::Reset(const _AstroRestrictions& br)
{
    Clear();
    AspMP.Clear();
}

AstroFoundAspectsList::AstroFoundAspectsList(const AstroAspects& aa, const AstroObjs& a, const AstroObjs& b, int flags)
{
    Flags = flags;
    Flags |= a.Accuracy > -1 ? Ha : 0;
    Flags |= b.Accuracy > -1 ? Hb : 0;
    GetAspects(aa, a.Vals, b.Vals, a(), b(), Flags);
}

void AstroFoundAspectsList::PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                                      const Values& a, enum Objs ob, const Values& b, float orb)
{
    /*#ifdef _OPENMP
    # pragma omp single
    #endif*/
    Append(new AspectFound(aa, asp, oa, a, ob, b, Flags, orb));
}

void AstroFoundAspectsList::PutAspect(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,
                                      enum Objs oc, float mp, enum Objs ob, const Values& b)
{
    /*#ifdef _OPENMP
    # pragma omp single
    #endif*/
    {
        if (oc == ARABPART)
            Append(new AspectFound(aa, asp, oa, oc, mp, ob, b, Flags));
        else
            AspMP.Append(new AspectFound(aa, asp, oa, oc, mp, ob, b, Flags));
    }
}

const AspectFound* AstroFoundAspectsList::Search(enum Objs o1, enum Aspects asp, enum Objs o2, const AspectFound* af, bool next, bool mp, enum Objs o3) const
{
    AlAf::Const_Iterator fmp(AspMP);
    Const_Iterator f(*this);
    if (af)
    {
        if (mp)
        {
            for (; fmp == AspMP && af != !fmp; ++fmp)
                if (af != !fmp) return 0;
            if (next)
            {
                ++fmp;
                if (!fmp == 0) return 0;
            }
        }
        else
        {
            for (; f == *this && !f != af; ++f) ;
            if (af != !f) return 0;
            if (next)
            {
                ++f;
                if (!f == 0) return 0;
            }
        }
    }
    const bool to1 = (o1 == Undefined_Obj), to2 = (o2 == Undefined_Obj), to3 = (o3 == Undefined_Obj || o3 == ARABPART);
    if (mp)
    {
        for (;fmp == AspMP; ++fmp)
        {
            const AspectFound* cmp = !fmp;
            const bool a = ((asp == Unknown_Aspect) ? true : asp == cmp->Asp),
                           b = ((to1 ? true : o1 == cmp->Oa) && (to3 ? true : o3 == cmp->Oc)) ||
                               ((to1 ? true : o1 == cmp->Oc) && (to3 ? true : o3 == cmp->Oa));
            if (b && a && (to2 ? true : o2 == cmp->Ob))
                return !fmp;
        }
        return 0;
    }
    for (;f == *this; f++)
    {
        const AspectFound* cf = !f;
        const bool a = ((asp == Unknown_Aspect) ? true : asp == cf->Asp);
        if (o3 == ARABPART)
        {
            if ( a && (((to1 ? true : o1 == cf->Oa) && (to2 ? true : o2 == cf->Ob) && cf->Oc == ARABPART) ||
                       ((to1 ? true : o1 == cf->Ob) && (to2 ? true : o2 == cf->Oa) && cf->Oc == ARABPART)))
                return cf;
        }
        else
            if ( a && (((to1 ? true : o1 == cf->Oa) && (to2 ? true : o2 == cf->Ob)) ||
                       ((to1 ? true : o1 == cf->Ob) && (to2 ? true : o2 == cf->Oa))))
                return cf;
    }
    return 0;
}

bool AstroFoundAspectsList::Already(enum Objs oa, enum Objs ob, enum Aspects a) const
{
    if (a != Unknown_Aspect)
    {
        if (!(Flags & IfSamePlanet))
            return Search(oa, a, ob) != 0;
        foreachc(*this, AstroFoundAspectsList)
        {
            const AspectFound* f = !it;
            if (f->Oa == oa && f->Ob == ob && f->Asp == a) return true;
        }
        return false;
    }
    if (!(Flags & IfSamePlanet))
        return Search(oa, Unknown_Aspect, ob) != 0;
    foreachc(*this, AstroFoundAspectsList)
    if ((!it)->Oa == oa && (!it)->Ob == ob) return true;
    return false;
}

AspectFound::AspectFound(const _AstroAspects& aa, enum Aspects asp, enum Objs oa, const Values& a,
                         enum Objs ob, const Values& b, int flags, float orb)
{
    const struct Rest* Restr = aa.GetRest();
    Aa = CSC(_AstroAspects*, &aa);
    Asp = asp;
    Oa = oa;
    Ob = ob;
    Oc = Undefined_Obj;
    if (Asp == Parallel || Asp == Antiparallel)
    {
        Angle_a = a.Get(oa, 1);
        Angle_b = b.Get(ob, 1);
    }
    else
    {
        Angle_a = a.Get(oa);
        Angle_b = b.Get(ob);
    }
    GetSide(a.Get(oa, 3), b.Get(ob, 3), flags);
    Orb = (*Aa) / asp + ((asp <= Inconjunct) ? Restr[oa].OrbAdd + Restr[ob].OrbAdd : 0);
    ExtraOrb = orb;//orb != -1.0 ? orb : fabs(DiffAngle(fabs(Angle_a), fabs(Angle_b)) - (*Aa) * Asp);
}

AspectFound::AspectFound(const _AstroAspects& aa, enum Aspects asp, enum Objs oa,  enum Objs oc, float mp, enum Objs ob, const Values& b, int flags)
{
    const struct Rest* Restr = aa.GetRest();
    Aa = (_AstroAspects *)&aa;
    Asp = asp;
    Oa = oa;
    Ob = ob;
    Oc = oc;
    Ifp = ((flags & Pta) || (flags & Ptb) || (flags & PMut));
    Angle_a = mp;
    Angle_b = b.Get(ob);
    GetSide(0.0, b.Get(ob, 3), flags);
    Orb = (*Aa) / asp + ((asp <= Inconjunct) ? aa.MPOrbSub + Restr[ob].OrbAdd : 0);
    ExtraOrb = fabs(DiffAngle(fabs(Angle_a), fabs(b.Get(ob, 0))) - (*Aa) * Asp);
}

enum AspectAccuracy AspectFound::GetAccuracy() const
{
    const double diff = (Asp >= Parallel ? ExtraOrb : fabs(DiffAngle(Angle_a, Angle_b)) - (*Aa) * Asp);
    const int x = int(100.0 * diff / Orb);
    if (x == 0)
        return Exact;
    else if (x <= 30)
        return Good;
    else if (x <= 60)
        return Medium;
    else
        return Poor;
}

int AspectFound::GetInfluence() const
{
    int infl;
    double x = fabs((Asp >= Parallel ? ExtraOrb : DiffAngle(Angle_a, Angle_b)) - ((*Aa) * Asp)), a = -1.0 / Orb;
    if (Oc != Undefined_Obj)
        infl = (Aa->GetRest()[Oa].Influence + Aa->GetRest()[Oc].Influence) / 2 + Aa->GetRest()[Ob].Influence;
    else
        infl = Aa->GetRest()[Oa].Influence +  Aa->GetRest()[Ob].Influence;
    //x = fabs(x - ((*Aa) * Asp));
    return infl * int(Aa->Influence(Asp) * (a * x + 1.0));
}
