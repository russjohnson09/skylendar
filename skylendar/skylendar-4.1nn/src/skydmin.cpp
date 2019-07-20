/***************************************************************************
                          skydmin.cpp  -  description
                             -------------------
    begin                : Fri Jan 23 2009
    copyright            : (C) 2009 by Christophe Gros
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
#include <QApplication>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QModelIndex>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDir>
#include <QStandardPaths>
#include <QTranslator> 
#include "skydmin.h"
#include "ui_password.h"
#include "ui_asteroid.h"
#include "../config.h"
#include <cstdio>
#include <unistd.h>
#ifdef __WINNT
#include "../config.h"
#include <QSettings>
#include <windows.h>
#include <winnetwk.h>
#include <lm.h>
#include <wchar.h>
#else
#include <pwd.h>
#endif
#define SKYSITE QString("https://skylendar.sourceforge.io")

#define UN(f) d.remove(f)

const char * const Nb[] = {"00", "06", "12", "18", "24", "30", "36", "42", "48", "54"};

const struct
{
    const char *name;
    int a, b;
} Se[] =
{
    { "seas_", 0, 8 },
    { "seasm", 1, 9 },
    { "semo_", 0, 8 },
    { "semom", 1, 9 },
    { "sepl_", 0, 8 },
    { "seplm", 1, 9 }
};

QString i18n2(const char *index, const char* fallback)
{
	return QCoreApplication::translate("QObject", index, fallback);
}

class GetPassword: public QDialog, public Ui_GetPassword
{
public:
    GetPassword() {
        setupUi(this);
    }
};

class GetAsteroid: public QDialog, public Ui_Asteroids
{
public:
    GetAsteroid() {
        setupUi(this);
    }
};

SkyDmin::SkyDmin()
{
    setupUi(this);
    T = 0;
    R = -1;
    Manager = 0;
    Logged = false;
	
#ifdef __WINNT
		Hostname->setText("127.0.0.1");
		QSettings settings(QString("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Skylendar\\skylendar ") + VERSION, QSettings::NativeFormat);
		Path = settings.value("Default").toString().replace("\\", "/") + "/data";
#else
		Path = SKYPATH;
#endif

}

void SkyDmin::on_tabWidget_currentChanged(int i)
{
    T = i - 1;
}

bool SkyDmin::run(const QString& qs, const QStringList& arg)
{
    Qp.start(qs, arg);
    if(!Qp.waitForFinished()) { Install->append(tr("Can't run %").arg(qs)); return false; }
    Install->append(Qp.readAllStandardError());
	return true;
}

bool SkyDmin::Connect(const QString& s)
{
    db.setDatabaseName(DbName->text().isEmpty() ? s : DbName->text());
    db.setUserName("postgres");
    db.setHostName(Hostname->text());
    db.setPassword(Password->text());
    if (!db.open())
    {
        QMessageBox::critical(0, tr("Skydmin Error Message"), db.lastError().text());
        return(false);
    }
    return(true);
}

void SkyDmin::on_LoginButton_clicked()
{
    if (!Connect("skylendar"))
    {
        Install->append(tr("Problem! Can't login."));
        return;
    }
    Logged = true;
    Fill();
    QSqlQuery qq;
    qq.exec("SELECT V FROM Version");
    qq.first();
    if(!qq.isValid() || qq.value(0).toDouble() != VERSIONB)
        Install->append(tr("Oops ! The installation doesn't seem to be complete. Please check above."));
}

static bool Qu(const QString& s, const QSqlField& f, const QString& s1 = "")
{
    QSqlQuery qq;
    QString a = (s1 != "") ? s.arg(f.value().toString()).arg(s1) : s.arg(f.value().toString());
    if (s1 != "")
        return qq.exec(s.arg(f.value().toString()).arg(s1));
    return qq.exec(s.arg(f.value().toString()));
}

void SkyDmin::UpdateAccess(int row, QSqlRecord& r)
{
    const QSqlRecord& rec = Tbm[0]->record(row);
    QSqlQuery qq;
    QString qs;
    if (r.field(1).value().toBool())
    {
        QString n = tr("You may set a password to the database user '%1'");
        GetPassword gc;
        gc.Notice->setText(n.arg(rec.field(0).value().toString()));
        if (gc.exec() == QDialog::Accepted)
        {
            if (gc.Password->text() != gc.Password_1->text())
            {
                QMessageBox::critical(0, tr("Skydmin Error Message"), "Both passwords don't match!");
                return;
            }
            if (gc.Password->text() != "")
                Qu("CREATE USER %1 PASSWORD '%2'", rec.field(0), gc.Password->text());
            else
                Qu("CREATE USER %1", rec.field(0));
            Qu("ALTER GROUP skyusers ADD USER %1", rec.field(0));
        }
    }
    else
    {
        Qu("ALTER GROUP skyusers DROP USER %1", rec.field(0));
        Qu("DROP USER %1", rec.field(0));
    }

}

void SkyDmin::Clicked(const QModelIndex& m)
{
    R = m.row();
}

void SkyDmin::on_Insert_clicked()
{
    QSqlRecord r;
    if (T == 2)
    {
        QSqlField qf("Idx");
        QSqlQuery qq("SELECT NEXTVAL('TypeIcons_Idx_Seq')");
        int i = qq.value(0).toInt();
        qf.setValue(i);
        r.append(qf);
    }
    if (T > 0)
    {
        Tbm[T]->insertRecord(Tbm[T]->rowCount(), r);
    }
}

void SkyDmin::on_Delete_clicked()
{
    if (T > 0 && R > -1)
    {
        Tbm[T]->removeRows(R, 1);
    }
}

void SkyDmin::on_InstallButton_clicked()
{
    QString s, ins;
    if (QMessageBox::question (0, tr("Skydmin question"), tr("Do you want to install the skylendar database ?"), QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) return;
    Install->clear();
    if (!Connect("template1")) { Install->append(tr("Can't connect to databse %").arg("template1")); return; }
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QSqlQuery qq("CREATE DATABASE Skylendar ENCODING='UTF8' TEMPLATE template0");
    Install->append(qq.lastError().text());
    db.close();
    if (!Connect("skylendar")) { Install->append(tr("Can't connect to %").arg("skylendar")); QApplication:: restoreOverrideCursor(); return; };
    Path.replace("\\", "/");
    s = "CREATE VIEW Path AS (SELECT text E'%1' AS Path)";
    qq.exec(s.arg(Path));
    Install->append(qq.lastError().text());
    ins = Path + "/installskydb.sql";
#ifdef __WINNT
    SetEnvironmentVariableA("PGPASSWORD", Password->text().toUtf8().data());
#else
    setenv("PGPASSWORD", Password->text().toUtf8().data(), 1);
#endif
    if(!run("psql", QStringList() << "-f" << ins << "-d" << "skylendar" << "-U" << "postgres")) { QApplication:: restoreOverrideCursor(); return;}
    Fill();
    qq.exec("SELECT V FROM Version");
    qq.first();
    if(!qq.isValid() || qq.value(0).toDouble() != VERSIONB)
        Install->append(tr("Oops ! The installation doesn't seem to be complete. Please check above."));
    else
        Install->append(tr("<b>Installation finished !</b><br><br>Now, click on the <i>Accesses</i> tab.<br>Then, set to 'True' the wanted user's access and press <i>Ok</i> below, when finished.<br>Then, you can give a password to the selected database users."));
    QApplication:: restoreOverrideCursor();
}

void SkyDmin::on_UninstallButton_clicked()
{
    if (QMessageBox::question (0, tr("Skydmin question"), tr("Do you want to uninstall the skylendar database ?"), QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) return;
    Install->clear();
    if (!Connect("template1")) { Install->append(tr("Can't connect to %").arg("template1")); return; };
    QSqlQuery qq("DROP DATABASE Skylendar");
    Install->append(qq.lastError().text());
    qq.exec("DROP Role SkyUsers");
    Install->append(qq.lastError().text());
    Install->append(tr("<b>Uninstallation finished !</b>"));
    db.close();
}

void SkyDmin::on_DeleteSources_clicked()
{
    if (QMessageBox::question (0, tr("Skydmin question"), tr("Do you want to delete the database sources files ?"), QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) return;
#ifndef __WINNT
    uid_t u = geteuid();
    seteuid(0);
#endif
    QDir d(Path);
    UN("Country.txt");
    UN("D1901.txt");
    UN("Degrees.txt");
    UN("ExtraObjs.txt");
    UN("installskydb.sql");
    UN("Parts.txt");
    UN("Place.txt");
    UN("Tarots.txt");
    UN("Interpret.txt");
    UN("Intertarots.txt");
    UN("ConsNames.txt");
    UN("Boundaries.txt");
    UN("Stars.txt");
#ifndef __WINNT
    seteuid(u);
#endif
}

void SkyDmin::on_DownloadSe1_clicked()
{
    if (QMessageBox::question (0, tr("Skydmin question"), tr("Do you want to download the missing ephemeris files ?"), QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) return;
    Install->clear();
    if (SePath == "" && !LoadSePath()) return;
#ifndef __WINNT
    uid_t u = geteuid();
    seteuid(0);
#endif
    for (int i = 0; i <= 6; i++)
        for (int j = Se[i].a; j <= Se[i].b; j++)
        {
            QString s = Se[i].name;
            s += Nb[j];
            s += ".se1";
            LoadSe1(s);
        }
    QSqlQuery qq;
    qq.exec(QString("SELECT Idx from ExtraObjs WHERE Asteroid = 't'"));
    qq.next();
    do
    {
        int idx = qq.value(0).toInt();
        const QString name = SeName(idx);
        const QFile f(Path + "/" + name);
        qDebug() << f.fileName();
        if (!f.exists())
        {
            Install->append(tr("%1 not present. Try to download it").arg(name));
            LoadSe1(name, QString("ast%1/").arg(idx / 1000));
        }
        else
            Install->append(tr("%1 present.").arg(name));
    } while (qq.next());
    Install->append(tr("finished"));
#ifndef __WINNT
    seteuid(u);
#endif
}

QString SkyDmin::SeName(int idx) const
{
    QString sid, prefix = idx < 100000 ? "se" : "s";
    if (idx < 10000) sid =    "0";
    if (idx < 1000)  sid =   "00";
    if (idx < 100)   sid =  "000";
    if (idx < 10)    sid = "0000";
    return QString("%1%2.se1").arg(prefix).arg(sid + QString().setNum(idx));
}

void SkyDmin::on_DownloadAster_clicked()
{

}

void SkyDmin::Progress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (bytesTotal && ((bytesReceived * 100) / bytesTotal > P))
    {
        P = (bytesReceived * 100) / bytesTotal;
        Install->insertPlainText(".");
    }
}

bool SkyDmin::LoadSePath()
{
        SePath ="http://www.astro.com/ftp/swisseph/ephe/";
				return true;
}

void SkyDmin::LoadSe1(const QString& qs, const QString& dir)
{
    P = 0;
    QDir d(Path);
    if (d.exists(qs))
    {
        Install->append(tr("%1 already exists").arg(qs.toLatin1().data()));
        return;
    }
    QNetworkRequest request;
    request.setUrl(QUrl(SePath + dir + qs));
    request.setRawHeader("User-Agent", USER_AGENT);
    QNetworkReply *reply = Manager->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(Progress(qint64, qint64)));
    Install->append("");
    Install->insertPlainText(tr("Loading %1 ").arg(qs));
    while (!reply->isFinished()) qApp->processEvents(QEventLoop::WaitForMoreEvents, 500);
    if (reply->error() != QNetworkReply::NoError)
    {
        Install->append(tr("<b>Download Error %1</b>").arg(reply->error()));
        delete reply;
        return;
    }
    Install->append("");
    QFile f(Path + "/" + qs);
    if (!f.open(QIODevice::WriteOnly))
    {
        Install->append(tr("<b>Write Error</b>"));
        delete reply;
        return;
    }
    f.write(reply->read(reply->size()));
    f.close();
    delete reply;
}

void SkyDmin::Fill()
{
    struct passwd *pw ;
    QSqlQuery qq;
    Accesses->setEnabled(true);
    ExtraObjs->setEnabled(true);
    TypeIcons->setEnabled(true);
    Parts->setEnabled(true);
    if (!qq.exec("CREATE TEMP TABLE Users (Name VARCHAR UNIQUE, B Boolean)"))
    {
        QMessageBox::warning(0, tr("Skydmin Error Message"), db.lastError().text());
        return;
    }
#ifdef __WINNT
    NET_API_STATUS nStatus;
    LPUSER_INFO_1 Userbuf_1 = NULL, Userbuf_2 = NULL;
    DWORD entriesread = 0, totalentries = 0, resume_handle = 0;
    DWORD Level = 1, n = 0;
    mbstate_t ps;
    char buf[100];
    do
    {
        nStatus=NetUserEnum(0, Level, FILTER_NORMAL_ACCOUNT, (LPBYTE *)&Userbuf_1, MAX_PREFERRED_LENGTH, &entriesread, &totalentries, &resume_handle);
        if ((nStatus == NERR_Success)||(nStatus == ERROR_MORE_DATA))
        {
            if ((Userbuf_2 = Userbuf_1) != NULL)
            {
                for (n = 0; n < entriesread; n++)
                {
                    QString qs("INSERT INTO Users VALUES(LOWER('%1'), 'f')");
                    const WCHAR* wc = Userbuf_2->usri1_name;
                    wcsrtombs(buf, static_cast<const wchar_t**>(&wc), 100, &ps);
                    qq.exec(qs.arg(buf));
                    Userbuf_2++;
                }
            }
        }
        else
        {
            exit(1);
        }

        if (Userbuf_1)
            NetApiBufferFree(Userbuf_1);

    } while (nStatus == ERROR_MORE_DATA);
#else
    setpwent();
    while ((pw = getpwent()))
    {
        QString qs("INSERT INTO Users VALUES('%1', 'f')");
        qq.exec(qs.arg(pw->pw_name));
    }
    endpwent();
#endif
    qq.exec("UPDATE Users SET B = 't' WHERE Name IN (SELECT rolname FROM pg_authid, pg_auth_members WHERE member = oid AND roleid = (SELECT oid FROM pg_authid WHERE rolname = 'skyusers'))");
    Tbm[0] = new QSqlTableModel;
    Tbm[0]->setTable("users");
    Tbm[0]->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Tbm[0]->setHeaderData(0, Qt::Horizontal, tr("User"));
    Tbm[0]->setHeaderData(1, Qt::Horizontal, tr("Access"));
    Tbm[0]->select();
    Tbm[1] = new QSqlTableModel;
    Tbm[1]->setTable("extraobjs");
    Tbm[1]->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Tbm[1]->setHeaderData(0, Qt::Horizontal, tr("Idx"));
    Tbm[1]->setHeaderData(1, Qt::Horizontal, tr("Name"));
    Tbm[1]->setHeaderData(2, Qt::Horizontal, tr("Short Name"));
    Tbm[1]->setHeaderData(3, Qt::Horizontal, tr("Asteroid"));
    Tbm[1]->select();
    Tbm[2] = new QSqlTableModel;
    Tbm[2]->setTable("typeicons");
    Tbm[2]->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Tbm[2]->setHeaderData(0, Qt::Horizontal, tr("Idx"));
    Tbm[2]->setHeaderData(1, Qt::Horizontal, tr("Name"));
    Tbm[2]->setHeaderData(2, Qt::Horizontal, tr("Icon File"));
    Tbm[2]->select();
    Tbm[3] = new QSqlTableModel;
    Tbm[3]->setTable("parts");
    Tbm[3]->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Tbm[3]->setHeaderData(0, Qt::Horizontal, tr("Name"));
    Tbm[3]->setHeaderData(1, Qt::Horizontal, tr("P1"));
    Tbm[3]->setHeaderData(2, Qt::Horizontal, tr("P2"));
    Tbm[3]->setHeaderData(3, Qt::Horizontal, tr("P3"));
    Tbm[3]->setHeaderData(4, Qt::Horizontal, tr("Night"));
    Tbm[3]->setHeaderData(5, Qt::Horizontal, tr("Idx"));
    Tbm[3]->select();
		Tbm[4] = new QSqlTableModel;
    Tbm[4]->setTable("stars");
    Tbm[4]->setEditStrategy(QSqlTableModel::OnManualSubmit);
		Tbm[4]->setHeaderData(0, Qt::Horizontal, tr("Name"));
		Tbm[4]->setHeaderData(1, Qt::Horizontal, tr("Language"));
		Tbm[4]->setHeaderData(2, Qt::Horizontal, tr("Nomenclature"));
		Tbm[4]->setHeaderData(3, Qt::Horizontal, tr("Short Name"));
    Tbm[4]->select();
    Accesses->setModel(Tbm[0]);
    ExtraObjs->setModel(Tbm[1]);
    TypeIcons->setModel(Tbm[2]);
    Parts->setModel(Tbm[3]);
		Stars->setModel(Tbm [4]);
    connect(Tbm[0], SIGNAL(beforeUpdate( int, QSqlRecord&)), SLOT(UpdateAccess(int,QSqlRecord&)));
    connect(ExtraObjs, SIGNAL(pressed(const QModelIndex&)), SLOT(Clicked(const QModelIndex&)));
    connect(TypeIcons, SIGNAL(pressed(const QModelIndex&)), SLOT(Clicked(const QModelIndex&)));
    connect(Parts, SIGNAL(pressed(const QModelIndex&)), SLOT(Clicked(const QModelIndex&)));
		connect(Stars, SIGNAL(pressed(const QModelIndex&)), SLOT(Clicked(const QModelIndex&)));
		
}

int main(int argc, char **argv)
{
    QApplication Skydmin(argc, argv);
		QApplication::setApplicationName("Skydmin");
		QApplication::setOrganizationDomain("skylendar.org");
		QApplication::setApplicationVersion("4.04");
    QApplication::setWindowIcon(QIcon(":/icon.png"));
		QTranslator t;
		if(t.load("skydmin_" + QLocale::system().name(), QString(SKYPATH))) 
			Skydmin.installTranslator(&t);
    auto Sd = new SkyDmin;
    Sd->db = QSqlDatabase::addDatabase("QPSQL");
#ifdef __WINNT
    CHAR u[100];
    DWORD d;
    GetUserNameA (u, &d);
#else
    if (geteuid() != 0)
    {
			QMessageBox::critical(0, QT_TRANSLATE_NOOP("main", "Skydmin Error Message"),
#ifdef __WINNT
				QT_TRANSLATE_NOOP("main", "Skydmin must run with <b>Administrator</b> privileges !"));
#else
				QT_TRANSLATE_NOOP("main", "Skydmin must run with <b>ROOT</b> privileges !"));
#endif
        exit(1);
    }
#endif
    if (!Sd->db.isValid())
    {
			QMessageBox::critical(0, QT_TRANSLATE_NOOP("main", "Skydmin Error Message"), Sd->db.lastError().text());
        exit(1);
    }
#ifndef __WINNT
    struct passwd *pw ;
    setpwent();
    while ((pw = getpwent()))
        if (!strcmp(pw->pw_name, "postgres"))
        {
            seteuid(pw->pw_uid);
            break;
        }
    endpwent();
#endif
    if (Sd->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < 5; i++)
            Sd->Tbm[i]->submitAll();
    }
    Sd->db.close();
}
