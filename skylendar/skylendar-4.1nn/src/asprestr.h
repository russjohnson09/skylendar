#ifndef ASPREST_H
#define ASPREST_H
#include "ui_asprestr.h"
#include "astrodefs.h"
#include "astrorestrictions.h"
#include <QCheckBox>
#include <QMenu>
#include <QPixmap>
#include <QScrollArea>

struct AspectRestrictions;
class QPixmap;
class AspRestList;
class QActionGroup;
class QAction;

class AspRest : public QWidget, public Ui_AspRestr
{
    Q_OBJECT

public:
    AspRest(AspRestList* arl, int i);
    ~AspRest();

public slots:

    void on_IsRestricted_toggled(bool);
    void on_ColorButton_pressed();
    void on_Orb_valueChanged(double);
    void on_Influence_valueChanged(int);

private:

    AspRestList* Arl;
    int Item;

};

class AspRestList : public QScrollArea
{
    Q_OBJECT

public:

    friend class AspRest;
    friend class EditRestrictions;

    AspRestList(QWidget* parent);
    ~AspRestList();
    void Init(struct AspectRestrictions* asr);
    void GetLen(int* a, int* b, int* c, int *d, int* e) const;
    void Inhibit(int i, bool b);
    void Check(int i, bool b);
    bool IsChecked(int i) const;

public slots:

    void Triggered(QAction*);

private:

    struct AspectRestrictions* Asrt;
    AspRest *Ar[Unknown_Aspect];
    void FillList(int first, int last);
    int Y, H, Item;
    QMenu Qppm;
    QActionGroup* Qag;
    QWidget* Backg;

};

#endif // ASPREST_H
