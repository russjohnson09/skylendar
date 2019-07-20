/***************************************************************************
                          direngine.h  -  description
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

#ifndef DIRENGINE_H
#define DIRENGINE_H

#include "astrotransfer.h"
#include "astroutils.h"

//#define LAT 0
#define LNG 1
#define RA 2
#define DEC 3
#define POLE 0
#define W 5
#define CMP 4
#define MDSA 4
#define PMP 5

class DirEngine
{
public:

    DirEngine(Values& v, const _AstroRestrictions &ar, enum House h, enum DirType dt, enum StatKey st, double dval, bool converse);
    double ArcDir(enum Objs p, enum Objs s, enum Aspects asp, bool right = false) const;
    double ArcDate(double arc) const;
    inline bool IfConverse() const {
        return Converse;
    }

private:

    double Get(int i, int j) const {
        return Vals[i].V[j];
    }
    double GetArmc();
    void Speculum();
    void SpecPla(int i);
    void SpecAngle(int i);
    void NsaDsa(double ar, double ad);
    int Quadrant(double ar) const;
    int Quadrant(double ar, double dec, double dlat) const;
    double PlanetDir(enum Objs p, enum Objs s, double aspdeg) const;
    double GetPlacidian(double arc) const;
    //if regiomontanus, returns pole, if campanus returns zd
    double Pole(double decl) const;
    double SimmoSunStep(double jd);
    double CompDate(double jd, double arc, double lon) const;
    double GetParallel(enum Objs p, enum Objs s, bool contra) const;
    Values* V;
    DataValues Vals[Last_Star];
    double Armc, Aric, nsa, dsa, md, umd, lmd, E, Sss, DVal;
    bool Converse;
    mutable char serr[256];
    enum House H;
    enum DirType Dt;
    enum StatKey St;
    _AstroRestrictions* Ar;
};

#endif
