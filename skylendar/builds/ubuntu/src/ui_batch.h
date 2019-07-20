/********************************************************************************
** Form generated from reading UI file 'batch.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCH_H
#define UI_BATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Batch
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *Condition;
    QCheckBox *Save;
    QCheckBox *Vdv;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Batch)
    {
        if (Batch->objectName().isEmpty())
            Batch->setObjectName(QStringLiteral("Batch"));
        Batch->resize(337, 93);
        gridLayout = new QGridLayout(Batch);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Batch);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Condition = new QLineEdit(Batch);
        Condition->setObjectName(QStringLiteral("Condition"));

        gridLayout->addWidget(Condition, 0, 1, 1, 3);

        Save = new QCheckBox(Batch);
        Save->setObjectName(QStringLiteral("Save"));

        gridLayout->addWidget(Save, 1, 0, 1, 2);

        Vdv = new QCheckBox(Batch);
        Vdv->setObjectName(QStringLiteral("Vdv"));

        gridLayout->addWidget(Vdv, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(152, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

        buttonBox = new QDialogButtonBox(Batch);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 2, 1, 2);


        retranslateUi(Batch);
        QObject::connect(buttonBox, SIGNAL(accepted()), Batch, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Batch, SLOT(reject()));

        QMetaObject::connectSlotsByName(Batch);
    } // setupUi

    void retranslateUi(QDialog *Batch)
    {
        Batch->setWindowTitle(QApplication::translate("Batch", "Batch Chart", 0));
        label->setText(QApplication::translate("Batch", "SQL Condition:", 0));
        Save->setText(QApplication::translate("Batch", "Save to Table", 0));
        Vdv->setText(QApplication::translate("Batch", "By VDV", 0));
    } // retranslateUi

};

namespace Ui {
    class Batch: public Ui_Batch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCH_H
