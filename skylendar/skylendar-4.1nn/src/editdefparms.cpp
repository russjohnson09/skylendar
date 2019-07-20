#include "editdefparms.h"
#include "astrohm.h"
#include "astrostring.h"
#include "astroutils.h"
#include "astrographics.h"
#include "editchartparms.h"
#include "astrospinbox.h"
#include "astrochoosecol.h"
#include <QCursor>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <QFileDialog>
#include <QColorDialog>

/*
 *  Constructs a EditDefParms which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
EditDefParms::EditDefParms(AstroParams* ap)
{
    AstroString as;
    QFont f;
    setupUi(this);
    Ac = new AstroColor[16];
    Qag = new QActionGroup(this);
		Qag->setExclusive(true);
    Ap =ap;
    ApBase = *Ap;
    Chosen = -1;
    //Qppm.setCheckable(true);
    //Background->setText("");
    AstroHM hm = ApBase.ExtraTime;
    emit ZoneInfoPath->setText(ApBase.ZPath);
    emit ZoomFactor->setValue(ApBase.CardZoomFactor);
    emit NbLines->setValue(ApBase.NbLines);
    f.fromString(ApBase.TextFont);
		TextFont->setCurrentFont(f);
		LazyDog->setFont(f);
		emit FontSize->setValue(f.pointSize());
    emit Astrologer->setText(ApBase.Astrologer);
    emit IncDecGlyph->setValue(ApBase.IncDecGlyph);
    emit UTC->setChecked(ApBase.UTC);
    emit InvBack->setChecked(ApBase.StartInvBack);
    emit RightDW->setChecked(ApBase.RightDW);
    emit UserName->setText(ApBase.SkyUser);
    emit Password->setText(ApBase.SkyPass);
    emit Background->addItem(ApBase.Background);
    TextFont->setFont(f);
    hm.Get(as);
    for (int i = 0; i < 16; i++)
			Ac[i] = COL[i];
    Col0->setIcon(COL % 0);
    Col1->setIcon(COL % 1);
    Col2->setIcon(COL % 2);
    Col3->setIcon(COL % 3);
    Col4->setIcon(COL % 4);
    Col5->setIcon(COL % 5);
    Col6->setIcon(COL % 6);
    Col7->setIcon(COL % 7);
    Col8->setIcon(COL % 8);
    Col9->setIcon(COL % 9);
    Col10->setIcon(COL % 10);
    Col11->setIcon(COL % 11);
    Col12->setIcon(COL % 12);
    Col13->setIcon(COL % 13);
    Col14->setIcon(COL % 14);
    Col15->setIcon(COL % 15);
    emit ExtraTime->setText(as);
    emit PrintBW->setChecked(ApBase.IfBW);
    emit CustomDT->setChecked(ApBase.CustomDT);
    emit Width->setValue(ApBase.Width);
    emit Height->setValue(ApBase.Height);
    emit Antialias->setChecked(ApBase.Antialias);
    emit FireColor->setIcon(COL % ApBase.FireColor);
    emit AirColor->setIcon(COL % ApBase.AirColor);
    emit WaterColor->setIcon(COL % ApBase.WaterColor);
    emit EarthColor->setIcon(COL % ApBase.EarthColor);
    emit AsteroColor->setIcon(COL % ApBase.AsteroColor);
    emit ExtraColor->setIcon(COL % ApBase.ExtraColor);
    emit OtherColor->setIcon(COL % ApBase.OtherColor);
    QAction* qa;
    for (int i = 0; i < 16; i++)
    {
        qa = Qppm.addAction(COL % i, "");
        qa->setData(i);
				qa->setCheckable(true);
				qa->setActionGroup(Qag);
    }
    connect(Qag, SIGNAL(triggered(QAction*)), this, SLOT(Activated(QAction*)));
		emit Temp->setValue(ApBase.Temperature);
		emit Press->setValue(ApBase.Pressure);
		emit Humid->setValue(ApBase.Humidity);
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditDefParms::~EditDefParms()
{
    //QColor::destroyAllocContext(Context);
    delete Ac;
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void EditDefParms::on_AirColor_clicked()
{
    ChooseColor(ApBase.AirColor);
    ChangeButton(AirColor, Ac[ApBase.AirColor]);
}
/*
 * public slot
 */
void EditDefParms::on_AsteroColor_clicked()
{
    ChooseColor(ApBase.AsteroColor);
    ChangeButton(AsteroColor, Ac[ApBase.AsteroColor]);
}
/*
 * public slot
 */
void EditDefParms::on_EarthColor_clicked()
{
    ChooseColor(ApBase.EarthColor);
    ChangeButton(EarthColor, Ac[ApBase.EarthColor]);
}
/*
 * public slot
 */
void EditDefParms::on_ExtraColor_clicked()
{
    ChooseColor(ApBase.ExtraColor);
    ChangeButton(ExtraColor, Ac[ApBase.ExtraColor]);
}
/*
 * public slot
 */
void EditDefParms::on_FireColor_clicked()
{
    ChooseColor(ApBase.FireColor);
    ChangeButton(FireColor, Ac[ApBase.FireColor]);
}

void EditDefParms::on_BackFile_clicked()
{
	const QString f = QFileDialog::getOpenFileName(0, i18n("Get a background file"), QString(), i18n("Images Files (*.jpg *.png)"));
	if(!f.isEmpty())
		Background->insertItem(Background->count(), f);
}

/*
 * public slot
 */
void EditDefParms::on_OkButton_clicked()
{
    AstroHM hm = (AstroString)ExtraTime->text();
    strncpy(ApBase.ZPath, ZoneInfoPath->text().toUtf8().data(), BUFSIZE);
    ApBase.ExtraTime = hm.Get();
    ApBase.Width = Width->value();
    ApBase.Height = Height->value();
    ApBase.Antialias = Antialias->isChecked();
		QFont f = TextFont->currentFont();
		f.setPointSize(FontSize->value());
    ApBase.TextFont = f.toString();
    ApBase.IfBW     = PrintBW->isChecked();
    ApBase.CustomDT = CustomDT->isChecked();
    ApBase.CardZoomFactor = ZoomFactor->value();
    ApBase.NbLines = NbLines->value();
    ApBase.Astrologer = Astrologer->text();
    ApBase.IncDecGlyph = IncDecGlyph->value();
    ApBase.UTC = UTC->isChecked();
    ApBase.StartInvBack  = InvBack->isChecked();
    ApBase.RightDW  = RightDW->isChecked();
    ApBase.SkyUser = UserName->text();
    ApBase.SkyPass = Password->text();
    ApBase.Background = Background->currentText();
    for (int i = 0; i < 16; i++)
        Acl->SetColor(Ac[i], i);
		ApBase.Temperature = Temp->value();
		ApBase.Pressure = Press->value();
		ApBase.Humidity = Humid->value();
    *Ap = ApBase;
    emit accept();
}
/*
 * public slot
 */
void EditDefParms::on_OtherColor_clicked()
{
    ChooseColor(ApBase.OtherColor);
    ChangeButton(OtherColor, Ac[ApBase.OtherColor]);
}
/*
 * public slot
 */
void EditDefParms::on_WaterColor_clicked()
{
    ChooseColor(ApBase.WaterColor);
    ChangeButton(WaterColor, Ac[ApBase.WaterColor]);
}
/*
 * public slot
 */
void EditDefParms::on_CancelButton_clicked()
{
    emit reject();
}

void EditDefParms::ChooseColor(int& ptr)
{
	auto qa = Qag->actions()[ptr];
	if(qa)
		qa->setChecked(true);
	Qppm.exec(QCursor::pos());
	if(Chosen != -1)
		ptr = Chosen;
}

void EditDefParms::Activated(QAction* qa)
{
    Chosen = qa->data().toInt();
}

void EditDefParms::on_DefChartParms_clicked()
{
    EditChartParms ecp(&ApBase);
    ecp.exec();
}

void ChangeButton(QPushButton* pb, const QColor& c)
{
    QIcon qi = pb->icon();
    if (!qi.isNull())
    {
        QPixmap qx = qi.pixmap(pb->iconSize());
        emit qx.fill(c);
        emit pb->setIcon(qx);
    }
}

void EditDefParms::ChangeColor(const QColor& c, int i)
{
	AstroColor ac(c.red(), c.green(), c.blue());
	auto qa = Qag->actions()[i];
    Ac[i] = ac;
    if (qa && !qa->icon().isNull())
    {
			QPixmap qx = qa->icon().pixmap(80, 60);
			//qa->setChecked(true);
        qx.fill(c);
        qa->setIcon(qx);
    }
    if (ApBase.FireColor == i) ChangeButton(FireColor, c);
    if (ApBase.AirColor == i) ChangeButton(AirColor, c);
    if (ApBase.WaterColor == i) ChangeButton(WaterColor, c);
    if (ApBase.EarthColor == i) ChangeButton(EarthColor, c);
    if (ApBase.AsteroColor == i) ChangeButton(AsteroColor, c);
    if (ApBase.ExtraColor == i) ChangeButton(ExtraColor, c);
    if (ApBase.OtherColor == i) ChangeButton(OtherColor, c);
}

void EditDefParms::on_Col0_ChangeColor(const QColor& c)
{
    ChangeColor(c, 0);
}

void EditDefParms::on_Col10_ChangeColor(const QColor& c)
{
    ChangeColor(c, 10);
}

void EditDefParms::on_Col11_ChangeColor(const QColor& c)
{
    ChangeColor(c, 11);
}

void EditDefParms::on_Col12_ChangeColor(const QColor& c)
{
    ChangeColor(c, 12);
}

void EditDefParms::on_Col13_ChangeColor(const QColor& c)
{
    ChangeColor(c, 13);
}

void EditDefParms::on_Col14_ChangeColor(const QColor& c)
{
    ChangeColor(c, 14);
}

void EditDefParms::on_Col15_ChangeColor(const QColor& c)
{
    ChangeColor(c, 15);
}

void EditDefParms::on_Col1_ChangeColor(const QColor& c)
{
    ChangeColor(c, 1);
}

void EditDefParms::on_Col2_ChangeColor(const QColor& c)
{
    ChangeColor(c, 2);
}

void EditDefParms::on_Col3_ChangeColor(const QColor& c)
{
    ChangeColor(c, 3);
}

void EditDefParms::on_Col4_ChangeColor(const QColor& c)
{
    ChangeColor(c, 4);
}

void EditDefParms::on_Col5_ChangeColor(const QColor& c)
{
    ChangeColor(c, 5);
}

void EditDefParms::on_Col6_ChangeColor(const QColor& c)
{
    ChangeColor(c, 6);
}

void EditDefParms::on_Col7_ChangeColor(const QColor& c)
{
    ChangeColor(c, 7);
}

void EditDefParms::on_Col8_ChangeColor(const QColor& c)
{
    ChangeColor(c, 8);
}

void EditDefParms::on_Col9_ChangeColor(const QColor& c)
{
    ChangeColor(c, 9);
}

AstroChooseCol::AstroChooseCol(QWidget* parent) : QPushButton(parent)
{
	connect(this, SIGNAL(clicked()), SLOT(Clicked()));
}

void AstroChooseCol::Clicked()
{
	QColorDialog d(Col, nullptr);
	if(d.exec() == QDialog::Accepted && Col != d.selectedColor())
	{
		Col = d.selectedColor();
		ChangeButton(this, Col);
		emit ChangeColor(Col);
	}
}

void EditDefParms::on_TextFont_currentFontChanged(const QFont& f)
{
	LazyDog->setFont(f);
}

void EditDefParms::on_FontSize_valueChanged(int i)
{
	QFont f = LazyDog->font();
	f.setPointSize(i);
	LazyDog->setFont(f);
}

