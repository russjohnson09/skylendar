#ifndef SEARCHDATA_H
#define SEARCHDATA_H
#include "ui_searchdata.h"
#include "astrosql.h"
#include <QTreeWidget>
#include "astrowindow.h"
class QButtonGroup;

class SearchData : public QDialog, public Ui_SearchData
{
    Q_OBJECT

public:
    SearchData();
    ~SearchData();

public slots:
    void ClickedSlot(QTreeWidgetItem*);
    void on_OkButton_clicked();
    void ReqTypeSlot(int);
    void on_SearchButton_clicked();
    void on_CancelButton_clicked();
    void on_ANDButton_clicked();
    void on_Aspects_activated(int);
    void on_Planets_activated(int);
    void on_NOTButton_clicked();
    void on_ORButton_clicked();
    void on_TAspButton_clicked();
    void on_THouseButton_clicked();
    void on_TObjButton_clicked();
    void on_TRestButton_clicked();
    void on_SiblButton_clicked();
    void on_DeleteButton_clicked();
    void on_DumpValButton_clicked();

private:

    int SQLReqType;
    AstroRequest Arq;
    void Insert(const QString& qs, int pos = 0);
    void ShowBtn(bool);
    QButtonGroup* Qbg;

};

class SearchItem : public QTreeWidgetItem
{
public:

    SearchItem(QTreeWidget* parent, Index idx, const AstroString& name, const AstroString& date, const AstroString& place, const AstroIcon& icon);
    Index Idx;
};
#endif // SEARCHDATA_H
