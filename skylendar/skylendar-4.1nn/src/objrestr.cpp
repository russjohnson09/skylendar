#include "objrestr.h"
#include "astrorestrictions.h"
#include "astroresources.h"
#include "astroutils.h"
#include <cstdlib>
#include <QLabel>
#include <QSpinBox>

/*
 *  Constructs a ObjRestr which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
ObjRestr::ObjRestr(QWidget* parent, struct Rest* rest, int i) : QWidget(parent)
{
    Rest = rest;
    setupUi(this);
    emit Name->setText(ObjName(i));
    emit IsRestricted->setChecked(!rest->Rest);
    emit OrbAdd->setValue(rest->OrbAdd);
    emit Influence->setValue(rest->Influence);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjRestr::~ObjRestr()
{
    // no need to delete child widgets, Qt does it all for us
}

void ObjRestr::on_OrbAdd_valueChanged(double d)
{
    Rest->OrbAdd = d;
}

void ObjRestr::on_Influence_valueChanged(int i)
{
    Rest->Influence = i;
}

bool ObjRestr::IfRestrict() const
{
    return Rest->Rest;
}

ObjRestList::ObjRestList(QWidget* parent) : QScrollArea(parent)
{
    Qw = new QWidget(this);
    setWidget(Qw);
    Cnt = 0;
}

void ObjRestList::FillList(struct Rest* rest, int first, int last)
{
    for (int i = first; i <= last; i++)
    {
        Or[i] = new ObjRestr(Qw, &rest[i], i);
        Or[i]->move(0, Yi);
        Yi += H;
        ++Cnt;
    }
}

void ObjRestList::Init(struct Rest* rest)
{
    int w;
    Rest = rest;
    Or[Sun] = new ObjRestr(Qw, &rest[Sun], Sun);
    w = Or[Sun]->width() - 5;
    Yi = H = Or[Sun]->height();
    FillList(rest, Moon, Last_Planet);
    FillList(rest, First_Extra, Asr->LastExtra);
    FillList(rest, XPoint, House_12);
    FillList(rest, First_Star, Final_Star-1);
    Qw->resize(w, H * (Cnt + 1));
}

ObjRestList::~ObjRestList()
{
}

void ObjRestr::on_IsRestricted_toggled(bool b)
{
    Rest->Rest = !b;
}

void ObjRestList::GetLen(int* a, int* b, int* c, int *d) const
{
    const ObjRestr& ors = *Or[Sun];
    *a = ors.IsRestricted->x();
    *b = ors.OrbAdd->x() - *a;
    *c = ors.Influence->x() - ors.OrbAdd->x();
    *d = width() - ors.Influence->x();
}

void ObjRestList::Inhibit(int i, bool b)
{
    ObjRestr& ori = *Or[i];
    emit ori.Name->setEnabled(!b);
    emit ori.IsRestricted->setEnabled(!b);
    emit ori.Influence->setEnabled(!b);
    emit ori.OrbAdd->setEnabled(!b);
}

void ObjRestList::Check(int i, bool b)
{
    emit Or[i]->IsRestricted->setChecked(b);
}
