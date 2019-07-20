#include "validskif.h"
#ifndef SHARED
#include "editcountry.h"
#endif
#include "astroutils.h"
#include "astrostring.h"
#include "astrosql.h"
#include <QComboBox>
#include <QLabel>

/*
 *  Constructs a ValidSKIF which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ValidSKIF::ValidSKIF(AstroString& charttype, const AstroString& place, AstroString& country, const AstroString& name)
{
    AstroString as;
    AstroRequest arq;
    setupUi(this);
    emit Name->setText(name);
    ChartTypePtr = &charttype;
    CountryPtr = &country;
    if (!arq.Exec("SELECT Name FROM TypeIcons ORDER BY Idx") || !arq.Valid())
    {
        AstroMessage(i18n("Can't access the database !"));
        return;
    }
    do
    {
        ChartTypeBox->addItem(arq < "Name");
    }
    while (arq.Next());
    if (charttype != "")
    {
        emit ChartType->setEnabled(true);
        emit ChartTypeText->setText(Sprintf(i18n("'%a' is unknown.\n Select a Chart Type from the list"),
                                            &as, &charttype));
    }
    if (country != "")
    {
        emit Country->setEnabled(true);
        emit CountryText->setText(Sprintf(i18n("'%a' is unknown.\nEdit or select a country"), &as, &country));
    }
    if (place != "")
    {
        emit Place->setEnabled(true);
        emit PlaceText->setText(Sprintf(i18n("'%a' is unknown.\n You will have to change it at the next step !"), &as, &place));
    }
}

/*
 *  Destroys the object and frees any allocated resources
 */
ValidSKIF::~ValidSKIF()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
#ifndef SHARED
void ValidSKIF::on_CountryButton_clicked()
{
    EditCountry ec(CountryPtr);
    if (ec.exec())
        *CountryPtr = ec.SavedName;
}
#endif
/*
 * public slot
 */
void ValidSKIF::on_Next_clicked()
{
    if (*ChartTypePtr != "")
        *ChartTypePtr = AstroString(ChartTypeBox->currentText());
    accept();
}


