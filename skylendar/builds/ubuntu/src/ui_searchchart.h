/********************************************************************************
** Form generated from reading UI file 'searchchart.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHCHART_H
#define UI_SEARCHCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchChart
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *ChartList;
    QLineEdit *ReqLine;
    QCheckBox *SQLStatement;
    QPushButton *Destroy;
    QPushButton *OkButton;
    QPushButton *SearchButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *SearchChart)
    {
        if (SearchChart->objectName().isEmpty())
            SearchChart->setObjectName(QStringLiteral("SearchChart"));
        SearchChart->resize(311, 361);
        gridLayout = new QGridLayout(SearchChart);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ChartList = new QTreeWidget(SearchChart);
        ChartList->setObjectName(QStringLiteral("ChartList"));
        ChartList->setIndentation(0);

        gridLayout->addWidget(ChartList, 0, 0, 1, 3);

        ReqLine = new QLineEdit(SearchChart);
        ReqLine->setObjectName(QStringLiteral("ReqLine"));

        gridLayout->addWidget(ReqLine, 1, 0, 1, 3);

        SQLStatement = new QCheckBox(SearchChart);
        SQLStatement->setObjectName(QStringLiteral("SQLStatement"));

        gridLayout->addWidget(SQLStatement, 2, 0, 1, 2);

        Destroy = new QPushButton(SearchChart);
        Destroy->setObjectName(QStringLiteral("Destroy"));

        gridLayout->addWidget(Destroy, 2, 2, 1, 1);

        OkButton = new QPushButton(SearchChart);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 3, 0, 1, 1);

        SearchButton = new QPushButton(SearchChart);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));
        SearchButton->setAutoDefault(false);

        gridLayout->addWidget(SearchButton, 3, 1, 1, 1);

        CancelButton = new QPushButton(SearchChart);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setAutoDefault(false);

        gridLayout->addWidget(CancelButton, 3, 2, 1, 1);

        QWidget::setTabOrder(ReqLine, OkButton);
        QWidget::setTabOrder(OkButton, SearchButton);
        QWidget::setTabOrder(SearchButton, CancelButton);

        retranslateUi(SearchChart);

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(SearchChart);
    } // setupUi

    void retranslateUi(QDialog *SearchChart)
    {
        SearchChart->setWindowTitle(QApplication::translate("SearchChart", "Search for Chart", 0));
        QTreeWidgetItem *___qtreewidgetitem = ChartList->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("SearchChart", "Date", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("SearchChart", "Name", 0));
        SQLStatement->setText(QApplication::translate("SearchChart", "SQL Statement", 0));
        Destroy->setText(QApplication::translate("SearchChart", "Destroy Chart", 0));
        OkButton->setText(QApplication::translate("SearchChart", "Ok", 0));
        SearchButton->setText(QApplication::translate("SearchChart", "Search", 0));
        CancelButton->setText(QApplication::translate("SearchChart", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchChart: public Ui_SearchChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHCHART_H
