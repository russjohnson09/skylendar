/***************************************************************************
                          astrorestrictions.cpp  -  description
                             -------------------
    begin                : Wed Apr 18 2001
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
#include "../config.h"
#include "astrorestrictions.h"
#include "astroresources.h"
#include "editrestrictions.h"
#include "astrosql.h"
#include "astroutils.h"

#define C(a, b) for(i = a; i <= b; i++) { if(!Restr[i].Rest) c++; }
#define R(i) Restr[i].Rest

extern const struct AspectRestrictions* AspRestVector;
extern const struct Rest* RestVector;
extern const int* ScoresTable;
extern const char *AccessModes[];

AstroRestrictions::AstroRestrictions()
{
    memcpy(Restr, RestVector, sizeof(struct Rest[House_12+1]));
		for(int i = First_Star; i < Final_Star; i++)
		{
			struct Rest& r = Restr[i];
			r.Rest = true;
			r.OrbAdd = 0.0;
			r.Influence = 0;
		}
    memcpy(Asprst, AspRestVector, sizeof(struct AspectRestrictions[Unknown_Aspect]));

    Houses = DEF_HOUSES_COMP;
    Extra = DEF_EXTRA_COMP;
    Stars  = DEF_STARS_COMP;
    Minor  = DEF_MINOR_COMP;
    TrueNode = DEF_trueNODE;
    House    = DEF_HOUSESYS;
    Sidereal = DEF_TROPICAL_SIDEREAL;
    Heliocentric = DEF_HELIOCENTRIC;
    Equatorial   = DEF_EQUATORIAL;
    Dnpf         = DEF_DNPF;
    Southern     = DEF_SOUTERN;
    ProgFact     = DEF_PROG_FACT;
    MPOrbSub = 0.0;
    CountObjects();
    for (int i = 0; i < NBSCORES; i++)
        Scores[i] = ScoresTable[i];
    Idx = 0;
    LastExtra = Asr->LastExtra;
    Modified = Preload = Default = false;
    Threshold = DEF_THRESHOLD;
}

void _AstroRestrictions::CountObjects()
{
    int i, c = 0;
    C(Sun, Last_Planet);
    if (!Restr[XPoint].Rest) c++;
    if (Houses)
        C(Ascendant, House_12);
    if (Extra)
        C(First_Extra, LastExtra);
    if (Stars)
        C(First_Star, Final_Star-1);
    Count = c;
}

bool _AstroRestrictions::operator == (int index) const
{
    if (!Houses && index >= Ascendant && index <= House_12) return false;
    if (!Extra && index >= First_Extra && index <= LastExtra) return false;
    if (index > LastExtra && index < XPoint) return false;
    if (!Stars && index >= First_Star && index < Final_Star) return false;
    return !Restr[index].Rest;
}

bool _AstroRestrictions::operator != (int index) const
{
    if (!Houses && index >= Ascendant && index <= House_12) return true;
    if (!Extra && index >= First_Extra && index <= LastExtra) return true;
    if (index > LastExtra && index < XPoint) return true;
    if (!Stars && index >= First_Star && index < Final_Star) return true;
    return Restr[index].Rest;
}

void _AstroRestrictions::Restrict(int index, bool b)
{
    if (index < 0 && index >= Undefined_Obj) return;
    if (index > LastExtra && index < XPoint)
        return;
    Restr[index].Rest = b;
    if (b)
        Count--;
    else
        Count++;
}

void _AstroRestrictions::AspRestrict(int index, bool b)
{
    if (index < 0 && index > Unknown_Aspect)
        return;
    Asprst[index].Rest = b;
}

bool AstroRestrictions::Edit()
{
#ifdef QT
    EditRestrictions er(this);
    CountObjects();
    return er.exec() ==  QDialog::Accepted;
#endif
}

AstroRestrictionsList::AstroRestrictionsList()
{
    Max = BOUND;
    AstroRequest arq;
    AstroRestrictions* ar;
    AstroString s = "#" + Asr->DbUser;
    Drs = new AstroRestrictions;
    Drs->Idx = 1;
    Drs->Name = s;
		Drs->Default = true;
    if (arq.Exec("SELECT Idx FROM Restrictions WHERE Name = '%a'", &s) && arq.Valid())
			Drs->DbFetch(arq.GetInt("Idx", 1));
    else
        Drs->DbSave();
		Drs->Name = i18n("Default restrictions set");
    Append(Drs);
    if (arq.Exec("SELECT Idx FROM Restrictions WHERE Preload = 't' AND Idx <> 1 ORDER BY Idx") && arq.Valid())
        do
        {
            ar = new AstroRestrictions;
            ar->DbFetch(arq.GetInt("Idx"));
            AddRestrictions(ar);
        }
        while (arq.Next());
}

void AstroRestrictionsList::AddRestrictions(AstroRestrictions* ar)
{
    if (ar->Idx == 0)
        ar->Idx = ++Max;
    Append(ar);
}

AstroRestrictionsList::~AstroRestrictionsList()
{}

AstroRestrictions* AstroRestrictionsList::Get(Index idx) const
{
    foreachc(*this, AstroRestrictionsList)
    if ((!it)->Idx == idx)
        return CSC(AstroRestrictions*, !it);
    return 0;
}

AstroRestrictions* AstroRestrictionsList::GetDefault() const
{
    foreachc(*this, AstroRestrictionsList)
    if ((!it)->Default)
        return CSC(AstroRestrictions*, !it);
    return 0;
}

bool AstroRestrictions::DbFetch(Index idx)
{
    int g;
    AstroRequest arq;
    if (!arq.Exec(
                "SELECT Name, Houses, Extra, Stars, Minor, HousesSys, TrueNode, Dnpf, Southern, Heliocentric, Equatorial, Sidereal, S1, S2, S3, S4, S5, S6, S7, S8, S9, MPOrbSub, Preload, ProgFact, Threshold FROM Restrictions WHERE Idx = %d"
				, idx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch restrictions set"));
        return false;
    }
    Idx = idx;
    Name   = arq < "Name";
    Houses = arq.GetBool("Houses");
    Extra = arq.GetBool("Extra");
    Stars  = arq.GetBool("Stars");
    Minor  = arq.GetBool("Minor");
    House  = (enum House)arq.GetInt("HousesSys");
    TrueNode = arq.GetBool("TrueNode");
    Dnpf     = arq.GetBool("Dnpf");
    Southern = arq.GetBool("Southern");
    Heliocentric = arq.GetBool("Heliocentric");
    Equatorial   = arq.GetBool("Equatorial");
    Sidereal = (enum Sidereal)arq.GetInt("Sidereal");
    ProgFact = arq.GetDouble("ProgFact");
    Scores[0] = arq.GetInt("S1", ScoresTable[0]);
    Scores[1] = arq.GetInt("S2", ScoresTable[1]);
    Scores[2] = arq.GetInt("S3", ScoresTable[2]);
    Scores[3] = arq.GetInt("S4", ScoresTable[3]);
    Scores[4] = arq.GetInt("S5", ScoresTable[4]);
    Scores[5] = arq.GetInt("S6", ScoresTable[5]);
    Scores[6] = arq.GetInt("S7", ScoresTable[6]);
    Scores[7] = arq.GetInt("S8", ScoresTable[7]);
    Scores[8] = arq.GetInt("S9", ScoresTable[8]);
    MPOrbSub  = arq.GetDouble("MPOrbSub");
    Threshold = arq.GetInt("Threshold");
    Preload   = arq.GetBool("Preload");
    if (!arq.Exec("SELECT ObjIndex, Rest, OrbAdd, Influence FROM ObjRest WHERE Index = %d", idx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch restrictions set"));
        return false;
    }
    do
    {
			g                 = arq.GetInt("ObjIndex");
      if (g < 0 || g >= Final_Star) continue;
      Restr[g].Rest      = arq.GetBool("Rest");
      Restr[g].OrbAdd    = arq.GetDouble("OrbAdd");
      Restr[g].Influence = arq.GetInt("Influence");
			
    }
    while (arq.Next());
    if (!arq.Exec("SELECT AspIndex, Rest, Orb, Color, Influence FROM AspRest WHERE Index = %d", idx) || !arq.Valid(true))
    {
        AstroMessage(i18n("Can't fetch restrictions set"));
        return false;
    }
    do
    {
			g                   = arq.GetInt("AspIndex");
      if (g < 0 || g >= Unknown_Aspect) continue;
      Asprst[g].Rest      = arq.GetBool("Rest");
      Asprst[g].Orb       = arq.GetDouble("Orb");
      Asprst[g].Color     = arq.GetInt("Color");
      Asprst[g].Influence = arq.GetInt("Influence");
    }
    while (arq.Next());
    CountObjects();
    return true;
}

bool AstroRestrictions::DbFetch(const AstroString& name)
{
    AstroRequest arq;
    if (!arq.Exec("SELECT Idx FROM Restrictions WHERE Name = '%a'", &name) || !arq.Valid(true))
        return false;
    return DbFetch(arq.GetInt("Idx"));
}

void AstroRestrictions::ObjIU(AstroRequest& arq, int f, int l, bool update)
{
    bool ret;
    for (int i = f; i <= l; i++)
    {
        const struct Rest& rest = Restr[i];
        if (update)
            ret = arq.Exec("UPDATE ObjRest SET Rest = %b, OrbAdd = %f, Influence = %d WHERE Index = %d AND ObjIndex = %d", rest.Rest, rest.OrbAdd, rest.Influence, Idx, i);
        else
            ret = arq.Exec("INSERT INTO ObjRest (ObjIndex, Rest, OrbAdd, Influence, Index) VALUES (%d, %b, %f, %d, %d)", i, rest.Rest, rest.OrbAdd, rest.Influence, Idx);
        if (!ret)
        {
            AstroMessage(i18n("Can't INSERT/UPDATE the restrictions data"));
            return;
        }
    }
}

Index AstroRestrictions::DbSave()
{
    bool update = false;
    Index idx;
    AstroRequest arq;
    if (arq.Exec("SELECT Idx FROM Restrictions WHERE Name = '%a'", &Name) && arq.Valid() && Index(arq.GetInt("Idx")) != Idx)
    {
        AstroMessage(i18n("Sorry, a restrictions set with the same name already exists."), false);
        return Idx;
    }
		if(Default) Name = "#" + Asr->DbUser;
#ifdef IFEXCEPT
    arq.SetException(true);
    try
    {
#endif
        arq.Begin();
				if(!arq.Exec("SELECT EXISTS(SELECT Idx FROM Restrictions WHERE Idx = %d)", Idx) || !arq.GetBool("exists", false))
        {
            idx = arq.NextId("Restrictions");
            if (!arq.Exec("INSERT INTO Restrictions (Idx, Name, Houses, Extra, Stars, Minor, HousesSys, TrueNode, Dnpf, Southern, Heliocentric, Equatorial, Sidereal, S1, S2, S3, S4, S5, S6, S7, S8, S9, MPOrbSub, Preload, ProgFact, Threshold) VALUES (%d, '%a', %b, %b, %b, %b, %d, %b, %b, %b, %b, %b, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %f, %b, %f, %d)", idx, &Name, Houses, Extra, Stars, Minor, House, TrueNode, Dnpf, Southern, Heliocentric, Equatorial, Sidereal, Scores[0], Scores[1], Scores[2], Scores[3], Scores[4], Scores[5], Scores[6], Scores[7], Scores[8], MPOrbSub, Preload, ProgFact, Threshold))
            {
                AstroMessage(i18n("Can't save restrictions set"));
								if(Default) Name = i18n("Default restrictions set"); 
                return Idx;
            }
            Idx = idx;
        }
        else
        {
					  update = true;
            if (!arq.Exec("UPDATE Restrictions SET Name = '%a', Houses = %b, Extra = %b, Stars = %b, Minor = %b, HousesSys = %d, TrueNode = %b, Dnpf = %b, Southern = %b, Heliocentric = %b, Equatorial = %b, Sidereal = %d, S1 = %d, S2 = %d, S3 = %d, S4 = %d, S5 = %d, S6 = %d, S7 = %d, S8 = %d, S9 = %d, MPOrbSub = %f, Preload = %b, ProgFact = %f, Threshold = %d WHERE Idx = %d", &Name, Houses, Extra, Stars, Minor, House, TrueNode, Dnpf, Southern, Heliocentric, Equatorial, Sidereal, Scores[0], Scores[1], Scores[2], Scores[3], Scores[4], Scores[5], Scores[6], Scores[7], Scores[8], MPOrbSub, Preload, ProgFact, Threshold, Idx))
            {
                AstroMessage(i18n("Can't save restrictions set"));
								if(Default) Name = i18n("Default restrictions set");
                return Idx;
            }
        }
				if(!arq.Effective())
				{
					AstroMessage(i18n("You probably don't have sufficient privileges to do that"));
					if(Default) Name = i18n("Default restrictions set");
                return Idx;
				}
				if (update)
				{
            arq.Exec("SELECT * FROM ObjRest WHERE Index = %d FOR UPDATE", Idx);
            arq.Exec("SELECT * FROM AspRest WHERE Index = %d FOR UPDATE", Idx);
				}
        ObjIU(arq, Sun, Last_Planet, update);
        ObjIU(arq, XPoint, House_12, update);
        ObjIU(arq, First_Extra, LastExtra, update);
        ObjIU(arq, First_Star, Final_Star-1, update);
        for (int i = Conjunction; i < Unknown_Aspect; i++)
        {
            if (update)
                arq.Exec("UPDATE AspRest SET Rest = %b, Orb = %f, Color = %d, Influence = %d WHERE Index = %d AND AspIndex = %d",Asprst[i].Rest, Asprst[i].Orb, Asprst[i].Color, Asprst[i].Influence, Idx, i);
            else
                arq.Exec("INSERT INTO AspRest (AspIndex, Rest, Orb, Color, Influence, Index) VALUES (%d, %b, %f, %d, %d, %d)", i, Asprst[i].Rest, Asprst[i].Orb, Asprst[i].Color, Asprst[i].Influence, Idx);
        }
        arq.Commit();
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        arq.Rollback();
        Exception(ae);
    }
#endif
		if(Default) Name = i18n("Default restrictions set");
    return Idx;
}

void AstroRestrictions::RestrictAll()
{
    Houses = Extra = Stars = false;
    for (int i = Sun; i <= Last_Planet; i++)
        Restr[i].Rest = true;
    Count = 0;
}

void  AstroRestrictions::RestrictAllAsps()
{
    for (int i = Conjunction; i < Unknown_Aspect; i++)
        Asprst[i].Rest = true;
}

bool _AstroRestrictions::operator()(fun f) const
{
	for (int i = Sun; i <= Last_Planet; i++) if (!R(i)) f(i);
	if (!R(XPoint)) f(XPoint);
	if (Houses)
		for (int i = Ascendant; i <= House_12; i++) if(!R(i)) f(i);
	if(Extra)
		for (int i = First_Extra; i <= LastExtra; i++) if(!R(i)) f(i);
	if(Stars)
		for (int i = First_Star; i < Final_Star; i++) if(!R(i)) f(i);
	return true;
}

bool _AstroRestrictions::Iterate(fun f, bool extras, bool houses, bool stars) const
{
	for (int i = Sun; i <= Last_Planet; i++) if (!R(i)) f(i);
	if (!R(XPoint)) f(XPoint);
	if (Houses && houses)
		for (int i = Ascendant; i <= House_12; i++) if(!R(i)) f(i);
	if(Extra && extras)
		for (int i = First_Extra; i <= LastExtra; i++) if(!R(i)) f(i);
	if(Stars && stars)
		for (int i = First_Star; i < Final_Star; i++) if(!R(i)) f(i);
	return true;
}

int _AstroRestrictions::operator+(int i) const
{
	for(++i; i < Final_Star; i++)
	{
		if (i >= First_Extra && i <= LastExtra && !Extra) i = XPoint;
    if (i > LastExtra && i < XPoint) i = XPoint;
		if (i == XPoint && !Restr[i].Rest) return i;
    if (i >= Ascendant && i <= House_12 && !Houses) i = First_Star;
    if (i >= First_Star && i < Final_Star && !Stars) return Undefined_Obj;
		if (!Restr[i].Rest) return i;
	}
	return Undefined_Obj;
}

void _AstroRestrictions::SetHousesSys(enum House house, bool hide)
{
    House = house;
    if (hide)
        Restr[House_1].Rest  = Restr[House_4].Rest  = Restr[House_7].Rest  = Restr[House_10].Rest = (house == Vehlow || house == Azimuthal) ? false : true;
}

bool AstroRestrictionsList::RemoveFromDb(Index idx)
{
    bool b;
    AstroRequest arq;
    Remove(Get(idx));
    if (idx >= BOUND)
        return true;
#ifdef IFEXCEPT
    arq.SetException(true);
    try
    {
#endif
        arq.Begin();
        b = arq.Exec("DELETE FROM Restrictions WHERE Idx = %d", idx);
        arq.Commit();
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        arq.Rollback();
        Exception(ae);
    }
#else
        if (!b)
            AstroMessage(i18n("Problem in restrictions set deletion"));
#endif
    return b;
}

bool AstroRestrictionsList::CheckName(const AstroString& as, Index idx)
{
    AstroRequest arq;
    bool ret = false;
    foreachc(*this, AstroRestrictionsList)
    if ((!it)->Idx != idx && (!it)->Name == as)
        ret = true;
    if (arq.Exec("SELECT Idx FROM Restrictions WHERE Name = '%a'", &as) && arq.Valid() && arq.GetInt("Idx") != idx)
        ret = true;
    return ret;
}

