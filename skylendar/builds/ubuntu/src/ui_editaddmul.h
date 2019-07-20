/********************************************************************************
** Form generated from reading UI file 'editaddmul.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITADDMUL_H
#define UI_EDITADDMUL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_EditAddMul
{
public:
    QGridLayout *gridLayout;
    QPushButton *OkButton;
    QLabel *Caption;
    QLineEdit *Value;
    QComboBox *ValBox;
    QPushButton *CancelButton;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *EditAddMul)
    {
        if (EditAddMul->objectName().isEmpty())
            EditAddMul->setObjectName(QStringLiteral("EditAddMul"));
        EditAddMul->resize(286, 88);
        gridLayout = new QGridLayout(EditAddMul);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        OkButton = new QPushButton(EditAddMul);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 1, 0, 1, 1);

        Caption = new QLabel(EditAddMul);
        Caption->setObjectName(QStringLiteral("Caption"));
        Caption->setWordWrap(false);

        gridLayout->addWidget(Caption, 0, 0, 1, 1);

        Value = new QLineEdit(EditAddMul);
        Value->setObjectName(QStringLiteral("Value"));
        Value->setAlignment(Qt::AlignRight);

        gridLayout->addWidget(Value, 0, 1, 1, 2);

        ValBox = new QComboBox(EditAddMul);
        ValBox->setObjectName(QStringLiteral("ValBox"));
        ValBox->setEnabled(true);

        gridLayout->addWidget(ValBox, 0, 3, 1, 1);

        CancelButton = new QPushButton(EditAddMul);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout->addWidget(CancelButton, 1, 2, 1, 2);

        spacerItem = new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 1, 1, 1, 1);


        retranslateUi(EditAddMul);

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(EditAddMul);
    } // setupUi

    void retranslateUi(QDialog *EditAddMul)
    {
        EditAddMul->setWindowTitle(QApplication::translate("EditAddMul", "Add or Mul factor", 0));
        OkButton->setText(QApplication::translate("EditAddMul", "OK", 0));
        Caption->setText(QString());
        ValBox->clear();
        ValBox->insertItems(0, QStringList()
         << QApplication::translate("EditAddMul", "2", 0)
         << QApplication::translate("EditAddMul", "3", 0)
         << QApplication::translate("EditAddMul", "4", 0)
         << QApplication::translate("EditAddMul", "5", 0)
         << QApplication::translate("EditAddMul", "6", 0)
         << QApplication::translate("EditAddMul", "7", 0)
         << QApplication::translate("EditAddMul", "8", 0)
         << QApplication::translate("EditAddMul", "9", 0)
         << QApplication::translate("EditAddMul", "10", 0)
         << QApplication::translate("EditAddMul", "11", 0)
         << QApplication::translate("EditAddMul", "12", 0)
        );
        CancelButton->setText(QApplication::translate("EditAddMul", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class EditAddMul: public Ui_EditAddMul {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITADDMUL_H
