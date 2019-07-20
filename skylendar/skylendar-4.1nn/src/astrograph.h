/**************************************************************************                          astrograph.h  -  description
                             -------------------
    begin                : sam nov 1 2003
    copyright            : (C) 2003 by Christophe Gros
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

#ifndef ASTROGRAPH_H
#define ASTROGRAPH_H

#include <astrographics.h>

#define SGSIZE 3750
#define FBSIZE 11527344

typedef const signed char fmbt[FBSIZE];
typedef const signed char segt[SGSIZE];

typedef struct
{
    char magic[12];
    unsigned char maxlength[4];
    unsigned char index[560];
} Header;

typedef struct
{
    unsigned char minlong[3];
    unsigned char maxlong[3];
    unsigned char minlat[3];
    unsigned char maxlat[3];
    unsigned char address[4];
} Segment_Index;

CONST inline double Dist(double a, double b) {
    return fabs(a * b < 0.0 ? b + a : a - b);
}

class AstroWorldMap
{
public:

    AstroWorldMap() {
        Count = 0;
    }
    ~AstroWorldMap() {
        Delete();
    }

    bool Get();
    void Release();
    const fmbt& GetFmb() const {
        return reinterpret_cast<const fmbt&>(*Fullmap_Buffer);
    }
    const Segment_Index& operator[](int i) const {
        return SIndex[i];
    }
    const unsigned char* GetIndex(int i) const {
        return &Head->index[i];
    }
    int GetAddr0() const {
        return Address0;
    }

private:

    int Count, FbSize, Address0;
    void Delete();
    signed char *Fullmap_Buffer;
    Header* Head;
    Segment_Index* SIndex;
};

/**This class implements the astro-graph computing and display
  *@author Christophe Gros
  */

class AstroGraph : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(AstroGraph)

public:

    friend class AstroWindow;

    AstroGraph(ChartBaseParams*, ObjsVector*);
    ~AstroGraph();

    void GetCoord(int x, int y, double* rx, double* ry) const;

    bool Redisplay();

private:

    inline int ConvX(int x) const
    {
        return W2 + (int)((float)x * Xc);//(int)(( ((double)x / 3600.0) * W) / fabs(Llong - Rlong));
    }

    inline int ConvY(int y) const
    {
        return H2 - (int)((float)y * Yc);//(int)(( ((double)y / 3600.0) * H) / fabs(Tlat - Blat)/*180.0*/);
    }
    void WLine(double z0, double z2, double dlat) const;
    Header* Head;
    Segment_Index* SIndex;
    int address0, W2, H2, ZoomFact, FbSize;
    double W, H, Tlat, Blat, Rlong, Llong, Res;
    float Xc, Yc;
    AstroGraphics *Agp;
};

struct PushElem
{
    enum Objs o;
    int val, type;
};

class AstroPusher
{
public:

    AstroPusher(int nbelems, int nbslots, int x);
    ~AstroPusher() {
        delete Elems;
        delete Slots;
    }
    inline struct PushElem& operator[](int i) const {
            return Slots[i];
        }
    bool AddElem(enum Objs o, int v, int t);
    inline int GetMaxX() const {
        return MaxX;
    }
    void Push();

private:

    struct PushElem *Elems, *Slots;
    int Cnt, NbElems, NbSlots, MaxX;
};
#endif
