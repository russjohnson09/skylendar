/***************************************************************************
                          astroapp.cpp  -  description
                             -------------------
    begin                : Wed Oct 18 2000
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

#include "astroapp.h"
#include "astrodefs.h"
#include "astrodata.h"
#include "astroprocess.h"
#include "astrorestrictions.h"
#include "astrochart.h"
#include "astrosql.h"
#include "astroparams.h"
#include "astrowindow.h"
#include "astrosigns.h"
#include "astrochartbase.h"
#include "stdwheelchart.h"
#include "astrolist.h"
#include "astroaspects.h"
#include "astrointerface.h"
#include "astromainwindow.h"
#include "astrograph.h"
#include "astrogetvalues.h"
#include "scanspan.h"
#include "tzlist.h"
#include <iostream>
#include <cstdlib>
#include "astrosplash.h"
#include "astroprocess.h"
#ifdef QT
# include <QCommandLineParser>
# include <QFile>
# include <QSplashScreen>
# include <QTranslator>
# include <astrogetvaluesadaptor.h>
#elif defined(KF5)
# include <KCoreAddons/KAboutData>
# include <KCrash>
#endif

extern "C"
{
# include "swe/swephexp.h"
# include "swe/sweph.h"
};
#ifdef __WINNT
# include <processthreadsapi.h>
STARTUPINFO Startup;
PROCESS_INFORMATION ProcessInfo;
#else
extern "C"
{
# include <signal.h>
};
#endif

extern AstroSplash* Asp;
QString SkyPath;

static void CrashHandler(int)
{
    delete Asq;
    CloseServices();
}

AstroApp::AstroApp(int argc, char *argv[])
{
  QApplication skylendar(argc, argv);
	QApplication::setApplicationName(PACKAGE);
	QApplication::setOrganizationDomain("skylendar.org");
    QApplication::setApplicationVersion(VERSION);
	QCommandLineParser parser;
	parser.setApplicationDescription("Astrology software");
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption DebugOption("b", QCoreApplication::translate("main", "Debug"));
	parser.addOption(DebugOption);
	   // An option with a value
	QCommandLineOption DatasetOption(QStringList() << "d" << "dataset",
    QCoreApplication::translate("main", "Load Dataset <dataset>."),
    QCoreApplication::translate("main", "dataset"));
	parser.addOption(DatasetOption);
	QCommandLineOption RestrictionsetOption(QStringList() << "r" << "restriction_set",
    QCoreApplication::translate("main", "Load Restrictions set <restrictions set>."),
    QCoreApplication::translate("main", "restrictions set"));
	parser.addOption(RestrictionsetOption);
	parser.addPositionalArgument("skif", QCoreApplication::translate("main", "Skif file to load."));
	parser.process(skylendar);
	Skif = parser.positionalArguments();
	Dataset = parser.value(DatasetOption);
	Restrictionset = parser.value(RestrictionsetOption);
	D = parser.isSet(DebugOption);
	QApplication::setWindowIcon(QIcon(":/icon.png"));
	QTranslator t;
	/*QStringList qsl = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
for (QStringList::const_iterator it = qsl.constBegin();  it != qsl.constEnd(); ++it)
	{
		QDir d((*it) + "/pics");
		if(d.exists())
		{
			path = *it;
			break;
		}
		}*/
#ifdef __WINNT
	QSettings settings(QString("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Skylendar\\skylendar ") + VERSION, QSettings::NativeFormat);
	SkyPath = settings.value("Default").toString().replace("\\", "/") + "/data";
	int i = 100;
	// if(!QDBusConnection::sessionBus().isConnected())
	// {
	// 	/*int i = 100;
// 	QString xx = "start /B dbus-daemon --config-file=\"" + SkyPath + "/session.conf\"";
	// 	char buf[200];
	// 	strncpy(buf, xx.toUtf8().data(), 200);
	// 	if(CreateProcessA(NULL, LPSTR(buf), NULL, NULL, TRUE, DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP, NULL, NULL, &Startup, &ProcessInfo) == 0)*/
	// 	qint64 pid;
	// 	QStringList arg;
	// 	int i = 100;
	// 	//QString xx = "--config-file=\"" + SkyPath + "/session.conf\"";
	// 	arg << "start" << "/B" << "/I" << "--config-file=\"" + SkyPath + "/session.conf\"" << "--nopidfile" << "--nofork";
	// 	//QProcess qp;
	// 	//qp.start("dbus-daemon.exe", arg);
	// 	if(!QProcess::startDetached("dbus-daemon.exe", arg, QString(), &pid))
	// 	{
	// 		AstroMessage(i18n("Can't start dbus-daemon. Error code=%1").arg(GetLastError()));
	// 		exit(1);
	// 	}
		while(!QDBusConnection::sessionBus().isConnected() && i) { QThread::msleep(100); i--; }
		if(!i)
		{
			AstroMessage(i18n("Can't connect to dbus daemon"));
			exit(2);
		}

#else
	SkyPath = SKYPATH;
#endif
if(t.load("skylendar_" + QLocale::system().name(), SkyPath))
	skylendar.installTranslator(&t);
#ifdef KF5
	KAboutData about(PACKAGE, i18n(PACKAGE), VERSION, i18n("A modern design astrology program, using swisseph %1").arg(SE_VERSION), KAboutLicense::LGPL, i18n("Copyright (C) 2014 Christophe Gros"));
	about.addAuthor(i18n("Christophe Gros"), i18n("Author"), "skylendar@yahoo.com", "http://skylendar.kde.org");
	about.addCredit(i18n("Christian Amy and François Ilacqua."), i18n("Merci François and Chrisian for the given hardware,\nthe Internet download parties and much more...!"));
 about.addCredit(i18n("Alois Treindl, Dieter Koch"), i18n("Swisseph library developer"), "alois@astro.ch", "www.astro.ch");
 about.addCredit(i18n("Walter D.Pullen"), i18n("Astro-Graph map inspired from astrolog"), "Astara@msn.com", "www.astrolog.org");
 about.addCredit(i18n("Jean-Pierre Demailly"), i18n("CIA_WDB2 file reading routines inspired from xrmap"), "demailly@ujf-grenoble.fr");
 about.addCredit(i18n("Valentin Abramov"), i18n("Texts of Interpretation"), "valja@www.bdcol.ee");
 about.addCredit(i18n("Bob Makransky"), i18n("Primary Directions computing"), "bw@posthorse.com");
 about.addCredit(i18n("Andreas Schröter"), i18n("Tarots Cards"), "aquatictarot@atarot.de");
 KAboutData::setApplicationData(about);
 KCrash::setCrashHandler(CrashHandler);
#elif !defined(__WINNT)
 const struct sigaction s = { [](int i) { CrashHandler(i); exit(2); }, 0L, 0, 0, 0L };
 sigaction(SIGSEGV, &s, nullptr);
#endif
 if (!PreLogin()) exit(1);
 Asp = new AstroSplash(this);
 skylendar.exec();
}

AstroApp::~AstroApp()
{
}

void CloseServices()
{
    if (Ahl)
        foreachc(*Ahl, AstroChartList)
    {
        const AstroChart* ac = !it;
        if (ac && ac->Acb && ac->Acb->Cbp && ac->Acb->Cbp->Aif)
            ac->Acb->Cbp->Aif->Kill();
    }
    if (Asf) Asf->Kill();
}

void AstroApp::ProcessArgs()
{
		Asr->IfDebug = D;
    for (QStringList::const_iterator it = Skif.constBegin(); it != Skif.constEnd(); ++it)
			ReadSKIF(AstroString(QFile::decodeName(it->toUtf8())));
		if(!Dataset.isEmpty())
			{
				auto ad = new AstroData;
				if (!ad->DbFetch(Dataset))
				{
					qDebug() << "Can't load data set " << Dataset;
					delete ad;
				}
				else
					Adl->AddData(ad);
			}
		if(!Restrictionset.isEmpty())
			{
				auto ar = new AstroRestrictions;
				if (!ar->DbFetch(Restrictionset))
				{
					qDebug() << "Can't load restrictions set " << Restrictionset;
					delete ar;
				}
				else
					Arl->AddRestrictions(ar);
			}
}

bool PreLogin()
{
    Acl = new AstroColorList;
    Asr = new AstroResources;
    Asq = new AstroSQL;
    return Asq->IfOk();
}

bool PostLogin(AstroApp* ap, QString dbname, QString username, QString password, QString hostname)
{
    AstroString as, err;
    AstroData *defad;
    extern AstroGetValues* Agv;
    if (!Asq->Login(dbname, username, password, hostname))
    {
        err = Asq->Error();
				 AstroMessage(Sprintf(QT_TRANSLATE_NOOP("nc", "Login failed ! The returned message is :\n%a\nMaybe you don't have installed the database ?\nRun skydmin before using skylendar"), &as, &err));
				 return false;
    }
#ifdef IFEXCEPT
    AstroRequest Arq;
    Arq.SetException(true);
    try
    {
#endif
        Arq.Exec("SELECT idx FROM Data WHERE Name = 'ZeroGMT'");
        Arq.Exec("SELECT v FROM Version");
        as = QT_TRANSLATE_NOOP("nc", "The Database doesn't seem to be up-to-date. Make the upgrade with Skydmin.");
        if(Arq.GetDouble("v") != VERSIONB) throw AstroException(DbException, as);
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        Exception(ae);
        return false;
    }
#endif
    Arq.SetException(false);
    Arq.Exec("SELECT V FROM Version");
    if(!Arq.Valid() || Arq.GetDouble("V") < VERSIONB)
    {
        AstroMessage(QT_TRANSLATE_NOOP("nc", "Please, upgrade the database with Skydmin."), true);
        exit(3);
    }
    Asr->LoadStars();
    if (ap) Asp->Progress(20);
    Awm = new AstroWorldMap;
    if (ap) Asp->Progress(30);
    Asr->SetDefZFile();
    Asg = new AstroSigns;
    Asr->InitExtraNames();
    Asr->LoadParts();
    if (ap) Asp->Progress(40);
    //Asr-> LoadParts();
    Asr->LoadInterpl();
    Arl = new AstroRestrictionsList;
    Asf = CreateInterface();
    if (!Asf)
    {
        AstroMessage(QT_TRANSLATE_NOOP("nc", "Can't access skyservice"));
        qApp->exit(1);
    }
    if (Asf->GetVersion() + 0.00001 < SKYSERVICE_VERSION)
    {
        AstroString as;
        AstroMessage(Sprintf(QT_TRANSLATE_NOOP("nc", "Version of skyservice < %f"), &as, SKYSERVICE_VERSION));
        qApp->exit(1);
    }
    if (ap) Asp->Progress(50);
    Atl = new AstroTzList;
    Adl = new AstroDataList;
    Ahl = new AstroChartList;
    if (ap) Asp->Progress(70);
    Ail = new AstroIconsList;
    if (ap) ap->ProcessArgs();
    if (ap) Asp->Progress(80);
    defad = Now;
    Amw = new AstroMainWindow();
    Amw->AddChart(defad);
    if (ap) Asp->Progress(90);
    Agv = new AstroGetValues;
    return true;
}

API int Skylendar(int argc, char *argv[])
{
    AstroApp ap(argc, argv);
    return EXIT_SUCCESS;
}
