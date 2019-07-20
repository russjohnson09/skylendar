/********************************************************************************
** Form generated from reading UI file 'stopscan.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOPSCAN_H
#define UI_STOPSCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_StopScan
{
public:
    QGridLayout *gridLayout;
    QLabel *Dual;
    QProgressBar *progressBar;
    QSpacerItem *spacerItem;
    QPushButton *StopButton;
    QSpacerItem *spacerItem1;

    void setupUi(QDialog *StopScan)
    {
        if (StopScan->objectName().isEmpty())
            StopScan->setObjectName(QStringLiteral("StopScan"));
        StopScan->resize(219, 98);
        gridLayout = new QGridLayout(StopScan);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Dual = new QLabel(StopScan);
        Dual->setObjectName(QStringLiteral("Dual"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dual->sizePolicy().hasHeightForWidth());
        Dual->setSizePolicy(sizePolicy);
        Dual->setAlignment(Qt::AlignCenter);
        Dual->setWordWrap(false);

        gridLayout->addWidget(Dual, 0, 0, 1, 3);

        progressBar = new QProgressBar(StopScan);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 1, 0, 1, 3);

        spacerItem = new QSpacerItem(53, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 2, 0, 1, 1);

        StopButton = new QPushButton(StopScan);
        StopButton->setObjectName(QStringLiteral("StopButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(StopButton->sizePolicy().hasHeightForWidth());
        StopButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(StopButton, 2, 1, 1, 1);

        spacerItem1 = new QSpacerItem(52, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 2, 2, 1, 1);


        retranslateUi(StopScan);
        QObject::connect(StopButton, SIGNAL(clicked()), StopScan, SLOT(StopSlot()));

        QMetaObject::connectSlotsByName(StopScan);
    } // setupUi

    void retranslateUi(QDialog *StopScan)
    {
        StopScan->setWindowTitle(QApplication::translate("StopScan", "Aspects Scan", 0));
        Dual->setText(QString());
        StopButton->setText(QApplication::translate("StopScan", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class StopScan: public Ui_StopScan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOPSCAN_H
