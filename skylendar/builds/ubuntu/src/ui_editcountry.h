/********************************************************************************
** Form generated from reading UI file 'editcountry.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCOUNTRY_H
#define UI_EDITCOUNTRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_EditCountry
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *CountriesList;
    QLineEdit *Name;
    QLineEdit *ZifName;
    QLineEdit *Code;
    QLabel *textLabel1;
    QLineEdit *J2g;
    QLabel *textLabel1_2;
    QLineEdit *Comment;
    QPushButton *SearchButton;
    QPushButton *NewButton;
    QPushButton *DeleteButton;
    QPushButton *ModifyButton;
    QPushButton *FileListButton;
    QPushButton *OkButton;

    void setupUi(QDialog *EditCountry)
    {
        if (EditCountry->objectName().isEmpty())
            EditCountry->setObjectName(QStringLiteral("EditCountry"));
        EditCountry->resize(473, 354);
        gridLayout = new QGridLayout(EditCountry);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        CountriesList = new QTreeWidget(EditCountry);
        CountriesList->setObjectName(QStringLiteral("CountriesList"));
        CountriesList->setIndentation(0);

        gridLayout->addWidget(CountriesList, 0, 0, 1, 7);

        Name = new QLineEdit(EditCountry);
        Name->setObjectName(QStringLiteral("Name"));

        gridLayout->addWidget(Name, 1, 0, 1, 3);

        ZifName = new QLineEdit(EditCountry);
        ZifName->setObjectName(QStringLiteral("ZifName"));

        gridLayout->addWidget(ZifName, 1, 3, 1, 3);

        Code = new QLineEdit(EditCountry);
        Code->setObjectName(QStringLiteral("Code"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Code->sizePolicy().hasHeightForWidth());
        Code->setSizePolicy(sizePolicy);
        Code->setMaximumSize(QSize(35, 32767));
        Code->setMaxLength(3);
        Code->setAlignment(Qt::AlignHCenter);

        gridLayout->addWidget(Code, 1, 6, 1, 1);

        textLabel1 = new QLabel(EditCountry);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 2, 0, 1, 2);

        J2g = new QLineEdit(EditCountry);
        J2g->setObjectName(QStringLiteral("J2g"));

        gridLayout->addWidget(J2g, 2, 3, 1, 4);

        textLabel1_2 = new QLabel(EditCountry);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        gridLayout->addWidget(textLabel1_2, 3, 0, 1, 1);

        Comment = new QLineEdit(EditCountry);
        Comment->setObjectName(QStringLiteral("Comment"));

        gridLayout->addWidget(Comment, 3, 1, 1, 6);

        SearchButton = new QPushButton(EditCountry);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SearchButton->sizePolicy().hasHeightForWidth());
        SearchButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(SearchButton, 4, 0, 1, 1);

        NewButton = new QPushButton(EditCountry);
        NewButton->setObjectName(QStringLiteral("NewButton"));
        sizePolicy1.setHeightForWidth(NewButton->sizePolicy().hasHeightForWidth());
        NewButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(NewButton, 4, 1, 1, 1);

        DeleteButton = new QPushButton(EditCountry);
        DeleteButton->setObjectName(QStringLiteral("DeleteButton"));
        sizePolicy1.setHeightForWidth(DeleteButton->sizePolicy().hasHeightForWidth());
        DeleteButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(DeleteButton, 4, 2, 1, 2);

        ModifyButton = new QPushButton(EditCountry);
        ModifyButton->setObjectName(QStringLiteral("ModifyButton"));
        sizePolicy1.setHeightForWidth(ModifyButton->sizePolicy().hasHeightForWidth());
        ModifyButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(ModifyButton, 4, 4, 1, 1);

        FileListButton = new QPushButton(EditCountry);
        FileListButton->setObjectName(QStringLiteral("FileListButton"));
        sizePolicy1.setHeightForWidth(FileListButton->sizePolicy().hasHeightForWidth());
        FileListButton->setSizePolicy(sizePolicy1);
        FileListButton->setMinimumSize(QSize(0, 0));
        FileListButton->setMaximumSize(QSize(32767, 32767));

        gridLayout->addWidget(FileListButton, 4, 5, 1, 2);

        OkButton = new QPushButton(EditCountry);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        OkButton->setCheckable(false);
        OkButton->setAutoDefault(false);

        gridLayout->addWidget(OkButton, 5, 0, 1, 1);

        QWidget::setTabOrder(Name, ZifName);
        QWidget::setTabOrder(ZifName, Code);
        QWidget::setTabOrder(Code, SearchButton);
        QWidget::setTabOrder(SearchButton, NewButton);
        QWidget::setTabOrder(NewButton, DeleteButton);
        QWidget::setTabOrder(DeleteButton, ModifyButton);
        QWidget::setTabOrder(ModifyButton, FileListButton);
        QWidget::setTabOrder(FileListButton, OkButton);

        retranslateUi(EditCountry);

        OkButton->setDefault(true);


        QMetaObject::connectSlotsByName(EditCountry);
    } // setupUi

    void retranslateUi(QDialog *EditCountry)
    {
        EditCountry->setWindowTitle(QApplication::translate("EditCountry", "Edit country", 0));
        QTreeWidgetItem *___qtreewidgetitem = CountriesList->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("EditCountry", "Comment", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("EditCountry", "Jul->Greg", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("EditCountry", "Code", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("EditCountry", "Zone Info File", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("EditCountry", "Name", 0));
        Code->setText(QString());
        textLabel1->setText(QApplication::translate("EditCountry", "Julian->Gregorian:", 0));
        textLabel1_2->setText(QApplication::translate("EditCountry", "Comment:", 0));
        SearchButton->setText(QApplication::translate("EditCountry", "Search", 0));
        NewButton->setText(QApplication::translate("EditCountry", "New", 0));
        DeleteButton->setText(QApplication::translate("EditCountry", "Delete", 0));
        ModifyButton->setText(QApplication::translate("EditCountry", "Modify", 0));
        FileListButton->setText(QApplication::translate("EditCountry", "...", 0));
        OkButton->setText(QApplication::translate("EditCountry", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class EditCountry: public Ui_EditCountry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCOUNTRY_H
