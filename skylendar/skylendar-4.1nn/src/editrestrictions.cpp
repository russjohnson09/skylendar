#include "objrestr.h"
#include "asprestr.h"
#include "astroutils.h"
#include "editrestrictions.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>

/*
 *  Constructs a EditObjRestr which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */

EditRestrictions::EditRestrictions(AstroRestrictions* ar)
{
    int a, b, c, d, e;
    Ar = ar;
    ArBase = *Ar;
    CurScore = 0;
    qApp->setOverrideCursor(Qt::WaitCursor);
    setupUi(this);
    Orl->Init(ArBase.Restr);
    P;
    Orl->GetLen(&a, &b, &c, &d);
    emit RSName->setText(ArBase.Name);
    if (ArBase.IfHouses())
        emit ToggleHouses->setChecked(true);
    else
        on_ToggleHouses_toggled(false);
    if (ArBase.IfExtra())
        emit ToggleExtra->setChecked(true);
    else
        on_ToggleExtra_toggled(false);
    if (ArBase.IfStars())
        emit ToggleStars->setChecked(true);
    else
        on_ToggleStars_toggled(false);
    const ObjRestr& o = *Orl->Or[0];
    Header->Add(i18n("Object"), o.Name->width() + 8);
    Header->Add(i18n("Use"), o.IsRestricted->width() + 5);
    Header->Add(i18n("Orb Add"), o.OrbAdd->width() + 5);
    Header->Add(i18n("Influence"), o.Influence->width(), true);
    Arl->Init(ArBase.Asprst);
    Arl->GetLen(&a, &b, &c, &d, &e);
    if (ArBase.IfMinor())
        emit ToggleMinor->setChecked(true);
    else
        on_ToggleMinor_toggled(false);
    const AspRest& ap = *Arl->Ar[0];
    AspHeader->Add(i18n("Aspect"), ap.Name->width() + 9);
    AspHeader->Add(i18n("Use"), ap.IsRestricted->width());
    AspHeader->Add(i18n("Orb"), ap.Orb->width());
    AspHeader->Add(i18n("Influence"), ap.Influence->width() + 3);
    AspHeader->Add(i18n("Color"), ap.ColorButton->width(), true);
    for (int i = Placidus; i <=  Sripati; i++)
        HousesCombo->addItem(*Asr->HousesSystemNames[i], i);
    HousesCombo->setCurrentIndex(ArBase.GetHouse());
    TrueNodeCheck->setChecked(ArBase.TrueNode);
    Heliocentric->setChecked(ArBase.Heliocentric);
    Equatorial->setChecked(ArBase.Equatorial);
    for (int i = Tropical; i <= True_Revati; i++)
        SiderealCombo->addItem(*Asr->SiderealSystemNames[i + 1], i+ 1);
    SiderealCombo->setCurrentIndex(ArBase.Sidereal + 1);
    emit Values->setValue(ArBase.Scores[CurScore]);
    emit MPOrbSub->setValue(ArBase.MPOrbSub);
    if (ArBase.Idx == 1)
        Preload->setEnabled(false);
    else
        Preload->setChecked(ArBase.Preload);
    emit Dnpf->setChecked(ArBase.Dnpf);
    emit Southern->setChecked(ArBase.Southern);
    emit ProgFact->setValue(ArBase.ProgFact);
    emit Threshold->setValue(ArBase.Threshold);
    IfSun = ArBase.Restr[Sun].Rest;
    IfEarth = ArBase.Restr[The_Earth].Rest;
    qApp->restoreOverrideCursor();
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditRestrictions::~EditRestrictions()
{
}

void EditRestrictions::on_Ok_clicked()
{
    const AstroString as = (AstroString)RSName->text();
    if (as.isEmpty() || ::Arl->CheckName(as, ArBase.Idx))
    {
        AstroMessage(i18n("All the restrictions sets must have a non-empty and unique name"));
        return;
    }
		if(as[0] == QChar('#'))
		{
			AstroMessage(i18n("the name of a restrictions set must not begin with a #"));
        return;
		}
    ArBase.SetHousesSys((enum House)HousesCombo->currentIndex());
    ArBase.TrueNode = TrueNodeCheck->isChecked();
    ArBase.Heliocentric = Heliocentric->isChecked();
    ArBase.Equatorial   = Equatorial->isChecked();
    ArBase.Dnpf         = Dnpf->isChecked();
    ArBase.Southern     = Southern->isChecked();
    ArBase.ProgFact     = ProgFact->value();
    ArBase.Threshold    = Threshold->value();
    ArBase.Sidereal = (enum Sidereal)(SiderealCombo->currentIndex() - 1);
    *Ar = ArBase;
    Ar->Name = RSName->text();
    Ar->Modified = true;
    Ar->CountObjects();
    Ar->MPOrbSub = MPOrbSub->value();
    Ar->Preload  = Preload->isChecked();
    emit accept();
}

void EditRestrictions::Check(int i, bool b)
{
    Orl->Check(i, b);
    ArBase.Restrict(i, !b);
    if (i == Sun) IfSun = b;
    if (i == The_Earth) IfEarth = b;
}

void EditRestrictions::on_Cancel_clicked()
{
    emit reject();
}

void  EditRestrictions::on_ToggleExtra_toggled(bool b)
{
    for (int i = First_Extra; i <= ArBase.LastExtra; i++)
        if (IfExtraObj(i))
            Orl->Inhibit(i, !b);
    ArBase.RestExtra(b);
}

void EditRestrictions::on_ToggleHouses_toggled(bool b)
{
    for (int i = Ascendant; i <= House_12; i++)
        Orl->Inhibit(i, !b);
    ArBase.RestHouses(b);
}

void EditRestrictions::on_ToggleStars_toggled(bool b)
{
    for (int i = First_Star; i < Final_Star; i++)
        Orl->Inhibit(i, !b);
    ArBase.RestStars(b);
}

void EditRestrictions::on_RestrictAll_clicked()
{
    for (int i = Sun; i <= Last_Planet; i++)
        Check(i, false);
    for (int i = XPoint; i <= House_12; i++)
        Check(i, false);
    for (int i = First_Extra; i <= ArBase.LastExtra; i++)
        Check(i, false);
    for (int i = First_Star; i < Final_Star; i++)
        Check(i, false);
}

void EditRestrictions::on_ReleaseAll_clicked()
{
    for (int i = Sun; i <= Last_Planet; i++)
        Check(i, true);
    for (int i = XPoint; i <= House_12; i++)
        Check(i, true);
    for (int i = First_Extra; i <= ArBase.LastExtra; i++)
        Check(i, true);
    for (int i = First_Star; i < Final_Star; i++)
        Check(i, true);
}

void EditRestrictions::on_InverseSel_clicked()
{
    for (int i = Sun; i <= Last_Planet; i++)
        Check(i, !Orl->IsChecked(i));
    //ArBase.Restrict(i, !(ArBase == i));
    for (int i = XPoint; i <= House_12; i++)
        Check(i, !Orl->IsChecked(i));
    for (int i = First_Extra; i <= ArBase.LastExtra; i++)
        Check(i, !Orl->IsChecked(i));
    for (int i = First_Star; i < Final_Star; i++)
        Check(i, !Orl->IsChecked(i));
}

void EditRestrictions::on_ReleaseAllAsp_clicked()
{
    for (int i = Conjunction; i < Unknown_Aspect; i++)
    {
        Arl->Check(i, true);
        ArBase.AspRestrict(i, false);
    }
}

void EditRestrictions::on_RestrictAllAsp_clicked()
{
    for (int i = Conjunction; i < Unknown_Aspect; i++)
    {
        Arl->Check(i, false);
        ArBase.AspRestrict(i, true);
    }
}

void EditRestrictions::on_InverseSelAsp_clicked()
{
    for (int i = Conjunction; i < Unknown_Aspect; i++)
    {
        Arl->Check(i, !Arl->IsChecked(i));
        ArBase.AspRestrict(i, !ArBase.Asp(i));
    }
}

void EditRestrictions::on_ToggleMinor_toggled(bool b)
{
    for (int i = First_Minor; i < Unknown_Aspect; i++)
        Arl->Inhibit(i, !b);
    ArBase.RestMinor(b);
}

void EditRestrictions::on_Scores_itemClicked(QListWidgetItem*)
{
    int i = Scores->currentRow();
    CurScore = i;
    emit Values->setValue(ArBase.Scores[i]);
}

void EditRestrictions::on_Values_valueChanged(int i)
{
    ArBase.Scores[CurScore] = i;
}

void EditRestrictions::on_MPOrbSub_valueChanged(double d)
{
    Ar->MPOrbSub = d;
}

void EditRestrictions::on_Heliocentric_toggled(bool b)
{
    if (b)
    {
        Check(Sun, false);
        Check(The_Earth, true);
    }
    else
    {
        Check(Sun, IfSun);
        Check(The_Earth, IfEarth);
    }
}
