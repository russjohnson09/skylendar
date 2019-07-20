/***************************************************************************
                          astrolist.h  -  description
                             -------------------
    begin                : Mon Jan 8 2001
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

#ifndef ASTROLIST_H
#define ASTROLIST_H

#include "../config.h"
#include "astrostring.h"
#include <algorithm>
#ifdef QT
#include <QList>

#ifdef foreach
# undef foreach
#endif

#define foreach(list, type) for(type::Iterator it(list); it == list; ++it)

#define foreachc(list, type) for(type::Const_Iterator it(list); it == list; ++it)
#endif

template <class T> class AstroList :
#ifdef QT
            public QList<T*>
{
public:

    // From now on, skylendar uses iterators instead integrated list pointers
    class  Iterator: public QList<T*>::iterator
    {
    public:
        inline Iterator(AstroList<T>& al): QList<T*>::iterator()
        {
            typename QList<T*>::iterator& it = *this;
            it = al.begin();
        }

        inline Iterator operator++()
        {
            typename QList<T*>::iterator& i1 = *this;
            ++i1;
            return *this;
        }

        inline bool operator==(const AstroList<T>& al) const {
            return (*this) != al.end();
        }
    };


    // Iterator for constant lists

    class Const_Iterator: public QList<T*>::const_iterator
    {
    public:
        inline Const_Iterator(const AstroList<T>& al): QList<T*>::const_iterator()
        {
            *SC(typename QList<T*>::const_iterator*, this) = al.constBegin();
        }
        inline const T* operator !() const {
            return *(*this);
        }

        inline bool operator==(const AstroList<T>& al) const {
            return (*this) != al.constEnd();
        }

        inline void operator = (const AstroList<T>& al) {
            *SC(typename QList<T*>::const_iterator*, this) = al.constBegin();
        }
    };
#endif

    inline virtual ~AstroList()
    {
#ifdef QT
        qDeleteAll(QList<T*>::begin(), QList<T*>::end());
#endif
    }

    inline unsigned int Count() const
    {
#ifdef QT
        return QList<T*>::count();
#endif
    }

    inline void Prepend(const T* item)
    {
#ifdef QT
        QList<T*>::prepend(CSC(T*, item));
#endif
    }

    inline void Append(const T* item)
    {
#ifdef QT
        QList<T*>::append(CSC(T*, item));
#endif
    }

    inline void Insert(Iterator& it, const T* item)
    {
#ifdef QT
        void(QList<T*>::insert(SC(typename QList<T*>::iterator, it), *item));
#endif
    }

    /** Sorting method
    @param myfunc boolean function
    */
    template<typename f> inline void Sort(f myfunc)
    {
#ifdef QT
			std::sort(QList<T*>::begin(), QList<T*>::end(), myfunc);
#endif
    }

    inline T* GetFirst()
    {
#ifdef QT
        return QList<T*>::first();
#endif
    }

    inline T* GetLast()
    {
#ifdef QT
        return QList<T*>::last();
#endif
    }

    inline void Clear()
    {
#ifdef QT
        QList<T*>::clear();
#endif
    }

    inline T* operator[](int i) const
    {
#ifdef QT
        return QList<T*>::at(i);
#endif
    }

    inline void Remove(Iterator& it)
    {
#ifdef QT
        QList<T*>::erase(it);
#endif
    }

    inline void Remove(T* item)
    {
#ifdef QT
        QList<T*>::removeOne(item);
        /*	for(Iterator it(*this); it == (*this); ++it)
        {
        	if(*it == item)
        	{
        		Remove(it);
        		break;
        		}
         }*/
#endif
    }

    inline int Find(const T* item) const
    {
#ifdef QT
        return QList<T*>::indexOf(*item, 0);
#endif
    }
};

typedef AstroList<AstroString>  AstroStringList;

#endif
