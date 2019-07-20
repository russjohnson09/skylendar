/********************************************************************************
** Form generated from reading UI file 'editrestrictions.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRESTRICTIONS_H
#define UI_EDITRESTRICTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "asprestr.h"
#include "astroheader.h"
#include "objrestr.h"

QT_BEGIN_NAMESPACE

class Ui_EditObjRestr
{
public:
    QGridLayout *gridLayout;
    QPushButton *Cancel;
    QSpacerItem *spacerItem;
    QPushButton *Ok;
    QTabWidget *TabWidget;
    QWidget *Objects;
    QGridLayout *gridLayout_2;
    AstroHeader *Header;
    QLabel *TextLabel1;
    ObjRestList *Orl;
    QLineEdit *RSName;
    QPushButton *RestrictAll;
    QSpacerItem *horizontalSpacer;
    QPushButton *ReleaseAll;
    QPushButton *InverseSel;
    QCheckBox *Preload;
    QCheckBox *ToggleHouses;
    QCheckBox *ToggleExtra;
    QCheckBox *ToggleStars;
    QWidget *Aspects;
    QGridLayout *gridLayout1;
    AstroHeader *AspHeader;
    QPushButton *RestrictAllAsp;
    AspRestList *Arl;
    QPushButton *ReleaseAllAsp;
    QPushButton *InverseSelAsp;
    QCheckBox *ToggleMinor;
    QSpacerItem *spacerItem1;
    QWidget *Misc;
    QGridLayout *gridLayout2;
    QComboBox *HousesCombo;
    QSpacerItem *spacerItem2;
    QDoubleSpinBox *ProgFact;
    QLabel *label;
    QComboBox *SiderealCombo;
    QSpacerItem *spacerItem3;
    QSpinBox *Threshold;
    QLabel *label_2;
    QDoubleSpinBox *MPOrbSub;
    QLabel *textLabel1_2;
    QSpacerItem *spacerItem4;
    QGroupBox *Score1;
    QGridLayout *gridLayout3;
    QLabel *textLabel1;
    QListWidget *Scores;
    QSpacerItem *spacerItem5;
    QLabel *textLabel2;
    QSpacerItem *spacerItem6;
    QSpinBox *Values;
    QCheckBox *TrueNodeCheck;
    QCheckBox *Heliocentric;
    QCheckBox *Equatorial;
    QCheckBox *Dnpf;
    QCheckBox *Southern;

    void setupUi(QDialog *EditObjRestr)
    {
        if (EditObjRestr->objectName().isEmpty())
            EditObjRestr->setObjectName(QStringLiteral("EditObjRestr"));
        EditObjRestr->resize(574, 404);
        gridLayout = new QGridLayout(EditObjRestr);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Cancel = new QPushButton(EditObjRestr);
        Cancel->setObjectName(QStringLiteral("Cancel"));

        gridLayout->addWidget(Cancel, 1, 2, 1, 1);

        spacerItem = new QSpacerItem(312, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 1, 1, 1, 1);

        Ok = new QPushButton(EditObjRestr);
        Ok->setObjectName(QStringLiteral("Ok"));

        gridLayout->addWidget(Ok, 1, 0, 1, 1);

        TabWidget = new QTabWidget(EditObjRestr);
        TabWidget->setObjectName(QStringLiteral("TabWidget"));
        Objects = new QWidget();
        Objects->setObjectName(QStringLiteral("Objects"));
        gridLayout_2 = new QGridLayout(Objects);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Header = new AstroHeader(Objects);
        Header->setObjectName(QStringLiteral("Header"));
        Header->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(Header, 0, 0, 1, 1);

        TextLabel1 = new QLabel(Objects);
        TextLabel1->setObjectName(QStringLiteral("TextLabel1"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextLabel1->sizePolicy().hasHeightForWidth());
        TextLabel1->setSizePolicy(sizePolicy);
        TextLabel1->setWordWrap(false);

        gridLayout_2->addWidget(TextLabel1, 0, 1, 1, 2);

        Orl = new ObjRestList(Objects);
        Orl->setObjectName(QStringLiteral("Orl"));
        Orl->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Orl->sizePolicy().hasHeightForWidth());
        Orl->setSizePolicy(sizePolicy1);
        Orl->setMinimumSize(QSize(280, 100));

        gridLayout_2->addWidget(Orl, 1, 0, 8, 1);

        RSName = new QLineEdit(Objects);
        RSName->setObjectName(QStringLiteral("RSName"));
        RSName->setMaxLength(32);

        gridLayout_2->addWidget(RSName, 1, 1, 1, 2);

        RestrictAll = new QPushButton(Objects);
        RestrictAll->setObjectName(QStringLiteral("RestrictAll"));
        sizePolicy.setHeightForWidth(RestrictAll->sizePolicy().hasHeightForWidth());
        RestrictAll->setSizePolicy(sizePolicy);
        RestrictAll->setAutoDefault(false);

        gridLayout_2->addWidget(RestrictAll, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(147, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 2, 1, 1);

        ReleaseAll = new QPushButton(Objects);
        ReleaseAll->setObjectName(QStringLiteral("ReleaseAll"));
        ReleaseAll->setAutoDefault(false);

        gridLayout_2->addWidget(ReleaseAll, 3, 1, 1, 1);

        InverseSel = new QPushButton(Objects);
        InverseSel->setObjectName(QStringLiteral("InverseSel"));
        InverseSel->setAutoDefault(false);

        gridLayout_2->addWidget(InverseSel, 4, 1, 1, 1);

        Preload = new QCheckBox(Objects);
        Preload->setObjectName(QStringLiteral("Preload"));

        gridLayout_2->addWidget(Preload, 5, 1, 1, 1);

        ToggleHouses = new QCheckBox(Objects);
        ToggleHouses->setObjectName(QStringLiteral("ToggleHouses"));

        gridLayout_2->addWidget(ToggleHouses, 6, 1, 1, 1);

        ToggleExtra = new QCheckBox(Objects);
        ToggleExtra->setObjectName(QStringLiteral("ToggleExtra"));

        gridLayout_2->addWidget(ToggleExtra, 7, 1, 1, 1);

        ToggleStars = new QCheckBox(Objects);
        ToggleStars->setObjectName(QStringLiteral("ToggleStars"));

        gridLayout_2->addWidget(ToggleStars, 8, 1, 1, 1);

        TabWidget->addTab(Objects, QString());
        Aspects = new QWidget();
        Aspects->setObjectName(QStringLiteral("Aspects"));
        gridLayout1 = new QGridLayout(Aspects);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        AspHeader = new AstroHeader(Aspects);
        AspHeader->setObjectName(QStringLiteral("AspHeader"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(AspHeader->sizePolicy().hasHeightForWidth());
        AspHeader->setSizePolicy(sizePolicy2);
        AspHeader->setMinimumSize(QSize(0, 26));

        gridLayout1->addWidget(AspHeader, 0, 0, 1, 1);

        RestrictAllAsp = new QPushButton(Aspects);
        RestrictAllAsp->setObjectName(QStringLiteral("RestrictAllAsp"));
        sizePolicy.setHeightForWidth(RestrictAllAsp->sizePolicy().hasHeightForWidth());
        RestrictAllAsp->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(RestrictAllAsp, 0, 1, 1, 1);

        Arl = new AspRestList(Aspects);
        Arl->setObjectName(QStringLiteral("Arl"));
        sizePolicy1.setHeightForWidth(Arl->sizePolicy().hasHeightForWidth());
        Arl->setSizePolicy(sizePolicy1);
        Arl->setMinimumSize(QSize(330, 100));

        gridLayout1->addWidget(Arl, 1, 0, 4, 1);

        ReleaseAllAsp = new QPushButton(Aspects);
        ReleaseAllAsp->setObjectName(QStringLiteral("ReleaseAllAsp"));

        gridLayout1->addWidget(ReleaseAllAsp, 1, 1, 1, 1);

        InverseSelAsp = new QPushButton(Aspects);
        InverseSelAsp->setObjectName(QStringLiteral("InverseSelAsp"));

        gridLayout1->addWidget(InverseSelAsp, 2, 1, 1, 1);

        ToggleMinor = new QCheckBox(Aspects);
        ToggleMinor->setObjectName(QStringLiteral("ToggleMinor"));

        gridLayout1->addWidget(ToggleMinor, 3, 1, 1, 1);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem1, 4, 1, 1, 1);

        TabWidget->addTab(Aspects, QString());
        Misc = new QWidget();
        Misc->setObjectName(QStringLiteral("Misc"));
        gridLayout2 = new QGridLayout(Misc);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        HousesCombo = new QComboBox(Misc);
        HousesCombo->setObjectName(QStringLiteral("HousesCombo"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(HousesCombo->sizePolicy().hasHeightForWidth());
        HousesCombo->setSizePolicy(sizePolicy3);

        gridLayout2->addWidget(HousesCombo, 0, 0, 1, 2);

        spacerItem2 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem2, 0, 2, 1, 1);

        ProgFact = new QDoubleSpinBox(Misc);
        ProgFact->setObjectName(QStringLiteral("ProgFact"));
        ProgFact->setDecimals(5);
        ProgFact->setMaximum(1000);
        ProgFact->setValue(365.242);

        gridLayout2->addWidget(ProgFact, 0, 3, 1, 2);

        label = new QLabel(Misc);
        label->setObjectName(QStringLiteral("label"));

        gridLayout2->addWidget(label, 0, 5, 1, 2);

        SiderealCombo = new QComboBox(Misc);
        SiderealCombo->setObjectName(QStringLiteral("SiderealCombo"));
        sizePolicy3.setHeightForWidth(SiderealCombo->sizePolicy().hasHeightForWidth());
        SiderealCombo->setSizePolicy(sizePolicy3);

        gridLayout2->addWidget(SiderealCombo, 1, 0, 1, 2);

        spacerItem3 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem3, 1, 2, 1, 1);

        Threshold = new QSpinBox(Misc);
        Threshold->setObjectName(QStringLiteral("Threshold"));
        Threshold->setMaximum(10);

        gridLayout2->addWidget(Threshold, 1, 3, 1, 2);

        label_2 = new QLabel(Misc);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout2->addWidget(label_2, 1, 5, 1, 2);

        MPOrbSub = new QDoubleSpinBox(Misc);
        MPOrbSub->setObjectName(QStringLiteral("MPOrbSub"));
        MPOrbSub->setDecimals(1);
        MPOrbSub->setMinimum(-20);
        MPOrbSub->setMaximum(0);

        gridLayout2->addWidget(MPOrbSub, 2, 0, 1, 1);

        textLabel1_2 = new QLabel(Misc);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        sizePolicy1.setHeightForWidth(textLabel1_2->sizePolicy().hasHeightForWidth());
        textLabel1_2->setSizePolicy(sizePolicy1);
        textLabel1_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel1_2, 2, 1, 1, 4);

        spacerItem4 = new QSpacerItem(73, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem4, 2, 6, 1, 1);

        Score1 = new QGroupBox(Misc);
        Score1->setObjectName(QStringLiteral("Score1"));
        gridLayout3 = new QGridLayout(Score1);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        gridLayout3->setContentsMargins(-1, 0, -1, 0);
        textLabel1 = new QLabel(Score1);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout3->addWidget(textLabel1, 0, 0, 1, 1);

        Scores = new QListWidget(Score1);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        new QListWidgetItem(Scores);
        Scores->setObjectName(QStringLiteral("Scores"));

        gridLayout3->addWidget(Scores, 0, 1, 2, 2);

        spacerItem5 = new QSpacerItem(37, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacerItem5, 1, 0, 1, 1);

        textLabel2 = new QLabel(Score1);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout3->addWidget(textLabel2, 2, 0, 1, 1);

        spacerItem6 = new QSpacerItem(211, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacerItem6, 2, 1, 1, 1);

        Values = new QSpinBox(Score1);
        Values->setObjectName(QStringLiteral("Values"));
        Values->setMaximum(10);

        gridLayout3->addWidget(Values, 2, 2, 1, 1);


        gridLayout2->addWidget(Score1, 3, 0, 5, 4);

        TrueNodeCheck = new QCheckBox(Misc);
        TrueNodeCheck->setObjectName(QStringLiteral("TrueNodeCheck"));

        gridLayout2->addWidget(TrueNodeCheck, 3, 4, 1, 2);

        Heliocentric = new QCheckBox(Misc);
        Heliocentric->setObjectName(QStringLiteral("Heliocentric"));

        gridLayout2->addWidget(Heliocentric, 4, 4, 1, 3);

        Equatorial = new QCheckBox(Misc);
        Equatorial->setObjectName(QStringLiteral("Equatorial"));

        gridLayout2->addWidget(Equatorial, 5, 4, 1, 2);

        Dnpf = new QCheckBox(Misc);
        Dnpf->setObjectName(QStringLiteral("Dnpf"));

        gridLayout2->addWidget(Dnpf, 6, 4, 1, 3);

        Southern = new QCheckBox(Misc);
        Southern->setObjectName(QStringLiteral("Southern"));

        gridLayout2->addWidget(Southern, 7, 4, 1, 3);

        TabWidget->addTab(Misc, QString());

        gridLayout->addWidget(TabWidget, 0, 0, 1, 3);

        QWidget::setTabOrder(TabWidget, RSName);
        QWidget::setTabOrder(RSName, RestrictAll);
        QWidget::setTabOrder(RestrictAll, ReleaseAll);
        QWidget::setTabOrder(ReleaseAll, InverseSel);
        QWidget::setTabOrder(InverseSel, Preload);
        QWidget::setTabOrder(Preload, ToggleHouses);
        QWidget::setTabOrder(ToggleHouses, ToggleExtra);
        QWidget::setTabOrder(ToggleExtra, ToggleStars);
        QWidget::setTabOrder(ToggleStars, RestrictAllAsp);
        QWidget::setTabOrder(RestrictAllAsp, ReleaseAllAsp);
        QWidget::setTabOrder(ReleaseAllAsp, InverseSelAsp);
        QWidget::setTabOrder(InverseSelAsp, ToggleMinor);
        QWidget::setTabOrder(ToggleMinor, HousesCombo);
        QWidget::setTabOrder(HousesCombo, TrueNodeCheck);
        QWidget::setTabOrder(TrueNodeCheck, SiderealCombo);
        QWidget::setTabOrder(SiderealCombo, Heliocentric);
        QWidget::setTabOrder(Heliocentric, Equatorial);
        QWidget::setTabOrder(Equatorial, Values);
        QWidget::setTabOrder(Values, Ok);
        QWidget::setTabOrder(Ok, Cancel);

        retranslateUi(EditObjRestr);

        Ok->setDefault(true);
        TabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditObjRestr);
    } // setupUi

    void retranslateUi(QDialog *EditObjRestr)
    {
        EditObjRestr->setWindowTitle(QApplication::translate("EditObjRestr", "Restrictions dialog box", 0));
        Cancel->setText(QApplication::translate("EditObjRestr", "Cancel", 0));
        Ok->setText(QApplication::translate("EditObjRestr", "Ok", 0));
        TextLabel1->setText(QApplication::translate("EditObjRestr", "Restrictions set name:", 0));
        RestrictAll->setText(QApplication::translate("EditObjRestr", "Restrict All", 0));
        ReleaseAll->setText(QApplication::translate("EditObjRestr", "Release All", 0));
        InverseSel->setText(QApplication::translate("EditObjRestr", "Inverse Sel", 0));
        Preload->setText(QApplication::translate("EditObjRestr", "Preload", 0));
        ToggleHouses->setText(QApplication::translate("EditObjRestr", "Toggle Houses", 0));
        ToggleExtra->setText(QApplication::translate("EditObjRestr", "Toggle Extra", 0));
        ToggleStars->setText(QApplication::translate("EditObjRestr", "Toggle Stars", 0));
        TabWidget->setTabText(TabWidget->indexOf(Objects), QApplication::translate("EditObjRestr", "Objects", 0));
        RestrictAllAsp->setText(QApplication::translate("EditObjRestr", "Restrict All", 0));
        ReleaseAllAsp->setText(QApplication::translate("EditObjRestr", "Release All", 0));
        InverseSelAsp->setText(QApplication::translate("EditObjRestr", "Inverse Sel", 0));
        ToggleMinor->setText(QApplication::translate("EditObjRestr", "Toggle Minor", 0));
        TabWidget->setTabText(TabWidget->indexOf(Aspects), QApplication::translate("EditObjRestr", "Aspects", 0));
#ifndef QT_NO_TOOLTIP
        HousesCombo->setToolTip(QApplication::translate("EditObjRestr", "Choose your Houses System", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("EditObjRestr", "Progression Factor", 0));
#ifndef QT_NO_TOOLTIP
        SiderealCombo->setToolTip(QApplication::translate("EditObjRestr", "Choose Tropical or Sidereal Zodiac", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("EditObjRestr", "House Threshold", 0));
        textLabel1_2->setText(QApplication::translate("EditObjRestr", "Orb reduction for aspects to MidPoints/Planets", 0));
        Score1->setTitle(QApplication::translate("EditObjRestr", "Scores", 0));
        textLabel1->setText(QApplication::translate("EditObjRestr", "Types:", 0));

        const bool __sortingEnabled = Scores->isSortingEnabled();
        Scores->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = Scores->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("EditObjRestr", "Conj. to Asc/MC", 0));
        QListWidgetItem *___qlistwidgetitem1 = Scores->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("EditObjRestr", "Conj. to Dsc/FC", 0));
        QListWidgetItem *___qlistwidgetitem2 = Scores->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("EditObjRestr", "Master of Asc/MC", 0));
        QListWidgetItem *___qlistwidgetitem3 = Scores->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("EditObjRestr", "Mastery of", 0));
        QListWidgetItem *___qlistwidgetitem4 = Scores->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("EditObjRestr", "Conj. to Masters", 0));
        QListWidgetItem *___qlistwidgetitem5 = Scores->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("EditObjRestr", "per Mastery", 0));
        QListWidgetItem *___qlistwidgetitem6 = Scores->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("EditObjRestr", "per Aspect", 0));
        QListWidgetItem *___qlistwidgetitem7 = Scores->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("EditObjRestr", "Exaltation", 0));
        QListWidgetItem *___qlistwidgetitem8 = Scores->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("EditObjRestr", "Decan/Term", 0));
        Scores->setSortingEnabled(__sortingEnabled);

        textLabel2->setText(QApplication::translate("EditObjRestr", "Value:", 0));
#ifndef QT_NO_TOOLTIP
        TrueNodeCheck->setToolTip(QApplication::translate("EditObjRestr", "True or Mean lunar Nodes", 0));
#endif // QT_NO_TOOLTIP
        TrueNodeCheck->setText(QApplication::translate("EditObjRestr", "True Node", 0));
        Heliocentric->setText(QApplication::translate("EditObjRestr", "Heliocentric", 0));
        Equatorial->setText(QApplication::translate("EditObjRestr", "Equatorial", 0));
        Dnpf->setText(QApplication::translate("EditObjRestr", "Day/Night Part of Fortune", 0));
        Southern->setText(QApplication::translate("EditObjRestr", "Southern Ecliptic", 0));
        TabWidget->setTabText(TabWidget->indexOf(Misc), QApplication::translate("EditObjRestr", "Misc", 0));
    } // retranslateUi

};

namespace Ui {
    class EditObjRestr: public Ui_EditObjRestr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRESTRICTIONS_H
