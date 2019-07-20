#include "scanspan.h"
#include "astroresources.h"
#include <QSpinBox>
#include <QButtonGroup>
#include <QRadioButton>

/*
 *  Constructs a ScanSpan which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
EditScanSpan::EditScanSpan(AspScanParams* asp, bool mp)
{
    setupUi(this);
    Asp = asp;
    Qbg = new QButtonGroup(this);
    Qbg->addButton(CurDay, Current_Day);
    Qbg->addButton(CurMonth, Current_Month);
    Qbg->addButton(CurYear, Current_Year);
    Qbg->addButton(NbYears, Years);
    if (mp)
    {
        Qbg->addButton(SolRev, Solar_Rev);
        Qbg->addButton(LunarRev, Lunar_Rev);
    }
    else
    {
        SolRev->setEnabled(false);
        LunarRev->setEnabled(false);
    }
    Selected = asp->Ss;
    Qbg->button(asp->Ss)->setChecked(true);
    YearsNumber->setValue(asp->NbYears);
    emit MP->setChecked(asp->MP);
    emit Part->setChecked(asp->AP);
    emit DumpAsp->setChecked(asp->DumpAsp);
    if (!mp)
    {
        MP->setHidden(true);
        Part->setHidden(true);
        DumpAsp->setHidden(true);

    }
    connect(Qbg, SIGNAL(buttonClicked(int)), this, SLOT(ButtonSlot(int)));
}

void EditScanSpan::ButtonSlot(int i)
{
    Selected = (enum ScanSpan)i;
    YearsNumber->setEnabled(Selected == Years);
    MP->setEnabled(Selected != Solar_Rev && Selected != Lunar_Rev);
    Part->setEnabled(Selected != Solar_Rev && Selected != Lunar_Rev);
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditScanSpan::~EditScanSpan()
{
    // no need to delete child widgets, Qt does it all for us
}

void EditScanSpan::on_OkButton_clicked()
{
    Asp->Ss = Selected;
    Asp->NbYears = YearsNumber->value();
    Asp->MP = MP->isChecked();
    Asp->DumpAsp = DumpAsp->isChecked();
    Asp->AP = Part->isChecked();
}
