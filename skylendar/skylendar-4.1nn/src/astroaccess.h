#ifndef ASTROACCESS_H
#define ASTROACCESS_H

#include "ui_access.h"
#include <astroresources.h>

class AstroAccess : public QWidget, public Ui_AstroAccess
{
	Q_OBJECT

 public:

	inline AstroAccess(QWidget* parent) : QWidget(parent)
	{
		setupUi(this);
		SetOwnerAccess(Asr->DbUser);
	}

void SetOwnerAccess(const AstroString& name, enum Access a = Private)
	{
		Owner->setText(name);
		Access->setCurrentIndex(int(a));
		//Access->setDisabled(name != Asr->DbUser);
	}

	enum Access GetAccess() const { return (enum Access)Access->currentIndex(); }
};
#endif
