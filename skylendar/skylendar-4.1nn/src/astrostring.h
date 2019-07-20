/***************************************************************************
                          astrostring.h  -  description
                             -------------------
    begin                : Sat Sep 16 2000
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

#ifndef ASTROSTRING_H
#define ASTROSTRING_H

#include "../config.h"

#ifdef QT
#include <QString>
#endif

#include "astrodefs.h"

class AstroRegExp;

/** AstroString is a portable, unicode and templated string class */

class AstroString :
#ifdef QT
            public QString
#endif
{

public:

    inline AstroString() {}
#ifdef QT
    inline AstroString(QString q) : QString(q) {}
#endif

    inline AstroString(const char *c)
    {
#ifdef QT
        QString::operator=(c);
#endif
    }

    inline AstroString& operator = (char c)
    {
#ifdef QT
        return static_cast<AstroString&>(QString::operator=(c));
#endif
    }

    inline AstroString& operator = (const char* c)
    {
#ifdef QT
        return static_cast<AstroString&>(QString::operator=(c));
#endif
    }

    /** returns the string length */
    inline int Len() const
    {
#ifdef QT
        return QString::length();
#endif
    }

    /** initialize the char buffer c of length len with the Utf8 content of the string
     * @param c the pointer to the string
    	 * @param len the buffer length
     */
    inline void Data(char *c, int len = BUFSIZE) const
    {
#ifdef QT
        strncpy(c, toUtf8().data(), len);
#endif
    }

    /** puts an integer converted into a string into an _AstroString */
    inline AstroString& operator = (int i)
    {
#ifdef QT
        setNum(i);
        return *this;
#endif
    }

    /** adds an integer converted into a string to an _AstroString */
    inline AstroString& operator += (int i)
    {
#ifdef QT
        AstroString s;
        s.setNum(i);
        *this += s;
        return *this;
#endif
    }

    /** adds an unsigned integer converted into a string to an _AstroString */
    inline AstroString& operator += (unsigned int i)
    {
#ifdef QT
        AstroString s;
        s.setNum(i);
        *this += s;
        return *this;
#endif
    }

    inline AstroString& operator = (double d)
    {
#ifdef QT
        setNum(d);
        return *this;
#endif
    }

    /** adds a double converted into a string to an _AstroString */
    inline AstroString& operator += (double d)
    {
#ifdef QT
        AstroString s;
        s.setNum(d);
        *this += s;
        return *this;
#endif
    }

    /** adds a string to an _AstroString */
    inline AstroString& operator += (const char* c)
    {
#ifdef QT
        QString::append(c);
        return *this;
#endif
    }

    /** adds a character to an AstroString */
    inline AstroString& operator += (char c)
    {
#ifdef QT
        QString::append(c);
        return *this;
#endif
    }

    /** adds an AstroString to an AstroString */
    inline friend AstroString operator + (const AstroString& as1, const AstroString& as2)
    {
        AstroString s = as1;
        s += as2;
        return s;
    }

    inline friend AstroString operator + (const AstroString& as1, const char *s1)
    {
        AstroString s = as1;
        s += s1;
        return s;
    }

    inline friend AstroString operator + (const char* s1, const AstroString& as2)
    {
        AstroString s = s1;
        s += as2;
        return s;
    }

    inline friend AstroString operator + (const AstroString& s1, int i)
    {
        AstroString s = s1;
        s += i;
        return s;
    }

    inline friend AstroString operator + (int i, const AstroString& s2)
    {
        AstroString s;
        s.setNum(i);
        s += s2;
        return s;
    }

    /** adds an AstroString */
    inline AstroString& operator += (const AstroString& as)
    {
#ifdef QT
        QString::append(as);
        return *this;
#endif
    }

    inline const AstroString Char(int i)
    {
#ifdef QT
        return AstroString(mid(i, 1));
#endif
    }

    inline const AstroString Left(int i) const
    {
#ifdef QT
        return static_cast<const AstroString>(left(i));
#endif
    }

    inline const AstroString Right(int i) const
    {
#ifdef QT
        return static_cast<const AstroString>(right(i));
#endif
    }

    /** Returns the Unicode utf8 coded string */
    inline AstroString Utf8() const
    {
#ifdef QT
        return toUtf8().data();
#endif
    }

    /** Initializes with an unicode utf8 codes string */
    inline void Utf8(const char *c)
    {
#ifdef QT
        *this = fromUtf8(c);
#endif
    }

    /** Returns the ith character into an AstroString */
    inline const AstroString operator[](int i) const
    {
#ifdef QT
        return AstroString(at(i));
#endif
    }

    /** Returns the first char of the string */
    inline char operator !() const
    {
#ifdef QT
        return at(0).toLatin1();
#endif
    }

    /** returns j characters from the ith position */
    inline const AstroString Mid(int i, int j) const
    {
#ifdef QT
        return static_cast<const AstroString>(mid(i, j));
#endif
    }

    /** Replace a substring by another */
    inline AstroString Replace(const AstroString& before, const AstroString& after)
    {
#ifdef QT
        return AstroString(replace(before, after));
#endif
    }

    /** Finds the nth position of the given string
    @param pat, the searched string
    @param i from the ith position
    @return position of the found string, otherwise -1 */
    inline int Find(const AstroString& pat, int i = 0) const
    {
#ifdef QT
        return QString::indexOf(pat, i);
#endif
    }

    /** Finds the nth position of the given string
    @param pat, the regexp pattern
    @param i from the ith position
    @return position of the found string, otherwise -1 */
    int Find(AstroRegExp& pat, int i = 0) const;

    /** Returns the lower characters form string */
    inline AstroString Low() const
    {
#ifdef QT
        return AstroString(toLower());
#endif
    }

    /** returns a possible integer from string
    @param ok if ok and ok == true the string contains a valid number
    @return the wanted integer value, if any */
    int Int(bool *ok) const
    {
#ifdef QT
        return toInt(ok);
#endif
    }
};

#endif

