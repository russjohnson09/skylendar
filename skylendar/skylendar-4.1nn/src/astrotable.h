/***************************************************************************
                          astrotable.h  -  description
                             -------------------
    begin                : Fri Aug 15 2003
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

#ifndef ASTROTABLE_H
#define ASTROTABLE_H

#include "astrodefs.h"

typedef unsigned char ind;

/** This class manages a simple 2 dimentional array of type T */

//extern "C" void* memset(void*, int, unsigned int);

template <typename T> class AstroTable
{
public:

    /** Constructor */
    inline AstroTable() {
        Ptr = 0;
        X = Y = 0;
    }

    /** Constructor */
    inline AstroTable(ind x, ind y, const T* t = 0) {
        Ptr = 0;
        Create(x, y, t);
    }

    /** Destructor */
    inline ~AstroTable() {
        Empty();
    }

    /** Creates a x * y array and initializes
    each element it with t if t not null */
    inline void Create(ind x, ind y, const T* t = 0);

    /** returns true if created */
    inline bool Created() const {
        return Ptr ? true : false;
    }

    /** Same as above, but as an operator */
    inline bool operator !() const {
        return Ptr ? true : false;
    }

    /** Purges the content of the array */
    inline void Empty() {
        delete Ptr;
        Ptr = 0;
        X = Y = 0;
    }

    /** Returns the yth elem of column x */
    inline T& Get(ind x, ind y) const {
        return Ptr[y * X + x/*Y * x + y*/];
    }

    /** Same as above, but returns a pointer, if any */
    inline T* PGet(ind x, ind y) const {
        int i = Y * x + Y;
        return (i >= X * Y) ? 0 : &Ptr[i];
    }

    /** Returns true if elem[x, y] within the table */
    inline bool Valid(ind x, ind y) const {
        return (x < X && y < Y) ? true : false;
    }

    /** Dump Ptr, (for testing) */
    T* Dump() const {
        return Ptr;
    }

    /** Copy an AstroTable to another */
    inline void operator = (const AstroTable&);

    /** Returns width */
    inline ind GetX() const {
        return X;
    }

    /** Returns height */
    inline ind GetY() const {
        return Y;
    }


private:

    T* Ptr;
    ind X, Y;
};

template <typename T> inline void AstroTable<T>::Create(ind x, ind y, const T* t)
{
    const int s = x * y;
    Empty();
    X = x;
    Y = y;
    Ptr = new T[s];
    if (t)
    {
        if (sizeof(T) == 1)
            memset(Ptr, *reinterpret_cast<const char*>(t), s);
        else
            for (int i = 0; i < s; i++)
                Ptr[i] = *t;
    }
}

template <typename T> inline void AstroTable<T>::operator = (const AstroTable& at)
{
    int lx = at.GetX(), ly = at.GetY();
    Empty();
    Create(lx, ly);
    for (int i = 0; i < lx; i++)
        for (int j = 0; j < ly; j++)
            Get(i, j) = at.Get(i, j);
}

#endif
