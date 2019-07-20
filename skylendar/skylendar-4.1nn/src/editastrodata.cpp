#include "editplace.h"
#include "editastrodata.h"
#include "astrodata.h"
#include "astroprocess.h"
#include "astrospinbox.h"
#include "astrowindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QUrl>
#include <QLabel>
#include <QCheckBox>
#include <QRegExp>
#include <QPushButton>
#include <QValidator>
#include <QButtonGroup>

extern AstroIconsList* Ail;

int GetTz(QString s, double& d)
{
    bool b = false;
    int i;
    AstroHM hm;
    if (s.left(1) == "-") // "c"
    {
        b = true;
        s.remove(0,1);
    }
    i = hm.Set(AstroString(s));
    d = b ? -hm.Get() : hm.Get();
    return i;
}

class TdValidator: public QValidator
{
public:

	State	validate(QString & input, int & pos) const;
	void fixup(QString & input) const;
};

void TdValidator::fixup(QString & input) const
{
	//qDebug() << input;
}

QValidator::State TdValidator::validate(QString & input, int & pos) const
{
	AstroString r(input);
    double d;
		return GetTz(r, d) ? QValidator::Invalid : QValidator::Acceptable;
    /*switch (GetTz(r, d))
    {
    case ASTROHM_WRONG_HOUR:
			return QValidator::Invalid;
        r = i18n("Error in offset hour");
        break;
    case ASTROHM_WRONG_SEPARATOR:
			return QValidator::Invalid;
        r = i18n("Error in hour/minute separator");
        break;
    case ASTROHM_WRONG_MINUTE:
			return QValidator::Invalid;
        r = i18n("Error in offset minute");
        break;
    case ASTROHM_WRONG_SECOND:
			return QValidator::Invalid;
        r = i18n("Error in offset second");
        break;
    default:;
        r = "";
		}
		return QValidator::Acceptable;*/
}

/*
 *  Constructs a EditAstroData which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */


EditAstroData::EditAstroData(AstroData& ad, const AstroString* n)
{
    AdBase = new AstroData(ad);
    Ad = &ad;
    int h, m, s, day, month, year;
    bool corr = AdBase->Automatic;
    AstroString as;
    AstroIcon* ai;
    Change = true;
    setupUi(this);
    Qbg = new QButtonGroup(this);
    Qbg->addButton(MaleButton, Male);
    Qbg->addButton(FemaleButton, Female);
    Qbg->addButton(NeutralButton, Neutral);
    Qbg->addButton(SituationButton, Situation);
    AdBase->GetDate(&day, &month, &year, &h, &m, &s);
    AdBase->Automatic = false;
		Td = new TdValidator;
		TimezoneLine->setValidator(Td);
		DaylightLine->setValidator(Td);
    if (Ad->Name == i18n("Now"))
    {
        emit Date->setEnabled(false);
        emit Name->setEnabled(false);
        emit TypeofChart->setEnabled(false);
        emit Preload->setEnabled(false);
        emit NowButton->setEnabled(false);
    }
    if (Ad->Automatic)
    {
        emit DtsChoice->setEnabled(false);
        emit TimezoneLine->setEnabled(false);
        emit DaylightLine->setEnabled(false);
    }
    else
    {
        emit DSLabel->setEnabled(false);
        emit DateSystem->setEnabled(false);
    }
    if (Ad->Accuracy < 0)
    {
        emit Second->setEnabled(false);
        emit Minute->setEnabled(false);
        emit Hour->setEnabled(false);
    }
    foreachc(*Ail, AstroIconsList)
    TypeofChart->addItem((!it)->Name);
    emit ChartTypeIcon->setPixmap(*(*Ail)[AdBase->ChartType]);
    emit Name->setText(AdBase->Name);
    emit Comment->setText(AdBase->Comment);
    emit Keywords->setText(AdBase->Keywords);
    Qbg->button(AdBase->Gender)->setChecked(true);
    TypeofChart->setCurrentIndex(AdBase->ChartType);
    TrueSolarTime->setChecked(AdBase->TrueSolarTime);
    AdBase->Automatic = corr;
    SetDate(AdBase->Day, AdBase->Month, AdBase->Year, h, m, s);
    emit Accuracy->setValue(Ad->Idx == 0 ? 0 : AdBase->Accuracy);
    PlaceEdition->Init(this, AdBase, n);
    ToSecond->setChecked(AdBase->To_Second);
    Change = false;
    Automatic->setChecked(AdBase->Automatic);
    Change = true;
    HMSButton->setChecked(AdBase->HMS_Format);
    Preload->setChecked(AdBase->Preload);
    if (!AdBase->To_Second) emit Second->setEnabled(false);
    bool hf = AdBase->HMS_Format;
    AdBase->HMS_Format = false;
    on_HMSButton_toggled(hf);
    AdBase->HMS_Format = hf;
    if (Ad->Automatic)
        emit DateSystem->setText(*Asr->DateSysNames[AdBase->GetDs()]);
    emit Julday->setText(Sprintf("%f", &as, AdBase->GetJd()));
    OffTzRecomp();
    connect(PlaceEdition, SIGNAL(OffTzRecomp()), this, SLOT(OffTzRecomp()));
    QUrl u(SKYSITE + "/geo/skylendar.php");
    u.setUserName(Asr->SkyUser.Len() ? Asr->SkyUser : Asr->DbUser);
    u.setPassword(Asr->SkyPass.Len() ? Asr->SkyPass : Asr->DbPass);
}
/*
 *  Destroys the object and frees any allocated resources
 */
EditAstroData::~EditAstroData()
{
    delete AdBase;
		delete Td;
}

/*
 * public slot
 */
void EditAstroData::on_CancelButton_clicked()
{
    Ad->Modified = false;
    emit reject();
}

void EditAstroData::OffTzRecomp()
{
    AstroString as;
    AstroHM hm(AdBase->GetOffset());
    emit TimezoneLine->setText(hm.Get(as, HM_Time, false, AdBase->To_Second));
    hm = AdBase->GetDaylight();
    emit DaylightLine->setText(hm.Get(as, HM_Time, false, AdBase->To_Second));

}

/*
 * public slot
 */
void EditAstroData::on_OkButton_clicked()
{
	double o, d;
    if (Name->text().isEmpty())
    {
        AstroMessage(i18n("You must provide a name to this data set"));
        return;
    }
        if(Name->text()[0] == '#')
        {
            AstroMessage(i18n("The name of a data set must not begin with a #"));
            return;
        }
    if (PlaceEdition->PlaceName->text().isEmpty())
    {
        AstroMessage(i18n("You must provide a place to this data set"));
        return;
    }
    if (PlaceEdition->Modified)
    {
        AstroMessage(i18n("You have forgotten to validate the modification of the place !"));
        return;
    }
    AdBase->TrueSolarTime = TrueSolarTime->isChecked();
    if (!CheckDate(Day->currentIndex() + 1, Month->currentIndex() + 1, Year->value(), Hour->value(), Minute->value(), Second->value()))
    {
        WriteError(i18n("Wrong date !"));
        return;
    }
    AdBase->Name = AstroString(Name->text());
    AdBase->Comment = AstroString(Comment->toPlainText());
    AdBase->Keywords = AstroString(Keywords->text());
    QRegExp pat(", ?$");
    AdBase->Keywords.remove(pat);
    pat.setPattern(" ?= ?");
    AdBase->Keywords.replace(pat, "=");
    AdBase->Gender = (enum Gender)Qbg->checkedId();
    AdBase->Accuracy = Accuracy->value();
    AdBase->ChartType = TypeofChart->currentIndex();
    AdBase->GetCountryName();
    GetTz(TimezoneLine->text(), o);
		GetTz(DaylightLine->text(), d);
    AdBase->SetOffDay(o, d);
    AdBase->To_Second = ToSecond->isChecked();
    AdBase->Automatic = Automatic->isChecked();
    AdBase->Preload = Preload->isChecked();
    AdBase->Modified = true;
		PlaceEdition->UpdateAd(false);
    *Ad = *AdBase;
    AstroString as;
    emit accept();
}

bool EditAstroData::CheckDate(int d, int mo, int y, int h, int m, int s)
{
    enum DateSystem ds = AdBase->CheckDate(d, mo, y, h, m, s);
    if (ds == Invalid_date)
    {
        WriteError(i18n("Wrong date !"));
        return false;
    }
    emit DateSystem->setText(AdBase->Automatic ? *Asr->DateSysNames[ds] : "");
    SetDate(d, mo, y, h, m, s);
    WriteError("");
    return true;
}

void EditAstroData::SetDate(int d, int mo, int y, int h, int m, int s)
{
    AstroString as;
    AstroHM hm;
    Change = false;
    emit Day->setCurrentIndex(d - 1);
    emit Month->setCurrentIndex(mo - 1);
    emit Year->setValue(y);
    emit Hour->setValue(h);
    emit Minute->setValue(m);
    emit Second->setValue(s);
    Change = true;
    AdBase->SetDate(d, mo, y, h, m, s);
    emit Julday->setText(Sprintf("%f", &as, AdBase->GetJd()));
}

void EditAstroData::on_Day_activated(int day)
{
    int d, mo, y, h, m, s;
    AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
    CheckDate(day + 1, mo, y, h, m, s);
    if (AdBase->Automatic) OffTzRecomp();
}

void EditAstroData::on_Month_activated(int month)
{
    int d, mo, y, h, m, s;
    AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
    CheckDate(d, month + 1, y, h, m, s);
    if (AdBase->Automatic) OffTzRecomp();
}

void EditAstroData::on_Year_valueChanged(int year)
{
    int d, mo, y, h, m, s;
    if (Change)
    {
        AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
        CheckDate(d, mo, year, h, m, s);
        if (AdBase->Automatic) OffTzRecomp();
    }
}

void EditAstroData::on_Hour_valueChanged(int hour)
{
    int d, mo, y, h, m, s;
    if (Change)
    {
        AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
        CheckDate(d, mo, y, hour, m, s);
        if (AdBase->Automatic) OffTzRecomp();
    }
}

void EditAstroData::on_Minute_valueChanged(int min)
{
    int d, mo, y, h, m, s;
    if (Change)
    {
        AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
        CheckDate(d, mo, y, h, min, s);
        if (AdBase->Automatic) OffTzRecomp();
    }
}

void EditAstroData::on_Second_valueChanged(int sec)
{
    int d, mo, y, h, m, s;
    if (Change)
    {
        AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
        CheckDate(d, mo, y, h, m, sec);
        if (AdBase->Automatic) OffTzRecomp();
    }
}

void EditAstroData::on_TypeofChart_highlighted(int i)
{
    emit ChartTypeIcon->setPixmap(*(*Ail)[i]);
}

void EditAstroData::on_Automatic_toggled(bool b)
{
    AstroString as;
    AstroHM hm;
    AdBase->Automatic = b;
    AdBase->Modified = true;
    if (Change)
        on_RecomputeButton_clicked();
    emit DtsChoice->setEnabled(!b);
    emit TimezoneLine->setEnabled(!b);
    emit DaylightLine->setEnabled(!b);
    emit DSLabel->setEnabled(b);
    emit DateSystem->setEnabled(b);
    if (!b) emit DateSystem->setText("");
}

void EditAstroData::on_HMSButton_toggled(bool b)
{
    AstroHM hm;
    AstroString as = (AstroString)PlaceEdition->Longitude->text();
    hm.Set(as, AdBase->HMS_Format ? HM_HMS : HM_Longitude);
    AdBase->HMS_Format = PlaceEdition->HMS_Format = b;
    emit PlaceEdition->Longitude->setText(hm.Get(as, AdBase->HMS_Format ?  HM_HMS : HM_Longitude, false, AdBase->To_Second));
    PlaceEdition->SearchList->clear();
    AdBase->Modified = true;
}

void EditAstroData::on_DtsChoice_activated(int i)
{
    QString qs;
    switch (i)
    {
    case 0:
        qs = AdBase->To_Second ? "0:00:00" : "0:00";
        break;
    case 1:
        qs = AdBase->To_Second ? "1:00:00" : "1:00";
        break;
    case 2:
        qs = AdBase->To_Second ? "2:00:00" : "2:00";
        break;
    case 3:
        qs = AdBase->To_Second ? "0:30:00" : "0:30";
        break;
    };
    emit DaylightLine->setText(qs);
    //on_DaylightLine_lostFocus();
}

void EditAstroData::on_RecomputeButton_clicked()
{
    AstroHM hm;
    AstroString as;
    bool b = AdBase->Automatic;
    AdBase->Automatic = true;
    PlaceEdition->UpdateAd(true);
    hm = AdBase->GetOffset();
    emit TimezoneLine->setText(hm.Get(as, HM_Time, false, AdBase->To_Second));
    hm = AdBase->GetDaylight();
    emit DaylightLine->setText(hm.Get(as, HM_Time, false, AdBase->To_Second));
    AdBase->Modified = true;
    AdBase->Automatic = b;
}

void EditAstroData::on_NowButton_clicked()
{
    int d, mo, y, h, m, s;
    PlaceEdition->UpdateAd(false);
    AdBase->Now();
    AdBase->GetDate(&d, &mo, &y, &h, &m, &s);
    emit Day->setCurrentIndex(d - 1);
    emit Month->setCurrentIndex(mo - 1);
    emit Year->setValue(y);
    emit Hour->setValue(h);
    emit Minute->setValue(m);
    emit Second->setValue(s);
    if (AdBase->Automatic)
        OffTzRecomp();
    AdBase->Modified = true;
}

void EditAstroData::WriteError(const QString& s)
{
    emit Error->setText(s);
}

void EditAstroData::on_TagBox_activated(int i)
{
    QString s;
    switch (i)
    {
    case 0:
        s = "Prof=, ";
        break;
    case 1:
        s = "Chld=, ";
        break;
    case 2:
        s = "Illn=, ";
        break;
    case 3:
        s = "Src=, ";
        break;
    case 4:
        s = "Via=, ";
        break;
    case 5:
        s = "Cqu=, ";
        break;
    case 6:
        s = "Nat=, ";
        break;
    default:
        ;
    }
    emit Keywords->setFocus();
    Keywords->insert(s);
    Keywords->cursorBackward(false, 2);
}

void EditAstroData::on_SrcBox_activated(int i)
{
    QString s;
    switch (i)
    {
    case 0:
        s = "Orig=Direct, ";
        break;
    case 1:
        s = "Orig=Register, ";
        break;
    case 2:
        s = "Orig=Fambook, ";
        break;
    case 3:
        s = "Orig=Astrologer, ";
        break;
    case 4:
        s = "Orig=Mother, ";
        break;
    case 5:
        s = "Orig=Father, ";
        break;
    case 6:
        s = "Orig=Personal, ";
        break;
    case 7:
        s = "Orig=Biography, ";
        break;
    case 8:
        s = "Orig=Partner, ";
        break;
    case 9:
        s = "Orig=Possibility, ";
        break;
    case 10:
        s = "Orig=Speculative, ";
        break;
    default:
        ;
    }
    emit Keywords->setFocus();
    Keywords->insert(s);
}

void EditAstroData::on_Accuracy_valueChanged(int i)
{
    emit Second->setEnabled(i < 0 ? false : true);
    emit Minute->setEnabled(i < 0 ? false : true);
    emit Hour->setEnabled(i < 0 ? false : true);
}

void EditAstroData::on_Preload_toggled(bool b)
{
    AdBase->Preload = b;
}

void EditAstroData::on_ToSecond_toggled(bool b)
{
    AstroHM hm;
    AstroString as = AstroString(PlaceEdition->Longitude->text());
    hm.Set(as, AdBase->HMS_Format ? HM_HMS : HM_Longitude);
    AdBase->To_Second = b;
    Change = false;
    emit Second->setEnabled(AdBase->To_Second);
    OffTzRecomp();
    emit PlaceEdition->Longitude->setText(hm.Get(as, AdBase->HMS_Format ?  HM_HMS : HM_Longitude, false, AdBase->To_Second));
    as = (AstroString)PlaceEdition->Latitude->text();
    hm.Set(as, HM_Latitude);
    emit PlaceEdition->Latitude->setText(hm.Get(as, HM_Latitude, false, AdBase->To_Second));
    Change = true;
}
