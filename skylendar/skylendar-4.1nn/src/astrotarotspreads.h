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
#ifndef ASTROTAROTSPREADS_H
#define ASTROTAROTSPREADS_H

#include <astrographics.h>

/**
This class displays tarots spreads

@author Christophe Gros
*/

#define MAXCARDS 12
#define MAXLEVELS 3

class AstroCard;
class AstroRequest;

struct CardInfo
{
    enum TarotTypes Tt;
    char Nb;
    bool Inversed, Lying_Card;
    AstroPixmap* Ap;
};

class AstroTarotSpreads : public GraphicChartBase
{

	Q_DECLARE_TR_FUNCTIONS(AstroTarotSpreads)

public:

    friend class AstroCard;

    enum Position { MainSpread, Top, LeftTop, Left, LeftBottom, Bottom, BottomRight, Right, RightTop };

    AstroTarotSpreads(ChartBaseParams*, ObjsVector*);

    ~AstroTarotSpreads();

    bool Redisplay();

    AstroCard* GetCard(int x, int y) const;

    enum TarotSpreads Ts;

    bool Save(AstroRequest& arq, Index idx) const;

    bool Load(AstroRequest& arq, Index idx);

    void EditParams();

private:

    struct CardInfo Ci[MAXLEVELS][MAXCARDS];
    AstroCard* Ac[MAXLEVELS][MAXCARDS];
    int CardWidth, CardHeight;// W, H;
    void Create(int i, int j, int n, AstroTarotSpreads::Position pos = MainSpread, unsigned char level = 0, bool leftshift = false, bool lying = false);
    void CreateShot(int i, int j, int n, AstroTarotSpreads::Position pos = MainSpread, bool leftshift = false, bool lying = false);
    void Text(const AstroString& as, int l) {
        Ag->JustifText(as, AstroGraphics::Left, l);
    }
    void Spread_Cross_Shaped();
    void Spread_Horse_Shoe();
    void Spread_Pyramid();
    void Spread_Wheel();
    void Spread_Celtic();
};

class AstroCard : public AstroGraphics
{

	Q_DECLARE_TR_FUNCTIONS(AstroCard)

public:

    AstroCard(AstroTarotSpreads* ats, int x, int y, int n, unsigned char level, bool lying = false);
    void Put(enum TarotTypes tt, unsigned char nb, bool inversed = false);
    bool Already(enum TarotTypes tt, unsigned char nb) const;
    inline bool IsIn(int x, int y) const {
        return (x > PosX && x < PosX + Width && y > PosY && y < PosY + Height);
    };
    void Repaint();
    inline void DeleteCard() {
        Ats->Ci[Level][Nb].Ap = 0;
    }
private:

    AstroTarotSpreads* Ats;
    //struct CardInfo* Ci;
    unsigned char Level, Nb;
};

AstroPixmap* GetPixmap(const struct CardInfo& ci);
#endif
