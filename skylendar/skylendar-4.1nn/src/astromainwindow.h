/***************************************************************************
                          astromainwindow.h  -  description
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

#ifndef ASTROMAINWINDOW_H
#define  ASTROMAINWINDOW_H

#include "../config.h"
#include "astrostring.h"
#include "astrolist.h"
#include "astrowindow.h"

#ifdef QT
#include <QMainWindow>
#include <QDockWidget>
#include <QMdiArea>
#include <QAction>
#include <QToolBar>
class QMdiSubWindow;
class QActionGroup;
class QComboBox;
class QPrinter;
class QNetworkReply;
#endif

class AstroData;
class AstroIconsWindow;
class WindowsList;
class QNetworkAccessManager;
class QNetworkReply;

#define GROUP 0
#define SUBTYPE 1
#define RESTRICTION 2
#define NEWDATA 3
#define SEARCHDATA 4
#define ONR1 5
#define ONR2 6
#define ONR3 7
#define ONR4 8
#define ANIMOF 9
#define INVANIM 10
#define JBASE 11
#define JRATE 11
#define INVBG 12
#define MAJOR 13
#define SWORD 14
#define COIN  15
#define STICK 16
#define CUP   17
#define PREVIOUS 18
#define NEXT 19

#include "ui_about.h"
class AstroAbout : public QWidget, public Ui_About
{
  Q_OBJECT

 public:

 AstroAbout();
};

/** The application's main window */

class AstroMainWindow : public QMainWindow,
            public AstroList<AstroWindow>
{
    Q_OBJECT

public:

    /** Constructor
        @param ad the first data displayed (if any) in an AstroWindow
    */
    AstroMainWindow();
    ~AstroMainWindow();

    void AddChart(const AstroData* ad);

    /** Returns the active window */
    AstroWindow* ActiveWindow() const;

    friend class AstroWindow;
    friend class SearchData;
    friend class SearchRest;
    friend class AstroChartList;
    friend void WriteSKIF(const AstroString&, AstroData*);
    friend void ReadSKIF(const AstroString&);
		friend class AstroGraphicChart;

#ifdef QT

public slots:

    /** New chart */
    void NewData();

    /** Read SKIF file */
    void Read();

    /** Write SKIF file */
    void Write();

    /** Changes title of active chart */
    void SetOwnTitle();

    /** Search for data */
    void SearchForData();

    /** Search for restrictions sets */
    void SearchForRest();

    /** Search for a sotored chart */
    void SearchForChart();

    /** New restrictions set */
    void NewRestrictions();

    /** Creates a standard wheel chart */
    void StandardChart();

    /** Creates an object list chart */
    void ObjectListChart();

    /** Creates a text data list chart */
    void TextListChart();

    /** Creates a local horizon chart */
    void LocalHorizonChart();

    /** Creates an Aspects Table Chart */
    void AspectsTableChart();

    /** Create a Squared Chart */
    void SquaredChart();

    /** Creates a Solar System Chart */
    void SolarSystem();

    /** Creates a Tarots Spread Chart */
    void TarotsSpread();

    /** Edit current chart parameters */
    void EditParams();

    /** Edit the default parameters */
    void EditDefParms();

    /** Edits the countries database */
    void EditCountries();
    /** Exports active chart */
    void Export();

    /** Save current chart */
    void SaveChart();

    /** Quits the application */
    void Quit();

    /** Reorganize the chart windows as tiles */
    void Tile();

    /** Reorganize the chart windows in cascade */
    void Cascade();

    /** Edits the current data or restrictions set */
    void Edit();

    /** Deletes the current data or restriction set*/
    void Delete();

    /** Saves the current data or restrictions set into the db */
    void Save();

    /** Duplicate the current dagag.pngte or restriction set */
    void Duplicate();

    /** Duplicates the current window */
    void DupWindow();

    /** Displays the data tree if hidden */
    void DisplayDataTree();

    /** Duplicate the current window and perform the drop action */
    void DupnDrop(enum ButtonType, int);

    /** Prints the current window */
    void Print();

    /** Preview the current chart */
    void Preview();

    /** Closes the chart window */
    void Close(AstroWindow*);

    /** Manually increments the animation time */
    void Increment();

    /** Manually decrements the animation time */
    void Decrement();

    /** Slots for animation s */
    void AnimOnOff(bool);
    void InvAnim(bool);

    /** Inverse foreground/backgound*/
    void InvBackground(bool);

    /** display backgroup image */
    void BackImage(bool);

    /** previous text list section */
    void Previous();

    /** Next text list section */
    void Next();

    /** Sets the value of the X point */
    void SetX();

    void About();

    void Doc();

    void Finished(QNetworkReply*);

    void Jr(QAction*);
		void Jr(int);
    void Jb(QAction*);
		void Jb(int);

    void WinListSlot(QAction*);

protected:

    void SetupActions();

private slots:

    void WindowActivated(QMdiSubWindow*);
    void Triggered (QAction*);
		void PaintPreview(QPrinter*);

#endif

private:

    int Ring = 1, CountWindows = 0;
    AstroIconsWindow* Aiw;
#ifdef QT
		QAction *quit, *print, *preview, *saveopt, *prefs, *open, *save, *searchdata, *searchrest, *editcountries, *datatree, *prevblock, *nextblock, *standardchart, *textlistchart, *objectlistchart, *localhorizonchart, *aspecttablechart, *squaredchart, *solarsystem, *tarotspread, *editparams, *dupwindow, *exportchart, *setowntitle, *setx, *savechart, *searchforchart, *increment, *decrement, *invbackground, *backimage, *newdata, *newrestrictions, *write, *edit, *deletedata, *duplicate, *tile, *cascade, *onoffanim, *animinv, *onr1, *onr2, *onr3, *onr4, *doc, *about;
		QToolBar *Tb;
    QActionGroup *Qar, *winlist, *JrPm, *JbPm, *Rin;
		QMenu *m, *File, *View, *Chart, *Data, *Windows, *Animations, *Help;
		QAction* Men(QString str, const char *slot, const QKeySequence& ks = QKeySequence(QKeySequence::UnknownKey), enum QStyle::StandardPixmap pm = QStyle::SP_TitleBarMenuButton);
		QAction* Men(QString str, const char *slot, const QIcon& c, const QKeySequence& ks = QKeySequence(QKeySequence::UnknownKey));
		QAction* Menc(QString str, const char *slot, const QKeySequence& ks = QKeySequence(QKeySequence::UnknownKey), enum QStyle::StandardPixmap pm = QStyle::SP_TitleBarMenuButton);
		QAction* Menc(QString str, const char *slot, const QIcon& c, const QKeySequence& ks = QKeySequence(QKeySequence::UnknownKey));
    WindowsList* Wl;
    QDockWidget* DockLeft;
#endif
    /** Edit a data */
    void EditData();

    void EditRestr();

    void DeleteData();

    void DeleteRestr();

    void DupWindow(enum ChartType);

    void UpdateCharts(Index idx, bool data);

    void AddWindow(const AstroWindow*);
    void RemWindow(const AstroWindow*);
    void ChangeWindow(const AstroWindow*, const QString& newname);
    void CheckWindow(const AstroWindow* aw) const;
    void NewChart(enum ChartType ct);
    const AstroString& RenameWindow(AstroString&);

#ifdef QT
    void closeEvent(QCloseEvent*);
    QComboBox *JumpBase, *JumpRate;
    QMdiArea* QMa;
    void customEvent(QEvent*);
    QNetworkAccessManager* QNam;
    QNetworkReply* QNr;
#endif
};

#endif
