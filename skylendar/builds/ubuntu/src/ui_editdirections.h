/********************************************************************************
** Form generated from reading UI file 'editdirections.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDIRECTIONS_H
#define UI_EDITDIRECTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_EditDirections
{
public:
    QGridLayout *gridLayout;
    QComboBox *House;
    QSpacerItem *horizontalSpacer;
    QComboBox *DirType;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *StatKey;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *CustVal;
    QLabel *label;
    QCheckBox *Converse;
    QCheckBox *Dump;
    QPushButton *OkButton;

    void setupUi(QDialog *EditDirections)
    {
        if (EditDirections->objectName().isEmpty())
            EditDirections->setObjectName(QStringLiteral("EditDirections"));
        EditDirections->resize(247, 247);
        gridLayout = new QGridLayout(EditDirections);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        House = new QComboBox(EditDirections);
        House->setObjectName(QStringLiteral("House"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(House->sizePolicy().hasHeightForWidth());
        House->setSizePolicy(sizePolicy);

        gridLayout->addWidget(House, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        DirType = new QComboBox(EditDirections);
        DirType->setObjectName(QStringLiteral("DirType"));

        gridLayout->addWidget(DirType, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        StatKey = new QComboBox(EditDirections);
        StatKey->setObjectName(QStringLiteral("StatKey"));

        gridLayout->addWidget(StatKey, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        CustVal = new QDoubleSpinBox(EditDirections);
        CustVal->setObjectName(QStringLiteral("CustVal"));
        CustVal->setEnabled(false);
        CustVal->setDecimals(4);
        CustVal->setMaximum(9999.99);

        gridLayout->addWidget(CustVal, 3, 0, 1, 1);

        label = new QLabel(EditDirections);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 1, 1, 1);

        Converse = new QCheckBox(EditDirections);
        Converse->setObjectName(QStringLiteral("Converse"));

        gridLayout->addWidget(Converse, 4, 0, 1, 1);

        Dump = new QCheckBox(EditDirections);
        Dump->setObjectName(QStringLiteral("Dump"));

        gridLayout->addWidget(Dump, 5, 0, 1, 1);

        OkButton = new QPushButton(EditDirections);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 6, 0, 1, 1);


        retranslateUi(EditDirections);
        QObject::connect(OkButton, SIGNAL(clicked()), EditDirections, SLOT(accept()));

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(EditDirections);
    } // setupUi

    void retranslateUi(QDialog *EditDirections)
    {
        EditDirections->setWindowTitle(QApplication::translate("EditDirections", "Parameters for directions", 0));
        House->clear();
        House->insertItems(0, QStringList()
         << QApplication::translate("EditDirections", "Regiomontanus", 0)
         << QApplication::translate("EditDirections", "Placidus", 0)
         << QApplication::translate("EditDirections", "Campanus", 0)
        );
        DirType->clear();
        DirType->insertItems(0, QStringList()
         << QApplication::translate("EditDirections", "Mundane", 0)
         << QApplication::translate("EditDirections", "Zodiacal", 0)
        );
        StatKey->clear();
        StatKey->insertItems(0, QStringList()
         << QApplication::translate("EditDirections", "Ptolemy", 0)
         << QApplication::translate("EditDirections", "Naibod", 0)
         << QApplication::translate("EditDirections", "Simmonite", 0)
         << QApplication::translate("EditDirections", "Placidian", 0)
         << QApplication::translate("EditDirections", "Cardan", 0)
         << QApplication::translate("EditDirections", "Synodic", 0)
         << QApplication::translate("EditDirections", "Custom", 0)
        );
        label->setText(QApplication::translate("EditDirections", "Custom Value", 0));
        Converse->setText(QApplication::translate("EditDirections", "Converse", 0));
        Dump->setText(QApplication::translate("EditDirections", "Dump into AspTbl", 0));
        OkButton->setText(QApplication::translate("EditDirections", "Proceed", 0));
    } // retranslateUi

};

namespace Ui {
    class EditDirections: public Ui_EditDirections {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDIRECTIONS_H
