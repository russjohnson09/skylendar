/***************************************************************************
                          astrochart.cpp  -  description
                             -------------------
    begin                : Mon Oct 16 2000
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
#include "../config.h"
#include "astrosql.h"
#include "astrochart.h"
#include "astroparams.h"
#include "stdwheelchart.h"
#include "stdgraphiclist.h"
#include "aspscanlist.h"
#include "localhorizonchart.h"
#include "astroobjectslist.h"
#include "astroaspectsarray.h"
#include "astroprocess.h"
#include "astroaspects.h"
#include "astroephemeris.h"
#include "astrograph.h"
#include "squared.h"
#include "solarsyschart.h"
#include "astrotarotspreads.h"
#include "astrodirections.h"
#include "astromainwindow.h"
#include "astrogauquelinchart.h"
#include "astrohousepos.h"
#include "astrobatch.h"

#define PL(i) &(ao < ((ao / i)->planet))
#define SCO(i) (ao / i)->score

AstroChart::AstroChart(bool owninterface)
{
    for (int i = 0; i < NBDATA; i++) Ov[i] = nullptr;
    Cbp = new ChartBaseParams(SC(ChartParams *,Asr), owninterface ? CreateInterface() : Asf);
    Ahl->Append(this);
}

AstroChart::~AstroChart()
{
    delete Acb;
    for (int i = 0; i < NBDATA; i++)
        delete Ov[i];
    delete Cbp->Aif;
    delete Cbp;
    Ahl->Remove(this);
}

/** This method displays the chart according to
the Chart Type */
bool AstroChart::Display(bool redraw)
{
    if (Acb)
    {
        if (Ct != Acb->GetCt())
        {
            delete Acb;
            CreateChart(redraw);
        }
        else
        {
            PreRedraw(redraw);
            bool b =  Acb->Redisplay();
            PostRedraw();
            return b;
        }
    }
    else
        CreateChart(redraw);
    return true;
}

/** This method creates an Acb according to ct */
void AstroChart::CreateChart(bool redraw)
{
    switch (Ct)
    {
    case NullChart   :
        Acb = new EmptyChart(Cbp, &Ov);
        break;
    case StdWheels   :
        Acb = new StdWheelChart(Cbp, &Ov);
        break;
    case GraphicList :
        Acb = new StdGraphicList(Cbp, &Ov);
        break;
    case AspScList   :
        Acb = new AspScanList(Cbp, &Ov);
        break;
    case LocalHorizon:
        Acb = new LocalHorizonChart(Cbp, &Ov);
        break;
    case ObjectList  :
        Acb = new AstroObjectsList(Cbp, &Ov);
        break;
    case AspectsArray:
        Acb = new AstroAspectsArray(Cbp, &Ov);
        break;
    case Ephemeris   :
        Acb = new AstroEphemeris(Cbp, &Ov);
        break;
    case Astro_Graph :
        Acb = new AstroGraph(Cbp, &Ov);
        break;
    case Squared     :
        Acb = new SquaredChart(Cbp, &Ov);
        break;
    case SolarSys    :
        Acb = new SolarSysChart(Cbp, &Ov);
        break;
    case House_Pos   :
        Acb = new AstroHousePos(Cbp, &Ov);
        break;
    case Tarots_Spreads:
        Acb = new AstroTarotSpreads(Cbp, &Ov);
        break;
    case Directions:
        Acb = new AstroDirections(Cbp, &Ov);
        break;
    case Gauquelin:
        Acb = new AstroGauquelinChart(Cbp, &Ov);
        break;
    case Batch:
        Acb = new AstroBatch(Cbp, &Ov);
        break;
    case TensorFlow:
        Acb = new TensorFlowChart(Cbp, &Ov);
        break;
    default:
        ;
    };
    if (redraw)
    {
        Acb->PostRecompute();
        if (Ct != AspScList)
        {
            PreRedraw(redraw);
            Acb->Redisplay();
            PostRedraw();
        }
    }
}

void AstroChart::Repaint(bool b)
{
	if (Acb && b && (Ct == AspScList || Ct == Ephemeris || Ct == GraphicList || Ct == Directions))
	//if(b && (DC(GraphicListBase*, Acb) != nullptr))
		Acb->PostRecompute();
}

void AstroChart::SetData(AstroData *ad, int i, bool placeonly)
{
    if (i < 0 || i >= NBDATA)
        return;
    if (!Ov[i])
    {
        Ov[i] = new AstroObjs(*ad, this, i);
        Ov[i]->SetInterface(Cbp->Aif);
        if (Acb)
        {
					Acb->GetFS();
					Acb->PostSetData(i);
					UpdateRestrict(Drs);
        }
    }
    else
    {
        auto adp = SC(AstroData *,Ov[i]);
        if (!placeonly)
            *adp = *ad;
        adp->SetInterface(Cbp->Aif);
        Acb->GetFS();
        adp->Recompute();
    }
}

int AstroChart::IfData(const AstroData* ad, bool placeonly) const
{
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i] && (placeonly ? (Ov[i]->PlaceIdx == ad->PlaceIdx) : (Ov[i]->Idx == ad->Idx)))
            return i;
    return -1;
}

bool AstroChart::EditChartParams()
{
    if (Cbp->Edit())
    {
        for (int i = 0; i < NBDATA; i++)
            if (Ov[i])
            {
                *SC(ChartParams*, Ov[i]) = *SC(ChartParams*, Cbp);
                Ov[i]->Recompute();
            }
    }
    return true;
}

int AstroChart::IfRestrict(const AstroRestrictions* ar) const
{
    for (int i = 0; i < NBDATA; i++)
			if (Ov[i] && ~*Ov[i] && (*Ov[i])().Idx == ar->Idx)
            return i;
    return -1;
}

bool AstroChart::UpdateRestrict(AstroRestrictions *ar)
{
    bool ret = false;
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i] && ~*Ov[i] && (~*Ov[i])->Idx == ar->Idx)
        {
            SetRestrict(ar, i);
            ret = true;
        }
    return ret;
}

bool AstroChart::UpdateData(AstroData *ad, bool placeonly)
{
    bool ret = false;
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i] && (placeonly ? (Ov[i]->PlaceIdx == ad->PlaceIdx) : (Ov[i]->Idx == ad->Idx)))
        {
            SetData(ad, i);
            ret =  true;
        }
    return ret;
}

bool AstroChart::UpdateZif(Index idx, const char* zif)
{
    bool ret = false;
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i] && Ov[i]->CountryIdx == idx)
        {
            Ov[i]->SetTZ(zif);
            Ov[i]->Recompute();
            ret = true;
        }
    return ret;
}

void AstroChart::SetRestrict(AstroRestrictions* ar, int i)
{
    if (i < 0 || i >= NBDATA) return;
    if (Ov[i])
    {
        Ov[i]->SetRestrict(ar);
        //Cbp->Aif->SetRestrict(ar, i);
        Ov[i]->Recompute();
    }
    else
        AstroMessage(i18n("Can't set this restrictions set for an empty ring"));
}

int AstroChart::NbSingle() const
{
    int s = 0;
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i] && Ov[i]->GetSubType() == Single)
            s++;
    return s;
}

bool AstroChart::Show(int i)
{
    int nb = 0;
    AstroObjs& ao = *Ov[i];
    if (ao.Show)
    {
        for (int j = 0; j < NBDATA; j++)
            if (Ov[j] && Ov[j]->Show)
                nb++;
        if (nb == 1)
            return false;
    }
    ao.Show = !ao.Show;
    Acb->GetFS();
    return true;
}

bool AstroChart::SetSubType(ChartSubType cst, int i)
{
    int nbs = NbSingle();
    if (i < 0 || i >= NBDATA) return false;
    if (!Ov[i])
        SetData(Adl->Get(0), i, true);
    AstroObjs& ao = *Ov[i];
    switch (cst)
    {
    case NoSt:
        break;
    case Show_Hide:
        return Show(i);
    case Single:
        Acb->GetFS();
        ao.SetSubChart(cst);
        ao.Recompute();
        break;
    case Transit:
    case Direction:
    case Progression:
    case AddAngle:
    case MulAngle:
    case Composite:
    case TimeSpace:
    case SolarArc:
    case Profection:
        if (nbs == 1 &&  cst != Single && ao.GetSubType() == Single)
            //if(nbs == 0 || (nbs == 1 && cst != Single && cst != Show_Hide && ao.GetSubType() == Single))
            return false;
        else
        {
            ao.SetSubChart(cst);
            Acb->GetFS();
            ao.Recompute();
        }
        break;
    default:
        ;
    }
    return true;
}

Index AstroChart::ExtractandSave(int i, Index& oldidx, bool& createnew, const AstroFoundAspectsList* afal)
{
    AstroRequest arq;
    AstroString as;
    char c, c1;
    if (i < 0 || i >= NBDATA || !Ov[i]) return 0;
    AstroObjs &ao = *Ov[i];
    const AstroObjs& fs = Acb->GetRef(ao.ARef);
    Index restidx, f = fs.Idx;
    enum ChartSubType cst = ao.GetSubType();
    enum SubTypeState sts = ao.GetState();
    oldidx = ao.Idx;
    restidx = ao().Idx;
    if (restidx >= BOUND)
        restidx = 0;
    createnew = false;
    if (ao.Idx == 0) return 0;
    if (fs.Modified || fs.Idx >= BOUND)
    {
        AstroMessage(Sprintf(i18n("The Data set %a should be saved\n before extracting these values"), &as, &fs.Name), false);
        return 0;
    }
    switch (cst)
    {
    case Single :
        c = 'S';
        break;
    case Transit:
        c = 'T';
        break;
    case Direction:
        c = 'D';
        break;
    case Progression:
        c = 'P';
        break;
    case AddAngle:
        c = 'A';
        break;
    case MulAngle:
        c = 'M';
        break;
    case Composite:
        c = 'C';
        break;
    case TimeSpace:
        c = 'I';
        break;
    case SolarArc:
        c = 'R';
        break;
    case Profection:
        c = 'F';
        break;
    default:
        c = 'X';
    };
    switch (sts)
    {
    case Master:
        c1 = 'M';
        break;
    case Slave:
        c1 = 'S';
        break;
    case AMaster:
        c1 = 'A';
        break;
    case ASlave:
        c1 = 'a';
        break;
    default:
        c1 = 'x';
    };
#ifdef IFEXCEPT
    arq.SetException(true);
    try
    {
#endif
        if (ao.Modified || ao.Idx >= BOUND)
        {
            if (c != 'S' && ao.Name.isEmpty())
            {
                int k = 0;
                auto ad = new AstroData(ao);
                ad->Idx = 1;
                arq.Exec("SELECT MAX(Idx) FROM Data");
                if (arq.Valid())
                    k = arq.GetInt("Max") + 1;
                ad->Name = Sprintf("%a #%d on %a", &as, &ao.GetSubTypeName(), k, &fs.Name);
                Adl->AddData(ad);
                createnew = true;
                ad->DbSave();
                SetData(ad, i);
            }
            else
                ao.DbSave();
        }
        arq.Exec("SELECT DataIdx,Type FROM VDV WHERE Idx = %d", ao.Idx);
        char type = 0;
        bool valid = arq.Valid();
        if (valid)
            type = arq.GetChar("Type");
        arq.Begin();
        if (valid && type == c)
        {
            arq.Exec("UPDATE VData SET RefIdx = %d, RestIdx = %d, Type = '%c', State = '%c' WHERE DataIdx = %d",
                     f,restidx, c, c1, ao.Idx);
            arq.Exec("DELETE FROM Obj WHERE DataIdx = %d", ao.Idx);
            arq.Exec("DELETE FROM Asp WHERE DataIdx = %d", ao.Idx);
        }
        else
        {
            arq.Exec("INSERT INTO VData (DataIdx, RefIdx, RestIdx, Type, State) VALUES (%d, %d, %d, '%c', '%c')",
                     ao.Idx, f, restidx, c, c1);
        }
        if (cst == AddAngle || cst == MulAngle)
            arq.Exec("UPDATE VData SET Angle = %f WHERE DataIdx = %d", ao.Angle, ao.Idx);
        for (int j = Sun; j <= Last_Planet; j++)
            if (ao == j)
            {
                arq.Exec("INSERT INTO Obj (DataIdx, Id, Lon, Lat, Retro, InHouse) VALUES (%d, '%a', %f, %f, %b, %d)",
                         ao.Idx, &(ao < j), ao * j, (*ao[j])[1], ao[j]->Retro, ao.InHouse(j));
            }
        if (ao.IfHouses())
        {
            for (int j = Ascendant; j <= House_12; j++)
                if (ao == j)
                    arq.Exec("INSERT INTO Obj (DataIdx, Id, Lon, Lat, Retro, InHouse) VALUES (%d, '%a', %f, %f, %b, %d)",
                             ao.Idx, &(ao < j), ao * j, (*ao[j])[1], ao[j]->Retro, ao.InHouse(j));

        }
        if (ao.IfExtra())
        {
            for (int j = First_Extra; j <= Asr->LastExtra; j++)
                if (ao == j)
                    arq.Exec("INSERT INTO Obj (DataIdx, Id, Lon, Lat, Retro, InHouse) VALUES (%d, '%a', %f, %f, %b, %d)",
                             ao.Idx, &(ao < j), ao * j, (*ao[j])[1], ao[j]->Retro, ao.InHouse(j));

        }
        if (ao.IfStars())
        {
            for (int j = First_Star; j < Final_Star; j++)
                if (ao == j)
                    arq.Exec("INSERT INTO Obj (DataIdx, Id, Lon, Lat, Retro, InHouse) VALUES (%d, '%a', %f, %f, %b, %d)",
                             ao.Idx, &(ao < j), ao * j, (*ao[j])[1], ao[j]->Retro, ao.InHouse(j));

        }
        if (afal)
        {
            AstroAspects aa(~ao);
            AstroFoundAspectsList& a = (AstroFoundAspectsList&)*afal;
            AlAf& alaf = ~a;
            foreachc(a, AstroFoundAspectsList)
            {
                char c;
                const AspectFound* af = (!it);
                switch (af->AspectSide)
                {
                case Exact:
                    c = 'E';
                    break;
                case Applying:
                    c = 'A';
                    break;
                case Separating:
                    c = 'S';
                    break;
                default:
                    ;
                };
                as = ao < af->Oa;
                as += '-';
                as += ao < af->Ob;
                arq.Exec("INSERT INTO Asp (DataIdx, Objs, AspId, Orb, Pos) VALUES (%d, '%a', '%a', %f, '%c')",
                         ao.Idx, &as, &(aa < af->Asp), af->ExtraOrb, c);
            }
            foreachc(alaf, AlAf)
            {
                char c, w;
                const AspectFound* af = (!it);
                switch (af->AspectSide)
                {
                case Exact:
                    c = 'E';
                    break;
                case Applying:
                    c = 'A';
                    break;
                case Separating:
                    c = 'S';
                    break;
                default:
                    ;
                };
                switch (af->AspWay)
                {
                case LeftAspect:
                    w = 'L';
                    break;
                case RightAspect:
                    w = 'R';
                    break;
                default:
                    w = ' ';
                };
                as = ao < af->Oa;
                as += '/';
                as +=  ao < af->Oc;
                as += '-';
                as += ao < af->Ob;
                arq.Exec("INSERT INTO Asp (DataIdx, Objs, AspId, Orb, Pos, Way) VALUES (%d, '%a', '%a', %f, '%c', '%c')",
                         ao.Idx, &as, &(aa < af->Asp), af->ExtraOrb, c, w);
            }
        }
        if (ao.GetSubType() == Single && ao / 0)
        {
            arq.Exec("DELETE FROM Ranks WHERE DataIdx = %d", ao.Idx);
            for (int i = 0; i < 10; i++)
                arq.Exec("INSERT INTO Ranks (DataIdx, Rank, Planet, Score) VALUES (%d, %d, '%a', %d)", ao.Idx, i + 1, PL(i), SCO(i));
        }
        arq.Commit();
        return ao.Idx;
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        arq.Rollback();
        Exception(ae);
        return 0;
    }
#endif
}

bool AstroChart::Save()
{
    AstroRequest arq;
    AstroString as, title;
    char type;
    double angle = 0.0;
    AstroTarotSpreads* act = DC(AstroTarotSpreads*, Acb);
    foreachc(*Ahl, AstroChartList)
    if ((!it)->Acb != Acb && (!it)->Acb->OwnTitle == Acb->OwnTitle)
    {
        AstroMessage(i18n("Sorry this chart already exists"), false);
        return false;
    }
    Acb->GetTitle(title);
    if (arq.Exec("SELECT Idx FROM Charts WHERE Name = '%a'", &title) && arq.Valid())
    {
        if (AstroQuestion(i18n("This chart already exists. Overwrite it ?")))
            Idx = arq.GetInt("Idx", 0);
        else
            return false;
    }
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i])
        {
            if (Ov[i]->Idx == 0)
            {
                AstroMessage(i18n("Sorry, you can't save a chart with 'Now' as a DataSet"), false);
                return false;
            }
            else if (Ov[i]->Idx >= BOUND)
            {
                AstroMessage(Sprintf(i18n("Sorry, the DataSet '%a' must be saved before"), &as, &Ov[i]->Name), false);
                return false;
            }
        }
#ifdef IFEXCEPT
    arq.SetException(true);
    try
    {
#endif
        arq.Begin();
        switch (Acb->Ct)
        {
        case StdWheels :
            type = 'W';
            break;
        case GraphicList:
            type = 'L';
            break;
        case LocalHorizon:
            type = 'H';
            break;
        case AspectsArray:
            type = 'A';
            break;
        case Astro_Graph:
            type = 'G';
            break;
        case Squared:
            type = 'S';
            break;
        case SolarSys:
            type = 'Y';
            break;
        case Tarots_Spreads:
            type = 'T';
            break;
        case Gauquelin:
            type = 'Q';
            break;
        case House_Pos:
            type = 'P';
        default:
            AstroMessage(i18n("Sorry, this chart has not been designed to be saved"));
            return false;
        };
        if (Idx > 0)
        {
            arq.Exec("DELETE FROM Ring WHERE ChartIdx = %d", Idx);
            arq.Exec(
                                         "UPDATE Charts SET Name = '%a', Type = '%c', Flags = %l, ExtraFlags = %d, Date = current_TimeStamp WHERE Idx = %d",
                                         &title, type, Acb->Cbp->GetFlags(),  Acb->Ct == Tarots_Spreads ? int(act->Ts) : int(Acb->Cbp->Subring), Idx);
        }
        else
        {
            Idx = arq.NextId("Chart");
            arq.Exec(
                                         "INSERT INTO Charts (Idx, Name, Type, Flags, ExtraFlags) VALUES (%d, '%a','%c', %l, %d)",
                                         Idx, &title, type, Acb->Cbp->GetFlags(), Acb->Ct == Tarots_Spreads ? int(act->Ts) : int(Acb->Cbp->Subring));
        }	
        for (int i = 0; i < NBDATA; i++)
            if (Ov[i])
            {
                const AstroObjs& ao = *(Ov[i]);
                char nb = '1' + i, subtype, state;
                switch (-ao)
                {
                case Single:
                    subtype = 'S';
                    break;
                case Transit:
                    subtype = 'T';
                    break;
                case Direction:
                    subtype = 'D';
                    break;
                case Progression:
                    subtype = 'P';
                    break;
                case AddAngle:
                    subtype = 'A';
                    angle = Ov[i]->Angle;
                    break;
                case MulAngle:
                    subtype = 'M';
                    angle = Ov[i]->Angle;
                    break;
                case Composite:
                    subtype = 'C';
                    break;
                case TimeSpace:
                    subtype = 'I';
                    break;
                case SolarArc:
                    subtype = 'R';
                    break;
                case Profection:
                    subtype = 'F';
                    break;
                default:
                    ;
                };
                switch (ao.GetState())
                {
                case Master:
                    state = 'M';
                    break;
                case Slave:
                    state = 'S';
                    break;
                case AMaster:
                    state = 'A';
                    break;
                case ASlave:
                    state = 'a';
                    break;
                default:
                    state = 'x';
                };
                arq.Exec(
												 "INSERT INTO Ring (ChartIdx, RingNb, Subtype, Hidden, Angle, DataIdx, RestrIdx, State) VALUES(%d, '%c', '%c', %b, %f, %d, %d, '%c')",
												 Idx, nb, subtype, !ao.Show, ao.Angle, ao.Idx, (~ao)->Idx, state);
            }
        if (act && Acb->Ct == Tarots_Spreads)
            act->Save(arq, Idx);
        arq.Commit();
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        arq.Rollback();
        Exception(ae);
        return false;
    }
#endif
    return true;
}

void AstroChart::SetAFirst(int ring)
{
    if (Acb && Acb->Cbp->AFirst)
    {
        if (Acb->Cbp->AFirst->GetRing() == ring)
        {
            Acb->Cbp->AFirst = 0;
            for (int i = 0; i < NBDATA; i++)
                if (Ov[i] && Ov[i]->ARef)
                {
                    Ov[i]->ARef = false;
                    Ov[i]->Recompute();
                }
        }
        else
        {
            for (int i = 0; i < NBDATA; i++)
                if (Ov[i] && Ov[i]->GetRing() == ring)
                {
                    Acb->Cbp->AFirst = Ov[i];
                    Acb->Cbp->AFirst->ARef = false;
                    break;
                }
            for (int i = 0; i < NBDATA; i++)
                if (Ov[i] && Ov[i]->ARef) Ov[i]->Recompute();
        }
        return;
    }
    Acb->Cbp->AFirst = Ov[ring];
}

bool AstroChart::SetASecond(int ring)
{
    if (Acb && Acb->Cbp->AFirst == nullptr) return false;
    for (int i = 0; i < NBDATA; i++)
        if (Ov[i] && Ov[i]->GetRing() == ring)
        {
            Ov[i]->ARef = !Ov[i]->ARef;
            Ov[i]->Recompute();
            break;
        }
    return true;
}


void AstroChartList::UpdateData(AstroData* ad, bool placeonly)
{
    foreach(*this, AstroChartList)
    {
        if ((*it)->UpdateData(ad, placeonly))
            (*it)->Repaint();
    }
}

void AstroChartList::UpdateZif(Index idx, const char* zif)
{
    foreach(*this, AstroChartList)
    {
        if ((*it)->UpdateZif(idx, zif))
            (*it)->Repaint();
    }
}

void AstroChartList::UpdateRestrict(AstroRestrictions* ar)
{
    foreach(*this, AstroChartList)
    {
        if ((*it)->UpdateRestrict(ar))
            (*it)->Repaint();
    }
}

bool AstroChartList::CheckIdx(Index idx)
{
    AstroObjs* ao;
    foreachc(*this, AstroChartList)
    {
        const AstroChart& ac = *(!it);
        for (int i = 0; i < NBDATA; i++)
        {
            ao = ac[i];
            if (ao && ao->Idx == idx)
                return true;
        }
    }
    return false;
}

bool AstroChartList::CheckPlaceIdx(Index idx, bool country)
{
    AstroObjs* ao;
    foreachc(*this, AstroChartList)
    {
        const AstroChart& ac = *(!it);
        for (int i = 0; i < NBDATA; i++)
        {
            ao = ac[i];
            if (ao && ((country ? ao->CountryIdx : ao->PlaceIdx) == idx))
                return true;
        }
    }
    return false;
}

void AstroChartList::ChangeIdx(Index oldidx, Index newidx)
{
    AstroObjs* ao;
    foreach(*this, AstroChartList)
    {
        AstroChart& ac = *(*it);
        for (int i = 0; i < NBDATA; i++)
        {
            ao = ac[i];
            if (ao && ao->Idx == oldidx)
            {
                ao->Idx = newidx;
                ao->Modified = false;
            }
        }
    }
}

bool AstroChartList::Load(Index idx, AstroChart& ac)
{
    AstroRequest arq;
    AstroString name;
    Index dataidx, restridx;
    double angle = 0.0;
    int ring;
    Long flags;
    unsigned long extraflags;
    if (arq.Exec("SELECT * FROM Charts WHERE Idx = %d", idx) && arq.Valid(true))
    {
        enum ChartType ct;
        enum ChartSubType cst;
        enum SubTypeState sts[NBDATA];
        ac.Idx = idx;
        name = arq < "Name";
        flags = arq.GetLong("Flags", 0);
        switch (arq.GetChar("Type", 'W'))
        {
        case 'W':
            ct = StdWheels;
            break;
        case 'L':
            ct = GraphicList;
            break;
        case 'H':
            ct = LocalHorizon;
            break;
        case 'A':
            ct = AspectsArray;
            break;
        case 'G':
            ct = Astro_Graph;
            break;
        case 'S':
            ct = Squared;
            break;
        case 'Y':
            ct = SolarSys;
            break;
        case 'T':
            ct = Tarots_Spreads;
            break;
        case 'Q':
            ct = Gauquelin;
            break;
        case 'P':
            ct = House_Pos;
            break;
        default:
            ct = StdWheels;
        };
        extraflags = arq.GetInt("ExtraFlags", 0);
        if (arq.Exec("SELECT * FROM Ring WHERE ChartIdx = %d", idx) && arq.Valid(true))
            do
            {
                ring = arq.GetChar("RingNb", '1') - '1';
                switch (arq.GetChar("Subtype", 'S'))
                {
                case 'S':
                    cst = Single;
                    break;
                case 'T':
                    cst = Transit;
                    break;
                case 'D':
                    cst = Direction;
                    break;
                case 'P':
                    cst = Progression;
                    break;
                case 'A':
                    cst = AddAngle;
                    angle = arq.GetDouble("Angle", 0.0);
                    break;
                case 'M':
                    cst = MulAngle;
                    angle = arq.GetDouble("Angle", 0.0);
                    break;
                case 'C':
                    cst = Composite;
                    break;
                case 'I':
                    cst = TimeSpace;
                    break;
                case 'R':
                    cst = SolarArc;
                    break;
                case 'F':
                    cst = Profection;
                    break;

                default :
                    cst = Single;
                };
                switch (arq.GetChar("State", 'x'))
                {
                case 'M':
                    sts[ring] = Master;
                    break;
                case 'S':
                    sts[ring] = Slave;
                    break;
                case 'A':
                    sts[ring] = AMaster;
                    break;
                case 'a':
                    sts[ring] = ASlave;
                    break;
                default:
                    sts[ring] = Unknown_State;
                };
                dataidx = Index(arq.GetInt("DataIdx", 0));
                AstroData* ad = Adl->Get(dataidx);
                if (!ad)
                {
                    ad = new AstroData();
                    if(!ad->DbFetch(dataidx)) { delete ad; return false; }
                    Amw->Aiw->AddData(ad);
                }
                ac.SetData(ad, ring);
                ac[ring]->Angle = angle;
                restridx = Index(arq.GetInt("RestrIdx", 0));
                AstroRestrictions* ar = Arl->Get(restridx);
                if (!ar)
                {
                    ar = new AstroRestrictions;
                    if(!ar->DbFetch(restridx)) { delete ar; return false; }
                    Amw->Aiw->AddRestrict(ar);
                }
                ac.SetRestrict(ar, ring);
                ac[ring]->SetSubChart(cst);
                ac[ring]->Show = !arq.GetInt("Hidden", 0);
            } while (arq.Next());
				else
					return false;
        ac.SetCt(ct);
        for (int i = 0; i < NBDATA; i++)
            if (ac.Ov[i] && sts[i] == AMaster)
            {
                ac.SetAFirst(i);
                break;
            }
        for (int i = 0; i < NBDATA; i++)
            if (ac.Ov[i] && sts[i] == ASlave)
            {
                ac.Ov[i]->ARef = true;
                ac.Ov[i]->Recompute();
            }
        if (ct != Tarots_Spreads)
            ac.CreateChart(false);
        else
            ac.Acb = new AstroTarotSpreads(ac.Cbp, &ac.Ov);
        ac.Acb->SetOwnTitle(name);
        ac.Acb->Cbp->SetFlags(flags);
        if (ct == Tarots_Spreads)
        {
            ac.Acb->Cbp->Subring = No_Subring;
            AstroTarotSpreads* ats = DC(AstroTarotSpreads*, ac.Acb);
            ats->Ts = (enum TarotSpreads)extraflags;
            ats->Load(arq, idx);
        }
        else
            ac.Acb->Cbp->Subring = (enum Subring)extraflags;
        return true;
    }
    return false;
}

void AstroChartList::Delete(Index idx)
{
    AstroRequest arq;
    arq.Exec("DELETE FROM Charts WHERE Idx = %d", idx);
}

#undef SCO
