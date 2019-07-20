/***************************************************************************
                          graphiclistbase.h  -  description
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

#ifndef GRAPHICLISTBASE_H
#define GRAPHICLISTBASE_H

#include "astrographics.h"
#include "astrochartbase.h"
#include "astrotransfer.h"

//#define MAXY 65355

/**This class implements what is necessary for
the tabulated lists of values, arrays etc...
  *@author Christophe Gros
  */

class GraphicListBase : public GraphicChartBase
{

public:

    /** Constructor */
    GraphicListBase(DataLineList* dll, ChartBaseParams*, ObjsVector*);

    /** Destructor */
    ~GraphicListBase();

    /** Returns true if last line of list displayed */
    inline bool IsEnd() const {
        return End;
    }

protected:

    /** Initializes some variables before drawing text */
    void Init();

    /** Draw tabbed text, i.e. The cursor is moved to the next tab stop */
    void DrawTabText(const AstroString&);

    /** Draws a tabbed centered glyph
    @param c the glyph char
    */
    void DrawTabGlyph(char c);

    /** Draws a Degree/Sign/Minute planetary position
    @param val the zodiacal position
    @param retro if retro */
    void DrawDegSignMin(double val, bool retro = false);

    /** Sets the tab position list
    @param t a pointer to an array of int containing positives values for the tab */
    void SetTabList(const int *t, bool centered = false);

    /** Displays a double number
    @param as the buffer, also returned by Dbl
    @param d the double number itself
    @param four if true, four digits, else only two
    @param sci if true scientific notation
    @return buffer with the ASCII value of d
    */
    const AstroString& Dbl(AstroString& as, double d, bool four = false, bool sci = false);
    //int W, H;

    /** Returns the current clickable position */
    int Pos() const;

    /** Draws a little dot as a button */
    void DrawButton();

    /* Overloaded methods */
    const DataLineBase* GetCoord(int x, int y) const;

    const DataLineBase* GetNext(const DataLineBase* ref, unsigned int i) const;

    bool End;

    void NewLine(bool horline = false);

    DataLineList* Dll;
    int Ow;

private:

    int *TabList, Four0, Seven, Zero, Offs = 0, RightMost = 0;
};

#endif
