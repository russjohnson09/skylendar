#include "dblogin.h"
#include "astroresources.h"
#include <klineedit.h>

/*
 *  Constructs a DbLogin which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DbLogin::DbLogin()
        : _DbLogin(0, "DbLogin", true, 0)
{
    DbName->setText(Asr->DbName);
    UserName->setText(Asr->DBUser);
    HostName->setText(Asr->DBHost);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DbLogin::~DbLogin()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void DbLogin::CancelSlot()
{
    emit reject();
}

/*
 * public slot
 */
void DbLogin::OkSlot()
{
    emit accept();
}


