/***************************************************************************
                          astroobjectslist.cpp  -  description
                             -------------------
    begin                : ven jun 27 2003
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

#include "astroobjectslist.h"
#include "astrosql.h"

AstroObjectsList::AstroObjectsList(ChartBaseParams* cbp, ObjsVector* ov) : GraphicListBase(this, cbp, ov)
{
    Ct = ObjectList;
    DualChart = false;
    NbPM = 1;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
}

AstroObjectsList::~AstroObjectsList()
{
}

bool AstroObjectsList::Redisplay()
{
    int h;
    const AstroObjs& ao = *AstroChartBase::operator[](Search());
    AstroRequest Arq;
    char b[14], lang[3];
    Init();
    Ag->GlyphMetrics('7', &w, &h);
    NewLine();
    SetTextStyle(MainTitle);
    DrawText(i18n("Objects and Aspects List"));
    NewLine();
    int l = W / 5, l2 = l / 2;
    const int tab[] = { 0, l / 3, l + l2, 2 * l + l2, 3 * l + l2, 4 * l + l2, 5 * l + l2, 6 * l + l2 };
    AstroString as, buf;
    SetTabList(tab);
    SetTextStyle(Title);
    DrawText(i18n("Planets & Standard Objects"));
    NewLine();
    NewLine();
    SetTextStyle(TabText);
    DrawTabText(" ");
    DrawTabText(i18n("Short Name"));
    DrawTabText(i18n("Name"));
    NewLine();
    NewLine();
#ifdef IFEXCEPT
    try
    {
#endif
        for (int i = Sun; i<= Last_Planet; i++)
        {
            const char c = ao.GetObjChar(i);
            if (c)
            {
                Ag->Color(ao.GetObjColor(i));
                DrawTabGlyph(c);
            }
            else
                DrawTabGlyph(' ');
            Ag->Fore();
            DrawTabText(ao < i);
            DrawTabText(ao << i);
            NewLine();
        }
        NewLine();
        SetTextStyle(Title);
        DrawText(i18n("Extra Objects"));
        NewLine();
        NewLine();
        SetTextStyle(TabText);
        for (int i = First_Extra; i<= ao().LastExtra; i++)
        {
            const char c = ao.GetObjChar(i);
            if (c)
                Ag->Glyph(c);
            DrawTabText(" ");
            DrawTabText(ao < i);
            DrawTabText(ao << i);
            NewLine();
        }
        NewLine();
        SetTextStyle(Title);
        DrawText(i18n("Stars"));
        NewLine();
        NewLine();
        SetTextStyle(TabText);
        DrawTabText(" ");
        DrawTabText(i18n("Short Name"));
        DrawTabText(i18n("Name"));
        DrawTabText(i18n("Magnitude"));
        NewLine();
        NewLine();
        for (int i = First_Star; i < Final_Star; i++)
        {
            const char c = ao.GetObjChar(i);
            if (c)
                Ag->Glyph(c);
            DrawTabText(" ");
            DrawTabText(ao < i);
            DrawTabText(ao << i);
            double d = ao.GetInterface()->GetMagnitude(i);
            if (d < 999)
            {
                AstroString as;
                as = d;
                DrawTabText(as);
            }
            NewLine();
        }
        NewLine();
        SetTextStyle(Title);
        DrawText(i18n("Interpretation of Stars"));
        NewLine();
        NewLine();
        SetTextStyle(PlainText);
        for (int i = First_Star; i < Final_Star; i++)
        {
            sprintf(b, "stars 00 %.2d", i - First_Star + 1);
            Arq.Exec("SELECT COALESCE((SELECT Text FROM Interpret WHERE Lang = '%s' AND Code = '%s'), (SELECT Text FROM Interpret WHERE Lang = 'en' AND Code = '%s'))", Asr->Lang, b, b);
            as = Arq < "coalesce";
            if (as.Len())
            {
                DrawMultiLineText(ObjName(i) + " : " + as);
                NewLine();
            }

        }
        NewLine();
        NewLine();
        const AstroAspects aa(~ao);
        SetTextStyle(Title);
        DrawText(i18n("Aspects"));
        NewLine();
        NewLine();
        SetTextStyle(TabText);
        DrawTabText(" ");
        DrawTabText(i18n("Short Name"));
        DrawTabText(i18n("Name"));
        DrawTabText(i18n("Value"));
        NewLine();
        NewLine();
        SetTextStyle(TabText);
        for (int i = Conjunction; i < Unknown_Aspect; i++)
        {
            Ag->Color(COL[aa.Color((enum Aspects)i)]);
            DrawTabGlyph(aa.GetAspChar((enum Aspects)i));
            Ag->Fore();
            DrawTabText(aa < (enum Aspects)i);
            DrawTabText(aa << (enum Aspects)i);
            SetTextStyle(TabDot);
            DrawTabText(Dbl(as, aa * (enum Aspects)i));
            SetTextStyle(TabText);
            NewLine();
        }
        NewLine();
        NewLine();
        SetTextStyle(Title);
        DrawText(i18n("Arabic Parts"));
        NewLine();
        NewLine();
        SetTextStyle(TabText);
        DrawTabText(i18n("Nb"));
        DrawTabText(i18n("Name"));
        NewLine();
        NewLine();
        SetTextStyle(TabText);
        for (int i = 0; i < Asr->NbParts; i++)
        {
            as = i + 1;
            DrawTabText(as);
            DrawTabText(*Asr->PartsNames[i]);
            NewLine();
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
    return true;
}
