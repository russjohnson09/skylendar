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
#ifndef SEARCHCHART_H
#define SEARCHCHART_H

#include <ui_searchchart.h>
#include <QTreeWidget>
#include "astrosql.h"

class AstroPixmap;

/**
@author Christophe Gros
*/
class SearchChart : public QDialog, public Ui_SearchChart
{
    Q_OBJECT

public:
    SearchChart();

    ~SearchChart();

    Index* Idx;
    int Nb;

public slots:

    void on_CancelButton_clicked();
    void Clicked(QTreeWidgetItem*, int);
    void on_OkButton_clicked();
		void on_Destroy_clicked();
    void on_SearchButton_clicked();

private:

    AstroRequest Arq;
};

class SearchChartItem: public QTreeWidgetItem
{
public:

    SearchChartItem(QTreeWidget* parent, Index idx, const AstroString& name, const AstroString& date, const AstroPixmap& px);
    Index Idx;
};

#endif
