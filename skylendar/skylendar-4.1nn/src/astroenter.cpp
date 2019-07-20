#include "astroenter.h"

/*
 *  Constructs a AstroEnter which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
AstroEnter::AstroEnter(const AstroString& as, const AstroString& label)
{
    setupUi(this);
    emit Name->setText(as);
    emit Label->setText(label);
}

/*
 *  Destroys the object and frees any allocated resources
 */
AstroEnter::~AstroEnter()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void AstroEnter::NameSlot()
{
    qWarning( "AstroEnter::NameSlot() not yet implemented!" );
}


