#ifndef EDITDEFPARMS_H
#define EDITDEFPARMS_H
#include "ui_editdefparms.h"
#include "astroparams.h"
#include <QMenu>
#include "astrographics.h"
class QActionGroup;
class QAction;

class EditDefParms : public QDialog, public Ui_EditDefParms
{
    Q_OBJECT

public:
    EditDefParms(AstroParams*);
    ~EditDefParms();

public slots:
    void on_AirColor_clicked();
    void on_AsteroColor_clicked();
    void on_EarthColor_clicked();
    void on_ExtraColor_clicked();
    void on_FireColor_clicked();
    void on_OkButton_clicked();
    void on_OtherColor_clicked();
    void on_WaterColor_clicked();
    void on_CancelButton_clicked();
		void on_BackFile_clicked();
    void Activated(QAction*);
    void on_DefChartParms_clicked();
    void on_Col0_ChangeColor(const QColor&);
    void on_Col10_ChangeColor(const QColor&);
    void on_Col11_ChangeColor(const QColor&);
    void on_Col12_ChangeColor(const QColor&);
    void on_Col13_ChangeColor(const QColor&);
    void on_Col14_ChangeColor(const QColor&);
    void on_Col15_ChangeColor(const QColor&);
    void on_Col1_ChangeColor(const QColor&);
    void on_Col2_ChangeColor(const QColor&);
    void on_Col3_ChangeColor(const QColor&);
    void on_Col4_ChangeColor(const QColor&);
    void on_Col5_ChangeColor(const QColor&);
    void on_Col6_ChangeColor(const QColor&);
    void on_Col7_ChangeColor(const QColor&);
    void on_Col8_ChangeColor(const QColor&);
    void on_Col9_ChangeColor(const QColor&);
		void on_TextFont_currentFontChanged(const QFont&);
		void on_FontSize_valueChanged(int);

private:

    AstroColor* Ac;
    void ChangeColor(const QColor&, int i);
    AstroParams* Ap, ApBase;
    QMenu Qppm;
    QActionGroup* Qag;
    void ChooseColor(int&);
    int Chosen, Context;
};

void ChangeButton(QPushButton*, const QColor&);

#endif // EDITDEFPARMS_H
