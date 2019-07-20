/***************************************************************************
 *   Copyright (C) 2006 by Christophe Gros                                 *
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

#ifndef ASTROSPINBOX_H
#define ASTROSPINBOX_H

#include <QSpinBox>
//Added by qt3to4:
#include <QFocusEvent>

class AstroSpinBox : public QSpinBox
{
    Q_OBJECT

public:

    AstroSpinBox( QWidget * parent = 0) : QSpinBox ( parent ) {}

    //signals:

    //void valueChanged(int);

private:

    inline void focusOutEvent ( QFocusEvent *) {
        emit valueChanged(value());
    }

};

#endif
