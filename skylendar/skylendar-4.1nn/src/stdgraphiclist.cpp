/***************************************************************************
                          stdgraphiclist.cpp  -  description
                             -------------------
    begin                : mer ao 21 2002
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

#include "stdgraphiclist.h"
#include "astroutils.h"
#include "aspconflist.h"
#include "astromidpoints.h"
#include "astrosql.h"
#include <QApplication>

#define DTT(d, four, sci) DrawTabText(Dbl(buf, d, four, sci))
#define EXCL(i) (i < Mercury || (i > Pluto && i < Chiron) || (i > Vesta && i < First_Extra))

StdGraphicList::StdGraphicList(ChartBaseParams* cbp, ObjsVector* ov) : GraphicListBase(this, cbp, ov)
{
    Ct = GraphicList;
    DualChart = false;
    It = Buttons;
    PartsVals = nullptr;
    PrevGlobOccult = NextGlobOccult = nullptr;
    NbPM = 19;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Data Table"), Sidebars);
    PMSET(2, i18n("Aspects Table"), AspectsFrame);
    PMSET(3, i18n("Midpoints"),DisplayMidPoints);
    PMSET(4, i18n("Sort Aspects List"), SortAsp);
    PMSET(5, i18n("Displays Seconds"), DisplaySeconds);
    PMSET(6, i18n("Planets Rank"), PlanetsRank);
    PMSET(7, i18n("Planets Risings/Settings"), RiseSet);
    PMSET(8, i18n("Eclipses Dates"), GlobEclipse);
    PMSET(9, i18n("Aspects Configurations"), AspectsConfig);
    PMSET(10, i18n("Sabian Degrees"), Sabian);
    PMSET(11, i18n("Comment"), DisplayComment);
    PMSET(12, i18n("Apsides"), Apsides);
    PMSET(13, i18n("Arabic Parts"), ArabicParts);
    PMSET(14, i18n("Interpretation of natal objects"), Interpretation);
    PMSET(15, i18n("Interpretation of transits"), InterpretTrans);
    PMSET(16, i18n("Helical events"), Heliacal);
    PMSET(17, i18n("Decans && Terms"), DecTerms);
    PMSET(18, i18n("Global Lunar Occultation"), Occultations);
}

StdGraphicList::~StdGraphicList()
{
    delete PartsVals;
		delete PrevGlobOccult;
		delete NextGlobOccult;
}

bool StdGraphicList::PostRecompute()
{
    AstroInterface& itf = *First->GetInterface();
    fl = First->DefSweFlags;
    //First->DefSweFlags |= SEFLG_SPEED;

#ifdef QT
    if (Cbp->Heliacal || Cbp->Occultations)
        qApp->setOverrideCursor(Qt::WaitCursor);
#endif
    First->Recompute();
    P;
    if (Second)
    {
        fl1 = Second->DefSweFlags;
        //Second->DefSweFlags |= SEFLG_SPEED;
        Second->Recompute();
    }
    P;
    Clear();
    Afal.Clear();
    Afal.SetParts(Asr->Parts, Asr->NbParts);
    P;
    if (Cbp->AspectsFrame)
    {
        int flags = Cbp->ArabicParts ? Pta : 0;
        AstroAspects aa(Second ? ~(*Second) : ~(*First));
        if (Second)
        {
            flags |= IfSamePlanet;
            if (Cbp->DisplayMidPoints)
                flags |= (First->GetSubType() == Single && Second->GetSubType() == Single) ? Mutual : MPb;
            Afal.GetAspects(aa, *Second, *First, flags);
        }
        else
            Afal.GetAspects(aa, *First, *First, Cbp->DisplayMidPoints ? flags | MPa : flags);
        if (Cbp->SortAsp)
            Afal.SortAspects();
    }
    P;
    First->DefSweFlags = fl;
    if (Second)
        Second->DefSweFlags = fl1;
    if (Cbp->GlobEclipse)
    {
        GetEcl(SolGlobEcl[0], true, true, false);
        GetEcl(SolGlobEcl[1], true, false, false);
        GetEcl(LunGlobEcl[0], true, true, true);
        GetEcl(LunGlobEcl[1], true, false, true);
        GetEcl(SolLocEcl[0], false, true, false);
        GetEcl(SolLocEcl[1], false, false, false);
        P;
    }
    if (Cbp->RiseSet)
    {
        for (int i = Sun; i <= Last_Planet; i++)
            if (*First == i)
            {
                for (int j = Rising; j <= AtNadir; j++)
                    ValRS[j][i] = First->GetRiseSet(SC(enum Objs, i), SC(enum ConjAngles, j));
                if (i % 5) P;
            }
        if (First->IfStars())
            for (int i = First_Star; i < Last_Star; i++)
                if (*First == i)
                {
                    for (int j = Rising; j <= AtNadir; j++)
                        ValRS[j][i] = First->GetRiseSet(SC(enum Objs, i), SC(enum ConjAngles, j));
                    if (i % 5) P;
                }
    }
    if (Cbp->AspectsConfig)
    {
        Acl.Clear();
        CompAspConfig(Acl);
    }
    if (Cbp->Sabian) LoadSabian();
    P;
    if (Cbp->Apsides)
    {
        double j = First->GetJd();
        for (int i = Sun; i <= Last_Planet; i++)
            if (*First == i)
                itf.GetApsides(j, i, fl, Aps[i]);
        P;
        if (First->IfExtra())
            for (int i = First_Extra; i <= Asr->LastExtra; i++)
                if (*First == i)
                    itf.GetApsides(j, i, fl, Aps[i]);
    }
    P;
    if (Cbp->ArabicParts)
    {
        if (!PartsVals)
            PartsVals = new double[Asr->NbParts];
        for (int i = 0; i < Asr->NbParts; i++)
            PartsVals[i] = First->Part(i);
    }
    if (Cbp->Heliacal)
    {
        const Double3 geo = { First->Longitude.Get(), First->Latitude.Get(), First->Altitude };
        double julday = First->GetJd();
        for (int i = Sun; i <= Neptune; i++)
            if (*First == i)
            {
                itf.Heliacal(julday, geo, (enum Objs)i, HelRising, HelRis[i]);
                itf.Heliacal(julday, geo, (enum Objs)i, HelSetting, HelSet[i]);
                switch (i)
                {
                case Mercury:
                    itf.Heliacal(julday, geo, (enum Objs)i, EveningFirst, EveFirst[0]);
                    itf.Heliacal(julday, geo, (enum Objs)i, MorningLast, MorLast[0]);
                    break;
                case Venus:
                    itf.Heliacal(julday, geo, (enum Objs)i, EveningFirst, EveFirst[1]);
                    itf.Heliacal(julday, geo, (enum Objs)i, MorningLast, MorLast[1]);
                    break;
                case Moon:
                    itf.Heliacal(julday, geo, (enum Objs)i, EveningFirst, EveFirst[2]);
                    itf.Heliacal(julday, geo, (enum Objs)i, MorningLast, MorLast[2]);
                    break;
                default:
                    ;
                }
            }
            else
            {
                HelRis[i].ds.d1 = HelRis[i].ds.d2 = HelRis[i].ds.d3 = 0.0;
                HelSet[i].ds.d1 = HelSet[i].ds.d2 = HelSet[i].ds.d3 = 0.0;
            }
    }
    if (Cbp->Occultations)
    {
        GetOccult(true, false);
        GetOccult(false, false);
    }
#ifdef QT
    if (Cbp->Heliacal || Cbp->Occultations)
        qApp->restoreOverrideCursor();
#endif

    return true;
}

void StdGraphicList::GetEcl(struct Ecl& e, bool glob, bool dir, bool lun) const
{
    AstroInterface& itf = *First->GetInterface();
    if (glob)
        e.r = itf.ComputeGlobEclipse(First->GetJd(), First->DefSweFlags, dir, lun);
    else
        e.r = itf.ComputeLocEclipse(First->GetJd(), First->DefSweFlags, First->Latitude.Get(), First->Longitude.Get(), First->Altitude, dir);
    if (e.r == -1)
        itf.GetError(e.err);
    else
    {
        e.err = "";
        for (int j = 0; j < 8; j++)
            e.d[j] = itf.GetEclipseValue(j);
        e.r = itf.ComputeEclPos(e.d[0], First->DefSweFlags);
        e.d[8] = itf.GetEclipseValue(8);
        e.d[9] = itf.GetEclipseValue(9);
    }
}

void StdGraphicList::DisplayValues(const AstroString& as, const struct DataValues& dv)
{
    AstroString buf;
    SetTextStyle(TabText);
    DrawTabText(as);
    DrawTabText(dv.Retro ? "R" : " ");
    SetTextStyle(TabDot);
    DTT(DecToDeg(dv[0]), true, false);
    DTT(DecToDeg(dv[1]), true, false);
    DTT(dv[2], false, true);
    DTT(dv[3], false, true);
    DTT(dv[4], false, true);
    DTT(dv[5], false, true);
    NewLine();
}

bool StdGraphicList::Redisplay()
{
    AstroString as;
    Init();
    W += W /2;
#ifdef	IFEXCEPT
    try
    {
#endif
        if (Cbp->Sidebars)
            DisplayValues(*First);
        if (Cbp->DisplayMidPoints)
        {
            if (Second && (Afal.GetFlags() & Mutual))
                DispMidPoints(*First, *Second, true);
            else
                DispMidPoints(*First, *First, false);
        }
        if (Second && Cbp->Sidebars)
            DisplayValues(*Second);
        if (Cbp->AspectsFrame)
            DisplayAspects();
        if (Cbp->Sabian)
            DisplaySabianDegrees(*First);
        if (Cbp->RiseSet)
            DisplayRiseSet(*First);
        if (Cbp->Heliacal)
            DisplayHeliacal(*First);
        if (Cbp->GlobEclipse)
            DisplayEclipses(*First);
        if (Cbp->AspectsConfig)
            DisplayAspectsConfiguration(*First);
        if (Cbp->Apsides)
            DisplayApsides(*First);
        if (Cbp->ArabicParts)
            DisplayParts(*First);
        if (Cbp->Interpretation)
            DisplayInterp(*First);
        if (Cbp->InterpretTrans)
            DisplayInterpTransit();
        if (Cbp->DecTerms)
            DisplayDecTerms(*First);
        if (Second && Cbp->DecTerms)
            DisplayDecTerms(*Second);
        if (Cbp->Occultations)
            DisplayGlobOcculations(*First);
        if (Cbp->PlanetsRank)
        {
            First->GetPlanetsRank(&Afal);
            DisplayRank(*First);
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
    return true;
}

void StdGraphicList::DispMidPoints(const AstroObjs& a, const AstroObjs& b, bool ifsameplanet)
{
    int l = W / 6, l2 = l / 2, li, lj, k = 0;
    const int tab[] = { 0, l / 3, l + l2, 2 * l + l2, -1 };
    AstroString as, buf;
    NewLine();
    SetTextStyle(Title);
    if (ifsameplanet)
        DrawText(Sprintf(i18n("Midpoints List for %a and %a"), &as, &First->Name, &Second->Name));
    else
        DrawText(Sprintf(i18n("Midpoints List for %a"), &as, &First->Name));
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(TabText);
    NewLine();
    DrawTabText("");
    DrawTabText(i18n("Object 1"));
    DrawTabText(i18n("Object 2"));
    DrawTabText(i18n("Angle"));
    NewLine(true);
    NewLine();
    const AstroMidPoints& amp = *Afal.GetAmp();
    li = amp.GetX();
    lj = amp.GetY();
    for (int i = 0; i < li; i++)
        for (int j = i; j < lj; j++)
        {
            float mp = amp.Get((enum Objs)i, (enum Objs)j);
            if (mp != NOVALUE)
            {
                as = ++k;
                as += " ";
                DrawTabText(as);
                SetTextStyle(TabText);
                DrawTabText(a << i);
                DrawTabText(b << j);
                if (!Nl())
                {
                    //SetTextStyle(TabRight);
                    Ag->RMove(-(17 * Ow) / 10);
                    Ag->DegSignMin(DecToDeg(mp), false, false, Cbp->DisplaySeconds);
                }
                NewLine();
            }
        }
    NewLine();
}

void StdGraphicList::DisplayValues(const AstroObjs& ao)
{
    int l = W / 9, l5 = l / 5;
    const int tab[] = { 0, 2 * l,  2 * l + l / 4, 3 * l + l5, 4 * l + l5 , 5 * l + l5, 6 * l + l5, 7 * l + l5,  8 * l + l5, -1 };
    AstroString as, ty;
    const _AstroRestrictions& ar = ao();
    NewLine();
    SetTextStyle(MainTitle);
    ty = ao.GetSubTypeName();
    DrawText(Sprintf(i18n("%a Values List for"), &as, &ty));
    NewLine();
    DrawText(ao.Name);
    NewLine();
    Ag->FontSize(AstroGraphics::Tiny);
    DrawInfo(ao);
    NewLine();
    if (Cbp->DisplayComment && ao.Comment.Len() > 0)
    {
        DrawComment(ao);
        NewLine();
        NewLine();
    }
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(TabText);
    DrawTabText(i18n("Name"));
    DrawTabText("R");
    SetTextStyle(SubTitle);
    DrawTabText(ao().Equatorial ? i18n("Rectasc.") : i18n("Longitude"));
    DrawTabText(ao().Equatorial ? i18n("Declin.") : i18n( "Latitude"));
    DrawTabText(i18n("Dist (AU)"));
    DrawTabText(i18n("Speed Lon"));
    DrawTabText(i18n("Speed Lat"));
    DrawTabText(i18n("Speed Dis"));
    NewLine(true);
    NewLine();
    ar([&](int i)
    {
        if(i >= Ascendant && i <= House_12)
        {
            as = ao << i;
            if (ao().Equatorial)
                switch (i)
                {
                case Ascendant:
                    as = i18n("Equ Ascendant");
                    break;
                case MC :
                    as = i18n("ARMC");
                    break;
                case Descendant:
                    as = i18n("Equ Descendant");
                    break;
                case FC:
                    as = i18n("ARIC");
                    break;
                default:
                    ;
                };
            DisplayValues(as, *ao[i]);
        }
        else
            DisplayValues(ao << i, *ao[i]);
    });
    NewLine();
}

void StdGraphicList::DisplayAspects()
{
    int i = 1, l = W / 6, l2 = l / 2;
    const int tab[] = { 0, l / 4, l + l2, 2 * l + l2, 3 * l + l2, 4 * l + l2, 5 * l + l2, 6 * l, -1 };
    AstroString as, buf;
    AstroAspects aa(Second ? ~(*Second) : ~(*First));
    AspectFound* af;
    const AstroObjs &ao = *First, &ao1 = Second ? * Second : * First;
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(Title);
    if (Second)
        DrawText(Sprintf(i18n("Aspects List for %a and %a (%a)"), &as, &First->Name, &Second->Name, &Second->GetSubTypeName()));
    else
        DrawText(Sprintf(i18n("Aspects List for %a"), &as, &First->Name));
    NewLine();
    SetTextStyle(TabText);
    NewLine();
    DrawTabText("");
    DrawTabText(i18n("Object 1"));
    DrawTabText(i18n("Aspect"));
    DrawTabText(i18n("Object 2"));
    DrawTabText(i18n("Actual Orb"));
    DrawTabText(i18n("Direction"));
    DrawTabText(i18n("Way"));
    NewLine(true);
    NewLine();
    i = 1;
    foreachc(Afal, AstroFoundAspectsList)
    {
        const AspectFound* af = !it;
        if (af->Oc == ARABPART) continue;
        if (af->Asp == Opposition && !Second)
            if ((af->Oa == Ascendant && af->Ob == Descendant) || (af->Oa == MC && af->Ob == FC) || (af->Oa == North_Node && af->Ob == South_Node)) continue;
        as = i++;
        as += " ";
        SetTextStyle(TabRight);
        DrawTabText(as);
        SetTextStyle(TabText);
        DrawTabText(ao << af->Oa);
        DrawTabText(aa << af->Asp);
        DrawTabText(ao1 << af->Ob);
        SetTextStyle(TabDot);
        double da = (af->Asp >= Parallel/*af->Asp == Parallel || af->Asp == Antiparallel*/ ? af->ExtraOrb : DiffAngle(af->Angle_a, af->Angle_b));
        DTT(DecToDeg(fabs(da - (aa * af->Asp))), false, false);
        switch (af->AspectSide)
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
        switch (af->AspWay)
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
    if (Cbp->DisplayMidPoints)
    {
        NewLine();
        SetTextStyle(Title);
        DrawText(Sprintf(i18n("List Aspects between %a's Midpoints and %a's objects"), &as, &ao.Name, &ao1.Name));
        NewLine();
        NewLine();
        SetTabList(tab, true);
        SetTextStyle(TabText);
        NewLine();
        DrawTabText("");
        DrawTabText(i18n("Midpoint"));
        DrawTabText(i18n("Aspect"));
        DrawTabText(i18n("Object"));
        DrawTabText(i18n("Actual Orb"));
        DrawTabText(i18n("Direction"));
        DrawTabText(i18n("Way"));
        NewLine(true);
        NewLine();
        i = 1;
        foreachc(~Afal, AlAf)
        {
            const AspectFound* af = !it;
            as = i++;
            as += " ";
            SetTextStyle(TabRight);
            DrawTabText(as);
            SetTextStyle(TabText);
            DrawTabText(Sprintf("%a/%a", &buf, &(ao < af->Oa) , &(ao < af->Oc)));
            DrawTabText(aa << af->Asp);
            DrawTabText(ao1 << af->Ob);
            SetTextStyle(TabDot);
            double da = DiffAngle(af->Angle_a, af->Angle_b);
            DTT(DecToDeg(fabs(da - (aa * af->Asp))), false, false);
            switch (af->AspectSide)
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
            switch (af->AspWay)
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
    }
    if (Cbp->ArabicParts)
    {
        const int tab[] = { 0, l2, 2 * l, 3 * l, 4 * l, 5 * l, 6 * l, -1 };
        i = 1;
        NewLine();
        SetTextStyle(Title);
        DrawText(Sprintf(i18n("List Aspects between %a's Parts and %a's objects"), &as, &ao.Name, &ao1.Name));
        NewLine();
        SetTabList(tab, true);
        SetTextStyle(TabText);
        NewLine();
        DrawTabText("");
        DrawTabText(i18n("Part"));
        DrawTabText(i18n("Aspect"));
        DrawTabText(i18n("Object"));
        DrawTabText(i18n("Actual Orb"));
        DrawTabText(i18n("Direction"));
        DrawTabText(i18n("Way"));
        NewLine(true);
        NewLine();
        foreachc(Afal, AstroFoundAspectsList)
        {
            const AspectFound* af = !it;
            if (af->Oc != ARABPART) continue;
            if (af->Ob >= House_1 && af->Ob <= House_12) continue;
            as = i++;
            as += " ";
            SetTextStyle(TabRight);
            DrawTabText(as);
            SetTextStyle(TabText);
            DrawTabText(*Asr->PartsNames[af->Oa]);
            DrawTabText(aa << af->Asp);
            DrawTabText(ao1 << af->Ob);
            SetTextStyle(TabDot);
            double da = DiffAngle(af->Angle_a, af->Angle_b);
            DTT(DecToDeg(fabs(da - (aa * af->Asp))), false, false);
            switch (af->AspectSide)
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
            switch (af->AspWay)
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
    }
    NewLine();
}

void StdGraphicList::SaveRiseSet(AstroDate& ad, int i, enum ConjAngles ca)
{
    AstroString as;
    double d = ValRS[ca][i];
    if (d == -1.0)
    {
        DrawTabText(i18n("Unavailable"));
        return;
    }
    ad.SetJd(d);
    DrawTabText(ad.GetTime(as));
    auto asp = new struct AspData;
    asp->ak = RiseSet;
    asp->a = (enum Objs)i;
    asp->b = asp->c = Undefined_Obj;
    asp->jd = d;
    asp->y = Pos();
    Append(asp);
}

void StdGraphicList::SaveHeliacal(AstroDate& ad, int i, int j, enum AspKind ak)
{
    AstroString as, as1;
    Double3* d3;
    switch (ak)
    {
    case HelRising :
        d3 = &HelRis[i];
        break;
    case HelSetting :
        d3 = &HelSet[i];
        break;
    case EveningFirst :
        d3 = &EveFirst[i];
        break;
    case MorningLast :
        d3 = &MorLast[i];
        break;
    default:
        return;
    }
    ad.SetJd(d3->d3[j]);
    DrawTabText(ad.GetDate(as, true) + " " + ad.GetTime(as1, 0, true));
    auto asp = new struct AspData;
    asp->ak = ak;
    asp->a = (enum Objs)i;
    asp->b = asp->c = Undefined_Obj;
    asp->jd = d3->d3[j];
    asp->y = Pos();
    Append(asp);
}

void StdGraphicList::SaveEclipse(double julday, bool local, bool lunar, double latitude, double longitude)
{
    auto asp = new struct AspData;
    asp->y = Pos();
    asp->ak = Eclipse;
    asp->jd = julday;
    asp->a = lunar ? Moon : Sun;
    asp->b  = Undefined_Obj;
    asp->c = local ? Undefined_Obj : The_Earth;
    asp->apos = latitude;
    asp->bpos = longitude;
    Append(asp);
}

void StdGraphicList::DisplayEclipses(const AstroObjs& a)
{
    AstroString as;
    int l = W / 7, l2= l / 2;
    const int tab[] = { 0, l2, 2 * l - l2, 3 * l - l2, 4 * l - l2, 5 * l, 6 * l - l2, 6* l + l /6, -1 };
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(Title);
    DrawText(i18n("Previous/Next Global Eclipses"));
    NewLine();
    DrawText(Sprintf(i18n("from %a"), &as, &a.Name));
    NewLine();
    SetTextStyle(TabText);
    NewLine();
    DrawTabText(i18n("Type"));
    DrawTabText(i18n("Beginning"));
    DrawTabText(i18n("Maximum"));
    DrawTabText(i18n("End"));
    DrawTabText(i18n("Type"));
    DrawTabText(i18n("Latitude"));
    DrawTabText(i18n("Longitude"));
    NewLine(true);
    NewLine();
    DisplayGlobEclipse(a, false, false);
    DisplayGlobEclipse(a, true, false);
    DisplayGlobEclipse(a, false, true);
    DisplayGlobEclipse(a, true, true);
    NewLine();
    NewLine();
    SetTextStyle(Title);
    DrawText(i18n("Previous/Next Local Eclipses"));
    NewLine();
    DrawText(Sprintf(i18n("from %a"), &as, &a.Name));
    SetTextStyle(TabText);
    NewLine();
    NewLine();
    DisplayLocEclipse(a, false);
    DisplayLocEclipse(a, true);
    NewLine();
    NewLine();
}

void StdGraphicList::DisplayGlobEclipse(const AstroObjs& a, bool direction, bool lunar)
{
    AstroString as, date, time;
    AstroDate ad = a;
    const struct Ecl& e = lunar ? LunGlobEcl[direction ? 0 : 1] : SolGlobEcl[direction ? 0 : 1];
    double ecl = e.d[0];
    if (e.r == -1)
    {
        AstroMessage(e.err);
        return;
    }
    ad.SetJd(e.d[2]);
    DrawButton();
    DrawTabText(lunar ? i18n("Lunar") : i18n("Solar"));
    DrawTabText(ad.GetDate(date, true) + " " + ad.GetTime(time));
    SaveEclipse(ad.GetJd(), false, lunar, e.d[9], e.d[8]);
    ad.SetJd(ecl);
    DrawTabText(ad.GetDate(date, true) + " " + ad.GetTime(time));
    SaveEclipse(ad.GetJd(), false, lunar, e.d[9], e.d[8]);
    ad.SetJd(e.d[3]);
    DrawTabText(ad.GetDate(date, true) + " " + ad.GetTime(time));
    SaveEclipse(ad.GetJd(), false, lunar, e.d[9], e.d[8]);
    switch (e.r)
    {
    case SE_ECL_TOTAL:
        as = i18n("Total");
        break;
    case SE_ECL_ANNULAR:
        as = i18n("Annular");
        break;
    case SE_ECL_TOTAL + SE_ECL_CENTRAL:
        as = i18n("Total-central");
        break;
    case SE_ECL_TOTAL + SE_ECL_NONCENTRAL:
        as = i18n("Total-noncentral");
        break;
    case SE_ECL_ANNULAR + SE_ECL_CENTRAL:
        as = i18n("Annular-central");
        break;
    case SE_ECL_ANNULAR + SE_ECL_NONCENTRAL:
        as = i18n("Annular-noncentral");
        break;
    case SE_ECL_PARTIAL:
        as = i18n("Partial");
        break;
    default:
        as = i18n("Undefined");
    };
    DrawTabText(as);
    AstroHM hm = e.d[9];
    hm.Get(as, HM_Latitude);
    if (!lunar)	DrawTabText(as);
    hm = e.d[8];
    hm.Get(as, HM_Longitude);
    if (!lunar) DrawTabText(as);
    NewLine();
}

void StdGraphicList::DisplayLocEclipse(const AstroObjs& a, bool direction)
{
    AstroString as, date, time;
    const struct Ecl &e = SolLocEcl[direction ? 0 : 1];
    double ecl = e.d[0];
    int r = e.r;
    if (r == -1)
    {
        AstroMessage(e.err);
        return;
    }
    AstroDate ad = a;
    ad.SetJd(e.d[1]);
    DrawButton();
    DrawTabText(i18n("Solar"));
    DrawTabText(ad.GetDate(date, true) + " " + ad.GetTime(time));
    SaveEclipse(ad.GetJd(), true, false, a.Latitude.Get(), a.Longitude.Get());
    ad.SetJd(ecl);
    DrawTabText(ad.GetDate(date, true) + " " + ad.GetTime(time));
    SaveEclipse(ad.GetJd(), true, false, a.Latitude.Get(), a.Longitude.Get());
    ad.SetJd(e.d[4]);
    DrawTabText(ad.GetDate(date, true) + " " + ad.GetTime(time));
    SaveEclipse(ad.GetJd(), true, false, a.Latitude.Get(), a.Longitude.Get());
    as = "";
    if (r & SE_ECL_TOTAL) as += i18n("Total");
    if (r & SE_ECL_ANNULAR) as += i18n("Annular");
    if (r & SE_ECL_PARTIAL) as += i18n("Partial");
    if (r & SE_ECL_VISIBLE) as += i18n(", Visible");
    if (r & SE_ECL_MAX_VISIBLE) as += i18n(", Max.Visible");
    if (r & SE_ECL_1ST_VISIBLE) as += i18n(", 1st Visible");
    if (r & SE_ECL_2ND_VISIBLE) as += i18n(", 2nd Visible");
    if (r & SE_ECL_3RD_VISIBLE) as += i18n(", 3rd Visible");
    if (r & SE_ECL_4TH_VISIBLE) as += i18n(", 4th Visible");
    DrawTabText(as);
    NewLine();
}

void StdGraphicList::DisplayRank(const AstroObjs& a)
{
    AstroString as;
    const int l = W / 10;
    int y1;
    NewLine();
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Planets Rank for %a"), &as, &a.Name));
    NewLine();
    NewLine();
    Ag->RMove(l);
    for (int i = 0; i < 10; i++)
    {
        const struct AstroObjs::PlanetRank* pr = a / i;
        Ag->Color(a.GetObjColor(pr->planet));
        Ag->JustifGlyph(a.GetObjChar(pr->planet), AstroGraphics::Center, l);
    }
    NewLine();
    NewLine();
    Ag->RMove(XMargin);
    const int y = W / 7, max = (a / 0)->score, max10 = max / 10 + ((max % 10) ? 1 : 0), ym = y / max10;
    Ag->Grey();
    Ag->RLine(0,  y);
    y1 = Ag->GetY();
    SetHeight(Ag->GetHeight() + y + 2);
    Ag->RLine(10 * l, 0);
    Ag->RMove(-10 * l, 0);
    for (int i = 1; i <= max10; i++)
    {
        Ag->RMove(0, -ym);
        Ag->RLine((l / 10), 0);
        Ag->RMove(-(l / 10), 0);
    }
    Ag->Fore();
    auto pr = CSC(struct AstroObjs::PlanetRank*, a / 0);
    int sc = (y * pr->score) / max;
    Ag->Move(XMargin + l + l / 2, y1 - sc);
    y1 = y;
    for (int i = 1; i < 10; i++)
    {
        pr = CSC(struct AstroObjs::PlanetRank*, a / i);
        sc =  (y * pr->score) / max;
        Ag->RLine(l, y1 - sc);
        y1 = sc;
    }
}

void StdGraphicList::DisplayRiseSet(const AstroObjs& a)
{
    int l = W / 6;
    const int tab[] = { 0, l, 2 * l, 3 * l, 4 * l, 5 * l, -1 };
    AstroString as;
    AstroDate ad = a;
    const _AstroRestrictions& ar = a();
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Objects Rising, Culminating and Settings Times for %a"), &as, &a.Name));
    SetTextStyle(TabText);
    NewLine();
    NewLine();
    DrawTabText(i18n("Name"));
    SetTextStyle(TabRight);
    DrawTabText(i18n("Rising"));
    DrawTabText(i18n("Culminating"));
    DrawTabText(i18n("Setting"));
    DrawTabText(i18n("At Nadir"));
    NewLine(true);
    NewLine();
    ar([&](int i)
    {
        DrawButton();
        SetTextStyle(TabText);
        DrawTabText(a << i);
        SetTextStyle(TabRight);
        SaveRiseSet(ad, i, Rising);
        SaveRiseSet(ad, i, Culminating);
        SaveRiseSet(ad, i, Setting);
        SaveRiseSet(ad, i, AtNadir);
        NewLine();
    });
    NewLine();
}

void StdGraphicList::DisplayHeliacal(const AstroObjs& a)
{
    int l = W / 6;
    const int tab[] = { 0, l, 2 * l, 3 * l, 4 * l, 5 * l /*-l /4*/, -1 };
    AstroString as;
    AstroDate ad = a;
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Heliacal Visibility for %a"), &as, &a.Name));
    NewLine();
    SetTextStyle(TabText);
    NewLine();
    DrawTabText(i18n("Name"));
    DrawTabText(i18n("Type"));
    DrawTabText(i18n("Beginning"));
    DrawTabText(i18n("Optimum"));
    DrawTabText(i18n("End"));
    NewLine(true);
    NewLine();
    for (int i = Sun; i <= Neptune; i++)
        if (a == i)
        {
            if (!HelRis[i].IfNull())
                DrawButton();
            DrawTabText(a << i);
            DrawTabText(i18n("Morning First"));
            if (HelRis[i].IfNull())
                DrawTabText(i18n("no heliacal date found within 5 synodic periods"));
            else
            {
                SaveHeliacal(ad, i, 0, HelRising);
                SaveHeliacal(ad, i, 1, HelRising);
                SaveHeliacal(ad, i, 2, HelRising);
            }
            NewLine();
            if (!HelSet[i].IfNull())
                DrawButton();
            DrawTabText("");
            DrawTabText(i18n("Evening Last"));
            if (HelSet[i].IfNull())
                DrawTabText(i18n("no heliacal date found within 5 synodic periods"));
            else
            {
                SaveHeliacal(ad, i, 0, HelSetting);
                SaveHeliacal(ad, i, 1, HelSetting);
                SaveHeliacal(ad, i, 2, HelSetting);
            }
            NewLine();
            if ((i == Mercury) || (i == Venus) || (i == Moon))
            {
                if (!EveFirst[i].IfNull())
                    DrawButton();
                DrawTabText("");
                DrawTabText(i18n("Evening First"));
                if (EveFirst[i].IfNull())
                    DrawTabText(i18n("no heliacal date found within 5 synodic periods"));
                else
                {
                    SaveHeliacal(ad, i, 0, EveningFirst);
                    SaveHeliacal(ad, i, 1, EveningFirst);
                    SaveHeliacal(ad, i, 2, EveningFirst);
                }
                NewLine();
                if (!MorLast[i].IfNull())
                    DrawButton();
                DrawTabText("");
                DrawTabText(i18n("Morning Last"));
                if (MorLast[i].IfNull())
                    DrawTabText(i18n("no heliacal date found within 5 synodic periods"));
                else
                {
                    SaveHeliacal(ad, i, 0, MorningLast);
                    SaveHeliacal(ad, i, 1, MorningLast);
                    SaveHeliacal(ad, i, 2, MorningLast);
                }
                NewLine();
            }
            NewLine();
        }
    NewLine();
}

void StdGraphicList::DisplayAspectsConfiguration(const AstroObjs& a)
{
    int l = W / 6, l2 = l / 2;
    const int tab[] = { 0, l + l2, 2 * l + l2, 3 * l + l2, 4 * l + l2, -1 };
    AstroString as;
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Aspects Configurations for %a"), &as, &a.Name));
    NewLine();
    NewLine(true);
    NewLine();
    SetTextStyle(TabText);
    foreachc(Acl, AspConfList)
    {
        DrawTabText(*Asr->AspConfigNames[(!it)->Ac]);
        for (int i = 0; i < (!it)->NbObjs; i++)
            DrawTabText(ObjName((!it)->O[i]));
        NewLine();
    }
    NewLine();
}

void StdGraphicList::LoadSabian()
{
    AstroRequest arq;
    arq.Exec("SELECT Idx, Sabian FROM Degrees WHERE Lang = '%s' UNION SELECT Idx, Sabian FROM Degrees WHERE Lang = 'en' AND Idx NOT IN (SELECT Idx FROM Degrees WHERE Lang = '%s') ORDER BY Idx", Asr->Lang, Asr->Lang);
    if (arq.Valid())
    {
        for (int i = 0; i < 360 && arq.Valid(); i++)
        {
            SabList[i]   = arq < "Sabian";
            arq.Next();
        }
    }

}

void StdGraphicList::DisplaySabianDegrees(const AstroObjs& a)
{
    int deg;
    AstroString as;
    int l = W / 18;
    const int tab[] = { 0, l, 2 * l, -1 };
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Sabian Degrees for %a"), &as, &a.Name));
    NewLine();
    SetTabList(tab);
    SetTextStyle(TabText);
    NewLine();
    DrawTabText(i18n("Pla"));
    DrawTabText(i18n("Deg"));
    DrawTabText(i18n("Caption"));
    NewLine(true);
    NewLine();
    for (int i = Sun; i <= Last_Planet; i++)
        if (a == i)
        {
            deg = a.SabianDegree((enum Objs)i);
            DrawTabText(a < i);
            as = deg;
            DrawTabText(as);
            DrawTabText(SabList[deg - 1]);
            NewLine();
        }
    if (a == XPoint)
    {
        deg = a.SabianDegree(XPoint);
        DrawTabText(a < XPoint);
        as = deg;
        DrawTabText(as);
        DrawTabText(SabList[deg - 1]);
        NewLine();
    }
    if (a.IfHouses())
        for (int i = Ascendant; i <= House_12; i++)
            if (a == i)
            {
                deg = a.SabianDegree((enum Objs)i);
                DrawTabText(a < i);
                as = deg;
                DrawTabText(as);
                DrawTabText(SabList[deg - 1]);
                NewLine();
            }
    if (a.IfExtra())
        for (int i = First_Extra; i <= Asr->LastExtra; i++)
            if (a == i)
            {
                deg = a.SabianDegree((enum Objs)i);
                DrawTabText(a < i);
                as = deg;
                DrawTabText(as);
                DrawTabText(SabList[deg - 1]);
                NewLine();
            }
    NewLine();
}

void StdGraphicList::DisplayApsides(const AstroObjs& a)
{
    AstroString as;
    const _AstroRestrictions& ar = a();
    int l = W / 6;
    const int tab[] = { 0, l, 2 * l, 3 * l, 4 * l, 5 * l - l / 4, -1 };
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Apsides for %a"), &as, &a.Name));
    NewLine();
    NewLine();
    SetTextStyle(TabText);
    DrawTabText(i18n("Planet"));
    DrawTabText(i18n("Asc Node"));
    DrawTabText(i18n("Desc Node"));
    DrawTabText(i18n("Perihelion"));
    DrawTabText(i18n("Aphelion"));
    NewLine(true);
    NewLine();
    ar([&](int i)
    {
        if(i == Sun || (i > Pluto && i < Earth) || (i > Vesta &&  i < First_Extra) || (i > XPoint)) return;
        DrawTabText(a << i);
        DrawDegSignMin(DecToDeg(Aps[i].Nasc[0]));
        DrawDegSignMin(DecToDeg(Aps[i].Ndsc[0]));
        DrawDegSignMin(DecToDeg(Aps[i].Peri[0]));
        DrawDegSignMin(DecToDeg(Aps[i].Aphe[0]));
        NewLine();
    });
    NewLine();
}

void StdGraphicList::DisplayParts(const AstroObjs& a)
{
    AstroString as;
    int l = W * 3 / 10;
    const int tab[] = { 0, 0 + l / 5, l, 2 * l, -1 };
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Arabic Parts for %a"), &as, &a.Name));
    NewLine();
    NewLine();
    SetTabList(tab, true);
    SetTextStyle(TabText);
    DrawTabText(i18n("Nb"));
    DrawTabText(i18n("Name"));
    DrawTabText(i18n("Position"));
    NewLine();
    NewLine(true);
    for (int i = 0; i < Asr->NbParts; i++)
    {
        as = i + 1;
        DrawTabText(as);
        if (PartsVals[i] == NOVALUE)
        {

            DrawTabText(i18n("Invalid Value"));
            NewLine();
            continue;
        }
        DrawTabText(*Asr->PartsNames[i]);
        DrawDegSignMin(DecToDeg(PartsVals[i]));
        NewLine();
    }
}

const AstroString StdGraphicList::GetTextInterp(const AstroString& code, AstroRequest& req) const
{
    req.Exec("SELECT COALESCE((SELECT Text FROM Interpret WHERE Lang = '%s' AND Code = '%a'), (SELECT Text FROM Interpret WHERE Lang = 'en' AND Code = '%a'))", Asr->Lang, &code, &code);
    return req < "coalesce";
}

const AstroString StdGraphicList::GetPl(enum Objs pl, bool ifhouse, int nb) const
{
    char buf[20];
    sprintf(buf, "pl%.2d %.2d %.2d", pl + 1, ifhouse ? 2 : 1, nb);
    return buf;
}

const AstroString StdGraphicList::GetAsp(enum Objs p1, enum Objs p2, enum Aspects asp, bool transiting) const
{
    char buf[15];
    if (p2 < p1)
    {
        enum Objs p3;
        p3 = p1;
        p2 = p1;
        p1 = p3;
    }
    if (transiting)
        sprintf(buf, "pl%.2dta %.2d %.2d", p1 + 1, p2 + 1, asp + 1);
    else
        sprintf(buf, "pl%.2da %.2d %.2d", p1 + 1, p2 + 1, asp + 1);
    return buf;
}

void StdGraphicList::DisplayInterp(const AstroObjs& a)
{
    enum Signs s;
    AstroRequest req;
    AstroString as, as1;
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Interpretation for %a"), &as, &a.Name));
    NewLine();
    NewLine();
    SetTextStyle(PlainText);
#ifdef	IFEXCEPT
    try
    {
#endif
        for (int i = Sun; i <= Last_Planet; i++)
            if (a == i)
            {
                s = Asg->GetSign(a * i);
                as1 = GetTextInterp(GetPl((enum Objs)i, false, s + 1), req);
                if (as1.Len())
                {
                    Sprintf(i18n("%a in %a : "), &as, &ObjName(i), &((*Asg) << s));
                    DrawMultiLineText(as + as1);
                    NewLine();
                }
            }
        NewLine();
        for (int i = Sun; i <= Last_Planet; i++)
            if (a == i)
            {
                as1 = GetTextInterp(GetPl((enum Objs)i, true, a.InHouse(i)), req);
                if (as1.Len())
                {
                    Sprintf(i18n("%a in House %d : "), &as, &ObjName(i), a.InHouse(i));
                    DrawMultiLineText(as + as1);
                    NewLine();
                }
            }
        foreachc(Afal, AstroFoundAspectsList)
        {
            const AspectFound* af = !it;
            as1 = GetTextInterp(GetAsp(af->Oa, af->Ob, af->Asp), req);
            if (as1.Len())
            {
                Sprintf(i18n("%a %a %a : "), &as, &ObjName(af->Oa), Asr->AspectNames[af->Asp], &ObjName(af->Ob));
                DrawMultiLineText(as + as1);
                NewLine();
            }
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
}

void StdGraphicList::DisplayInterpTransit()
{
    if (!Second) return;
    const AstroObjs &a = *First, &b = *Second;
    enum Signs s;
    AstroRequest req;
    AstroString as, as1;
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Interpretation for %a"), &as, &a.Name));
    NewLine();
    NewLine();
    SetTextStyle(PlainText);
#ifdef	IFEXCEPT
    try
    {
#endif
        foreachc(Afal, AstroFoundAspectsList)
        {
            const AspectFound* af = !it;
            as1 = GetTextInterp(GetAsp(af->Oa, af->Ob, af->Asp), req);
            if (as1.Len())
            {
                Sprintf(i18n("%a %a %a : "), &as, &ObjName(af->Oa), Asr->AspectNames[af->Asp], &ObjName(af->Ob), true);
                DrawMultiLineText(as + as1);
                NewLine();
            }
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
}

void StdGraphicList::DisplayDecTerms(const AstroObjs& a)
{
    AstroString as;
    int l = W / 5;
    const int tab[] = { 0, l, 2 * l, -1 };
    const _AstroRestrictions& ar = a();
    SetTextStyle(Title);
    DrawText(Sprintf(i18n("Table of Decans and Terms Rulers for %a"), &as, &a.Name));
    NewLine();
    NewLine();
    SetTabList(tab, true);
    SetTextStyle(TabText);
    NewLine();
    DrawTabText(i18n("Planet"));
    DrawTabText(i18n("Decan"));
    DrawTabText(i18n("Term"));
    NewLine(true);
    NewLine();
    ar([&](int i)
    {
        DrawTabText(a << i);
        DrawTabText(ObjName(a.GetDecan((enum Objs)i)));
        DrawTabText(ObjName(a.GetTerm((enum Objs)i)));
        NewLine();
    });
    NewLine();
}

void StdGraphicList::GetOccult(bool back, bool local)
{
    int r;
    const AstroObjs& ao = *First;
    AstroInterface& itf = *ao.GetInterface();
    double lat = ao.Latitude.Get(true), lon = ao.Longitude.Get(true);
    if (PrevGlobOccult == nullptr && back)
        PrevGlobOccult = new struct Occult[Last_Star];
    if (NextGlobOccult == nullptr && !back)
        NextGlobOccult = new struct Occult[Last_Star];
    struct Occult* GlobOccult = back ?  PrevGlobOccult : NextGlobOccult;
    auto f = [&](int i)
    {
        if (EXCL(i)) return;
        r = itf.LunarOccult(ao.GetJd(), i, ao.DefSweFlags, lat, lon, ao.Altitude, back, local);
        P;
        if (r != -1)
        {
            GlobOccult[i].r = r;
            for (int j = 0; j < 4; j++)
                GlobOccult[i][j] = itf.GetEclipseValue(j);
        }
    };
    ao().Iterate(f, true, false, true);
}

void StdGraphicList::SaveOccult(double julday, enum Objs o, bool local, double latitude, double longitude)
{
    auto asp = new struct AspData;
    asp->y = Pos();
    asp->ak = GlobOccult;
    asp->jd = julday;
    asp->a = o;
    asp->b  = Undefined_Obj;
    asp->c = local ? Undefined_Obj : The_Earth;
    asp->apos = latitude;
    asp->bpos = longitude;
    Append(asp);
}

void StdGraphicList::DisplayGlobOcculations(const AstroObjs& a)
{
	AstroString as, date, time, type;
    static const int globsense[] = { 2, 0, 3 };
    const AstroObjs& ao = *First;
    AstroDate ad = ao;
    int l = W / 5;
    const int tab[] = { 0, 7 * l / 10, 2 * l - l / 2, 3 * l - l / 3, 4 * l - l / 6, -1 };
		auto f = [&](int i)
		{
			if(EXCL(i)) return;
			DrawButton();
			DrawTabText(ao << i);
			int r = PrevGlobOccult[i].r;
			type="";
			if(r & SE_ECL_TOTAL)   type = i18n("Total");
			else if(r & SE_ECL_ANNULAR) type = i18n("Annular");
			else if(r & SE_ECL_PARTIAL) type = i18n("Partial");
			/*if(r & SE_ECL_CENTRAL) type += "-cent";
				if(r & SE_ECL_NONCENTRAL) type += -ncent";*/
			else if(type == "")         type = i18n("Undefined");
			DrawTabText(type);
			for(const int& j : globsense)
      {
				ad.SetJd(PrevGlobOccult[i][j]);
				DrawTabText(PrevGlobOccult[i][j] < 0.1 ? "--" : ad.GetDate(date, true) + " " + ad.GetTime(time, 0, true));
				SaveOccult(PrevGlobOccult[i][j], (enum Objs)i, false, ao.Latitude.Get(true), ao.Longitude.Get(true));
			}
			NewLine();
		};

		auto f1 = [&](int i)
		{
			if (EXCL(i)) return;
        DrawButton();
        DrawTabText(ao << i);
			int r = PrevGlobOccult[i].r;
			type="";
			if(r & SE_ECL_TOTAL)   type = i18n("Total");
			else if(r & SE_ECL_ANNULAR) type = i18n("Annular");
			else if(r & SE_ECL_PARTIAL) type = i18n("Partial");
			else if(type == "")         type = i18n("Undefined");
      DrawTabText(type);
        for(const int& j : globsense)
        {
            ad.SetJd(NextGlobOccult[i][j]);
            DrawTabText(NextGlobOccult[i][j] < 0.1 ? "--" : ad.GetDate(date, true) + " " + ad.GetTime(time, 0, true));
            SaveOccult(NextGlobOccult[i][j], (enum Objs)i, false, ao.Latitude.Get(true), ao.Longitude.Get(true));
        }
        NewLine();
		};

    SetTextStyle(Title);
    DrawText(i18n("Previous/Next Global Lunar Occultations"));
    NewLine();
    DrawText(Sprintf(i18n("from %a"), &as, &a.Name));
    NewLine();
    SetTabList(tab, true);
    NewLine();
    SetTextStyle(TabText);
    DrawTabText(i18n("Planet"));
    DrawTabText(i18n("Type"));
    DrawTabText(i18n("Beginning"));
    DrawTabText(i18n("Maximum"));
    DrawTabText(i18n("End"));
    NewLine(true);
    NewLine();
		a().Iterate(f, true, false, true);
    NewLine();
		a().Iterate(f1, true, false, true);
    NewLine();
}
