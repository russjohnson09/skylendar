#ifndef ASTROENTER_H
#define ASTROENTER_H
#include "ui_astroenter.h"

#include "astrostring.h"
#include <qlineedit.h>

class AstroEnter : public QDialog, public Ui_AstroEnter
{
    Q_OBJECT

public:
    AstroEnter(const AstroString&, const AstroString& label
							 );
    ~AstroEnter();

    inline const AstroString& GetName() {
        ChartName = AstroString(Name->text());
        return ChartName;
    }

public slots:
    void NameSlot();

private:

    AstroString ChartName;
};

#endif
