/***************************************************************************
 *   Copyright (C) 2007 by Christophe Gros                                 *
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
#include "editdirections.h"
#include "astrodirections.h"
#include <QSpinBox>
#include <QRadioButton>

EditDirections::EditDirections(AstroDirections* ad)
{
    int i;
    setupUi(this);
    Ad = ad;
    switch (Ad->Hs)
    {
    case Regiomontanus:
        i = 0;
        break;
    case Placidus:
        i = 1;
        break;
    case Campanus:
        i = 2;
        break;
    default:
        i = -1;
    };
    emit House->setCurrentIndex(i);
    emit DirType->setCurrentIndex((Ad->Dt == Mundane) ? 0 : 1);
    switch (Ad->Sk)
    {
    case Ptolemy:
        i = 0;
        break;
    case Naibod:
        i = 1;
        break;
    case Simmonite:
        i = 2;
        break;
    case Placidian:
        i = 3;
        break;
    case Cardan:
        i = 4;
        break;
    case Synodic:
        i = 5;
        break;
    case Custom:
        i = 6;
        break;
    default :
        i = -1;
    };
    emit StatKey->setCurrentIndex(i);
    emit Converse->setChecked(Ad->Converse);
    emit Dump->setChecked(Ad->Dump);
}


EditDirections::~EditDirections()
{
}

void EditDirections::on_StatKey_activated(int i)
{
    emit CustVal->setEnabled(i == 6);
}


