/***************************************************************************
                          astrograph.cpp  -  description
                             -------------------
    begin                : sam nov 1 2003
    copyright            : (C) 2003 by Christophe Gros
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
#include "astrograph.h"
#include "astrodefs.h"
#include "astrohm.h"

#ifdef QT
#include <QApplication>
#include <QStandardPaths>
#include <QPolygon>
#endif

#define X 0
#define Y 1
#define Z 2
#define LARGE -1000.0
#define PI2 1.5707963267948966
#define TILT 23.44578889
#define MINLON -179.99
#define MAXLON 180.0
#define CX(x) ConvX(int((x) * 3600.0))
#define CY(y) ConvY(int((y) * 3600.0))
#define NORM(x) if(x < MINLON) x += 360.0; if(x > MAXLON) x -= 360.0
#define CIAFILE "CIA_WDB2.jpd.gz"
#define HEADER_MAGIC "!JPD1.0\n"
#define NSTROKES 9743
#define HEIGHT 40

extern "C"
{
#include <zlib.h>
}

struct xy
{
    double x, y;
};

static const char* Code = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static inline const AstroString& Code62(AstroString& as, int i)
{
    int j = i / 62, k = i % 62;
    AstroString as1;
    as = Code[k];
    if (j > 0)
    {
        as1 = Code[j];
        as = as1 + as;
    }
    return as;
}

class PolyAg : public AstroGraphics
{
public:

    inline void DrawPolyline(const QPolygon& a, int index = 0, int npoints = -1) {
        Qp->drawPolyline(a);
    }

    inline void DrawPolyline(const QPoint* a, int npoints = -1) {
        Qp->drawPolyline(a, npoints);
    }

    inline void DrawPolygon(const QPolygon& a, int index = 0, int npoints = -1) {
        Qp->drawPolygon(a);
    }

    inline void SetBrush(const QBrush& qb) {
        Qp->setBrush(qb);
    }
};

static inline __attribute__((pure)) int str4toint(const unsigned char *str)
{
    return int(str[3]<<24)|(str[2]<<16)|(str[1]<<8)|str[0];
}

static inline __attribute__((pure)) int str3toint(const unsigned char *str)
{
    if (str[2]<=127)
        return int(str[2]<<16)|(str[1]<<8)|str[0];
    else
        return int(0xff<<24)|(str[2]<<16)|(str[1]<<8)|str[0];
}

static inline __attribute__((pure)) double Norm(double x)
{
    if (x < MINLON) x += 360.0;
    if (x > MAXLON) x -= 360.0;
    return x;
}

bool AstroWorldMap::Get()
{
    int numseg;
    if (Count == 0)
    {
        SIndex = 0;
        Fullmap_Buffer = 0;
#ifdef QT
        QString p = SkyPath + "/" + CIAFILE;//QStandardPaths::locate(QStandardPaths::DataLocation, CIAFILE);
        gzFile zf = gzopen(p.toUtf8().data(), "r");
#endif
        if (!zf)
            return false;
#ifdef QT
        qApp->setOverrideCursor(Qt::WaitCursor);
#endif
        Head = new Header;
        gzread(zf, Head, sizeof(Header));
        if (strcmp(Head->magic, HEADER_MAGIC))
        {
            gzclose(zf);
#ifdef QT
            qApp->restoreOverrideCursor();
#endif
            return false;
        }
        numseg = str4toint(&Head->index[556]);
        SIndex = new Segment_Index[numseg];
        gzseek(zf, sizeof(Header), SEEK_SET);
        gzread(zf, SIndex, numseg * sizeof(Segment_Index));
        Address0 = sizeof(Header) + numseg * sizeof(Segment_Index);
        FbSize = str4toint(SIndex[numseg - 1].address) - Address0;
        Fullmap_Buffer = new signed char[FbSize];
        gzseek(zf, Address0, SEEK_SET);
        gzread(zf, Fullmap_Buffer, FbSize);
        gzclose(zf);
    }
    Count++;
#ifdef QT
    qApp->restoreOverrideCursor();
#endif
    return true;
}

void AstroWorldMap::Release()
{
    Count--;
    if (Count == 0) Delete();
}

void AstroWorldMap::Delete()
{
    delete SIndex;
    delete Fullmap_Buffer;
    delete Head;
}

AstroGraph::AstroGraph(ChartBaseParams* cbp, ObjsVector* ov): GraphicChartBase(cbp, ov, cbp->Ag)
{
    Ct = Astro_Graph;
    Cm = GraphicMode;
    DualChart = false;
    NbPM = 4;
    It = Click;
    Agp = nullptr;
    Apm = new AstroPopupMenu[NbPM];
    PMSET(0, i18n("Dynamically Resize"), DynamicResize);
    PMSET(1, i18n("Grid"), Grid);
    PMSET(2, i18n("Borders"), Borders);
    PMSET(3, i18n("Comment"), DisplayComment);
    Blat = -89.99;
    Tlat = 90.0;
    Rlong = MAXLON;
    Llong = MINLON;
    ZoomFact = 1;
    if (!Awm->Get())
    {
        AstroString as;
        AstroMessage(Sprintf(i18n("Sorry, Can't open %s"), &as, CIAFILE));
        return;
    }
}

AstroGraph::~AstroGraph()
{
    Awm->Release();
    delete Agp;
}

static inline double Angle(double x, double y)
{
    double a;
    if (x != 0.0)
    {
        if (y != 0.0)
            a = atan(y/x);
        else
            a = x < 0.0 ? PI : 0.0;
    }
    else
        a = y < 0.0 ? -PI2 : PI2;
    if (a < 0.0)
        a += PI;
    if (y < 0.0)
        a += PI;
    return a;
}

static void Ecl2Equ(double& azi, double& alt)
{
    double x, y, a1, l1, rtilt = DEGRAD(TILT);
    double sinalt, cosalt, sinazi, sintilt, costilt;
    azi = DEGRAD(azi);
    alt = DEGRAD(alt);
    sinalt = sin(alt);
    cosalt = cos(alt);
    sinazi = sin(azi);
    sintilt = sin(rtilt);
    costilt = cos(rtilt);

    x = cosalt * sinazi * costilt;
    y = sinalt * sintilt;
    x -= y;
    a1 = cosalt;
    y = cosalt * cos(azi);
    l1 = Angle(y, x);
    a1 = a1 * sinazi * sintilt + sinalt * costilt;
    a1 = asin(a1);
    azi = RADDEG(l1);
    alt = RADDEG(a1);
}

void AstroGraph::GetCoord(int x, int y, double* rx, double* ry) const
{
    double d = fabs(Rlong - Llong) * x / W;
    d += Llong;
    if (d < MINLON) d = MINLON;
    if (d > MAXLON) d = MAXLON;
    *rx = d;
    d = fabs(Tlat - Blat) * y / H;
    d = Tlat - d;
    if (d < -89.99) d = -89.99;
    if (d > 90.0) d = 90.0;
    *ry = d;
}

bool AstroGraph::Redisplay()
{
    const AstroWorldMap& awm = *Awm;
    int i, j, k, w, h, h1, h2, index1, index2, address1, address2, nstrokes, lon, lat, address0 = awm.GetAddr0();
    delete Agp;
    Ag->FontSize(AstroGraphics::Tiny);
    Ag->TextMetrics("A", &w, &h2);
		h = Ag->GetSize() * HEIGHT;
		w = h * Ag->GetWidth() / Ag->GetHeight();
    Agp = new AstroGraphics(Ag, 0, 2 * h2, w, h);
    auto pag = SC(PolyAg*, Agp);
    const fmbt& fmb = awm.GetFmb();
    const AstroObjs& ao = *First;
    (~ao)->Restrict(MC, false);
    //GetFS();
    double frl = fabs(Rlong - Llong), ftb = fabs(Tlat - Blat);
    W = double(Agp->GetWidth());
#ifdef QT
    QPoint qpa[NSTROKES];
    qApp->setOverrideCursor(Qt::WaitCursor);
#endif
    H = ftb * W / frl;
    if (ftb < 179.0)
    {
        H = W / 6.0 * 5.0;
        ftb = H * frl / W;
        Blat = Tlat - ftb;
    }
    else
    {
        ftb = 179.99;
        H = ftb * W / frl;
        Blat = Tlat - ftb;
    }
    if (Blat < -90.0) Blat = -90.0;
    W2 =  int(W * -Llong / frl);
    H2 = int(H * Tlat / ftb);
    Xc = ((1.0 / 3600.0) * W) / frl;
    Yc = ((1.0 / 3600.0) * H) / ftb;
    const int bound = int(H), rl = CX(Rlong), ll = CX(Llong);
    auto xy = new struct xy[bound];
    Res = ftb / H;
    for (int u = 0; u < 140; u++)
    {
        i = u / 28;
        j = u % 28;
        if (j <= 2) k = 5;
        else if (j <= 4) k = 1;
        else if (j <= 15)
        {
            k = 4;
            if (ZoomFact < 32) continue;
        }
        else k = 6;
        if (!Cbp->Borders && k != 6 && k != 4) continue;
        pag->Color(COL[k]);
        if (u == 0) index1 = 0;
        else index1 = str4toint(awm.GetIndex(4 * (u - 1)));
        index2 = str4toint(awm.GetIndex(4 * u));
        for (int i = index1; i < index2; i++)
        {
            const Segment_Index& si = awm[i];
            if ((str3toint(si.minlong) / 3600.0) > Llong || (str3toint(si.maxlong) / 3600.0)  < Rlong ||
                    (str3toint(si.minlat) / 3600.0) > Blat || (str3toint(si.maxlat) / 3600.0) < Tlat)
            {
                if (i)
                    address1 = str4toint(awm[i - 1].address);
                else
                    address1 = address0;
                address2 = str4toint(si.address);
                nstrokes = (address2 - address1 - 6) / 2;
                const segt& sb = reinterpret_cast<const segt&>(fmb[address1 - address0]);
                lon = str3toint((const unsigned char *)&sb[0]);
                lat = str3toint((const unsigned char *)&sb[3]);
                bool first = false;
                int x, y, rx = -10, ry = -10, m;
                for (j = 0, k = 0, m = 6; j < nstrokes; j++, m += 2)
                {
                    if (first)
                    {
                        lon += int(sb[m]);
                        lat += int(sb[m+1]);
                    }
                    else
                        first = true;
                    x = ConvX(lon);
                    y = ConvY(lat);
                    if (x >= int(W) || y >= int(H) || x < 0 || y < 0)
                    {
                        rx = x;
                        ry = y;
                        continue;
                    }
                    if (abs(x - rx) > 0 || abs(y - ry) > 0)
                    {
                        qpa[k++] = QPoint(x, y + 2 * h2);
                        rx = x;
                        ry = y;
                    }
                }
                pag->DrawPolyline(qpa, k);
            }
        }
    }
    int nb = 0, nbslots = 60;
    double lat1 = Blat <= -60.0 ? -60.0 : Blat, lat2 = Tlat >= 75.0 ? 75.0 : Tlat;
    int ylat1 = CY(lat1), ylat2 = CY(lat2);
    if (ylat1 > int(H))
    {
        ylat1 = int(H);
        lat1 = - ftb * (H - H2) / H;
    }
    double mc = ao * MC, mcl = ao[MC]->V[1], l = ao.Longitude.Get(true), val[10], d[10][2], e;
    Ecl2Equ(mc, mcl);
    for (int i = Sun; i <= Pluto; i++)
        if (ao == i) nb++;
    AstroPusher ap(nb * 4, nbslots, int(W));
    for (int i = Sun; i <= Pluto; i++)
        if (ao == i)
        {
            d[i][0] = ao * i;
            d[i][1] = ao[i]->V[1];
            Ecl2Equ(d[i][0], d[i][1]);
            val[i] = d[i][0] - mc + l + 180.0;
            if (val[i] > 180.0) val[i] -= 360.00;
            if (val[i] < MINLON)   val[i] += 359.99;
            if (val[i] >= Llong && val[i] <= Rlong)
            {
                int xx = CX(val[i]);
                Agp->Color(COL[Asr->EarthColor]);
                Agp->Move(xx, ylat2);
                Agp->Line(xx, ylat1);
                ap.AddElem((enum Objs)i, xx, 0);
            }
            e = val[i] + 180.0;
            if (e > MAXLON) e -= 360.0;
            if (e < MINLON) e += 359.99;
            if (e >= Llong && e <= Rlong)
            {
                int xx = CX(e);
                Agp->Color(COL[Asr->WaterColor]);
                Agp->Move(xx, ylat2);
                Agp->Line(xx, ylat1);
                ap.AddElem((enum Objs)i, xx, 1);
            }
        }
    const double longm = DEGRAD(Normalize(mc - l));
    double dlat, ad, od, oa, am, dm, z0, z1 = 0, z2;
    AstroString as;
    Agp->Fore();
    Agp->Move(ll, ylat1);
    Agp->Line(rl, ylat1);
    for (int d = -180; d <= 180; d += 5)
    {
        i = ConvX(d * 3600);
        if (i >= 0 && i <= int(W))
        {
            Agp->Move(i, ylat1);
            Agp->Line(i, ylat1 - ((d % 30) ? 3 : 5));
            Agp->Move(i, ylat2);
            Agp->Line(i, ylat2 + ((d % 30) ? 3 : 5));
        }
    }
    Agp->Move(ll, ylat2);
    Agp->Line(rl, ylat2);
    for (double d = lat1; d <= lat2; d += 5.0)
    {
        double d1 = floor(d);
        int id1 = int(d1);
        if (id1 % 5)
        {
            d1 = (double)(id1 / 5) * 5.0;
            if (d1 < d) d1 += 5.0;
        }
        i = CY(d1);
        if (i >= 0 && i <= int(H))
        {
            Agp->Move(ll, i);
            Agp->Line(ll + ((id1 % 30) ? 3 : 5), i);
            Agp->Move(rl - ((id1 % 30) ? 3 : 5), i);
            Agp->Line(rl, i);
        }
    }
    Agp->Move(rl, ylat2);
    Agp->Line(rl, ylat1);
    i = ConvY(0);
    if (i < int(H))
    {
        Agp->Move(ll, i);
        Agp->Dash(2);
        Agp->Line(rl, i);
        Agp->Dash(0);
    }
    Agp->FontSize(AstroGraphics::Very_Tiny);
    if (Cbp->Grid)
    {
        AstroHM hm;
        double dinc = (Rlong - Llong) / 4.0;
        //Agp->FontSize(AstroGraphics::Very_Tiny);
        Agp->TextMetrics("A", &w, &h);
        Agp->Dash(3);
        for (double d = Llong; d <= Rlong; d += dinc)
        {
            i = ConvX(int(d * 3600));
            if (i >= 0 && i <= int(W))
            {
                hm = DecToDeg(d);
                Agp->Grey();
                Agp->Move(i, ylat2);
                Agp->Line(i, ylat1 + (h / 2));
                Agp->Fore();
                Agp->Move(i, ylat1 + h);
                Agp->Text(hm.Get(as, HM_Longitude));
            }
        }
        dinc = (lat2 - lat1) / 4.0;
        for (double d = lat1; d <= lat2; d += dinc)
        {
            i = ConvY(int(d * 3600));
            if (i >= 0 && i <= int(H))
            {
                hm = DecToDeg(d);
                Agp->Grey();
                Agp->Move(ll, i);
                Agp->Line(rl + (h / 2), i);
                Agp->Fore();
                Agp->Text(hm.Get(as, HM_Latitude));
            }
        }
        Agp->Dash(0);
        SetWidth(W + W / 10);
    }
    for (int i = Sun; i <= Pluto; i++)
        if (ao == i)
        {
            bool b = false, b1 = false, jb = false;
            double ab = -tan(DEGRAD(d[i][1])), jt[3] = {-1000.0 };
            Agp->Color(COL[Asr->FireColor]);
            for (j = 0, dlat = lat1; dlat <= lat2 && j < bound; dlat += Res)
            {
                ad = ab * tan(DEGRAD(dlat));
                if (ad * ad > 1.0)
                    jb = true;
                else
                {
                    ad = asin(ad);
                    oa = DEGRAD(d[i][0]) - ad;
                    if (oa < 0.0)
                        oa += TWOPI;
                    am = oa -PI2;
                    z2 = am;
                    if (am < 0.0)
                        am += TWOPI;
                    z2 = RADDEG(longm - z2) + 180.0;
                    xy[j].x = -z2;
                    xy[j].y = dlat;
                    j++;
                }
                od = DEGRAD(d[i][0]) + ad;
                dm = od + PI2;
                z2 = RADDEG(longm - dm) + 180.0;
                if (jb)
                {
                    jt[0] = Norm(xy[j - 1].x);
                    jt[1] = xy[j - 1].y;
                    jt[2] = Norm(-z1);
                    jb = false;
                }
                else
                {
                    z1 = z2;
                    if (!b)
                    {
                        z0 = z2;
                        double z3 = Norm(-z2);
                        if (z3 >= Llong && z3 <= Rlong)
                        {
                            int x1 = CX(z3);
                            Agp->Move(x1, CY(dlat));
                            if (dlat == lat1)
                                ap.AddElem((enum Objs)i, x1, 2);
                            b = true;
                        }
                    }
                    else
                    {
                        WLine(-z0, -z2, dlat);
                        z0 = z2;
                    }
                }
            }
            Agp->Color(COL[Asr->AirColor]);
            for (int k = 0; k < j; k++)
                if (!b1)
                {
                    z0 = xy[k].x;
                    double z3 = Norm(z0);
                    if (z3 >= Llong && z3 <= Rlong)
                    {
                        int x1 = CX(z3);
                        Agp->Move(x1, CY(xy[k].y));
                        if (xy[k].y == lat1)
                            ap.AddElem((enum Objs)i, x1, 3);
                        b1 = true;
                    }
                }
                else
                {
                    WLine(z0, xy[k].x, xy[k].y);
                    z0 = xy[k].x;
                }
            if (jt[0] != -1000.0)
            {
                Agp->Color(COL[7]);
                Agp->Move(CX(jt[2]), CY(jt[1]));
                WLine(jt[2], jt[0], jt[1]);
                Agp->Color(COL[0]);
            }
        }
    delete xy;
    ap.Push();
    int max = 0, la = CY(Blat), z, by;
    char c;
    Agp->FontSize(AstroGraphics::Tiny, true);
    Agp->GlyphMetrics('A', &w, &h1);
    h = h1;
    if (la - CY(lat1) < 2) la += 3 * h;
    by = z = la;
    j = int(W) / nbslots;
    for (int i = 0; i < nbslots; i++)
        if (ap[i].o != Undefined_Obj && ap[i].val >= 0 && ap[i].val < int(W))
        {
            c = ao.GetObjChar(ap[i].o);
            Agp->GlyphMetrics(c, &w, &h);
            Agp->Move(ap[i].val, CY(lat1));
            switch (ap[i].type)
            {
            case 0:
                Agp->Color(COL[Asr->EarthColor]);
                as = "M";
                break;
            case 1:
                Agp->Color(COL[Asr->WaterColor]);
                as = "F";
                break;
            case 2:
                Agp->Color(COL[Asr->FireColor]);
                as = "A";
                break;
            default:
                Agp->Color(COL[Asr->AirColor]);
                as = "D";
            }
            Agp->Dash(3);
            Agp->Line(j * i + (j / 2), la);
            Agp->Dash(0);
            Agp->Color(ao.GetObjColor(ap[i].o));
            k = j * i + (j - w) / 2;
            Agp->Move(k, la + h);
            Agp->Glyph(c);
            Agp->TextMetrics(as, &w, &h);
            k = j * i + (j - w) / 2;
            Agp->Move(k, la + h + h1);
            Agp->Text(as);
        }
    if (ZoomFact >= 128)
    {
        AstroString as;
        AstroRequest Arq;
        int w, h, w1, h1, count = 0, col = int(W) / 4;
        Agp->TextMetrics("A", &w1, &h1);
        int tx = w1, ty = 0;
        la += 3 * h1;
        Arq.Exec("SELECT COUNT(*) FROM Place WHERE Latitude > %f AND Latitude < %f AND Longitude > %f AND Longitude < %f", Blat, Tlat, Llong, Rlong);
        max = Arq.GetInt("COUNT");
        Arq.Exec("SELECT Name, Latitude, Longitude FROM Place WHERE Latitude > %f AND Latitude < %f AND Longitude > %f AND Longitude < %f ORDER BY Longitude", Blat, Tlat, Llong, Rlong);
        if (Arq.Valid()) do
            {
                double lat = Arq.GetDouble("Latitude"), lon = Arq.GetDouble("Longitude");
                int x = CX(DegToDec(lon)), y = CY(DegToDec(lat - 0.01));
                if (x < int(W) && y < int(H) && x > 0 && y > 0)
                {
                    Code62(as, count);
                    Agp->TextMetrics(as, &w, &h);
                    Agp->Move(x - w / 2, y - h / 2);
                    Agp->Color(COL[3]);
                    Agp->Text(as);
                    if (ty > max / 4)
                    {
                        tx += col;
                        ty = 0;
                    }
                    z = la + ty * h1;
                    Agp->Move(tx, z);
                    if (z > by) by = z;
                    as += ":";
                    Agp->Text(as);
                    Agp->Fore();
                    Agp->RMove(2 * w1);
                    Agp->Text(Arq < "Name");
                    count++;
                    ty++;
                }
            }
            while (Arq.Next());
    }
    Init(false, by + 4 * h + 2 * h2);
    DrawInfo(ao, ao.GetRing());
    if (Cbp->DisplayComment)
        DrawComment(ao);
    SetHeight(by + 4 * h + 2 * h2 + GetSizeLines());
#ifdef QT
    qApp->restoreOverrideCursor();
#endif
    return 1;
}

void AstroGraph::WLine(double z0, double z2, double dlat) const
{
    int x, h, y = CY(dlat);
    double d, dlat1;
    if (z2 < MINLON)
    {
        if (z0 > MINLON)
        {
            d =  Res / (z2 - z0);
            dlat1 = dlat - (-d * (MINLON - z0));
            if (Llong < z0)
            {
                h = CY(dlat1);
                Agp->Line(CX(MINLON), h);
                z2 += 360.0;
                if (z2 <= Rlong)
                {
                    x = ConvX(180 * 3600);
                    Agp->Move(x, y);
                    Agp->Line(CX(z2), y);
                }
            }
        }
        else
        {
            z2 += 360.0;
            if (z2 < Rlong)
            {
                x = CX(z2);
                if (abs(x - Agp->GetX()) > W2 / 2)
                    Agp->Move(x, y);
                Agp->Line(x, y);
            }
        }
        return;
    }
    if (z2 > MAXLON)
    {
        if (z0 < MAXLON)
        {
            d = Res / (z2 - z0);
            if (fabs(MINLON - z0) > 180.0)
                z0 = -z0;
            dlat1 = dlat - (-d * (MINLON - z0));
            if (Rlong > z0)
            {
                h = CY(dlat1);
                Agp->Line(int(W), h);
                z2 -= 360.0;
                if (z2 >= Llong)
                {
                    x = ConvX(-180 * 3600);
                    Agp->Move(x, h);
                    Agp->Line(CX(z2), y);
                }
            }
        }
        else
        {
            z2 -= 360.0;
            if (z2 > Llong)
            {
                x = CX(z2);
                if (abs(x - Agp->GetX()) > W2 / 2)
                    Agp->Move(x, y);
                Agp->Line(x, y);
            }
        }
        return;
    }
    if (z2 >= Llong && z2 <= Rlong)
    {
        x = CX(z2);
        if (abs(x - Agp->GetX()) > W2 / 2)
            Agp->Move(x, y);
        Agp->Line(x, y);
    }
}

AstroPusher::AstroPusher(int nbelems, int nbslots, int x)
{
    NbElems = nbelems;
    NbSlots = nbslots;
    MaxX = x;
    Elems = new struct PushElem[nbelems];
    Slots = new struct PushElem[nbslots];
    Cnt = 0;
    for (int i = 0; i < NbSlots; i++)
        Slots[i].o = Undefined_Obj;
}

bool AstroPusher::AddElem(enum Objs o, int v, int t)
{
    if (Cnt == NbElems) return false;
    Elems[Cnt].o = o;
    Elems[Cnt].val = v;
    Elems[Cnt].type = t;
    Cnt++;
    return true;
}

extern "C"
{
    static int pecompar(const void *a, const void *b)
    {
        auto pea = SC(const PushElem*, a), peb = SC(const PushElem*, b);
        if (pea->val < peb->val) return -1;
        if (pea->val == peb->val) return 0;
        return 1;
    }
}

void AstroPusher::Push()
{
    int k;
    qsort(Elems, Cnt, sizeof(struct PushElem), pecompar);
    for (int i = 0; i < Cnt; i++)
    {
        int j = (Elems[i].val * NbSlots) / MaxX;
        if (Slots[j].o == Undefined_Obj)
        {
            Slots[j] = Elems[i];
            continue;
        }
        bool b = false;
        for (k = j; k < NbSlots; k++)
            if (Slots[k].o == Undefined_Obj)
            {
                Slots[k] = Elems[i];
                b = true;
                break;
            }
        if (k - j > 2 || !b)
        {
            for (k = j; k >= 0; k--)
            {
                if (Slots[k].o == Undefined_Obj)
                {
                    int l;
                    for (l = k; Slots[l + 1].o != Undefined_Obj && l < NbSlots - 1; l++)
                        Slots[l] = Slots[l + 1];
                    Slots[l].o = Undefined_Obj;
                    break;
                }
            }
        }
        if (!b)
            Slots[j] = Elems[i];
    }
}
