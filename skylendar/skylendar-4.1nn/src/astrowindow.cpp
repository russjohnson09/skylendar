/***************************************************************************
                          astrowindow.cpp  -  description
                             -------------------
    begin                : Sat Dec 30 2000
    copyright            : (C) 2000 by Christophe Gros
    email                : skylendar@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "astrosql.h"
#include "astrowindow.h"
#include "stdwheelchart.h"
#include "astroresources.h"
#include "astroprocess.h"
#include "astrointerface.h"
#include "astromainwindow.h"
#include "astrorestrictions.h"
#include "aspscanlist.h"
#include "astrograph.h"
#include "editaddmul.h"
#include "astrotarotspreads.h"
#include "astrodirections.h"

#ifdef QT
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QKeyEvent>
#include <QDropEvent>
#include <QPicture>
#include <QScrollBar>
#include <QPixmap>
#include <QTimer>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QScrollArea>
#include <QMdiSubWindow>
#include <QDrag>
#include <QtSvg/QSvgGenerator>
#endif

#ifndef TWOPI
# define TWOPI (2.0 * PI)
#endif

// The first Id of subring popup
#define SUBRID 20
#define AA(i) qa = SubringPm->addAction(*Asr->SubringsNames[i]); qa->setCheckable(true); qa->setData(SUBRID + i); Qag->addAction(qa)
#define AA1(qm, text, id) qa =  qm->addAction(text); qa->setData(id)
#define TR(qtr, parent, text) qtr = new QTreeWidgetItem(parent); qtr->setText(0, text)//; qtr->setForeground(0, QBrush(Qt::black));

class MyScrollArea: public QScrollArea
{
public:
    MyScrollArea(AstroWindow* asw, QWidget* parent = 0): QScrollArea(parent) {
        Asw = asw;
    }

private:
    void resizeEvent(QResizeEvent* qre);
    AstroWindow* Asw;

};

extern AstroMainWindow* Amw;



void AstroWindow::Setup(const AstroMainWindow* amw)
{
    int vsbw = 18, hsbh = 35;
    Width = GetWidth();
    Height = GetHeight();
    Amw->Ring = 1;
#ifdef QT
    QAction* qa;
    setAcceptDrops(true);
    AstroString as;
    setBackgroundRole(QPalette::Window);
    setAutoFillBackground(Asr->Background == "");
    QPict = new QPicture;
    Qsa = new MyScrollArea(this, Amw);
    Qsa->setWidget(this);
    Qsw = amw->QMa->addSubWindow(Qsa);
    Qsw->setAttribute(Qt::WA_DeleteOnClose);
    setFocusPolicy(Qt::StrongFocus);
    WinRatio = float(OrigWidth) / float(Qsw->size().width());
    Cbp->Qw = this;
    ParamPm = new QMenu(this);
    SubringPm = new QMenu(this);
    if (Asr->StartInvBack)
    {
        emit Amw->invbackground->setChecked(true);
        Cpr->InvBack = true;
    }
    auto corner = new QWidget(Qsa);
    Qsa->setCornerWidget(corner);
    const QPalette qp = CSC(QPalette&, palette());
    const QColor sb = qp.color(QPalette::Active, QPalette::Window);
    corner->setStyleSheet(QString("QWidget { background-color: rgb(%1,%2,%3) }").arg(sb.red()).arg(sb.green()).arg(sb.blue()));
    Qag = new QActionGroup(this);
    Qag1 = new QActionGroup(this);
    Qag1->setExclusive(false);
    AA(0);
    AA(1);
    AA(2);
    AA(3);
    AA(4);
    AA(5);
    connect(this, SIGNAL(Close(AstroWindow *)), amw, SLOT(Close(AstroWindow *)));
    connect(ParamPm, SIGNAL(triggered(QAction*)), this, SLOT(Activated(QAction*)));
    connect(SubringPm, SIGNAL(triggered(QAction*)), this, SLOT(Activated(QAction*)));
    connect(this, SIGNAL(DupnDrop(enum ButtonType, int)), amw, SLOT(DupnDrop(enum ButtonType, int)));
    Repaint();
    emit Qsw->setWindowTitle(GetTitle(as));
    int w = GetWidth(), h = GetHeight();
    emit resize(w, h);
    if (w + vsbw + 4 > amw->QMa->width()) w = amw->QMa->width() -  2 * vsbw;
    if (h + hsbh + 4 > amw->QMa->height()) h = amw->QMa->height() - 2 * hsbh;
    SetPm(GetCt());
    emit Qsw->resize(w + vsbw, h + hsbh);
    BackgroundColor();
    Qsw->show();
		setFocus(Qt::ActiveWindowFocusReason);
#endif
}

AstroWindow::AstroWindow(const AstroMainWindow* amw, AstroData* ad1, enum ChartType ect, AstroData* ad2, AstroData* ad3, AstroData* ad4): AstroGraphicChart(Asr->Width, Asr->Height)
{
	  SetCt(ect);
		SetData(ad1, 0);
		SetRestrict(Arl->GetDefault(), 0);
    if (ad2)
    {
        SetData(ad2, 1);
        SetRestrict(Arl->GetDefault(), 1);
    }
    if (ad3)
    {
        SetData(ad3, 2);
        SetRestrict(Arl->GetDefault(), 2);
    }
    if (ad4)
    {
        SetData(ad4, 3);
        SetRestrict(Arl->GetDefault(), 3);
    }
    Setup(amw);
}


AstroWindow::AstroWindow(const AstroMainWindow* amw, const AstroChart& ac, enum ChartType ect): AstroGraphicChart(Asr->Width, Asr->Height)
{
    AstroString as;
    SetCt(ect);
    for (int i = 0; i < NBDATA; i++)
        if (ac[i])
        {
            SetData(ac[i], i);
            SetRestrict(~(*ac[i]), i);
        }
    Display(false);
    if (ac.Acb->IfOwnTitle) Acb->SetOwnTitle(ac.GetTitle(as));
    Cbp->SetFlags(ac.Cbp->GetFlags());
    Cbp->Subring = ac.Cbp->Subring;
    for (int i = 0; i < NBDATA; i++)
        if (ac[i])
            (*this)[i]->SetSubChart(ac[i]->GetSubType());
    Setup(amw);
}

AstroWindow::AstroWindow(const AstroMainWindow* amw, Index idx): AstroGraphicChart(Asr->Width, Asr->Height)
{
    SetCt(NullChart);
    Display(false);
    if(!Ahl->Load(idx, *this))
		{
			ParamPm = nullptr;
			SubringPm = nullptr;
			AstroMessage(i18n("Can't load this chart"));
			return;
		}
    Setup(amw);
}

AstroWindow::~AstroWindow()
{
    Amw->RemWindow(this);
    Amw->Remove(this);
    delete ParamPm;
    delete SubringPm;
}

void AstroWindow::paintEvent(QPaintEvent* event)
{
    QPainter qp(this);
    qp.drawPicture(0, 0, *QPict);
    qp.end();
}

void AstroWindow::SetPm(enum ChartType cti)
{
#ifdef QT
    QAction* qa;
    ParamPm->clear();
    struct AstroPopupMenu* apm = Acb->GetPm(0);
    //ParamPm->clear();
    delete Qag1;
    Qag1 = new QActionGroup(this);
    Qag1->setExclusive(false);
    for (int i = 0; apm; apm = Acb->GetPm(++i))
    {
        qa = ParamPm->addAction(*apm->Name);
        qa->setCheckable(true);
        qa->setChecked(*apm->B);
        qa->setData(i + 1);
        qa->setActionGroup(Qag1);
        //Qag1->addAction(qa);
    }
    if (cti == StdWheels)
    {
        const QList<QAction*> qa = SubringPm->actions();
        for (QList<QAction *>::const_iterator i = qa.constBegin(); i != qa.constEnd(); ++i)
            if ((*i)->data().toInt() == Cbp->Subring + SUBRID)
            {
                (*i)->setChecked(true);
                break;
            }
        SubringPm->setTitle(i18n("Subring"));
        ParamPm->addMenu(SubringPm);
    }
#endif
}

void AstroWindow::closeEvent(QCloseEvent* e)
{
    if (IsLocked())
    {
        qApp->beep();
        return;
    }
    emit Close(this);
    QWidget::closeEvent(e);
}

#ifdef QT

void  MyScrollArea::resizeEvent(QResizeEvent* qre)
{
    if (!Asw->Cbp->DynamicResize)
        Asw->WinRatio = float(Asw->OrigWidth) / float(size().width());
    QScrollArea::resizeEvent(qre);
}

void AstroWindow::resizeEvent(QResizeEvent*)
{
    if (Cbp->DynamicResize && !NoResize)
    {
        int nw = int(Qsa->size().width() * WinRatio), nh = int(float(nw) * float(OrigHeight) / float(OrigWidth));
        Resize(nw, nh);
        OrigWidth = nw;
        OrigHeight = nh;
        NoResize = true;
        Repaint(false);
        NoResize = false;
    }
}

void AstroWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        AstroString as("^");
        as += PACKAGE;
        Art = as;
        if (Art < event->mimeData()->text())
        {
            event->acceptProposedAction();
            return;
        }
    }
    event->setDropAction(Qt::IgnoreAction);
}

void AstroWindow::dropEvent(QDropEvent* event)
{
    AstroString text, as("^"), as1;
    ButtonType bt = Undefined_Button;
    as += PACKAGE;
    P;
    if (IsLocked())
    {
        qApp->beep();
        return;
    }
    text = event->mimeData()->text();
    if (text.isNull()) return;
    int i;
    Art = (as + " (.*):");
    if (Art < text)
    {
        as = Art / 1;
        if (as == "Data")    {
            bt = DataButton;
            goto end;
        }
        if (as == "Restrict") {
            bt = RestrictButton;
            goto end;
        }
        if (as == "Type")    {
            bt = TypeButton;
            goto end;
        }
        if (as == "Subtype") {
            bt = SubTypeButton;
            goto end;
        }
        if (as == "Major")   {
            bt = MajorButton;
            goto end;
        }
        if (as == "Sword")   {
            bt = SwordButton;
            goto end;
        }
        if (as == "Coin")    {
            bt = CoinButton;
            goto end;
        }
        if (as == "Stick")   {
            bt = StickButton;
            goto end;
        }
        if (as == "Cup")     bt = CupButton;
end:
        if (bt != Undefined_Button)
        {
            text = text.right(text.length() - text.indexOf(':') - 1);
            i = text.toUInt();
            if (Asr->Shift)
            {
                emit DupnDrop(bt, i);
                return;
            }
            DropAction(bt, i, event->pos().x(), event->pos().y());
            event->acceptProposedAction();
        }
    }
}

void AstroWindow::DropAction(enum ButtonType bt, int i, int x, int y)
{
    AstroString as;
    switch (bt)
    {
    case DataButton:
        SetData(Adl->Get(i), GetRing());
        emit Qsw->setWindowTitle(GetTitle(as));
        break;
    case RestrictButton:
        SetRestrict(Arl->Get(i), GetRing());
        break;
    case TypeButton:
        ManageTypes(i);
        emit Qsw->setWindowTitle(GetTitle(as));
        break;
    case SubTypeButton:
        ManageSubTypes(i);
        emit Qsw->setWindowTitle(GetTitle(as));
        break;
    case MajorButton:
        ManageTarots(Major, i, x, y);
        break;
    case SwordButton:
        ManageTarots(Swords, i, x, y);
        break;
    case CoinButton:
        ManageTarots(Coins, i, x, y);
        break;
    case StickButton:
        ManageTarots(Sticks, i, x, y);
        break;
    case CupButton:
        ManageTarots(Cups, i, x, y);
        break;
    default:
        ;
    }
    Repaint(true);
    if (bt == TypeButton)
    {
        if (!Asr->Shift)
        {
            Amw->ChangeWindow(this, GetCurTitle());
            setFocus();
        }
        SetPm((enum ChartType)i);
				auto Glb = DC(GraphicListBase*, Acb);
				Amw->prevblock->setEnabled(Glb);
				Amw->nextblock->setEnabled(Glb);
    }
}

#endif

AstroIconsWindow& AstroWindow::Aiw() const
{
    return *Amw->Aiw;
}

void AstroWindow::ManageTypes(int i)
{
    auto cti = (enum ChartType)i;
    auto plb = DC(ParamListBase*, Acb);
		Acb->Clean();
    //bool b = (cti == AspScList || cti == Ephemeris || cti == Directions);
    if (cti < StdWheels || cti >= Unknown_ChartType)
        return;
    if ((cti == AspScList || cti == Directions || cti == Batch) && Acb->Count() < 2)
    {
        AstroMessage(i18n("Sorry, this chart needs 2 visible rings."), false);
        return;
    }
    // if (plb && b)
    // {
    //     UnlockChart();
    //     plb->EditParams();
    //     if (!LockChart()) return;
    // }
    SetCt(cti);
}

void AstroWindow::ManageSubTypes(int i)
{
    AstroString as;
    int r = GetRing();
    AstroObjs* ao = (*this)[r];
    bool createnew;
    Index idx, oldidx;
    switch (i)
    {
    case Show_Hide:
        if (!SetSubType(Show_Hide, r))
            AstroMessage(i18n("Sorry, Can't hide this ring !"), false);
        break;
    case ExtrnSave:
        if (Asr->Ctrl)
        {
            if (!ao)
            {
                AstroMessage(i18n("Can't extract this ring !"));
                return;
            }
            auto ad = new AstroData(*ao);
            ad->Idx = 1;
            if (ad->Name.Left(1) == "~")
                ad->Name = ad->Name.Right(ad->Name.Len() - 1) + "(" + ++ao->ExtractID + ")";
            else
                ad->Name = ad->Name + "(" + ++ao->ExtractID + ")";
            ad->ChartType = 0;
            Aiw().AddData(ad);
            return;
        }
        if (!(idx = ExtractandSave(r, oldidx, createnew, Acb->GetAspectsList())))
            AstroMessage(i18n("Can't extract this ring !"), false);
        else
        {
            if (oldidx >= BOUND && !createnew)
            {
                Adl->Get(oldidx)->Idx = idx;
                Aiw().UpdateDataIdx(oldidx, idx);
            }
            if (createnew)
                (void)new AstroIconsWindow::AstroIconButton(&Aiw(), Adl->Get(idx));
        }
        break;
    case Single:
    case Transit:
    case Direction:
    case Progression:
    case Composite:
    case TimeSpace:
    case SolarArc:
    case Profection:
			if (i == Direction && Acb->Second && (!(*Acb->First)().Equatorial || !(*Acb->Second)().Equatorial)) AstroMessage(i18n("Both first and second ring should be equatorial."), false);
        if (!SetSubType((enum ChartSubType)i, r))
            AstroMessage(Sprintf(i18n("Sorry, Can't set this subtype ring to %a"), &as, Asr->SubTypesNames[i]));
        break;
    case AddAngle:
    case MulAngle:
        if (!ao)
        {
            AstroMessage(Sprintf(i18n("Sorry, Can't set this subtype ring to %a"), &as, Asr->SubTypesNames[i]));
            return;
        }
        {
            EditAddMul ead(ao->Angle);
            if (ead.exec() == QDialog::Accepted)
                ao->Angle = ead.Val;
        }
        if (!SetSubType((enum ChartSubType)i, r))
        {
            AstroMessage(Sprintf(i18n("Sorry, Can't set this subtype ring to %a"), &as, Asr->SubTypesNames[i]));
            return;
        }
        break;
    case AFirst:
        SetAFirst(ao->GetRing());
        break;
    case ASecond:
        SetASecond(ao->GetRing());
        break;
    default:
        ;
    }
}

void AstroWindow::ManageTarots(enum TarotTypes tt, int i, int x, int y)
{
    if (GetCt() != Tarots_Spreads)
    {
        AstroMessage(i18n("Sorry, only for the Tarot Spreads"), false);
        return;
    }
    auto ats = DC(AstroTarotSpreads*, Acb);
    if (ats)
    {
        auto ac = ats->GetCard(x + QWidget::x() + Qsa->horizontalScrollBar()->value(), y + QWidget::y() + Qsa->verticalScrollBar()->value());
        if (!ac)
        {
            qApp->beep();
            return;
        }
        ac->Put(tt, i + 1, Asr->Ctrl);
    }
}

int AstroWindow::GetRing() const
{
    return Amw->Ring -1;
}

AstroGraphicChart::AstroGraphicChart(int width, int height): AstroGraphics(0, 0, 0, width, height), AstroChart()
{
    Cbp->Ag = Base = this;
    Cpr = Cbp;
    SetCt(StdWheels);
    Dm = GraphicMode;
    Qprint = nullptr;
    Width  = OrigWidth = width;
    Height = OrigHeight = height;
    PosX = PosY = 0;
    Size = Width / 50;
    Qp = new QPainter;
    Pen = new QPen;
    astro = Asr->Astro;
    text = new QFont(TEXTFONT);
    if (!Asr->TextFont.isEmpty()) text->fromString(Asr->TextFont);
}

bool AstroGraphicChart::SaveSVG(const AstroString &file)
{
    enum DisplayMode dm = Dm;
#ifdef QT
	QSvgGenerator gen;
    SetDisplayMode(SVGMode);
	gen.setFileName(file);
	gen.setSize(QSize(GetWidth(), GetHeight()));
	gen.setViewBox(QRect(0, 0, GetWidth(), GetHeight()));
	AstroString as;
	gen.setTitle(GetTitle(as));
	gen.setDescription("Astrological chart made with skylendar 4");
	QPainter p;
    Repaint(false);
	p.begin(&gen);
	bool b = QPict->play(&p);
	p.end();
    SetDisplayMode(dm);
    Repaint();
	return b;
#endif
}

AstroGraphicChart::~ AstroGraphicChart()
{
    delete text;
    delete Pen;
    delete Qp;
}

AstroPrintPage::AstroPrintPage(AstroString& title, AstroChartBase* acb, AstroGraphicChart* agc, int height)
{
    Acb = acb;
    Agc = agc;
    Page = 1;
    Height = height;
    Title = title;
#ifdef QT
    connect(acb, SIGNAL(NewPage()), this, SLOT(NewPage()));
#endif
}

AstroPrintPage::~AstroPrintPage()
{
#ifdef QT
    disconnect(Acb, SIGNAL(NewPage()), this, SLOT(NewPage()));
#endif
}

void AstroPrintPage::NewPage()
{

    Footer(Acb->IfPage);
    Agc->Qprint->newPage();
    Page++;
    Header();
}

void AstroPrintPage::Header()
{
    extern AstroData* Now;
    int w = Agc->GetWidth(), h;
    //w -= w / 3;
    enum AstroGraphics::SizeChars sc = Agc->GetSc();
    Agc->FontSize(AstroGraphics::Tiny);
    Agc->TextMetrics("O", 0, &h);
		h /=2;
    AstroString as, l = PACKAGE;
    l += " ";
    l += VERSION;
    Agc->Move(0, h);
    Agc->JustifText(Now->GetDate(as), AstroGraphics::Left, w);
    Agc->Move(0, h);
    Agc->JustifText(Title, AstroGraphics::Center, w);
    Agc->Move(0, h);
    Agc->JustifText(l, AstroGraphics::Right, w);
    Agc->FontSize(sc);
    /*GraphicListBase* glb = SC(GraphicListBase*, Agc->Acb);
    	if(glb) { glb->NewLine(); glb->NewLine(); glb->NewLine(); }*/
}

void AstroPrintPage::Footer(bool ifpage)
{
    int w = Agc->GetWidth(), h;
    //w -= w / 3;
    enum AstroGraphics::SizeChars sc = Agc->GetSc();
    Agc->FontSize(AstroGraphics::Tiny);
    Agc->TextMetrics("O", 0, &h);
    AstroString r;
    Sprintf(i18n("Page %d"), &r, Page);
    Agc->Move(0, Agc->GetHeight() - h);
    if (ifpage) Agc->JustifText(Page % 2 ? "" : r, AstroGraphics::Left, w);
    Agc->Move(0, Agc->GetHeight() - h);
    Agc->JustifText(Asr->Astrologer, AstroGraphics::Center, w);
    Agc->Move(0, Agc->GetHeight() - h);
    if (ifpage) Agc->JustifText(Page % 2 ? r : "", AstroGraphics::Right, w);
    Agc->FontSize(sc);
}

void AstroGraphicChart::SetDisplayMode(enum DisplayMode dm)
{
    Dm = dm;
    GraphicListBase *glb;
    switch (Dm)
    {
    case GraphicMode:
    case DblBufMode:
    case SVGMode:
        if (Qprint)
        {
            delete Qprint;
            Qprint = nullptr;
        }
        Acb->IfPage = false;
        Acb->NoSpot = (Dm == SVGMode);
        break;
#ifdef QT
    case PrintMode:
    {
        Qprint = new QPrinter;
        Qprint->setCreator(QString(PACKAGE) + " " + VERSION);
        auto printDialog = new QPrintDialog(Qprint);
        if (printDialog->exec() != QDialog::Accepted)
        {
            Dm = GraphicMode;
            delete Qprint;
            Qprint = nullptr;
        }
    }
    case PreviewMode:
#endif
        if ((glb = DC(GraphicListBase*, Acb))) Acb->IfPage = true;
        Acb->NoSpot = true;
    };
}

void AstroGraphicChart::BackgroundColor()
{
#ifdef QT
	//const QPalette qp = CSC(QPalette&, palette());
//     qp.setColor(QPalette::Active, QPalette::Window, Cpr->InvBack ? *Acl->Fore : *Acl->Back);
//     qp.setColor(QPalette::Inactive, QPalette::Window, Cpr->InvBack ? *Acl->Fore : *Acl->Back);
// 		setPalette(qp);
// Problem with qt 4.7.1 setPalette worked before. Had to declare Qsa in AstroGraphicChart
    const AstroColor& b = Cpr->InvBack ? *Acl->Fore : *Acl->Back;
		parentWidget()->setStyleSheet(QString("* { background-image: url(%1); background-color: rgb(%2,%3,%4)}").arg(Cpr->BackImage ? Asr->Background : "").arg(b.red()).arg(b.green()).arg(b.blue()));
#endif
}

void AstroGraphicChart::PreRedraw(bool b)
{
    int w, h, mx, my, ph;
    AstroString as;
    const AstroChart& ao = *this;
#ifdef QT
    switch (Dm)
    {
    case GraphicMode:
    case DblBufMode:
    case SVGMode:
        delete QPict;
        QPict = new QPicture;
        Qp->begin(QPict);
        break;
    case PrintMode:
        Qp->begin(Qprint);
    case PreviewMode:
        Asr->IfPrint = true;
        GetTitle(as);
        PrinterSize(w, h, mx, my, ph);
        App = new AstroPrintPage(as, Acb, this, (Qp->viewport().width() * PRINTZOOMFACT * h) / w);
        if (Acb->IfPage)
        {
            Resize(w, h);
        }
        else
        {
            int w1 = GetWidth(), h1 = GetHeight(), w2 = w1 *  PRINTZOOMFACT, h2 = h1 * PRINTZOOMFACT, w4, h4;
            W = Qp->viewport().width(), H = Qp->viewport().height();
            Resize(w2, h2);
            auto pn = CSC(QPen&, Qp->pen());
            pn.setWidth(BOLDLINE);
            auto x = float(OrigWidth) / w1;
            w4 = float(W) * x;
            w4 -= w4 / 10;
            h4 = h1 * w4 / w1;
            if(h4 > H) { h4 = H; w4 = H * w1 / h1; }
            int t = (W - w1) / 2;
            t = (t > 0) ? t : 0;
            Qp->setViewport(t, 0, w4, h4);
            if (Cbp->DynamicResize)
            {
                int ww = Asr->Width * w / OrigWidth, hh = Asr->Height * h / OrigHeight;
                Qp->setWindow(0, 0, ww * PRINTZOOMFACT, hh * PRINTZOOMFACT);
            }
            else
                Qp->setWindow(0, 0, w2, h2);
            Qp->translate(0, my * PRINTZOOMFACT);
        }
        break;
    }
    if (Asr->Antialias)
    {
        Qp->setRenderHints(QPainter::Antialiasing);
        Qp->setRenderHints(QPainter::TextAntialiasing);
    }
    Qp->setRenderHints(QPainter::SmoothPixmapTransform);
#endif
}

void AstroGraphicChart::PostRedraw()
{
    switch (Dm)
    {
    case GraphicMode:
    case DblBufMode:
    case SVGMode:
        Qp->end();
        P;
        break;
    case PrintMode:
    case PreviewMode:
        App->Footer(Acb->IfPage);
        if (!Acb->IfPage)
        {
            Qp->translate(0.0, 0);
            FontSize(AstroGraphics::Tiny);
            Fore();
            App->Header();
        }
        Qp->setViewport(0, 0, W, H);
        Qp->setWindow(0, 0, W, H);
        Qp->end();
        P;
        Resize(OrigWidth, OrigHeight);
        delete App;
        Asr->IfPrint = false;
        break;
    }
    Acb->NoSpot = false;
}

void AstroGraphicChart::Repaint(bool b)
{
	AstroChart::Repaint(b);
	Display();
	update();
}

void AstroGraphicChart::PrinterSize(int&w, int &h, int& mx, int& my, int& ph)
{
#ifdef QT
	const QPrinter* p = SC(QPrinter*, Qp->device());
	const QPageLayout & l = p->pageLayout();
	const QMargins& m = l.marginsPoints();
	w = l.paintRect().width();
	h = l.paintRect().height();
	mx = m.left();
	my = m.top();
    ph = l.fullRectPixels(p->resolution()).bottom();
#endif
}

void AstroGraphicChart::ResizeView(int w, int h)
{
#ifdef QT
    int r;
		w -= w / 6;
		const QPrinter* p = SC(QPrinter*, Qp->device());
    if (p->orientation() == QPrinter::Landscape)
    {
			r = Qprint->height();
			Qp->setViewport(0, 0, int(double(r) * double(w) / double(h)), r);
			return;
    }
    r = p->width();
    Qp->setViewport(0, 0, r, int(double(r) * double(h) / double(w)));
#endif
}

void AstroWindow::Repaint(bool b)
{
#ifdef QT
    AstroString as;
    QRect target, source;
    switch (Dm)
    {
    case GraphicMode:
    case DblBufMode:
    case SVGMode:
        SetWidth(Asr->Width);
        SetHeight(Asr->Height);
        AstroGraphicChart::Repaint(b);
        resize(GetWidth(), GetHeight());
        UnlockChart();
        break;
    case PrintMode:
    case PreviewMode:
        AstroGraphicChart::Repaint(true);
    };
#endif
}

void AstroWindow::BackgroundColor()
{
#ifdef QT
	AstroGraphicChart::BackgroundColor();
	const QColor &sb = qApp->palette().color(QPalette::Active, QPalette::Base), &sf = qApp->palette().color(QPalette::Active, QPalette::Highlight);
	const QString x = QString("* { background-color: rgb(%1, %2, %3); selection-background-color: rgb(%4, %5, %6); background-image: url() }").arg(sb.red()).arg(sb.green()).arg(sb.blue()).arg(sf.red()).arg(sf.green()).arg(sf.blue());
	Qsa->verticalScrollBar()->setStyleSheet(x);
	Qsa->horizontalScrollBar()->setStyleSheet(x);
	ParamPm->setStyleSheet(x);
	SubringPm->setStyleSheet(x);
#endif
}

void AstroWindow::Anim(bool start)
{
#ifdef QT
    enum ChartType ct = Acb->GetCt();
    if (start && IfLocked() && (ct == StdWheels || ct == LocalHorizon || ct == AspectsArray))
    {
        qApp->beep();
        emit Amw->onoffanim->setChecked(false);
        return;
    }
    if (start && LockChart())
    {
        SetDisplayMode(DblBufMode);
        Ring = GetRing() + 1;
        QTim = new QTimer;
        QTim->setSingleShot(false);
        connect(QTim, SIGNAL(timeout()), this, SLOT(TimerSlot()));
        QTim->start(MilliSec);
    }
    else
    {
        UnlockChart();
        if (QTim)
        {
            QTim->stop();
            emit Amw->onoffanim->setChecked(false);
            SetDisplayMode(GraphicMode);
            delete QTim;
            QTim = nullptr;
        }
    }
#endif
}

void AstroWindow::TimerSlot()
{
    int s = Backward ? -1 : 1;
    AstroObjs& ao = *(*this)[IsLocked() ? Ring - 1 : GetRing()];
    ao.Modified = true;
    if (ao.Name.Left(1) != "~")
        ao.Name = "~" + ao.Name;
    ao.AstroDate::Recompute();
    double j = IncTime(ao.GetJd(), s * Second, s * Minute, s * Hour, s * Day, s * Month, s * Year);
    if (j >= MAXJD || j <= MINJD)
    {
        QTim->stop();
        AstroMessage(i18n("Sorry, the current date goes beyond the Swiss Ephemeris limits"));
        Anim(false);
        return;
    }
    ao.SetJd(j);
    ao.Recompute();
    Repaint();
}

void AstroWindow::mousePressEvent(QMouseEvent *e)
{
    int i =  IsLocked() ? Ring - 1 : GetRing();
    double rx, ry;
    AstroObjs& ao = *(*this)[i];
    QAction* qa;
    if (&ao == nullptr)
    {
        qApp->beep();
        AstroMessage(i18n("Select a valid ring !"), false);
        return;
    }
    switch (e->button())
    {
    case Qt::RightButton:
        ParamPm->exec(mapToGlobal(e->pos()));
        break;
    case Qt::LeftButton:
        if (Acb->GetIt() == AstroChartBase::Click)
        {
            if ((Acb->GetCt() == StdWheels || Acb->GetCt() == SolarSys) && ao == XPoint)
            {
                Acb->GetCoord(e->x() + Ox, e->y() + Oy, &rx, &ry);
                ao.GetInterface()->SetXPoint(rx, 0.0, ry, i);
                ao.Recompute();
                Repaint();
            }
            else if (Acb->GetCt() == Astro_Graph)
            {
                double w, h, x1, x2, y1, y2;
                auto ag = SC(AstroGraph*, Acb);
                ag->GetCoord(e->x() + Ox, e->y() + Oy, &rx, &ry);
                if (Asr->Ctrl)
                {
                    if (ag->ZoomFact == 1) return;
                    ag->ZoomFact /= 2;
                    w = fabs(ag->Rlong - ag->Llong);
                    h = fabs(ag->Tlat - ag->Blat);
                }
                else
                {
                    ag->ZoomFact *= 2;
                    w = fabs(ag->Rlong - ag->Llong) / 4.0;
                    h = fabs(ag->Tlat - ag->Blat) / 4.0;
                }
                x1 = rx - w;
                x2 = x1 + 2 * w;
                if (x1 < -179.99)
                {
                    x1 = -179.99;
                    x2 = x1 + 2 * w;
                }
                if (x2 > 180.0)
                {
                    x2 = 180.0;
                    x1 = x2 - 2 * w;
                }
                y1 = ry - h;
                y2 = y1 + 2 * h;
                if (y1 < -89.99)
                {
                    y1 = -89.99;
                    y2 = y1 + 2 * h;
                }
                if (y2 > 90.0)
                {
                    y2 = 90.0;
                    y1 = y2 - 2 * h;
                }
                ag->Llong = x1;
                ag->Rlong = x2;
                ag->Blat = y1;
                ag->Tlat = y2;
                Repaint();
            }
        }
        if (Acb->GetIt() == AstroChartBase::Buttons)
        {
            const DataLineBase* dl = Acb->GetCoord(e->x() + Ox, e->y() + Oy);
            if (!dl) return;
            const AstroObjs& ao = (Acb->Second && Acb->GetCt() == AspScList) ? *Acb->Second : *Acb->First;
            AstroString as;
            auto asp = SC(const AspData*, dl);
            const AstroString g = i18n("Global"), l = i18n("Local"), s = i18n("Solar"), u = i18n("Lunar");
            switch (asp->ak)
            {
            case ExAsp:
                AddData(Sprintf(i18n("Exact %a for %a & %a"), &as, Asr->AspectShortNames[asp->asp], &(ao < asp->a), asp->b < 0 ? Asr->PartsNames[-int(asp->b)] : &(ao < asp->b)), ExAsp, ao, dl);
                break;
            case ChangeDir:
                AddData(Sprintf(i18n("%a Changed its Direction"), &as, &(ao < asp->a)), ChangeDir, ao, dl);
                break;
            case ChangeSign:
                AddData(Sprintf(i18n("%a Enters %a"), &as, &(ao < asp->a), &((*Asg) << (int)asp->apos)), ChangeSign, ao, dl);
                break;
            case RiseSet:
                AddData(Sprintf(i18n("Rising hour for %a"), &as, &(ao < asp->a)), RiseSet, ao, dl);
                AddData(Sprintf(i18n("Culminating hour for %a"), &as, &(ao < asp->a)), RiseSet, ao, Acb->GetNext(dl, 1));
                AddData(Sprintf(i18n("Setting hour for %a"), &as, &(ao < asp->a)), RiseSet, ao, Acb->GetNext(dl, 2));
                AddData(Sprintf(i18n("Nadir hour for %a"), &as, &(ao < asp->a)), RiseSet, ao, Acb->GetNext(dl, 3));
                break;
            case Eclipse:
                AddData(Sprintf(i18n("%a Begin. %a Eclipse"), &as, asp->c == The_Earth ? &g : &l, asp->a == Sun ? &s : &u), Eclipse, ao, dl, false, asp->apos, asp->bpos);
                AddData(Sprintf(i18n("%a Max. %a Eclipse"), &as, asp->c == The_Earth ? &g : &l, asp->a == Sun ? &s : &u), Eclipse, ao, Acb->GetNext(dl, 1), false, asp->apos, asp->bpos);
                AddData(Sprintf(i18n("%a End %a Eclipse"), &as, asp->c == The_Earth ? &g : &l, asp->a == Sun ? &s : &u), Eclipse, ao, Acb->GetNext(dl, 2), false, asp->apos, asp->bpos);
                break;
            case ExDir:
                AddData(Sprintf(i18n("Arc of Dir %a & %a"), &as, &(ao < asp->a), &(ao < asp->b)), ExAsp, ao, dl);
                break;
            case ExCDir:
                AddData(Sprintf(i18n("Conv Arc of Dir %a & %a"), &as, &(ao < asp->a), &(ao < asp->b)), ExAsp, ao, dl);
                break;
            case EphemDay:
                AddData(i18n("Ephemeris Day"), EphemDay, ao, dl, true);
                break;
            case HelRising:
                AddData(Sprintf(i18n("First Hel Rising of %a"), &as, &(ao < asp->a)), HelRising, ao, dl);
                AddData(Sprintf(i18n("Optimal Hel Rising of %a"), &as, &(ao < asp->a)), HelRising, ao,  Acb->GetNext(dl, 1));
                AddData(Sprintf(i18n("Last Hel Rising of %a"), &as, &(ao < asp->a)), HelRising, ao,  Acb->GetNext(dl, 2));
                break;
            case HelSetting:
                AddData(Sprintf(i18n("First Hel Setting of %a"), &as, &(ao < asp->a)), HelRising, ao, dl);
                AddData(Sprintf(i18n("Optimal Hel Setting of %a"), &as, &(ao < asp->a)), HelRising, ao,  Acb->GetNext(dl, 1));
                AddData(Sprintf(i18n("Last Hel Setting of %a"), &as, &(ao < asp->a)), HelRising, ao,  Acb->GetNext(dl, 2));
                break;
            case EveningFirst:
                AddData(Sprintf(i18n("First Evening First of %a"), &as, &(ao < asp->a)), EveningFirst, ao, dl);
                AddData(Sprintf(i18n("Optimal Evening First of %a"), &as, &(ao < asp->a)), EveningFirst, ao,  Acb->GetNext(dl, 1));
                AddData(Sprintf(i18n("Last Evening First of %a"), &as, &(ao < asp->a)), EveningFirst, ao,  Acb->GetNext(dl, 2));
                break;
            case MorningLast:
                AddData(Sprintf(i18n("First Morning Last of %a"), &as, &(ao < asp->a)), MorningLast, ao, dl);
                AddData(Sprintf(i18n("Optimal Morning Last of %a"), &as, &(ao < asp->a)), MorningLast, ao,  Acb->GetNext(dl, 1));
                AddData(Sprintf(i18n("Last Morning Last of %a"), &as, &(ao < asp->a)), MorningLast, ao,  Acb->GetNext(dl, 2));
                break;
            case GlobOccult:
                AddData(Sprintf(i18n("First Glob Moon Occult of %a"), &as, &(ao < asp->a)), GlobOccult, ao, dl);
                AddData(Sprintf(i18n("Optimal Glob Moon Occult of %a"), &as, &(ao < asp->a)), GlobOccult, ao,  Acb->GetNext(dl, 1));
                AddData(Sprintf(i18n("Last Glob Moon Occult of %a"), &as, &(ao < asp->a)), GlobOccult, ao,  Acb->GetNext(dl, 2));
                break;
            default:
                ;
            };
        }
    default:
        ;
    }
}

void AstroWindow::AddData(const AstroString& name, enum AspKind ak, const AstroObjs& ao, const DataLineBase* dl, bool ifephem, double latitude, double longitude)
{
    if (!dl) return;
    AstroString as, as1;
    auto ad = new AstroData(*SC(const AstroData*, &ao));
    auto asp = SC(const AspData*, dl);
    if (ifephem) ad->DbFetch("ZeroGMT");
    ad->Idx = 0;
		ad->Default = false;
    ad->SetInterface(Asf);
    ad->SetJd(dl->jd);
    ad->Gender = Situation;
    ad->Name = name;
    ad->ChartType = Ail->GetSpecIcon(ak);
    ad->Latitude = (ak == Eclipse)  ? latitude : ao.Latitude;
    ad->Longitude = (ak == Eclipse)  ? longitude : ao.Longitude;
    ad->Comment = Sprintf(i18n("From Chart '%a'"), &as, &GetTitle(as1));
    ad->Recompute();

    Aiw().AddData(ad);
}

void AstroWindow::keyReleaseEvent(QKeyEvent* e)
{
	bool b;
    switch (e->key())
    {
    case Qt::Key_Control :
        Asr->Ctrl = false;
        return;
    case Qt::Key_Shift   :
        Asr->Shift = false;
        return;
		case 43: if(e->modifiers() == Qt::KeypadModifier) { b = Backward; Backward = false; TimerSlot(); Backward = b; }  return;
		case 45: if(e->modifiers() == Qt::KeypadModifier) {  b = Backward; Backward = true;  TimerSlot(); Backward = b; } return;
    default:
        ;
    };
}

void AstroWindow::keyPressEvent(QKeyEvent* e)
{
    switch (e->modifiers())
    {
    case Qt::ControlModifier :
        Asr->Ctrl = true;
        return;
    case Qt::ShiftModifier   :
        Asr->Shift = true;
        return;
    default:
        ;
    };
    switch (e->key())
    {
    case Qt::Key_PageUp:
        H -= Qsa->height() / 2;
        if (H < 0) H = 0;
        break;
    case Qt::Key_PageDown:
        H += Qsa->height() /2;
        if (H > height()) H = height();
        break;
    case Qt::Key_Home:
        H = 0;
        break;
    case Qt::Key_End:
        H = height();
        break;
    default:
        ;
    };
    Qsa->ensureVisible (0, H, 0, 0);
    if (Acb->GetCt() == Astro_Graph)
    {
        auto ag = SC(AstroGraph*, Acb);
        double x1 = ag->Llong, x2 = ag->Rlong, y1 = ag->Blat, y2 = ag->Tlat, w = fabs(x1 - x2) / 2.0,
                                    h = fabs(y1 - y2) / 2.0;
        switch (e->key())
        {
        case Qt::Key_Left:
            x1 -= w;
            x2 = x1 + 2.0 * w;
            break;
        case Qt::Key_Right:
            x1 += w;
            x2 = x1 + 2.0 * w;
            break;
        case Qt::Key_Down:
            y1 -= h;
            y2 = y1 + 2.0 * h;
            break;
        case Qt::Key_Up:
            y1 += h;
            y2 = y1 + 2.0 * h;
            break;
        default:
            ;
        }
        if (x1 < -179.99)
        {
            x1 = -179.99;
            x2 = x1 + 2.0 * w;
        }
        if (x2 > 180.0)
        {
            x2 = 180.0;
            x1 = x2 - 2.0 * w;
        }
        if (y1 < -89.99)
        {
            y1 = -89.99;
            y2 = y1 + 2.0 * h;
        }
        if (y2 > 90.0)
        {
            y2 = 90.0;
            y1 = y2 - 2.0 * h;
        }
        ag->Llong = x1;
        ag->Rlong = x2;
        ag->Blat = y1;
        ag->Tlat = y2;
        Repaint();
        return;
    }
    e->ignore();
}

bool AstroWindow::LockChart()
{
    AstroString as;
    if (IsLocked())
    {
        qApp->beep();
        return false;
    }
    AstroChart::LockChart();
    GetTitle(as);
    as += i18n(" [LOCKED]");
#ifdef QT
    Qsw->setWindowTitle(as);
#endif
    return true;
}

void AstroWindow::UnlockChart()
{
    AstroString as;
    AstroChart::UnlockChart();
    GetTitle(as);
#ifdef QT
    Qsw->setWindowTitle(as);
#endif
}

void AstroWindow::Activated(QAction* qa)
{
    int i = qa->data().toInt();
    if (IsLocked())
    {
        qApp->beep();
        return;
    }
    if (i < SUBRID)
    {
        bool *b = Acb->GetPm(i -1)->B;
        *b = !(*b);
        if (i == 1)
            Qsa->setWidgetResizable(*b);
    }
    else
        switch (i)
        {
        case SUBRID    :
            Cbp->Subring  = No_Subring;
            break;
        case SUBRID + 1:
            Cbp->Subring  = Decans;
            break;
        case SUBRID + 2:
            Cbp->Subring  = Solar_Houses;
            break;
        case SUBRID + 3:
            Cbp->Subring  = Lunar_Houses;
            break;
        case SUBRID + 4:
            Cbp->Subring  = Nodal_Houses;
            break;
        case SUBRID + 5:
            Cbp->Subring  = Terms;
        };
    Repaint(i != 1);
}

void AstroWindow::SetJbt(enum JumpBaseType jbt)
{
    Jbt = jbt;
    Day = Month = Year = Hour = Minute = Second = 0;
    switch (Jbt)
    {
    case Seconds:
        Second = Rate;
        break;
    case Minutes:
        Minute = Rate;
        break;
    case Hours:
        Hour   = Rate;
        break;
    case Days:
        Day    = Rate;
        break;
    case Months:
        Month  = Rate;
        break;
    case Years:
        Year   = Rate;
        break;
    case Centuries:
        Year   = 100 * Rate;
        break;
    case Millenia:
        Year   = 1000 * Rate;
        break;
    };
}

void AstroWindow::SetRate(int r)
{
    Rate = r;
    switch (Jbt)
    {
    case Seconds:
        Second = Rate;
        break;
    case Minutes:
        Minute = Rate;
        break;
    case Hours:
        Hour   = Rate;
        break;
    case Days:
        Day    = Rate;
        break;
    case Months:
        Month  = Rate;
        break;
    case Years:
        Year   = Rate;
        break;
    case Centuries:
        Year   = 100 * Rate;
        break;
    case Millenia:
        Year   = 1000 * Rate;
        break;
    };
}
//static const char* const fn[] = { "exasp.png", "dirch.png", "signch.png", "rising.png", "eclipse.png", "ephemeris.png", "pdir.png", "cpdir.png", "occult.png" };
AstroIconsList::AstroIconsList()
{
    int i = 0, j = 0;
    AstroIcon* ai;
    AstroString name, file;
    AstroRequest Arq;
    static const char* const fn[] = { "exasp.png", "dirch.png", "signch.png", "rising.png", "eclipse.png", "ephemeris.png", "pdir.png", "cpdir.png", "occult.png" };
    for (int k = 0; k < 9; k++)
        SpecIconsId[k] = 0;
    if (!Arq.Exec("SELECT Name, File FROM TypeIcons ORDER BY Idx"))
    {
        AstroMessage(i18n("Can't load Type icons"));
        exit(1);
    }
    if (Arq.Valid()) do
        {
            name = Arq < "Name";
            file = Arq < "File";
            ai = new AstroIcon(file, name);
            Append(ai);
            for (int k = 0; k < 9; k++)
                if (file == fn[k])
                {
                    SpecIconsId[k] = i;
                    break;
                }
            i++;
        }
        while (Arq.Next());
}

const AstroString& AstroIconsList::GetName(unsigned int idx)
{
    Index i = 0;
    foreachc(*this, AstroIconsList)
    if (i == idx)
        return (!it)->Name;
    AstroIconsList::Const_Iterator it(*this);
    return (!it)->Name;
}

int AstroIconsList::GetSpecIcon(enum AspKind ak) const
{
    if (ak <= GlobOccult)
        return SpecIconsId[ak];
    return SpecIconsId[3];
}

AstroIconsWindow::AstroIconsWindow(AstroMainWindow *amw) : QTreeWidget(amw->centralWidget())
{
    QAction* qa;
    Idx = 0;
    IsPressed = false;
    Aib = nullptr;
    const AstroPixmap& gp = *Asr->MiscPixmaps[GROUP];
#ifdef QT
    setRootIsDecorated(true);
    setSortingEnabled(false);
    setColumnCount(1);
    setHeaderLabel(i18n("Data Tree"));

    TR(Data, this, i18n("Data sets"));
    TR(Restrictions, this, i18n("Restrictions sets"));
    TR(Types, this, i18n("Types"));
    TR(SubTypes, this, i18n("Subtypes"));
    TR(Tarots, this, i18n("Tarots"));
    TR(Major, Tarots, i18n("Major"));
    TR(Sword, Tarots, i18n("Swords"));
    TR(Coin, Tarots, i18n("Coins"));
    TR(Stick, Tarots, i18n("Sticks"));
    TR(Cup, Tarots, i18n("Cups"));
    Data->setExpanded(true);
    Data->setIcon(0, gp);
    Restrictions->setIcon(0, gp);
    Types->setIcon(0, gp);
    SubTypes->setExpanded(true);
    SubTypes->setIcon(0, gp);
    Tarots->setIcon(0, gp);
    Major->setIcon(0, *Asr->MiscPixmaps[MAJOR]);
    Sword->setIcon(0, *Asr->MiscPixmaps[SWORD]);
    Coin->setIcon(0, *Asr->MiscPixmaps[COIN]);
    Stick->setIcon(0, *Asr->MiscPixmaps[STICK]);
    Cup->setIcon(0, *Asr->MiscPixmaps[CUP]);
    DataPm = new QMenu(this);
    AA1(DataPm, i18n("Edit"), 1);
    AA1(DataPm, i18n("Save"), 2);
    AA1(DataPm, i18n("Delete"), 3);
    AA1(DataPm, i18n("Duplicate"), 4);
    RestPm = new QMenu(this);
    AA1(RestPm, i18n("Edit"), 1);
    AA1(RestPm, i18n("Save"), 2);
    AA1(RestPm, i18n("Delete"), 3);
    AA1(RestPm, i18n("Duplicate"), 4);
    //setStyleSheet("background-image: url(:/pics/background.png)");
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(Clicked(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)), SLOT(Pressed(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SLOT(DoubleClicked(QTreeWidgetItem*, int)));
    connect(DataPm, SIGNAL(triggered(QAction*)), this, SLOT(Triggered(QAction*)));
    connect(RestPm, SIGNAL(triggered(QAction*)), this, SLOT(Triggered(QAction*)));
#endif
    for (int i = Show_Hide; i <= Last_SubType; i++)
        //if (i != Direction)
        (void)new AstroIconButton(this, i);
    foreachc(*Adl, AstroDataList)
    (void)new AstroIconButton(this, !it);
    foreachc(*Arl, AstroRestrictionsList)
    (void)new AstroIconButton(this, !it);
    for (int i = StdWheels; i <= Last_Type; i++)
        (void)new AstroIconButton(this, i, TypeButton);
    for (int i = 0; i <= 22; i++)
        (void)new AstroIconButton(this, i, MajorButton);
    for (int i = 0; i <= 13; i++)
    {
        (void)new AstroIconButton(this, i, SwordButton);
        (void)new AstroIconButton(this, i, CoinButton);
        (void)new AstroIconButton(this, i, StickButton);
        (void)new AstroIconButton(this, i, CupButton);
    }
}

void AstroIconsWindow::AddData(const AstroData* ad)
{
    Adl->AddData((AstroData*)ad);
    (void)new AstroIconButton(this, ad);
}

void AstroIconsWindow::AddRestrict(const AstroRestrictions* ar)
{
    Arl->AddRestrictions((AstroRestrictions*)ar);
    (void)new AstroIconButton(this, ar);
}

bool AstroIconsWindow::DeleteIdx(Index idx)
{
    if (!Ahl->CheckIdx(idx) && Aib->Bt == DataButton)
    {
        if (Aib->Idx == idx)
        {
            delete Aib;
            Aib = nullptr;
            Idx = 0;
        }
        else
            delete GetDataButton(idx);
        Adl->Remove(Adl->Get(idx));
        return true;
    }
    return false;
}

void AstroIconsWindow::DeleteCurrent()
{
    AstroRequest arq;
    switch (Aib->Bt)
    {
    case DataButton:
        if (Idx)
        {
            arq.Exec("SELECT COUNT(Idx) FROM Data WHERE Idx = %d", Idx);
            if (arq.GetInt("COUNT", 0) == 0)
            {
                if (AstroQuestion(i18n("Do you want to remove this DataSet ?")))
                {
                    Data->removeChild(Aib);
                    Adl->Remove(Adl->Get(Idx));
                    delete Aib;
                    Aib = nullptr;
                    Idx = 0;
                }
            }
            else
                switch (AstroQuestion3(i18n("Do you want to delete the\ncorresponding DB record too ?")))
                {
#ifdef QT
                case 1:
                    if (Adl->RemoveFromDb(Idx)) {
                        Data->removeChild(Aib);
                        delete Aib;
                        Aib = nullptr;
                        Idx = 0;
                    } break;
                case 2:
                    Data->removeChild(Aib);
                    Adl->Remove(Adl->Get(Idx));
                    delete Aib;
                    Aib = nullptr;
                    Idx = 0;
                    break;
                default:
                    return;
#endif
                }
        }
        else
            AstroMessage(i18n("Can't remove this icon"), false);
        break;
    case RestrictButton:
        if (Idx != 1)
        {
            arq.Exec("SELECT COUNT(Idx) FROM Restrictions WHERE Idx = %d", Idx);
            if (arq.GetInt("COUNT", 0) == 0)
            {
                if (AstroQuestion(i18n("Do you want to remove this Restrictions Set ?")))
                {
                    Restrictions->removeChild(Aib);
                    Arl->Remove(Arl->Get(Idx));
                    delete Aib;
                    Aib = nullptr;
                }
            }
            else
                switch (AstroQuestion3(i18n("Do you want to delete the\ncorresponding DB record too ?")))
                {
#ifdef QT
                case 1:
                    Restrictions->removeChild(Aib);
                    Arl->RemoveFromDb(Idx);
                    delete Aib;
                    Aib = nullptr;
                    break;
                case 2:
                    Restrictions->removeChild(Aib);
                    Arl->Remove(Arl->Get(Idx));
                    delete Aib;
                    Aib = nullptr;
                    break;
                default:
                    ;
                    return;
#endif
                }
        }
        else
            AstroMessage(i18n("Can't remove this icon"), false);
        break;
    default:
        AstroMessage(i18n("Can't remove this icon."), false);
    }
}

#ifdef QT

void AstroIconsWindow::Clicked(QTreeWidgetItem *qlvi, int c)
{
    IsPressed = false;
    const AstroIconButton* aib = SC(AstroIconButton *, qlvi);
    if (aib)
        Idx = aib->Idx;
}

void AstroIconsWindow::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) DragPos = e->pos();
    QAbstractItemView::mousePressEvent(e);
}

void AstroIconsWindow::mouseMoveEvent(QMouseEvent * e)
{

    if (!Aib || !IsPressed) return;
    if (!(e->buttons() & Qt::LeftButton)) return;
    if ((e->pos() - DragPos).manhattanLength() < QApplication::startDragDistance())
        return;
    AstroString as(PACKAGE);
    switch (Aib->Bt)
    {
    case DataButton:
        as += " Data:";
        as += Aib->Idx;
        break;
    case RestrictButton:
        as += " Restrict:";
        as += Aib->Idx;
        break;
    case TypeButton:
        as += " Type:";
        as += Aib->Idx;
        break;
    case SubTypeButton:
        as += " Subtype:";
        as += Aib->Idx;
        break;
    case MajorButton:
        as += " Major:";
        as += Aib->Idx;
        break;
    case SwordButton:
        as += " Sword:";
        as += Aib->Idx;
        break;
    case CoinButton:
        as += " Coin:";
        as += Aib->Idx;
        break;
    case StickButton:
        as += " Stick:";
        as += Aib->Idx;
        break;
    case CupButton:
        as += " Cup:";
        as += Aib->Idx;
        break;
    default:
        ;
    };
    Idx = Aib->Idx;
    auto drag = new QDrag(this);
    auto mimeData = new QMimeData;
    mimeData->setText(as);
    drag->setMimeData(mimeData);
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
    e->accept();
    IsPressed = false;
}

void AstroIconsWindow::Pressed(QTreeWidgetItem* item, int c)
{
    auto aib = SC(AstroIconButton*, item);
    Aib = (item != Data && item != SubTypes) ? aib : 0;
    switch (QApplication::mouseButtons())
    {
    case Qt::LeftButton:
        IsPressed = true;
        if (item == Data || item == Restrictions || item == Types || item == SubTypes || item == Tarots || item == Major || item == Sword || item == Coin || item == Stick || item == Cup) item->setExpanded(!item->isExpanded());
        break;
    case Qt::RightButton:
        if (Aib)
        {
            Idx = Aib->Idx;
            switch (aib->Bt)
            {
            case DataButton:
                DataPm->exec(QCursor::pos());
                break;
            case RestrictButton:
                RestPm->exec(QCursor::pos());
                break;
            default:
                ;
            };
        }
        break;
    default:
        ;
    }
}

void AstroIconsWindow::keyPressEvent(QKeyEvent* e)
{
    if (e->modifiers() == Qt::ShiftModifier) Asr->Shift = true;
    if (e->modifiers() == Qt::ControlModifier) Asr->Ctrl = true;
    e->ignore();
}

void AstroIconsWindow::keyReleaseEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Shift)  Asr->Shift = false;
    if (e->key() == Qt::Key_Control) Asr->Ctrl = false;
    e->ignore();
}

#endif

void AstroIconsWindow::UpdateDataIdx(Index oldidx, Index newidx)
{
    AstroIconButton* aib;
    if (Aib && Aib->Bt == DataButton && Aib->Idx == oldidx)
        Idx = Aib->Idx = newidx;
    aib = GetDataButton(oldidx);
    if (aib)
        aib->Idx = newidx;
    if (oldidx != newidx)
        Ahl->ChangeIdx(oldidx, newidx);
}

AstroIconsWindow::AstroIconButton::AstroIconButton(AstroIconsWindow* parent, const AstroData* ad) : QTreeWidgetItem(parent->Data)
{
    Idx = ad->Idx;
    Bt = DataButton;
#ifdef QT
    setText(0, ad->Name);
    setIcon(0, *(*Ail)[ad->ChartType]);
#endif
}

AstroIconsWindow::AstroIconButton::AstroIconButton(AstroIconsWindow* parent, const AstroRestrictions* ar) : QTreeWidgetItem(parent->Restrictions)
{
    Idx = ar->Idx;
    Bt = RestrictButton;
#ifdef QT
    setText(0, ar->Name);
    setIcon(0, *Asr->MiscPixmaps[RESTRICTION]);
#endif
}

QTreeWidgetItem* AstroIconsWindow::AstroIconButton::GetParent(const AstroIconsWindow& aiw, ButtonType bt) const
{
    switch (bt)
    {
    case SubTypeButton:
        return aiw.SubTypes;
        break;
    case TypeButton:
        return aiw.Types;
        break;
    case MajorButton:
        return aiw.Major;
        break;
    case SwordButton:
        return aiw.Sword;
        break;
    case CoinButton:
        return aiw.Coin;
        break;
    case StickButton:
        return aiw.Stick;
        break;
    case CupButton:
        return aiw.Cup;
        break;
    default:
        return 0;
    }
}

AstroIconsWindow::AstroIconButton::AstroIconButton(AstroIconsWindow* parent, int index, ButtonType bt) : QTreeWidgetItem(GetParent(*parent, bt))
{
    extern const char** RomanNumbers;
    Idx = index;
    Bt = bt;
    switch (Bt)
    {
    case SubTypeButton:
#ifdef QT
        setText(0, index == Single ? i18n("Single") : *Asr->SubTypesNames[index]);
        setIcon(0, *Asr->MiscPixmaps[SUBTYPE]);
        break;
    case TypeButton:
        setText(0, *Asr->TypesNames[index]);
        setIcon(0, *Asr->TypePixmaps[index - 1]);
        break;
    case MajorButton:
    {
        AstroString as;
        if (index != 0 && index != 22) as = RomanNumbers[index] + AstroString(" ");
        setText(0, as + *Asr->MajTarots[index]);
        break;
    }
    case SwordButton:
    case CoinButton:
    case StickButton:
    case CupButton:
        setText(0, *Asr->MinTarots[index]);
        break;
#endif
    default:
        ;
    };
}

AstroIconsWindow::AstroIconButton* AstroIconsWindow::GetDataButton(Index idx) const
{
    int i = 0;
    QTreeWidgetItem* qlvi = Data->child(i);
    AstroIconButton* aib;
    while (qlvi)
    {
        aib = SC(AstroIconsWindow::AstroIconButton*, qlvi);
        if (aib->Idx == idx) return aib;
        qlvi = Data->child(++i);
    }
    return nullptr;
}

void AstroIconsWindow::ChangeCurrent(const AstroData* ad)
{
    auto aib = SC(AstroIconButton*, currentItem());
#ifdef QT
    aib->setText(0, ad->Name);
    aib->setIcon(0,*(*Ail)[ad->ChartType]);
#endif
}

void AstroIconsWindow::ChangeCurrent(const AstroRestrictions* ar)
{
    auto aib = SC(AstroIconButton*, currentItem());
#ifdef QT
    emit aib->setText(0, ar->Name);
#endif
}

void AstroIconsWindow::Triggered(QAction* qa)
{
    switch (qa->data().toInt())
    {
    case 1:
        Amw->Edit();
        break;
    case 2:
        Amw->Save();
        break;
    case 3:
        Amw->Delete();
        break;
    case 4:
        Amw->Duplicate();
        break;
    }
}

void AstroIconsWindow::DoubleClicked(QTreeWidgetItem* qlvi, int c)
{
    auto aib = SC(AstroIconButton*, qlvi);
    if (aib)
    {
        Idx = aib->Idx;
        Amw->Edit();
    }
}

