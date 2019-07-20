/***************************************************************************
 *   Copyright (C) 2004 by Christophe Gros                                 *
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
#include "astrotarotspreads.h"
#include "spreads.h"
#include "astrosql.h"

static const int NbCards[5] = { 4, 7, 10, 12, 10 };

AstroTarotSpreads::AstroTarotSpreads(ChartBaseParams* cbp, ObjsVector* ov): GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = Tarots_Spreads;
    Cm = GraphicMode;
    DualChart = false;
    for (int i = 0; i < MAXLEVELS; i++)
        for (int j = 0; j < MAXCARDS; j++)
        {
            Ac[i][j] = 0;
            Ci[i][j].Ap = 0;
        }
    Asr->SetTarotsPixmaps();
    Asr->LoadInterTarots();
    NbPM = 5;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("FrameLess"), Frameless);
    PMSET(2, i18n("Display Comment"), DisplayComment);
    PMSET(3, i18n("Display Tarot Table"), DispTarotTable);
    PMSET(4, i18n("Cards Interpretations"), Interpretation);
    EditParams();
}

void AstroTarotSpreads::EditParams()
{
    Spreads s;
    if (s.exec() == QDialog::Accepted)
        switch (s.Id())
        {
        case 0:
            Ts = Cross_Shaped;
            break;
        case 1:
            Ts = Horse_Shoe;
            break;
        case 2:
            Ts = Pyramid;
            break;
        case 3:
            Ts = Wheel;
            break;
        case 4:
            Ts = Celtic;
            break;
        default:
            return;
        }
}

AstroTarotSpreads::~AstroTarotSpreads()
{
    for (int i = 0; i < MAXLEVELS; i++)
        for (int j = 0; j < NbCards[Ts]; j++)
            delete Ac[i][j];
    Asr->SetTarotsPixmaps(false);
    Asr->LoadInterTarots(false);
}

bool AstroTarotSpreads::Redisplay()
{
    AstroString as;
    int w, h, w1 = Ag->GetWidth();
    float size = float(Ag->GetSize() * (Asr->CardZoomFactor * 50) / 100) / Asr->Width;
    W = H = 0;
    Ag->FontSize(AstroGraphics::Tiny);
    CardWidth = int(Asr->TarotsPixmaps[0]->width() * size);
    CardHeight= int(Asr->TarotsPixmaps[0]->height() * size);
    for (int i = 0; i < MAXLEVELS; i++)
        for (int j = 0; j < NbCards[Ts]; j++)
            delete Ac[i][j];
    switch (Ts)
    {
    case Cross_Shaped:
        Spread_Cross_Shaped();
        break;
    case Horse_Shoe:
        Spread_Horse_Shoe();
        break;
    case Pyramid:
        Spread_Pyramid();
        break;
    case Wheel:
        Spread_Wheel();
        break;
    case Celtic:
        Spread_Celtic();
    };
    for (int i = MAXLEVELS -1 ; i >= 0; i--)
        for (int j = 0; j < NbCards[Ts]; j++)
            Ac[i][j]->Repaint();
    SetWidth(W);
    w = W / 3;
    h = H;
    Init(false, H);
    NewLine();
    if (Cbp->DispTarotTable)
    {
        NewLine();
        SetTextStyle(Title);
        Text(i18n("Main Spread"), w);
        Text(i18n("Level 1"), w);
        Text(i18n("Level 2"), w);
        NewLine();
        SetTextStyle(PlainText);
        NewLine();
        for (int j = 0; j < NbCards[Ts]; j++)
        {
            for (int i = 0; i < MAXLEVELS; i++)
            {
                const struct CardInfo& ci = Ci[i][j];
                if (ci.Ap)
                    switch (ci.Tt)
                    {
                    case Major:
                        Text(Sprintf("%d) %a", &as, j + 1, Asr->MajTarots[ci.Nb - 1]), w);
                        break;
                    case Swords:
                        Text(Sprintf(i18n("%a of Swords"), &as, Asr->MinTarots[ci.Nb - 1]), w);
                        break;
                    case Coins:
                        Text(Sprintf(i18n("%a of Coins"), &as, Asr->MinTarots[ci.Nb - 1]), w);
                        break;
                    case Sticks:
                        Text(Sprintf(i18n("%a of Sticks"), &as, Asr->MinTarots[ci.Nb - 1]), w);
                        break;
                    default:
                        Text(Sprintf(i18n("%a of Cups"), &as, Asr->MinTarots[ci.Nb - 1]), w);
                    }
                else
                    Text(" ", w);
            }
            NewLine();
        }
        NewLine();
    }
    if (Cbp->DisplayComment)
        DrawComment(*First);
    if (Cbp->Interpretation)
    {
        NewLine();
        SetTextStyle(Title);
        Text(i18n("Interpretation"), w);
        NewLine();
        SetTextStyle(PlainText);
        for (int j = 0; j < NbCards[Ts]; j++)
        {
            for (int i = 0; i < MAXLEVELS; i++)
            {
                const struct CardInfo& ci = Ci[i][j];
                if (ci.Ap)
                    switch (ci.Tt)
                    {
                    case Major:
                        as = *Asr->MajTarots[ci.Nb - 1] + AstroString(": ");
                        DrawMultiLineText(as + (Asr->InterTarots[ci.Nb - 1] ? *Asr->InterTarots[ci.Nb - 1] : ""));
                        NewLine();
                        break;
                    case Swords:
                        as = Sprintf(i18n("%a of Swords"), &as, Asr->MinTarots[ci.Nb - 1]) + AstroString(": ");
                        DrawMultiLineText(as + (Asr->InterTarots[21 + 28 + ci.Nb] ? *Asr->InterTarots[21 + 28 + ci.Nb] : ""));
                        NewLine();
                        break;
                    case Coins:
                        as = Sprintf(i18n("%a of Coins"), &as, Asr->MinTarots[ci.Nb - 1]) + AstroString(": ");
                        DrawMultiLineText(as + (Asr->InterTarots[21 + 42 + ci.Nb] ? *Asr->InterTarots[21 + 42 + ci.Nb] : ""));
                        NewLine();
                        break;
                    case Sticks:
                        as = Sprintf(i18n("%a of Sticks"), &as, Asr->MinTarots[ci.Nb - 1]) + AstroString(": ");
                        DrawMultiLineText(as + (Asr->InterTarots[21 + ci.Nb] ? *Asr->InterTarots[21 + ci.Nb] : ""));
                        NewLine();
                        break;
                    case Cups:
                        as = Sprintf(i18n("%a of Cups"), &as, Asr->MinTarots[ci.Nb - 1]) + AstroString(": ");
                        DrawMultiLineText(as + (Asr->InterTarots[21 + 14 + ci.Nb] ? *Asr->InterTarots[21 + 14 + ci.Nb] : ""));
                        NewLine();
                        break;
                    };
//                     default:
//                         Text(Sprintf(
            }
        }
        if (Ag->GetWidth() < w1) SetWidth(w1);
    }
    SetHeight(h + (Cbp->DispTarotTable ? Lh * (5 + NbCards[Ts]) : 0) + GetSizeLines());
    return true;
}

void AstroTarotSpreads::Create(int i, int j, int n, enum Position pos, unsigned char level, bool leftshift, bool lying)
{
    int cw = lying ? CardHeight : CardWidth, ch = lying ? CardWidth : CardHeight;
    int rw = level * cw / 2, rh = level * ch / 2, rf = level * cw * 3 / 4, hf = level * ch * 3 / 4;
    if (lying)
    {
        i *= CardWidth;
        i = i + CardWidth / 2 - CardHeight / 2;
        j *= CardHeight;
        j = j + CardHeight / 2 - CardWidth / 2;
    }
    else
    {
        i *= cw;
        j *= ch;
    }
    if (leftshift)
        i -= cw / 2;
    switch (pos)
    {
    case MainSpread:
        break;
    case Top:
        j -= hf;
        break;
    case LeftTop:
        i -= rw;
        j -= rh;
        break;
    case Left:
        i -= rf;
        break;
    case LeftBottom:
        i -= rw;
        j += rh;
        break;
    case Bottom:
        j += hf;
        break;
    case BottomRight:
        i += rw;
        j += rh;
        break;
    case Right:
        i += rf;
        break;
    case RightTop:
        i += rw;
        j -= rh;
    };
    Ac[level][n] = new AstroCard(this, i, j, n, level, lying);
    // Ci[level][]
    if (i + cw > W) W = i + cw;
    if (j + ch > H) H = j + ch;
}

void AstroTarotSpreads::CreateShot(int i, int j, int n, enum Position pos, bool leftshift, bool lying)
{
    i++;
    j++;
    for (int k = MAXLEVELS -1; k >= 0; k--)
        Create(i, j, n, k ? pos : MainSpread, k, leftshift, lying);
}

void AstroTarotSpreads::Spread_Cross_Shaped()
{
    CreateShot(0, 1, 0, LeftBottom);
    CreateShot(2, 1, 1, RightTop);
    CreateShot(1, 0, 2, LeftTop);
    CreateShot(1, 2, 3, BottomRight);
}

void AstroTarotSpreads::Spread_Horse_Shoe()
{
    CreateShot(1, 0, 0, LeftTop);
    CreateShot(0, 1, 1, Left);
    CreateShot(1, 2, 2, LeftBottom);
    CreateShot(2, 3, 3, Bottom);
    CreateShot(3, 2, 4, BottomRight);
    CreateShot(4, 1, 5, Right);
    CreateShot(3, 0, 6, RightTop);
}

void AstroTarotSpreads::Spread_Pyramid()
{
    CreateShot(2, 0, 0, Top, true);
    CreateShot(1, 1, 1, LeftTop);
    CreateShot(2, 1, 2, RightTop);
    CreateShot(1, 2, 3, Left, true);
    CreateShot(6, 2, 4, RightTop, true);
    CreateShot(3, 2, 5, Right, true);
    CreateShot(0, 3, 6, Bottom);
    CreateShot(1, 3, 7, Bottom);
    CreateShot(2, 3, 8, Bottom);
    CreateShot(3, 3, 9, Bottom);
}

void AstroTarotSpreads::Spread_Wheel()
{
    CreateShot(0, 3, 0, Left);
    CreateShot(1, 4, 1, LeftBottom, true);
    CreateShot(1, 5, 2, LeftBottom);
    CreateShot(2, 6, 3, Bottom, true);
    CreateShot(2, 5, 4, BottomRight);
    CreateShot(3, 4, 5, BottomRight, true);
    CreateShot(3, 3, 6, Right);
    CreateShot(3, 2, 7, RightTop, true);
    CreateShot(2, 1, 8, RightTop);
    CreateShot(2, 0, 9, Top, true);
    CreateShot(1, 1, 10, LeftTop);
    CreateShot(1, 2, 11, LeftTop, true);
}

void AstroTarotSpreads::Spread_Celtic()
{
    CreateShot(2, 2, 0, LeftBottom, false, true);
    CreateShot(2, 2, 1, RightTop);
    CreateShot(2, 0, 2, RightTop);
    CreateShot(4, 2, 3, BottomRight);
    CreateShot(2, 4, 4, BottomRight);
    CreateShot(0, 2, 5, LeftTop);
    CreateShot(6, 6, 6, RightTop);
    CreateShot(6, 4, 7, RightTop);
    CreateShot(6, 2, 8, RightTop);
    CreateShot(6, 0, 9, RightTop);
}

AstroCard* AstroTarotSpreads::GetCard(int x, int y) const
{
    for (int i = MAXLEVELS -1 ; i >= 0; i--)
        for (int j = 0; j < NbCards[Ts]; j++)
            if (Ac[i][j]->IsIn(x, y))
            {
                if (i > 0 && Ac[i - 1][j]->IsIn(x, y)) return Ac[i - 1][j];
                return Ac[i][j];
            }
    return 0;
}

bool AstroTarotSpreads::Save(AstroRequest& arq, Index idx) const
{
    char type;
    arq.Exec("DELETE FROM Spreads WHERE ChartIdx = %d", idx);
    arq.Exec("UPDATE Charts SET ExtraFlags = %d WHERE Idx = %d", Ts, idx);
    for (int i = 0; i < MAXLEVELS; i++)
        for (int j = 0; j < NbCards[Ts]; j++)
            if (Ci[i][j].Ap)
            {
                const CardInfo& ci = Ci[i][j];
                switch (ci.Tt)
                {
                case Major:
                    type = 'M';
                    break;
                case Swords:
                    type = 'W';
                    break;
                case Coins:
                    type = 'C';
                    break;
                case Sticks:
                    type = 'S';
                    break;
                default:
                    type = 'U';
                };
                arq.Exec(
												"INSERT INTO Spreads (ChartIdx, TarotIdx, Pos, Level, Inversed) VALUES(%d, (SELECT Idx FROM Tarots WHERE Type = '%c' AND Number = %d), %d, '%c', %b)",  
												 idx, type, ci.Nb, j + 1, '1' + i, ci.Inversed);
            }
    return true;
}

bool AstroTarotSpreads::Load(AstroRequest& arq, Index idx)
{
    int pos, level, nb;
    bool inversed;
    enum TarotTypes tt;
    if (arq.Exec("SELECT * FROM Spreads JOIN Tarots ON TarotIdx = Tarots.Idx WHERE ChartIdx = %d", idx) && arq.Valid())
        do
        {
            pos = arq.GetInt("Pos", 1);
            level = arq.GetChar("Level", '1') - '1';
            inversed = arq.GetBool("Inversed", false);
            switch (arq.GetChar("Type", 'M'))
            {
            case 'M':
                tt = Major;
                break;
            case 'W':
                tt = Swords;
                break;
            case 'C':
                tt = Coins;
                break;
            case 'S':
                tt = Sticks;
                break;
            default:
                tt = Cups;
            };
            nb = arq.GetInt("Number", 1);
            struct CardInfo& ci = Ci[level][pos - 1];
            ci.Tt = tt;
            ci.Nb = nb;
            ci.Inversed = inversed;
            ci.Ap = GetPixmap(ci);
        }
        while (arq.Next());
    return true;
}

AstroCard::AstroCard(AstroTarotSpreads* ats, int x, int y, int n, unsigned char level, bool lying) : AstroGraphics(ats->Ag, x, y, lying ? ats->CardHeight : ats->CardWidth, lying ? ats->CardWidth : ats->CardHeight)
{
    Ats = ats;
    Level = level;
    Nb = n;
    Ats->Ci[Level][Nb].Lying_Card = lying;
}



AstroPixmap* GetPixmap(const struct CardInfo& ci)
{
    switch (ci.Tt)
    {
    case Major:
        return Asr->TarotsPixmaps[ 0 + ci.Nb - 1];
        break;
    case Swords:
        return Asr->TarotsPixmaps[50 + ci.Nb - 1];
        break;
    case Coins:
        return Asr->TarotsPixmaps[36 + ci.Nb - 1];
        break;
    case Sticks:
        return Asr->TarotsPixmaps[64 + ci.Nb - 1];
        break;
    default:
        return Asr->TarotsPixmaps[22 + ci.Nb - 1];
    }
}

void AstroCard::Repaint()
{
    const struct CardInfo& Ci = Ats->Ci[Level][Nb];
    if (Ci.Ap)
    {
        enum PixPos pp = Ci.Inversed ? Upside_Down : Straight;
        if (Ci.Lying_Card) pp = Lying;
        Move(0, 0);
        DrawPixmap(*Ci.Ap, float(GetSize() * (Asr->CardZoomFactor * 50) / 100) / Asr->Width, pp);
    }
    else if (!Ats->Cbp->Frameless)
    {
        int w, h;
        AstroString as;
        Color(Level == 0 ? COL[3] : *Acl->Grey);
        Move(0, 0);
        Line(GetWidth(), 0);
        Line(GetWidth(), GetHeight());
        Line(0, GetHeight());
        Line(0, 0);
        Sprintf("%d", &as, Nb + 1);
        TextMetrics(as, &w, &h);
        Move(GetWidth() / 2 - w / 2, GetHeight() / 2 + h / 2);
        Text(as);
    }
}

void AstroCard::Put(enum TarotTypes tt, unsigned char nb, bool inversed)
{
    struct CardInfo& Ci = Ats->Ci[Level][Nb];
    if (tt == Major && nb == 23)
    {
        DeleteCard();
        return;
    }
    if (Already(tt, nb))
    {
        AstroMessage(i18n("Sorry, this card has already been used"), false);
        return;
    }
    Ci.Tt = tt;
    Ci.Nb = nb;
    Ci.Inversed = inversed;
    Ci.Ap = GetPixmap(Ci);
}

bool AstroCard::Already(enum TarotTypes tt, unsigned char nb) const
{
    for (int i = 0; i < MAXLEVELS; i++)
        for (int j = 0; j < NbCards[Ats->Ts]; j++)
            if (Ats->Ac[i][j])
            {
                const AstroCard& ac = *Ats->Ac[i][j];
                const struct CardInfo& Ci = Ats->Ci[ac.Level][ac.Nb];
                if (Ci.Ap && Ci.Tt == tt && Ci.Nb == nb) return true;
            }
    return false;
}
