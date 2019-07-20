/********************************************************************************
** Form generated from reading UI file 'editdefparms.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDEFPARMS_H
#define UI_EDITDEFPARMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <astrospinbox.h>
#include "astrochoosecol.h"
#include "astrospinbox.h"

QT_BEGIN_NAMESPACE

class Ui_EditDefParms
{
public:
    QGridLayout *gridLayout;
    QPushButton *OkButton;
    QPushButton *DefChartParms;
    QPushButton *CancelButton;
    QTabWidget *TabWidget2;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QLineEdit *ZoneInfoPath;
    QLabel *TextLabel1;
    QLineEdit *ExtraTime;
    QLabel *TextLabel3;
    QCheckBox *PrintBW;
    QCheckBox *UTC;
    QCheckBox *CustomDT;
    QCheckBox *InvBack;
    QCheckBox *RightDW;
    QSpinBox *ZoomFactor;
    QLabel *textLabel1;
    AstroSpinBox *NbLines;
    QLabel *textLabel1_2;
    QLineEdit *Astrologer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *Background;
    QPushButton *BackFile;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QLineEdit *UserName;
    QLabel *label_3;
    QLineEdit *Password;
    QLabel *label_4;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *Temp;
    QLabel *label_8;
    QDoubleSpinBox *Press;
    QLabel *label_9;
    QSpinBox *Humid;
    QLabel *label_10;
    QWidget *tab1;
    QGridLayout *gridLayout_4;
    AstroSpinBox *Width;
    QLabel *TextLabel4;
    QCheckBox *Antialias;
    AstroSpinBox *Height;
    QLabel *TextLabel5;
    QSpacerItem *horizontalSpacer;
    QSpinBox *IncDecGlyph;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QFontComboBox *TextFont;
    QLabel *label_6;
    QSpinBox *FontSize;
    QLabel *label_7;
    QLabel *LazyDog;
    QSpacerItem *verticalSpacer;
    QWidget *tab2;
    QGridLayout *gridLayout2;
    QGroupBox *ColorsGroupBox1;
    QGridLayout *gridLayout3;
    QPushButton *FireColor;
    QLabel *TextLabel6;
    QPushButton *AsteroColor;
    QLabel *TextLabel9_2;
    QPushButton *AirColor;
    QLabel *TextLabel7;
    QPushButton *ExtraColor;
    QLabel *TextLabel9_2_2;
    QPushButton *WaterColor;
    QLabel *TextLabel8;
    QPushButton *OtherColor;
    QLabel *TextLabel9_2_3;
    QPushButton *EarthColor;
    QLabel *TextLabel9;
    QGroupBox *PaletteGroupBox1;
    QGridLayout *gridLayout4;
    AstroChooseCol *Col0;
    AstroChooseCol *Col1;
    AstroChooseCol *Col2;
    AstroChooseCol *Col3;
    AstroChooseCol *Col4;
    AstroChooseCol *Col5;
    AstroChooseCol *Col6;
    AstroChooseCol *Col7;
    AstroChooseCol *Col8;
    AstroChooseCol *Col9;
    AstroChooseCol *Col10;
    AstroChooseCol *Col11;
    AstroChooseCol *Col12;
    AstroChooseCol *Col13;
    AstroChooseCol *Col14;
    AstroChooseCol *Col15;

    void setupUi(QDialog *EditDefParms)
    {
        if (EditDefParms->objectName().isEmpty())
            EditDefParms->setObjectName(QStringLiteral("EditDefParms"));
        EditDefParms->resize(681, 532);
        gridLayout = new QGridLayout(EditDefParms);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        OkButton = new QPushButton(EditDefParms);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        gridLayout->addWidget(OkButton, 1, 0, 1, 1);

        DefChartParms = new QPushButton(EditDefParms);
        DefChartParms->setObjectName(QStringLiteral("DefChartParms"));

        gridLayout->addWidget(DefChartParms, 1, 1, 1, 1);

        CancelButton = new QPushButton(EditDefParms);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout->addWidget(CancelButton, 1, 2, 1, 1);

        TabWidget2 = new QTabWidget(EditDefParms);
        TabWidget2->setObjectName(QStringLiteral("TabWidget2"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        ZoneInfoPath = new QLineEdit(tab);
        ZoneInfoPath->setObjectName(QStringLiteral("ZoneInfoPath"));

        gridLayout_5->addWidget(ZoneInfoPath, 0, 0, 1, 1);

        TextLabel1 = new QLabel(tab);
        TextLabel1->setObjectName(QStringLiteral("TextLabel1"));
        TextLabel1->setWordWrap(false);

        gridLayout_5->addWidget(TextLabel1, 0, 3, 1, 1);

        ExtraTime = new QLineEdit(tab);
        ExtraTime->setObjectName(QStringLiteral("ExtraTime"));
        ExtraTime->setAlignment(Qt::AlignRight);

        gridLayout_5->addWidget(ExtraTime, 1, 0, 1, 1);

        TextLabel3 = new QLabel(tab);
        TextLabel3->setObjectName(QStringLiteral("TextLabel3"));
        TextLabel3->setWordWrap(false);

        gridLayout_5->addWidget(TextLabel3, 1, 3, 1, 1);

        PrintBW = new QCheckBox(tab);
        PrintBW->setObjectName(QStringLiteral("PrintBW"));

        gridLayout_5->addWidget(PrintBW, 2, 0, 1, 1);

        UTC = new QCheckBox(tab);
        UTC->setObjectName(QStringLiteral("UTC"));

        gridLayout_5->addWidget(UTC, 2, 3, 1, 2);

        CustomDT = new QCheckBox(tab);
        CustomDT->setObjectName(QStringLiteral("CustomDT"));

        gridLayout_5->addWidget(CustomDT, 3, 0, 1, 1);

        InvBack = new QCheckBox(tab);
        InvBack->setObjectName(QStringLiteral("InvBack"));

        gridLayout_5->addWidget(InvBack, 3, 3, 1, 2);

        RightDW = new QCheckBox(tab);
        RightDW->setObjectName(QStringLiteral("RightDW"));

        gridLayout_5->addWidget(RightDW, 4, 0, 1, 1);

        ZoomFactor = new QSpinBox(tab);
        ZoomFactor->setObjectName(QStringLiteral("ZoomFactor"));
        ZoomFactor->setMinimum(1);
        ZoomFactor->setMaximum(1000);
        ZoomFactor->setValue(100);

        gridLayout_5->addWidget(ZoomFactor, 5, 0, 1, 1);

        textLabel1 = new QLabel(tab);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout_5->addWidget(textLabel1, 5, 1, 1, 2);

        NbLines = new AstroSpinBox(tab);
        NbLines->setObjectName(QStringLiteral("NbLines"));
        NbLines->setMaximum(3000);
        NbLines->setValue(99);
        NbLines->setProperty("maxValue", QVariant(3000));
        NbLines->setProperty("minValue", QVariant(100));

        gridLayout_5->addWidget(NbLines, 6, 0, 1, 1);

        textLabel1_2 = new QLabel(tab);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        gridLayout_5->addWidget(textLabel1_2, 6, 1, 1, 4);

        Astrologer = new QLineEdit(tab);
        Astrologer->setObjectName(QStringLiteral("Astrologer"));

        gridLayout_5->addWidget(Astrologer, 7, 0, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 7, 2, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(187, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 7, 4, 1, 1);

        Background = new QComboBox(tab);
        Background->setObjectName(QStringLiteral("Background"));

        gridLayout_5->addWidget(Background, 8, 0, 1, 1);

        BackFile = new QPushButton(tab);
        BackFile->setObjectName(QStringLiteral("BackFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/pics/document-open.png"), QSize(), QIcon::Normal, QIcon::On);
        BackFile->setIcon(icon);

        gridLayout_5->addWidget(BackFile, 8, 1, 1, 1);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 8, 2, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(187, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 8, 4, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout1 = new QGridLayout(groupBox);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        UserName = new QLineEdit(groupBox);
        UserName->setObjectName(QStringLiteral("UserName"));

        gridLayout1->addWidget(UserName, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout1->addWidget(label_3, 0, 1, 1, 1);

        Password = new QLineEdit(groupBox);
        Password->setObjectName(QStringLiteral("Password"));
        Password->setEchoMode(QLineEdit::Password);

        gridLayout1->addWidget(Password, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout1->addWidget(label_4, 1, 1, 1, 1);


        gridLayout_5->addWidget(groupBox, 9, 0, 1, 3);

        frame_2 = new QFrame(tab);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        Temp = new QDoubleSpinBox(frame_2);
        Temp->setObjectName(QStringLiteral("Temp"));
        Temp->setMinimum(-273);
        Temp->setMaximum(100);
        Temp->setValue(20);

        gridLayout_3->addWidget(Temp, 0, 0, 1, 1);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 0, 1, 1, 1);

        Press = new QDoubleSpinBox(frame_2);
        Press->setObjectName(QStringLiteral("Press"));
        Press->setDecimals(2);
        Press->setMaximum(2000);
        Press->setValue(1023);

        gridLayout_3->addWidget(Press, 1, 0, 1, 1);

        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_3->addWidget(label_9, 1, 1, 1, 1);

        Humid = new QSpinBox(frame_2);
        Humid->setObjectName(QStringLiteral("Humid"));
        Humid->setMaximum(100);

        gridLayout_3->addWidget(Humid, 2, 0, 1, 1);

        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 2, 1, 1, 1);


        gridLayout_5->addWidget(frame_2, 9, 3, 1, 2);

        TabWidget2->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        gridLayout_4 = new QGridLayout(tab1);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        Width = new AstroSpinBox(tab1);
        Width->setObjectName(QStringLiteral("Width"));
        Width->setMaximum(10000);
        Width->setProperty("maxValue", QVariant(5000));
        Width->setProperty("minValue", QVariant(100));

        gridLayout_4->addWidget(Width, 0, 0, 1, 1);

        TextLabel4 = new QLabel(tab1);
        TextLabel4->setObjectName(QStringLiteral("TextLabel4"));
        TextLabel4->setWordWrap(false);

        gridLayout_4->addWidget(TextLabel4, 0, 1, 1, 1);

        Antialias = new QCheckBox(tab1);
        Antialias->setObjectName(QStringLiteral("Antialias"));

        gridLayout_4->addWidget(Antialias, 0, 3, 1, 2);

        Height = new AstroSpinBox(tab1);
        Height->setObjectName(QStringLiteral("Height"));
        Height->setMaximum(10000);
        Height->setProperty("maxValue", QVariant(5000));
        Height->setProperty("minValue", QVariant(100));

        gridLayout_4->addWidget(Height, 1, 0, 1, 1);

        TextLabel5 = new QLabel(tab1);
        TextLabel5->setObjectName(QStringLiteral("TextLabel5"));
        TextLabel5->setWordWrap(false);

        gridLayout_4->addWidget(TextLabel5, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(287, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 2, 1, 1);

        IncDecGlyph = new QSpinBox(tab1);
        IncDecGlyph->setObjectName(QStringLiteral("IncDecGlyph"));
        IncDecGlyph->setMinimum(-5);
        IncDecGlyph->setMaximum(5);

        gridLayout_4->addWidget(IncDecGlyph, 1, 3, 1, 1);

        label = new QLabel(tab1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 1, 4, 1, 1);

        frame = new QFrame(tab1);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        TextFont = new QFontComboBox(frame);
        TextFont->setObjectName(QStringLiteral("TextFont"));

        gridLayout_2->addWidget(TextFont, 0, 0, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 0, 1, 1, 1);

        FontSize = new QSpinBox(frame);
        FontSize->setObjectName(QStringLiteral("FontSize"));
        FontSize->setMinimum(4);
        FontSize->setValue(10);

        gridLayout_2->addWidget(FontSize, 0, 2, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 3, 1, 1);

        LazyDog = new QLabel(frame);
        LazyDog->setObjectName(QStringLiteral("LazyDog"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LazyDog->sizePolicy().hasHeightForWidth());
        LazyDog->setSizePolicy(sizePolicy);
        LazyDog->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(LazyDog, 1, 0, 1, 4);


        gridLayout_4->addWidget(frame, 2, 0, 1, 5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 3, 1, 1, 1);

        TabWidget2->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        gridLayout2 = new QGridLayout(tab2);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        ColorsGroupBox1 = new QGroupBox(tab2);
        ColorsGroupBox1->setObjectName(QStringLiteral("ColorsGroupBox1"));
        gridLayout3 = new QGridLayout(ColorsGroupBox1);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        FireColor = new QPushButton(ColorsGroupBox1);
        FireColor->setObjectName(QStringLiteral("FireColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(FireColor->sizePolicy().hasHeightForWidth());
        FireColor->setSizePolicy(sizePolicy1);
        FireColor->setFlat(true);

        gridLayout3->addWidget(FireColor, 0, 0, 1, 1);

        TextLabel6 = new QLabel(ColorsGroupBox1);
        TextLabel6->setObjectName(QStringLiteral("TextLabel6"));
        TextLabel6->setWordWrap(false);

        gridLayout3->addWidget(TextLabel6, 0, 1, 1, 1);

        AsteroColor = new QPushButton(ColorsGroupBox1);
        AsteroColor->setObjectName(QStringLiteral("AsteroColor"));
        sizePolicy1.setHeightForWidth(AsteroColor->sizePolicy().hasHeightForWidth());
        AsteroColor->setSizePolicy(sizePolicy1);
        AsteroColor->setFlat(true);

        gridLayout3->addWidget(AsteroColor, 0, 2, 1, 1);

        TextLabel9_2 = new QLabel(ColorsGroupBox1);
        TextLabel9_2->setObjectName(QStringLiteral("TextLabel9_2"));
        TextLabel9_2->setWordWrap(false);

        gridLayout3->addWidget(TextLabel9_2, 0, 3, 1, 1);

        AirColor = new QPushButton(ColorsGroupBox1);
        AirColor->setObjectName(QStringLiteral("AirColor"));
        sizePolicy1.setHeightForWidth(AirColor->sizePolicy().hasHeightForWidth());
        AirColor->setSizePolicy(sizePolicy1);
        AirColor->setFlat(true);

        gridLayout3->addWidget(AirColor, 1, 0, 1, 1);

        TextLabel7 = new QLabel(ColorsGroupBox1);
        TextLabel7->setObjectName(QStringLiteral("TextLabel7"));
        TextLabel7->setWordWrap(false);

        gridLayout3->addWidget(TextLabel7, 1, 1, 1, 1);

        ExtraColor = new QPushButton(ColorsGroupBox1);
        ExtraColor->setObjectName(QStringLiteral("ExtraColor"));
        sizePolicy1.setHeightForWidth(ExtraColor->sizePolicy().hasHeightForWidth());
        ExtraColor->setSizePolicy(sizePolicy1);
        ExtraColor->setFlat(true);

        gridLayout3->addWidget(ExtraColor, 1, 2, 1, 1);

        TextLabel9_2_2 = new QLabel(ColorsGroupBox1);
        TextLabel9_2_2->setObjectName(QStringLiteral("TextLabel9_2_2"));
        TextLabel9_2_2->setWordWrap(false);

        gridLayout3->addWidget(TextLabel9_2_2, 1, 3, 1, 1);

        WaterColor = new QPushButton(ColorsGroupBox1);
        WaterColor->setObjectName(QStringLiteral("WaterColor"));
        sizePolicy1.setHeightForWidth(WaterColor->sizePolicy().hasHeightForWidth());
        WaterColor->setSizePolicy(sizePolicy1);
        WaterColor->setFlat(true);

        gridLayout3->addWidget(WaterColor, 2, 0, 1, 1);

        TextLabel8 = new QLabel(ColorsGroupBox1);
        TextLabel8->setObjectName(QStringLiteral("TextLabel8"));
        TextLabel8->setWordWrap(false);

        gridLayout3->addWidget(TextLabel8, 2, 1, 1, 1);

        OtherColor = new QPushButton(ColorsGroupBox1);
        OtherColor->setObjectName(QStringLiteral("OtherColor"));
        sizePolicy1.setHeightForWidth(OtherColor->sizePolicy().hasHeightForWidth());
        OtherColor->setSizePolicy(sizePolicy1);
        OtherColor->setFlat(true);

        gridLayout3->addWidget(OtherColor, 2, 2, 1, 1);

        TextLabel9_2_3 = new QLabel(ColorsGroupBox1);
        TextLabel9_2_3->setObjectName(QStringLiteral("TextLabel9_2_3"));
        TextLabel9_2_3->setWordWrap(false);

        gridLayout3->addWidget(TextLabel9_2_3, 2, 3, 1, 1);

        EarthColor = new QPushButton(ColorsGroupBox1);
        EarthColor->setObjectName(QStringLiteral("EarthColor"));
        sizePolicy1.setHeightForWidth(EarthColor->sizePolicy().hasHeightForWidth());
        EarthColor->setSizePolicy(sizePolicy1);
        EarthColor->setFlat(true);

        gridLayout3->addWidget(EarthColor, 3, 0, 1, 1);

        TextLabel9 = new QLabel(ColorsGroupBox1);
        TextLabel9->setObjectName(QStringLiteral("TextLabel9"));
        TextLabel9->setWordWrap(false);

        gridLayout3->addWidget(TextLabel9, 3, 1, 1, 1);


        gridLayout2->addWidget(ColorsGroupBox1, 0, 0, 1, 1);

        PaletteGroupBox1 = new QGroupBox(tab2);
        PaletteGroupBox1->setObjectName(QStringLiteral("PaletteGroupBox1"));
        gridLayout4 = new QGridLayout(PaletteGroupBox1);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName(QStringLiteral("gridLayout4"));
        Col0 = new AstroChooseCol(PaletteGroupBox1);
        Col0->setObjectName(QStringLiteral("Col0"));

        gridLayout4->addWidget(Col0, 0, 0, 1, 1);

        Col1 = new AstroChooseCol(PaletteGroupBox1);
        Col1->setObjectName(QStringLiteral("Col1"));

        gridLayout4->addWidget(Col1, 0, 1, 1, 1);

        Col2 = new AstroChooseCol(PaletteGroupBox1);
        Col2->setObjectName(QStringLiteral("Col2"));

        gridLayout4->addWidget(Col2, 0, 2, 1, 1);

        Col3 = new AstroChooseCol(PaletteGroupBox1);
        Col3->setObjectName(QStringLiteral("Col3"));

        gridLayout4->addWidget(Col3, 0, 3, 1, 1);

        Col4 = new AstroChooseCol(PaletteGroupBox1);
        Col4->setObjectName(QStringLiteral("Col4"));

        gridLayout4->addWidget(Col4, 0, 4, 1, 1);

        Col5 = new AstroChooseCol(PaletteGroupBox1);
        Col5->setObjectName(QStringLiteral("Col5"));

        gridLayout4->addWidget(Col5, 0, 5, 1, 1);

        Col6 = new AstroChooseCol(PaletteGroupBox1);
        Col6->setObjectName(QStringLiteral("Col6"));

        gridLayout4->addWidget(Col6, 0, 6, 1, 1);

        Col7 = new AstroChooseCol(PaletteGroupBox1);
        Col7->setObjectName(QStringLiteral("Col7"));

        gridLayout4->addWidget(Col7, 0, 7, 1, 1);

        Col8 = new AstroChooseCol(PaletteGroupBox1);
        Col8->setObjectName(QStringLiteral("Col8"));

        gridLayout4->addWidget(Col8, 1, 0, 1, 1);

        Col9 = new AstroChooseCol(PaletteGroupBox1);
        Col9->setObjectName(QStringLiteral("Col9"));

        gridLayout4->addWidget(Col9, 1, 1, 1, 1);

        Col10 = new AstroChooseCol(PaletteGroupBox1);
        Col10->setObjectName(QStringLiteral("Col10"));

        gridLayout4->addWidget(Col10, 1, 2, 1, 1);

        Col11 = new AstroChooseCol(PaletteGroupBox1);
        Col11->setObjectName(QStringLiteral("Col11"));

        gridLayout4->addWidget(Col11, 1, 3, 1, 1);

        Col12 = new AstroChooseCol(PaletteGroupBox1);
        Col12->setObjectName(QStringLiteral("Col12"));

        gridLayout4->addWidget(Col12, 1, 4, 1, 1);

        Col13 = new AstroChooseCol(PaletteGroupBox1);
        Col13->setObjectName(QStringLiteral("Col13"));

        gridLayout4->addWidget(Col13, 1, 5, 1, 1);

        Col14 = new AstroChooseCol(PaletteGroupBox1);
        Col14->setObjectName(QStringLiteral("Col14"));

        gridLayout4->addWidget(Col14, 1, 6, 1, 1);

        Col15 = new AstroChooseCol(PaletteGroupBox1);
        Col15->setObjectName(QStringLiteral("Col15"));

        gridLayout4->addWidget(Col15, 1, 7, 1, 1);


        gridLayout2->addWidget(PaletteGroupBox1, 2, 0, 1, 1);

        TabWidget2->addTab(tab2, QString());

        gridLayout->addWidget(TabWidget2, 0, 0, 1, 3);

        QWidget::setTabOrder(TabWidget2, ZoneInfoPath);
        QWidget::setTabOrder(ZoneInfoPath, ExtraTime);
        QWidget::setTabOrder(ExtraTime, Width);
        QWidget::setTabOrder(Width, Height);
        QWidget::setTabOrder(Height, FireColor);
        QWidget::setTabOrder(FireColor, AirColor);
        QWidget::setTabOrder(AirColor, WaterColor);
        QWidget::setTabOrder(WaterColor, EarthColor);
        QWidget::setTabOrder(EarthColor, AsteroColor);
        QWidget::setTabOrder(AsteroColor, ExtraColor);
        QWidget::setTabOrder(ExtraColor, OtherColor);
        QWidget::setTabOrder(OtherColor, OkButton);
        QWidget::setTabOrder(OkButton, DefChartParms);
        QWidget::setTabOrder(DefChartParms, CancelButton);

        retranslateUi(EditDefParms);

        OkButton->setDefault(true);
        TabWidget2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditDefParms);
    } // setupUi

    void retranslateUi(QDialog *EditDefParms)
    {
        EditDefParms->setWindowTitle(QApplication::translate("EditDefParms", "Edit default parameters", 0));
        OkButton->setText(QApplication::translate("EditDefParms", "Ok", 0));
        DefChartParms->setText(QApplication::translate("EditDefParms", "Def Chart Parms", 0));
        CancelButton->setText(QApplication::translate("EditDefParms", "Cancel", 0));
        TextLabel1->setText(QApplication::translate("EditDefParms", "ZoneInfo path", 0));
        TextLabel3->setText(QApplication::translate("EditDefParms", "Extra time", 0));
        PrintBW->setText(QApplication::translate("EditDefParms", "Print in Black and White", 0));
        UTC->setText(QApplication::translate("EditDefParms", "Coordinated Universal Time", 0));
        CustomDT->setText(QApplication::translate("EditDefParms", "Custom Date and Time", 0));
        CustomDT->setShortcut(QString());
        InvBack->setText(QApplication::translate("EditDefParms", "Inverse Background at Startup", 0));
        RightDW->setText(QApplication::translate("EditDefParms", "Right Dock Widget", 0));
        textLabel1->setText(QApplication::translate("EditDefParms", "Card Zoom Factor", 0));
        textLabel1_2->setText(QApplication::translate("EditDefParms", "Maximum number of lines per text block", 0));
        Astrologer->setText(QApplication::translate("EditDefParms", "name, \342\234\206phone, @mail, http://site", 0));
        label_2->setText(QApplication::translate("EditDefParms", "Astrologer", 0));
        BackFile->setText(QString());
        label_5->setText(QApplication::translate("EditDefParms", "Background Image", 0));
        groupBox->setTitle(QApplication::translate("EditDefParms", "SKYSITE", 0));
        label_3->setText(QApplication::translate("EditDefParms", "User name", 0));
        label_4->setText(QApplication::translate("EditDefParms", "Password", 0));
        label_8->setText(QApplication::translate("EditDefParms", "Temperature \302\272C", 0));
        label_9->setText(QApplication::translate("EditDefParms", "Pressure mb", 0));
        label_10->setText(QApplication::translate("EditDefParms", "Humidity %", 0));
        TabWidget2->setTabText(TabWidget2->indexOf(tab), QApplication::translate("EditDefParms", "General", 0));
        TabWidget2->setTabWhatsThis(TabWidget2->indexOf(tab), QApplication::translate("EditDefParms", "Image file for the chart background, if any", 0));
#ifndef QT_NO_TOOLTIP
        Width->setToolTip(QApplication::translate("EditDefParms", "Drawing width", 0));
#endif // QT_NO_TOOLTIP
        TextLabel4->setText(QApplication::translate("EditDefParms", "Width", 0));
        Antialias->setText(QApplication::translate("EditDefParms", "Antialias", 0));
#ifndef QT_NO_TOOLTIP
        Height->setToolTip(QApplication::translate("EditDefParms", "Drawing height", 0));
#endif // QT_NO_TOOLTIP
        TextLabel5->setText(QApplication::translate("EditDefParms", "Height", 0));
        label->setText(QApplication::translate("EditDefParms", "Inc/Decrement glyph size", 0));
        label_6->setText(QApplication::translate("EditDefParms", "Text font", 0));
        label_7->setText(QApplication::translate("EditDefParms", "Font Size", 0));
        LazyDog->setText(QApplication::translate("EditDefParms", "The Quick Brown Fox Jumps Over The Lazy Dog", 0));
        TabWidget2->setTabText(TabWidget2->indexOf(tab1), QApplication::translate("EditDefParms", "Graphic", 0));
        ColorsGroupBox1->setTitle(QApplication::translate("EditDefParms", "Colors", 0));
        FireColor->setText(QString());
        TextLabel6->setText(QApplication::translate("EditDefParms", "Fire color", 0));
        AsteroColor->setText(QString());
        TextLabel9_2->setText(QApplication::translate("EditDefParms", "Asteroids color", 0));
        AirColor->setText(QString());
        TextLabel7->setText(QApplication::translate("EditDefParms", "Air color", 0));
        ExtraColor->setText(QString());
        TextLabel9_2_2->setText(QApplication::translate("EditDefParms", "Extra objects color", 0));
        WaterColor->setText(QString());
        TextLabel8->setText(QApplication::translate("EditDefParms", "Water color", 0));
        OtherColor->setText(QString());
        TextLabel9_2_3->setText(QApplication::translate("EditDefParms", "Other objects color", 0));
        EarthColor->setText(QString());
        TextLabel9->setText(QApplication::translate("EditDefParms", "Earth color", 0));
        PaletteGroupBox1->setTitle(QApplication::translate("EditDefParms", "Palette", 0));
        Col0->setText(QString());
        Col1->setText(QString());
        Col2->setText(QString());
        Col3->setText(QString());
        Col4->setText(QString());
        Col5->setText(QString());
        Col6->setText(QString());
        Col7->setText(QString());
        Col8->setText(QString());
        Col9->setText(QString());
        Col10->setText(QString());
        Col11->setText(QString());
        Col12->setText(QString());
        Col13->setText(QString());
        Col14->setText(QString());
        Col15->setText(QString());
        TabWidget2->setTabText(TabWidget2->indexOf(tab2), QApplication::translate("EditDefParms", "Colors", 0));
    } // retranslateUi

};

namespace Ui {
    class EditDefParms: public Ui_EditDefParms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDEFPARMS_H
