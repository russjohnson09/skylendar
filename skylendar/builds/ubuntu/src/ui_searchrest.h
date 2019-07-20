/********************************************************************************
** Form generated from reading UI file 'searchrest.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHREST_H
#define UI_SEARCHREST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchRest
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *RestList;
    QLineEdit *ReqLine;
    QPushButton *OkButton;
    QPushButton *SearchButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *SearchRest)
    {
        if (SearchRest->objectName().isEmpty())
            SearchRest->setObjectName(QStringLiteral("SearchRest"));
        SearchRest->resize(345, 342);
        gridLayout = new QGridLayout(SearchRest);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        RestList = new QTreeWidget(SearchRest);
        RestList->setObjectName(QStringLiteral("RestList"));
        RestList->setIndentation(0);

        gridLayout->addWidget(RestList, 0, 0, 1, 3);

        ReqLine = new QLineEdit(SearchRest);
        ReqLine->setObjectName(QStringLiteral("ReqLine"));

        gridLayout->addWidget(ReqLine, 1, 0, 1, 3);

        OkButton = new QPushButton(SearchRest);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 2, 0, 1, 1);

        SearchButton = new QPushButton(SearchRest);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));

        gridLayout->addWidget(SearchButton, 2, 1, 1, 1);

        CancelButton = new QPushButton(SearchRest);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout->addWidget(CancelButton, 2, 2, 1, 1);

        QWidget::setTabOrder(ReqLine, OkButton);
        QWidget::setTabOrder(OkButton, SearchButton);
        QWidget::setTabOrder(SearchButton, CancelButton);

        retranslateUi(SearchRest);

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(SearchRest);
    } // setupUi

    void retranslateUi(QDialog *SearchRest)
    {
        SearchRest->setWindowTitle(QApplication::translate("SearchRest", "Search for Restrictions set", 0));
        QTreeWidgetItem *___qtreewidgetitem = RestList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("SearchRest", "Name", 0));
        OkButton->setText(QApplication::translate("SearchRest", "Ok", 0));
        SearchButton->setText(QApplication::translate("SearchRest", "Search", 0));
        CancelButton->setText(QApplication::translate("SearchRest", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchRest: public Ui_SearchRest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHREST_H
