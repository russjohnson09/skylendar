/***************************************************************************
                          astrochartbase.cpp  -  description
                             -------------------
    begin                : Sat Oct 14 2000
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

#include "astrochartbase.h"
#include "astroaspects.h"
#include "aspconflist.h"
#include "scanspan.h"
#include "scanclient.h"
#include "stopscan.h"
#include "astrosql.h"
#include "astrospot.h"
#include "unistd.h"

AstroChartBase::AstroChartBase(ChartBaseParams *cbp, ObjsVector* ob)
{
    Cbp = cbp;
    Ob = ob;
    GetFS();
}

AstroChartBase::~AstroChartBase()
{
    if (Apm)
    {
        for (int i = 0; i < NbPM; i++)
            delete Apm[i].Name;
        delete Apm;
    }
}

int AstroChartBase::Count() const
{
    int nb = 0;
    const ObjsVector& ob = *Ob;
    for (int i = 0; i < NBDATA; i++)
        if (ob[i] && ob[i]->Show)
            nb++;
    return nb;
}

int AstroChartBase::Search(int r, enum SearchType st, bool visible) const
{
    const ObjsVector& ob = *Ob;
    if (r >= NBDATA) return -1;
    for (int i = r; i < NBDATA; i++)
        if (ob[i])
        {
            if (visible && !ob[i]->Show) continue;
            else
                switch (st)
                {
                case SingleOnly:
                    if (ob[i]->GetSubType() == Single) return i;
                    break;
                case NonSingle:
                    if (ob[i]->GetSubType() != Single) return i;
                    break;
                case Any:
                    return i;
                };
        }
    return -1;
}

bool AstroChartBase::operator == (int i) const
{
    const ObjsVector& ob = *Ob;
    if (i < 0 || i >= NBDATA) return false;
    return ob[i];
}

void AstroChartBase::PostSetData(int i)
{
    if (i > 0)
    {
        if (!DualChart) DualChart = true;
        (*this)[i]->SetSubChart(Transit);
    }
}

const AstroString& AstroChartBase::GetTitle(AstroString &as) const
{
    int nb = Count(), f = Search(), s = Search(f + 1);
    const AstroObjs &ao = *(*this)[f], &ao1 = (s != -1) ? *(*this)[s] : 0;
    if (IfOwnTitle)
    {
        as = OwnTitle;
        as.Replace("$1", ao.Name);
        as.Replace("$t", *Asr->TypesNames[Ct]);
        if (s != -1)
            for (int i = s + 1; i < NBDATA; i++)
            {
                int t = Search(i);
                if (t != -1)
                {
                    AstroString a;
                    const AstroObjs& ao1 = *(*this)[t];
                    as.replace(Sprintf("$%d", &a, i), ao1.Name);
                }
            }
        return as;
    }
    const AstroString unknown = i18n("Unknown");
    AstroString as1, r1 = ao.GetSubType() > Single ? Sprintf(i18n("(%a ring)"), &as1, &ao.GetSubTypeShortName()) : "", r2 ;
    if (Ct == Ephemeris)
    {
        as = i18n("Ephemeris at 0h");
        return as;
    }
    if (nb == 1)
        return Sprintf(i18n("%a for %a %a"), &as, Ct == Unknown_ChartType ? &unknown : Asr->TypesNames[Ct] , &ao.Name, &r1);
    r2 =  ao1.GetSubType() > Single ? Sprintf(i18n("(%a ring)"), &as1,  &ao1.GetSubTypeShortName()) : "";
    return Sprintf(i18n("%a for %a %a and %a %a"), &as, Ct == Unknown_ChartType ? &unknown : Asr->TypesNames[Ct], &ao.Name, &r1, &ao1.Name, &r2);
}

void AstroChartBase::SetOwnTitle(const AstroString& as)
{
    if (as.isEmpty())
    {
        IfOwnTitle = false;
        OwnTitle = "";
        return;
    }
    IfOwnTitle = true;
    OwnTitle = as;
}

void AstroChartBase::CompAspConfig(AspConfList& acl) const
{
    if (GetAspectsList())
        acl.Compute(this);
}

void AstroChartBase::GetFS()
{
    int f = Search(0, SingleOnly), s;
    if (f != -1)
    {
        s = Search(0, NonSingle);
        if (s == -1)
            s = Search(f + 1);
    }
    else
    {
        f = Search();
        s = Search(f + 1);
    }
    First = (*this)[f];
    Second = (s != -1) ? (*this)[s] : 0;
}

bool AstroChartBase::PlaceSpot(const AstroObjs& a, enum Objs o, int x, int y, int size, const AstroColor& ac)
{
    if(!NoSpot)
    {
        auto as = Spots[a.GetID() - int(o)];
        if(as)
            as->RePos(x, y, size);
        else
            Spots.insert(a.GetID() - int(o), new AstroSpot(Cbp->Qw, Cbp->Ag, a, o, x, y, size, ac));
     }
	return true;
}

bool AstroChartBase::PlaceSpot(enum Signs s, int x, int y, int size, const AstroColor& ac)
{
    if(!NoSpot)
    {
        auto as = Spots[int(s)];
        if(as)
            as->RePos(x, y, size);
        else
            Spots.insert(int(s), new AstroSpot(Cbp->Qw, Cbp->Ag, s, x, y, size, ac));
     }
    return true;
}


void AstroChartBase::HideAll()
{
#ifdef QT
    QHashIterator<int, AstroSpot*> i(Spots);
  while (i.hasNext())
	{
      i.next();
      i.value()->hide();
  }
#endif
}

void AstroChartBase::Clean()
{
#ifdef QT
    QHashIterator<int, AstroSpot*> i(Spots);
  while (i.hasNext())
	{
      i.next();
      delete i.value();
  }
	Spots.clear();
#endif
}

bool TensorFlowChart::PostRecompute()
{
    AstroAspects aa(Second ? ~(*Second) : ~(*First));
    Afal.Clear();
    Afal.GetAspects(aa, *First, Second ? *Second : *First, Second ? IfSamePlanet : 0);
    return true;
}


bool ParamListBase::EditScSp(AspScanParams& asp, bool mp)
{
    EditScanSpan ess(&asp, mp);
#ifdef QT
    return ess.exec() == QDialog::Accepted;
#endif
}

ParamListBase::ParamListBase(AspScan* as)
{
    TblIdx = 0;
    Ss = nullptr;
    Ad = nullptr;
    As = as;
    Sci = new ScanClient(qApp, As, Asr->ScanId++);
}

ParamListBase::ParamListBase(AstroDir* ad)
{
    TblIdx = 0;
    Ss = nullptr;
    As = nullptr;
    Ad = ad;
    Sci = new ScanClient(qApp, Ad, Asr->ScanId++);
}

ParamListBase::~ParamListBase()
{
    delete Sci;
    delete Ss;
    if (TblIdx)
    {
        AstroRequest arq;
        Asr->AspIdx.Delete(TblIdx, arq);
    }
}

void ParamListBase::Progress(int i)
{
    if (Ss) Ss->Set(i);
}

void ParamListBase::ShowSs(bool dual)
{
    if (Ad)
        Ss = new StopScan(Ad);
    if (As)
        Ss = new StopScan(As, dual);
    Progress(0);
}

void ParamListBase::HideSs()
{
    delete Ss;
    Ss = 0;
}

const AstroString ParamListBase::ScServer() const
{
    AstroString as;
    return Sprintf("-%d %s%d", &as, getpid(), SCANCLIENT, Sci->Id);
}
