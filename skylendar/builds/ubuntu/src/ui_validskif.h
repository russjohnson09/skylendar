/********************************************************************************
** Form generated from reading UI file 'validskif.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALIDSKIF_H
#define UI_VALIDSKIF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ValidSKIF
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *spacerItem;
    QLabel *Name;
    QSpacerItem *spacerItem1;
    QGroupBox *ChartType;
    QGridLayout *gridLayout1;
    QLabel *label_7;
    QLabel *ChartTypeText;
    QComboBox *ChartTypeBox;
    QLabel *label;
    QGroupBox *Country;
    QGridLayout *gridLayout2;
    QLabel *label_8;
    QLabel *CountryText;
    QPushButton *CountryButton;
    QLabel *label_2;
    QGroupBox *Place;
    QGridLayout *gridLayout3;
    QLabel *label_9;
    QLabel *PlaceText;
    QLabel *label_3;
    QPushButton *CancelButton;
    QSpacerItem *spacerItem2;
    QPushButton *Next;

    void setupUi(QDialog *ValidSKIF)
    {
        if (ValidSKIF->objectName().isEmpty())
            ValidSKIF->setObjectName(QStringLiteral("ValidSKIF"));
        ValidSKIF->resize(505, 369);
        gridLayout = new QGridLayout(ValidSKIF);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spacerItem = new QSpacerItem(160, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 0, 1, 2);

        Name = new QLabel(ValidSKIF);
        Name->setObjectName(QStringLiteral("Name"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        Name->setFont(font);
        Name->setWordWrap(false);

        gridLayout->addWidget(Name, 0, 2, 1, 1);

        spacerItem1 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 0, 3, 1, 2);

        ChartType = new QGroupBox(ValidSKIF);
        ChartType->setObjectName(QStringLiteral("ChartType"));
        ChartType->setEnabled(false);
        gridLayout1 = new QGridLayout(ChartType);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        label_7 = new QLabel(ChartType);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/pics/attention.png")));

        gridLayout1->addWidget(label_7, 0, 0, 1, 1);

        ChartTypeText = new QLabel(ChartType);
        ChartTypeText->setObjectName(QStringLiteral("ChartTypeText"));
        ChartTypeText->setWordWrap(false);

        gridLayout1->addWidget(ChartTypeText, 0, 1, 1, 1);

        ChartTypeBox = new QComboBox(ChartType);
        ChartTypeBox->setObjectName(QStringLiteral("ChartTypeBox"));

        gridLayout1->addWidget(ChartTypeBox, 0, 2, 1, 1);

        label = new QLabel(ChartType);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(label, 1, 0, 1, 1);


        gridLayout->addWidget(ChartType, 1, 0, 1, 5);

        Country = new QGroupBox(ValidSKIF);
        Country->setObjectName(QStringLiteral("Country"));
        Country->setEnabled(false);
        gridLayout2 = new QGridLayout(Country);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        label_8 = new QLabel(Country);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/pics/attention.png")));

        gridLayout2->addWidget(label_8, 0, 0, 1, 1);

        CountryText = new QLabel(Country);
        CountryText->setObjectName(QStringLiteral("CountryText"));
        CountryText->setWordWrap(false);

        gridLayout2->addWidget(CountryText, 0, 1, 1, 1);

        CountryButton = new QPushButton(Country);
        CountryButton->setObjectName(QStringLiteral("CountryButton"));

        gridLayout2->addWidget(CountryButton, 0, 2, 1, 1);

        label_2 = new QLabel(Country);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout2->addWidget(label_2, 1, 0, 1, 1);


        gridLayout->addWidget(Country, 2, 0, 1, 5);

        Place = new QGroupBox(ValidSKIF);
        Place->setObjectName(QStringLiteral("Place"));
        Place->setEnabled(false);
        gridLayout3 = new QGridLayout(Place);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        label_9 = new QLabel(Place);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/pics/attention.png")));

        gridLayout3->addWidget(label_9, 0, 0, 1, 1);

        PlaceText = new QLabel(Place);
        PlaceText->setObjectName(QStringLiteral("PlaceText"));
        PlaceText->setWordWrap(false);

        gridLayout3->addWidget(PlaceText, 0, 1, 1, 1);

        label_3 = new QLabel(Place);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout3->addWidget(label_3, 1, 0, 1, 1);


        gridLayout->addWidget(Place, 3, 0, 1, 5);

        CancelButton = new QPushButton(ValidSKIF);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout->addWidget(CancelButton, 4, 0, 1, 1);

        spacerItem2 = new QSpacerItem(309, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem2, 4, 1, 1, 3);

        Next = new QPushButton(ValidSKIF);
        Next->setObjectName(QStringLiteral("Next"));

        gridLayout->addWidget(Next, 4, 4, 1, 1);


        retranslateUi(ValidSKIF);
        QObject::connect(CancelButton, SIGNAL(clicked()), ValidSKIF, SLOT(reject()));

        Next->setDefault(true);


        QMetaObject::connectSlotsByName(ValidSKIF);
    } // setupUi

    void retranslateUi(QDialog *ValidSKIF)
    {
        ValidSKIF->setWindowTitle(QApplication::translate("ValidSKIF", "SKIF file validation dialog box", 0));
        Name->setText(QString());
        ChartType->setTitle(QApplication::translate("ValidSKIF", "Chart Type Validation", 0));
        label_7->setText(QString());
        ChartTypeText->setText(QString());
        label->setText(QString());
        Country->setTitle(QApplication::translate("ValidSKIF", "Country Validation", 0));
        label_8->setText(QString());
        CountryText->setText(QString());
        CountryButton->setText(QApplication::translate("ValidSKIF", "Define Country", 0));
        label_2->setText(QString());
        Place->setTitle(QApplication::translate("ValidSKIF", "Place Validation", 0));
        label_9->setText(QString());
        PlaceText->setText(QString());
        label_3->setText(QString());
        CancelButton->setText(QApplication::translate("ValidSKIF", "Cancel", 0));
        Next->setText(QApplication::translate("ValidSKIF", "Next", 0));
    } // retranslateUi

};

namespace Ui {
    class ValidSKIF: public Ui_ValidSKIF {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALIDSKIF_H
