/***************************************************************************
                          astrographics.h  -  description
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

#ifndef ASTROGRAPHICS_H
#define ASTROGRAPHICS_H

#include "../config.h"
#include "astrodefs.h"
#include "astrosigns.h"
#include "astrochartbase.h"

#ifdef QT
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QPixmap>
#include <QPen>
class QFont;
class QRegExp;
#endif

#define MAXLINES 200

class GraphicChartBase;

/** A portable pixmap class */
class AstroPixmap
#ifdef QT
            : public QPixmap
#endif
{
public:

    /** Constructor */
    inline AstroPixmap() {}

    /** Constructor */

    AstroPixmap(const AstroString& file, const AstroString& path= Asr->IconsPath);

    /** Constructor */
    inline AstroPixmap(int w, int h)
#ifdef QT
            :
            QPixmap(w, h) {}
    inline AstroPixmap(const QPixmap& qp) : QPixmap(qp) {}
#endif

    /** Sets the pixmap with the file c */
    inline void SetPixmap(const char* c)
    {
#ifdef QT
        load(c);
#endif
    }
};

/** This class implements a standard color management */
class AstroColor
#ifdef QT
            : public QColor
#endif
{
public:

	inline AstroColor(){}
    inline AstroColor(int r, int g, int b)
# ifdef QT
            :
            QColor(r, g, b)
# endif
    {}

    inline AstroColor(const char *name)
# ifdef QT
            :
            QColor(name)
# endif
    {}
    inline void SetRgb(int r, int g, int b)
    {
# ifdef QT
        setRgb(r, g, b);
#endif
    }
    AstroColor GetLighter() const;
};

/** This class implements the standard 16 colors palette for all the drawings */
class AstroColorList
{
public:

    AstroColorList();
    AstroColorList(unsigned const char*);
    ~AstroColorList();

    inline const AstroColor& operator[](int i) const {
        return Ac[i];
    }

    void SetColor(AstroColor& ac, int i);

    void SetColor(unsigned char red, unsigned char green, unsigned char blue, int i);

    // The foreground and background, medium grey black and white AstroColor pointers
    AstroColor *Fore, *Back, *Grey, *Black, *White;

    const AstroPixmap& operator % (int i) const {
        return *ColorPixmaps[i];
    }

private:

    AstroColor Ac[16];
    AstroPixmap *ColorPixmaps[16];
};


/** This class implements the management of a standard graphic field, with basic graphic primitives, such as lines. circles, etc..
*/

class AstroGraphics
{

	//Q_DECLARE_TR_FUNCTIONS(AstroGraphics)

public:

    friend class GraphicChartBase;
    friend class GraphicListBase;
    friend class AstroSpot;

    enum SizeChars { Very_Tiny, Tiny, Medium, Large, Huge };
    enum Justif    { Left, Right, Center, Dot };
    enum PixPos    { Straight, Lying, Upside_Down };

    /** Constructor */
    AstroGraphics(AstroGraphics* parent = 0, int x = 0, int y = 0, int w = 200, int h = 200);

    /** Destructor */
    virtual ~AstroGraphics() {}

    /** Moves the cursor to x, y */
    void Move(int x, int y);

    /** Moves relatively to x, y */
    inline void RMove(int x, int y = 0) {
        Move(x + Xi - PosX, y + Yi - PosY);
    }

    /** Draws a line up to x, y */
    void Line(int x, int y);

    /** Draws a relative line */
    inline void RLine(int x, int y) {
        Line(x + Xi - PosX, y + Yi - PosY);
    }

    /** Draws a little dot */
    void DrawDot();

    /** Draws a rectangle of w width and h height */
    void DrawRect(int w, int h);

    /** Draw a circle.
     @param x,y circle center
     @param r radius
     @param filled if true, circle is filled with the current color
     */
    void Circle(int x, int y, int r, bool filled = false);

    /** Sets current color */
    void Color(const AstroColor&);

    /** Draws a pixmap
    	@param zoom the zooming factor. 1.0 = no zoom
    	@param upside_down if true vertically mirrored */
    void DrawPixmap(const AstroPixmap& pm, float zoom = 1.0, enum PixPos pp = Straight);

    /** Foreground color */
    inline void Fore() {
        Color(Cpr->InvBack ? *Acl->Back : *Acl->Fore);
    }

    /** Background color */
    inline void Back() {
        Color(Cpr->InvBack ? *Acl->Fore : *Acl->Back);
    }

    /** Medium grey color */
    inline void Grey() {
        Color(*Acl->Grey);
    }

    /** Sets the background Color */
    void Background(const AstroColor&);

    /** Gives the dash degree of a line. 0 = solid, 4 = fully dotted */
    void Dash(int d);

    /** Sets the line width */
    void SetLineWidth(int w);

    /** Sets the relative size of the text or astro font. This size is relative to
        the actual display size */
    void FontSize(enum SizeChars, bool isastro = false);

    enum SizeChars GetSc(bool isastro = false) const {
        return isastro ? ScA : ScT;
    }

    /** Draws a line of unicode string */
    void Text(const AstroString& as, bool movex = false);

    /** Draws a text with a given angle */
    void TextAngle(AstroString& a, float angle);

    /** Draws a justified line of text
     @param as the justified string to print
     @param justif Left, Right, Center or Dot
     @param len, the length of the string in pixels
     @param l2, the length of the integer part of the number when Dot justif
    */
    void JustifText(const AstroString& as, enum Justif justif, int len, int l2 = 0);

    /** Draws a sign glyph */
    void Sign(enum Signs);

    /** Draws an astrofont glyph */
    void Glyph(char c);

    /** Draws a justified glyph */
    void JustifGlyph(char c, enum Justif justif, int len);

    /** Gives the AstroString metrics, (i.e. its width and height
    If width or height == 0, value not returned */
    void TextMetrics(const AstroString&, int* width = 0, int* height = 0);

    /** Gives the astro glyph metrics, (i.e. its width and height)
    If width or height == 0, value not returned */
    void GlyphMetrics(char c, int* width = 0, int* height = 0);

    /** Draws a degree sign (glyph or name) min string
    @param d The longitude in decimal
    @param name Short name instead of glyph
    @param retro Appends a R if retro
    @param seconds if seconds are displayed
    */
    void DegSignMin(double d, bool name = false, bool retro = false, bool seconds = false);

    /** Draws a hh:mm:ss hour:minute:second string */
    void Hms(double d, const AstroString& sep, bool second = false);

    /** Draw the ring number */
    void DrawRing(int ring);

    /** Returns drawing field width */
    virtual inline int GetWidth()  const {
        return Width;
    }

    /** Returns drwing field height */
    virtual inline int GetHeight() const {
        return Height;
    }

    /** Returns the Size factor */
    inline int GetSize() const {
        return Size;
    }

    /** Returns the horizontal cursor position */
    inline int GetX() const {
        return Xi - PosX;
    }

    /** Returns the vertical cursor position */
    inline int GetY() const {
        return Yi - PosY;
    }

protected:

    AstroGraphics* Base;
    ChartParams* Cpr;

#ifdef QT
    QPainter *Qp;
    QPen *Pen;
    QFont *astro, *text;
#endif
    int Width, Height, PosX, PosY, Size, Xi, Yi;
    void SetWidth(int i);
    void SetHeight(int i);

private:

    enum SizeChars ScT, ScA;
    char charbuf[2];
};

/** The actual field where all the graphic charts will be drawn  */
class GraphicChartBase : public AstroChartBase
{

	Q_DECLARE_TR_FUNCTIONS(GraphicChartBase)

public:

    friend class AstroMainWindow;

    /** Different paragraph styles */
    enum TextStyle { PlainText, MainTitle, Title, SubTitle, TabText, TabRight, TabDot};

    GraphicChartBase(ChartBaseParams *cbp, ObjsVector* ov, AstroGraphics *ag);

    /** virtual methods which return the drawing space width and height */

    inline void SetWidth(int i) {
        Ag->SetWidth(i);
    }
    inline void SetHeight(int i) {
        Ag->SetHeight(i);
    }
    /* inline int GetWidth()  const { return (Ag && Ag->Base) ? Ag->Base->GetWidth() : 0; } */
    /* inline int GetHeight() const { return (Ag && Ag->Base) ? Ag->Base->GetHeight() : 0; } */

    /** Initializes the text mode drawings
    @param page if true, reduces the display height with margins
    @param y if -1, moves the vertical cursor to YMargin, ans to y otherwise
    */
    void Init(bool page = false, int y = -1);

    /** Draws the info (name, date, hour, houses system, etc...) about AstroObjs a
    @param a the current AstroObjs
    @param i its slot number. If -1, i not displayed
    */
    void DrawInfo(const AstroObjs& a, int i = -1);

    /** Displays the commetn associated with the given AstroObjs as a multiline text
    @return height of the comment, in pixels*/
    void DrawComment(const AstroObjs&);

    /** Sets the style of the coming text */
    void SetTextStyle(enum TextStyle ts);

    /** Draw text */
    void DrawText(const AstroString&);

    /** New line */
    bool NewLine();

    /** Draws a test of several lines */
    void DrawMultiLineText(const AstroString&);

    /** Returns the vertical size of all the drawn lines so far */
    int GetSizeLines() const;

protected:

    int XMargin, YMargin, Lh, W, H, Tab, Lines, CurLine, FirstLine, LastLine;
    bool Ex;
    enum TextStyle Ts;
    AstroGraphics* Ag;
    void DrawParagraph(const AstroString&, const QRegExp&);
    enum AstroGraphics::Justif GetJustif() const;
    void LText(const AstroString& as, bool movex = false);
    inline bool Nl() const
    {
        if (IfPage) return false;
        return CurLine >= LastLine || CurLine < FirstLine;
    }
};

#endif
