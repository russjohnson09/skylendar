/********************************************************************************
** Form generated from reading UI file 'astrosplash.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASTROSPLASH_H
#define UI_ASTROSPLASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AstroSplash
{
public:
    QGridLayout *gridLayout;
    QLabel *Sky;
    QProgressBar *Status;
    QLabel *TextLabel2;
    QLineEdit *UserName;
    QLabel *TextLabel1;
    QLineEdit *DbName;
    QLabel *TextLabel3;
    QLineEdit *Password;
    QLabel *TextLabel4;
    QLineEdit *HostName;
    QFrame *frame4;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem;
    QPushButton *CancelButton;
    QPushButton *OkButton;

    void setupUi(QWidget *AstroSplash)
    {
        if (AstroSplash->objectName().isEmpty())
            AstroSplash->setObjectName(QStringLiteral("AstroSplash"));
        AstroSplash->resize(404, 592);
        gridLayout = new QGridLayout(AstroSplash);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Sky = new QLabel(AstroSplash);
        Sky->setObjectName(QStringLiteral("Sky"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Sky->sizePolicy().hasHeightForWidth());
        Sky->setSizePolicy(sizePolicy);
        Sky->setMinimumSize(QSize(386, 452));
        Sky->setScaledContents(true);
        Sky->setWordWrap(false);

        gridLayout->addWidget(Sky, 0, 0, 1, 4);

        Status = new QProgressBar(AstroSplash);
        Status->setObjectName(QStringLiteral("Status"));
        Status->setValue(0);

        gridLayout->addWidget(Status, 1, 0, 1, 4);

        TextLabel2 = new QLabel(AstroSplash);
        TextLabel2->setObjectName(QStringLiteral("TextLabel2"));
        TextLabel2->setWordWrap(false);

        gridLayout->addWidget(TextLabel2, 2, 0, 1, 1);

        UserName = new QLineEdit(AstroSplash);
        UserName->setObjectName(QStringLiteral("UserName"));

        gridLayout->addWidget(UserName, 2, 1, 1, 1);

        TextLabel1 = new QLabel(AstroSplash);
        TextLabel1->setObjectName(QStringLiteral("TextLabel1"));
        TextLabel1->setWordWrap(false);

        gridLayout->addWidget(TextLabel1, 2, 2, 1, 1);

        DbName = new QLineEdit(AstroSplash);
        DbName->setObjectName(QStringLiteral("DbName"));

        gridLayout->addWidget(DbName, 2, 3, 1, 1);

        TextLabel3 = new QLabel(AstroSplash);
        TextLabel3->setObjectName(QStringLiteral("TextLabel3"));
        TextLabel3->setWordWrap(false);

        gridLayout->addWidget(TextLabel3, 3, 0, 1, 1);

        Password = new QLineEdit(AstroSplash);
        Password->setObjectName(QStringLiteral("Password"));
        Password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(Password, 3, 1, 1, 1);

        TextLabel4 = new QLabel(AstroSplash);
        TextLabel4->setObjectName(QStringLiteral("TextLabel4"));
        TextLabel4->setWordWrap(false);

        gridLayout->addWidget(TextLabel4, 3, 2, 1, 1);

        HostName = new QLineEdit(AstroSplash);
        HostName->setObjectName(QStringLiteral("HostName"));

        gridLayout->addWidget(HostName, 3, 3, 1, 1);

        frame4 = new QFrame(AstroSplash);
        frame4->setObjectName(QStringLiteral("frame4"));
        frame4->setFrameShape(QFrame::NoFrame);
        frame4->setFrameShadow(QFrame::Plain);
        gridLayout1 = new QGridLayout(frame4);
        gridLayout1->setSpacing(0);
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        spacerItem = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem, 0, 1, 1, 1);

        CancelButton = new QPushButton(frame4);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout1->addWidget(CancelButton, 0, 2, 1, 1);

        OkButton = new QPushButton(frame4);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        OkButton->setAutoDefault(true);

        gridLayout1->addWidget(OkButton, 0, 0, 1, 1);


        gridLayout->addWidget(frame4, 4, 0, 1, 4);


        retranslateUi(AstroSplash);

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(AstroSplash);
    } // setupUi

    void retranslateUi(QWidget *AstroSplash)
    {
        AstroSplash->setWindowTitle(QApplication::translate("AstroSplash", "Database Login and Startup", 0));
        TextLabel2->setText(QApplication::translate("AstroSplash", "User Name:", 0));
        TextLabel1->setText(QApplication::translate("AstroSplash", "Database Name:", 0));
        TextLabel3->setText(QApplication::translate("AstroSplash", "Password:", 0));
        TextLabel4->setText(QApplication::translate("AstroSplash", "Host Name:", 0));
        CancelButton->setText(QApplication::translate("AstroSplash", "Cancel", 0));
        OkButton->setText(QApplication::translate("AstroSplash", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class AstroSplash: public Ui_AstroSplash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASTROSPLASH_H
