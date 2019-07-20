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

#include "astrosplash.h"
#include "astroapp.h"
#include "astroapp.h"
#include "astroresources.h"
#include "astrointerface.h"
#include "astromainwindow.h"
#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QDesktopWidget>
#include <QProgressBar>

AstroSplash::AstroSplash(AstroApp* ap)
{
    Ap = ap;
    setupUi(this);
		Sky->setPixmap(Asr->IconsPath + "skylendar.jpg");
    emit DbName->setText(Asr->DbName);
    emit HostName->setText(Asr->DbHost);
    emit UserName->setText(Asr->DbUser);
    emit Status->setValue(10);
    emit move((qApp->desktop()->width() - width()) / 2, (qApp->desktop()->height() - height()) / 2);
    show();
}

void AstroSplash::on_CancelButton_clicked()
{
    qApp->exit(0);
}

void AstroSplash::on_OkButton_clicked()
{
    if (!PostLogin(Ap, DbName->text(), UserName->text(), Password->text(), HostName->text())) exit(1);
		deleteLater();
		//QCoreApplication::postEvent(Amw, new AstroEvent(1235, nullptr));
}

void AstroSplash::Progress(int i)
{
    Status->setValue(i);
}
