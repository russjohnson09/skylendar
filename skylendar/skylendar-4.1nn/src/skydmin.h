/***************************************************************************
                          skydmin.h  -  description
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
#include "ui_skydmin.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QProcess>
#include <QNetworkReply>
#include <QFile>

class QSqlTableModel;
class QSqlRecord;
class QModelIndex;
class QStringList;
class QNetworkReply;
#define i18n(s) s
#define USER_AGENT "skylendar 4.0"

class SkyDmin: public QDialog, public Ui_Skydmin
{
    Q_OBJECT

public:

    SkyDmin();

    QSqlDatabase db;
    QSqlTableModel *Tbm[5];
    bool Connect(const QString& db);
	QString Path;

public slots:

    void on_tabWidget_currentChanged(int);
    void on_LoginButton_clicked();
    void on_Insert_clicked();
    void UpdateAccess(int, QSqlRecord&);
    void on_Delete_clicked();
    void on_InstallButton_clicked();
    void on_UninstallButton_clicked();
    void on_DeleteSources_clicked();
    void on_DownloadSe1_clicked();
    void on_DownloadAster_clicked();
    void Clicked(const QModelIndex&);
    void Progress(qint64 bytesReceived, qint64 bytesTotal);

private:

    QProcess Qp;
    void Fill();
    int T, R, P;
    bool Logged;
    bool run(const QString&, const QStringList&);
    bool LoadSePath();
    void LoadSe1(const QString&, const QString& dir = "");
    QString SeName(int idx) const;
    QString SePath;
    QNetworkAccessManager *Manager;
};
