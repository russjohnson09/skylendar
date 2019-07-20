/***************************************************************************
                          astroapp.h  -  description
                             -------------------
    begin                : Wed Oct 18 2000
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

#ifndef ASTROAPP_H
#define ASTROAPP_H

#include "astrodefs.h"
#include "../config.h"
#ifdef QT
#include <QObject>
#include <QStringList>
#include <QtCore>
#endif
class AstroGraphicChart;
class AstroSplash;

/**This class is the basic kastrolog application class.
It initializes all the global variables
  *@author Christophe Gros
  */

class AstroApp
{

	Q_DECLARE_TR_FUNCTIONS(AstroApp)

public:

    AstroApp(int argc, char *argv[]);
    ~AstroApp();

		void ProcessArgs();

private:

		QStringList Skif;
		QString Dataset, Restrictionset;
		bool D;
    AstroGraphicChart *ac;
};

/** Closes all the skyservces when sk crashes */
void CloseServices();

/** Run before login dialog box */
bool PreLogin();

/** Run after login */
bool PostLogin(AstroApp* ap, QString dbname, QString username, QString password, QString hostname);

#endif
