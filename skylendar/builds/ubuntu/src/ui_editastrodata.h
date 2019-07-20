/*
This dialog box class allows 
the user to edit an AstroData class
*/

/********************************************************************************
** Form generated from reading UI file 'editastrodata.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITASTRODATA_H
#define UI_EDITASTRODATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <astrospinbox.h>
#include "astrodefs.h"
#include "astrospinbox.h"
#include "editplace.h"

QT_BEGIN_NAMESPACE

class Ui_EditAstroData
{
public:
    QGridLayout *gridLayout;
    QPushButton *OkButton;
    QLabel *Error;
    QPushButton *CancelButton;
    QTabWidget *DataWidget;
    QWidget *TabName;
    QGridLayout *gridLayout_2;
    QLabel *TextLabel1;
    QLineEdit *Name;
    QSpacerItem *spacerItem;
    QLabel *TextLabel2;
    QGroupBox *GenderGroup;
    QGridLayout *gridLayout1;
    QRadioButton *MaleButton;
    QRadioButton *FemaleButton;
    QRadioButton *NeutralButton;
    QRadioButton *SituationButton;
    QSpacerItem *spacerItem1;
    QLabel *TextLabel3;
    QComboBox *TypeofChart;
    QSpacerItem *horizontalSpacer;
    QLabel *ChartTypeIcon;
    QSpacerItem *spacerItem2;
    QGroupBox *KeywordGroupBox;
    QGridLayout *gridLayout2;
    QSpacerItem *spacerItem3;
    QLabel *textLabel1;
    QComboBox *SrcBox;
    QComboBox *TagBox;
    QLineEdit *Keywords;
    QWidget *TabDate;
    QGridLayout *gridLayout3;
    QGroupBox *Date;
    QGridLayout *gridLayout4;
    QLabel *textLabel1_3;
    QSpacerItem *spacerItem4;
    QLabel *textLabel2;
    QSpacerItem *spacerItem5;
    QLabel *textLabel3;
    QSpacerItem *spacerItem6;
    QLabel *textLabel4;
    QSpacerItem *spacerItem7;
    QLabel *textLabel5;
    QSpacerItem *spacerItem8;
    QLabel *textLabel1_6;
    QSpacerItem *spacerItem9;
    QLabel *textLabel6;
    QComboBox *Day;
    QSpacerItem *spacerItem10;
    QComboBox *Month;
    QSpacerItem *spacerItem11;
    AstroSpinBox *Year;
    QSpacerItem *spacerItem12;
    AstroSpinBox *Hour;
    QSpacerItem *spacerItem13;
    AstroSpinBox *Minute;
    QSpacerItem *spacerItem14;
    AstroSpinBox *Second;
    QSpacerItem *spacerItem15;
    AstroSpinBox *Accuracy;
    QCheckBox *Preload;
    QSpacerItem *spacerItem16;
    QPushButton *NowButton;
    QCheckBox *Automatic;
    QGroupBox *TimeZoneGroupBox;
    QGridLayout *gridLayout5;
    QLabel *TextLabel1_2;
    QSpacerItem *spacerItem17;
    QLineEdit *TimezoneLine;
    QLabel *textLabel1_2;
    QComboBox *DtsChoice;
    QLineEdit *DaylightLine;
    QPushButton *RecomputeButton;
    QCheckBox *HMSButton;
    QCheckBox *ToSecond;
    QCheckBox *TrueSolarTime;
    QLabel *DSLabel;
    QLabel *DateSystem;
    QLabel *textLabel1_4;
    QLabel *Julday;
    QSpacerItem *spacerItem18;
    QSpacerItem *spacerItem19;
    QSpacerItem *spacerItem20;
    QWidget *TabPlace;
    QGridLayout *gridLayout6;
    EditPlace *PlaceEdition;
    QWidget *TabComment;
    QGridLayout *gridLayout7;
    QTextEdit *Comment;

    void setupUi(QDialog *EditAstroData)
    {
        if (EditAstroData->objectName().isEmpty())
            EditAstroData->setObjectName(QStringLiteral("EditAstroData"));
        EditAstroData->resize(650, 425);
        EditAstroData->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(EditAstroData);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        OkButton = new QPushButton(EditAstroData);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 1, 0, 1, 1);

        Error = new QLabel(EditAstroData);
        Error->setObjectName(QStringLiteral("Error"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Error->sizePolicy().hasHeightForWidth());
        Error->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        Error->setFont(font);
        Error->setFrameShape(QFrame::Panel);
        Error->setFrameShadow(QFrame::Sunken);
        Error->setTextFormat(Qt::AutoText);
        Error->setAlignment(Qt::AlignCenter);
        Error->setWordWrap(false);

        gridLayout->addWidget(Error, 1, 1, 1, 1);

        CancelButton = new QPushButton(EditAstroData);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout->addWidget(CancelButton, 1, 2, 1, 1);

        DataWidget = new QTabWidget(EditAstroData);
        DataWidget->setObjectName(QStringLiteral("DataWidget"));
        TabName = new QWidget();
        TabName->setObjectName(QStringLiteral("TabName"));
        gridLayout_2 = new QGridLayout(TabName);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        TextLabel1 = new QLabel(TabName);
        TextLabel1->setObjectName(QStringLiteral("TextLabel1"));
        TextLabel1->setWordWrap(false);

        gridLayout_2->addWidget(TextLabel1, 0, 0, 1, 1);

        Name = new QLineEdit(TabName);
        Name->setObjectName(QStringLiteral("Name"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Name->sizePolicy().hasHeightForWidth());
        Name->setSizePolicy(sizePolicy1);
        Name->setMinimumSize(QSize(0, 20));
        Name->setMaxLength(27);
        Name->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(Name, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(spacerItem, 1, 1, 1, 1);

        TextLabel2 = new QLabel(TabName);
        TextLabel2->setObjectName(QStringLiteral("TextLabel2"));
        TextLabel2->setWordWrap(false);

        gridLayout_2->addWidget(TextLabel2, 2, 0, 1, 1);

        GenderGroup = new QGroupBox(TabName);
        GenderGroup->setObjectName(QStringLiteral("GenderGroup"));
        gridLayout1 = new QGridLayout(GenderGroup);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        MaleButton = new QRadioButton(GenderGroup);
        MaleButton->setObjectName(QStringLiteral("MaleButton"));

        gridLayout1->addWidget(MaleButton, 0, 0, 1, 1);

        FemaleButton = new QRadioButton(GenderGroup);
        FemaleButton->setObjectName(QStringLiteral("FemaleButton"));

        gridLayout1->addWidget(FemaleButton, 0, 1, 1, 1);

        NeutralButton = new QRadioButton(GenderGroup);
        NeutralButton->setObjectName(QStringLiteral("NeutralButton"));

        gridLayout1->addWidget(NeutralButton, 0, 2, 1, 1);

        SituationButton = new QRadioButton(GenderGroup);
        SituationButton->setObjectName(QStringLiteral("SituationButton"));

        gridLayout1->addWidget(SituationButton, 0, 3, 1, 1);


        gridLayout_2->addWidget(GenderGroup, 2, 1, 1, 1);

        spacerItem1 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(spacerItem1, 3, 1, 1, 1);

        TextLabel3 = new QLabel(TabName);
        TextLabel3->setObjectName(QStringLiteral("TextLabel3"));
        TextLabel3->setWordWrap(false);

        gridLayout_2->addWidget(TextLabel3, 4, 0, 1, 1);

        TypeofChart = new QComboBox(TabName);
        TypeofChart->setObjectName(QStringLiteral("TypeofChart"));
        TypeofChart->setEnabled(true);
        sizePolicy1.setHeightForWidth(TypeofChart->sizePolicy().hasHeightForWidth());
        TypeofChart->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(TypeofChart, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(269, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 4, 2, 1, 1);

        ChartTypeIcon = new QLabel(TabName);
        ChartTypeIcon->setObjectName(QStringLiteral("ChartTypeIcon"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ChartTypeIcon->sizePolicy().hasHeightForWidth());
        ChartTypeIcon->setSizePolicy(sizePolicy2);
        ChartTypeIcon->setScaledContents(true);
        ChartTypeIcon->setWordWrap(false);

        gridLayout_2->addWidget(ChartTypeIcon, 5, 1, 1, 1);

        spacerItem2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(spacerItem2, 6, 1, 1, 1);

        KeywordGroupBox = new QGroupBox(TabName);
        KeywordGroupBox->setObjectName(QStringLiteral("KeywordGroupBox"));
        gridLayout2 = new QGridLayout(KeywordGroupBox);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        spacerItem3 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem3, 0, 0, 1, 1);

        textLabel1 = new QLabel(KeywordGroupBox);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout2->addWidget(textLabel1, 0, 1, 1, 1);

        SrcBox = new QComboBox(KeywordGroupBox);
        SrcBox->setObjectName(QStringLiteral("SrcBox"));

        gridLayout2->addWidget(SrcBox, 0, 2, 1, 1);

        TagBox = new QComboBox(KeywordGroupBox);
        TagBox->setObjectName(QStringLiteral("TagBox"));

        gridLayout2->addWidget(TagBox, 0, 3, 1, 1);

        Keywords = new QLineEdit(KeywordGroupBox);
        Keywords->setObjectName(QStringLiteral("Keywords"));

        gridLayout2->addWidget(Keywords, 1, 0, 1, 4);


        gridLayout_2->addWidget(KeywordGroupBox, 7, 0, 1, 3);

        DataWidget->addTab(TabName, QString());
        TabDate = new QWidget();
        TabDate->setObjectName(QStringLiteral("TabDate"));
        gridLayout3 = new QGridLayout(TabDate);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        Date = new QGroupBox(TabDate);
        Date->setObjectName(QStringLiteral("Date"));
        gridLayout4 = new QGridLayout(Date);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName(QStringLiteral("gridLayout4"));
        textLabel1_3 = new QLabel(Date);
        textLabel1_3->setObjectName(QStringLiteral("textLabel1_3"));
        textLabel1_3->setWordWrap(false);

        gridLayout4->addWidget(textLabel1_3, 0, 0, 1, 1);

        spacerItem4 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem4, 0, 1, 1, 1);

        textLabel2 = new QLabel(Date);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout4->addWidget(textLabel2, 0, 2, 1, 1);

        spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem5, 0, 3, 1, 1);

        textLabel3 = new QLabel(Date);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setWordWrap(false);

        gridLayout4->addWidget(textLabel3, 0, 4, 1, 1);

        spacerItem6 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem6, 0, 5, 1, 1);

        textLabel4 = new QLabel(Date);
        textLabel4->setObjectName(QStringLiteral("textLabel4"));
        textLabel4->setWordWrap(false);

        gridLayout4->addWidget(textLabel4, 0, 6, 1, 1);

        spacerItem7 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem7, 0, 7, 1, 1);

        textLabel5 = new QLabel(Date);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setWordWrap(false);

        gridLayout4->addWidget(textLabel5, 0, 8, 1, 1);

        spacerItem8 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem8, 0, 9, 1, 1);

        textLabel1_6 = new QLabel(Date);
        textLabel1_6->setObjectName(QStringLiteral("textLabel1_6"));
        textLabel1_6->setWordWrap(false);

        gridLayout4->addWidget(textLabel1_6, 0, 10, 1, 1);

        spacerItem9 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem9, 0, 11, 1, 1);

        textLabel6 = new QLabel(Date);
        textLabel6->setObjectName(QStringLiteral("textLabel6"));
        textLabel6->setWordWrap(false);

        gridLayout4->addWidget(textLabel6, 0, 12, 1, 1);

        Day = new QComboBox(Date);
        Day->setObjectName(QStringLiteral("Day"));
        sizePolicy2.setHeightForWidth(Day->sizePolicy().hasHeightForWidth());
        Day->setSizePolicy(sizePolicy2);

        gridLayout4->addWidget(Day, 1, 0, 1, 1);

        spacerItem10 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem10, 1, 1, 1, 1);

        Month = new QComboBox(Date);
        Month->setObjectName(QStringLiteral("Month"));

        gridLayout4->addWidget(Month, 1, 2, 1, 1);

        spacerItem11 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem11, 1, 3, 1, 1);

        Year = new AstroSpinBox(Date);
        Year->setObjectName(QStringLiteral("Year"));
        Year->setMinimum(-5401);
        Year->setMaximum(5399);
        Year->setProperty("maxValue", QVariant(5399));
        Year->setProperty("minValue", QVariant(-5401));

        gridLayout4->addWidget(Year, 1, 4, 1, 1);

        spacerItem12 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem12, 1, 5, 1, 1);

        Hour = new AstroSpinBox(Date);
        Hour->setObjectName(QStringLiteral("Hour"));
        Hour->setMaximum(23);
        Hour->setProperty("maxValue", QVariant(23));

        gridLayout4->addWidget(Hour, 1, 6, 1, 1);

        spacerItem13 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem13, 1, 7, 1, 1);

        Minute = new AstroSpinBox(Date);
        Minute->setObjectName(QStringLiteral("Minute"));
        Minute->setMaximum(59);
        Minute->setProperty("maxValue", QVariant(59));

        gridLayout4->addWidget(Minute, 1, 8, 1, 1);

        spacerItem14 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem14, 1, 9, 1, 1);

        Second = new AstroSpinBox(Date);
        Second->setObjectName(QStringLiteral("Second"));
        Second->setMaximum(59);
        Second->setProperty("maxValue", QVariant(59));

        gridLayout4->addWidget(Second, 1, 10, 1, 1);

        spacerItem15 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacerItem15, 1, 11, 1, 1);

        Accuracy = new AstroSpinBox(Date);
        Accuracy->setObjectName(QStringLiteral("Accuracy"));
        Accuracy->setMinimum(-1);
        Accuracy->setMaximum(300);
        Accuracy->setProperty("maxValue", QVariant(300));
        Accuracy->setProperty("minValue", QVariant(-1));

        gridLayout4->addWidget(Accuracy, 1, 12, 1, 1);


        gridLayout3->addWidget(Date, 0, 0, 1, 4);

        Preload = new QCheckBox(TabDate);
        Preload->setObjectName(QStringLiteral("Preload"));

        gridLayout3->addWidget(Preload, 1, 0, 1, 1);

        spacerItem16 = new QSpacerItem(290, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacerItem16, 1, 1, 1, 2);

        NowButton = new QPushButton(TabDate);
        NowButton->setObjectName(QStringLiteral("NowButton"));

        gridLayout3->addWidget(NowButton, 1, 3, 1, 1);

        Automatic = new QCheckBox(TabDate);
        Automatic->setObjectName(QStringLiteral("Automatic"));

        gridLayout3->addWidget(Automatic, 2, 0, 1, 1);

        TimeZoneGroupBox = new QGroupBox(TabDate);
        TimeZoneGroupBox->setObjectName(QStringLiteral("TimeZoneGroupBox"));
        gridLayout5 = new QGridLayout(TimeZoneGroupBox);
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(11, 11, 11, 11);
        gridLayout5->setObjectName(QStringLiteral("gridLayout5"));
        TextLabel1_2 = new QLabel(TimeZoneGroupBox);
        TextLabel1_2->setObjectName(QStringLiteral("TextLabel1_2"));
        TextLabel1_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        TextLabel1_2->setWordWrap(false);

        gridLayout5->addWidget(TextLabel1_2, 0, 0, 1, 1);

        spacerItem17 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout5->addItem(spacerItem17, 0, 1, 1, 1);

        TimezoneLine = new QLineEdit(TimeZoneGroupBox);
        TimezoneLine->setObjectName(QStringLiteral("TimezoneLine"));
        TimezoneLine->setAlignment(Qt::AlignRight);

        gridLayout5->addWidget(TimezoneLine, 0, 2, 1, 1);

        textLabel1_2 = new QLabel(TimeZoneGroupBox);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        gridLayout5->addWidget(textLabel1_2, 1, 0, 1, 1);

        DtsChoice = new QComboBox(TimeZoneGroupBox);
        DtsChoice->setObjectName(QStringLiteral("DtsChoice"));
        DtsChoice->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(DtsChoice->sizePolicy().hasHeightForWidth());
        DtsChoice->setSizePolicy(sizePolicy3);

        gridLayout5->addWidget(DtsChoice, 1, 1, 1, 1);

        DaylightLine = new QLineEdit(TimeZoneGroupBox);
        DaylightLine->setObjectName(QStringLiteral("DaylightLine"));
        DaylightLine->setAlignment(Qt::AlignRight);

        gridLayout5->addWidget(DaylightLine, 1, 2, 1, 1);

        RecomputeButton = new QPushButton(TimeZoneGroupBox);
        RecomputeButton->setObjectName(QStringLiteral("RecomputeButton"));

        gridLayout5->addWidget(RecomputeButton, 2, 1, 1, 2);


        gridLayout3->addWidget(TimeZoneGroupBox, 2, 2, 5, 2);

        HMSButton = new QCheckBox(TabDate);
        HMSButton->setObjectName(QStringLiteral("HMSButton"));

        gridLayout3->addWidget(HMSButton, 3, 0, 1, 1);

        ToSecond = new QCheckBox(TabDate);
        ToSecond->setObjectName(QStringLiteral("ToSecond"));

        gridLayout3->addWidget(ToSecond, 4, 0, 1, 1);

        TrueSolarTime = new QCheckBox(TabDate);
        TrueSolarTime->setObjectName(QStringLiteral("TrueSolarTime"));

        gridLayout3->addWidget(TrueSolarTime, 5, 0, 1, 1);

        DSLabel = new QLabel(TabDate);
        DSLabel->setObjectName(QStringLiteral("DSLabel"));
        DSLabel->setWordWrap(false);

        gridLayout3->addWidget(DSLabel, 6, 0, 1, 1);

        DateSystem = new QLabel(TabDate);
        DateSystem->setObjectName(QStringLiteral("DateSystem"));
        DateSystem->setWordWrap(false);

        gridLayout3->addWidget(DateSystem, 6, 1, 1, 1);

        textLabel1_4 = new QLabel(TabDate);
        textLabel1_4->setObjectName(QStringLiteral("textLabel1_4"));
        textLabel1_4->setWordWrap(false);

        gridLayout3->addWidget(textLabel1_4, 7, 0, 1, 1);

        Julday = new QLabel(TabDate);
        Julday->setObjectName(QStringLiteral("Julday"));
        Julday->setWordWrap(false);

        gridLayout3->addWidget(Julday, 7, 1, 1, 1);

        spacerItem18 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacerItem18, 8, 0, 1, 1);

        spacerItem19 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacerItem19, 8, 1, 1, 1);

        spacerItem20 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout3->addItem(spacerItem20, 8, 3, 1, 1);

        DataWidget->addTab(TabDate, QString());
        TabPlace = new QWidget();
        TabPlace->setObjectName(QStringLiteral("TabPlace"));
        gridLayout6 = new QGridLayout(TabPlace);
        gridLayout6->setSpacing(6);
        gridLayout6->setContentsMargins(11, 11, 11, 11);
        gridLayout6->setObjectName(QStringLiteral("gridLayout6"));
        PlaceEdition = new EditPlace(TabPlace);
        PlaceEdition->setObjectName(QStringLiteral("PlaceEdition"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(PlaceEdition->sizePolicy().hasHeightForWidth());
        PlaceEdition->setSizePolicy(sizePolicy4);
        PlaceEdition->setMinimumSize(QSize(0, 0));

        gridLayout6->addWidget(PlaceEdition, 0, 0, 1, 1);

        DataWidget->addTab(TabPlace, QString());
        TabComment = new QWidget();
        TabComment->setObjectName(QStringLiteral("TabComment"));
        gridLayout7 = new QGridLayout(TabComment);
        gridLayout7->setSpacing(6);
        gridLayout7->setContentsMargins(11, 11, 11, 11);
        gridLayout7->setObjectName(QStringLiteral("gridLayout7"));
        Comment = new QTextEdit(TabComment);
        Comment->setObjectName(QStringLiteral("Comment"));

        gridLayout7->addWidget(Comment, 0, 0, 1, 1);

        DataWidget->addTab(TabComment, QString());

        gridLayout->addWidget(DataWidget, 0, 0, 1, 3);

        QWidget::setTabOrder(DataWidget, Name);
        QWidget::setTabOrder(Name, TypeofChart);
        QWidget::setTabOrder(TypeofChart, SrcBox);
        QWidget::setTabOrder(SrcBox, TagBox);
        QWidget::setTabOrder(TagBox, Keywords);
        QWidget::setTabOrder(Keywords, Day);
        QWidget::setTabOrder(Day, Month);
        QWidget::setTabOrder(Month, Preload);
        QWidget::setTabOrder(Preload, Automatic);
        QWidget::setTabOrder(Automatic, HMSButton);
        QWidget::setTabOrder(HMSButton, ToSecond);
        QWidget::setTabOrder(ToSecond, NowButton);
        QWidget::setTabOrder(NowButton, TimezoneLine);
        QWidget::setTabOrder(TimezoneLine, DtsChoice);
        QWidget::setTabOrder(DtsChoice, DaylightLine);
        QWidget::setTabOrder(DaylightLine, RecomputeButton);
        QWidget::setTabOrder(RecomputeButton, OkButton);
        QWidget::setTabOrder(OkButton, CancelButton);

        retranslateUi(EditAstroData);

        OkButton->setDefault(true);
        DataWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditAstroData);
    } // setupUi

    void retranslateUi(QDialog *EditAstroData)
    {
        EditAstroData->setWindowTitle(QApplication::translate("EditAstroData", "New/Edit data", 0));
        OkButton->setText(QApplication::translate("EditAstroData", "Ok", 0));
        Error->setText(QString());
        CancelButton->setText(QApplication::translate("EditAstroData", "Cancel", 0));
        TextLabel1->setText(QApplication::translate("EditAstroData", "Name:", 0));
        TextLabel2->setText(QApplication::translate("EditAstroData", "Gender:", 0));
        GenderGroup->setTitle(QString());
        MaleButton->setText(QApplication::translate("EditAstroData", "&Male", 0));
        FemaleButton->setText(QApplication::translate("EditAstroData", "Female", 0));
        NeutralButton->setText(QApplication::translate("EditAstroData", "Neutral", 0));
        SituationButton->setText(QApplication::translate("EditAstroData", "Si&tuation", 0));
        TextLabel3->setText(QApplication::translate("EditAstroData", "Type:", 0));
        KeywordGroupBox->setTitle(QApplication::translate("EditAstroData", "Keywords", 0));
        textLabel1->setText(QApplication::translate("EditAstroData", "Orig:", 0));
        SrcBox->clear();
        SrcBox->insertItems(0, QStringList()
         << QApplication::translate("EditAstroData", "Direct", 0)
         << QApplication::translate("EditAstroData", "Register", 0)
         << QApplication::translate("EditAstroData", "Family Book", 0)
         << QApplication::translate("EditAstroData", "Astrologer", 0)
         << QApplication::translate("EditAstroData", "Mother", 0)
         << QApplication::translate("EditAstroData", "Father", 0)
         << QApplication::translate("EditAstroData", "Personal", 0)
         << QApplication::translate("EditAstroData", "Biography", 0)
         << QApplication::translate("EditAstroData", "Partner", 0)
         << QApplication::translate("EditAstroData", "Possibility", 0)
         << QApplication::translate("EditAstroData", "Speculation", 0)
        );
        TagBox->clear();
        TagBox->insertItems(0, QStringList()
         << QApplication::translate("EditAstroData", "Profession", 0)
         << QApplication::translate("EditAstroData", "Children", 0)
         << QApplication::translate("EditAstroData", "Illness", 0)
         << QApplication::translate("EditAstroData", "Source Doc", 0)
         << QApplication::translate("EditAstroData", "Via", 0)
         << QApplication::translate("EditAstroData", "Orig Comm", 0)
         << QApplication::translate("EditAstroData", "Nationality", 0)
        );
        DataWidget->setTabText(DataWidget->indexOf(TabName), QApplication::translate("EditAstroData", "Name", 0));
        Date->setTitle(QApplication::translate("EditAstroData", "Date and Time", 0));
        textLabel1_3->setText(QApplication::translate("EditAstroData", "Day", 0));
        textLabel2->setText(QApplication::translate("EditAstroData", "Month", 0));
        textLabel3->setText(QApplication::translate("EditAstroData", "Year", 0));
        textLabel4->setText(QApplication::translate("EditAstroData", "Hour", 0));
        textLabel5->setText(QApplication::translate("EditAstroData", "Minute", 0));
        textLabel1_6->setText(QApplication::translate("EditAstroData", "Second", 0));
        textLabel6->setText(QApplication::translate("EditAstroData", "Accuracy", 0));
        Day->clear();
        Day->insertItems(0, QStringList()
         << QApplication::translate("EditAstroData", "1", 0)
         << QApplication::translate("EditAstroData", "2", 0)
         << QApplication::translate("EditAstroData", "3", 0)
         << QApplication::translate("EditAstroData", "4", 0)
         << QApplication::translate("EditAstroData", "5", 0)
         << QApplication::translate("EditAstroData", "6", 0)
         << QApplication::translate("EditAstroData", "7", 0)
         << QApplication::translate("EditAstroData", "8", 0)
         << QApplication::translate("EditAstroData", "9", 0)
         << QApplication::translate("EditAstroData", "10 ", 0)
         << QApplication::translate("EditAstroData", "11 ", 0)
         << QApplication::translate("EditAstroData", "12 ", 0)
         << QApplication::translate("EditAstroData", "13", 0)
         << QApplication::translate("EditAstroData", "14", 0)
         << QApplication::translate("EditAstroData", "15", 0)
         << QApplication::translate("EditAstroData", "16", 0)
         << QApplication::translate("EditAstroData", "17", 0)
         << QApplication::translate("EditAstroData", "18", 0)
         << QApplication::translate("EditAstroData", "19", 0)
         << QApplication::translate("EditAstroData", "20", 0)
         << QApplication::translate("EditAstroData", "21", 0)
         << QApplication::translate("EditAstroData", "22", 0)
         << QApplication::translate("EditAstroData", "23", 0)
         << QApplication::translate("EditAstroData", "24", 0)
         << QApplication::translate("EditAstroData", "25", 0)
         << QApplication::translate("EditAstroData", "26", 0)
         << QApplication::translate("EditAstroData", "27", 0)
         << QApplication::translate("EditAstroData", "28", 0)
         << QApplication::translate("EditAstroData", "29", 0)
         << QApplication::translate("EditAstroData", "30", 0)
         << QApplication::translate("EditAstroData", "31", 0)
        );
        Month->clear();
        Month->insertItems(0, QStringList()
         << QApplication::translate("EditAstroData", "January", 0)
         << QApplication::translate("EditAstroData", "February", 0)
         << QApplication::translate("EditAstroData", "March", 0)
         << QApplication::translate("EditAstroData", "April", 0)
         << QApplication::translate("EditAstroData", "May", 0)
         << QApplication::translate("EditAstroData", "June", 0)
         << QApplication::translate("EditAstroData", "July", 0)
         << QApplication::translate("EditAstroData", "August", 0)
         << QApplication::translate("EditAstroData", "September", 0)
         << QApplication::translate("EditAstroData", "October", 0)
         << QApplication::translate("EditAstroData", "November", 0)
         << QApplication::translate("EditAstroData", "December", 0)
        );
        Preload->setText(QApplication::translate("EditAstroData", "Preload", 0));
#ifndef QT_NO_TOOLTIP
        NowButton->setToolTip(QApplication::translate("EditAstroData", "Set the actual time", 0));
#endif // QT_NO_TOOLTIP
        NowButton->setText(QApplication::translate("EditAstroData", "Now", 0));
#ifndef QT_NO_TOOLTIP
        Automatic->setToolTip(QApplication::translate("EditAstroData", "Automatically recompute daylight time saving & time zone", 0));
#endif // QT_NO_TOOLTIP
        Automatic->setText(QApplication::translate("EditAstroData", "Automatic", 0));
        TimeZoneGroupBox->setTitle(QApplication::translate("EditAstroData", "Daylight and TimeZone", 0));
        TextLabel1_2->setText(QApplication::translate("EditAstroData", "Timezone:", 0));
#ifndef QT_NO_TOOLTIP
        TimezoneLine->setToolTip(QApplication::translate("EditAstroData", "Put here the Hour:Minute time zone offset", 0));
#endif // QT_NO_TOOLTIP
        textLabel1_2->setText(QApplication::translate("EditAstroData", "Daylight:", 0));
        DtsChoice->clear();
        DtsChoice->insertItems(0, QStringList()
         << QApplication::translate("EditAstroData", "0", 0)
         << QApplication::translate("EditAstroData", "1:00", 0)
         << QApplication::translate("EditAstroData", "2:00", 0)
         << QApplication::translate("EditAstroData", "0:30", 0)
        );
#ifndef QT_NO_TOOLTIP
        DtsChoice->setToolTip(QApplication::translate("EditAstroData", "Choice of classical Daylight Time Saving offsets", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RecomputeButton->setToolTip(QApplication::translate("EditAstroData", "Manually recompute daylight saving & time zone", 0));
#endif // QT_NO_TOOLTIP
        RecomputeButton->setText(QApplication::translate("EditAstroData", "<<", 0));
#ifndef QT_NO_TOOLTIP
        HMSButton->setToolTip(QApplication::translate("EditAstroData", "if longitude value expressed in hour:min:sec", 0));
#endif // QT_NO_TOOLTIP
        HMSButton->setText(QApplication::translate("EditAstroData", "H:M.S Longitude", 0));
        ToSecond->setText(QApplication::translate("EditAstroData", "To the Second", 0));
        TrueSolarTime->setText(QApplication::translate("EditAstroData", "True Solar Time", 0));
        DSLabel->setText(QApplication::translate("EditAstroData", "Date System:", 0));
        DateSystem->setText(QString());
        textLabel1_4->setText(QApplication::translate("EditAstroData", "Julian Day:", 0));
        Julday->setText(QString());
        DataWidget->setTabText(DataWidget->indexOf(TabDate), QApplication::translate("EditAstroData", "Date", 0));
        DataWidget->setTabText(DataWidget->indexOf(TabPlace), QApplication::translate("EditAstroData", "Place", 0));
        DataWidget->setTabText(DataWidget->indexOf(TabComment), QApplication::translate("EditAstroData", "Comment", 0));
    } // retranslateUi

};

namespace Ui {
    class EditAstroData: public Ui_EditAstroData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITASTRODATA_H
