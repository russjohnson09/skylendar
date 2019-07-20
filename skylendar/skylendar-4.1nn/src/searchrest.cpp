#include <QLineEdit>
#include "searchrest.h"
#include "astrorestrictions.h"
#include "astromainwindow.h"

extern AstroMainWindow* Amw;

/*
 *  Constructs a SearchRest which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
SearchRest::SearchRest()
{
    setupUi(this);
#ifdef SHARED
		RestList->headerItem()->setText(1, i18n("Owner"));
		RestList->headerItem()->setText(2, i18n("Access"));
#endif
}

/*
 *  Destroys the object and frees any allocated resources
 */
SearchRest::~SearchRest()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void SearchRest::on_CancelButton_clicked()
{
    emit reject();
}
/*
 * public slot
 */
void SearchRest::Clicked(QTreeWidgetItem* qlvi)
{

}
/*
 * public slot
 */
void SearchRest::on_OkButton_clicked()
{
    auto sri = SC(SearchRestItem*, RestList->topLevelItem(0));
    for (; sri; sri = SC(SearchRestItem*, RestList->itemBelow(sri)))
    {
        if (sri->isSelected() && !Arl->Get(sri->Idx))
        {
            auto ar = new AstroRestrictions;
            ar->DbFetch(sri->Idx);
            Amw->Aiw->AddRestrict(ar);
        }
    }
    emit accept();
}
/*
 * public slot
 */
void SearchRest::on_SearchButton_clicked()
{
    bool b;
		auto as = AstroString(ReqLine->text());
    if (ReqLine->text().isEmpty())
        b = Arq.Exec(
#ifdef SHARED
				"SELECT Uname(uid) AS Own, r AS Acc, Name, Idx FROM Restrictions WHERE (Name LIKE '\\%') AND (substr(Name, 1, 1) <> '#') ORDER BY Name"
#else
				"SELECT Name, Idx FROM Restrictions WHERE (Name LIKE '\\%') AND (substr(Name, 1, 1) <> '#') ORDER BY Name"
#endif
										 );
    else
			b = Arq.Exec(
#ifdef SHARED
			"SELECT Uname(uid) AS Own, r AS Acc, Name, Idx FROM Restrictions WHERE (Name ~* '%a') AND (substr(Name, 1, 1) <> '#')  ORDER BY Name"
#else
			"SELECT Name, Idx FROM Restrictions WHERE (Name ~* '%a') AND (substr(Name, 1, 1) <> '#')  ORDER BY Name"							 
#endif
									 , &as);
    if (!b)
    {
        AstroMessage(i18n("Can't fetch restrictions !"));
        return;
    }
    RestList->clear();
    if (Arq.Valid()) do
            RestList->addTopLevelItem(new SearchRestItem(RestList, Arq.GetInt("Idx"), Arq < "Name"
#ifdef SHARED
						, Arq < "Own", Arq < "Acc"
#endif
						));
        while (Arq.Next());
}

SearchRestItem::SearchRestItem(QTreeWidget* parent, Index idx, const AstroString& name
#ifdef SHARED
		, const AstroString& owner, const AstroString& access													 
#endif
		 ): QTreeWidgetItem (parent)
{
    setText(0, name);
#ifdef SHARED
		setText(1, owner);
		setText(2, access);
#endif
    Idx = idx;
}
