/***************************************************************************
                          direngine.cpp  -  description
                             -------------------
    begin                : Wed Sep 24 2009
    copyright            : (C) 2009 by Christophe Gros
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
#include "direngine.h"
#include "astroaspects.h"
#ifdef __WINNT
#undef LONG
#endif
extern "C"
{
#include "sweodef.h"
#include "swephexp.h"
#include "sweph.h"
};
#define NOANGLE(i) if(i >= Ascendant && i <= Descendant) return NOVALUE

CONST inline bool East(double ar, double armc, double aric)
{
    if (armc > aric)
    {
        if (ar > aric && ar < armc) return false;
    }
    else
        if ((ar > aric && ar < 360.0) || (ar < armc && ar > 0.0)) return false;
    return true;
    // if (armc < 180.0)
    //     return ar > armc && ar < aric;
    // else
    //     return ar < armc && ar > aric;
}

double DirEngine::SimmoSunStep(double jd)
{
    double array[6], d;
    swe_calc_ut(floor(jd) - 0.5, Sun, SEFLG_EQUATORIAL, array, serr);
    d = array[0];
    swe_calc_ut(floor(jd) + 0.5, Sun, SEFLG_EQUATORIAL, array, serr);
    return array[0] - d;
}

double DirEngine::GetArmc()
{
    int h;
    double hs[13], ascmc[10];
    switch (H)
    {
    case Placidus:
        h = 'P';
        break;
    case Regiomontanus:
        h = 'R';
        break;
    case Campanus:
        h = 'C';
        break;
    default:
        ;
    };
    swe_houses(V->Julday, V->Latitude, V->Longitude, h, hs, ascmc);
    Vals[Ascendant].V[LNG] = ascmc[0];
    Vals[MC].V[LNG] = ascmc[1];
    Vals[Descendant].V[LNG] = Normalize(Vals[Ascendant].V[LNG] + 180.0);
    Vals[Vertex].V[LNG] = ascmc[3];

    return ascmc[2];
}

void DirEngine::NsaDsa(double ar, double ad)
{
    nsa = 90.0 - ad;
    dsa = 90.0 + ad;
    umd = fabs(Armc - ar);
    lmd = fabs(180.0 - umd);
    md = umd < lmd ? umd : lmd;
}

int DirEngine::Quadrant(double ar) const
{
    bool east = East(ar, Armc, Aric), beneath = umd > dsa || lmd < nsa;
    if (east && beneath) return 1;
    if (!east && beneath) return 2;
    if (!east && !beneath) return 3;
    return 4;
}

int DirEngine::Quadrant(double ar, double dec, double dlat) const
{
    double umd = fabs(Armc - ar), ad = Ad(dec, dlat), nsa = 90.0 - ad, dsa = 90.0 + ad;
    bool east = East(ar, Armc, Aric), beneath = umd > dsa || lmd < nsa;
    if (east && beneath) return 1;
    if (!east && beneath) return 2;
    if (!east && !beneath) return 3;
    return 4;
}

double DirEngine::Pole(double decl) const
{
    double a, b, c, f, zd;
    double l = DEGRAD(V->Latitude), m = DEGRAD(md);
    if (H == Regiomontanus || H == Campanus)
    {
        if (md == 90.0)
            return 90.0 - RADDEG(atan(fabs(sin(l)) * tan(DEGRAD(decl))));
        a = RADDEG(atan(cos(l) * tan(m)));
        b = RADDEG(atan(tan(fabs(l)) * cos(m)));
        if (V->Latitude * decl  >= 0.0)
            c = (md == umd) ? b - fabs(decl) : b + fabs(decl);
        else
            c = (md == umd) ? b + fabs(decl) : b - fabs(decl);
        f = RADDEG(atan(sin(fabs(l)) * sin(m) * tan(DEGRAD(c))));
        if (b == fabs(decl)) {
            c = f = 0.0;
        }
        zd = a + f;
        if (H == Campanus) return zd;
        return RADDEG(asin(sin(l) * sin(DEGRAD(zd))));
    }
    return NOVALUE;
}

DirEngine::DirEngine(Values& v, const _AstroRestrictions &ar, enum House h, enum DirType dt, enum StatKey st, double dval, bool converse)
{
    double x[6];
    H = h;
    Dt = dt;
    St = st;
    DVal = dval;
    Ar = CSC(_AstroRestrictions*, &ar);
    Converse = converse;
    V = &v;
    swe_calc(V->Julday, SE_ECL_NUT, 0, x, serr);
    E = x[0];
    if (st == Simmonite) Sss = SimmoSunStep(V->Julday);
    Speculum();
}

void DirEngine::Speculum()
{
    Armc = GetArmc();
    Aric = Normalize(Armc + 180.0);
    for (int i = Sun; i < East_Point; i++)
        if ((*Ar) == i) SpecPla(i);
    if (Ar->IfHouses())
    {
        if ((*Ar) == Ascendant) SpecAngle(Ascendant);
        if ((*Ar) == MC) SpecAngle(MC);
//         if ((*Ar) == FC) SpecAngle(FC);
//         if ((*Ar) == Descendant) SpecAngle(Descendant);
    }
    if (Ar->IfExtra())
        for (int i = First_Extra; i <= Ar->LastExtra; i++)
            if ((*Ar) == i) SpecPla(i);
    if ((*Ar) == XPoint) SpecPla(XPoint);
    if (Ar->IfStars())
        for (int i = First_Star; i < Final_Star; i++)
            if ((*Ar) == i) SpecPla(i);
}

void DirEngine::SpecPla(int i)
{
    double ad, d[6], dlat = V->Latitude, pole, Q, w, cmp;
    Vals[i].V[LNG] = V->Get(i);
    swe_calc_ut(V->Julday, i, SEFLG_EQUATORIAL, d, serr);
    Vals[i].V[RA] = d[0];
    Vals[i].V[DEC] = d[1];
    ad = Ad(Vals[i].V[DEC], dlat);
    NsaDsa(d[0], ad);
    int q = Quadrant(d[0]);
    pole = Pole(d[1]);
    switch (H)
    {
    case Regiomontanus:
        Vals[i].V[POLE] = pole;
        Q = fabs(AscDif(d[1], pole));
        w = (q == 1 || q == 4) ? d[0] - Q : d[0] + Q;
        Vals[i].V[W] = w;
        break;;
    case Campanus:
        if (q == 1 || q == 4)
            cmp = (md == umd) ? 270.0 + pole : 90.0 - pole;//zenith :  nadir
        else
            cmp = (md == umd) ? 270.0 - pole : 90.0 + pole;
        Vals[i].V[CMP] = cmp;
        break;
    case Placidus:
        Vals[i].V[MDSA] = md / ((umd > dsa || lmd < nsa) ? nsa : dsa);
        switch (q)
        {
        case 1:
            Vals[i].V[PMP] = 90.0 - 90.0 * Vals[i].V[MDSA];
            break;
        case 2:
            Vals[i].V[PMP] = 90.0 + 90.0 * Vals[i].V[MDSA];
            break;
        case 3:
            Vals[i].V[PMP] = 270.0 - 90.0 * Vals[i].V[MDSA];
            break;
        case 4:
            Vals[i].V[PMP] = 270.0 + 90.0 * Vals[i].V[MDSA];
        default:
            ;
        };
        break;
    default:
        ;
    }
}

void DirEngine::SpecAngle(int i)
{
    Vals[i].V[LNG] = V->Get(i);
    Vals[i].V[RA] = Lon2Ra(Vals[i].V[LNG], E);
    Vals[i].V[DEC] = Lon2Dec(0.0, E);
}

double DirEngine::ArcDir(enum Objs p, enum Objs s, enum Aspects asp, bool right) const
{
    extern const struct AspectsConstants* AspConstVector;
    double dg = right ? -AspConstVector[asp].Angle : AspConstVector[asp].Angle;
    if (asp == Parallel)     return GetParallel(p, s, false);
    if (asp == Antiparallel) return GetParallel(p, s, true);
    if (s == MC || s == FC)
    {
        double pl = Normalize(Get(p, LNG) + dg),
                    ra = (Dt == Zodiacal) ?  Lon2Ra(pl, E) : Get(p, RA);
        return ra - Normalize(((s == FC) ? Aric : Armc) + ((Dt == Zodiacal) ? 0.0 : dg));
    }
    // if (p == MC /*|| p == FC*/)
    // {
    //     NOANGLE(s);
    //     double pl = Get(s, LNG),
    //                 ra = (Dt == Zodiacal) ?  Lon2Ra(pl, E) : Normalize(Get(s, RA) + dg);
    //     return ((s == FC) ? Aric : Armc) - ra;
    // }
    if (s == Ascendant)
    {
        NOANGLE(p);
        if (p == Fortune) return NOVALUE;
        double pl = Normalize(Get(p, LNG) + dg),
                    ra = (Dt == Zodiacal) ?  Lon2Ra(pl, E) : Normalize(Get(p, RA) + dg),
                         dec = (Dt == Zodiacal) ?  Lon2Dec(pl, E) : Get(p, DEC),
                               oasc = Normalize(Armc + 90.0 + ((Dt == Zodiacal) ? dg : 0.0)),
                                      oap = Normalize(ra - Ad(dec, V->Latitude));
        return oap - oasc;
    }
    if (s == Descendant)
    {
        NOANGLE(p);
        if (p == Fortune) return NOVALUE;
        double pl = Normalize(Get(p, LNG) + dg),
                    ra = (Dt == Zodiacal) ?  Lon2Ra(pl, E) : Normalize(Get(p, RA) + dg),
                         dec = (Dt == Zodiacal) ?  Lon2Dec(pl, E) : Get(p, DEC),
                               odesc = Normalize(Armc - 90.0 + ((Dt == Zodiacal) ? dg : 0.0)),
                                       odp = Normalize(ra + Ad(dec, V->Latitude));
        return odp - odesc;
    }

    if (s == Vertex)
    {
        NOANGLE(p);
        if (p == Fortune) return NOVALUE;
        double pl = Normalize(Get(p, LNG) + dg),
                    od2ytx = Normalize(Armc - 90.0),
                             od2p = Normalize(((Dt == Zodiacal) ? Lon2Ra(pl, E) : Get(p, RA)) - Ad2((Dt == Zodiacal) ? Lon2Dec(pl, E) : Get(p, DEC), V->Latitude) + ((Dt == Zodiacal) ? 0.0 : dg));
        return od2p - od2ytx;
    }
    return PlanetDir(p, s, dg);
}

double DirEngine::PlanetDir(enum Objs p, enum Objs s, double aspdeg) const
{
    double l = DEGRAD(V->Latitude), Ra, Dec;
    if (p == Fortune) return NOVALUE;
    if (Dt == Zodiacal)
    {
        double la = Normalize(Get(p, LNG) + aspdeg);
        Ra = Lon2Ra(la, E);
        Dec = Lon2Dec(la, E);
        aspdeg = 0.0;
    }
    else
    {
        Ra = Get(p, RA);
        Dec = Get(p, DEC);
    }
    if (H == Regiomontanus)
    {
        int q = Quadrant(Get(s, RA), Get(s, DEC), V->Latitude);
        double wap = Normalize(Get(s, W) + aspdeg),
                     ra = (Normalize(wap - Armc) < Normalize(wap - Aric)) ? Armc : Aric,
                          mdap = fabs(wap - ra),
                                 qp = fabs(RADDEG(asin(tan(DEGRAD(Dec)) * tan(l) * sin(DEGRAD(mdap))))),
                                      wp = (q == 1 || q == 4) ? Ra - qp : Ra + qp;
        return wp - wap;
    }
    else if (H == Campanus)
    {
        double cmp = Get(s, CMP),
                     cmpap = Normalize(cmp + aspdeg),
                             zdap = Normalize(fabs(cmpap - 90.0)),
                                    pole = asin(sin(l) * sin(DEGRAD(zdap))), dap, x, raap, qap, qp, wap, wp;
        pole = fabs(pole) * ((l < 0.0) ? -1.0 : 1.0);
        dap = -asin(sin(l) * sin(DEGRAD(cmpap)));
        qap = asin(tan(dap) * tan(pole));
        x = RADDEG(atan(cos(l) * tan(DEGRAD(cmpap))));
        if (cmpap > 90.0 && cmpap < 270.0)
        {
            raap = Normalize(Armc - 90.0 + x);
            wap = Normalize(raap + RADDEG(qap));
        }
        else
        {
            raap = Normalize(Armc + 90.0 + x);
            wap = Normalize(raap - RADDEG(qap));
        }
        qp = RADDEG(asin(tan(DEGRAD(Dec) * tan(pole))));
        wp = (cmpap > 90.0 && cmpap < 270.0) ? Ra + qp : Ra - qp;
        return wp - wap;
    }
    else if (H == Placidus)
    {
        int q;
        double pmps, pmpap, mdsap, t, v, r, adp;
        switch (Quadrant(Get(s, RA), Get(s, DEC), V->Latitude))
        {
        case 1:
            pmps = 90.0 - 90.0 * Get(s, MDSA);
            break;
        case 2:
            pmps = 90.0 + 90.0 * Get(s, MDSA);
            break;
        case 3:
            pmps = 270.0 - 90.0 * Get(s, MDSA);
            break;
        default:
            pmps = 270.0 + 90.0 * Get(s, MDSA);
        };
        pmpap = Normalize(pmps + aspdeg);
        if (pmpap >= 0 && pmpap < 90.0)
        {
            q = 1;
            mdsap = 1.0 - pmpap / 90.0;
        }
        else if (pmpap >= 90.0 && pmpap < 180.0)
        {
            q = 2;
            mdsap = pmpap / 90.0 -1.0;
        }
        else if (pmpap >= 180.0 && pmpap < 270.0)
        {
            q = 3;
            mdsap = 3.0 - pmpap / 90.0;
        }
        else
        {
            q = 4;
            mdsap = pmpap / 90.0 - 3.0;
        }
        t = (q == 1 || q == 3) ? 1.0 : -1.0;
        v = (q == 1 || q == 2) ? -1.0 : 1.0;
        r = (q == 1 || q == 2) ? Aric : Armc;
        adp = Ad(Dec, V->Latitude);
        return Ra -r + t * (90.0 + v * adp) * mdsap;

    }
    return NOVALUE;
}

double DirEngine::CompDate(double jd, double arc, double lon) const
{
    double xx[6], y;
    char serr[256];
    swe_calc_ut(jd + arc -2.0, SE_SUN, 0, xx, serr);
    y = *xx;
    for (double j = jd + arc - 1.0; j <= jd + arc + 2.0; j += 1.0)
    {
        swe_calc_ut(j, SE_SUN, 0, xx, serr);
        if (*xx > lon)
        {
            double a = *xx - y, b = *xx - a * j;
            return (lon - b) / a;
        }
        y = *xx;
    }
    return 0.0;
}

double DirEngine::GetPlacidian(double arc) const
{
    arc = fabs(arc);
    double r = arc + Vals[Sun].V[RA], rl = Ra2Lon(r, E), p = CompDate(V->Julday, arc, rl);
    if (p == 0.0) return NOVALUE;
    return V->Julday + ((p - V->Julday) * 365.25);
}

double DirEngine::GetParallel(enum Objs p, enum Objs s, bool contra) const
{
    if (Dt != Mundane) return NOVALUE;
    if (H == Regiomontanus || H == Campanus)
    {
        double ra = (md == umd) ?  Armc : Aric, qpp = fabs(AscDif(Vals[p].V[DEC], Vals[s].V[POLE])), wpp = 2.0 * ra - Vals[s].V[W], rapp;
        if (contra)
        {
            wpp += 180.0;
            rapp = (Vals[p].V[W] == Vals[p].V[LNG] - qpp) ? wpp + qpp : wpp - qpp;
        }
        else
            rapp = (Vals[p].V[W] == Vals[p].V[LNG] - qpp) ? wpp - qpp : wpp + qpp;
        return Vals[p].V[RA] - rapp;
    }
    else if (H == Placidus)
    {
        int q;
        double pmps, pmpap, mdsap, t, v, r, adp;
        switch (Quadrant(Get(s, RA), Get(s, DEC), V->Latitude))
        {
        case 1:
            pmps = 90.0 - 90.0 * Get(s, MDSA);
            break;
        case 2:
            pmps = 90.0 + 90.0 * Get(s, MDSA);
            break;
        case 3:
            pmps = 270.0 - 90.0 * Get(s, MDSA);
            break;
        default:
            pmps = 270.0 + 90.0 * Get(s, MDSA);
        };
        pmpap = Normalize(pmps);
        if (pmpap >= 0 && pmpap < 90.0)
        {
            q = 1;
            mdsap = 1.0 - pmpap / 90.0;
        }
        else if (pmpap >= 90.0 && pmpap < 180.0)
        {
            q = 2;
            mdsap = pmpap / 90.0 -1.0;
        }
        else if (pmpap >= 180.0 && pmpap < 270.0)
        {
            q = 3;
            mdsap = 3.0 - pmpap / 90.0;
        }
        else
        {
            q = 4;
            mdsap = pmpap / 90.0 - 3.0;
        }
        t = (q == 1 || q == 3) ? -1.0 : 1.0;
        if (contra)
        {
            v = (q == 1 || q == 2) ? 1.0 : -1.0;
            r = (q == 1 || q == 2) ? Armc : Aric;
        }
        else
        {
            v = (q == 1 || q == 2) ? -1.0 : 1.0;
            r = (q == 1 || q == 2) ? Aric : Armc;
        }
        adp = Ad(Get(p, DEC), V->Latitude);
        return Get(p, RA) - r + t * ((90.0 + v * adp) * mdsap);
    }
    return NOVALUE;
}

double DirEngine::ArcDate(double arc) const
{
    if (arc == NOVALUE) return NOVALUE;
    switch (St)
    {
    case Ptolemy:
        return V->Julday + fabs(arc) * 365.25;
        break;
    case Naibod:
        return V->Julday + fabs(arc) * 1.0146 * 365.25;
        break;
    case Cardan:
        return V->Julday + fabs(arc) * 1.013514 * 365.25;
        break;
    case Synodic:
        return V->Julday + fabs(arc) * 0.984413 * 365.25;
        break;
    case Simmonite:
        return V->Julday + fabs(arc) * 365.25 / Sss;
        break;
    case Placidian:
        return GetPlacidian(arc);
        break;
    case Custom:
        return V->Julday + fabs(arc) * DVal;
        break;
    }
    return 0.0;
}
