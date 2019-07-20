#include "editplace.h"
#include "astrodata.h"
#include "astrohm.h"
#include "astrowindow.h"
#include "editastrodata.h"
#include "editcountry.h"
#ifdef QT
#include <QString>
#include <QComboBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QValidator>
using namespace KXmlRpc;
#endif

#define LAST 4294967295

class LlValidator: public QValidator
{
public:

	inline LlValidator(enum HM_Mode m) { M = m; }
	State	validate(QString & input, int & pos) const;
	void fixup(QString & input) const;

private:

	enum HM_Mode M;
};

void LlValidator::fixup(QString & input) const
{
	//qDebug() << input;
}

QValidator::State LlValidator::validate(QString & input, int & pos) const
{
	AstroHM hm;
	return hm.Set(AstroString(input), M) ? QValidator::Invalid : QValidator::Acceptable;
	/*if (input != "")
        switch (hm.Set(AstroString(input), M))
        {
        case ASTROHM_WRONG_HOUR:
					r = i18n("Error in latitude hour");
					break;
        case ASTROHM_WRONG_SEPARATOR:
					return QValidator::Invalid;
					r = i18n("Error in hour/minute separator or trailer");
					break;
        case ASTROHM_WRONG_MINUTE:
					r = i18n("Error in latitude minute");
					break;
        case ASTROHM_WRONG_SECOND:
					r = i18n("Error in latitude second");
					break;
        default:;
					r = "";
        };
				return QValidator::Acceptable;*/
}

int EditPlace::SearchIdx(Index idx) const
{
    for (int i = 0; i < Nb; i++)
        if (IdxPtr[i] == idx)
            return i;
    return -1;
}

void EditPlace::UpdateAd(bool b)
{
    AstroHM hm;
    if (b) Ad->DbExtraFetch(Arq, IdxPtr[Id]);
    Ad->PlaceName  = PlaceName->text();
    Ad->PlaceIdx   = Idx;
    Ad->CountryIdx = IdxPtr[Id];
    hm.Set((AstroString)Latitude->text(), HM_Latitude);
    Ad->Latitude   = hm;
    hm.Set((AstroString)Longitude->text(), Ad->HMS_Format ? HM_HMS : HM_Longitude);
    Ad->Longitude  = hm;
    Ad->Altitude   = Altitude->value();
    Ad->Recompute();
    if (Ad->Automatic)
    {
        int d, mo, y, h, m, s;
        Ad->GetDate(&d, &mo, &y, &h, &m, &s);
        Ead->CheckDate(d, mo, y, h, m, s);
        emit OffTzRecomp();
    }
}

void EditPlace::Clicked(QTreeWidgetItem* qlvi, int i)
{
    auto sl = SC(SearchLine *, qlvi);
    if (!sl) return;
    AstroString as;
    emit PlaceName->setText(sl->text(NAME));
    emit Latitude->setText(sl->text(LATITUDE));
    emit Longitude->setText(sl->text(LONGITUDE));
    emit Altitude->setValue(sl->Altitude);
    Id = SearchIdx(sl->CountryIdx);
    emit Country->setCurrentIndex(Id);
    Idx = sl->Idx;
    UpdateAd(true);
    Modified = false;
}

void EditPlace::Init(EditAstroData* ead, AstroData* ad, const AstroString* n)
{
    AstroString as;
    Index idx;
    Ad = ad;
    Ead = ead;
    Idx = Ad->PlaceIdx;
    emit PlaceName->setText(n ? *n : Ad->PlaceName);
    Ad->Latitude.Get(as, HM_Latitude, false, Ad->To_Second);
    emit Latitude->setText(as);
		lat = new LlValidator(HM_Latitude);
		lon = new LlValidator(HM_Longitude);
		Latitude->setValidator(lat);
    Ad->Longitude.Get(as, HM_Longitude, false, Ad->To_Second);
    emit Longitude->setText(as);
		Longitude->setValidator(lon);
    emit Altitude->setValue(Ad->Altitude);
    //SearchList->headerItem()->setText(MODIFIABLE, i18n("Shared"));
    connect(SearchList, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(Clicked(QTreeWidgetItem*, int)));
    connect(PlaceName, SIGNAL(textChanged(const QString&)), this, SLOT(on_PlaceName_textChanged(const QString&)));
    if (!Arq.Exec("SELECT COUNT(*) FROM Country"))
    {
        AstroMessage(i18n("Can't fetch countries names !"));
        return;
    }
    Nb = Arq.GetInt("Count");
    IdxPtr = new Index[Nb];
    Arq.Clear();
    Arq.Exec("SELECT Name, Idx FROM Country ORDER BY Name");
    for (int i = 0; i < Nb; i++, Arq.Next())
    {
        emit Country->addItem(Arq < "Name", i);
        idx = Arq.GetInt("Idx");
        if (Ad->CountryIdx == idx)
            Id = i;
        IdxPtr[i] = idx;
    }
    Country->setCurrentIndex(Id);
}
/*
 *  Constructs a EditPlace which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
EditPlace::EditPlace( QWidget* parent) : QWidget(parent)
{
    setupUi(this);
    Modified = false;
    Id = 1;
    HMS_Format = false;
    SearchList->setIndentation(0);
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditPlace::~EditPlace()
{
    delete IdxPtr;
		delete lat;
		delete lon;
}

/*
 * public slot
 */
void EditPlace::on_DeleteButton_clicked()
{
    if (Idx == LAST)
    {
        AstroMessage(i18n("No such place in the local database !"));
        return;
    }
    if (!Arq.Exec("SELECT Data.Idx FROM Data JOIN Place ON Data.PlaceIdx = Place.Idx WHERE Place.Idx = %d", Idx))
    {
        AstroMessage(i18n("Can't delete this place"));
        return;
    }
    if (Arq.Valid() || Adl->CheckIdx(Idx) || Ahl->CheckPlaceIdx(Idx))
    {
        AstroMessage(i18n("Can't delete this place"));
        return;
    }
    if (Arq.Exec("DELETE FROM Place WHERE Idx = %d", Idx))
    {
        delete SC(SearchLine*, SearchList->currentItem());
        on_CleanButton_clicked();
    }
}

void EditPlace::on_ModifyButton_clicked()
{
    double lat, lon, alt;
    AstroHM hm;
    Index countryidx;
    AstroString as, alat, alon;
    if (Idx == LAST)
    {
        AstroMessage(i18n("This place must be saved first !"), false);
        return;
    }
    if (PlaceName->text().isEmpty() || Latitude->text().isEmpty() ||
            Longitude->text().isEmpty())
    {
        AstroMessage(i18n("Fields Name, Latitude or Longitude can't be empty !"));
        return;
    }
    alat = Latitude->text();
    hm.Set(alat, HM_Latitude);
    lat = hm.Get();
    alon = Longitude->text();
    hm.Set(alon, Ad->HMS_Format ? HM_HMS : HM_Longitude);
    lon = hm.Get();
    alt = Altitude->value();
    as = PlaceName->text();
    countryidx = AstroData::FetchCountryIdx(Country->itemText(Id).toUtf8().data());
    if (!Arq.Exec("UPDATE Place SET Name = '%a', Latitude = %f, Longitude = %f, Altitude = %f, CountryIdx = %d WHERE Idx = %d", &as, lat, lon, alt, countryidx, Idx))
    {
        AstroMessage(i18n("Can't modify new place"));
        return;
    }
    UpdateAd(true);
    Modified = false;
}

/*
 * public slot
 */
void EditPlace::on_Country_highlighted(int i)
{
    Id = i;
    UpdateAd(true);
    emit OffTzRecomp();
}

void EditPlace::on_Altitude_valueChanged(double d)
{
	Modified = Ad->Altitude != d;
}

void EditPlace::on_PlaceName_textChanged(const QString& s)
{
	Modified = Ad->PlaceName != s;
}

void EditPlace::on_NewButton_clicked()
{
    double lat, lon, alt;
    AstroHM hm;
    Index idx, countryidx;
    AstroString as, alat, alon;
    if (PlaceName->text().isEmpty() || Latitude->text().isEmpty() ||
            Longitude->text().isEmpty())
    {
        AstroMessage(i18n("Fields Name, Latitude or Longitude can't be empty !"), true);
        return;
    }
    alat = Latitude->text();
    hm.Set(alat, HM_Latitude);
    lat = hm.Get();
    alon = Longitude->text();
    hm.Set(alon, Ad->HMS_Format ? HM_HMS : HM_Longitude);
    lon = hm.Get();
    as =  PlaceName->text();
    countryidx = AstroData::FetchCountryIdx(Country->itemText(Id).toUtf8().data());
    alt = Altitude->value();
    idx = Arq.NextId("Place");
    if (!Arq.Exec(
				"INSERT INTO Place (Idx, Name, Latitude, Longitude, Altitude, CountryIdx) VALUES(%d, '%a', %f, %f, %f, %d)", idx, &as, lat, lon, alt, countryidx))
    {
        AstroMessage(i18n("Can't insert new place"));
        return;
    }
    Idx = idx;
    Modified = false;
    SearchList->clear();
    SearchList->addTopLevelItem(new SearchLine(Idx, SearchList, as, alat, alon, alt, Country->itemText(Id), countryidx));
    UpdateAd(true);
}
/*
 * public slot
 */
void EditPlace::on_SearchButton_clicked()
{
    AstroString lat, lon, s;
    double alt;
    AstroHM hm;
    if (PlaceName->text().isEmpty())
    {
        AstroMessage(i18n("Place name must not be empty !"), false);
        return;
    }
    s = PlaceName->text();
    if (!Arq.Exec(
		 "SELECT Place.Idx AS PIdx, Place.Name AS PName, Latitude, Longitude, Altitude, Country.Name AS CName, Country.Idx AS CIdx FROM Place JOIN Country ON Place.CountryIdx = Country.Idx WHERE Place.Name ~* '%a' ORDER BY Place.Name"					
		 , &s))
    {
        AstroMessage(i18n("Can't fetch places names !"), false);
        return;
    }
    SearchList->clear();
    if (Arq.Valid()) do
        {
            hm = Arq.GetDouble("Latitude");
            hm.Get(lat, HM_Latitude, false, Ad->To_Second);
            hm = Arq.GetDouble("Longitude");
            hm.Get(lon, Ad->HMS_Format ? HM_HMS : HM_Longitude, false, Ad->To_Second);
            alt = Arq.GetDouble("Altitude");
            SearchList->addTopLevelItem(new SearchLine(Arq.GetInt("PIdx"), SearchList, Arq < "PName", lat, lon, alt, Arq < "CName", Arq.GetInt("Cidx")

					 ));
        }
        while (Arq.Next());
    for (int i = 0; i < 4; i++)
        SearchList->resizeColumnToContents(i);
}

void EditPlace::on_CleanButton_clicked()
{
    emit PlaceName->setText("");
    emit Latitude->setText("");
    emit Longitude->setText("");
    emit Altitude->setValue(0.0);
    Idx = 0;
    //on_CountryButton_clicked();
    emit Country->setCurrentIndex(0);
    Modified = true;
}

void EditPlace::on_CountryButton_clicked()
{
    EditCountry ec;
    ec.exec();
}

void EditPlace::on_ExtSearch_clicked()
{
}

void EditPlace::gotData(const QList<QVariant>& vl, const QVariant v)
{
    AstroStringList asl;
    AstroString name, lat, lon, country, comment, as;
    double alt, dla, dlo;
    Index idx;
    if (vl.first().type() == QVariant::String)
    {
        AstroMessage(vl.first().toString());
        return;
    }
    if (vl.first().type() == QVariant::List)
    {
        SearchList->clear();
        AstroHM hm;
        AstroString as;
        QList<QVariant> qv = vl.first().toList();
        for (QList<QVariant>::const_iterator i = qv.constBegin(); i != qv.constEnd(); ++i)
        {
            Split((*i).toString(), "|", &asl);
            AstroStringList::Const_Iterator it(asl);
            name = (!it) ? QString::fromUtf8(QByteArray::fromBase64((!it)->toLatin1()).data()) : "";
            it++;
            if (!it)
            {
                hm.Set((!it)->toDouble());
                dla = hm.Get();
                lat  = hm.Get(as, HM_Latitude, false, true);
                it++;
            }
            if (!it)
            {
                hm.Set((!it)->toDouble());
                dlo = hm.Get();
                lon  = hm.Get(as, HM_Longitude, false, true);
                it++;
            }
            if (!it) as = *(!it);
            it++;
            alt = as.toDouble();
            if (!it) as = *(!it);
            it++;
            idx = as.toUInt();
            if (!it) comment = *(!it);
            Arq.Exec("SELECT Name FROM Country WHERE idx = %d", idx);
            country = Arq < "Name";
            Arq.Exec("SELECT COUNT(*) FROM Place WHERE floor(Latitude * 10000.0) = %f AND floor(Longitude * 10000.0) = %f", floor(dla * 10000.0), floor(dlo * 10000.0));
            SearchLine* sl = new SearchLine(LAST, SearchList, name, lat, lon, alt, country, idx, comment);
            if (Arq.GetInt("COUNT") != 0)
            {
                const QBrush qb((*Acl)[3]);
                for (int i = 0; i < 5 ; i++)
                    sl->setBackground(i, qb);
            }
            SearchList->addTopLevelItem(sl);
        }
    }
		QApplication::restoreOverrideCursor();
}

void EditPlace::gotError(int i, const QString& s, const QVariant& v)
{
	AstroString as, as1 = s;
	QApplication::restoreOverrideCursor();
	AstroMessage(Sprintf("Error %d\n%a", &as, i, &as1));
}


