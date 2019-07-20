/********************************************************************************
** Form generated from reading UI file 'asteroid.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASTEROID_H
#define UI_ASTEROID_H

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

class Ui_Asteroids
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *Name;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Asteroids)
    {
        if (Asteroids->objectName().isEmpty())
            Asteroids->setObjectName(QStringLiteral("Asteroids"));
        Asteroids->resize(258, 65);
        gridLayout = new QGridLayout(Asteroids);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Asteroids);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Name = new QLineEdit(Asteroids);
        Name->setObjectName(QStringLiteral("Name"));

        gridLayout->addWidget(Name, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(Asteroids);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(Asteroids);
        QObject::connect(buttonBox, SIGNAL(accepted()), Asteroids, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Asteroids, SLOT(reject()));

        QMetaObject::connectSlotsByName(Asteroids);
    } // setupUi

    void retranslateUi(QDialog *Asteroids)
    {
        Asteroids->setWindowTitle(QApplication::translate("Asteroids", "Search for an asteroid", 0));
        label->setText(QApplication::translate("Asteroids", "Name", 0));
    } // retranslateUi

};

namespace Ui {
    class Asteroids: public Ui_Asteroids {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASTEROID_H
