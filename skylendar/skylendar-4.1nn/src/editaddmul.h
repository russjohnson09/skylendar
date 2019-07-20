#ifndef EDITADDMUL_H
#define EDITADDMUL_H
#include "ui_editaddmul.h"

class AstroObjs;

class EditAddMul : public QDialog, public Ui_EditAddMul
{
    Q_OBJECT

public:
    EditAddMul(double val);
    ~EditAddMul();

    double Val;

public slots:

    void on_CancelButton_clicked();
    void on_OkButton_clicked();
    void on_ValBox_activated(int);
};

#endif // EDITADDMUL_H
