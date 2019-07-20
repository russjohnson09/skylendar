/********************************************************************************
** Form generated from reading UI file 'astroenter.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASTROENTER_H
#define UI_ASTROENTER_H

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

class Ui_AstroEnter
{
public:
    QGridLayout *gridLayout;
    QLabel *Label;
    QLineEdit *Name;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AstroEnter)
    {
        if (AstroEnter->objectName().isEmpty())
            AstroEnter->setObjectName(QStringLiteral("AstroEnter"));
        AstroEnter->resize(243, 98);
        gridLayout = new QGridLayout(AstroEnter);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Label = new QLabel(AstroEnter);
        Label->setObjectName(QStringLiteral("Label"));
        Label->setWordWrap(false);

        gridLayout->addWidget(Label, 0, 0, 1, 1);

        Name = new QLineEdit(AstroEnter);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setMaxLength(50);

        gridLayout->addWidget(Name, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(AstroEnter);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(AstroEnter);
        QObject::connect(buttonBox, SIGNAL(accepted()), AstroEnter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AstroEnter, SLOT(reject()));

        QMetaObject::connectSlotsByName(AstroEnter);
    } // setupUi

    void retranslateUi(QDialog *AstroEnter)
    {
        AstroEnter->setWindowTitle(QApplication::translate("AstroEnter", "Enter a Value", 0));
        Label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AstroEnter: public Ui_AstroEnter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASTROENTER_H
