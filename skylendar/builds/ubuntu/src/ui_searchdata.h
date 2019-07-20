/********************************************************************************
** Form generated from reading UI file 'searchdata.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDATA_H
#define UI_SEARCHDATA_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchData
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QTreeWidget *DataLIST;
    QGroupBox *RequestType;
    QGridLayout *gridLayout2;
    QRadioButton *ByNameButton;
    QRadioButton *ByVDVButton;
    QRadioButton *ByStatementButton;
    QTextEdit *ReqLine;
    QGroupBox *VDVGroup;
    QGridLayout *gridLayout3;
    QPushButton *SiblButton;
    QPushButton *DeleteButton;
    QPushButton *DumpValButton;
    QPushButton *OkButton;
    QPushButton *SearchButton;
    QPushButton *CancelButton;
    QLabel *textLabel1;
    QLabel *Count;
    QGroupBox *VDVFunc;
    QGridLayout *gridLayout4;
    QComboBox *Planets;
    QComboBox *Aspects;
    QPushButton *TObjButton;
    QPushButton *TAspButton;
    QPushButton *TRestButton;
    QPushButton *THouseButton;
    QPushButton *ANDButton;
    QPushButton *ORButton;
    QPushButton *NOTButton;

    void setupUi(QDialog *SearchData)
    {
        if (SearchData->objectName().isEmpty())
            SearchData->setObjectName(QStringLiteral("SearchData"));
        SearchData->resize(544, 506);
        gridLayout = new QGridLayout(SearchData);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(SearchData);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout1 = new QGridLayout(groupBox);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        DataLIST = new QTreeWidget(groupBox);
        DataLIST->setObjectName(QStringLiteral("DataLIST"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DataLIST->sizePolicy().hasHeightForWidth());
        DataLIST->setSizePolicy(sizePolicy1);

        gridLayout1->addWidget(DataLIST, 0, 0, 1, 1);

        RequestType = new QGroupBox(groupBox);
        RequestType->setObjectName(QStringLiteral("RequestType"));
        gridLayout2 = new QGridLayout(RequestType);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        ByNameButton = new QRadioButton(RequestType);
        ByNameButton->setObjectName(QStringLiteral("ByNameButton"));

        gridLayout2->addWidget(ByNameButton, 0, 0, 1, 1);

        ByVDVButton = new QRadioButton(RequestType);
        ByVDVButton->setObjectName(QStringLiteral("ByVDVButton"));

        gridLayout2->addWidget(ByVDVButton, 0, 2, 1, 1);

        ByStatementButton = new QRadioButton(RequestType);
        ByStatementButton->setObjectName(QStringLiteral("ByStatementButton"));

        gridLayout2->addWidget(ByStatementButton, 0, 1, 1, 1);


        gridLayout1->addWidget(RequestType, 1, 0, 1, 1);

        ReqLine = new QTextEdit(groupBox);
        ReqLine->setObjectName(QStringLiteral("ReqLine"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ReqLine->sizePolicy().hasHeightForWidth());
        ReqLine->setSizePolicy(sizePolicy2);
        ReqLine->setMaximumSize(QSize(16777215, 90));

        gridLayout1->addWidget(ReqLine, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 2, 3);

        VDVGroup = new QGroupBox(SearchData);
        VDVGroup->setObjectName(QStringLiteral("VDVGroup"));
        gridLayout3 = new QGridLayout(VDVGroup);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        SiblButton = new QPushButton(VDVGroup);
        SiblButton->setObjectName(QStringLiteral("SiblButton"));

        gridLayout3->addWidget(SiblButton, 0, 0, 1, 1);

        DeleteButton = new QPushButton(VDVGroup);
        DeleteButton->setObjectName(QStringLiteral("DeleteButton"));

        gridLayout3->addWidget(DeleteButton, 1, 0, 1, 1);

        DumpValButton = new QPushButton(VDVGroup);
        DumpValButton->setObjectName(QStringLiteral("DumpValButton"));

        gridLayout3->addWidget(DumpValButton, 2, 0, 1, 1);


        gridLayout->addWidget(VDVGroup, 1, 3, 1, 2);

        OkButton = new QPushButton(SearchData);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 2, 0, 1, 1);

        SearchButton = new QPushButton(SearchData);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));
        SearchButton->setAutoDefault(false);

        gridLayout->addWidget(SearchButton, 2, 1, 1, 1);

        CancelButton = new QPushButton(SearchData);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setAutoDefault(false);

        gridLayout->addWidget(CancelButton, 2, 2, 1, 1);

        textLabel1 = new QLabel(SearchData);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 2, 3, 1, 1);

        Count = new QLabel(SearchData);
        Count->setObjectName(QStringLiteral("Count"));
        sizePolicy.setHeightForWidth(Count->sizePolicy().hasHeightForWidth());
        Count->setSizePolicy(sizePolicy);
        Count->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Count->setWordWrap(false);

        gridLayout->addWidget(Count, 2, 4, 1, 1);

        VDVFunc = new QGroupBox(SearchData);
        VDVFunc->setObjectName(QStringLiteral("VDVFunc"));
        gridLayout4 = new QGridLayout(VDVFunc);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName(QStringLiteral("gridLayout4"));
        Planets = new QComboBox(VDVFunc);
        Planets->setObjectName(QStringLiteral("Planets"));

        gridLayout4->addWidget(Planets, 0, 0, 1, 1);

        Aspects = new QComboBox(VDVFunc);
        Aspects->setObjectName(QStringLiteral("Aspects"));

        gridLayout4->addWidget(Aspects, 1, 0, 1, 1);

        TObjButton = new QPushButton(VDVFunc);
        TObjButton->setObjectName(QStringLiteral("TObjButton"));

        gridLayout4->addWidget(TObjButton, 2, 0, 1, 1);

        TAspButton = new QPushButton(VDVFunc);
        TAspButton->setObjectName(QStringLiteral("TAspButton"));

        gridLayout4->addWidget(TAspButton, 3, 0, 1, 1);

        TRestButton = new QPushButton(VDVFunc);
        TRestButton->setObjectName(QStringLiteral("TRestButton"));

        gridLayout4->addWidget(TRestButton, 4, 0, 1, 1);

        THouseButton = new QPushButton(VDVFunc);
        THouseButton->setObjectName(QStringLiteral("THouseButton"));

        gridLayout4->addWidget(THouseButton, 5, 0, 1, 1);

        ANDButton = new QPushButton(VDVFunc);
        ANDButton->setObjectName(QStringLiteral("ANDButton"));

        gridLayout4->addWidget(ANDButton, 6, 0, 1, 1);

        ORButton = new QPushButton(VDVFunc);
        ORButton->setObjectName(QStringLiteral("ORButton"));

        gridLayout4->addWidget(ORButton, 7, 0, 1, 1);

        NOTButton = new QPushButton(VDVFunc);
        NOTButton->setObjectName(QStringLiteral("NOTButton"));

        gridLayout4->addWidget(NOTButton, 8, 0, 1, 1);


        gridLayout->addWidget(VDVFunc, 0, 3, 1, 2);

        QWidget::setTabOrder(ByNameButton, ByStatementButton);
        QWidget::setTabOrder(ByStatementButton, ByVDVButton);
        QWidget::setTabOrder(ByVDVButton, Planets);
        QWidget::setTabOrder(Planets, Aspects);
        QWidget::setTabOrder(Aspects, TObjButton);
        QWidget::setTabOrder(TObjButton, TAspButton);
        QWidget::setTabOrder(TAspButton, TRestButton);
        QWidget::setTabOrder(TRestButton, THouseButton);
        QWidget::setTabOrder(THouseButton, ANDButton);
        QWidget::setTabOrder(ANDButton, ORButton);
        QWidget::setTabOrder(ORButton, NOTButton);
        QWidget::setTabOrder(NOTButton, SiblButton);
        QWidget::setTabOrder(SiblButton, DeleteButton);
        QWidget::setTabOrder(DeleteButton, DumpValButton);
        QWidget::setTabOrder(DumpValButton, OkButton);
        QWidget::setTabOrder(OkButton, SearchButton);
        QWidget::setTabOrder(SearchButton, CancelButton);

        retranslateUi(SearchData);

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(SearchData);
    } // setupUi

    void retranslateUi(QDialog *SearchData)
    {
        SearchData->setWindowTitle(QApplication::translate("SearchData", "Search for data", 0));
        groupBox->setTitle(QString());
        QTreeWidgetItem *___qtreewidgetitem = DataLIST->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("SearchData", "Place", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("SearchData", "Date", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("SearchData", "Name", 0));
        RequestType->setTitle(QApplication::translate("SearchData", "Type of request", 0));
#ifndef QT_NO_TOOLTIP
        ByNameButton->setToolTip(QApplication::translate("SearchData", "Criteria zone contains a name or a fragment of name", 0));
#endif // QT_NO_TOOLTIP
        ByNameButton->setText(QApplication::translate("SearchData", "By name", 0));
#ifndef QT_NO_TOOLTIP
        ByVDVButton->setToolTip(QApplication::translate("SearchData", "Criteria zone accepts specific VDV search arguments", 0));
#endif // QT_NO_TOOLTIP
        ByVDVButton->setText(QApplication::translate("SearchData", "By VDV", 0));
#ifndef QT_NO_TOOLTIP
        ByStatementButton->setToolTip(QApplication::translate("SearchData", "Criteria zone contains raw SQL WHERE clause", 0));
#endif // QT_NO_TOOLTIP
        ByStatementButton->setText(QApplication::translate("SearchData", "By SQL statement", 0));
        VDVGroup->setTitle(QApplication::translate("SearchData", "VDV Management", 0));
#ifndef QT_NO_TOOLTIP
        SiblButton->setToolTip(QApplication::translate("SearchData", "List all the siblings belonging to the first listed Dataset", 0));
#endif // QT_NO_TOOLTIP
        SiblButton->setText(QApplication::translate("SearchData", "Siblings", 0));
#ifndef QT_NO_TOOLTIP
        DeleteButton->setToolTip(QApplication::translate("SearchData", "DANGEROUS ! Delete listed Datasets or just purge their VDV associated values ", 0));
#endif // QT_NO_TOOLTIP
        DeleteButton->setText(QApplication::translate("SearchData", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        DumpValButton->setToolTip(QApplication::translate("SearchData", "Extact & Save the values from all the displayed datasets", 0));
#endif // QT_NO_TOOLTIP
        DumpValButton->setText(QApplication::translate("SearchData", "Dump Values", 0));
        OkButton->setText(QApplication::translate("SearchData", "Ok", 0));
#ifndef QT_NO_TOOLTIP
        SearchButton->setToolTip(QApplication::translate("SearchData", "Search all the Datasets with the provided criteria ", 0));
#endif // QT_NO_TOOLTIP
        SearchButton->setText(QApplication::translate("SearchData", "Search", 0));
        CancelButton->setText(QApplication::translate("SearchData", "Cancel", 0));
        textLabel1->setText(QApplication::translate("SearchData", "Total:", 0));
        Count->setText(QApplication::translate("SearchData", "0", 0));
        VDVFunc->setTitle(QApplication::translate("SearchData", "VDV functions & ops", 0));
#ifndef QT_NO_TOOLTIP
        Planets->setToolTip(QApplication::translate("SearchData", "Objects Id", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        Aspects->setToolTip(QApplication::translate("SearchData", "Aspects Id", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        TObjButton->setToolTip(QApplication::translate("SearchData", "TObj(Index, 'Obj', sign number)", 0));
#endif // QT_NO_TOOLTIP
        TObjButton->setText(QApplication::translate("SearchData", "TObj()", 0));
#ifndef QT_NO_TOOLTIP
        TAspButton->setToolTip(QApplication::translate("SearchData", "TAsp(Index, 'Asp', 'Obj', 'Obj')", 0));
#endif // QT_NO_TOOLTIP
        TAspButton->setText(QApplication::translate("SearchData", "TAsp()", 0));
#ifndef QT_NO_TOOLTIP
        TRestButton->setToolTip(QApplication::translate("SearchData", "TObj(Index, 'Obj')", 0));
#endif // QT_NO_TOOLTIP
        TRestButton->setText(QApplication::translate("SearchData", "TRest()", 0));
#ifndef QT_NO_TOOLTIP
        THouseButton->setToolTip(QApplication::translate("SearchData", "TObj(Index, 'Obj', house number)", 0));
#endif // QT_NO_TOOLTIP
        THouseButton->setText(QApplication::translate("SearchData", "THouse()", 0));
#ifndef QT_NO_TOOLTIP
        ANDButton->setToolTip(QApplication::translate("SearchData", "condition AND condition", 0));
#endif // QT_NO_TOOLTIP
        ANDButton->setText(QApplication::translate("SearchData", "AND", 0));
#ifndef QT_NO_TOOLTIP
        ORButton->setToolTip(QApplication::translate("SearchData", "condition OR condition", 0));
#endif // QT_NO_TOOLTIP
        ORButton->setText(QApplication::translate("SearchData", "OR", 0));
#ifndef QT_NO_TOOLTIP
        NOTButton->setToolTip(QApplication::translate("SearchData", "NOT condition", 0));
#endif // QT_NO_TOOLTIP
        NOTButton->setText(QApplication::translate("SearchData", "NOT", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchData: public Ui_SearchData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDATA_H
