/***************************************************************************
                          astromainwindow.cpp  -  description
                             -------------------
    begin                : Sat May 26 2001
    copyright            : (C) 2001 by Christophe Gros
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

#include "astromainwindow.h"
#include "astrosplash.h"
#ifdef QT
#include <QApplication>
#include <QDesktopWidget>
#include <QList>
#include <QMdiSubWindow>
#include <QPicture>
#include <QScrollArea>
#include <QActionGroup>
#include <QKeySequence>
#include <QIcon>
#include <QStyle>
#include <QMenuBar>
#include <QUrl>
#include <QKeySequence>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QDesktopServices>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#undef forward
#include <QFileDialog>

#endif
#include "astrodefs.h"
#include "astroprocess.h"
#include "astroutils.h"
#include "astrodata.h"
#include "searchdata.h"
#include "searchrest.h"
#include "editastrodata.h"
#include "astroenter.h"
#include "astroapp.h"
#include "searchchart.h"
#include "graphiclistbase.h"
#include "aspscanlist.h"
#include "editcountry.h"

extern "C"
{
# include "swephexp.h"
# include "sweph.h"
}

#ifdef QT
#define S(s) QKeySequence::s
#define T(s) QKeySequence(s)
#define Y(s) QStyle::s

#define MEN(menu, t) menu = menuBar()->addMenu(t); m = menu

#define PIXM(i) QIcon(*Asr->MiscPixmaps[i])
#define PIXT(i) QIcon(*Asr->TypePixmaps[i])

#define JBPM(s, t) a = JbPm->addAction(s);\
	a->setCheckable(true);\
	a->setData(t);\
	m->addAction(a)

#define JRPM(s, i, t) a = JrPm->addAction(s);\
	a->setCheckable(true);\
	a->setShortcut(QKeySequence(Qt::i));					\
	a->setData(t);\
	m->addAction(a)

#define RING(i, t, s, n) a = Rin->addAction(PIXM(i), t);	\
	a->setShortcut(QKeySequence(Qt::s));\
	a->setData(n);											\
	a->setCheckable(true);\
	Tb->addAction(a)
#endif

class WindowsList: public QList<QAction*>
{
public:

    WindowsList() {}
    ~WindowsList()
    {
        for (QList<QAction*>::iterator i = begin(); i != end(); ++i)
            delete *i;
    }
};

AstroMainWindow::AstroMainWindow()
{
    int w, h;
    AstroString as;
#ifdef QT
    setMinimumSize(320, 200);
    w = QApplication::desktop()->width();
    w -= w / 20;
    h = QApplication::desktop()->height();
    h -= h / 10;
    emit resize(w, h);
    QMa = new QMdiArea(this);
    QMa->setBackground(QBrush(QPixmap(":/pics/background.png")));
    setCentralWidget(QMa);
    DockLeft = new QDockWidget(i18n("Skylendar's Data Tree"), this);
    DockLeft->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Asr->RightDW ? Qt::RightDockWidgetArea : Qt::LeftDockWidgetArea, DockLeft);
    Aiw = new AstroIconsWindow(this);
    DockLeft->setWidget(Aiw);
    Wl = new WindowsList;
    Qar = new QActionGroup(this);
    QNam = new QNetworkAccessManager(this);
    QObject::connect(QNam, &QNetworkAccessManager::finished, this, &AstroMainWindow::Finished);
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://skylendar.sourceforge.io/Msg.php?Id=%1").arg(Asr->Id)));
#ifdef __WINNT
    request.setRawHeader("User-Agent", "Skylendar/4.1 (Win)");
#elif defined(__linux__)
    request.setRawHeader("User-Agent", "Skylendar/4.1 (Lin)");
#elif defined(__APPLE__)
     request.setRawHeader("User-Agent", "Skylendar/4.1 (Mac)");
#else
     request.setRawHeader("User-Agent", "Skylendar/4.1 ( ? )");
#endif
    request.setRawHeader("HTTP_ACCEPT_LANGUAGE", "en");
    QNr = QNam->get(request);
    SetupActions();
    connect(QMa, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(WindowActivated(QMdiSubWindow*)));
    show();
#endif
}

AstroMainWindow::~AstroMainWindow()
{
    delete Wl;
}

void AstroMainWindow::AddChart(const AstroData* ad)
{
	auto aw = new AstroWindow(this, CSC(AstroData*, ad));
	Append(aw);
	AddWindow(aw);
}

QAction* AstroMainWindow::Men(QString str, const char *slot, const QKeySequence& ks, enum QStyle::StandardPixmap pm)
{
	QAction* a;
	if(pm !=QStyle::SP_TitleBarMenuButton)
		a = new QAction(style()->standardIcon(pm), str, this);
	else
		a = new QAction(str, this);
	if(ks !=  QKeySequence(QKeySequence::UnknownKey))
		a->setShortcut(ks);
	connect(a, SIGNAL(triggered()), this, slot);
	m->addAction(a);
	return a;
}

QAction* AstroMainWindow::Men(QString str, const char *slot, const QIcon& c, const QKeySequence& ks)
{
	auto a = new QAction(c, str, this);
	if(ks != QKeySequence(QKeySequence::UnknownKey))
		a->setShortcut(ks);
	connect(a, SIGNAL(triggered()), this, slot);
	m->addAction(a);
	return a;
}

QAction* AstroMainWindow::Menc(QString str, const char *slot, const QKeySequence& ks, enum QStyle::StandardPixmap pm)
{
	QAction* a;
	if(pm !=QStyle::SP_TitleBarMenuButton)
		a = new QAction(style()->standardIcon(pm), str, this);
	else
		a = new QAction(str, this);
	if(ks != QKeySequence(QKeySequence::UnknownKey))
		a->setShortcut(ks);
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, slot);
	m->addAction(a);
	return a;
}

QAction* AstroMainWindow::Menc(QString str, const char *slot, const QIcon& c, const QKeySequence& ks)
{
	auto a = new QAction(c, str, this);
	if(ks != QKeySequence(QKeySequence::UnknownKey))
		a->setShortcut(ks);
	a->setCheckable(true);
	connect(a, SIGNAL(toggled(bool)), this, slot);
	m->addAction(a);
	return a;
}

#ifdef QT
void AstroMainWindow::SetupActions()
{
	QMenu *m1;
	Tb = addToolBar(i18n("Main"));
	MEN(File, i18n("&File"));
	open = Men(i18n("&Open"), SLOT(Read()), QIcon(":/pics/document-open.png"), S(Open));
	Tb->addAction(open);
	save = Men(i18n("&Save"), SLOT(Write()), QIcon(":/pics/document-save.png"), S(Save));
	Tb->addAction(save);
	m->addSeparator();
	print = Men(i18n("&Print"), SLOT(Print()), QIcon(":/pics/document-print.png"), S(Print));
	Tb->addAction(print);
	preview = Men(i18n("Pre&view"), SLOT(Preview()), QIcon(":/pics/document-print-preview.png"));
		Tb->addAction(preview);
  m->addSeparator();
  searchdata = Men(i18n("Search for &Data"), SLOT(SearchForData()), PIXM(SEARCHDATA), T(i18n("s")));
	Tb->addAction(searchdata);
  searchrest = Men(i18n("Search for &Restrictions Sets"), SLOT(SearchForRest()));
  editcountries = Men(i18n("Edit &Countries"), SLOT(EditCountries()));
	m->addSeparator();
	prefs = Men(i18n("Pre&ferences"), SLOT(EditDefParms()), QIcon(":/pics/configure.png")); 
  quit = Men(i18n("&Quit"), SLOT(Quit()), QIcon(":/pics/application-exit.png"), S(Quit));
  
	MEN(View, i18n("&View"));
	datatree =  Men(i18n("&Display Data Tree"), SLOT(DisplayDataTree()), T(i18n("Ctrl+v")));
	prevblock = Men(i18n("&Previous Text Block"), SLOT(Previous()), PIXM(PREVIOUS), T(Qt::SHIFT+Qt::Key_PageUp));
	nextblock = Men(i18n("&Next Text Block"), SLOT(Next()), PIXM(NEXT), T(Qt::SHIFT+Qt::Key_PageDown));
	MEN(Chart, i18n("&Charts"));
	m1 = m;
	m = m->addMenu(i18n("&Create Charts"));
	standardchart = Men(i18n("S&tandard Chart"), SLOT(StandardChart()), PIXT(0));
	textlistchart = Men(i18n("&Text List Chart"), SLOT(TextListChart()), PIXT(1));
	objectlistchart = Men(i18n("&Object List Chart"), SLOT(ObjectListChart()), PIXT(2));
	localhorizonchart = Men(i18n("L&ocal Horizon Chart"), SLOT(LocalHorizonChart()), PIXT(3));
	aspecttablechart = Men(i18n("A&spects Table Chart"), SLOT(AspectsTableChart()), PIXT(5));
	squaredchart = Men(i18n("S&quared Chart"), SLOT(SquaredChart()), PIXT(8));
	solarsystem = Men(i18n("&Solar System"), SLOT(SolarSystem()), PIXT(9));
	tarotspread = Men(i18n("&Tarots Spread"), SLOT(TarotsSpread()), PIXT(10));
	m = m1;
	editparams = Men(i18n("&Edit Parameters"), SLOT(EditParams()));
	dupwindow = Men(i18n("Duplicate &Window"), SLOT(DupWindow()));
	exportchart = Men(i18n("E&xport Chart"), SLOT(Export()));
	setowntitle = Men(i18n("Chan&ge Title"), SLOT(SetOwnTitle()));
	setx = Men(i18n("Set the value of the X point"), SLOT(SetX()), T(i18n("Ctrl+x")));
	savechart = Men(i18n("&Save into DB"), SLOT(SaveChart()));
	searchforchart = Men(i18n("Sea&rch for Charts"), SLOT(SearchForChart()));
	increment = Men(i18n("Manually &Increment Animation"), SLOT(Increment()), T(Qt::Key_Plus));
	decrement = Men(i18n("Manually &Decrement Animation"), SLOT(Decrement()), T(Qt::Key_Minus));
	invbackground = Menc(i18n("Inverse background"), SLOT(InvBackground(bool)), PIXM(INVBG), T(i18n("i")));
	backimage = Menc(i18n("Background Image"), SLOT(BackImage(bool)), T(i18n("Shift+m")));
	MEN(Data, i18n("&Data"));
	newdata = Men(i18n("&New Data"), SLOT(NewData()), PIXM(NEWDATA), T(i18n("n")));
	Tb->addAction(newdata);
	newrestrictions = Men(i18n("New &Restrictions Set"), SLOT(NewRestrictions()), T(i18n("r")));
	
	write = Men(i18n("Save"), SLOT(Write()));
	edit = Men(i18n("&Edit"), SLOT(Edit()));
	deletedata = Men(i18n("&Delete"), SLOT(Delete()));
	duplicate = Men(i18n("D&uplicate"), SLOT(Duplicate()), T(i18n("Ctrl+r"))); 
	MEN(Windows, i18n("&Windows"));
	tile = Men(i18n("&Tile Windows"), SLOT(Tile()));
	cascade = Men(i18n("&Cascade Windows"), SLOT(Cascade()));
	m->addSeparator();
	winlist = new QActionGroup(this);
	winlist->setExclusive(true);
	connect(winlist, SIGNAL(triggered(QAction*)), this, SLOT(WinListSlot(QAction*)));
	MEN(Animations, i18n("Animations"));
	m1 = m;
	m = m->addMenu(PIXM(JBASE), i18n("Jump base"));
	JbPm = new QActionGroup(this);
	auto JBPM(i18n("&Seconds"), AstroWindow::Seconds);
	JBPM(i18n("&Minutes"), AstroWindow::Minutes);
	a->setChecked(true);
	JBPM(i18n("&Hours"), AstroWindow::Hours);
	JBPM(i18n("&Days"), AstroWindow::Days);
	JBPM(i18n("M&onths"), AstroWindow::Months);
	JBPM(i18n("&Years"), AstroWindow::Years);
	JBPM(i18n("&Centuries"), AstroWindow::Centuries);
	JBPM(i18n("M&illenia"), AstroWindow::Millenia);
	connect(JbPm, SIGNAL(triggered(QAction*)), this, SLOT(Jb(QAction*)));
	m = m1;
	m1 = m;
	m = m->addMenu(PIXM(JRATE), i18n("Jump rate"));
	JrPm = new QActionGroup(this);
	JRPM("1", Key_1, 1);
	a->setChecked(true);
	JRPM("2", Key_2, 2);
	JRPM("3", Key_3, 3);
	JRPM("4", Key_4, 4);
	JRPM("5", Key_5, 5);
	JRPM("6", Key_6, 6);
	JRPM("7", Key_7, 7);
	JRPM("8", Key_8, 8);
	JRPM("9", Key_9, 9);
	m = m1;
	connect(JrPm, SIGNAL(triggered(QAction*)), this, SLOT(Jr(QAction*)));
	onoffanim = Menc(i18n("Animation On/Off"), SLOT(AnimOnOff(bool)), PIXM(ANIMOF));
	animinv = Menc(i18n("Inverse animation"), SLOT(InvAnim(bool)), PIXM(INVANIM));
	MEN(Help, i18n("&Help"));
	about = Men(i18n("A&bout"), SLOT(About()));
	doc = Men(i18n("&Online Documentation"), SLOT(Doc()), QIcon(":/pics/help-contents.png"), T(i18n("Ctrl+h")));
	Rin = new QActionGroup(this);
	RING(ONR1, i18n("Onto ring &1"), Key_A, 1);
	RING(ONR2, i18n("Onto ring &2"), Key_B, 2);
	RING(ONR3, i18n("Onto ring &3"), Key_C, 3);
	RING(ONR4, i18n("Onto ring &4"), Key_D, 4);
	connect(Rin, SIGNAL(triggered(QAction*)), this, SLOT(Triggered(QAction*)));
	JumpBase = new QComboBox(this);
	JumpBase->addItem(i18n("Seconds"));
	JumpBase->addItem(i18n("Minutes"));
	JumpBase->addItem(i18n("Hours"));
	JumpBase->addItem(i18n("Days"));
	JumpBase->addItem(i18n("Months"));
	JumpBase->addItem(i18n("Years"));
	JumpBase->addItem(i18n("Centuries"));
	JumpBase->addItem(i18n("Millenia"));
	emit JumpBase->setCurrentIndex(1);
	connect(JumpBase, SIGNAL(activated(int)), this, SLOT(Jb(int)));
	Tb->addWidget(JumpBase);
	JumpRate =  new QComboBox(this);
	JumpRate->addItem("1");
	JumpRate->addItem("2");
	JumpRate->addItem("3");
	JumpRate->addItem("4");
	JumpRate->addItem("5");
	JumpRate->addItem("6");
	JumpRate->addItem("7");
	JumpRate->addItem("8");
	JumpRate->addItem("9");
	connect(JumpRate, SIGNAL(activated(int)), this, SLOT(Jr(int)));
	Tb->addWidget(JumpRate);
	Tb->addAction(onoffanim);
	Tb->addAction(animinv);
	Tb->addAction(invbackground);
	Tb->addAction(prevblock);
	Tb->addAction(nextblock);
}

void AstroMainWindow::Triggered (QAction* qa)
{
    auto aw = ActiveWindow();
    if (!aw) return;
    Ring = qa->data().toInt();
    aw->Ring = Ring;
}

void AstroMainWindow::Jr(QAction* a)
{
    auto aw = ActiveWindow();
    if (!aw) return;
		int i = a->data().toInt();
    aw->SetRate(i + 1);
		JumpRate->setCurrentIndex(aw->Rate - 2);
}

void AstroMainWindow::Jr(int i)
{
	auto aw = ActiveWindow();
	if (!aw) return;
	aw->SetRate(i + 1);
	JrPm->actions()[aw->Rate - 1]->setChecked(true);	
}

void AstroMainWindow::Jb(QAction* a)
{
		auto aw = ActiveWindow();
		if (!aw) return;
		int i = a->data().toInt();
		aw->SetJbt(SC(enum AstroWindow::JumpBaseType, i));
		JumpBase->setCurrentIndex(aw->Jbt);		
}

void AstroMainWindow::Jb(int i)
{
	auto aw = ActiveWindow();
  if (!aw) return;
	aw->SetJbt(SC(enum AstroWindow::JumpBaseType, i));
	JbPm->actions()[aw->Jbt]->setChecked(true);	
}

void AstroMainWindow::WindowActivated(QMdiSubWindow* w)
{
    if (!w) return;
    auto qsa = SC(const QScrollArea*, w->widget());
    if (!qsa) return;
    auto aw = SC(const AstroWindow*, qsa->widget());
    if (!aw) return;
    emit onoffanim->setChecked(aw->IfAnim);
    emit animinv->setChecked(aw->Backward);
    emit invbackground->setChecked(aw->Cpr->InvBack);
    emit backimage->setChecked(aw->Cpr->BackImage);
    JumpRate->setCurrentIndex(aw->Rate - 1);
    JumpBase->setCurrentIndex(aw->Jbt);
		JbPm->actions()[aw->Jbt]->setChecked(true);
		JrPm->actions()[aw->Rate - 1]->setChecked(true);
		Rin->actions()[aw->Ring - 1]->setChecked(true);
    CheckWindow(aw);
		auto Glb = DC(GraphicListBase*, aw->Acb);
		prevblock->setEnabled(Glb);
		nextblock->setEnabled(Glb);
		/*if(Glb)
			{
				prevblock->setEnabled(Glb->FirstLine > 0);
				nextblock->setEnabled(!Glb->IsEnd());
			}
		else
			{
				prevblock->setEnabled(false);
        nextblock->setEnabled(false);
				}*/
}

void AstroMainWindow::AddWindow(const AstroWindow* aw)
{
    CountWindows++;
		auto a = winlist->addAction(aw->GetCurTitle());
		a->setCheckable(true);
		QVariant v;
		v.setValue((void*)aw);
		a->setData(v);
		Windows->addAction(a);
    CheckWindow(aw);
}

void AstroMainWindow::RemWindow(const AstroWindow* aw)
{
	auto qa = winlist->actions();
	for(QList<QAction*>::iterator it = qa.begin(); it != qa.end(); it++)
	{
		auto w = RC(AstroWindow*, (*it)->data().value<void*>());
		if(w == aw)
		{
			winlist->removeAction(*it);
			delete *it;
			break;
		}
	}
    Remove(CSC(AstroWindow*, aw));
    CheckWindow(ActiveWindow());
}

void AstroMainWindow::ChangeWindow(const AstroWindow* aw, const QString& newname)
{
}

void AstroMainWindow::CheckWindow(const AstroWindow* aw) const
{
	auto qa = winlist->actions();
	for(QList<QAction*>::iterator it = qa.begin(); it != qa.end(); it++)
	{
		auto w = RC(AstroWindow*, (*it)->data().value<void*>());
		if(w == aw)
		{
			(*it)->setChecked(true);
			break;
		}
	}
}

const AstroString& AstroMainWindow::RenameWindow(AstroString& as)
{
    int count = 0;
    AstroString buf;
    foreachc(*this, AstroMainWindow)
    if ((!it)->windowTitle() == as)
        count++;
    return count ? Sprintf("%a (%d)", &buf, &as, count) : as;
}

void AstroMainWindow::WinListSlot(QAction* a)
{
    // auto ka = SC(const AstroToggleAction*, sender());
    // if (ka)
    // {
    //     //const QString name = ka->text();
    //     foreachc(*this, AstroMainWindow)
    //     if (!it == ka->Aw)
    //     {
    //         CheckWindow(!it);
    //         emit QMa->setActiveSubWindow((!it)->Qsw);
    //         return;
    //     }
    // }
}

#endif

void AstroMainWindow::Increment()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    bool b = aw->Backward;
    aw->Backward = false;
    aw->TimerSlot();
    aw->Backward = b;
}

void AstroMainWindow::Decrement()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    bool b = aw->Backward;
    aw->Backward = true;
    aw->TimerSlot();
    aw->Backward = b;
}

void AstroMainWindow::AnimOnOff(bool b)
{
    auto aw = ActiveWindow();
    if (!aw) return;
    aw->IfAnim = b;
    aw->Anim(aw->IfAnim);
}

void AstroMainWindow::InvAnim(bool b)
{
    auto aw = ActiveWindow();
    if (aw) aw->Backward = b;
}

void AstroMainWindow::InvBackground(bool b)
{
    auto aw = ActiveWindow();
    if (!aw) return;
    aw->Cpr->InvBack = b;
    aw->BackgroundColor();
    aw->Repaint(false);
}

void AstroMainWindow::BackImage(bool b)
{
    auto aw = ActiveWindow();
    if (!aw) return;
    aw->Cpr->BackImage = b;
    aw->BackgroundColor();
    aw->Repaint(false);
}


void AstroMainWindow::Previous()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    auto Glb = DC(GraphicListBase*, aw->Acb);
    if (!Glb) return;
    Glb->FirstLine -= Asr->NbLines;
    if (Glb->FirstLine <= 0)
    {
        Glb->FirstLine = 0;
        Glb->LastLine = Asr->NbLines;
        //prevblock->setEnabled(false);
        //nextblock->setEnabled(true);
        qApp->beep();
        aw->Repaint(false);
        return;
    }
    nextblock->setEnabled(true);
    Glb->FirstLine -= Asr->NbLines;
    Glb->LastLine -= Asr->NbLines;
    aw->Repaint(false);
}

void AstroMainWindow::Next()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    auto Glb = DC(GraphicListBase*, aw->Acb);
    if (!Glb) return;
    if (Glb->IsEnd())
    {
			//nextblock->setEnabled(false);
			//prevblock->setEnabled(true);
        qApp->beep();
        aw->Repaint(false);
        return;
    }
    prevblock->setEnabled(true);
    Glb->FirstLine += Asr->NbLines;
    Glb->LastLine += Asr->NbLines;
    aw->Repaint(false);
}

void AstroMainWindow::SetX()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    AstroObjs& ao = *(*aw)[aw->Ring - 1];
    AstroHM hm;
    hm.Set(ao * XPoint);
    const DataValues& dv = ao.GetXPoint();
    AstroString as, as1 = ao.XPDec ? AstroString(QString("%1").arg(hm.Get(true))) : hm.Get(as, HM_Sign, false, true);
    if (dv[1] || dv[2])
    {
        as1 += ",";
        as1 += dv[1];
        as1 += ",";
        as1 += dv[2];
    }
    AstroEnter ae(as1, i18n("Value of the X Point"));
#ifdef QT
    if (ae.exec() == QDialog::Accepted)
    {
        double d, d1 = 0.0, d2 = 0.0;
        bool ok;
        int count;
        AstroStringList asl;
        Split(ae.Name->text(), ",", &asl);
        count = asl.Count();
        if (count >= 1)
        {
            d = asl[0]->toDouble(&ok);
            if (ok)
            {
                hm.Set(d);
                ao.XPDec = true;
            }
            else
            {
                hm.Set(*asl[0], HM_Sign);
                ao.XPDec = false;
            }
            if (count >= 2)
            {
                d1 = asl[1]->toDouble(&ok);
                if (!ok) d1 = 0.0;
            }
            if (count >= 3)
            {
                d2 = asl[2]->toDouble(&ok);
                if (!ok) d2 = 0.0;
            }
            ao.GetInterface()->SetXPoint(hm.Get(true), d1, d2, aw->Ring - 1);
            ao.Recompute();
            aw->Repaint();
        }
    }
#endif

}

AstroWindow* AstroMainWindow::ActiveWindow() const
{
#ifdef QT
    QMdiSubWindow* qma = QMa->activeSubWindow();
    if (!qma) return 0;
    auto qsa = SC(QScrollArea*, qma->widget());
    return SC(AstroWindow*, qsa->widget());
#endif
}

void AstroMainWindow::StandardChart()
{
    NewChart(StdWheels);
}

void AstroMainWindow::ObjectListChart()
{
    NewChart(ObjectList);
}

void AstroMainWindow::TextListChart()
{
    NewChart(GraphicList);
}

void AstroMainWindow::LocalHorizonChart()
{
    NewChart(LocalHorizon);
}

void AstroMainWindow::AspectsTableChart()
{
    NewChart(AspectsArray);
}

void AstroMainWindow::SquaredChart()
{
    NewChart(Squared);
}

void AstroMainWindow::SolarSystem()
{
    NewChart(SolarSys);
}

void AstroMainWindow::TarotsSpread()
{
    NewChart(Tarots_Spreads);
}

void AstroMainWindow::NewChart(enum ChartType ct)
{
    auto ad = Aiw->GetData();
		auto aw = new AstroWindow(this, ad ? ad : Now, ct);
		Append(aw);
		AddWindow(aw);
}

void AstroMainWindow::EditParams()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    if (aw->EditParms())
        aw->Repaint(true);
}

void AstroMainWindow::EditDefParms()
{
	if(Asr->Edit()) Asr->Save();
}

void AstroMainWindow::EditCountries()
{
    EditCountry ec;
    ec.exec();
}

void AstroMainWindow::Export()
{
    auto aw = ActiveWindow();
    if (!aw) return;
#ifdef QT
    if (aw->QPict)
    {
			const QString f =  QFileDialog::getSaveFileName(this, i18n("Get a .svg file"), "", i18n("Vector file (*.svg)"));
        if (!f.isNull())
        {
					//if (!aw->QPict->save(f))// "svg"))
					if(!aw->SaveSVG(f))
                AstroMessage(i18n("Can't save current chart"));
        }
    }
#endif
}

void AstroMainWindow::SaveChart()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    AstroChart& ac = *SC(AstroChart*, aw);
    ac.Save();
}

void AstroMainWindow::Quit()
{
    AstroString as;
    if (AstroQuestion(Sprintf(i18n("Do you really want to quit %s ?"), &as, PACKAGE)))
    {
        CloseServices();
        Asr->AspIdx.Purge();
        delete Asq;
        qApp->quit();
    }
}

void AstroMainWindow::Read()
{
#ifdef QT
    QString file =  QFileDialog::getOpenFileName(this, i18n("Get an astrological data file"), "", i18n(" Astrological data file (*.skif *.kst *.dat *.aaf *.mtx *.zbs *.qck)"));
    QRegExp r(".*\\.(\\w{,4})$");
    if (r.indexIn(file) > -1)
    {
        const QStringList qsl = r.capturedTexts();
        QString ra;
        const QString t = QDir::tempPath() + QDir::separator() + "sk" + ra.setNum(rand()) + ".skif";
        QStringList::const_iterator it = qsl.begin();
        ++it;
        while (it != qsl.end())
        {
            if ((*it).toLower() != "skif")
            {
                QStringList arg;
                QProcess qp;
                QDir qd;
                arg << "--out=" + t;
                arg << "--tzp=\"" + AstroString(Asr->ZPath) + "\"";
                if ((*it).toLower() == "aaf")
                {
                    arg << "--db=" + Asr->DbName << "--user=" + Asr->DbUser;
                    if (!Asr->DbHost.isEmpty()) arg << "--host=" + Asr->DbHost;
                    if (!Asr->DbPass.isEmpty()) arg << "--pw=" + Asr->DbPass;
                }
                arg << "\"" + file + "\"";
                qp.execute("skif.pl", arg);
                if (qp.exitStatus() != QProcess::NormalExit)
                {
                    AstroString as, as1 = QString(qp.readAllStandardOutput());
                    AstroMessage(Sprintf(i18n("skif.pl returned:\n %a"), &as, &as1), false);
                    return;
                }
                ReadSKIF(AstroString(t));
                qd.remove(t);
            }
            else
                ReadSKIF(AstroString(file));
            ++it;
        }
    }
#endif
}


void AstroMainWindow::Write()
{
    bool selected;
    AstroString file;
    switch (AstroQuestion3(i18n("Do you want do save only the selected DataSet ?\nIf NO, all the DataSets (Except Now) will be saved")))
    {
    case 1:
        selected = true;
        break;
    case 2:
        selected = false;
        break;
    default:
        return;
    };
#ifdef QT
    file =  AstroString(QFileDialog::getSaveFileName(this, i18n("Get a SKIF file"), "", i18n("SKIF File (*.skif)")));
    if (file.isNull())
        return;
#endif
    WriteSKIF(file, selected ? Aiw->GetData() : 0);
}

void AstroMainWindow::SetOwnTitle()
{
    AstroString as;
    auto aw = ActiveWindow();
    if (!aw) return;
    AstroEnter ae(aw->GetTitle(as), i18n("Enter the new chart's title'"));
#ifdef QT
    if (ae.exec() == QDialog::Accepted)
    {
        aw->Acb->SetOwnTitle(ae.GetName());
        aw->Repaint();
        aw->Qsw->setWindowTitle(ae.GetName());
    }
#endif
}

void AstroMainWindow::Tile()
{
#ifdef QT
    emit QMa->tileSubWindows();
#endif
}

void AstroMainWindow::Cascade()
{
#ifdef QT
    emit QMa->cascadeSubWindows();
#endif
}

void AstroMainWindow::NewData()
{
    auto ada = new AstroData;
    ada->Now();
    if (ada->Edit())
        Aiw->AddData(ada);
    else
        delete ada;
}

void AstroMainWindow::SearchForData()
{
    SearchData sd;
    sd.exec();
}

void AstroMainWindow::SearchForRest()
{
    SearchRest sr;
    sr.exec();
}

void AstroMainWindow::NewRestrictions()
{
    auto ar = new AstroRestrictions;
    ar->Name = i18n("New restrictions set");
    if (ar->Edit())
        Aiw->AddRestrict(ar);
    else
        delete ar;
}

void AstroMainWindow::Edit()
{
    if (Aiw->Aib)
        switch (Aiw->Aib->Bt)
        {
        case DataButton:
            EditData();
            break;
        case RestrictButton:
            EditRestr();
            break;
            //case TypeButton:
        default:
            AstroMessage(i18n("Can't edit this icon."), false);
        }
}

void AstroMainWindow::Save()
{
    AstroData* ad;
    AstroRestrictions* ar;
    Index oldidx;
    if (Aiw->Aib)
        switch (Aiw->Aib->Bt)
        {
        case DataButton:
            ad = Aiw->GetData();
            oldidx = ad->Idx;
            Aiw->UpdateDataIdx(oldidx, ad->DbSave());
            break;
        case RestrictButton:
            ar = Aiw->GetRestrictions();
            oldidx = ar->Idx;
            Aiw->Idx = Aiw->Aib->Idx = ar->DbSave();
            ar->Modified = false;
            break;
        default:
            AstroMessage(i18n("Can't save this icon."), false);
        }
}

void AstroMainWindow::PaintPreview(QPrinter* printer)
{
	auto aw = ActiveWindow();
	if (!aw) return;
	QPainter p;
	if(!p.begin(printer))
	{
		AstroMessage(i18n("Printer not available"), true);
		return;
	}
	aw->SetDisplayMode(AstroGraphicChart::PreviewMode);
	QPainter *orig = aw->Qp;
	aw->Qprint = printer;
	aw->Qp = &p;
	aw->PreRedraw(true);
	aw->Acb->Redisplay();
	//p.drawPicture(0, 0, *aw->QPict);
	//aw->QPict->play(&p);
	aw->PostRedraw();
	aw->Qp = orig;
	aw->Qprint = nullptr;
	aw->SetDisplayMode(AstroGraphicChart::GraphicMode);
	aw->Repaint();
}

void AstroMainWindow::Print()
{
    auto aw = ActiveWindow();
    if (!aw) return;
    aw->SetDisplayMode(AstroGraphicChart::PrintMode);
    aw->Repaint();
    aw->SetDisplayMode(AstroGraphicChart::GraphicMode);
    aw->Repaint(false);
}

void AstroMainWindow::Preview()
{
    auto aw = ActiveWindow();
    if (!aw) return;
		auto Qpp = new QPrintPreviewDialog(aw->Qprint, this);
		connect(Qpp, SIGNAL(paintRequested(QPrinter*)), this, SLOT(PaintPreview(QPrinter*)));
		Qpp->resize(640, 480);
		Qpp->exec();
    aw->Repaint(false);
		delete Qpp;
}

void AstroMainWindow::EditRestr()
{
    AstroRestrictions* ar = Aiw->GetRestrictions();
    if (ar->Edit())
    {
        Aiw->ChangeCurrent(ar);
        Ahl->UpdateRestrict(ar);
        UpdateCharts(ar->Idx, false);
    }
}

void AstroMainWindow::EditData()
{
    AstroData* ad = Aiw->GetData();
    if (ad->Edit())
    {
        Aiw->ChangeCurrent(ad);
        Ahl->UpdateData(ad);
        UpdateCharts(ad->Idx, true);
    }
}

void AstroMainWindow::UpdateCharts(Index idx, bool data)
{
    bool b = Asr->Ctrl;
    Asr->Ctrl = true;
    foreach(*this, AstroMainWindow)
    {
        AstroWindow& aw = *(*it);
        if (aw.GetCt() == AspScList || aw.GetCt() == Ephemeris || aw.GetCt() == Directions || aw.GetCt() == Batch)
            for (int i = 0; i < NBDATA; i++)
            {
                const AstroObjs& a = *aw[i];
                if (aw[i] && ((data && a.Idx == idx) || (!data && a().Idx == idx)))
                {
                    aw.Repaint(true);
                    break;
                }
            }
    }
    Asr->Ctrl = b;
}

void AstroMainWindow::Delete()
{
    if (Aiw->Aib)
        switch (Aiw->Aib->Bt)
        {
        case DataButton:
            DeleteData();
            break;
        case RestrictButton:
            DeleteRestr();
            break;
        default:
            AstroMessage(i18n("Can't delete this icon."), false);
        }
}

void AstroMainWindow::Duplicate()
{
    AstroData* ad;
    AstroRestrictions* ar;
    AstroString as;
    if (Aiw->Aib)
        switch (Aiw->Aib->Bt)
        {
        case DataButton:
            ad = new AstroData(*Aiw->GetData());
            ad->Idx = 0;
						ad->Default = false;
            ad->Name = Sprintf(i18n("Copy of %a"), &as, &ad->Name);
            Aiw->AddData(ad);
            break;
        case RestrictButton:
            ar = new AstroRestrictions(*Aiw->GetRestrictions());
            ar->Idx = 0;
						ar->Default = false;
            ar->Name = Sprintf(i18n("Copy of %a"), &as, &ar->Name);
            Aiw->AddRestrict(ar);
            break;
        default:
            AstroMessage(i18n("Can't duplicate this icon."));
        }
}

void AstroMainWindow::DisplayDataTree()
{
    DockLeft->setFloating(false);
		DockLeft->setVisible(true);
}

void AstroMainWindow::DupWindow(enum ChartType cti)
{
    AstroString as;
    const AstroWindow& cur = *ActiveWindow();
    auto aw = new AstroWindow(this, cur, cti);
    Append(aw);
    AddWindow(aw);
}


void AstroMainWindow::DupWindow()
{
    DupWindow(ActiveWindow()->GetCt());
    ActiveWindow()->Repaint(false);
}

void AstroMainWindow::DeleteData()
{
    const AstroData* ad = Aiw->GetData();
    foreachc(*Ahl, AstroChartList)
    {
        if (!Aiw->Aib)
        {
            AstroMessage(i18n("Can't delete this item !"), false);
            return;
        };
        if ((!it)->IfData(ad) != -1)
        {
            AstroMessage(i18n("Data in use. Can't delete it !"), false);
            return;
        }
    }
    Aiw->DeleteCurrent();
}

void AstroMainWindow::DeleteRestr()
{
    const AstroRestrictions* ar = Aiw->GetRestrictions();
    foreachc(*Ahl, AstroChartList)
    {
        if (!Aiw->Aib)
        {
            AstroMessage(i18n("Can't delete this item !"), false);
            return;
        };
        if ((!it)->IfRestrict(ar) != -1)
        {
            AstroMessage(i18n("Restrictions set in use. Can't delete it !"), false);
            return;
        }
    }
    Aiw->DeleteCurrent();
}

void AstroMainWindow::Close(AstroWindow* aw)
{
    if (aw->Idx > 0)
    {
        switch (AstroQuestion(i18n("Do you want to delete the corresponding Database entry ?")))
        {
        case 1:
            Ahl->Delete(aw->Idx);
            aw->Idx = 0;
            break;
        case 2:
        case 0:
        default:
            ;
        };
    }
    Remove(aw);
}

void AstroMainWindow::closeEvent(QCloseEvent* e)
{
    AstroString as;
    if (AstroQuestion(Sprintf(i18n("Do you really want to quit %s ?"), &as, PACKAGE)))
    {
        CloseServices();
        Asr->AspIdx.Purge();
        exit(0);
    }
		else
			e->ignore();
}

void AstroMainWindow::DupnDrop(enum ButtonType bt, int i)
{
    AstroWindow& cur = *ActiveWindow();
    auto aw = new AstroWindow(this, cur, NullChart);
    Append(aw);
    AddWindow(aw);
    if (bt != TypeButton) aw->SetCt(cur.GetCt());
    aw->Cpr = cur.Cpr;
    aw->DropAction(bt, i,  0, 0);
}


/*!
    \fn AstroMainWindow::SearchForChart()
 */
void AstroMainWindow::SearchForChart()
{
    SearchChart sc;
    if (sc.exec() == QDialog::Accepted)
        for (int i = 0; i < sc.Nb; i++)
        {
            auto aw = new AstroWindow(this, sc.Idx[i]);
						if(aw->GetCt() == NullChart)
						{
							delete aw;
							return;
						}
            Append(aw);
            AddWindow(aw);
        }
}

AstroAbout::AstroAbout()
{
	setupUi(this);
	setWindowModality(Qt::NonModal);
	setAttribute(Qt::WA_DeleteOnClose);
	QString s = Text->toHtml();
	s.replace("$1", VERSION);
	s.replace("$2", SKYSITE);
	s.replace("$3", SE_VERSION);
	Text->setHtml(s);
	show(); 
}

void AstroMainWindow::About()
{
 auto a = new AstroAbout();
}

void AstroMainWindow::Doc()
{
	QDesktopServices::openUrl(QUrl("http://sourceforge.net/skylendar/index.html"));
	// auto t = new QTextBrowser;
	// t->setWindowTitle(i18n("Online Documentation"));
	// t->resize(600, 400);
	// t->setWindowModality(Qt::NonModal);
	// t->setAttribute(Qt::WA_DeleteOnClose);
	// t->setSearchPaths(QStringList(SkyPath));
	// QFile f("http://sourceforge.net/skylendar/index.html");
	// f.open(QIODevice::ReadOnly | QIODevice::Text);
	// QString s = f.readAll();
	// f.close();
	// t->setHtml(s);
	// t->show();
}

void AstroMainWindow::Finished(QNetworkReply *reply)
{
    reply->open(QIODevice::ReadOnly);
    QByteArray qba =  reply->read(1000000);
    reply->close();
//    delete reply;
//    delete QNam;
    if(qba.size() == 0) return;
    auto qte = new QTextEdit(nullptr);
    qte->setReadOnly(true);
    qte->insertHtml(QString(qba));
    auto qsa = new QScrollArea(nullptr);
    qsa->setAttribute(Qt::WA_DeleteOnClose);
    qsa->setWindowTitle(i18n("Message"));
    qsa->setWidget(qte);
    qsa->resize(200, 200);
    qsa->move(width() - 200, 20);
    qsa->show();
}

#ifdef QT
void AstroMainWindow::customEvent(QEvent* c)
{
    auto ae = DC(const AstroEvent*, c);
		if (ae->type() != 1234) return;
    //if (ae->type() < 1234 || ae->type() > 1235) return;
		// if(ae->type() == 1235)
		// 	{
		// 		extern AstroSplash* Asp;
		// 		delete Asp;
		// 		return;
		// 	}
    foreach(*this, AstroMainWindow)
    if (DC(ParamListBase*, (*it)->Acb) == ae->Plb)
    {
        ae->Plb->Finish();
        (*it)->Repaint(false);
        return;
    }
}

#endif
