#ifndef OBJRESTR_H
#define OBJRESTR_H

#include "ui_objrestr.h"
#include "astrodefs.h"
#include <QCheckBox>
#include <QScrollArea>

struct Rest;

class ObjRestr : public QWidget, public Ui_ObjRestr
{
    Q_OBJECT

public:
    ObjRestr(QWidget* parent, struct Rest* rest, int i);
    ~ObjRestr();

public slots:

    void on_IsRestricted_toggled(bool);
    void on_OrbAdd_valueChanged(double);
    void on_Influence_valueChanged(int);
    bool IfRestrict() const;

private:

    struct Rest* Rest;
};

class ObjRestList : public QScrollArea
{
    Q_OBJECT

public:

    friend class EditRestrictions;

    ObjRestList(QWidget* parent);
    ~ObjRestList();
    void Init(struct Rest* rest);
    void GetLen(int* a, int* b, int* c, int *d) const;
    void Inhibit(int i, bool b);
    void Check(int i, bool b);
    bool IsChecked(int i) const {
        return Or[i]->IsRestricted->isChecked();
    }

private:

    struct Rest* Rest;
    ObjRestr *Or[Last_Star];
    void FillList(struct Rest* rest, int first, int last);
    int Yi, H, Cnt;
    QWidget* Qw;
};

#endif // OBJRESTR_H
