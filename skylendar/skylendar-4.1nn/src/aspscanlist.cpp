/***************************************************************************
                          aspscanlist.cpp  -    description
                             -------------------
    begin                : sam oct 5 2002
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

#include "aspscanlist.h"
#include "astroprocess.h"
#include "astrodefs.h"
#include "astroresources.h"
#include "astrosql.h"
#ifdef QT
#include <QGuiApplication>
#include <QTimer>
#endif

static const char AspChar[] = { 'X', 'D', 'S', 'R', 'E', 'P', 'B' };

struct Voc
{
    double j1, j2;
    enum Objs o;
    enum Aspects a;
};

AspScan::AspScan(AstroChartBase* acb) : ParamListBase(this)
{
    Acb = acb;
}

AspScanList::AspScanList(ChartBaseParams* cbp, ObjsVector* ov) : GraphicListBase(this, cbp, ov),  AspScan(this)
{
    Ct = AspScList;
    Cm = GraphicMode;
    It = Buttons;
    DualChart = true;
    NbPM = 1;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
}

AspScan::~AspScan()
{
}

bool AspScanList::PostRecompute()
{
    if (!Asr->Ctrl && !EditParams()) return false;
    return Run(true);
}

bool AspScan::Run(bool stopscan)
{
    int d = 0, m = 0, y = 0, h = 0, min = 0, sec = 0;
    AstroString as;
    AstroObjs &f = *Acb->First, &s = *Acb->Second;
    if (!Acb->Second) return false;
    if (Asp.Ss == Solar_Rev || Asp.Ss == Lunar_Rev)
    {
        int d1, m1;
        Dual = false;
        Keep = ~f;
        CurAr = new AstroRestrictions(*Keep);
        CurAr->RestrictAll();
        CurAr->RestrictAllAsps();
        CurAr->Restrict(Asp.Ss == Solar_Rev ? Sun : Moon, false);
        CurAr->AspRestrict(Conjunction, false);
        f.SetRestrict(CurAr);
        s.SetRestrict(CurAr);
        Orig = s;
        if (Asp.Ss == Solar_Rev)
        {
            f.GetDate(&d, &m, &y, &h, &min, &sec);
            d1 = d;
            m1 = m;
        }
        s.GetDate(&d, &m, &y, &h, &min, &sec);
        Dc = s.GetDataComp();
        if (Asp.Ss == Solar_Rev)
        {
            s.SetDate(d1 - 1, m1, y, 0, 0, 0);
            Dc.julday = IncTime(s.GetJd(), 0, 0, 0, 2);
        }
        else
        {
            s.SetDate(1, 1, y, 0, 0, 0);
            Dc.julday = IncTime(s.GetJd(), 0, 0, 0, 0, 12);
        }
        Dc.gethousesfirst = Dc.gethouses = Dc.gauquelin = false;
    }
    else
    {
        Dual = (f.Idx == s.Idx && -f == Single && -s == Single);
        Orig = s;
        if (Dual) Orif = f;
        if (!Dual && -s == Single) s.SetSubChart(Transit);
        s.GetDate(&d, &m, &y, &h, &min, &sec);
        switch (Asp.Ss)
        {
        case Current_Day   :
            break;
        case Current_Month :
            d = 1;
            break;
        case Current_Year  :
        case Years         :
            d = 1;
            m = 1;
            break;
        default:
            ;
        };
        s.SetDate(d, m, y, 0, 0, 0);
        int y1 = y, m1 = m;
        d = m = y = h = min = sec = 0;
        switch (Asp.Ss)
        {
        case Current_Day   :
            h = 23;
            min = 59;
            sec = 59;
            break;
        case Current_Month :
            m = 1;
            break;
        case Current_Year  :
            y = 1;
            break;
        case Years         :
            y = Asp.NbYears;
            break;
        default:
            ;
        }
        Dc = s.GetDataComp();
        Dc.julday = s.GetJd() + IncTime(y1, m1, sec, min, h, d, m, y);
        Dc.gethousesfirst = f().IfHouses();
        Dc.gethouses = s().IfHouses();
    }
    Clear();
    if (stopscan) ShowSs(Dual);
    if (Asp.AP)
        s.GetInterface()->LoadParts(Get1<ThePart>(*Asr->Parts,  sizeof(ThePart) * Asr->NbParts), Asr->NbParts);
    s.GetInterface()->ScanAsp(Get1<DataComp>(Dc), s.GetJd(), ScServer(), Dual, Asp.MP, s.To_Second, Asp.AP);
    return true;
}

void AspScan::Finish()
{
    const DataLineList& dl = *this;
    AstroObjs &f = *Acb->First, &s = *Acb->Second;
    Sort(DataLineSort);
    P;
    if (Asp.Ss != Solar_Rev && Asp.Ss != Lunar_Rev)
    {
        DataLineList::Iterator it(*this);
        if (it == dl)
        {
            auto ad = SC(AspData*, *it);
            enum Objs a = ad->a, b = ad->b;
            enum Aspects asp = ad->asp;
            ++it;
            while (it == dl)
            {
                ad = SC(AspData*, *it);
                if (ad && ad->a == b && ad->b == a && ad->asp == asp) ad->asp = Unknown_Aspect;//Remove(it);
                a = ad->a;
                b = ad->b;
                asp = ad->asp;
                ++it;
            }
        }
    }
    *SC(AstroDate*, &s) = Orig;
    if (Asp.Ss == Solar_Rev || Asp.Ss == Lunar_Rev)
    {
        f.SetRestrict(Keep);
        f.Recompute();
        s.SetRestrict(Keep);
    }
    s.Recompute();
    if (Dual)
    {
        *SC(AstroDate*, &f) = Orif;
        f.Recompute();
    }
    HideSs();
    if (Asp.DumpAsp)
        DumpAspects();
}

bool AspScanList::Redisplay()
{
    Dual = (First->Idx == Second->Idx && First->GetSubType() == Single && Second->GetSubType() == Single);
    AstroDate dat(*Second);
    AstroString as, as1;
#ifdef QT
    qApp->setOverrideCursor(Qt::WaitCursor);
#endif
    Init();
    int l = W / 5, l2 = 3 * l / 5;
    const int tab[] = { 0, l + l2 + (Second->To_Second ? (l2 * 22 / 100) : 0), 2 * l + 2 * l2, 3 * l + 2 * l2, 4 * l + 2 * l2, 5 * l + l2 };
    AstroList<Voc> voclist;
    bool voc = Dual && (*Second) == Moon; // Void of course
    AspData* advoc = nullptr;
    SetTabList(tab);
    SetTextStyle(MainTitle);
    if (Dual)
    {
        DrawText(i18n("Dual Scan List for"));
        NewLine();
        DrawText(Sprintf("%a", &as, &First->Name));
    }
    else
    {
        DrawText(i18n("Simple Scan List between"));
        NewLine();
        DrawText(Sprintf(i18n("%a and %a"), &as, &Second->Name, &First->Name));
    }
    NewLine();
    if (Asp.DumpAsp)
    {
        SetTextStyle(SubTitle);
        DrawText(Sprintf(i18n("With AspTbl.Idx = %d"), &as, TblIdx));
        NewLine();
        NewLine();
        NewLine();
    }
    SetTextStyle(TabText);
    DrawTabText("Date");
    DrawTabText(i18n("Object 1"));
    DrawTabText(i18n("Aspect"));
    DrawTabText(i18n("Object 2"));
    DrawTabText(i18n("Comment"));
    NewLine();
    NewLine();
#ifdef IFEXCEPT
    try
    {
#endif
        foreachc(*this, DataLineList)
        {
            auto ad = SC(const AspData *, !it);
            if (ad->asp == Unknown_Aspect) continue;
            dat.SetJd(ad->jd);
            dat.GetDate(as);
            as += "   ";
            as += dat.GetTime(as1, 0, Second->To_Second);
            DrawButton();
            DrawTabText(as);
            bool b = ad->c != Undefined_Obj && ad->c != ARABPART;
            switch (ad->ak)
            {
            case ExAsp:
                if (ad->apos < 0.0)
                    DrawTabText(Sprintf(i18n("%a [%a]"), &as, &ObjName(b  ? ad->b : ad->a), &((*Asg) < Asg->GetSign(fabs(b ? ad->bpos : ad->apos)))));
                else
                    DrawTabText(Sprintf(i18n("%a (%a)"), &as, &ObjName(b ? ad->b : ad->a), &((*Asg) < Asg->GetSign(fabs(b ? ad->bpos : ad->apos)))));
                DrawTabText(*Asr->AspectNames[ad->asp]);
                if (b)
                {
                    DrawTabText(Sprintf(("%a/%a (%a)"), &as, &((*First) < ad->a), &((*First) < ad->c), &((*Asg) < Asg->GetSign(fabs(ad->apos)))));
                }
                else
                {
                    if (ad->bpos < 0.0)
                        DrawTabText(Sprintf(i18n("%a [%a]"), &as, &ObjName(ad->b, ad->c == ARABPART), &((*Asg) < Asg->GetSign(fabs(ad->bpos)))));
                    else
                        DrawTabText(Sprintf(i18n("%a (%a)"), &as, &ObjName(ad->b, ad->c == ARABPART), &((*Asg) < Asg->GetSign(fabs(ad->bpos)))));
                }
                if (ad->c == Undefined_Obj)
                {
                    if (ad->a == ad->b && ad->asp == Conjunction)
                        DrawTabText(Sprintf(i18n("%a Return"), &as, &ObjName(ad->a)));
                    if (ad->a == ad->b && ad->asp == Opposition)
                        DrawTabText(Sprintf(i18n("%a-%a Opposition"), &as, &ObjName(ad->a), &ObjName(ad->b)));
                    if (ad->a == ad->b && ad->asp == Square)
                        DrawTabText(Sprintf(i18n("%a-%a Square"), &as, &ObjName(ad->a), &ObjName(ad->b)));
                    if (ad->a == ad->b && ad->asp == Trine)
                        DrawTabText(Sprintf(i18n("%a-%a Trine"), &as, &ObjName(ad->a), &ObjName(ad->b)));
                }
                if (Dual)
                {
                    if (b && ((ad->a == Sun && ad->b == Moon) || (ad->a == Moon && ad->b == Sun)))
                    {
                        if (ad->asp == Conjunction)
                            DrawTabText(i18n("New Moon"));
                        if (ad->asp == Opposition)
                            DrawTabText(i18n("Full Moon"));
                        if (ad->asp == Square)
                            DrawTabText(i18n("Half Moon"));
                    }
                    if (voc && ((ad->a == Moon && ad->b <= Pluto) || (ad->b == Moon && ad->a <= Pluto)) && ad->asp <= Sextile) advoc = CSC(AspData *, ad);
                }
                ad->y = Pos();
                break;
            case ChangeDir:
                as = ObjName(ad->a);
                as += " ";
                as += (*Asg) < Asg->GetSign(fabs(ad->apos));
                DrawTabText(as);
                DrawTabText(ad->apos < 0.0 ? i18n("Direct->Retro") : i18n("Retro->Direct"));
                ad->y = Pos();
                break;
            case ChangeSign:
                DrawTabText(Sprintf(i18n("%a Enters %a"), &as, &ObjName(ad->a), &((*Asg) << int(ad->apos))));
                if (voc && advoc)
                {
                    auto v = new struct Voc;
                    v->j1 = advoc->jd;
                    v->j2 = ad->jd;
                    v->o = (advoc->a == Moon) ? advoc->b : advoc->a;
                    v->a = advoc->asp;
                    voclist.Append(v);
                    advoc = NULL;
                }
                ad->y = Pos();
                break;
            default:
                ;
            };
            NewLine();
        }
        if (voc && voclist.Count())
        {
            AstroObjs ao = *Second;
            const AstroRestrictions& ar = ao();
            SetTextStyle(Title);
            NewLine();
            DrawText(i18n("Moon void of course"));
            NewLine();

            NewLine();
            SetTextStyle(TabText);
            DrawTabText(i18n("From"));
            DrawTabText(i18n("To"));
            NewLine();
            NewLine();
            foreachc(voclist, AstroList<Voc>)
            {
                auto v = SC(const struct Voc *, !it);
                int o = (ar * v->a)->Orb;
                double vt = 1.0 / (ao[1]->V[3] - ao[v->o]->V[3]), f = v->j1 + o * vt;
                if (f > v->j2) continue;
                ao.SetJd(f);
                DrawTabText(ao.GetDateTime(as));
                ao.SetJd(v->j2);
                DrawTabText(ao.GetDateTime(as));
                NewLine();
            }
        }
        End = true;
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        Ex = false;
        NewLine();
        Exception(ae);
    }
#endif

#ifdef QT
    qApp->restoreOverrideCursor();
#endif
    return true;
}

void AspScan::DrawDate(int i, double ipos, int j, double jpos, int asp, double julday, bool ap)
{
    auto ad = new struct AspData;
    ad->ak = ExAsp;
    ad->a = (enum Objs)i;//SC(enum Objs, i);
    ad->apos = ipos;
    ad->b = (enum Objs)j;//SC(enum Objs, j);
    ad->bpos = jpos;
    ad->asp = SC(enum Aspects, asp);
    ad->jd = julday;
    ad->c  = ap ? ARABPART : Undefined_Obj;
    Append(ad);
}

void AspScan::DrawMPDate(int i, int j, double pos, int k, double kpos, int asp, double julday)
{
    auto ad = new struct AspData;
    ad->ak = ExAsp;
    ad->a = SC(enum Objs, i);
    ad->apos = pos;
    ad->b = SC(enum Objs, k);
    ad->bpos = kpos;
    ad->asp = SC(enum Aspects, asp);
    ad->jd = julday;
    ad->c = SC(enum Objs, j);
    Append(ad);
}

void AspScan::DrawChange(int i, double ipos, double julday)
{
    auto ad = new struct AspData;
    ad->ak = ChangeDir;
    ad->apos = ipos;
    ad->a = SC(enum Objs, i);
    ad->jd = julday;
    Append(ad);
}

void AspScan::DrawSignTrans(int i, int sign, double julday)
{
    auto ad = new struct AspData;
    ad->ak = ChangeSign;
    ad->a  = SC(enum Objs, i);
    ad->apos = (double)sign;
    ad->jd = julday;
    Append(ad);
}

/**
 *
 * @return
 */
bool AspScan::DumpAspects()
{
    AstroRequest arq;
    AstroDate dat(*Acb->Second);
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
            switch (ad->ak)
            {
            case ExAsp:
                if (ad->asp != Unknown_Aspect)
                {
                    if (ad->c != Undefined_Obj && ad->c != ARABPART)
                        arq.Exec("INSERT INTO AspTbl(Idx, AspKind, Date, A, B, C, Asp, Apos, Bpos) VALUES (%d, '%c', TIMESTAMP '%a', '%a', '%a', '%a', '%a', %f, %f)", TblIdx, AspChar[ad->ak], &dat.SQLDate(as), &ObjShortName(ad->a), &ObjShortName(ad->b), &ObjShortName(ad->c), Asr->AspectShortNames[ad->asp], ad->apos, ad->bpos);
                    else
                        arq.Exec("INSERT INTO AspTbl(Idx, AspKind, Date, A, B, Asp, Apos) VALUES (%d, '%c', TIMESTAMP '%a', '%a', '%a', '%a', %f)", TblIdx, AspChar[ad->ak], &dat.SQLDate(as), &ObjShortName(ad->a), &ObjShortName(ad->b, ad->c == ARABPART), Asr->AspectShortNames[ad->asp], ad->apos);
                }
                break;
            case ChangeDir:
                arq.Exec("INSERT INTO AspTbl(Idx, AspKind, Date, A, Apos) VALUES (%d, '%c', TIMESTAMP '%a', '%a', %f)", TblIdx, AspChar[ad->ak], &dat.SQLDate(as), &ObjShortName(ad->a), ad->apos);
                break;
            case ChangeSign:
                arq.Exec("INSERT INTO AspTbl(Idx, AspKind, Date, A, Sgn) VALUES (%d, '%c', TIMESTAMP '%a', '%a', '%a')", TblIdx, AspChar[ad->ak], &dat.SQLDate(as), &ObjShortName(ad->a), &((*Asg ) < int(ad->apos)));
                break;
            default:
                ;
            }
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
