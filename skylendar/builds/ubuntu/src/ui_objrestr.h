/********************************************************************************
** Form generated from reading UI file 'objrestr.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJRESTR_H
#define UI_OBJRESTR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjRestr
{
public:
    QCheckBox *IsRestricted;
    QLabel *Name;
    QSpinBox *Influence;
    QDoubleSpinBox *OrbAdd;

    void setupUi(QWidget *ObjRestr)
    {
        if (ObjRestr->objectName().isEmpty())
            ObjRestr->setObjectName(QStringLiteral("ObjRestr"));
        ObjRestr->resize(260, 26);
        IsRestricted = new QCheckBox(ObjRestr);
        IsRestricted->setObjectName(QStringLiteral("IsRestricted"));
        IsRestricted->setGeometry(QRect(100, 0, 20, 20));
        Name = new QLabel(ObjRestr);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setGeometry(QRect(0, 0, 90, 20));
        Name->setWordWrap(false);
        Influence = new QSpinBox(ObjRestr);
        Influence->setObjectName(QStringLiteral("Influence"));
        Influence->setGeometry(QRect(200, 0, 50, 20));
        Influence->setMaximum(50);
        OrbAdd = new QDoubleSpinBox(ObjRestr);
        OrbAdd->setObjectName(QStringLiteral("OrbAdd"));
        OrbAdd->setGeometry(QRect(130, 0, 58, 20));

        retranslateUi(ObjRestr);

        QMetaObject::connectSlotsByName(ObjRestr);
    } // setupUi

    void retranslateUi(QWidget *ObjRestr)
    {
        ObjRestr->setWindowTitle(QApplication::translate("ObjRestr", "ObjRestr", 0));
        IsRestricted->setText(QString());
        Name->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ObjRestr: public Ui_ObjRestr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJRESTR_H
