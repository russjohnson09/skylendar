#ifndef EDITCHARTPARMS_H
#define EDITCHARTPARMS_H
#include "ui_editchartparms.h"
#include "astroparams.h"

class EditChartParms : public QDialog, public Ui_EditChartParms
{
    Q_OBJECT

public:
    EditChartParms(ChartParams*);
    ~EditChartParms();

public slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked();
    void SubringSlot(int);

private:

    ChartParams* Cp, CpBase;

};

#endif // EDITCHARTPARMS_H
