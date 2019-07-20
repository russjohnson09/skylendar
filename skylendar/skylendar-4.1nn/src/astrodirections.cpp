/***************************************************************************
 *   Copyright (C) 2007 by Christophe Gros                                 *
 *   skylendar@yahoo.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "astrodirections.h"
#include "astroprocess.h"
#include "editdirections.h"
#include "astrosql.h"
#include <cmath>
#include <unistd.h>
#include "stopscan.h"
#include "scanclient.h"
#ifdef QT
#include <QGuiApplication>
#include <QRadioButton>
#include <QSpinBox>
#endif
#ifdef __WINNT
#include <process.h>
#endif

AstroDir::AstroDir(AstroChartBase* acb) : ParamListBase(this)
{
    Acb = acb;
    Hs = Regiomontanus;
    Dt = Mundane;
    Sk = Ptolemy;
    Converse = true;
    Dump = false;
}

AstroDirections::AstroDirections(ChartBaseParams* cbp, ObjsVector* ov): GraphicListBase(this, cbp, ov), AstroDir(this)
{
    Ct = Directions;
    It = Buttons;
    Cm = GraphicMode;
    DualChart = true;
    NbPM = 1;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
}


AstroDirections::~AstroDirections()
{
}

bool AstroDirections::Redisplay()
{
    AstroDate dat(*First);
    AstroString as, as1, h, sk;
    AstroHM hm;
    Init();
    int l = W / 5, l2 = 3 * l / 5;
    const int tab[] = { 0, l + l2, 2 * l + l2, 3 * l + l2, 4 * l + l2, 5 * l + l2 };
    SetTabList(tab);
    switch (Hs)
    {
    case Regiomontanus:
        h = i18n("Regiomontanus");
        break;
    case Placidus:
        h = i18n("Placidus");
        break;
    case Campanus:
        h = i18n("Campanus");
        break;
    default:
        ;
    };
    switch (Sk)
    {
    case Ptolemy:
        sk = i18n("Ptolemy");
        break;
    case Naibod:
        sk = i18n("Naibod");
        break;
    case Simmonite:
        sk = i18n("Simmonite");
        break;
    case Placidian:
        sk = i18n("Placidian");
        break;
    case Cardan:
        sk = i18n("Cardan");
        break;
    case Synodic:
        sk = i18n("Synodic");
        break;
    case Custom:
        sk = i18n("Custom");
        break;
    };

    SetTextStyle(SubTitle);
    const AstroString m = i18n("Mundane"), z = i18n("Zodiacal");
    DrawText(Sprintf(i18n("%a, %a direction type, %a key"), &as1, &h, (Dt == Mundane) ? &m : &z, &sk));
    if (Dump)
    {
        NewLine();
        DrawText(Sprintf(i18n("AspTbl.Idx = %d"), &as, TblIdx));
    }
    NewLine();
    NewLine();
    SetTextStyle(TabText);
    DrawTabText("Date");
    DrawTabText(i18n("Promissor"));
    DrawTabText(i18n("Aspect"));
    DrawTabText(i18n("Significator"));
    DrawTabText(i18n("Sense"));
    DrawTabText(i18n("Arc"));
    NewLine();
    NewLine();
#ifdef	IFEXCEPT
    try
    {
#endif
        foreachc(*this, DataLineList)
        {
            auto ad = SC(const AspData *, !it);
            (!it)->y = Pos();
            dat.SetJd(ad->jd);
            dat.GetDate(as);
            //as += "   ";
            //as += dat.GetTime(as1, 0);
            DrawButton();
            DrawTabText(as);
            DrawTabText(ObjName(ad->a));
            DrawTabText(*Asr->AspectNames[ad->asp]);
            DrawTabText(ObjName(ad->b));
            DrawTabText(ad->ak == ExCDir ? i18n("Converse") : i18n("Direct"));
            hm.Set(fabs(ad->bpos));
            DrawTabText(hm.Get(as1, HM_Degrees, false, true));
            NewLine();
        }
        End = true;
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        Ex = false;
        NewLine();
        //Exception(ae);
    }
#endif
#ifdef QT
    qApp->restoreOverrideCursor();
#endif
    First->Recompute();
    return true;
}

bool AstroDirections::PostRecompute()
{
    if (!Asr->Ctrl && !EditParams()) return false;
    return Run(true);
}

bool AstroDir::Run(bool stopscan)
{
    int flags = 0;
    AstroObjs &f = *Acb->First, &s = *Acb->Second;
    if (!&s) return false;
#ifdef QT
    if (stopscan) qApp->setOverrideCursor(Qt::WaitCursor);
#endif
    Clear();
    if (Converse)  flags |= CONVERSE;
    if (stopscan) ShowSs();
    f.GetInterface()->ScanDir(f.GetRing(), s.GetRing(), ScServer(), uchar(Hs), uchar(Dt), uchar(Sk), CustVal, flags);
    return true;
}

void AstroDir::Finish()
{
    /*	const DataLineList& dl = *this;
    DataLineList::Iterator i1(*this), i2(*this);
    if (i1 == dl)
    	do
    	{
    		++i1;
    		for (int l = 0; l < 2 && i1 == dl; l++, ++i1)
    		{
    			const AspData *ad = SC(const AspData *, *i1), *ad1 = SC(const AspData *, *i2);
    			if ((ad->asp == Conjunction || ad->asp == Opposition) && ad->a == ad1->a && ad->b == ad1->b && ad->asp == ad1->asp && ad->ak == ad1->ak && floor(ad->jd) == floor(ad1->jd))
    				DataLineList::Remove(*i1);
    		}
    		i1 = i2;
    		++i1;
    		++i2;
    	} while (i1 == dl);
    	P;*/
    Sort(DataLineSort);
    //P;
    //First->Recompute();
    P;
    HideSs();
    if (Dump) DumpAspects();
}

bool AstroDirections::EditParams()
{
    EditDirections ed(this);
    if (ed.exec() == QDialog::Accepted)
    {
        CustVal = 0.0;
        switch (ed.House->currentIndex())
        {
        case 0:
            Hs = Regiomontanus;
            break;
        case 1:
            Hs = Placidus;
            break;
        case 2:
            Hs = Campanus;
            break;
        };
        Dt = (ed.DirType->currentIndex() == 0) ? Mundane : Zodiacal;
        switch (ed.StatKey->currentIndex())
        {
        case 0:
            Sk = Ptolemy;
            break;
        case 1:
            Sk = Naibod;
            break;
        case 2:
            Sk = Simmonite;
            break;
        case 3:
            Sk = Placidian;
            break;
        case 4:
            Sk = Cardan;
            break;
        case 5:
            Sk = Synodic;
            break;
        case 6:
            Sk = Custom;
            CustVal = ed.CustVal->value();
            break;
        };
        Converse = ed.Converse->isChecked();
        Dump     = ed.Dump->isChecked();
        return true;
    }
    return false;
}

void AstroDir::DrawDir(int i, double ipos, int j, double jpos, int asp, double julday, enum AspKind ak)
{
    auto ad = new struct AspData;
    ad->ak = ak;
    ad->a = (enum Objs)i;//SC(enum Objs, i);
    ad->apos = ipos;
    ad->b = (enum Objs)j;//SC(enum Objs, j);
    ad->bpos = jpos;
    ad->asp = SC(enum Aspects, asp);
    ad->jd = julday;
    ad->c  = Undefined_Obj;
    Append(ad);
}

bool AstroDir::DumpAspects()
{
    AstroRequest arq;
    AstroDate dat(*Acb->First);
    AstroString as;
    arq.Begin();
#ifdef IFEXCEPT
    arq.SetException(true);
    try
    {
#endif
        if (TblIdx == 0)
            TblIdx = Asr->AspIdx.GetIdx(arq);
        else
        {
            arq.Exec("SELECT COUNT(*) FROM AspTbl WHERE Idx = %d", TblIdx);
            if (arq.GetInt("count", 0) > 0)
                arq.Exec("DELETE FROM AspTbl WHERE Idx = %d", TblIdx);
        }
        foreachc(*this, DataLineList)
        {
            auto ad = SC(const AspData *, !it);
            dat.SetJd(ad->jd);
            arq.Exec("INSERT INTO AspTbl(Idx, AspKind, Date, A, B, C, Asp, Apos, Bpos) VALUES (%d, '%c', TIMESTAMP '%a', '%a', '%a', '%a', '%a', %f, %f)", TblIdx, ad->ak == ExDir ? 'c' : 'd', &dat.SQLDate(as), &ObjShortName(ad->a), &ObjShortName(ad->b), &ObjShortName(ad->c), Asr->AspectShortNames[ad->asp], ad->apos, ad->bpos);
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
    return true;
}
