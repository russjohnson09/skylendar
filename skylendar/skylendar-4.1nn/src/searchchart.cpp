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
#include "searchchart.h"
#include <QLineEdit>
#include <QCheckBox>
#include "astroutils.h"
#include "astrographics.h"

SearchChart::SearchChart()
{
    setupUi(this);
    ChartList->setIndentation(0);
    Idx = 0;
    Nb = 0;
}


SearchChart::~SearchChart()
{
    delete Idx;
}

void SearchChart::on_CancelButton_clicked()
{
    emit reject();
}

void SearchChart::Clicked(QTreeWidgetItem*, int)
{
}

void SearchChart::on_OkButton_clicked()
{
    int i;
    auto sri = SC(SearchChartItem*, ChartList->topLevelItem(0));
    for (; sri; sri = SC(SearchChartItem*, ChartList->itemBelow(sri)))
        if (sri->isSelected())
            Nb++;
    Idx = new Index[Nb];
    for (i = 0, sri = SC(SearchChartItem*, ChartList->topLevelItem(0)); sri; sri = SC(SearchChartItem*, ChartList->itemBelow(sri)))
        if (sri->isSelected())
            Idx[i++] = sri->Idx;
    emit accept();
}

void SearchChart::on_Destroy_clicked()
{
	bool b = false;
	auto sri = SC(SearchChartItem*, ChartList->topLevelItem(0));
	if (AstroQuestion(i18n("Do you want to destroy the selected charts ?")))
  {
		for (sri = SC(SearchChartItem*, ChartList->topLevelItem(0)); sri; sri = SC(SearchChartItem*, ChartList->itemBelow(sri)))
			if (sri->isSelected())
			{
				Arq.Exec("DELETE FROM Charts WHERE Idx = %d", sri->Idx);
				b = true;
			}
		if(b) on_SearchButton_clicked();
	}
}

void SearchChart::on_SearchButton_clicked()
{
    bool b;
    if (ReqLine->text().isEmpty())
        b = Arq.Exec(
										 "SELECT Name, Idx, to_char(Date, 'DD-Mon-YYYY') AS CDate, Type FROM Charts WHERE Name LIKE '\\%' ORDER BY Name"
										 );
    else
        b = SQLStatement->isChecked() ? Arq.Exec(

 "SELECT DISTINCT Charts.Name, Charts.Idx, to_char(Charts.Date, 'DD-Mon-YYYY') AS CDate, Charts.Type FROM Charts JOIN Ring ON Charts.Idx = Ring.ChartIdx JOIN Data ON Ring.DataIdx = Data.Idx JOIN Restrictions ON Ring.RestrIdx = Restrictions.Idx WHERE %s ORDER BY Name", ReqLine->text().toUtf8().data()) : Arq.Exec("SELECT Name, Idx, to_char(Date, 'DD-Mon-YYYY') AS CDate, Type FROM Charts WHERE Name ~* '%s' ORDER BY Name"
	, ReqLine->text().toUtf8().data());
    if (!b)
    {
        AstroMessage(i18n("Can't fetch charts !"));
        return;
    }
    ChartList->clear();
    if (Arq.Valid()) do
        {
            enum ChartType ct;
            switch (Arq.GetChar("Type", 'W'))
            {
            case 'W':
                ct = StdWheels;
                break;
            case 'L':
                ct = GraphicList;
                break;
            case 'H':
                ct = LocalHorizon;
                break;
            case 'A':
                ct = AspectsArray;
                break;
            case 'G':
                ct = Astro_Graph;
                break;
            case 'S':
                ct = Squared;
                break;
            case 'Y':
                ct = SolarSys;
                break;
            case 'T':
                ct = Tarots_Spreads;
                break;
            default:
                ct = StdWheels;
            };
            (void)new SearchChartItem(ChartList, Arq.GetInt("Idx"), Arq < "Name", Arq < "CDate", *Asr->TypePixmaps[ct - 1]
																			);
        }
        while (Arq.Next());
    ChartList->resizeColumnToContents(0);
}

SearchChartItem::SearchChartItem(QTreeWidget* parent, Index idx, const AstroString& name, const AstroString& date, const AstroPixmap& px
#ifdef SHARED
																 , const AstroString& owner, const AstroString& access
#endif
																 ) : QTreeWidgetItem (parent)
{
    setText(0, name);
    setText(1, date);
    Idx = idx;
    setIcon(0, px);
#ifdef SHARED
		setText(2, owner);
		setText(3, access);
#endif
}


