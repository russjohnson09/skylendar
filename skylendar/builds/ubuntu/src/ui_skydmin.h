/********************************************************************************
** Form generated from reading UI file 'skydmin.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKYDMIN_H
#define UI_SKYDMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Skydmin
{
public:
    QGridLayout *gridLayout_8;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *Insert;
    QPushButton *DownloadAster;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *DownloadSe1;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *DeleteSources;
    QSpacerItem *horizontalSpacer;
    QPushButton *Delete;
    QSpacerItem *horizontalSpacer_3;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout_7;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *DbName;
    QLabel *label_4;
    QPushButton *LoginButton;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *Password;
    QLabel *label_3;
    QLineEdit *Hostname;
    QLabel *label_2;
    QTextEdit *Install;
    QPushButton *InstallButton;
    QPushButton *UninstallButton;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableView *Accesses;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTableView *ExtraObjs;
    QWidget *tab_4;
    QGridLayout *gridLayout_5;
    QTableView *TypeIcons;
    QWidget *tab_5;
    QGridLayout *gridLayout_6;
    QTableView *Parts;
    QWidget *tab_6;
    QGridLayout *gridLayout_9;
    QTableView *Stars;

    void setupUi(QDialog *Skydmin)
    {
        if (Skydmin->objectName().isEmpty())
            Skydmin->setObjectName(QStringLiteral("Skydmin"));
        Skydmin->resize(625, 537);
        gridLayout_8 = new QGridLayout(Skydmin);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        frame_2 = new QFrame(Skydmin);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Insert = new QPushButton(frame_2);
        Insert->setObjectName(QStringLiteral("Insert"));

        gridLayout->addWidget(Insert, 0, 5, 1, 1);

        DownloadAster = new QPushButton(frame_2);
        DownloadAster->setObjectName(QStringLiteral("DownloadAster"));
        DownloadAster->setEnabled(false);

        gridLayout->addWidget(DownloadAster, 1, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        DownloadSe1 = new QPushButton(frame_2);
        DownloadSe1->setObjectName(QStringLiteral("DownloadSe1"));

        gridLayout->addWidget(DownloadSe1, 1, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(32, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        DeleteSources = new QPushButton(frame_2);
        DeleteSources->setObjectName(QStringLiteral("DeleteSources"));

        gridLayout->addWidget(DeleteSources, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        Delete = new QPushButton(frame_2);
        Delete->setObjectName(QStringLiteral("Delete"));

        gridLayout->addWidget(Delete, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(75, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 3, 1, 2);

        buttonBox = new QDialogButtonBox(frame_2);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 4, 1, 2);


        gridLayout_8->addWidget(frame_2, 1, 0, 1, 1);

        tabWidget = new QTabWidget(Skydmin);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_7 = new QGridLayout(tab_3);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        frame = new QFrame(tab_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label, 0, 0, 1, 5);

        DbName = new QLineEdit(frame);
        DbName->setObjectName(QStringLiteral("DbName"));

        gridLayout_4->addWidget(DbName, 1, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 1, 1, 1, 1);

        LoginButton = new QPushButton(frame);
        LoginButton->setObjectName(QStringLiteral("LoginButton"));

        gridLayout_4->addWidget(LoginButton, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(164, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 1, 3, 1, 2);

        Password = new QLineEdit(frame);
        Password->setObjectName(QStringLiteral("Password"));
        Password->setEchoMode(QLineEdit::Password);

        gridLayout_4->addWidget(Password, 2, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 2, 1, 1, 1);

        Hostname = new QLineEdit(frame);
        Hostname->setObjectName(QStringLiteral("Hostname"));

        gridLayout_4->addWidget(Hostname, 2, 2, 1, 2);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 2, 4, 1, 1);


        gridLayout_7->addWidget(frame, 0, 0, 1, 2);

        Install = new QTextEdit(tab_3);
        Install->setObjectName(QStringLiteral("Install"));
        Install->setLineWrapColumnOrWidth(0);
        Install->setReadOnly(true);

        gridLayout_7->addWidget(Install, 1, 0, 1, 2);

        InstallButton = new QPushButton(tab_3);
        InstallButton->setObjectName(QStringLiteral("InstallButton"));

        gridLayout_7->addWidget(InstallButton, 2, 0, 1, 1);

        UninstallButton = new QPushButton(tab_3);
        UninstallButton->setObjectName(QStringLiteral("UninstallButton"));

        gridLayout_7->addWidget(UninstallButton, 2, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Accesses = new QTableView(tab);
        Accesses->setObjectName(QStringLiteral("Accesses"));
        Accesses->setEnabled(false);

        gridLayout_2->addWidget(Accesses, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        ExtraObjs = new QTableView(tab_2);
        ExtraObjs->setObjectName(QStringLiteral("ExtraObjs"));
        ExtraObjs->setEnabled(false);

        gridLayout_3->addWidget(ExtraObjs, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_5 = new QGridLayout(tab_4);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        TypeIcons = new QTableView(tab_4);
        TypeIcons->setObjectName(QStringLiteral("TypeIcons"));
        TypeIcons->setEnabled(false);

        gridLayout_5->addWidget(TypeIcons, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        gridLayout_6 = new QGridLayout(tab_5);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        Parts = new QTableView(tab_5);
        Parts->setObjectName(QStringLiteral("Parts"));
        Parts->setEnabled(false);

        gridLayout_6->addWidget(Parts, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        gridLayout_9 = new QGridLayout(tab_6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        Stars = new QTableView(tab_6);
        Stars->setObjectName(QStringLiteral("Stars"));

        gridLayout_9->addWidget(Stars, 0, 0, 1, 1);

        tabWidget->addTab(tab_6, QString());

        gridLayout_8->addWidget(tabWidget, 0, 0, 1, 1);

        QWidget::setTabOrder(DbName, Password);
        QWidget::setTabOrder(Password, Hostname);
        QWidget::setTabOrder(Hostname, LoginButton);
        QWidget::setTabOrder(LoginButton, Install);
        QWidget::setTabOrder(Install, InstallButton);
        QWidget::setTabOrder(InstallButton, UninstallButton);
        QWidget::setTabOrder(UninstallButton, DeleteSources);
        QWidget::setTabOrder(DeleteSources, Delete);
        QWidget::setTabOrder(Delete, Insert);
        QWidget::setTabOrder(Insert, DownloadAster);
        QWidget::setTabOrder(DownloadAster, DownloadSe1);
        QWidget::setTabOrder(DownloadSe1, buttonBox);
        QWidget::setTabOrder(buttonBox, tabWidget);
        QWidget::setTabOrder(tabWidget, Accesses);
        QWidget::setTabOrder(Accesses, ExtraObjs);
        QWidget::setTabOrder(ExtraObjs, TypeIcons);
        QWidget::setTabOrder(TypeIcons, Parts);
        QWidget::setTabOrder(Parts, Stars);

        retranslateUi(Skydmin);
        QObject::connect(buttonBox, SIGNAL(accepted()), Skydmin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Skydmin, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Skydmin);
    } // setupUi

    void retranslateUi(QDialog *Skydmin)
    {
        Skydmin->setWindowTitle(QApplication::translate("Skydmin", "Skydmin", 0));
        Insert->setText(QApplication::translate("Skydmin", "Insert New Row", 0));
        DownloadAster->setText(QApplication::translate("Skydmin", "Download Asteroid", 0));
        DownloadSe1->setText(QApplication::translate("Skydmin", "Download Ephem Files", 0));
        DeleteSources->setText(QApplication::translate("Skydmin", "Delete Sources", 0));
        Delete->setText(QApplication::translate("Skydmin", "Delete Current Row", 0));
        label->setText(QApplication::translate("Skydmin", "Login as user postgres", 0));
        label_4->setText(QApplication::translate("Skydmin", "Database", 0));
        LoginButton->setText(QApplication::translate("Skydmin", "Login", 0));
        label_3->setText(QApplication::translate("Skydmin", "Postgres Password", 0));
        label_2->setText(QApplication::translate("Skydmin", "Hostname", 0));
        InstallButton->setText(QApplication::translate("Skydmin", "Install/Upgrade", 0));
        UninstallButton->setText(QApplication::translate("Skydmin", "Uninstall", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Skydmin", "Login", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Skydmin", "Accesses", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Skydmin", "Extra Objects", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Skydmin", "Type Icons", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("Skydmin", "Parts", 0));
#ifndef QT_NO_ACCESSIBILITY
        tab_6->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("Skydmin", "Stars", 0));
    } // retranslateUi

};

namespace Ui {
    class Skydmin: public Ui_Skydmin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKYDMIN_H
