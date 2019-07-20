/***************************************************************************
                          astroparams.cpp  -  description
                             -------------------
    begin                : Sat Sep 16 2000
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
#include "astroparams.h"
#include "astrographics.h"
#include "astroutils.h"
#include "astrorestrictions.h"
#include "editchartparms.h"
#include "editdefparms.h"
#include "astromainwindow.h"
#include "astrowindow.h"

#include <cstdio>
#ifdef __WINNT
#include <winsock.h>
//#include <windows.h>
#include <Lmcons.h>
#endif

// Various const param tables
static const unsigned char ColorVector[16 * 3] = DEF_COLORS;
static const int RulersVector[12 * 6]          = DEF_RULERS;
static const struct Rest Rv[]                  = DEF_RESTRICTIONS;
static const struct AspectsConstants Acv[]     = DEF_ASPECTS_CONST;
static const struct AspectRestrictions Arv[]   = DEF_ASPECTS_RESTRICTIONS;
static const enum Objs DecansTable[]           = DEF_DECANS;
static const enum Objs DaysMastersTable[]      = DEF_MASDAY;
static const enum Objs OrdMastHourTable[]      = DEF_ORMAH;
static const int ScoresVector[]                = DEF_SCORES;
static const char* RomanNumbersVector[]        = { " ", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "" };
static const SignTerms TermsTable[]            = DEF_TERMS;
const struct Rest* RestVector                  = Rv;
const struct AspectsConstants* AspConstVector  = Acv;
const struct AspectRestrictions* AspRestVector = Arv;
const char* HousesCodes                        = HOUSESCODES;
const enum Objs* DecansVector                  = DecansTable;
const int* ScoresTable                         = ScoresVector;
const enum Objs* DaysMasters                   = DaysMastersTable;
const enum Objs* OrdMastHours                  = OrdMastHourTable;
const char** RomanNumbers                      = RomanNumbersVector;
const SignTerms* TermsVector                   = TermsTable;
const char *AccessModes[]                      = { "Private", "Shown", "Shared" }; 

/*template <typename T, int N> char(&dim_helper(T(&)[N]))[N];
#define dim(x) (sizeof(dim_helper(x)))
std::extent<decltype(array)>::value;*/

bool AstroParams::Load()
{
	char user[50];
#ifdef KF5
    ConfFile = true;
    KConf = new KConfig("skylendarrc", KConfig::NoGlobals);
    if (KConf->hasGroup("General"))
        SetGroup("General");
    else
#else
#ifdef QT
			Qs = new QSettings("skylendar.org", PACKAGE);
		  SetGroup("General");
#endif
		  ConfFile = false;
#endif
    DynamicResize = GetArg("Dynamic_Resize", DEF_DYNAMICRESIZE);
    LeftAscendant = GetArg("Left_Ascendant", DEF_LEFTASCENDANT);
    Sidebars      = GetArg("Sidebars", DEF_SIDEBARS);
    DisplaySeconds= GetArg("Display_Seconds", DEF_SECONDS);
    AspectsFrame  = GetArg("Aspects_Frame", DEF_ASPECTS_BAR);
    DisplayMidPoints = GetArg("Display_Mid_Points",DEF_MID_POINTS);
    CentralRing   = GetArg("Central_Ring", DEF_CENTRAL_RING);
    EuropCapr     = GetArg("European_Capricornus_Glyph", DEF_EUROP_CAPR);
    EuropUran     = GetArg("European_Uranus_Glyph", EUROP_URAN);
    EuropPlut     = GetArg("European_Pluto_Glyph", EUROP_PLUT);
    SortAsp       = GetArg("Sort_Aspects_List", DEF_SORT_ASP);
    PlanetsRank   = GetArg("Planets_Rank", DEF_PLANET_RANK);
    RiseSet       = GetArg("Planets_Rise_Set",  DEF_RISESET);
    GlobEclipse   = GetArg("Global_Eclipse", DEF_GLOB_ECLIPSE);
    AspectsConfig = GetArg("Aspects_Configuration", DEF_ASPECTS_CONFIG);
    InvBack       = false;
    BackImage     = false;
    Grid          = GetArg("Grid", DEF_GRID);
    Sabian        = GetArg("Sabian", DEF_SABIAN);
    Outlines      = GetArg("Outlines", DEF_OUTLINES);
    DisplayComment= GetArg("Comment", DEF_COMMENT);
    Apsides       = GetArg("Apsides", DEF_APSIDES);
    Frameless     = GetArg("Frameless", DEF_FRAMELESS);
    DispTarotTable= GetArg("Display_Tarots_Table", DEF_DISPTAROTTABLE);
    PlanetHour    = GetArg("Planetary_Hour", DEF_PLANET_HOUR);
    ArabicParts   = GetArg("Arabic_Parts", DEF_ARABIC_PARTS);
    Interpretation= GetArg("Interpretation", DEF_INTERPRETATION);
    InterpretTrans= GetArg("InterpretTrans", DEF_INTERPRETTRANS);
    Heliacal      = GetArg("Heliacal", DEF_HELIACAL);
    DecTerms      = GetArg("Dec_Terms", DEF_DECTERMS);
    Occultations  = GetArg("Occultations", DEF_OCCULTATIONS);
    Borders       = GetArg("Borders", DEF_BORDERS);
    Constellations= GetArg("Constellations", DEF_CONSTELLATIONS);
    Sectors       = GetArg("Sectors", DEF_SECTORS);
    Subring       = (enum Subring)GetArg("Type_of_Subring", DEF_SUBRING);
    GetArg("Zone_Info_Path", ZPATH, ZPath, BUFSIZE);
    TextFont      = GetArg("Text_Font", AstroString(DEF_TEXT_FONT));
    ExtraTime     = GetArg("Time_Offset", DEF_TIMEOFFSET);
    FirstNow      = GetArg("Now_Chart", DEF_NOW_CHART);
    CustomDT      = GetArg("Custom_Date_Time", DEF_CUSTOM_DT);
    GetArg("Rulers_Table", Rulers, RulersVector, 12 * 6);
    Width         = GetArg("Graphic_Width", DEF_GRAPHIC_WIDTH);
    Height        = GetArg("Graphic_Height", DEF_GRAPHIC_HEIGHT);
    Antialias     = GetArg("Antialias",  DEF_ANTIALIAS);
    CardZoomFactor= GetArg("Card_Zoom_Factor", DEF_ZOOM_FACTOR);
    NbLines	      = GetArg("Number_of_Lines", DEF_NBLINES);
    IncDecGlyph   = GetArg("Inc_Dec_Glyph", DEF_INCDECGLYPH);
    UTC           = GetArg("Coordinated_Universal_Time", DEF_UTC);
    Astrologer    = GetArg("Astrologer", AstroString(DEF_ASTROLOGER));
    SkyUser       = GetArg("SkyUser", AstroString());
    SkyPass       = GetArg("SkyPass", AstroString());
    Background    = GetArg("Background", AstroString());
    IfBW          = GetArg("Print_BW", DEF_PRINT_BW);
    StartInvBack  = GetArg("Start_Inv_Back", DEF_START_INVBACK);
    RightDW       = GetArg("RightDW", DEF_RIGHTDW);
    Id            = GetArg("Id", Long(0L));
    if(Id == 0L)
    {
        srand(time(nullptr));
        Id =(Long(rand()) << 32) + Long(rand());
        SetArg("Id", Id);
    }
    SetGroup("Colors");
    FireColor     = GetArg("Fire_Color", DEF_FIRE_COLOR);
    AirColor      = GetArg("Air_Color", DEF_AIR_COLOR);
    WaterColor    = GetArg("Water_Color", DEF_WATER_COLOR);
    EarthColor    = GetArg("Earth_Color", DEF_EARTH_COLOR);
    OtherColor    = GetArg("Other_Color", DEF_OTHER_COLOR);
    AsteroColor   = GetArg("Astero_Color", DEF_ASTERO_COLOR);
    ExtraColor    = GetArg("Extra_Color", DEF_EXTRA_COLOR);
    GetArg("Palette", *Acl, ColorVector);
    SetGroup("DataBase");
    DbName        = GetArg("Database_Name", AstroString(DEF_DATABASE));
#ifdef __WINNT
		TCHAR name [ UNLEN + 1 ];
		DWORD size = UNLEN + 1;

		GetUserName((TCHAR*)name, &size );
		strncpy(user, name, size);
    for (char *c = user; *c; c++) {
        *c = tolower(*c);
    }
#else
    strncpy(user, cuserid(0), 30);
#endif
    DbUser         = GetArg("User_Name", AstroString(user));
    DbHost         = GetArg("Host_Name", AstroString(DEF_DB_HOST));
#ifdef KF5
    delete KConf;
    KConf = 0;
#else
		Qs->endGroup();
		delete Qs;
#endif
    return true;
}

bool AstroParams::Save()
{
#ifdef KF5
    KConf = new KConfig("skylendarrc", KConfig::NoGlobals);
#else
		Qs = new QSettings("skylendar.org", PACKAGE);
#endif
    SetGroup("General");
    SetArg("Dynamic_Resize", DynamicResize);
    SetArg("Left_Ascendant", LeftAscendant);
    SetArg("Sidebars", Sidebars);
    SetArg("Aspects_Frame", AspectsFrame);
    SetArg("Display_Mid_Points", DisplayMidPoints);
    SetArg("Display_Seconds", DisplaySeconds);
    SetArg("Central_Ring", CentralRing);
    SetArg("European_Capricornus_Glyph", EuropCapr);
    SetArg("European_Uranus_Glyph", EuropUran);
    SetArg("European_Pluto_Glyph", EuropPlut);
    SetArg("Sort_Aspects_List", SortAsp);
    SetArg("Planets_Rank", PlanetsRank);
    SetArg("Planets_Rise_Set", RiseSet);
    SetArg("Global_Eclipse", GlobEclipse);
    SetArg("Aspects_Configuration", AspectsConfig);
    SetArg("Grid", Grid);
    SetArg("Sabian", Sabian);
    SetArg("Outlines", Outlines);
    SetArg("Frameless", Frameless);
    SetArg("Display_Tarots_Table", DispTarotTable);
    SetArg("Planetary_Hour", PlanetHour);
    SetArg("Comment", DisplayComment);
    SetArg("Apsides", Apsides);
    SetArg("Arabic_Parts", ArabicParts);
    SetArg("Interpretation", Interpretation);
    SetArg("InterpretTrans", InterpretTrans);
    SetArg("Heliacal", Heliacal);
    SetArg("Dec_Terms", DecTerms);
    SetArg("Occultations", Occultations);
    SetArg("Borders", Borders);
    SetArg("Constellations", Constellations);
    SetArg("Sectors", Sectors);
    SetArg("Type_of_Subring", Subring);
    SetArg("Zone_Info_Path", ZPath);
    SetArg("Text_Font", TextFont);
    SetArg("Time_Offset", ExtraTime);
    SetArg("Graphic_Width", Width);
    SetArg("Graphic_Height", Height);
    SetArg("Antialias", Antialias);
    SetArg("Print_BW", IfBW);
    SetArg("Custom_Date_Time", CustomDT);
    SetArg("Card_Zoom_Factor", CardZoomFactor);
    SetArg("Number_of_Lines", NbLines);
    SetArg("Inc_Dec_Glyph", IncDecGlyph);
    SetArg("Coordinated_Universal_Time", UTC);
    SetArg("Start_Inv_Back", StartInvBack);
    SetArg("Astrologer", Astrologer);
    SetArg("SkyUser", SkyUser);
    SetArg("SkyPass", SkyPass);
    SetArg("Background", Background);
    SetArg("RightDW", RightDW);
    SetGroup("Colors");
    SetArg("Fire_Color", FireColor);
    SetArg("Air_Color", AirColor);
    SetArg("Water_Color", WaterColor);
    SetArg("Earth_Color", EarthColor);
    SetArg("Other_Color", OtherColor);
    SetArg("Astero_Color",  AsteroColor);
    SetArg("Extra_Color", ExtraColor);
    SetArg("Palette", *Acl);
    SetGroup("DataBase");
    SetArg("Database_Name", DbName);
    SetArg("User_Name", DbUser);
    SetArg("Host_Name", DbHost);
#ifdef KF5
    KConf->sync();
    delete KConf;
    KConf = 0;
#else
		Qs->endGroup();
		Qs->sync();
		delete Qs;
#endif
    return true;
}

bool AstroParams::Edit()
{
    EditDefParms edp(this);
#ifdef QT
    return edp.exec() ==  QDialog::Accepted;
#endif
}

void AstroParams::SetGroup(const AstroString& as)
{
#ifdef KF5
    Kg = KConf->group(as);
#else
		if(Qs->group() != "" && Qs->group() != as)
			Qs->endGroup();
		Qs->beginGroup(as);
#endif
}

void AstroParams::SetArg(const char* ident, int i)
{
#ifdef KF5
    Kg.writeEntry(ident, i);
#else
		Qs->setValue(ident, i);
#endif
}

void AstroParams::SetArg(const char* ident, const AstroString& as)
{
#ifdef KF5
    Kg.writeEntry(ident, QString(as));
#else
		Qs->setValue(ident, as);
#endif
}

void AstroParams::SetArg(const char* ident, const char* s)
{
#ifdef KF5
    Kg.writeEntry(ident, s);
#else
		Qs->setValue(ident, s);
#endif
}

void AstroParams::SetArg(const char* ident, double d)
{
#ifdef KF5
    Kg.writeEntry(ident, d);
#else
		Qs->setValue(ident, d);
#endif
}

void AstroParams::SetArg(const char* ident, bool b)
{
#ifdef KF5
    Kg.writeEntry(ident, b);
#else
		Qs->setValue(ident, b);
#endif
}

void AstroParams::SetArg(const char* ident, const int* array, int nb)
{
#ifdef KF5
    QList<int> v;
    for (int i = 0; i < nb; i++)
        v += array[i];
    Kg.writeEntry(ident, v);
#else
		QList<QVariant> v;
    for (int i = 0; i < nb; i++)
        v += array[i];
		Qs->setValue(ident, v);
#endif
}

void AstroParams::SetArg(const char* ident, Long i)
{
#ifdef KF5
    Kg.writeEntry(ident, i);
#else
        Qs->setValue(ident, qlonglong(i));
#endif
}

int AstroParams::GetArg(const char* ident, int Default)
{
#ifdef KF5
    return (KConf && ConfFile) ? Kg.readEntry(ident, Default) : Default;
#elif defined(QT)
		const QVariant qv = Qs->value(ident);
		return qv.isNull() ? Default : qv.toInt();
#else
    return Default;
#endif
}

void AstroParams::GetArg(const char* ident, AstroString Default, char* result, int size = BUFSIZE)
{
#ifdef KF5
    char buf[BUFSIZE];
    if (ConfFile)
    {
        QString s = Kg.readEntry(ident, QString(Default));
        strncpy(result, s.toUtf8().data(), size);
    }
    else
        Default.Data(result, size);
#elif defined(QT)
		const QVariant v = Qs->value(ident);
		if(v.isNull())
			strncpy(result, Default.toUtf8(), size);
		else
			strncpy(result, v.toByteArray().constData(), size);
#else
    strncpy(result, Default.Data(), size);
#endif
}

AstroString AstroParams::GetArg(const char* ident, const AstroString& Default)
{
#ifdef KF5
	return (KConf && ConfFile) ? Kg.readEntry(ident, QString(Default)) : Default;
#elif defined(QT)
		const QVariant v = Qs->value(ident);
		return v.isNull() ? Default : AstroString(v.toString());
#else
    return Default;
#endif
}

double AstroParams::GetArg(const char* ident, double Default)
{
#ifdef KF5
    return (KConf && ConfFile) ? Kg.readEntry(ident, Default) : Default;
#elif defined(QT)
		const QVariant v = Qs->value(ident);
		return v.isNull() ? Default : v.toDouble();
#else
    return Default;
#endif
}

void AstroParams::GetArg(const char* ident, AstroColorList& acl, const unsigned char* Default)
{
#ifdef KF5
    int r, g, b;
    const unsigned char *j = Default;
    AstroString id = ident;
    QColor col;
    QVariant qv;
    KConfigGroup Kg = KConf->group("Color");
    for (int i = 0; i < 16; i++)
    {
        r = *j++;
        g = *j++;
        b = *j++;
        col.setRgb(r, g, b);
        qv.setValue(col);
        if (ConfFile)
            col = Kg.readEntry(id + i, qv).value<QColor>();
        acl.SetColor(col.red(), col.green(), col.blue(), i);
    }
#elif defined(QT)
		const QVariant v = Qs->value(ident);
		if(!v.isNull())
		{
			const QList<QVariant> lv = v.toList();
			for (int i = 0; i < 16; i++)
			{
				const QColor& c = lv[i].value<QColor>();
				acl.SetColor(c.red(), c.green(), c.blue(), i);
			}
		}
		else
		{
			const unsigned char *cv = Default;
			for(int i = 0; i < 16; i++)
			{
				const unsigned char r = *cv++, g = *cv++, b = *cv++;
				acl.SetColor(r, g, b, i);
			}
		}
#endif
}

Long AstroParams::GetArg(const char* ident, Long Default)
{
#ifdef KF5
    return (KConf && ConfFile) ? Kg.readEntry(ident, Default) : Default;
#elif defined(QT)
    if(Qs->contains(ident))
    {
        const QVariant qv = Qs->value(ident);
        return qv.toLongLong();
    }
    else
        return Default;

#else
    return Default;
#endif
}

void AstroParams::SetArg(const char* ident, const AstroColorList& acl)
{
#ifdef KF5
    QVariant qv;
    AstroString id = ident;
    KConfigGroup Kg = KConf->group("Color");
    for (int i = 0; i < 16; i++)
    {
        qv.setValue(QColor(acl[i]));
        Kg.writeEntry(id + i, qv);
    }
#elif defined(QT)
		QList<QVariant> lv;
		for (int i = 0; i < 16; i++)
			lv += acl[i];
		Qs->setValue(ident, lv);
#endif
}

/** Gets a bool argument from init file. If not defined return default) */
bool AstroParams::GetArg(const char* ident, bool Default)
{
#ifdef KF5
    return (KConf && ConfFile) ? Kg.readEntry(ident, Default) : Default;
#elif defined(QT)
		const QVariant v = Qs->value(ident);
		return v.isNull() ? Default : v.toBool();
#else
    return Default;
#endif
}

void AstroParams::GetArg(const char* ident, int* result, const int* Default, int nb)
{
#ifdef KF5
    QList<int> qvi;
    QList<int>::Iterator it;
    if (ConfFile)
    {
        int i = 0;
        qvi = Kg.readEntry(ident, qvi);
        for (it = qvi.begin(); it != qvi.end() && i < nb; it++, i++)
            result[i] = (*it);
        while (i < nb)
            result[i] = Default[i++];
    }
    else
        for (int i = 0; i < nb; i++)
            result[i] = Default[i];
#elif defined(QT)
		QVariant v = Qs->value(ident);
		if(!v.isNull())
		{
			const QList<QVariant> lv = v.toList();
			for(int i = 0; i < nb; i++)
				result[i] = lv[i].toInt();
		}
		else
			for(int i = 0; i < nb; i++)
				result[i] = Default[i];
#else
    for (int i = 0; i < nb; i++)
        result[i] = Default[i]
#endif
}

void AstroParams::GetArg(const char* ident, double* result, const double* Default, int nb)
{
#ifdef KF5
    QStringList qsl;
    QStringList::Iterator it;
    if (ConfFile)
    {
        int i;
        qsl = Kg.readEntry(ident, qsl);
        for (it = qsl.begin(), i = 0; it != qsl.end() && i < nb; it++, i++)
            result[i] = atof((*it).toUtf8().data());
        while (i < nb)
            result[i] = Default[i++];
    }
    else
        for (int i = 0; i < nb; i++)
            result[i] = Default[i];
#elif defined(QT)
		QVariant v = Qs->value(ident);
		if(!v.isNull())
		{
			const QList<QVariant> lv = v.toList();
			for(int i = 0; i < nb; i++)
				result[i] = lv[i].toDouble();
		}
		else
			for(int i = 0; i < nb; i++)
				result[i] = Default[i];
#else
    for (int i = 0; i < nb; i++)
        result[i] = Default[i];
#endif
}

void AstroParams::GetArg(const char* ident, bool* result, const bool* Default, int nb)
{
#ifdef KF5
    QList<int> qvi;
    QList<int>::Iterator it;
    if (ConfFile)
    {
        int i = 0;
        qvi = Kg.readEntry(ident, qvi);
        for (it = qvi.begin(); it != qvi.end() && i < nb; it++, i++)
            result[i] = (*it);
        while (i < nb)
            result[i] = Default[i++];
    }
    else
        for (int i = 0; i < nb; i++)
            result[i] = Default[i];
#elif defined(QT)
				QVariant v = Qs->value(ident);
				if(!v.isNull())
				{
					const QList<QVariant> lv = v.toList();
					for(int i = 0; i < nb; i++)
						result[i] = lv[i].toBool();
				}
				else
					for(int i = 0; i < nb; i++)
						result[i] = Default[i];
#else
				for (int i = 0; i < nb; i++)
					result[i] = Default[i];
#endif
}

void AstroParams::GetArg(const char* ident, struct AspectData *result, const struct AspectData * Default)
{
#ifdef KF5
    QString s, l, group = ident;
    QStringList qsl;
    QStringList::Iterator it;
    if (ConfFile)
    {
        KConfigGroup Kg = KConf->group(group);
        for (int i = Conjunction; i < Unknown_Aspect; i++)
        {
            l = "Aspect " + i;
            qsl = Kg.readEntry(l, qsl);
            if (qsl.count() == 4)
            {
                it = qsl.begin();
                result[i].Angle = atof((*it).toUtf8().data());
                it++;
                result[i].Orb   = atof((*it).toUtf8().data());
                it++;
                result[i].Ak    = (enum AspectKind)atol((*it).toUtf8().data());
                it++;
                result[i].Color = atol((*it).toUtf8().data());
            }
            else
                result[i] = Default[i];
        }
        group = "General";
        Kg = KConf->group(group);
    }
    else
    {
        for (int i = Conjunction; i < Unknown_Aspect; i++)
            result[i] = Default[i];
    }
#elif defined(QT)
		
#else
    for (int i = Conjunction; i < Unknown_Aspect; i++)
        result[i] = Default[i];
#endif
}

bool ChartParams::Edit()
{
#ifdef QT
    EditChartParms ecp(this);
    return ecp.exec() == QDialog::Accepted;
#endif
}
/** Destructor */
AstroParams::~AstroParams()
{
}

#define G(fl) bf |= fl << (i++)
#define S(fl) fl = bitsfield & (1 << (i++))

Long ChartParams::GetFlags() const
{

    Long bf = 0;
    int i = 0;
    G(DynamicResize);
    G(LeftAscendant);
    G(Sidebars);
    G(DisplaySeconds);
    G(AspectsFrame);
    G(DisplayMidPoints);
    G(CentralRing);
    G(EuropCapr);
    G(EuropUran);
    G(EuropPlut);
    G(SortAsp);
    G(PlanetsRank);
    G(RiseSet);
    G(GlobEclipse);
    G(AspectsConfig);
    G(Grid);
    G(Sabian);
    G(Outlines);
    G(DisplayComment);
    G(Apsides);
    G(Frameless);
    G(DispTarotTable);
    G(PlanetHour);
    G(ArabicParts);
    G(Interpretation);
    G(InterpretTrans);
    G(Heliacal);
    G(DecTerms);
    G(Occultations);
    G(Borders);
    G(Constellations);
    G(BackImage);
    G(Sectors);
    return bf;
}

void ChartParams::SetFlags(Long bitsfield)
{
    int i = 0;
    S(DynamicResize);
    S(LeftAscendant);
    S(Sidebars);
    S(DisplaySeconds);
    S(AspectsFrame);
    S(DisplayMidPoints);
    S(CentralRing);
    S(EuropCapr);
    S(EuropUran);
    S(EuropPlut);
    S(SortAsp);
    S(PlanetsRank);
    S(RiseSet);
    S(GlobEclipse);
    S(AspectsConfig);
    S(Grid);
    S(Sabian);
    S(Outlines);
    S(DisplayComment);
    S(Apsides);
    S(Frameless);
    S(DispTarotTable);
    S(PlanetHour);
    S(ArabicParts);
    S(Interpretation);
    S(InterpretTrans);
    S(Heliacal);
    S(DecTerms);
    S(Occultations);
    S(Borders);
    S(Constellations);
    S(BackImage);
    S(Sectors);
    DynamicResize = false;
}
