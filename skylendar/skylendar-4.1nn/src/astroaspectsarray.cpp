/***************************************************************************
                          astroaspectsarray.cpp  -  description
                             -------------------
    begin                : sam ao 9 2003
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

#include "astroaspectsarray.h"
#include "astromidpoints.h"

AstroAspectsArray::AstroAspectsArray(ChartBaseParams* cbp, ObjsVector* ov) : GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = AspectsArray;
    Cm = GraphicMode;
    DualChart = true;
    NbPM = 2;
    Aa = 0;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Comment"), DisplayComment);

}

AstroAspectsArray::~AstroAspectsArray()
{
    if (Aa)
        delete Aa;
}

bool AstroAspectsArray::Redisplay()
{
    int k, l, lk, ll, height, flags = 0;
    AstroString as;
    Ag->FontSize(AstroGraphics::Tiny);
    Ag->TextMetrics("O", &W, &H);
    S = Ag->GetSize();
    const int s3 = 3 * S;
    Px = S;
    //GetFS();
    if (!Second) Second = First;
    bool same = First == Second;
    Aa = new AstroAspects(!same ? ~(*Second) : ~(*First));
    C1 = First->CountObjs() + 1;
    C2 = Second->CountObjs() + 1;
    for (int i = Sun; i < Final_Star; i++)
    {
        if ((*First) == i) lk = i;
        if ((*Second) == i) ll = i;
    }
    if (Px + C1 * s3 > Ag->GetWidth())
        SetWidth(Px + C1 * s3);
    else
        Px = (Ag->GetWidth() - (C1 * s3)) / 2;
    Ag->FontSize(AstroGraphics::Tiny);
    Ag->FontSize(AstroGraphics::Medium, true);
    Py = s3;
    height = Py + C2 * s3;
    Ag->Grey();
    for (int i = 0; i <= C2; i++)
    {
        Ag->Move(Px, Py + s3 * i);
        Ag->Line(Px + C1 * s3, Py + s3 * i);
    }
    for (int i = 0; i <= C1; i++)
    {
        Ag->Move(Px + s3 * i, Py);
        Ag->Line(Px + s3 * i, Py + s3 * C2);
    }
    Ag->Fore();
    for (int i = 1, k = Sun; i < C1; i++, k++)
    {
        while ( !((*First) == k) && k <= lk) k++;
        DrawPlanet(i, 1, (enum Objs)k);
    }
    for (int i = 2, k = Sun; i < C2 + 1; i++, k++)
    {
        while ( !((*Second) == k) && k <= ll) k++;
        DrawPlanet(0, i, (enum Objs)k);
    }
    flags |= (Second ? IfSamePlanet + Mutual : MPa);
    Afat.GetAspects(*Aa, *First, *Second, flags);
    const AstroMidPoints& amp = *Afat.GetAmp();
    Ag->FontSize(AstroGraphics::Tiny, true);
    Ag->FontSize(AstroGraphics::Very_Tiny);
    for (int i = 1, k = Sun; i < C1; i++, k++)
        for (int j = 2, l = Sun; j <= C2; j++, l++)
        {
            while ( !((*First) == k) && k <= lk) k++;
            while ( !((*Second) == l) && l <= ll) l++;
            if (!Afat.Valid(k, l)) continue;
            const AspectFound af((enum Aspects)Afat.Get(k, l), (enum Objs)k, (enum Objs)l);
            if (!(same && k == l))
            {
                if (af.Asp != Unknown_Aspect)
                    DrawAspect(i, j, af);
                else
                {
                    if (!amp.Valid(k, l)) continue;
                    float mp = amp.Get((enum Objs)k, (enum Objs)l);
                    if (mp != NOVALUE)
                        DrawMidpoint(i, j, mp);
                }
            }
        }
    Ag->FontSize(AstroGraphics::Tiny);
    Ag->Fore();
    if (same)
    {
        Ag->Move(Px + s3 * 0 + (s3 - W) / 2, Py + s3 * 1 - (s3 - H) / 2 - S / 5);
        Ag->Text(Sprintf("%d:", &as, First->GetRing() + 1));
    }
    else
    {
        Ag->Move(Px + s3 - S, Py + s3 * 1 - (s3 - H) / 2 - S / 5);
        Ag->Text(Sprintf("%d:", &as, First->GetRing() + 1));
        Ag->Move(Px + s3 * 0 + (s3 - W) / 2, Py + s3 - S / 5);
        Ag->Text(Sprintf("%d:", &as, Second->GetRing() + 1));
    }
    Init(false, height + 2 * H);
    DrawInfo(*First , First->GetRing());
    if (!same && Second->GetRing() != -1)
        DrawInfo(*Second , Second->GetRing());
    if (Cbp->DisplayComment)
        DrawComment(Second ? *Second : *First);
    SetHeight(height + 2 * H + GetSizeLines());
    return true;
}

void AstroAspectsArray::DrawPlanet(int x, int y, enum Objs o)
{
    AstroString as;
    const int s3 = 3 * S;
    const AstroObjs& ao = (*First) == o ? *First : *Second;
    if (!(ao == o)) return;
    char c = ao.GetObjChar(o);
    if (!c) as = ao < o;
    Ag->Color(ao.GetObjColor(o));
    if (c)
    {
        Ag->Move(Px + s3 * x + (s3 - W) / 2, Py + s3 * y - (s3 - H) / 2);
        Ag->Glyph(First->GetObjChar(o));
    }
    else
    {
        int w;
        Ag->TextMetrics(as, &w, 0);
        Ag->Move(Px + s3 * x + (s3 - w) / 2, Py + s3 * y - (s3 - H) / 2);
        Ag->Text(as);
    }
}

void AstroAspectsArray::DrawAspect(int x, int y, const AspectFound& af)
{
    const int s3 = 3 * S;
    Ag->Move(Px + s3 * x + (s3 - W) / 2, Py + s3 * y - (s3 - H / 2) / 2);
    Ag->Color(COL[Aa->Color(af.Asp)]);
    Ag->Glyph(Aa->GetAspChar(af.Asp));
}

void AstroAspectsArray::DrawMidpoint(int x, int y, float mp)
{
    const int s3 = 3 * S;
    Ag->Move(Px + s3 * x + (s3 -  ((7 * W) / 2)) / 2, Py + s3 * y - (s3 - H / 2) / 2);
    Ag->FontSize(AstroGraphics::Very_Tiny, true);
    Ag->Color(Asg->GetColor(Asg->GetSign(mp)));
    Ag->DegSignMin(DecToDeg(mp));
    Ag->FontSize(AstroGraphics::Tiny, true);
}
