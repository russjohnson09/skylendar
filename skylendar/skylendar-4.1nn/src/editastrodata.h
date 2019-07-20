#ifndef EDITASTRODATA_H
#define EDITASTRODATA_H

#include "../config.h"
#ifdef QT
#include "ui_editastrodata.h"
#include <QDialog>
class QButtonGroup;
class TdValidator;
namespace KXmlRpc
{
	class Client;
};
#endif

class AstroData;
class AstroString;
class EditPlace;

class EditAstroData : public QDialog, public Ui_EditAstroData
{
    Q_OBJECT

public:

    friend class EditPlace;

    EditAstroData(AstroData&, const AstroString* n = 0);

    ~EditAstroData();

public slots:
    void on_Automatic_toggled(bool);
    void on_CancelButton_clicked();
    //void on_DaylightLine_lostFocus();
    void on_Day_activated(int);
    void on_Month_activated(int);
    void on_Year_valueChanged(int);
    void on_Hour_valueChanged(int);
    void on_Minute_valueChanged(int);
    void on_Second_valueChanged(int);
    void on_OkButton_clicked();
    void on_TypeofChart_highlighted(int);
    void on_HMSButton_toggled(bool);
    //void on_TimezoneLine_lostFocus();
    void on_RecomputeButton_clicked();
    void on_NowButton_clicked();
    void on_TagBox_activated(int);
    void on_SrcBox_activated(int);
    void on_Accuracy_valueChanged(int);
    void on_DtsChoice_activated(int);
    void on_Preload_toggled(bool);
    void on_ToSecond_toggled(bool);

private slots:
    void OffTzRecomp();

private:

    void WriteError(const QString&);
    bool CheckDate(int d, int mo, int y, int h, int m, int s);
    void SetDate(int d, int mo, int y, int h, int m, int s);
    AstroData *Ad, *AdBase;
		TdValidator *Td;
    bool Change;
#ifdef QT
    QButtonGroup* Qbg;
		KXmlRpc::Client* Xr;

#endif
};

#endif // EDITASTRODATA_H
