#ifndef STOPSCAN_H
#define STOPSCAN_H
#include "ui_stopscan.h"

class AspScan;
class AstroEphemeris;
class AstroDir;

class StopScan : public QDialog, public Ui_StopScan
{
    Q_OBJECT

public:
    StopScan(AspScan*, bool dual);
    StopScan(AstroEphemeris*);
    StopScan(AstroDir*);
    ~StopScan();
    void Set(int);

public slots:

    void StopSlot();

private:

    AspScan* Asc;
    AstroEphemeris* Aem;
    AstroDir* Ad;

};

#endif // STOPSCAN_H
