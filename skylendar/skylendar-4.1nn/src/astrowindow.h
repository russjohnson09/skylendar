/***************************************************************************
                          astrowindow.h  -  description
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

#ifndef ASTROWINDOW_H
#define ASTROWINDOW_H

#include "../config.h"
#define QT
#include "astrochart.h"
#include "astrographics.h"
#include "astrodata.h"
#include "astroregexp.h"

#ifdef QT
#include <QCloseEvent>
#include <QDropEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDragEnterEvent>
#include <QMdiSubWindow>
#include <QMenu>
#include <QTreeWidget>

class QPainter;
class QPicture;
class QPrinter;
class QTimer;
class QPaintEvent;
class QMouseEvent;
class QCloseEvent;
class QKeyEvent;
class QActionGroup;
class QScrollArea;
#endif

class AstroInterface;
class AstroMainWindow;
class AstroRestrictions;
class AstroPrintPage;
class AstroIconsWindow;
class MyScrollArea;

enum ButtonType { Undefined_Button, DataButton, RestrictButton, TypeButton, SubTypeButton, MajorButton, SwordButton, CoinButton, StickButton, CupButton };

/** A portable Icon class */
class AstroIcon: public AstroPixmap
{

public:

    /** Contructor */
    AstroIcon(AstroString& name) {
        Name = name;
    }
    inline AstroIcon(const AstroString& file, const AstroString& name) : AstroPixmap(file) {
        Name = name;
    }

    // Icon name
    AstroString Name;
};

/** A list of icons */
class AstroIconsList: public AstroList<AstroIcon>
{
 
	Q_DECLARE_TR_FUNCTIONS(AstroIconsList)

public:

    /** Constructor */
    AstroIconsList();
    const AstroString& GetName(unsigned int idx);
    int GetSpecIcon(enum AspKind ak) const;

private:

    int SpecIconsId[8];
};

#ifdef QT

class AstroGraphicChart;

/** this class has been designed just in order to manage the page
	change with headers and footers
*/
class AstroPrintPage: public QObject
{
    Q_OBJECT
public:

    /** Constructor */
    AstroPrintPage(AstroString& title, AstroChartBase* acb, AstroGraphicChart* agc, int height);
    /** Destructor */
    ~AstroPrintPage();

    /** Dispays a header */
    void Header();
    /** Displays a footer */
    void Footer(bool ifpage = true);

public slots:
    void NewPage();

private:

    AstroChartBase* Acb;
    AstroGraphicChart* Agc;
    int Page, Height;
    AstroString Title;
};
#endif

/** This class is the standard class for the graphical charts (that can be displayed in a window) */
class AstroGraphicChart: public QWidget, public AstroGraphics, public AstroChart
{
public:

    friend class AstroPrintPage;
		friend class AstroMainWindow;

    enum DisplayMode { GraphicMode, DblBufMode, PrintMode, PreviewMode, SVGMode };

    /** Constructors
     @param width the charts's width
     @param height the chart's height
    */
    AstroGraphicChart(int width, int height);

    ~AstroGraphicChart();

    /** the overloaded Repaint() method */
    void Repaint(bool b = false);

    /** Sets the chart's background color */
    void BackgroundColor();

    /** Select the display mode, graphic, anim or printing mode */
    void SetDisplayMode(enum DisplayMode);

    /** Invoked when printing or window resizing
        @param x new width
        @param y new height
    */
    inline void Resize(int x, int y) {
        SetWidth(x);
        SetHeight(y);
        Size = AstroGraphics::Width/ 48;
    }

		
		/** Save in a SVG file */
        bool SaveSVG(const AstroString &file);

protected:

    int OrigWidth, OrigHeight;

    enum DisplayMode Dm;
    void PrinterSize(int&w, int &h, int& mx, int& my, int& ph);
    void ResizeView(int w, int h);

#ifdef QT
    QPicture* QPict;
    QPrinter* Qprint;
#endif

private:
    AstroPrintPage* App;
    void PreRedraw(bool b);
    void PostRedraw();
		int W, H;
};

/** This class manages the  window in which a chart is displayed */
class AstroWindow: public AstroGraphicChart
{
    Q_OBJECT

public:

    friend class AstroMainWindow;
    friend class MyScrollArea;

    /** Constructor
    @param ad1 the first data for the chart
    @param ad2 ad3 ad4 possible 2nd 3rd and 4th data for the chart
    */
    AstroWindow(const AstroMainWindow*, AstroData* ad1, enum ChartType ect = StdWheels, AstroData* ad2 = 0, AstroData* ad3 = 0, AstroData* ad4 = 0);

    AstroWindow(const AstroMainWindow* amw, const AstroChart& ac, enum ChartType ect = StdWheels);

    /** Creates an astrowindow from an Chart Idx
    @param idx the chart's database idx */
    AstroWindow(const AstroMainWindow* amw, Index idx);

    /** Destructor */
    ~AstroWindow();

    enum JumpBaseType { Seconds, Minutes, Hours, Days, Months, Years, Centuries, Millenia };

    /** The overloded Repaint method */
    void Repaint(bool b = false);

		void BackgroundColor();

    /** Displays a chart params dialog box */
    inline bool EditParms() {
        return EditChartParams();
    }

    /** Start or stop the animation */
    void Anim(bool start);

    // Used by anims
    int Day = 0, Month = 0, Year = 0, Hour = 0, Minute = 1, Second = 0, Rate = 1;

    // If anim runs backward
    bool IfAnim = false, Backward = false;

    // Type of anim jump
    enum JumpBaseType Jbt = Minutes;

    /** Locks the chart */
    virtual bool LockChart();

    /** Unlocks the chart */
    virtual void UnlockChart();

    /** Is chart locked ? */
    inline bool IsLocked() const {
        return Acb->Running;
    }

    /** Returns the window's tilte */
    inline const AstroString GetCurTitle() const {
        return Qsw->windowTitle();
    }

    AstroIconsWindow& Aiw() const;

private:

    void Setup(const AstroMainWindow* amw);
    void ManageTypes(int i);
    void ManageSubTypes(int i);
    void ManageTarots(enum TarotTypes tt, int i, int x, int y);
    void SetJbt(enum JumpBaseType);
    void SetRate(int r);
    void SetPm(enum ChartType cti);
    int GetRing() const;
    void AddData(const AstroString& name, enum AspKind ak, const AstroObjs& ao, const DataLineBase* dl, bool ifephem = false, double latitude = 0.0, double longitude = 0.0);

#ifdef QT
    QTimer* QTim = nullptr;
    QMenu *ParamPm, *SubringPm;
    QActionGroup *Qag, *Qag1;
    MyScrollArea* Qsa;
    QMdiSubWindow* Qsw;
    AstroRegExp Art;
    bool NoResize = false;
    float WinRatio;

    void DropAction(enum ButtonType, int i, int x, int y);
    void mousePressEvent(QMouseEvent* e);
    void resizeEvent(QResizeEvent*);
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void paintEvent(QPaintEvent * event);
    void closeEvent(QCloseEvent*);

#endif
    int MilliSec = 1000, Ring = 1;

    // The window's width and height
    int Width, Height, Oy = 0, Ox = 0, H = 0;

#ifdef QT

signals:

    void Close(AstroWindow *);
    void DupnDrop(enum ButtonType, int);

private slots:

    void TimerSlot();
    void Activated(QAction*);
#endif
};

/** The lateral windows diplaying the icons tree */
class AstroIconsWindow:
            public QTreeWidget
{
    Q_OBJECT

public:

    friend class AstroMainWindow;
    friend class AstroWindow;
    friend void WriteSKIF(const AstroString&, AstroData*);

    /** A class for the icon buttons */
    class AstroIconButton
#ifdef QT
                : public QTreeWidgetItem
#endif
    {
    public:

        /** Constructor
            @param index, ith button of the corresponding subtype branch of the tree
            @param bt subtype branch of the tree
            @param after if not null, create icon button after 'after'
        */
        AstroIconButton(AstroIconsWindow*, int index, ButtonType bt = SubTypeButton);

        /** Constructor that adds a data icon */
        AstroIconButton(AstroIconsWindow*, const AstroData* ad);

        AstroIconButton(AstroIconsWindow*, const AstroRestrictions* ar);

        // index database (if any) of the data
        Index Idx;

        // Type of button
        ButtonType Bt;

    private:

        QTreeWidgetItem* GetParent(const AstroIconsWindow& aiw, ButtonType bt) const;
    };

    /** Constructor */
    AstroIconsWindow(AstroMainWindow*);

    /** Destructor */
    ~AstroIconsWindow() {
        delete DataPm;
        delete RestPm;
    }

    /** Returns the data of the clicked icon */
    inline AstroData* GetData() const {
        return Adl->Get(Idx);
    }

    /** Returns the restrictions set of the clicked icon */
    inline AstroRestrictions* GetRestrictions() const {
        return Arl->Get(Idx);
    }

    /** Adds a new data icon */
    void AddData(const AstroData*);

    /** Adds a new restrictions set icon */
    void AddRestrict(const AstroRestrictions*);

    /** Delete the clicked data icon and value */
    void DeleteCurrent();

    /*** tries to delete the AstroData whose the index is idx
    @return true if success*/
    bool DeleteIdx(Index idx);

    /** Changes the data of the clicked icon data */
    void ChangeCurrent(const AstroData* ad);

    /** Changes the data of the clicked icon restrictions set */
    void ChangeCurrent(const AstroRestrictions* ar);

    /** Search for the Data Button having Idx idx. Returns 0 otherwise */
    AstroIconButton* GetDataButton(Index idx) const;

    /** Changes the data Idx everywhere where needed */
    void UpdateDataIdx(Index oldidx, Index newidx);

private:

#ifdef QT
    QTreeWidgetItem *Data, *Restrictions, *Types, *SubTypes, *Tarots, *Major, *Sword, *Coin, *Stick, *Cup;
    QPixmap* qpm;
    QMenu *DataPm, *RestPm;
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);
    QPoint DragPos;
#endif

    // Active button + array for the subtypes icon buttons
    AstroIconButton *Aib;
    Index Idx;
    bool IsPressed;
    int X, Y;

#ifdef QT
private slots:

    void Pressed(QTreeWidgetItem*, int);
    void Clicked(QTreeWidgetItem*, int);
    void DoubleClicked(QTreeWidgetItem *, int);
    void Triggered(QAction*);
#endif
};

#endif



