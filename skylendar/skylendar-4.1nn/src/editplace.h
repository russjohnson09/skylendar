#ifndef EDITPLACE_H
#define EDITPLACE_H
# include "ui_editplace.h"
#include "astrosql.h"
#include <QTreeWidget>
#include <QDialog>

class QString;
class AstroData;
class AstroString;
class EditAstroData;
class LlValidator;

#define NAME 0
#define COUNTRY 1
#define COMMENT 2
#define LATITUDE 3
#define LONGITUDE 4

class SearchLine: public QTreeWidgetItem
{

public:

    inline SearchLine(Index idx, QTreeWidget* parent, const QString& Name, const QString& Latitude, const QString& Longitude, double Alti, const QString& Country, Index countryidx, const QString& Comment = QString()
) : QTreeWidgetItem(parent)
    {
        setText(NAME, Name);
        setText(LATITUDE, Latitude);
        setText(LONGITUDE, Longitude);
        setText(COUNTRY, Country);
        setText(COMMENT, Comment);
        Altitude = Alti;
        Idx = idx;
        CountryIdx = countryidx;
    }

    Index Idx, CountryIdx;
    double Altitude;
};

class EditPlace : public QWidget, public Ui_EditPlace
{
    Q_OBJECT

public:

    friend class EditAstroData;

    EditPlace(QWidget* parent);
    void Init(EditAstroData* ead, AstroData* ad, const AstroString* n = 0);
    virtual ~EditPlace();
    bool Modified;

signals:

    void OffTzRecomp();

public slots:
    void on_DeleteButton_clicked();
    void on_Altitude_valueChanged(double);
    void on_PlaceName_textChanged(const QString&);
    void on_NewButton_clicked();
    void on_ModifyButton_clicked();
    void on_SearchButton_clicked();
    void on_Country_highlighted(int);
    void on_CleanButton_clicked();
    void on_CountryButton_clicked();
    void Clicked(QTreeWidgetItem*, int);
    void on_ExtSearch_clicked();
    void gotData(const QList<QVariant>&, const QVariant);
    void gotError(int, const QString&, const QVariant&);

private:

    AstroRequest Arq;
    AstroData* Ad;
    EditAstroData* Ead;
    int Id, Nb;
    Index Idx, *IdxPtr;
    int SearchIdx(Index) const;
    void UpdateAd(bool);
    bool HMS_Format;
    LlValidator *lat, *lon;
};

#endif // EDITPLACE_H
