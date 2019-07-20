/***************************************************************************
                          astroobjectslist.h  -  description
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

#ifndef ASTROOBJECTSLIST_H
#define ASTROOBJECTSLIST_H

#include <graphiclistbase.h>

/**This class displays a list of ALL the known objects with its glyph, short and long name, etc...
  *@author Christophe Gros
  */

class AstroObjectsList : public GraphicListBase, public DataLineList
{

	Q_DECLARE_TR_FUNCTIONS(AstroObjectsList)

public:

    AstroObjectsList(ChartBaseParams*, ObjsVector*);
    ~AstroObjectsList();
    bool Redisplay();

private:

    int w;
};

#endif
