#ifndef EDITRESTRICTIONS_H
#define EDITRESTRICTIONS_H
#include "ui_editrestrictions.h"
#include "astrorestrictions.h"
class AstroRestrictions;

class EditRestrictions : public QDialog, public Ui_EditObjRestr
{
    Q_OBJECT

public:
    EditRestrictions(AstroRestrictions* ar);
    ~EditRestrictions();

public slots:

    void on_Ok_clicked();
    void on_Cancel_clicked();
    void on_ToggleExtra_toggled(bool);
    void on_ToggleHouses_toggled(bool);
    void on_ToggleStars_toggled(bool);
    void on_RestrictAll_clicked();
    void on_ReleaseAll_clicked();
    void on_InverseSel_clicked();
    void on_ReleaseAllAsp_clicked();
    void on_RestrictAllAsp_clicked();
    void on_InverseSelAsp_clicked();
    void on_ToggleMinor_toggled(bool);
    void on_Scores_itemClicked(QListWidgetItem*);
    void on_Values_valueChanged(int);
    void on_MPOrbSub_valueChanged(double);
    void on_Heliocentric_toggled(bool);

private:

    void Check(int i, bool b);
    AstroRestrictions *Ar, ArBase;
    int CurScore;
    bool IfSun, IfEarth;

};

#endif // EDITOBJRESTR_H
