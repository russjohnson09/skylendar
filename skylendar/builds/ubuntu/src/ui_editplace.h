/********************************************************************************
** Form generated from reading UI file 'editplace.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPLACE_H
#define UI_EDITPLACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditPlace
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *SearchList;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *PlaceName;
    QLineEdit *Latitude;
    QLineEdit *Longitude;
    QDoubleSpinBox *Altitude;
    QPushButton *ExtSearch;
    QLabel *label_4;
    QComboBox *Country;
    QPushButton *SearchButton;
    QPushButton *NewButton;
    QPushButton *DeleteButton;
    QPushButton *ModifyButton;
    QPushButton *CleanButton;
    QPushButton *CountryButton;

    void setupUi(QWidget *EditPlace)
    {
        if (EditPlace->objectName().isEmpty())
            EditPlace->setObjectName(QStringLiteral("EditPlace"));
        EditPlace->resize(587, 269);
        gridLayout = new QGridLayout(EditPlace);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        SearchList = new QTreeWidget(EditPlace);
        SearchList->setObjectName(QStringLiteral("SearchList"));
        SearchList->setMaximumSize(QSize(16777215, 32767));

        gridLayout->addWidget(SearchList, 0, 0, 1, 10);

        label = new QLabel(EditPlace);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(EditPlace);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 5, 1, 1);

        label_3 = new QLabel(EditPlace);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 7, 1, 1);

        label_5 = new QLabel(EditPlace);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 9, 1, 1);

        PlaceName = new QLineEdit(EditPlace);
        PlaceName->setObjectName(QStringLiteral("PlaceName"));
        PlaceName->setMaximumSize(QSize(16777215, 32767));

        gridLayout->addWidget(PlaceName, 2, 0, 1, 5);

        Latitude = new QLineEdit(EditPlace);
        Latitude->setObjectName(QStringLiteral("Latitude"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Latitude->sizePolicy().hasHeightForWidth());
        Latitude->setSizePolicy(sizePolicy);
        Latitude->setMaximumSize(QSize(90, 32767));
        Latitude->setAlignment(Qt::AlignRight);

        gridLayout->addWidget(Latitude, 2, 5, 1, 2);

        Longitude = new QLineEdit(EditPlace);
        Longitude->setObjectName(QStringLiteral("Longitude"));
        sizePolicy.setHeightForWidth(Longitude->sizePolicy().hasHeightForWidth());
        Longitude->setSizePolicy(sizePolicy);
        Longitude->setMaximumSize(QSize(90, 32767));
        Longitude->setAlignment(Qt::AlignRight);

        gridLayout->addWidget(Longitude, 2, 7, 1, 2);

        Altitude = new QDoubleSpinBox(EditPlace);
        Altitude->setObjectName(QStringLiteral("Altitude"));
        sizePolicy.setHeightForWidth(Altitude->sizePolicy().hasHeightForWidth());
        Altitude->setSizePolicy(sizePolicy);
        Altitude->setMaximumSize(QSize(90, 32767));
        Altitude->setMinimum(-10000);
        Altitude->setMaximum(10000);

        gridLayout->addWidget(Altitude, 2, 9, 1, 1);

        ExtSearch = new QPushButton(EditPlace);
        ExtSearch->setObjectName(QStringLiteral("ExtSearch"));
        ExtSearch->setEnabled(false);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        ExtSearch->setFont(font);

        gridLayout->addWidget(ExtSearch, 3, 0, 1, 2);

        label_4 = new QLabel(EditPlace);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 2, 1, 1);

        Country = new QComboBox(EditPlace);
        Country->setObjectName(QStringLiteral("Country"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(255);
        sizePolicy1.setVerticalStretch(255);
        sizePolicy1.setHeightForWidth(Country->sizePolicy().hasHeightForWidth());
        Country->setSizePolicy(sizePolicy1);
        Country->setMaximumSize(QSize(32767, 32767));

        gridLayout->addWidget(Country, 3, 3, 1, 7);

        SearchButton = new QPushButton(EditPlace);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(SearchButton->sizePolicy().hasHeightForWidth());
        SearchButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(SearchButton, 4, 0, 1, 1);

        NewButton = new QPushButton(EditPlace);
        NewButton->setObjectName(QStringLiteral("NewButton"));
        sizePolicy2.setHeightForWidth(NewButton->sizePolicy().hasHeightForWidth());
        NewButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(NewButton, 4, 1, 1, 1);

        DeleteButton = new QPushButton(EditPlace);
        DeleteButton->setObjectName(QStringLiteral("DeleteButton"));
        sizePolicy2.setHeightForWidth(DeleteButton->sizePolicy().hasHeightForWidth());
        DeleteButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(DeleteButton, 4, 2, 1, 2);

        ModifyButton = new QPushButton(EditPlace);
        ModifyButton->setObjectName(QStringLiteral("ModifyButton"));
        sizePolicy2.setHeightForWidth(ModifyButton->sizePolicy().hasHeightForWidth());
        ModifyButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(ModifyButton, 4, 4, 1, 2);

        CleanButton = new QPushButton(EditPlace);
        CleanButton->setObjectName(QStringLiteral("CleanButton"));
        sizePolicy2.setHeightForWidth(CleanButton->sizePolicy().hasHeightForWidth());
        CleanButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(CleanButton, 4, 6, 1, 2);

        CountryButton = new QPushButton(EditPlace);
        CountryButton->setObjectName(QStringLiteral("CountryButton"));
        sizePolicy2.setHeightForWidth(CountryButton->sizePolicy().hasHeightForWidth());
        CountryButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(CountryButton, 4, 8, 1, 2);

        QWidget::setTabOrder(PlaceName, Latitude);
        QWidget::setTabOrder(Latitude, Longitude);
        QWidget::setTabOrder(Longitude, Country);

        retranslateUi(EditPlace);

        QMetaObject::connectSlotsByName(EditPlace);
    } // setupUi

    void retranslateUi(QWidget *EditPlace)
    {
        EditPlace->setWindowTitle(QApplication::translate("EditPlace", "Place Edit", 0));
        QTreeWidgetItem *___qtreewidgetitem = SearchList->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("EditPlace", "Longitude", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("EditPlace", "Latitude", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("EditPlace", "Comment", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("EditPlace", "Country", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("EditPlace", "Name", 0));
        label->setText(QApplication::translate("EditPlace", "Name", 0));
        label_2->setText(QApplication::translate("EditPlace", "Latitude", 0));
        label_3->setText(QApplication::translate("EditPlace", "Longitude", 0));
        label_5->setText(QApplication::translate("EditPlace", "Altitude", 0));
#ifndef QT_NO_TOOLTIP
        ExtSearch->setToolTip(QApplication::translate("EditPlace", "Search Place on the net", 0));
#endif // QT_NO_TOOLTIP
        ExtSearch->setText(QApplication::translate("EditPlace", "Extended Search", 0));
        label_4->setText(QApplication::translate("EditPlace", "Country", 0));
#ifndef QT_NO_TOOLTIP
        Country->setToolTip(QApplication::translate("EditPlace", "Country name", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        SearchButton->setToolTip(QApplication::translate("EditPlace", "Search for places names", 0));
#endif // QT_NO_TOOLTIP
        SearchButton->setText(QApplication::translate("EditPlace", "Search", 0));
#ifndef QT_NO_TOOLTIP
        NewButton->setToolTip(QApplication::translate("EditPlace", "New place", 0));
#endif // QT_NO_TOOLTIP
        NewButton->setText(QApplication::translate("EditPlace", "New", 0));
#ifndef QT_NO_TOOLTIP
        DeleteButton->setToolTip(QApplication::translate("EditPlace", "Delete current place", 0));
#endif // QT_NO_TOOLTIP
        DeleteButton->setText(QApplication::translate("EditPlace", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        ModifyButton->setToolTip(QApplication::translate("EditPlace", "Modify current place", 0));
#endif // QT_NO_TOOLTIP
        ModifyButton->setText(QApplication::translate("EditPlace", "Modify", 0));
        CleanButton->setText(QApplication::translate("EditPlace", "Clean", 0));
        CountryButton->setText(QApplication::translate("EditPlace", "Edit Country", 0));
    } // retranslateUi

};

namespace Ui {
    class EditPlace: public Ui_EditPlace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPLACE_H
