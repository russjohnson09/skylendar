#include "asprestr.h"
#include "astroaspects.h"
#include "astroresources.h"
#include "astroutils.h"
#include "astrographics.h"
#include <QLabel>
#include <QPixmap>
#include <QCursor>
#include <QPushButton>
#include <QSpinBox>
#include <QActionGroup>
#include <cstdlib>

/*
 *  Constructs a AspRest which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */

AspRest::AspRest(AspRestList* arl, int i) : QWidget(arl->Backg)
{
    Arl = arl;
    Item = i;
    const struct AspectRestrictions& asrt = Arl->Asrt[i];
    setupUi(this);
    emit Name->setText(*Asr->AspectNames[i]);
    emit IsRestricted->setChecked(!asrt.Rest);
    emit Orb->setValue(asrt.Orb);
    emit Influence->setValue(asrt.Influence);
    emit ColorButton->setIcon(COL % asrt.Color);
}

AspRest::~AspRest()
{
    /*	struct AspectRestrictions& asrt = Arl->Asrt[Item];
    	asrt.Orb = Orb->value();
    	asrt.Influence = Influence->value();*/
}

void AspRest::on_Orb_valueChanged(double d)
{
    Arl->Asrt[Item].Orb = d;
}

void AspRest::on_Influence_valueChanged(int i)
{
    Arl->Asrt[Item].Influence = i;
}

AspRestList::AspRestList(QWidget* parent) : QScrollArea(parent)
{
    QString s;
    QAction* qa;
    Backg = new QWidget(this);
    Qag = new QActionGroup(&Qppm);
    setWidget(Backg);
    Qag->setExclusive(true);
    connect(Qag, SIGNAL(triggered(QAction*)), this, SLOT(Triggered(QAction*)));
    for (int i = 0; i < 16; i++)
    {
        qa = Qppm.addAction(SC(const QIcon&, COL % i), "");
        qa->setCheckable(true);
        qa->setData(i);
        Qag->addAction(qa);
    }
}

AspRestList::~AspRestList()
{
}

void AspRestList::Init(struct AspectRestrictions* asrt)
{
    int w;
    Asrt = asrt;
    Ar[Conjunction] = new AspRest(this, Conjunction);
    w = Ar[Conjunction]->width();
    Y = H = Ar[Conjunction]->height();
    Backg->resize(w, H * Unknown_Aspect -1);
    FillList(Opposition, Unknown_Aspect);
}

void AspRestList::Triggered(QAction* qa)
{
    int i = qa->data().toInt();
    Asrt[Item].Color = i;
    qa->setChecked(true);
    emit Ar[Item]->ColorButton->setIcon(COL % i);
}

void AspRestList::GetLen(int* a, int* b, int* c, int *d, int *e) const
{
    const AspRest& arc = *Ar[Conjunction];
    *a = arc.IsRestricted->x();
    *b = arc.Orb->x() - *a;
    *c = arc.Influence->x() - arc.Orb->x();
    *d = arc.ColorButton->x()- arc.Influence->x();
    *e = width() - arc.ColorButton->x(); //width();
}

void AspRestList::Inhibit(int i, bool b)
{
    AspRest& ari = *Ar[i];
    emit ari.Name->setEnabled(!b);
    emit ari.IsRestricted->setEnabled(!b);
    emit ari.Influence->setEnabled(!b);
    emit ari.Orb->setEnabled(!b);
    emit ari.ColorButton->setEnabled(!b);
}

void AspRestList::Check(int i, bool b)
{
    emit Ar[i]->IsRestricted->setChecked(b);
    Asrt[i].Rest = b;
}

void AspRestList::FillList(int first, int last)
{
    for (int i = first; i < last; i++)
    {
        Ar[i] = new AspRest(this, i);
        Ar[i]->move(0, Y);
        Y += H;
    }
}

/*
 * public slot
 */
void AspRest::on_IsRestricted_toggled(bool b)
{
    Arl->Asrt[Item].Rest = !b;
}

/*
 * public slot
 */
void AspRest::on_ColorButton_pressed()
{
    const QList<QAction*> qa = Arl->Qppm.actions();
    Arl->Item = Item;
    for (QList<QAction *>::const_iterator i = qa.constBegin(); i != qa.constEnd(); ++i)
        if ((*i)->data().toInt() == Arl->Asrt[Item].Color)
        {
            (*i)->setChecked(true);
            break;
        }
    Arl->Qppm.exec(QCursor::pos(), Arl->Qag->checkedAction());
}

bool AspRestList::IsChecked(int i) const
{
    return Ar[i]->IsRestricted->isChecked();
}
