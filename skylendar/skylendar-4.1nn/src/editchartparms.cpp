#include "editchartparms.h"
#include "astroresources.h"
#include <QCheckBox>
#include <QComboBox>

/*
 *  Constructs a EditChartParms which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
EditChartParms::EditChartParms(ChartParams* cp)
{
    Cp = cp;
    CpBase = *Cp;
    setupUi(this);
    DynamicResize->setChecked(CpBase.DynamicResize);
    LeftAscendant->setChecked(CpBase.LeftAscendant);
    Sidebars->setChecked(CpBase.Sidebars);
    AspectsFrame->setChecked(CpBase.AspectsFrame);
    DisplayMidPoints->setChecked(CpBase.DisplayMidPoints);
    DisplaySeconds->setChecked(CpBase.DisplaySeconds);
    AspRing ->setChecked(CpBase.CentralRing);
    CaprGlyph->setChecked(CpBase.EuropCapr);
    UranGlyph->setChecked(CpBase.EuropUran);
    PlutoGlyph->setChecked(CpBase.EuropPlut);
    SortAspectsList->setChecked(CpBase.SortAsp);
    PlanetsRank->setChecked(CpBase.PlanetsRank);
    RiseSet->setChecked(CpBase.RiseSet);
    GlobEclipse->setChecked(CpBase.GlobEclipse);
    AspectsConf->setChecked(CpBase.AspectsConfig);
    InverseBg->setChecked(CpBase.InvBack);
    Grid->setChecked(CpBase.Grid);
    Sabian->setChecked(CpBase.Sabian);
    Outlines->setChecked(CpBase.Outlines);
    PlanetHour->setChecked(CpBase.PlanetHour);
    Comment->setChecked(CpBase.DisplayComment);
    Apsides->setChecked(CpBase.Apsides);
    Parts->setChecked(CpBase.ArabicParts);
    Interpretation->setChecked(CpBase.Interpretation);
    InterpretTrans->setChecked(CpBase.InterpretTrans);
    Sectors->setChecked(CpBase.Sectors);
    for (int i = 0; i < 5; i++)
        SubringBox->addItem(*Asr->SubringsNames[i]);
    SubringBox->setCurrentIndex(CpBase.Subring);
}

/*
 *  Destroys the object and frees any allocated resources
 */
EditChartParms::~EditChartParms()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void EditChartParms::on_OkButton_clicked()
{
    CpBase.DynamicResize = DynamicResize->isChecked();
    CpBase.LeftAscendant = LeftAscendant->isChecked();
    CpBase.Sidebars      = Sidebars->isChecked();
    CpBase.AspectsFrame = AspectsFrame->isChecked();
    CpBase.DisplayMidPoints = DisplayMidPoints->isChecked();
    CpBase.DisplaySeconds = DisplaySeconds->isChecked();
    CpBase.CentralRing = AspRing ->isChecked();
    CpBase.EuropCapr = CaprGlyph->isChecked();
    CpBase.EuropUran = UranGlyph->isChecked();
    CpBase.EuropPlut = PlutoGlyph->isChecked();
    CpBase.SortAsp   = SortAspectsList->isChecked();
    CpBase.PlanetsRank = PlanetsRank->isChecked();
    CpBase.RiseSet     = RiseSet->isChecked();
    CpBase.GlobEclipse = GlobEclipse->isChecked();
    CpBase.AspectsConfig = AspectsConf->isChecked();
    CpBase.InvBack = InverseBg->isChecked();
    CpBase.Grid    = Grid->isChecked();
    CpBase.Sabian  = Sabian->isChecked();
    CpBase.Outlines= Outlines->isChecked();
    CpBase.PlanetHour = PlanetHour->isChecked();
    CpBase.DisplayComment = Comment->isChecked();
    CpBase.Apsides = Apsides->isChecked();
    CpBase.ArabicParts = Parts->isChecked();
    CpBase.Interpretation = Interpretation->isChecked();
    CpBase.InterpretTrans = InterpretTrans->isChecked();
    CpBase.Sectors        = Sectors->isChecked();
    CpBase.Subring   = (enum Subring)SubringBox->currentIndex();
    *Cp = CpBase;
    emit accept();
}
/*
 * public slot
 */
void EditChartParms::on_CancelButton_clicked()
{
    emit reject();
}

void EditChartParms::SubringSlot(int i)
{
    CpBase.Subring = (enum Subring)i;
}
