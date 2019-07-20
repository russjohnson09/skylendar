#ifndef SCANSPAN_H
#define SCANSPAN_H
#include "ui_scanspan.h"
#include "astrodefs.h"

class AspScanParams;
class QButtonGroup;

class EditScanSpan : public QDialog, public Ui_EditScanSpan
{
    Q_OBJECT

public:
    EditScanSpan(AspScanParams*, bool mp = false);
    ~EditScanSpan();
    enum ScanSpan Selected;

public slots:

    void ButtonSlot(int);

    void on_OkButton_clicked();

private:

    QButtonGroup* Qbg;
    AspScanParams* Asp;
};

#endif // SCANSPAN_H
