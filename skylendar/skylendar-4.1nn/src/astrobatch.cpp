/***************************************************************************
                          atrobatch.h  -  description
                             -------------------
    begin                : thr nov 24 2011
    copyright            : (C) 2011 by Christophe Gros
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

#include "astrobatch.h"
#include "astrosql.h"

#ifdef QT
#include "ui_batch.h"
#endif

#define DTT(d, four, sci) DrawTabText(Dbl(buf, d, four, sci))

AstroBatch::AstroBatch(ChartBaseParams* cbp, ObjsVector* ov) : GraphicListBase(this, cbp, ov)
{
    Ct = Batch;
    Cm = GraphicMode;
    DualChart = true;
    NbPM = 1;
    It = Inactive;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    Table = Vdv = false;
    TblIdx = 0;
}

bool AstroBatch::EditParams()
{
#ifdef QT
    QDialog qd;
    Ui_Batch ub;
    ub.setupUi(&qd);
    ub.Condition->setText(Condition);
    ub.Save->setChecked(Table);
    ub.Vdv->setChecked(Vdv);
    if (qd.exec() == QDialog::Accepted)
    {
        Condition = ub.Condition->text();
        Table = ub.Save->isChecked();
        Vdv = ub.Vdv->isChecked();
        return true;
    }
#endif

    return false;
}

bool AstroBatch::Redisplay()
{
    AstroString as, buf;
    const AstroObjs& ao = *First;
    const AstroAspects aa(~(*Second));
    Init();
    int l = W / 3, l2 = l / 2;
    const int tab[] = { 0, l, l + l2, l + 2 * l2, l + 3 * l2, l + 4 * l2, l + 5 * l2 };
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Condition: %a"), &as, &Condition));
    NewLine();
    if (Table)
    {
        SetTextStyle(SubTitle);
        DrawText(Sprintf(i18n("With AspTbl.Idx = %d"), &as, TblIdx));
    }
    NewLine();
    NewLine();
    SetTabList(tab);
    SetTextStyle(TabText);
    DrawTabText(i18n("DataSet"));
    DrawTabText(i18n("Object 1"));
    DrawTabText(i18n("Aspect"));
    DrawTabText(i18n("Object 2"));
    DrawTabText(i18n("Actual Orb"));
    DrawTabText(i18n("Direction"));
    DrawTabText(i18n("Way"));
    NewLine();
    NewLine();
#ifdef IFEXCEPT
    try
    {
#endif
        foreachc(*this, DataLineList)
        {
            auto bd = SC(const BatchData*, !it);
            DrawTabText(NDict[bd->first]);
            DrawTabText(ao << bd->a);
            DrawTabText(aa << bd->asp);
            DrawTabText(ao << bd->b);
            SetTextStyle(TabDot);
            double da = (bd->asp >= Parallel) ? bd->extraorb : DiffAngle(bd->apos, bd->bpos);
            DTT(DecToDeg(fabs(da - (aa * bd->asp))), false, false);
            switch (bd->side)
            {
            case Exact:
                as = i18n("Exact");
                break;
            case Applying:
                as = i18n("Applying");
                break;
            case Separating:
                as = i18n("Separating");
                break;
            default:
                ;
            };
            SetTextStyle(TabText);
            DrawTabText(as);
            switch (bd->way)
            {
            case LeftAspect  :
                as = i18n("Left");
                break;
            case RightAspect :
                as = i18n("Right");
                break;
            default:
                as = "";
            };
            DrawTabText(as);
            NewLine();
        }
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

bool AstroBatch::PostRecompute()
{
    AstroRequest Arq;
    AstroString as;
    bool b;
    AstroObjs d(*First);
    if (!Asr->Ctrl && !EditParams()) return false;
#ifdef QT
    qApp->setOverrideCursor(Qt::WaitCursor);
#endif

    Clear();
#ifdef QT
    NDict.clear();
#endif
    const AstroAspects aa(~(*Second));
    b = Arq.Exec("SELECT Idx FROM %s WHERE %a", Vdv ? "Vdv" : "Data", &Condition);
    if (!b || !Arq.Valid())
    {
#ifdef QT
        qApp->restoreOverrideCursor();
#endif
        return false;
    }
    do
    {
        Index idx = Arq.GetInt("Idx");
        d.DbFetch(idx);
        Afal.GetAspects(aa, *Second, d, IfSamePlanet);
        Afal.SortAspects();
        foreachc(Afal, AlAf)
        {
            BatchData* bd = new BatchData;
            const AspectFound* af = !it;
            bd->ak = BatchAsp;
            bd->first = d.Idx;
#ifdef QT
            if (!NDict.contains(bd->first))
                NDict[bd->first] = d.Name;
#endif
            bd->second = Second->Idx;
            bd->asp = af->Asp;
            bd->a = af->Oa;
            bd->b = af->Ob;
            bd->apos = af->Angle_a;
            bd->bpos = af->Angle_b;
            bd->orb = af->Orb;
            bd->extraorb = af->ExtraOrb;
            bd->side = af->AspectSide;
            bd->way = af->AspWay;
            Append(bd);
        }
    } while (Arq.Next());
    First->Recompute();
    if (Table)
        DumpAspects();
    return true;
}

bool AstroBatch::DumpAspects()
{
    AstroRequest arq;
    AstroString as;
    if (Second->Idx == 0)
    {
        AstroMessage(i18n("Sorry, you can't save the aspects if 'Now' is the slave DataSet"), true);
        return false;
    }
    arq.Exec("SELECT Idx FROM Data WHERE Idx = %d", Second->Idx);
    if (arq.GetInt("Idx", -1) == -1)
    {
        AstroMessage(Sprintf(i18n("Sorry, in order to save the aspects in AspTbl, the slave DataSet '%a' must be saved first in the database"), &as, &Second->Name), true);
        return false;
    }
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
            auto bd = SC(const BatchData*, !it);
            arq.Exec("INSERT INTO AspTbl(Idx, AspKind, Date, A, B, Asp, Apos, Bpos, Master, Slave) VALUES (%d, 'B', TIMESTAMP '%a', '%a', '%a', '%a', %f, %f, %d, %d)", TblIdx, &Second->SQLDate(as), &ObjShortName(bd->a), &ObjShortName(bd->b), Asr->AspectShortNames[bd->asp], bd->apos, bd->bpos, bd->first, bd->second);
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
