/********************************************************************************
** Form generated from reading UI file 'scanspan.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANSPAN_H
#define UI_SCANSPAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditScanSpan
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *TimeSpan;
    QGridLayout *gridLayout;
    QRadioButton *CurDay;
    QRadioButton *CurMonth;
    QRadioButton *CurYear;
    QRadioButton *NbYears;
    QSpacerItem *spacerItem;
    QSpinBox *YearsNumber;
    QRadioButton *SolRev;
    QRadioButton *LunarRev;
    QCheckBox *MP;
    QCheckBox *Part;
    QCheckBox *DumpAsp;
    QPushButton *OkButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *EditScanSpan)
    {
        if (EditScanSpan->objectName().isEmpty())
            EditScanSpan->setObjectName(QStringLiteral("EditScanSpan"));
        EditScanSpan->resize(226, 334);
        gridLayout_2 = new QGridLayout(EditScanSpan);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        TimeSpan = new QGroupBox(EditScanSpan);
        TimeSpan->setObjectName(QStringLiteral("TimeSpan"));
        gridLayout = new QGridLayout(TimeSpan);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        CurDay = new QRadioButton(TimeSpan);
        CurDay->setObjectName(QStringLiteral("CurDay"));

        gridLayout->addWidget(CurDay, 0, 0, 1, 3);

        CurMonth = new QRadioButton(TimeSpan);
        CurMonth->setObjectName(QStringLiteral("CurMonth"));

        gridLayout->addWidget(CurMonth, 1, 0, 1, 3);

        CurYear = new QRadioButton(TimeSpan);
        CurYear->setObjectName(QStringLiteral("CurYear"));

        gridLayout->addWidget(CurYear, 2, 0, 1, 3);

        NbYears = new QRadioButton(TimeSpan);
        NbYears->setObjectName(QStringLiteral("NbYears"));

        gridLayout->addWidget(NbYears, 3, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 3, 1, 1, 1);

        YearsNumber = new QSpinBox(TimeSpan);
        YearsNumber->setObjectName(QStringLiteral("YearsNumber"));
        YearsNumber->setEnabled(false);
        YearsNumber->setMinimum(1);
        YearsNumber->setMaximum(10000);

        gridLayout->addWidget(YearsNumber, 3, 2, 1, 1);

        SolRev = new QRadioButton(TimeSpan);
        SolRev->setObjectName(QStringLiteral("SolRev"));

        gridLayout->addWidget(SolRev, 4, 0, 1, 3);

        LunarRev = new QRadioButton(TimeSpan);
        LunarRev->setObjectName(QStringLiteral("LunarRev"));

        gridLayout->addWidget(LunarRev, 5, 0, 1, 3);


        gridLayout_2->addWidget(TimeSpan, 0, 0, 1, 2);

        MP = new QCheckBox(EditScanSpan);
        MP->setObjectName(QStringLiteral("MP"));

        gridLayout_2->addWidget(MP, 1, 0, 1, 2);

        Part = new QCheckBox(EditScanSpan);
        Part->setObjectName(QStringLiteral("Part"));

        gridLayout_2->addWidget(Part, 2, 0, 1, 2);

        DumpAsp = new QCheckBox(EditScanSpan);
        DumpAsp->setObjectName(QStringLiteral("DumpAsp"));

        gridLayout_2->addWidget(DumpAsp, 3, 0, 1, 2);

        OkButton = new QPushButton(EditScanSpan);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout_2->addWidget(OkButton, 4, 0, 1, 1);

        CancelButton = new QPushButton(EditScanSpan);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout_2->addWidget(CancelButton, 4, 1, 1, 1);

        QWidget::setTabOrder(OkButton, CancelButton);

        retranslateUi(EditScanSpan);
        QObject::connect(OkButton, SIGNAL(clicked()), EditScanSpan, SLOT(accept()));
        QObject::connect(CancelButton, SIGNAL(clicked()), EditScanSpan, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditScanSpan);
    } // setupUi

    void retranslateUi(QDialog *EditScanSpan)
    {
        EditScanSpan->setWindowTitle(QApplication::translate("EditScanSpan", "Select a Time Span", 0));
        TimeSpan->setTitle(QApplication::translate("EditScanSpan", "Time Span", 0));
        CurDay->setText(QApplication::translate("EditScanSpan", "Current Day", 0));
        CurMonth->setText(QApplication::translate("EditScanSpan", "Current Month", 0));
        CurYear->setText(QApplication::translate("EditScanSpan", "Current Year", 0));
        NbYears->setText(QApplication::translate("EditScanSpan", "Nb.Years:", 0));
        SolRev->setText(QApplication::translate("EditScanSpan", "Solar Revolution of the Year", 0));
        LunarRev->setText(QApplication::translate("EditScanSpan", "Lunar Revolutions of the Year", 0));
        MP->setText(QApplication::translate("EditScanSpan", "Aspects to Midpoints", 0));
        Part->setText(QApplication::translate("EditScanSpan", "Aspects to Arabic Parts", 0));
        DumpAsp->setText(QApplication::translate("EditScanSpan", "Dump Aspects to AspTbl", 0));
        OkButton->setText(QApplication::translate("EditScanSpan", "Ok", 0));
        CancelButton->setText(QApplication::translate("EditScanSpan", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class EditScanSpan: public Ui_EditScanSpan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANSPAN_H
