/***************************************************************************
                          aspconflist.cpp  -  description
                             -------------------
    begin                : mer oct 15 2003
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

#include "aspconflist.h"
#include "astroobjs.h"
#include "astrochartbase.h"
#include "astrosigns.h"
#include <cstdlib>


static const unsigned char Nb[7] = { 3, 3, 255, 4, 3, 4, 6 };

extern "C"
{
    static int comparobjs(const void* v1, const void* v2)
    {
        auto a = SC(const enum Objs*, v1), b = SC(const enum Objs*, v2);
        if (*a == *b) return 0;
        else if (*a < *b) return -1;
        return 1;

    }
}

AspConfData::AspConfData(enum AspConfig ac, unsigned char n, enum Objs o, enum Objs o1, enum Objs o2,
                         enum Objs o3, enum Objs o4, enum Objs o5)
{
    Ac = ac;
    NbObjs = n;
    O[0] = o;
    O[1] = o1;
    O[2] = o2;
    O[3] = o3;
    O[4] = o4;
    O[5] = o5;
    qsort(O, n, sizeof(enum Objs), comparobjs);
}

AspConfList::AspConfList()
{
}

void AspConfList::Compute(const AstroChartBase* acb)
{
    Acb = CSC(AstroChartBase*, acb);
    const AstroFoundAspectsList* afal = Acb->GetAspectsList();
    if (afal)
        Afal = CSC(AstroFoundAspectsList*, afal);
    else
        return;
    Afal->Append(new AspectFound(Opposition, Ascendant, Descendant));
    Afal->Append(new AspectFound(Opposition, MC, FC));
    Afal->Append(new AspectFound(Opposition, North_Node, South_Node));
    GetDavid_Star();
    GetGrand_Trine();
    GetGrand_Cross();
    GetT_Square();
    GetStellium();
    GetYod();
    GetMyst_Rectangle();
}


AspConfList::~AspConfList()
{
}

bool AspConfList::Already(const AspConfData& acd)
{
    foreachc(*this, AspConfList)
    {
        const AspConfData& ad = *(!it);//*adptr;
        if (acd.Ac == ad.Ac)
        {
            bool ok = true;
            for (int i = 0; i < acd.NbObjs; i++)
                if (acd.O[i] != ad.O[i])
                {
                    ok = false;
                    break;
                }
            if (ok) return true;
        }
    }
    return false;
}

void AspConfList::GetGrand_Trine()
{
    AspectFound *t1 = 0, *t2, *t3, *t4 = 0;
    while ((t1 = Search(Undefined_Obj, Trine, Undefined_Obj, t1)))
    {
        t2 = t1;
        while ((t2 = Search(t1->Oa, Trine, Undefined_Obj, t2)))
        {
            t3 = t4 = t2;
            enum Objs o = t2->Oa == t1->Oa ? t2->Ob : t2->Oa;
            while ((t3 = Search(o, Trine, t1->Ob, t3)))
            {
                auto ad = new AspConfData(Grand_Trine, 3, t1->Oa, t2->Ob, t3->Oa == t2->Ob ? t3->Ob : t3->Oa);
                if (!Already(*ad))
                    Append(ad);
                else
                    delete ad;
            }
        }
        if (t4)
        {
            t1 = t4;
            t4 = 0;
        }
    }
}

bool AspConfList::AlreadyTS(const AspConfData& acd)
{
    foreachc(*this, AspConfList)
    if ((!it)->Ac == Grand_Cross)
    {
        bool t[3] = { false };
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                if (acd.O[i] == (!it)->O[j])
                    t[i] = true;
        if (t[0] && t[1] && t[2]) return true;
    }
    return false;
}

void AspConfList::GetT_Square()
{
    AspectFound *t1 = 0, *t2 = 0, *t3, *t4 = 0;
    while ((t1 = Search(Undefined_Obj, Opposition, Undefined_Obj, t1)))
    {
        while ((t2 = Search(t1->Oa, Square, Undefined_Obj, t2)))
        {
            t3 = t4 = t2;
            enum Objs o = t2->Oa == t1->Oa ? t2->Ob : t2->Oa;
            while ((t3 = Search(o, Square, t1->Ob, t3)))
            {
                auto ad = new AspConfData(T_Square, 3, t1->Oa, o, t1->Ob);
                if (!Already(*ad) && !AlreadyTS(*ad))
                    Append(ad);
                else
                    delete ad;
            }
        }
        /*if(t4)
        {
        	t1 = t4;
        	t4 = 0;
        }*/
    }
}

void AspConfList::GetStellium()
{
    const AstroObjs& ao = Acb->GetRef();
    unsigned char signs[12] = { 0 }, houses[12] = { 0 };
    for (int i = Sun; i <= Last_Planet; i++)
        if (ao == i)
        {
            signs[Asg->GetSign(ao * i)] += (i == Sun) ? 2 : 1;
            houses[ao.InHouse(i, 0)] += (i == Sun) ? 2 : 1;
        }
    for (int i = 0; i < 12; i++)
        if (signs[i] >= 5)
        {
            auto ad = new AspConfData;
            ad->Ac = Stellium;
            int k = 0;
            for (int j = Sun; j <= Last_Planet && k < NBO; j++)
                if (ao == j && Asg->GetSign(ao * j) == SC(enum Signs, i))
                    ad->O[k++] = SC(enum Objs, j);
            qsort(ad->O, k, sizeof(enum Objs), comparobjs);
            ad->NbObjs = k;
            if (!Already(*ad))
                Append(ad);
            else
                delete ad;
        }
    for (int i = 0; i < 12; i++)
        if (houses[i] >= 5)
        {
            auto ad = new AspConfData;
            ad->Ac = Stellium;
            int k = 0;
            for (int j = Sun; j <= Last_Planet && k < NBO; j++)
                if (ao == j && ao.InHouse(j, 0) == i)
                    ad->O[k++] = SC(enum Objs, j);
            qsort(ad->O, k, sizeof(enum Objs), comparobjs);
            ad->NbObjs = k;
            if (!Already(*ad))
                Append(ad);
            else
                delete ad;
        }
}

void AspConfList::GetGrand_Cross()
{
    AspectFound *t1 = 0, *t2, *t3 = 0, *t4 = 0;
    while ((t1 = Search(Undefined_Obj, Square, Undefined_Obj, t1)))
    {
        t2 = t1;
        while ((t2 = Search(t1->Oa, Square, Undefined_Obj, t2)))
        {
            while ((t3 = Search(t1->Oa, Opposition, Undefined_Obj, t3)))
            {
                t4 = t3;
                enum Objs o = t1->Oa == t3->Oa ? t3->Ob : t3->Oa;
                if (Search(o, Square, t1->Ob, t2) && Search(o, Square, t2->Ob, t2) && Search(t1->Ob, Opposition, t2->Ob, 0))
                {
                    auto ad = new AspConfData(Grand_Cross, 4, t1->Oa, o, t2->Ob, t1->Ob);
                    if (!Already(*ad))
                        Append(ad);
                    else
                        delete ad;
                }
            }
        }
        /*if(t5)
        {
        	t1 = t4;
        	t4 = 0;
        }*/
    }
}

void AspConfList::GetYod()
{
    AspectFound *t1 = 0, *t2 = 0, *t3, *t4 = 0;
    while ((t1 = Search(Undefined_Obj, Sextile, Undefined_Obj, t1)))
    {
        while ((t2 = Search(t1->Oa, Inconjunct, Undefined_Obj, t2)))
        {
            t3 = t4 = t2;
            enum Objs o = t2->Oa == t1->Oa ? t2->Ob : t2->Oa;
            while ((t3 = Search(o, Inconjunct, t1->Ob, t3)))
            {
                auto ad = new AspConfData(Yod, 3, t1->Oa, o, t1->Ob);
                if (!Already(*ad))
                    Append(ad);
                else
                    delete ad;
            }
        }
        /*if(t4)
        {
        	t1 = t4;
        	t4 = 0;
        }*/
    }
}

void AspConfList::GetMyst_Rectangle()
{
    AspectFound *t1 = 0, *t2, *t3 = 0, *t4 = 0;
    while ((t1 = Search(Undefined_Obj, Trine, Undefined_Obj, t1)))
    {
        t2 = t1;
        while ((t2 = Search(t1->Oa, Sextile, Undefined_Obj, t2)))
        {
            while ((t3 = Search(t1->Oa, Opposition, Undefined_Obj, t3)))
            {
                t4 = t3;
                enum Objs o = t1->Oa == t3->Oa ? t3->Ob : t3->Oa;
                if (Search(o, Sextile, t1->Ob, t2) && Search(o, Trine, t2->Ob, t2) && Search(t1->Ob, Opposition, t2->Ob, 0))
                {
                    auto ad = new AspConfData(Myst_Rect, 4, t1->Oa, o, t2->Ob, t1->Ob);
                    if (!Already(*ad))
                        Append(ad);
                    else
                        delete ad;
                }
            }
        }
        /*if(t5)
        {
        	t1 = t4;
        	t4 = 0;
        }*/
    }
}

void AspConfList::GetDavid_Star()
{
    AspectFound *t1 = 0, *t2, *t3 = 0, *t4 = 0, *t5, *t6;
    while ((t1 = Search(Undefined_Obj, Sextile, Undefined_Obj, t1)))
    {
        t2 = t1;
        while ((t2 = Search(t1->Oa, Sextile, Undefined_Obj, t2)))
        {
            while ((t3 = Search(t1->Oa, Trine, Undefined_Obj, t3)))
            {
                t4 = t3;
                enum Objs o = t1->Oa == t3->Oa ? t3->Ob : t3->Oa;
                if (Search(o, Sextile, t1->Ob, t2) && Search(o, Sextile, t2->Ob, t2) && Search(t1->Ob, Trine, t2->Ob, 0))
                {
                    t5 = t1;
                    while ((t5 = Search(t1->Ob, Sextile, Undefined_Obj, t5)))
                    {
                        t6 = t1;
                        enum Objs o1 = t5->Oa == t1->Ob ? t5->Ob : t5->Oa;
                        while ((t6 = Search(o1, Sextile, Undefined_Obj, t6)))
                            if (Search(t1->Ob, Trine, o1, t3)) /*&& Search(*/
                            {
                                auto ad = new AspConfData(David_Star, 6, t1->Oa, o, t2->Ob, o1, t6->Oa == o1 ? t6->Ob : t6->Oa, t1->Ob);
                                if (!Already(*ad))
                                    Append(ad);
                                else
                                    delete ad;
                            }
                    }
                }
            }
        }
    }
}
