/********************************************************************************
** Form generated from reading UI file 'asprestr.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASPRESTR_H
#define UI_ASPRESTR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AspRestr
{
public:
    QPushButton *ColorButton;
    QSpinBox *Influence;
    QCheckBox *IsRestricted;
    QLabel *Name;
    QDoubleSpinBox *Orb;

    void setupUi(QWidget *AspRestr)
    {
        if (AspRestr->objectName().isEmpty())
            AspRestr->setObjectName(QStringLiteral("AspRestr"));
        AspRestr->resize(301, 26);
        ColorButton = new QPushButton(AspRestr);
        ColorButton->setObjectName(QStringLiteral("ColorButton"));
        ColorButton->setGeometry(QRect(250, 0, 50, 22));
        Influence = new QSpinBox(AspRestr);
        Influence->setObjectName(QStringLiteral("Influence"));
        Influence->setGeometry(QRect(190, 0, 50, 20));
        Influence->setMaximum(50);
        IsRestricted = new QCheckBox(AspRestr);
        IsRestricted->setObjectName(QStringLiteral("IsRestricted"));
        IsRestricted->setGeometry(QRect(100, 0, 20, 20));
        Name = new QLabel(AspRestr);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setGeometry(QRect(0, 0, 90, 20));
        Name->setWordWrap(false);
        Orb = new QDoubleSpinBox(AspRestr);
        Orb->setObjectName(QStringLiteral("Orb"));
        Orb->setGeometry(QRect(120, 0, 62, 23));
        Orb->setMinimum(0.01);
        Orb->setMaximum(12);
        Orb->setValue(4);
        QWidget::setTabOrder(IsRestricted, Influence);
        QWidget::setTabOrder(Influence, ColorButton);

        retranslateUi(AspRestr);

        QMetaObject::connectSlotsByName(AspRestr);
    } // setupUi

    void retranslateUi(QWidget *AspRestr)
    {
        AspRestr->setWindowTitle(QApplication::translate("AspRestr", "AspRestr", 0));
        ColorButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        Influence->setToolTip(QApplication::translate("AspRestr", "Aspect Influence between 0..50", 0));
#endif // QT_NO_TOOLTIP
        IsRestricted->setText(QString());
        Name->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AspRestr: public Ui_AspRestr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASPRESTR_H
