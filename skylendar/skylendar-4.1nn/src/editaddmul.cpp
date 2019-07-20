#include "editaddmul.h"
#include "astroobjs.h"
#include "astroutils.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <cstdio>

/*
 *  Constructs a EditAddMul which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
EditAddMul::EditAddMul(double val)
{
    AstroString as;
    setupUi(this);
    Val = val;
    emit Value->setText(Sprintf("%f", &as, Val));
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditAddMul::~EditAddMul()
{
    // no need to delete child widgets, Qt does it all for us
}

void EditAddMul::on_CancelButton_clicked()
{
    emit reject();
}

void EditAddMul::on_OkButton_clicked()
{
    Val = atof(Value->text().toUtf8().data());
    emit accept();
}

void EditAddMul::on_ValBox_activated(int i)
{
    char buf[5];
    sprintf(buf, "%.02f", 1.0 * (i + 2));
    emit Value->setText(buf);
}
