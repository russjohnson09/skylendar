/********************************************************************************
** Form generated from reading UI file 'password.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORD_H
#define UI_PASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_GetPassword
{
public:
    QGridLayout *gridLayout;
    QLabel *Notice;
    QLabel *label;
    QLineEdit *Password;
    QLabel *label_2;
    QLineEdit *Password_1;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GetPassword)
    {
        if (GetPassword->objectName().isEmpty())
            GetPassword->setObjectName(QStringLiteral("GetPassword"));
        GetPassword->resize(270, 150);
        gridLayout = new QGridLayout(GetPassword);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Notice = new QLabel(GetPassword);
        Notice->setObjectName(QStringLiteral("Notice"));

        gridLayout->addWidget(Notice, 0, 0, 1, 2);

        label = new QLabel(GetPassword);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        Password = new QLineEdit(GetPassword);
        Password->setObjectName(QStringLiteral("Password"));
        Password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(Password, 1, 1, 1, 1);

        label_2 = new QLabel(GetPassword);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        Password_1 = new QLineEdit(GetPassword);
        Password_1->setObjectName(QStringLiteral("Password_1"));
        Password_1->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(Password_1, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(GetPassword);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(GetPassword);
        QObject::connect(buttonBox, SIGNAL(accepted()), GetPassword, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GetPassword, SLOT(reject()));

        QMetaObject::connectSlotsByName(GetPassword);
    } // setupUi

    void retranslateUi(QDialog *GetPassword)
    {
        GetPassword->setWindowTitle(QApplication::translate("GetPassword", "User's Password", 0));
        Notice->setText(QString());
        label->setText(QApplication::translate("GetPassword", "Password:", 0));
        label_2->setText(QApplication::translate("GetPassword", "Retype Password:", 0));
    } // retranslateUi

};

namespace Ui {
    class GetPassword: public Ui_GetPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORD_H
