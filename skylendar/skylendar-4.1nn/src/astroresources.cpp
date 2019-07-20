/***************************************************************************
                          Astroresources.cpp  -  description
                             -------------------
    begin                : Mon Oct 9 2000
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
#include "astroresources.h"
#include "astroutils.h"
#include "astrowindow.h"
#include "astrointerface.h"
#include "scanspan.h"
#include "astroapp.h"
#include "astrosplash.h"
#include "astrograph.h"
#include "tzlist.h"
#include "astromainwindow.h"
#include "astrogetvalues.h"
#include "astroprocess.h"
#include <cstdarg>
#ifdef QT
#include <QSpinBox>
#include <QRadioButton>
#include <QApplication>
#include <QMultiHash>
#include <QPainterPath>
#include <QDir>
#include "astrogetvaluesadaptor.h"
#endif

#include <cstdlib>
#include <iostream>

#ifndef __WINNT
extern "C"
{
#include <langinfo.h>
};
#endif
#undef i18n
#undef i18n2
#ifdef LAN_CONTEXT
# define i18n(s) new AstroString(tr(s))
# define i18n2(s, f) new AstroString(tr(s, f))
#else
# define i18n(s) new AstroString(Translate(s))
# define i18n2(s, f) new AstroString(i18n2(s, f))
#endif
static AstroString* Null = new AstroString;

typedef AstroString* Aptr;

int NbStars = 0, Final_Star = First_Star-1;

// The global AstroSigns Signs definitions object pointer
class AstroSign;
AstroSigns* Asg;

// The global AstroResources object pointer;
AstroResources* Asr;

// The global AstroData list
class AstroDataList;
AstroDataList* Adl;

// The global AstroChart list
class AstroChartList;
AstroChartList* Ahl;

// The Chart icons list
class AstroIconsList;
AstroIconsList* Ail;

//The global colors list
class AstroColorList;
AstroColorList* Acl;

// The global restrictions list
class AstroRestrictionsList;
AstroRestrictionsList* Arl;

// The standard interface object for non-reentrant routines
AstroInterface* Asf;

// The main window pointer
class AstroMainWindow;
AstroMainWindow* Amw = 0;

// The global "Now" data
class AstroData;
AstroData* Now;

// The global default restrictions set
class AstroRestrictions;
AstroRestrictions* Drs;

// The SQL access point
class AstroSQL;
AstroSQL* Asq;

// The world map pointer
class AstroWorldMap;
AstroWorldMap* Awm;

class AstroGetValues;
AstroGetValues* Agv;

// The AstroTzList pointer
AstroTzList* Atl;

AstroSplash* Asp;

AstroResources::AstroResources()
{
    QFont qf(TEXTFONT);
    Load();
    LoadCount = TaCount = 0;
// Initialisation of the various used constants
    fill(DayNames, i18n("Monday"), i18n("Tuesday"), i18n("Wednesday"), i18n("Thusrday"),
         i18n("Friday"), i18n("Saturday"), i18n("Sunday"), nullptr);

    fill(DayShortNames, i18n2("Mon", "day"), i18n2("Tue", "day"), i18n2("Wed", "day"),
         i18n2("Thu", "day"), i18n2("Fri", "day"), i18n2("Sat", "day"),
         i18n2("Sun", "day"), nullptr);

    fill(MonthNames, i18n("January"),  i18n("February"),  i18n("March"),  i18n("April"),
         i18n("May"),  i18n("June"),  i18n("July"),  i18n("August"),  i18n("September"),
         i18n("October"),  i18n("November"),  i18n("December"), nullptr);

    fill(MonthShortNames, i18n2("Jan", "mon"), i18n2("Feb", "mon"), i18n2("Mar", "mon"),
         i18n2("Apr", "mon"), i18n2("May", "mon"), i18n2("Jun", "mon"),
         i18n2("Jul", "mon"), i18n2("Aug", "mon"), i18n2("Sep", "mon"),
         i18n2("Oct", "mon"), i18n2("Nov", "mon"), i18n2("Dec", "mon"), nullptr);

    fill(HousesSystemNames, i18n("Placidus"),  i18n("Koch"), i18n("Porphyrius"),
         i18n("Regiomontanus"), i18n("Campanus"), i18n("Equal"), i18n("Vehlow"),
         i18n( "Meridian"), i18n("Azimuthal"), i18n("Topocentric"), i18n( "Alcabitus"), i18n("Morinus"), i18n("Whole sign"), i18n("Krusinski-Pisa"), i18n("APC"), i18n("Carter"), i18n("Equal MC=10"), i18n("SunShine"), i18n("Equal Asc=0"), i18n("PullenSD"), i18n("PullenSR"), i18n("Sripati"), nullptr);

    fill(SiderealSystemNames, i18n("Tropical"), i18n("Fagan Bradley"),  i18n("Lahiri"),
         i18n("Deluce"), i18n("Raman"), i18n("Ushashashi"), i18n("Krishnamurti"),
         i18n("Djwhal Khul"), i18n("Yukteshwar"), i18n("Jn Bhasin"),
         i18n("Babyl Kugler 1"), i18n("Babyl Kugler 2"), i18n("Babyl Kugler 3"),
         i18n("Babyl Huber"), i18n("Babyl Etpsc"), i18n("Aldebaran 15Tau"),
         i18n("Hipparchos"), i18n("Sassanian"), i18n("Galcent 0Sag"), i18n("J2000"),
         i18n("J1900"), i18n("B_1950"), i18n("Suryasiddhanta"), i18n("Suryasiddhanta Msun"), i18n("Aryabhata"), i18n("Aryabhata Msun"), i18n("SS_Revati"), i18n("SS_Citra"),  i18n("True_Citra"), i18n("True_Revati"), nullptr);

    fill(ObjNames, i18n2("Sun", "pla"), i18n("Moon"), i18n("Mercury"),
         i18n("Venus"), i18n("Mars"), i18n("Jupiter"), i18n("Saturn"),
         i18n("Uranus"), i18n("Neptune"), i18n("Pluto"), i18n("North Node"),
         i18n("South Node"), i18n("Black Moon"), i18n("Earth"), i18n("Chiron"),
         i18n("Pholus"), i18n("Ceres"), i18n("Pallas"), i18n("Juno"),
         i18n("Vesta") , i18n("Fortune"), i18n("Vertex"), i18n("East Point"), i18n("X Point"),
         i18n("Ascendant"), i18n("Midheaven"), i18n("Nadir"), i18n("Descendant"),
         i18n("1st House"), i18n("2nd House"), i18n("3rd House"), i18n("4th House"),
         i18n("5th House"), i18n("6th House"), i18n("7th House"), i18n("8th House"),
         i18n("9th House"), i18n("10th House"), i18n("11th House"), i18n("12th House"), nullptr);

    fill(ObjShortNames, i18n("Sun"), i18n("Moo"), i18n("Mer"), i18n("Ven"), i18n("Mar"),
         i18n("Jup"), i18n("Sat"), i18n("Ura"), i18n("Nep"), i18n("Plu"), i18n("Nnd"), i18n("Snd"),
         i18n("Blm"), i18n("Ear"), i18n("Chi"), i18n("Pho"), i18n("Cer"), i18n("Pal"), i18n("Jun"),
         i18n("Ves"), i18n("For"), i18n("Ver"), i18n("EP "), i18n(" X "),
         i18n("Asc"), i18n("MC "), i18n("Nad"), i18n("Dsc"),
         i18n("Hs1"), i18n("Hs2"), i18n("Hs3"), i18n("Hs4"), i18n("Hs5"), i18n("Hs6"),
         i18n("Hs7"), i18n("Hs8"), i18n("Hs9"), i18n("H10"), i18n("H11"), i18n("H12"), nullptr);
#ifdef QT
    ObjError = i18n("Unknown object");
#else
    ObjError = new AstroString(i18n("Unknown object"));
#endif

#ifdef QT
    ObjShortError = i18n("Ukn");
#else
    ObjShortError = new AstroString(i18n("Ukn"));
#endif

    fill(SignsNames, i18n("Aries"), i18n("Taurus"), i18n("Gemini"), i18n("Cancer"), i18n("Leo"),
         i18n("Virgo"), i18n("Libra"), i18n("Scorpio"), i18n("Sagittarius"), i18n("Capricorn"),
         i18n("Aquarius"), i18n("Pisces"), nullptr);

#ifdef QT
    SignsError = i18n("Unknown sign");
#else
    SignsError = new AstroString(i18n("Unknown sign"));
#endif

    fill(SignsShortNames, i18n2("Ari", "sgn"), i18n2("Tau", "sgn"), i18n2("Gem", "sgn"),
         i18n2("Can", "sgn"), i18n2("Leo", "sgn"), i18n2("Vir", "sgn"), i18n2("Lib", "sgn"),
         i18n2("Sco", "sgn"), i18n2("Sag", "sgn"), i18n2("Cap", "sgn"), i18n2("Aqu", "sgn"),
         i18n2("Pis", "sgn"), nullptr);

    fill(AspConfigNames, i18n("Grand Trine"), i18n("T-Square"), i18n("Stellium"), i18n("Grand Cross"),
         i18n("Yod"), i18n("Mystic Rectangle"), i18n("David's Star"), nullptr);
#ifdef QT
    StarsError = i18n("Unknown star");
#else
    StarsError = new AstroString(i18n("Unknown star"));
#endif

    fill(NthAbbrev, i18n("st"), i18n("nd"), i18n("rd"), i18n("th"), i18n("th"), i18n("th"),
         i18n("th"), i18n("th"), i18n("th"), i18n("th"), i18n("th"), i18n("th"), nullptr);

    fill(AspectNames, i18n("Conjunction"), i18n("Opposition"), i18n("Trine"), i18n("Square"), i18n("Sextile"), i18n("Inconjunct"), i18n("Semisextile"), i18n("Semisquare"), i18n("Sesquiquadrate"), i18n("Quintile"), i18n("Biquintile"), i18n("Semiquintile"), i18n("Septile"), i18n("Novile"), i18n("Binovile"), i18n("Biseptile"), i18n("Triseptile"), i18n("Quatronovile"), i18n("Parallel"), i18n("Anti-Parallel"), i18n("Antiscion"), i18n("Contra-Antiscion"), nullptr);

    fill(AspectShortNames, i18n("Con"), i18n("Opp"), i18n("Tri"), i18n("Squ"), i18n("Sex"), i18n("Inc"), i18n("Ssx"), i18n("Ssq"), i18n("Ses"), i18n("Qui"), i18n("BQn"), i18n("Sqn"), i18n("Sep"), i18n("Nov"), i18n("Bnv"), i18n("Bsp"), i18n("Tsp"), i18n("Qnv"), i18n("Par"), i18n("APl"), i18n("Ant"), i18n("Cat"), nullptr);

    fill(ElemPla, Fire, Water, Air, Earth, Fire, Fire, Earth, Air, Water, Water, Undefined_Element, Undefined_Element, Undefined_Element, Earth, Undefined_Element, Undefined_Element, Undefined_Element, Undefined_Element, Undefined_Element, Undefined_Element, Undefined_Element, Undefined_Element,Undefined_Element, Undefined_Element + 1);

    fill(ElemHouses, Fire, Earth, Water, Air, Fire, Earth, Air, Water, Fire, Earth, Air, Water, Fire, Earth, Air, Water, Undefined_Element + 1);


    fill(TypesNames, i18n("Null Chart"), i18n("Std Wheel Chart"), i18n("Std List Chart"), i18n("Aspects Scan List"), i18n("Local Horizon Chart"), i18n("Objects List"), i18n("Aspects Array"), i18n("Ephemeris"), i18n("Astro-Graph"), i18n("Squared Chart"), i18n("Solar System"), i18n("Tarots Spreads"), i18n("Primary Directions"), i18n("Gauquelin's sectors"), i18n("House Positions"), i18n("Batch Chart"), i18n("TensorFlow"), nullptr);

    fill(SubTypesNames, Null, i18n("Show/Hide"), i18n("Extract & Save"), i18n("Alternative Master"), i18n("Alternative Slave"), Null, i18n("Transits"), i18n("Directions"), i18n("Progressions"), i18n("Add Angle"), i18n("Mul Angle"), i18n("Composite"), i18n("Time/Space"), i18n("Solar Arc"), i18n("Profection"), nullptr);

    fill(SubTypesShortNames, Null, i18n("S/H"), i18n("E&S"), i18n("AFt"), i18n("ARf"), Null, i18n("Trn"), i18n("Dir"), i18n("Pro"), i18n("Add"), i18n("Mul"), i18n("Com"), i18n("T/S"), i18n("SoA"), i18n("Prf"), nullptr);

    fill(JumpBaseNames, i18n("Minutes"), i18n("Hours"), i18n("Days"), i18n("Months"), i18n("Years"), i18n("Centuries"), i18n("Millenia"), nullptr);
    fill(SubringsNames, i18n("No Subring"), i18n("Decans"), i18n("Solar Houses"), i18n("Lunar Houses"), i18n("Nodal Houses"), i18n("Terms"), nullptr);

    fill(DateSysNames, i18n("Julian"), i18n("Local hour"), i18n("< Dec 13 1901"), i18n("Time zone"), i18n("> Jan 18 2038"), i18n("Invalid date"), nullptr);

    fill(MajTarots, i18n("The Fool"), i18n("The Magician"), i18n("The High Priestess"), i18n("The Empress"), i18n("The Emperor"), i18n("The Pope"), i18n("The Lover"), i18n("The Chariot"), i18n("Strength"), i18n("The Hermit"), i18n("The Wheel of Fortune"), i18n("Justice"), i18n("The Hanged Man"), i18n("Arcanum XIII"), i18n("Temperance"), i18n("The Devil"), i18n("The Tower"), i18n("The Star"), i18n("The Moon"), i18n("The Sun"), i18n("Judgment"), i18n("The World"), i18n("Cancel Card"), nullptr);

    fill(MinTarots, i18n("I"), i18n("II"), i18n("III"), i18n("IV"), i18n("V"), i18n("VI"), i18n("VII"), i18n("VIII"), i18n("IX"), i18n("X"), i18n("The Servant"), i18n("The Rider"), i18n("The Queen"), i18n("The King"), i18n("Swords"), i18n("Coins"), i18n("Sticks"), i18n("Cups"), nullptr);

    fill(StateNames, i18n("Master"), i18n("Slave"), i18n("Alternative Master"), i18n("Alternative Slave"), i18n("Unknown State"), nullptr);

    fill(StateShortNames, i18n(" M"), i18n(" S"), i18n(" A"), i18n(" a"), i18n(""), nullptr);
#ifdef QT
//// for (QStringList::const_iterator it = qsl.constBegin();  it != qsl.constEnd(); ++it)
	// {
		// QDir d((*it) + "/pics");
		// if(d.exists())
			// IconsPath = d.absolutePath() + "/";
		// SWEphems += (*it) +
		IconsPath = SkyPath + "/pics/";
		SWEphems += SkyPath +
#ifdef __WINNT
			";";
#else
			":";
#endif
//	}
#endif
    fill(MiscPixmaps, "group.png", "subtype.png", "restriction.png", "newdata.png", "searchdata.png", "1.png", "2.png", "3.png", "4.png", "animation.png", "direction.png", "anim2.png", "invbg.png", "major.png", "sword.png", "coin.png", "stick.png", "cup.png", "previous.png", "next.png", nullptr);

    fill(TypePixmaps, "stdwheel.png", "stdlist.png", "stdlist.png", "local.png", "objlist.png", "asptable.png", "stdlist.png", "astrograph.png", "square.png", "solar_sys.png", "tarotspread.png", "stdlist.png", "stdwheel.png", "stdwheel.png", "stdlist.png", "tensorflow.png", nullptr);

    ScanId = TblId = 0;
    if (!TextFont.isEmpty())
        qf.fromString(TextFont);
    FontSize = qf.pointSize();
    Astro = new QFont(ASTROFONT);
    IfPrint = IfDebug = Shift = Ctrl = false;
    TarotsPixmaps[0] = nullptr;
    InterTarots = nullptr;
    DateFormat      = SetDateFmt(i18n("%a, %b %e %Y"),
#ifdef __WINNT
                                 "%a, %b %e %Y");
#else
                                 nl_langinfo(D_FMT));
#endif

    DateShortFormat = SetDateFmt(i18n("%m/%e/%Y"),
#ifdef __WINNT
                                 "%m/%e/%Y");
#else
                                 nl_langinfo(D_FMT));
#endif
    TimeFormat      = SetDateFmt(i18n("%k:%M"),
#ifdef __WINNT
                                 "%k:%M");
#else
                                 nl_langinfo(T_FMT));
#endif
    DateTimeFormat  = SetDateFmt(i18n("%a, %b %e %Y, %k:%M"),
#ifdef __WINNT
                                 "%a, %b %e %Y, %k:%M");
#else
                                 nl_langinfo(D_T_FMT));
#endif
    STimeFormat     = SetDateFmt(i18n("%k:%M:%S"),
#ifdef __WINNT
                                 "%k:%M:%S");
#else
                                 nl_langinfo(T_FMT));
#endif
    SDateTimeFormat = SetDateFmt(i18n("%a, %b %e %Y, %k:%M:%S"),
#ifdef __WINNT
                                 "%a, %b %e %Y, %k:%M:%S");
#else
                                 nl_langinfo(D_T_FMT));
#endif
    // DateFormat      = SetDateFmt(i18n("%a, %b %e %Y"), nl_langinfo(D_FMT));
// 	DateShortFormat = SetDateFmt(i18n("%m/%e/%Y"), nl_langinfo(D_FMT));
// 	TimeFormat      = SetDateFmt(i18n("%k:%M"), nl_langinfo(T_FMT));
// 	DateTimeFormat  = SetDateFmt(i18n("%a, %b %e %Y, %k:%M"), nl_langinfo(D_T_FMT));
// 	STimeFormat     = SetDateFmt(i18n("%k:%M:%S"), nl_langinfo(T_FMT));
// 	SDateTimeFormat = SetDateFmt(i18n("%a, %b %e %Y, %k:%M:%S"), nl_langinfo(D_T_FMT));

    AstroRegExp reg("^(\\w\\w)");
    if (reg < getenv("LANG"))
    {
        (reg / 1).Data(Lang, 3);
    }
    else if (reg < getenv("LC_ALL"))
    {
        (reg / 1).Data(Lang, 3);
    }
    else
    {
        Lang[0] = 0;
    }
}

#undef i18n
#ifdef LAN_CONTEXT
# define i18n(s) tr(s)
#else
# define i18n(s) Translate(s)
#endif

AstroString AstroResources::SetDateFmt(AstroString* a, const AstroString b)
{
    AstroString r = CustomDT ? *a : b;
    delete a;
    return r;
}

AstroResources::~AstroResources()
{
}

#ifdef QT
typedef QHash<QString, void*> SnDict;

static bool PutDict(SnDict& dict, const AstroString& sn)
{
    void* vv;
    if (dict[SC(const QString&, sn)])
    {
        AstroString as;
        AstroMessage(Sprintf(QT_TRANSLATE_NOOP("nc", "Error: the short name '%a' already exists"), &as, &sn));
        return false;
    }
    dict.insert(SC(const QString&, sn), vv);
    return true;
}
#endif

void AstroResources::InitExtraNames()
{
    int i = -1;
    AstroString as;
    AstroRequest arq;
#ifdef QT
    SnDict dict;
#endif
    for (int i = 0; i < 40; i++)
        PutDict(dict, *ObjShortNames[i]);
    for (int i = 0; i < NbStars; i++)
			PutDict(dict, *StaNames[i].SName);
    for (int i = 0; i < NBEXTRA; i++)
        ExtraNames[i] =  ExtraShortNames[i] = 0;
    if (!arq.Exec("SELECT * FROM ExtraObjs ORDER BY Oid"))
    {
			AstroMessage(QT_TRANSLATE_NOOP("nc", "Can't fetch Table of Extra Names !"));
        return;
    }
		int jj= 0;
    if (arq.Valid())
        do
        {
            PutDict(dict, arq < "SName");
            ExtraNames[++i]    = new AstroString(arq < "Name");
            ExtraShortNames[i] = new AstroString(arq < "SName");
            EId[i]             =  arq.GetBool("Asteroid") ? 10000 + arq.GetInt("Idx", 0) : arq.GetInt("Idx", 0);
        }
        while (arq.Next() && i < NBEXTRA);
    EId.Last = i < 0 ? 0 : i;
    LastExtra = (enum Objs)(i + First_Extra);
}

void AstroResources::SetDefZFile()
{
    AstroRequest arq;

    arq.Exec("SELECT TZFile FROM Country WHERE Idx = (SELECT countryidx FROM place WHERE idx = 1)");
    (arq < "TZFile").Data(DefZFile);
}

#ifdef QT
void AstroResources::fill(AstroString *t[], AstroString *c, ...)
{
    va_list vl;
    *t++ = c;
    va_start(vl, c);
    while ((c = va_arg(vl, AstroString*))) *t++ = c;
    va_end(vl);
}
#else
void AstroResources::fill(AstroString *t[], char *c, ...)
{
    char **RESTR ptr = &c;
    while (*ptr)
        t++ = new AstroString(*ptr++);
}
#endif

void AstroResources::fill(enum Elements *t, int e, ...)
{
    va_list vl;
    *t++ = SC(enum Elements, e);
    va_start(vl, e);
    while ((e = va_arg(vl, int)) <= Undefined_Element) *t++ = SC(enum Elements, e);
    va_end(vl);
}

void AstroResources::fill(AstroPixmap *t[], const char* c, ...)
{
    va_list vl;
    auto c1 = CSC(char*, c);
    *t++ = new AstroPixmap(c1, IconsPath);
    va_start(vl, c);
    while ((c1 = va_arg(vl, char*))) *t++ = new AstroPixmap(c1, IconsPath);
    va_end(vl);
}

bool AstroResources::SetTarotsPixmaps(bool load)
{
    if (LoadCount < 0) return false;
    if (load)
    {
        if (LoadCount == 0)
        {
#ifdef QT
            qApp->setOverrideCursor(Qt::WaitCursor);
#endif
            AstroRequest arq;
            Index idx = 0, idx1;
            AstroString path = IconsPath;
            path += "tarots/";
            if (arq.Exec("SELECT Idx, Filename FROM Tarots ORDER BY Idx") && arq.Valid())
                do
                {
                    idx1 = arq.GetInt("Idx", 0);
                    if (idx1 < 1 || idx1 > 78 || idx1 != idx + 1) return false;
                    TarotsPixmaps[idx] = new AstroPixmap(arq < "Filename", path);
                    if (!TarotsPixmaps[idx]) return false;
                    idx = idx1;
                } while (arq.Next());
#ifdef QT
            qApp->restoreOverrideCursor();
#endif
        }
        LoadCount++;
    }
    else
    {
        LoadCount--;
        if (LoadCount == 0)
            for (int i = 0; i < 78; i++)
                delete TarotsPixmaps[i];
    }
    return true;
}

static bool InitP(struct ThePart& tp, const AstroString& as, int i)
{
    int n;
    char buf[BUFSIZE];
    static const struct
    {
        const char* n;
        int o;
    } obj[] =
    {
        { "Sun", Sun },
        { "Moo", Moon },
        { "Mer", Mercury },
        { "Ven", Venus },
        { "Mar", Mars },
        { "Jup", Jupiter },
        { "Sat", Saturn },
        { "Ura", Uranus },
        { "Nep", Neptune },
        { "Plu", Pluto },
        { "Asc", Ascendant },
        { "MC ", MC },
        { "FC ", FC },
        { "Des", Descendant },
        { "Hs1", House_1 },
        { "Hs2", House_2 },
        { "Hs3", House_3 },
        { "Hs4", House_4 },
        { "Hs5", House_5 },
        { "Hs6", House_6 },
        { "Hs7", House_7 },
        { "Hs8", House_8 },
        { "Hs9", House_9 },
        { "H10", House_10 },
        { "H11", House_11 },
        { "H12", House_12 },
        { "For", Fortune },
        { 0, 0 }
    };
    static const struct
    {
        const char* n;
        int o;
    } extra[] =
    {
        { "Spi", SPI }, // Spirit
        { "Ams", AMS }, // Asc+Moo-Sun
        { "Asm", ASM }, // Asc+Sun-Moo
        { 0, 0 }
    };
    for (int j = 0; obj[j].n; j++)
        if (as == obj[j].n)
        {
            (tp * i).obj = obj[j].o;
            (tp * i).type = TYPE_OBJ;
            return true;
        }
    for (int j = 0; extra[j].n; j++)
        if (as == extra[j].n)
        {
            (tp * i).obj = extra[j].o;
            (tp * i).type = TYPE_EXTRA;
            return true;
        }
    as.Data(buf);
    if (sscanf(buf, "%d", &n) == 0)
    {
        (tp * i).type = TYPE_ERROR;
#ifdef IFEXCEPT
        AstroString as1;
        throw AstroException(OtherException, CSC(AstroString&, Sprintf(QT_TRANSLATE_NOOP("nc", "Unknown angle or part symbol '%a'"), &as1, &as)));
#else
        return false;
#endif
    }
    if (n < 1 || n > 360)
    {
        (tp * i).type = TYPE_ERROR;
#ifdef IFEXCEPT
        AstroString as1;
        throw AstroException(OtherException, CSC(AstroString&, Sprintf(QT_TRANSLATE_NOOP("nc", "Unknown angle or part symbol '%a'"), &as1, &as)));
#else
        return false;
#endif
    }
    (tp * i).obj = n;
    (tp * i).type = TYPE_VAL;
    return true;
}

bool AstroResources:: LoadParts()
{
    PartsNames = 0;
    NbParts = 0;
    AstroRequest Arq;
    AstroString as;
    if (Arq.Exec("SELECT MAX(Idx) FROM Parts") && Arq.Valid())
    {
        NbParts = Arq.GetInt("MAX", 0);
        if (NbParts)
        {
            Parts = new struct ThePart[NbParts];
            PartsNames = new Aptr[NbParts];
            for (int i = 0; i < NbParts; i++)
                Parts[i].Use = false;
#ifdef IFEXCEPT
            try
            {
#endif
                if (Arq.Exec("SELECT * FROM Parts ORDER BY Idx"))
                    do
                    {
                        int i = Arq.GetInt("Idx", 0) -1;
                        if (i < 0) continue;
                        Parts[i].Use = true;
                        PartsNames[i] = new AstroString(Arq < "Name");
                        InitP(Parts[i], Arq < "P1", 0);
                        InitP(Parts[i], Arq < "P2", 1);
                        InitP(Parts[i], Arq < "P3", 2);
                        Parts[i].Night = Arq.GetBool("Night", false);
                    } while (Arq.Next());
#ifdef IFEXCEPT
            }
            catch (AstroException& ae)
            {
                Exception(ae);
            }
#endif
        }
    }
    return true;
}

void AstroResources::SetIT(char c, int n, AstroString as)
{
    int offset;
    switch (c)
    {
    case 'M':
        offset = -1;
        break;
    case 'W':
        offset = 0;
        break;
    case 'U':
        offset = 1;
        break;
    case 'S':
        offset = 2;
        break;
    case 'C':
        offset = 3;
        break;
    default:
        return;
    };
    int i = (offset == -1) ? n - 1 : 21 + 14 * offset + n;
    if (i >= 0 && i < 78)
        InterTarots[i] = new AstroString(as);
}

bool AstroResources::LoadInterTarots(bool load)
{
    AstroRequest Arq;
    AstroString as;
    if (TaCount < 0) return false;
    if (load)
    {
        if (TaCount == 0 && Arq.Exec("SELECT COUNT(*) FROM Intertarots WHERE Lang = '%s' UNION SELECT COUNT(*) FROM Intertarots WHERE Lang = 'en' AND Idx NOT IN (SELECT Idx FROM Intertarots WHERE Lang = '%s')", Asr->Lang, Asr->Lang) && Arq.Valid())
        {
            int count = Arq.GetInt("Count", 0);
            Arq.Next();
            count += Arq.GetInt("Count", 0);
            if (count != 78)
            {
							AstroMessage(QT_TRANSLATE_NOOP("nc", "The Intertarots table must have 78 available definitions"));
                return false;
            }
            InterTarots = new Aptr[78];
            for (int i = 0; i < 78; i++) InterTarots[i] = nullptr;
            if (Arq.Exec("SELECT * FROM Intertarots WHERE Lang = '%s' UNION SELECT * FROM Intertarots WHERE Lang = 'en' AND Idx NOT IN (SELECT Idx FROM Intertarots WHERE Lang = '%s')", Asr->Lang, Asr->Lang))
                do
                    SetIT(Arq.GetChar("Type", 'X'), Arq.GetInt("Number", 0), Arq < "Text");
                while (Arq.Next());
            TaCount++;
        }
    }
    else
    {
        TaCount--;
        if (TaCount == 0)
        {
            for (int i = 0; i < 78; i++)
                delete InterTarots[i];
            delete InterTarots;
        }
    }
    return true;
}

AspScanParams::AspScanParams()
{
    Ss = Current_Day;
    NbYears = 1;
    MP = DumpAsp = AP = false;
}

Index AspIndexes::GetIdx(AstroRequest& arq)
{
    auto idx = new Index;
    Append(idx);
    //arq.Exec("SELECT NextVal('AspTbl_Idx_Seq')");
    //*idx = (Index)arq.GetInt("nextval", 0);
    *idx = arq.NextId("AspTbl");
    return *idx;
}

void AspIndexes::Delete(Index idx, AstroRequest& arq)
{
    foreach(*this, AspIndexes)
    if (*(*it) == idx)
    {
        arq.Exec("DELETE FROM AspTbl WHERE Idx = %d", idx);
        Remove((*it));
    }
}

void AspIndexes::Purge()
{
    AstroRequest arq;
    arq.Begin();
    foreach(*this, AspIndexes)
    arq.Exec("DELETE FROM AspTbl WHERE Idx = %d", *(*it));
    arq.Commit();
    Clear();
}

bool AstroResources::LoadStars()
{
	AstroRequest arq;
	AstroRegExp re("^(?!#)(.*),((\\w|-|\\*| )*),");
	re.setMinimal(true);
	QFile f(SkyPath + "/sefstars.txt");
	auto ndict = new QHash<QString, void*>;
	int cnt = 0;
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		AstroMessage(i18n("Can't open file sefstars.txt"));
		return false;
	}

	QByteArray asr = "INSERT INTO SefStars VALUES ";
	QString line;
	AstroString ax, a, b;
 arq.Exec("CREATE TEMP TABLE SefStars(Idx Int4, Ab VARCHAR(9))");
 while (!f.atEnd()) {
	 line = f.readLine();
	 if(line.left(1) != "#")
	 {
		 re <= AstroString(line);
		 a = ((re/1).trimmed());
		 b = re/2;
		 if(a.Len() && ! ndict->contains(b))
		 {
			 asr +="(";
			 asr += ax.setNum(cnt);
			 asr += ",'";
			 asr+= b;
			 asr += "'),";
			 ndict->insert(b, nullptr);
		 }
		 cnt++;
	 }
 }
 asr.truncate(asr.length()-1);
 delete ndict;
 f.close();
 arq.exec(asr.data());
 arq.Exec("CREATE TEMP VIEW SefView AS WITH St AS (SELECT * FROM Stars WHERE Lang = '%s' UNION SELECT * FROM Stars WHERE Lang = 'en' AND SName NOT IN (SELECT SName FROM Stars WHERE Lang = '%s')) SELECT St.name, x.idx, St.sname FROM St, (SELECT idx, ab FROM SefStars) AS x WHERE St.name <> '' AND sname <> '' AND St.ab = x.ab ORDER BY x.idx", &Lang, &Lang);
 arq.Exec("SELECT Count(*) FROM SefView");
 if(!arq.Valid()) return false;
 NbStars = arq.GetInt("Count");
 if(NbStars > NBSTARS) NbStars = NBSTARS;
 Final_Star = First_Star + NbStars;
 StaNames = new StNames[NbStars];
 int i = 0;
 arq.Exec("SELECT * FROM SefView");
 if(arq.Valid())
	 do
	 {
		 StNames& s = StaNames[i];
		 s.Idx = arq.GetInt("Idx");
		 s.Name = new AstroString(arq < "Name");
		 s.SName = new AstroString(arq < "SName");
	 }
	 while(arq.Next() && i++ < NbStars);
	arq.Exec("DROP VIEW SefView");
	arq.Exec("DROP TABLE SefStars");
 return true;
}

bool AstroResources::LoadInterpl()
{
    AstroRequest arq;
    AstroRegExp ar("ip(\\d+)");
    arq.Exec("SELECT Code, GetInter(Code, '%s') FROM Interpret WHERE Code LIKE 'ip\\%'", Asr->Lang);
    if(arq.Valid())
        do
        {
            ar < (arq < "Code");
            AstroString as = ar / 1;
            Interpl.insert(as.toShort(), new AstroString(arq < "GetInter"));

        }
        while(arq.Next());
        ar = "ih(\\d+)";
        arq.Exec("SELECT Code, GetInter(Code, '%s') FROM Interpret WHERE Code LIKE 'ih\\%'", Asr->Lang);
        if(arq.Valid())
            do
            {
                ar < (arq < "Code");
                AstroString as = ar / 1;
                Interpl.insert(as.toShort() + 1000, new AstroString(arq < "GetInter"));
            }
            while(arq.Next());
        ar = "is(\\d+)";
        arq.Exec("SELECT Code, GetInter(Code, '%s') FROM Interpret WHERE Code LIKE 'is\\%'", Asr->Lang);
        if(arq.Valid())
            do
            {
                ar < (arq < "Code");
                AstroString as = ar / 1;
                Interpl.insert(as.toShort() + 2000, new AstroString(arq < "GetInter"));
            }
            while(arq.Next());
        return true;
}


AstroString AstroResources::GetInterp(int i) const
{
    if(i >= Ascendant && i <= House_12)
    {
        switch(i)
       {
        case Ascendant : i = House_1; break;
        case MC : i = House_10; break;
        case Descendant : i = House_7; break;
        case FC : i = House_4; break;
        default:;
        }
        i = i - House_1 + 1000;
    }
    return Interpl[i] ? *Interpl[i] : AstroString("");
}

