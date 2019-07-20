#include "stopscan.h"
#include <qlabel.h>
#include "aspscanlist.h"
#include "astroephemeris.h"
#include "astrodirections.h"

/*
 *  Constructs a StopScan which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
StopScan::StopScan(AspScan* asc, bool dual)
{
    Asc = asc;
    Aem = 0;
    Ad = 0;
    setupUi(this);
    emit Dual->setText(dual ? i18n("Dual Scan") : i18n("Simple Scan"));
    emit progressBar->setMinimum(0);
    emit progressBar->setMaximum(100);
    //emit progressBar->setValue(0);
    show();
}


StopScan::StopScan(AstroEphemeris* aem)
{
    Aem = aem;
    Asc = 0;
    Ad = 0;
    setupUi(this);
    emit Dual->setText(i18n("Date Scan"));
    emit setWindowTitle(i18n("Ephemeris"));
    emit progressBar->setMinimum(0);
    show();
}

StopScan::StopScan(AstroDir* ad)
{
    Aem = 0;
    Asc = 0;
    Ad = ad;
    setupUi(this);
    emit Dual->setText(i18n("Date Scan"));
    emit setWindowTitle(i18n("Primary Directions"));
    emit progressBar->setMinimum(0);
    show();
}

/*
 *  Destroys the object and frees any allocated resources
 */
StopScan::~StopScan()
{
    // no need to delete child widgets, Qt does it all for us
}

void StopScan::StopSlot()
{
    if (Asc)
        Asc->Acb->Second->GetInterface()->StopScan();
    else if (Aem)
        Aem->First->GetInterface()->StopScan();
    else
        Ad->Acb->GetRef().GetInterface()->StopScan();
}

void StopScan::Set(int i)
{
    progressBar->setValue(i);
}
