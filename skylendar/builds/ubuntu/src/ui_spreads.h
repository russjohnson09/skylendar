/********************************************************************************
** Form generated from reading UI file 'spreads.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPREADS_H
#define UI_SPREADS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Spreads
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *Choice1;
    QGridLayout *gridLayout;
    QRadioButton *Cross_Shaped;
    QRadioButton *Horse_Shoe;
    QRadioButton *Pyramid;
    QRadioButton *Wheel;
    QRadioButton *Celtic;
    QPushButton *OkButton;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *Spreads)
    {
        if (Spreads->objectName().isEmpty())
            Spreads->setObjectName(QStringLiteral("Spreads"));
        Spreads->resize(136, 198);
        gridLayout_2 = new QGridLayout(Spreads);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Choice1 = new QGroupBox(Spreads);
        Choice1->setObjectName(QStringLiteral("Choice1"));
        gridLayout = new QGridLayout(Choice1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Cross_Shaped = new QRadioButton(Choice1);
        Cross_Shaped->setObjectName(QStringLiteral("Cross_Shaped"));

        gridLayout->addWidget(Cross_Shaped, 0, 0, 1, 1);

        Horse_Shoe = new QRadioButton(Choice1);
        Horse_Shoe->setObjectName(QStringLiteral("Horse_Shoe"));

        gridLayout->addWidget(Horse_Shoe, 1, 0, 1, 1);

        Pyramid = new QRadioButton(Choice1);
        Pyramid->setObjectName(QStringLiteral("Pyramid"));

        gridLayout->addWidget(Pyramid, 2, 0, 1, 1);

        Wheel = new QRadioButton(Choice1);
        Wheel->setObjectName(QStringLiteral("Wheel"));

        gridLayout->addWidget(Wheel, 3, 0, 1, 1);

        Celtic = new QRadioButton(Choice1);
        Celtic->setObjectName(QStringLiteral("Celtic"));

        gridLayout->addWidget(Celtic, 4, 0, 1, 1);


        gridLayout_2->addWidget(Choice1, 0, 0, 1, 2);

        OkButton = new QPushButton(Spreads);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout_2->addWidget(OkButton, 1, 0, 1, 1);

        spacerItem = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(spacerItem, 1, 1, 1, 1);


        retranslateUi(Spreads);
        QObject::connect(OkButton, SIGNAL(clicked()), Spreads, SLOT(accept()));

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(Spreads);
    } // setupUi

    void retranslateUi(QDialog *Spreads)
    {
        Spreads->setWindowTitle(QApplication::translate("Spreads", "Select a Spread", 0));
        Choice1->setTitle(QApplication::translate("Spreads", "Choice", 0));
        Cross_Shaped->setText(QApplication::translate("Spreads", "Cross Shaped", 0));
        Horse_Shoe->setText(QApplication::translate("Spreads", "Horse Shoe", 0));
        Pyramid->setText(QApplication::translate("Spreads", "The Pyramid", 0));
        Wheel->setText(QApplication::translate("Spreads", "The Wheel", 0));
        Celtic->setText(QApplication::translate("Spreads", "Celtic", 0));
        OkButton->setText(QApplication::translate("Spreads", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class Spreads: public Ui_Spreads {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPREADS_H
