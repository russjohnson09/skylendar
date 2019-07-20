/***************************************************************************
                          astrorings.h  -  description
                             -------------------
    begin                : Sat Dec 30 2000
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

#ifndef ASTRORINGS_H
#define ASTRORINGS_H

#include "../config.h"
#include "astrographics.h"
#include "astrolist.h"

class AstroChartBase;
class ChartParams;
class AstroObjs;
class AstroFoundAspectsList;

/** This class implements a classical wheel chart with signs ring,
    houses ring, 360 degrees ring, planets display, aspects, etc...
*/
class AstroRings : public AstroGraphics
{

	Q_DECLARE_TR_FUNCTIONS(AstroRings)

public:

    /** Builds an AstroRing
    @param parent The parent AstroGraphics
    @param x the x position
    @param y the y position
    @param size The ring diameter
    @param cp The ChartParams pointer
    @param acb The AstroChartBase pointer */
    AstroRings(AstroGraphics* parent, int x, int y, int size, ChartParams* cp, AstroChartBase* acb, AstroFoundAspectsList& afal, AstroObjs* first, AstroObjs* second);

    /** Destructor */
    ~AstroRings() {
        delete Sv;
    }

    /** The grand display method */
    virtual void Repaint();

    /** Displays ith ring info on wanted corner of the ring chart*/
    void CornerInfo(const AstroObjs& a, int i);

    /** Draws the crown of signs */
    void RingSigns();

    /** Draws a crown of 360 small lines showing the zodiac degrees */
    void DegreesRing();

    /** Draws a ring of Gauquelin's sectors */
    void GauquelinRing(bool hp = false);

    /** Draws a crown of 12 cuspides + corresponding houses numbers
     @param a The AstroObjs where the data is taken from */
    void HousesRing(const AstroObjs& a);

    /** Draws all the objects rings */
    void ObjectsRings();

    /** Draws the subring */
    void SubRing(const AstroObjs& a);

    /** Draws the Ascendant and MidHeaven lines */
    void AscMidH(const AstroObjs&);

    /** Draws the aspects lines within the remaining central disk */
    void Aspects(AstroObjs* ao);

    /** The angle between 0 Aries and leftmost point */
    double Angle0;

    /** An initialisation routine called at the beginning of the @ref Repaint method */
    void Init();

    /** Gets the angle in degrees corresponding to x, y */
    double GetAngle(int x, int y) const;


    int OutlRings[NBDATA], RingX, RingY;


    struct Slot; // Forward declaration

protected:

    /** The 4 corners of the ring. */
    enum Corner { Top_Left, Top_Right, Bottom_Left, Bottom_Right };

    /** Draws up to 3 lines of text in the corners of the ring */
    void CornerText(const AstroString& as, int line, enum Corner corner);

    /** Draws AstroPixmaps in the corners of the ring */
    void CornerPixmap(const AstroPixmap& ap, enum Corner corner);

    /** Selects the size class of a chart (i.e. the character size, number of slot, maximum number of objects on a ring, etc... )
        @param i the total number of objects displayed on a chart */
    void SelectSizeClass(int i);

    /** Draws a ring with objects form first to last, and corresponding dashed lines of length dlinelen.
    @param dlinelen length of dashed line connecting the object indicator line to the final dot.
    */
    void PutRing(const AstroObjs&, int dlinelen, int ring);

    /** Puts an object glyph on the ring.
    @param Slot The slot where the object should be placed
    @param angle, The object angle
    @param rs Radius of the glyph
    @param lrs radius of the crown which contains the object indicator
    @param lrs2 radius of the crown containing the dashed line connecting the object indicator to the final dot (if any)
    */
    void PutObj(const AstroObjs&, const struct Slot *slot, double angle, double rs, double lrs, double lrs2);

    void Cuspide(double angle, int i, int i1);

private:

    struct Slot
    {
        bool IfSlot, Inc;
        enum Objs O;
        double Angle;
    } *Sv;

    AstroList<Slot> Sl;

    void PushBack(int i);
    void PushForw(int i);
    void Insert(enum Objs, double);

    AstroChartBase* Acb;
    ChartParams* Cp;
    AstroFoundAspectsList* Afal;
    int Size, RingRadius, NbRings, Scindex, Thickness, Halfthick, Rx, Ry, NbSlots, MaxNbObj, Size0, Height0;
    AstroObjs *First, *Second;
    struct {
        AstroObjs* a;
        int f, l;
    } Pos[NBDATA];
    bool Narrow, Gau;
    AstroGraphics::SizeChars Sc;
};

/** This class is a base class for the text based frames */
class AstroTextFrame : public AstroGraphics
{
public:

    /** Constructor */
    AstroTextFrame(AstroGraphics* parent, int x, int y, int w, int h, ChartParams* cp, AstroChartBase* acb);

    /** Pushes the cursor to a new line */
    void NewLine();

    /** Draws a line of text
        @param newline if true, pushes the cursor on a new line */
    void TextLine(const AstroString, bool newline = true);

protected:

    void Init();
    inline virtual int NbLines() const {
        return 0;
    }
    int CharHeight, XCurs, YCurs, MaxNbLines, LineWidth, Size0, OrigWidth, NbWidth;
    AstroChartBase* Acb;
    ChartParams* Cp;
};

/** This class implements a side bar with rows of colored text + multi-columns */
class AstroSideBar : public AstroTextFrame
{

	Q_DECLARE_TR_FUNCTIONS(AstroSideBar)

public:

    /** Constructor */
    AstroSideBar(AstroGraphics* parent, int x, int y, int w, int h, ChartParams* cp, AstroChartBase* acb, AstroObjs* ao);

    /** overloaded method. Gives the width according to the number of text columns */
    int GetWidth() const;

    /** Standard header � la kastrolog 5.4 with name, date, place, type of domification, etc...
        @param i the ith chart index
    */
    void StdHeader(int i);

    /** Displays a line of text containing the zodiacal position of the "house"th house.
        @param house the house number.*/
    void HouseLine(int house);

    /** Displays a line of text containing the symbol of the ith object, its zodiacal position and elevation
        @param i the object index */
    void ObjLine(int i);

    /** Computes the fire/air/water/earth scores indexes and displays 2 lines of text containg the resulting values and the corresponding labels.*/
    void Fawe();

    /** Computes the Cardinal/Fixed/Mutable scores indexes and displays 1 line of text containg the resulting values and the corresponding labels.*/
    void Cfm();

    /** Computes the Angular/Succeedent/Cadent scores indexes and displays 1 line of text containg the resulting values and the corresponding labels.*/
    void Asc();

    /** Displays the planets ranking lines */
    void RankLines();

    /** The grand repaint method */
    void Repaint();


protected:

    void DrawLabelNb(const AstroString& label, int size, int nb);

private:

    int NbLines() const;
    AstroObjs* Ao;
    bool Gauq;
    int W;
};

/** This class implements an aspects list frame */
class AstroAspectsFrame : public AstroTextFrame
{
public:

    AstroAspectsFrame(AstroGraphics* parent, int x, int y, int w, int h, ChartParams* cp, AstroChartBase* acb, AstroFoundAspectsList* afal, AstroObjs* first, AstroObjs* second);

    /** overloaded method. Gives the width according to the number of text columns */
    int GetHeight() const;

    /** The grand repaint method */
    void Repaint();

private:

    void DrawAspectFound(const AspectFound&, const AstroAspects& aa);
    AstroFoundAspectsList* Afal;
    AstroObjs* First, *Second;
};

#endif















