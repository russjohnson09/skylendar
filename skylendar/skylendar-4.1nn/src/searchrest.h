#ifndef SEARCHREST_H
#define SEARCHREST_H
#include "ui_searchrest.h"
#include "astrosql.h"
#include <astroresources.h>
#include <QTreeWidgetItem>

class SearchRest : public QDialog, public Ui_SearchRest
{
    Q_OBJECT

public:
    SearchRest();
    ~SearchRest();

public slots:
    void on_CancelButton_clicked();
    void Clicked(QTreeWidgetItem*);
    void on_OkButton_clicked();
    void on_SearchButton_clicked();

private:

    AstroRequest Arq;

};

class SearchRestItem: public QTreeWidgetItem
{
public:

    SearchRestItem(QTreeWidget* parent, Index idx, const AstroString& name);
    Index Idx;
};
#endif // SEARCHREST_H
