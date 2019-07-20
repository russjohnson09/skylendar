#ifndef EDITCOUNTRY_H
#define EDITCOUNTRY_H
#include "ui_editcountry.h"
#include "astrosql.h"
#include <QTreeWidget>

class EditCountry : public QDialog, public Ui_EditCountry
{
    Q_OBJECT

public:
    EditCountry(const AstroString* n = 0);
    ~EditCountry();
    AstroString SavedName;

public slots:
    void Clicked(QTreeWidgetItem*, int);
    void on_DeleteButton_clicked();
    void on_ModifyButton_clicked();
    void on_NewButton_clicked();
    void on_OkButton_clicked();
    void on_SearchButton_clicked();
    void on_FileListButton_clicked();


private:

    AstroRequest Arq;
    Index Idx;

};

class CountryLine: public QTreeWidgetItem
{

public:

    inline CountryLine(Index idx, QTreeWidget* parent, const QString& name, const QString& zifile, const char* code, const QString& J2g, const QString& Comment) : QTreeWidgetItem(parent)
    {
        setText(0, name);
        setText(1, zifile);
        setText(2, code);
        setText(3, J2g);
        setText(4, Comment);
        Idx = idx;
    }

    Index Idx;
};
#endif // EDITCOUNTRY_H
