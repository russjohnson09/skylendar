/***************************************************************************
                          astrotransfer.h  -  description
                             -------------------
    begin                : Mon May 6 2002
    copyright            : (C) 2002 by Christophe Gros
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

#ifndef ASTROTRANSFER_H
#define ASTROTRANSFER_H

#include "astrorestrictions.h"
#include <QDBusVariant>
#include <QByteArray>
#define NOAFIRST 255


/* structure containing the 6 values returned by the swe computation routines */
struct DataValues
{
    double V[6];
    bool Retro;
    inline double operator[](int i) const {
        return V[i];
    }
};

/** A class that manages all the values for the computed objects */
class Values
{
public:

    double Julday, Latitude, Longitude;
    bool Southern = false;

    inline Values() {
        Data[XPoint].V[0] = Data[XPoint].V[1] = Data[XPoint].V[2] = 0.0;
    }

    /** returns the ith data */
    inline const DataValues& operator[](int i) const {
        return Data[i];
    }

    /** Returns the first (longitude) value for the ith object */
    inline double Get(int i) const {
        return Data[i].V[0];
    }

    /** If the ith object is retro */
    inline bool Retro(int i) const {
        return Data[i].Retro;
    }

    /** Gets the jth value of the ith object */
    inline double Get(int i, int j) const {
        return Data[i].V[j];
    }

    /** Sets all the values for the ith object */
    void Set(int i, double d, bool r = false, double d1 = 0.0, double d2 = 0.0, double d3 = 0.0, double d4 = 0.0, double d5 = 0.0);

    /** Just sets the first value of object i */
    void CSet(int i, double d, bool r = false);

    /** Returns the number of the house where the object index dwells in */
    int InHouse(int index, short threshold, double *f = 0) const;

    /** Puts the object index in house at position f
      @param index the object index.
      @param house the house number 1..12
      @param f position within the house 0.0..1.0
      */
    void PutInHouse(int index, int house, double f);

    inline double& CGet(int i, int j) {
        return Data[i].V[j];
    }

private:

    DataValues Data[Last_Star + 1];
};

class DataLineBase
{
public:

    enum AspKind ak;
    double jd;
    mutable int y;
};


CONST inline bool DataLineSort(const DataLineBase* a,  const DataLineBase* b)
{
    return a->jd < b->jd;
}

/* A structure containing all the data needed by the computation */

struct DataComp
{
	double julday, j2g, latitude, longitude, altitude, angle;
        enum ChartType ct;
	enum ChartSubType cst;
	unsigned char ring:2, first:2, afirst:2;
	int extraflags;
	bool gethouses:1, gethousesfirst:1, gauquelin:1, aref:1;
} __attribute__((packed));

struct DateTime
{
    int day, month, year;
    double hm;
};

typedef struct
{
    inline void Init() {
        d3[0] = d3[1] = d3[2] = 0.0;
    }

    inline bool IfNull() const {
        return d3[0] == 0.0 && d3[1] == 0.0 && d3[2] == 0.0;
    }

    inline double& operator[](int i) {
        return d3[i];
    }
    union
    {
        double d3[3];
        struct {
            double d1, d2, d3;
        } ds;
    };
} Double3;

/** This struct contains suitable data from aspects, object rising/setting, eclipses etc...*/
class AspData : public DataLineBase
{
public:

    inline bool operator < (const AspData& a) const
    {
        return jd < a.jd ? true : false;
    }

    enum Objs a, b, c;
    enum Aspects asp;
    double apos, bpos;
};

typedef struct
{
    inline double& operator[](int i) {
        return d6[i];
    }
    union
    {
        double d6[6];
        struct {
            double d1, d2, d3, d4, d5, d6;
        } ds;
    };
} Double6;

struct Apsides
{
    Double6 Nasc, Ndsc, Peri, Aphe;
};

typedef struct
{
    double julday;
    double Ao[Last_Star + 1], Pole[Last_Star + 1];
} AoPole;

#define TYPE_OBJ 0
#define TYPE_VAL 1
#define TYPE_EXTRA 2
#define TYPE_ERROR 3
#define SPI 1
#define AMS 2
#define ASM 3

struct ObjPart
{
	unsigned int obj:9, type:2;
} __attribute__((packed));

struct ThePart
{
    struct ObjPart Op[3];
    bool Night, Use;
    struct ObjPart& operator*(int i) {
        return Op[i];
    }
};

typedef struct
{
	float x, y;
} ConstData;

inline int CDSize(ConstData* cd)
{
	int i;
	for(i = 0; cd->x != 1000; cd++, i++);
	return i+1;
}

#ifdef QT
template <typename T> inline QByteArray Get1(const T& t, int size = sizeof(T))
{
    return QByteArray(RC(const char*, &t), size);
}

template <typename T> inline void Put(const QByteArray& qba, T& t, int size = sizeof(T))
{
    memcpy(&t, qba.constData(), size);
}

/* template <typename T> inline QDBusVariant Get1(const T& t, int size = sizeof(T)) { */
/*     return QDBusVariant(QVariant(QByteArray::fromRawData(RC(const char*, &t), size))); */
/* } */

/* template <typename T> void Put(const QDBusVariant& qdv, T& t, int size = sizeof(T)) */
/* { */
/*     memcpy(&t, qdv.variant().value<QByteArray>().constData(), size); */
/* } */

#endif

typedef AstroList<DataLineBase> DataLineList;

#endif
