#ifndef VALIDSKIF_H
#define VALIDSKIF_H
#include "ui_validskif.h"

class AstroString;

class ValidSKIF : public QDialog, public Ui_ValidSKIF
{
    Q_OBJECT

public:
    ValidSKIF(AstroString& charttype, const AstroString& place, AstroString& country, const AstroString& name);
    ~ValidSKIF();

public slots:
    void on_CountryButton_clicked();
    void on_Next_clicked();

private:

    AstroString *CountryPtr, *ChartTypePtr;

};

#endif // VALIDSKIF_H
