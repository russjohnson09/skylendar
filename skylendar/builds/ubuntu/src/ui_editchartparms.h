/********************************************************************************
** Form generated from reading UI file 'editchartparms.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCHARTPARMS_H
#define UI_EDITCHARTPARMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditChartParms
{
public:
    QGridLayout *gridLayout;
    QPushButton *OkButton;
    QPushButton *CancelButton;
    QTabWidget *TabWidget;
    QWidget *General;
    QGridLayout *gridLayout1;
    QCheckBox *DynamicResize;
    QCheckBox *AspRing;
    QCheckBox *AspectsFrame;
    QCheckBox *DisplaySeconds;
    QCheckBox *SortAspectsList;
    QCheckBox *PlanetsRank;
    QCheckBox *InverseBg;
    QCheckBox *Grid;
    QCheckBox *Comment;
    QWidget *Wheels;
    QGridLayout *gridLayout_2;
    QCheckBox *LeftAscendant;
    QCheckBox *Sidebars;
    QCheckBox *CaprGlyph;
    QCheckBox *UranGlyph;
    QCheckBox *PlutoGlyph;
    QCheckBox *Outlines;
    QCheckBox *PlanetHour;
    QCheckBox *Sectors;
    QLabel *TextLabel1;
    QComboBox *SubringBox;
    QWidget *TabPage;
    QGridLayout *gridLayout2;
    QCheckBox *RiseSet;
    QCheckBox *GlobEclipse;
    QCheckBox *AspectsConf;
    QCheckBox *DisplayMidPoints;
    QCheckBox *Sabian;
    QCheckBox *Apsides;
    QCheckBox *Parts;
    QCheckBox *Interpretation;
    QCheckBox *InterpretTrans;

    void setupUi(QDialog *EditChartParms)
    {
        if (EditChartParms->objectName().isEmpty())
            EditChartParms->setObjectName(QStringLiteral("EditChartParms"));
        EditChartParms->resize(320, 370);
        gridLayout = new QGridLayout(EditChartParms);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        OkButton = new QPushButton(EditChartParms);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 1, 0, 1, 1);

        CancelButton = new QPushButton(EditChartParms);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout->addWidget(CancelButton, 1, 1, 1, 1);

        TabWidget = new QTabWidget(EditChartParms);
        TabWidget->setObjectName(QStringLiteral("TabWidget"));
        General = new QWidget();
        General->setObjectName(QStringLiteral("General"));
        gridLayout1 = new QGridLayout(General);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        DynamicResize = new QCheckBox(General);
        DynamicResize->setObjectName(QStringLiteral("DynamicResize"));

        gridLayout1->addWidget(DynamicResize, 0, 0, 1, 1);

        AspRing = new QCheckBox(General);
        AspRing->setObjectName(QStringLiteral("AspRing"));

        gridLayout1->addWidget(AspRing, 1, 0, 1, 1);

        AspectsFrame = new QCheckBox(General);
        AspectsFrame->setObjectName(QStringLiteral("AspectsFrame"));

        gridLayout1->addWidget(AspectsFrame, 2, 0, 1, 1);

        DisplaySeconds = new QCheckBox(General);
        DisplaySeconds->setObjectName(QStringLiteral("DisplaySeconds"));

        gridLayout1->addWidget(DisplaySeconds, 3, 0, 1, 1);

        SortAspectsList = new QCheckBox(General);
        SortAspectsList->setObjectName(QStringLiteral("SortAspectsList"));

        gridLayout1->addWidget(SortAspectsList, 4, 0, 1, 1);

        PlanetsRank = new QCheckBox(General);
        PlanetsRank->setObjectName(QStringLiteral("PlanetsRank"));

        gridLayout1->addWidget(PlanetsRank, 5, 0, 1, 1);

        InverseBg = new QCheckBox(General);
        InverseBg->setObjectName(QStringLiteral("InverseBg"));

        gridLayout1->addWidget(InverseBg, 6, 0, 1, 1);

        Grid = new QCheckBox(General);
        Grid->setObjectName(QStringLiteral("Grid"));

        gridLayout1->addWidget(Grid, 7, 0, 1, 1);

        Comment = new QCheckBox(General);
        Comment->setObjectName(QStringLiteral("Comment"));

        gridLayout1->addWidget(Comment, 8, 0, 1, 1);

        TabWidget->addTab(General, QString());
        Wheels = new QWidget();
        Wheels->setObjectName(QStringLiteral("Wheels"));
        gridLayout_2 = new QGridLayout(Wheels);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        LeftAscendant = new QCheckBox(Wheels);
        LeftAscendant->setObjectName(QStringLiteral("LeftAscendant"));

        gridLayout_2->addWidget(LeftAscendant, 0, 0, 1, 2);

        Sidebars = new QCheckBox(Wheels);
        Sidebars->setObjectName(QStringLiteral("Sidebars"));

        gridLayout_2->addWidget(Sidebars, 1, 0, 1, 1);

        CaprGlyph = new QCheckBox(Wheels);
        CaprGlyph->setObjectName(QStringLiteral("CaprGlyph"));

        gridLayout_2->addWidget(CaprGlyph, 2, 0, 1, 2);

        UranGlyph = new QCheckBox(Wheels);
        UranGlyph->setObjectName(QStringLiteral("UranGlyph"));

        gridLayout_2->addWidget(UranGlyph, 3, 0, 1, 2);

        PlutoGlyph = new QCheckBox(Wheels);
        PlutoGlyph->setObjectName(QStringLiteral("PlutoGlyph"));

        gridLayout_2->addWidget(PlutoGlyph, 4, 0, 1, 2);

        Outlines = new QCheckBox(Wheels);
        Outlines->setObjectName(QStringLiteral("Outlines"));

        gridLayout_2->addWidget(Outlines, 5, 0, 1, 1);

        PlanetHour = new QCheckBox(Wheels);
        PlanetHour->setObjectName(QStringLiteral("PlanetHour"));

        gridLayout_2->addWidget(PlanetHour, 6, 0, 1, 1);

        Sectors = new QCheckBox(Wheels);
        Sectors->setObjectName(QStringLiteral("Sectors"));

        gridLayout_2->addWidget(Sectors, 7, 0, 1, 2);

        TextLabel1 = new QLabel(Wheels);
        TextLabel1->setObjectName(QStringLiteral("TextLabel1"));
        TextLabel1->setWordWrap(false);

        gridLayout_2->addWidget(TextLabel1, 8, 0, 1, 1);

        SubringBox = new QComboBox(Wheels);
        SubringBox->setObjectName(QStringLiteral("SubringBox"));

        gridLayout_2->addWidget(SubringBox, 8, 1, 1, 1);

        TabWidget->addTab(Wheels, QString());
        TabPage = new QWidget();
        TabPage->setObjectName(QStringLiteral("TabPage"));
        gridLayout2 = new QGridLayout(TabPage);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        RiseSet = new QCheckBox(TabPage);
        RiseSet->setObjectName(QStringLiteral("RiseSet"));

        gridLayout2->addWidget(RiseSet, 0, 0, 1, 1);

        GlobEclipse = new QCheckBox(TabPage);
        GlobEclipse->setObjectName(QStringLiteral("GlobEclipse"));

        gridLayout2->addWidget(GlobEclipse, 1, 0, 1, 1);

        AspectsConf = new QCheckBox(TabPage);
        AspectsConf->setObjectName(QStringLiteral("AspectsConf"));

        gridLayout2->addWidget(AspectsConf, 2, 0, 1, 1);

        DisplayMidPoints = new QCheckBox(TabPage);
        DisplayMidPoints->setObjectName(QStringLiteral("DisplayMidPoints"));

        gridLayout2->addWidget(DisplayMidPoints, 3, 0, 1, 1);

        Sabian = new QCheckBox(TabPage);
        Sabian->setObjectName(QStringLiteral("Sabian"));

        gridLayout2->addWidget(Sabian, 4, 0, 1, 1);

        Apsides = new QCheckBox(TabPage);
        Apsides->setObjectName(QStringLiteral("Apsides"));

        gridLayout2->addWidget(Apsides, 5, 0, 1, 1);

        Parts = new QCheckBox(TabPage);
        Parts->setObjectName(QStringLiteral("Parts"));

        gridLayout2->addWidget(Parts, 6, 0, 1, 1);

        Interpretation = new QCheckBox(TabPage);
        Interpretation->setObjectName(QStringLiteral("Interpretation"));

        gridLayout2->addWidget(Interpretation, 7, 0, 1, 1);

        InterpretTrans = new QCheckBox(TabPage);
        InterpretTrans->setObjectName(QStringLiteral("InterpretTrans"));

        gridLayout2->addWidget(InterpretTrans, 8, 0, 1, 1);

        TabWidget->addTab(TabPage, QString());

        gridLayout->addWidget(TabWidget, 0, 0, 1, 2);


        retranslateUi(EditChartParms);

        OkButton->setDefault(true);
        TabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditChartParms);
    } // setupUi

    void retranslateUi(QDialog *EditChartParms)
    {
        EditChartParms->setWindowTitle(QApplication::translate("EditChartParms", "Chart parameters", 0));
        OkButton->setText(QApplication::translate("EditChartParms", "Ok", 0));
        CancelButton->setText(QApplication::translate("EditChartParms", "Cancel", 0));
        DynamicResize->setText(QApplication::translate("EditChartParms", "Dynamically Resize", 0));
        AspRing->setText(QApplication::translate("EditChartParms", "Central Aspects Ring", 0));
        AspectsFrame->setText(QApplication::translate("EditChartParms", "Aspects Frame", 0));
        DisplaySeconds->setText(QApplication::translate("EditChartParms", "Displays Seconds", 0));
        SortAspectsList->setText(QApplication::translate("EditChartParms", "Sort Aspects List by Influence", 0));
        PlanetsRank->setText(QApplication::translate("EditChartParms", "Planets Rank", 0));
        InverseBg->setText(QApplication::translate("EditChartParms", "Inverse Background", 0));
        Grid->setText(QApplication::translate("EditChartParms", "Grid for Astro Graph", 0));
        Comment->setText(QApplication::translate("EditChartParms", "Comment", 0));
        TabWidget->setTabText(TabWidget->indexOf(General), QApplication::translate("EditChartParms", "General", 0));
        LeftAscendant->setText(QApplication::translate("EditChartParms", "Ascendant on the Left", 0));
        Sidebars->setText(QApplication::translate("EditChartParms", "Side Bars", 0));
        CaprGlyph->setText(QApplication::translate("EditChartParms", "European Capricornus Glyph", 0));
        UranGlyph->setText(QApplication::translate("EditChartParms", "European Uranus Glyph", 0));
        PlutoGlyph->setText(QApplication::translate("EditChartParms", "European Pluto Glyph", 0));
        Outlines->setText(QApplication::translate("EditChartParms", "Outlines", 0));
        PlanetHour->setText(QApplication::translate("EditChartParms", "Planetary Hour", 0));
        Sectors->setText(QApplication::translate("EditChartParms", "Colored Sectors", 0));
        TextLabel1->setText(QApplication::translate("EditChartParms", "Subring", 0));
        TabWidget->setTabText(TabWidget->indexOf(Wheels), QApplication::translate("EditChartParms", "Wheel", 0));
        RiseSet->setText(QApplication::translate("EditChartParms", "Planets Risings/Settings", 0));
        GlobEclipse->setText(QApplication::translate("EditChartParms", "Global Eclipse", 0));
        AspectsConf->setText(QApplication::translate("EditChartParms", "Aspects Config", 0));
        DisplayMidPoints->setText(QApplication::translate("EditChartParms", "Displays Midpoints", 0));
        Sabian->setText(QApplication::translate("EditChartParms", "Displays Sabian Degrees", 0));
        Apsides->setText(QApplication::translate("EditChartParms", "Displays Apsides", 0));
        Parts->setText(QApplication::translate("EditChartParms", "Displays Arabic Parts", 0));
        Interpretation->setText(QApplication::translate("EditChartParms", "Displays Interpretation", 0));
        InterpretTrans->setText(QApplication::translate("EditChartParms", "Displays Interp. of transits", 0));
        TabWidget->setTabText(TabWidget->indexOf(TabPage), QApplication::translate("EditChartParms", "List", 0));
    } // retranslateUi

};

namespace Ui {
    class EditChartParms: public Ui_EditChartParms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCHARTPARMS_H
