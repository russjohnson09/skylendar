#include "editcountry.h"
#include "astroutils.h"
#include "astroresources.h"
#include "astrodata.h"
#include "astrochart.h"
#include <QLineEdit>
#include "QFileDialog"
/*
 *  Constructs a EditCountry which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
EditCountry::EditCountry(const AstroString* n)
{
    setupUi(this);
    if (n)
        emit Name->setText(*n);
    Idx = 0;
    connect(CountriesList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(Clicked(QTreeWidgetItem*, int)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditCountry::~EditCountry()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void EditCountry::Clicked(QTreeWidgetItem* qlvi, int i)
{
    const CountryLine* cl = SC(CountryLine*, qlvi);
    if (!cl) return;
    emit Name->setText(cl->text(0));
    emit Code->setText(cl->text(2));
    SavedName = cl->text(0);
    emit ZifName->setText(cl->text(1));
    emit J2g->setText(cl->text(3));
    emit Comment->setText(cl->text(4));
    Idx = cl->Idx;
}
/*
 * public slot
 */
void EditCountry::on_DeleteButton_clicked()
{
    if (Adl->CheckIdx(Idx, true) || Ahl->CheckPlaceIdx(Idx, true))
    {
        AstroMessage(i18n("Can't delete this country"));
        return;
    }
    if (!Arq.Exec("DELETE FROM Country WHERE Idx = %d", Idx))
    {
        AstroMessage(i18n("Can't delete this country"));
        return;
    }
    CountriesList->clear();
    emit Name->setText("");
    emit Code->setText("");
    emit ZifName->setText("");
    emit J2g->setText("");
    emit Comment->setText("");
}

/*
 * public slot
 */
void EditCountry::on_ModifyButton_clicked()
{
    AstroString name = AstroString(Name->text());
    const char *zif = ZifName->text().toUtf8().data();
    if (!Arq.Exec("UPDATE Country SET Name = '%a', TzFile = '%s', Code = '%s', J2g = '%s', Comment = '%s' WHERE Idx = %d", &name, zif, Code->text().data(), J2g->text().data(), Comment->text().data(), Idx))
    {
        AstroMessage(i18n("Can't modify this country"));
        return;
    }
    auto cl = SC(CountryLine*, CountriesList->currentItem());
    if (!cl) return;
    cl->setText(0, Name->text());
    cl->setText(1, ZifName->text());
    cl->setText(2, Code->text());
    cl->setText(3, J2g->text());
    cl->setText(4, Comment->text());
    Ahl->UpdateZif(Idx, zif);
}

/*
 * public slot
 */
void EditCountry::on_NewButton_clicked()
{
    Index idx;
    AstroString name = AstroString(Name->text());
    if (Name->text().isEmpty() || ZifName->text().isEmpty())
    {
        AstroMessage(i18n("Fields Name and  ZifName can't be empty !"));
        return;
    }
    idx = Arq.NextId("Country");
    Arq.Exec("INSERT INTO Country (Idx, Name, TzFile, Code, J2g) VALUES (%d, '%a', '%s', '%s', '%s', '%s')", idx, &name, ZifName->text().data(), Code->text().data(), J2g->text().data(), Comment->text().data());
    CountriesList->clear();
    CountriesList->addTopLevelItem(new CountryLine(idx, CountriesList, Name->text(), ZifName->text(), Code->text().toUtf8().data(), J2g->text(), Comment->text()));
    Idx = idx;
}
/*
 * public slot
 */
void EditCountry::on_OkButton_clicked()
{
    emit accept();
}
/*
 * public slot
 */
void EditCountry::on_SearchButton_clicked()
{
    CountriesList->clear();
    if (Name->text().isEmpty())
        Arq.Exec("SELECT Name, TzFile, Code, CAST(J2g AS VARCHAR) AS CJ2g, Comment, Idx FROM Country WHERE Name LIKE '\\%' ORDER BY Name");
    else
        Arq.Exec("SELECT Name, TzFile, Code, CAST(J2g AS VARCHAR) AS CJ2g, Comment, Idx FROM Country WHERE Name ~* '%s' ORDER BY Name", Name->text().toUtf8().data());
    if (Arq.Valid()) do
            CountriesList->addTopLevelItem(new CountryLine(Arq.GetInt("Idx"), CountriesList, Arq < "Name" , Arq < "TzFile", (Arq < "Code").toUtf8().data(), Arq < "CJ2g", Arq < "Comment"));
        while (Arq.Next());
    CountriesList->resizeColumnToContents(0);
}
/*
 * public slot
 */
void EditCountry::on_FileListButton_clicked()
{
    QString path(Asr->ZPath), res;
    res = QFileDialog::getOpenFileName(nullptr, i18n("Zone info dir"), path);
    res.remove(0, path.length());
    if (!res.isEmpty())
        emit ZifName->setText(res);
}

