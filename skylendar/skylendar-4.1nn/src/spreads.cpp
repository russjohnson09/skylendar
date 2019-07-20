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
#include "spreads.h"
#include <QButtonGroup>

Spreads::Spreads()
{
    setupUi(this);
    Qbg = new QButtonGroup(this);
    Qbg->addButton(Cross_Shaped);
    Qbg->addButton(Horse_Shoe);
    Qbg->addButton(Pyramid);
    Qbg->addButton(Wheel);
    Qbg->addButton(Celtic);
    emit Cross_Shaped->setChecked(true);
}


Spreads::~Spreads()
{
}

int Spreads::Id() const
{
    return -Qbg->checkedId() - 2;
}


