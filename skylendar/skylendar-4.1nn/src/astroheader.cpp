#include "astroheader.h"

#include <QGridLayout>
#include <QLabel>

AstroHeader::AstroHeader(QWidget* parent) : QWidget(parent)
{
    //Qgl = new QGridLayout(this);
    //Qgl->setSpacing(1);
    Xi = 0;
}

void AstroHeader::Add(const QString& qs, int length, bool textlength)
{
	auto ql = new QLabel(this);
    ql->setGeometry(Xi, 1, textlength ? (qs.length() * 8) + 6: length + 4, height() -2);
    Xi += length + 2;
    ql->setFrameShape(QFrame::Panel);
    ql->setFrameShadow(QFrame::Raised);
    ql->setText(qs);
    //ql->setMaximumWidth(length);
    //Qgl->addWidget(ql, 0, X++, 1, 1);
}
