#include "astrospot.h"
#include "astroobjs.h"
#include "astrographics.h"
#include <QPainter>
#include <QPen>

AstroSpot::AstroSpot(QWidget* parent, AstroGraphics* ag, const AstroObjs& a, enum Objs o, int x, int y, int size, const AstroColor& ac): QWidget(parent), AstroGraphics(ag, x, y)
{
	C = a.GetObjChar(o);
	A = &CSC(AstroObjs&, a);
	O = o;
	X = x;
	Y = y;
	Sc = (enum AstroGraphics::SizeChars)size;
	Col = &CSC(AstroColor&, ac);
	move(x, y);
	FontSize(Sc, C);
	if(C)
		GlyphMetrics(C, &W, &H);
	else
		TextMetrics((*A) < O, &W, &H);
	resize(W, H);
	SetWidth(W);
	SetHeight(H);
    setWindowOpacity(0.0);
	setContentsMargins(0, 0, 0, 0);
	setMouseTracking(true);
    AstroString cap = Asr->GetInterp(O);
    if(!cap.isEmpty()) cap = "<br>" + cap;
	if(C)
        setToolTip("<span style=\"background:yellow;color:black\"><font face=\"skylendar\", size=20>" + QString(C) + "</font>&nbsp;" + QString(((*A) << O)) + QString(cap) + QString("</span>"));
	else
        setToolTip("<span style=\"background:yellow;color:black\"><font size=20>" + QString(((*A) < O)) + QString("</font>&nbsp;") + QString(((*A) << O)) + QString(cap) + QString("</span>"));
	setToolTipDuration(10000);
	raise();
	///setAutoFillBackground(true);
    //setAttribute(Qt::WA_DeleteOnClose);
	show();
}

AstroSpot::AstroSpot(QWidget* parent, AstroGraphics* ag, enum Signs s, int x, int y, int size, const AstroColor& ac): QWidget(parent), AstroGraphics(ag, x, y)
{
    X = x;
    Y = y;
    Sc = (enum AstroGraphics::SizeChars)size;
    Col = &CSC(AstroColor&, ac);
    move(x, y);
    C = Asg->GetChar(s, *Cpr);
    FontSize(Sc, C);
    GlyphMetrics(C, &W, &H);
    resize(W, H);
    SetWidth(W);
    SetHeight(H);
    setWindowOpacity(0.0);
    setContentsMargins(0, 0, 0, 0);
    setMouseTracking(true);
    AstroString cap = Asr->GetInterp(s + 2000);
    if(!cap.isEmpty()) cap = "<br>" + cap;
    setToolTip("<span style=\"background:yellow;color:black\"><font face=\"skylendar\", size=20>" + QString(C) + "</font>&nbsp;" + QString((*Asg) << s) + QString(cap) + QString("</span>"));
    setToolTipDuration(10000);
    raise();
    //setAttribute(Qt::WA_DeleteOnClose);
    show();
}

void AstroSpot::paintEvent(QPaintEvent *e)
{
    QPainter p(this), *pptr = Qp;
	Qp = &p;
	p.setPen(*Pen);
	PosX = PosY = 0;
	Color(*Col);
	FontSize(Sc, C);
	if(C)
	{

        AstroGraphics::Move(0, 6 * H  / 7);
		Glyph(C);
	}
	else
	{
        AstroGraphics::Move(0, H);//2 * H / 3);
		Text((*A) < O);
	}
    Fore();
//    Qp->drawLine(0, 0, width()-1, 0);
//    Qp->drawLine(width()-1, 0, width()-1, height()-1);
//    Qp->drawLine(width()-1, height()-1, 0, height()-1);
//    Qp->drawLine(0, height()-1, 0, 0);
    Qp = pptr;
	p.end();
}

void AstroSpot::RePos(int x, int y, int size)
{
    //if(Size != Base->GetSize())
    //{
        QPainter *pptr = Qp;
        Qp = Base->Qp;
        if(Size != Base->GetSize()) Size = Base->GetSize();
        Sc = (enum AstroGraphics::SizeChars)size;
        FontSize(Sc, C);
        if(C)
            GlyphMetrics(C, &W, &H);
        else
            TextMetrics((*A) < O, &W, &H);
        SetWidth(W);
        SetHeight(H);
        resize(W, H);
        Qp = pptr;
    //}
    move(x, y); show();
}
