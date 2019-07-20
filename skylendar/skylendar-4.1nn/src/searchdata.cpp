#include "searchdata.h"
#include "astroparams.h"
#include "astroutils.h"
#include "astromainwindow.h"
#include <QButtonGroup>
#include <QTextCursor>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <cstdio>

extern AstroMainWindow* Amw;

/*
 *  Constructs a SearchData which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
SearchData::SearchData()
{
    SQLReqType = 0;
    Qbg = new QButtonGroup(this);
    setupUi(this);
    Qbg->addButton(ByNameButton, 0);
    Qbg->addButton(ByStatementButton, 1);
    Qbg->addButton(ByVDVButton, 2);
    emit ByNameButton->setChecked(true);
    connect(Qbg, SIGNAL(buttonClicked(int)), this, SLOT(ReqTypeSlot(int)));
    ShowBtn(false);
#ifdef SHARED
		DataLIST->headerItem()->setText(3, i18n("Owner"));
		DataLIST->headerItem()->setText(4, i18n("Access"));
#endif
    DataLIST->setIndentation(0);
    DataLIST->setSelectionMode(QAbstractItemView::MultiSelection);
    for (int i = Sun; i < OBJNB -1; i++)
        Planets->addItem(*Asr->ObjNames[i], i);
    for (int i = 0; i < NbStars; i++)
        Planets->addItem(*Asr->StaNames[i].Name, i + OBJNB -1);
    for (int i = Conjunction; i < Unknown_Aspect; i++)
        Aspects->addItem(*Asr->AspectNames[i], i);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SearchData::~SearchData()
{
    // no need to delete child widgets MoveBackward, Qt does it all for us
}

/*
 * public slot
 */
void SearchData::ClickedSlot(QTreeWidgetItem*)
{
}
/*
 * public slot
 */
void SearchData::on_OkButton_clicked()
{
    auto sa = SC(SearchItem*, DataLIST->topLevelItem(0));
    for (; sa; sa = SC(SearchItem*, DataLIST->itemBelow(sa)))
    {
        if (sa->isSelected() && !Adl->Get(sa->Idx))
        {
            auto ad = new AstroData;
            ad->DbFetch(sa->Idx);
            Amw->Aiw->AddData(ad);
        }
    }
    emit accept();
}
/*
 * public slot
 */
void SearchData::ReqTypeSlot(int i)
{
    SQLReqType = i;
    ShowBtn(i == 2);
}
/*
 * public slot
 */
void SearchData::on_SearchButton_clicked()
{
    int i;
    bool r, b = false;
    AstroString as, val = ReqLine->toPlainText(), t = "Data", cmd = 
#ifdef SHARED
			"SELECT Uname(%a.uid) AS Own, %a.r AS Acc, %a.Name AS DName, %a.Idx AS Dix, EXTRACT(YEAR FROM BirthDay) AS Year, EXTRACT(MONTH FROM Birthday) AS Month, EXTRACT(DAY FROM Birthday) AS Day, ChartType, Place.Name AS PName FROM %a JOIN Place ON %a.PlaceIdx = Place.Idx WHERE (";
#else
		"SELECT %a.Name AS DName, %a.Idx AS Dix, EXTRACT(YEAR FROM BirthDay) AS Year, EXTRACT(MONTH FROM Birthday) AS Month, EXTRACT(DAY FROM Birthday) AS Day, ChartType, Place.Name AS PName FROM %a JOIN Place ON %a.PlaceIdx = Place.Idx WHERE (";
#endif
    switch (SQLReqType)
    {
    case 0:
        cmd += val.isEmpty() ? "Data.Name LIKE E'\\%' " : "Data.Name ~* '%a'";
        if (!val.isEmpty()) b = true;
        break;
    case 2:
        t = "VDV";
    case 1:
        cmd += "%A";
        b = true;
        break;
    };
    cmd += ") AND substr(%a.Name, 1, 1) <> '#' ORDER BY %a.Name";
#ifdef SHARED
    r = b ? Arq.Exec(cmd.toUtf8().data(), &t, &t, &t, &t, &t, &t, &val, &t, &t) : Arq.Exec(cmd.toUtf8().data(), &t, &t, &t, &t, &t, &t, &t, &t);
#else
		r = b ? Arq.Exec(cmd.toUtf8().data(), &t, &t, &t, &t, &val, &t, &t) : Arq.Exec(cmd.toUtf8().data(), &t, &t, &t, &t, &t, &t);
#endif
    if (!r)
    {
        AstroMessage(i18n("Can't fetch data !"));
        return;
    }
    DataLIST->clear();
    i = 0;
    val = i;
    emit Count->setText(val);
    if (Arq.Valid()) do
        {
            Sprintf("%d/%d/%d", &as, Arq.GetInt("Year"), Arq.GetInt("Month"), Arq.GetInt("Day"));
            (void)new SearchItem(DataLIST, Arq.GetInt("Dix"), Arq < "Dname", as, Arq < "PName", *(*Ail)[Arq.GetInt("ChartType")]
#ifdef SHARED
						, Arq < "Own", Arq < "Acc"
#endif
						);
            val = ++i;
            emit Count->setText(val);
        }
        while (Arq.Next());
    DataLIST->resizeColumnToContents(0);
}
/*
 * public slot
 */
void SearchData::on_CancelButton_clicked()
{
    emit reject();
}

SearchItem::SearchItem(QTreeWidget* parent, Index idx, const AstroString& name, const AstroString& date, const AstroString& place, const AstroIcon& icon
#ifdef SHARED
		 , const AstroString& owner, const AstroString& access
#endif
		 ): QTreeWidgetItem (parent)
{
    setText(0, name);
    setText(1, date);
    setText(2, place);
    Idx = idx;
    setIcon(0, icon);
#ifdef SHARED
		setText(3, owner);
		setText(4, access);
#endif
}

void SearchData::Insert(const QString& qs, int pos)
{
    int paf, idf;
    QTextCursor qc = ReqLine->textCursor();
    /*ReqLine->getCursorPosition(&paf, &idf);
    emit ReqLine->insertAt(qs, paf, idf);
    emit ReqLine->setCursorPosition(paf, qs.length() + idf + pos);*/
    emit ReqLine->insertPlainText(qs);
    qc.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, pos);
    ReqLine->setTextCursor(qc);
}

void SearchData::on_ANDButton_clicked()
{
    Insert("AND ");
}

void SearchData::on_Aspects_activated(int i)
{
    QString qs("\'");
    qs += *Asr->AspectShortNames[i];
    qs += "\', ";
    Insert(qs);
}

void SearchData::on_Planets_activated(int i)
{
    QString qs("\'");
    qs += (i > OBJNB - 2) ? *Asr->StaNames[i - OBJNB + 1].SName : *Asr->ObjShortNames[i];
    qs += "\', ";
    Insert(qs);
}


void SearchData::on_NOTButton_clicked()
{
    Insert("NOT ");
}

void SearchData::on_ORButton_clicked()
{
    Insert("OR ");
}

void SearchData::on_TAspButton_clicked()
{
    Insert("TAsp(DataIdx, ) ", -2);
}

void SearchData::on_THouseButton_clicked()
{
    Insert("THouse(DataIdx, ) ", -2);
}

void SearchData::on_TObjButton_clicked()
{
    Insert("TObj(DataIdx, ) ", -2);
}

void SearchData::on_TRestButton_clicked()
{
    Insert("TRest(DataIdx, ) ", -2);
}

void SearchData::ShowBtn(bool b)
{
    Planets->setEnabled(b);
    Aspects->setEnabled(b);
    TObjButton->setEnabled(b);
    TAspButton->setEnabled(b);
    TRestButton->setEnabled(b);
    THouseButton->setEnabled(b);
    ANDButton->setEnabled(b);
    ORButton->setEnabled(b);
    NOTButton->setEnabled(b);
}

void SearchData::on_SiblButton_clicked()
{
    int i, idx, cnt = 0;
    QString qs;
    auto sa = SC(SearchItem*, DataLIST->topLevelItem(0));
    for (; sa; sa = SC(SearchItem*,DataLIST->itemBelow(sa) ))
        if (sa->isSelected()) cnt++;
    if (cnt != 1)
    {
        AstroMessage(i18n("You must click on 1 dataset"));
        return;
    }
    for (sa = SC(SearchItem*, DataLIST->topLevelItem(0)); sa; sa = SC(SearchItem*, DataLIST->itemBelow(sa)))
        if (sa->isSelected()) break;
    idx = sa->Idx;
    if (!Arq.Exec("SELECT VDV.Name AS DName, VDV.Idx AS Dix, BirthDay, ChartType, Place.Name AS PName FROM VDV JOIN Place ON VDV.PlaceIdx = Place.Idx WHERE RefIdx IN (SELECT Idx FROM Data WHERE Idx = %d) AND VDV.Idx <> RefIdx ORDER BY VDV.Name", idx))
    {
        AstroMessage(i18n("Can't fetch data !"));
        return;
    }
    DataLIST->clear();
    i = 0;
    qs.setNum(i);
    emit Count->setText(qs);
    if (Arq.Valid()) do
        {
            (void)new SearchItem(DataLIST, Arq.GetInt("Dix"), Arq < "Dname", Arq < "BirthDay", Arq < "PName", *(*Ail)[Arq.GetInt("ChartType")]);
            qs.setNum(++i);
            emit Count->setText(qs);
        }
        while (Arq.Next());
}

void SearchData::on_DeleteButton_clicked()
{
    auto sa = SC(SearchItem*, DataLIST->topLevelItem(0));
#ifdef IFEXCEPT
    Arq.SetException(true);
    try
    {
#endif
        switch (AstroQuestion3(i18n("This Operation is DANGEROUS !!!\nIf YES, the listed DataSets and their associated values will be erased.\nIf NO, only the associated values will be erased.\nIf Cancel, the operation is cancelled.")))
        {
        case 0:
            return;
        case 1:
            Arq.Begin();
            for (; sa; sa = SC(SearchItem*, DataLIST->itemBelow(sa)))
            {
                Arq.Exec("DELETE FROM VData WHERE DataIdx = %d", sa->Idx);
                if (Amw->Aiw->DeleteIdx(sa->Idx))
                    Adl->RemoveFromDb(sa->Idx);
            }
            Arq.Commit();
            DataLIST->clear();
            break;
        case 2:
            Arq.Begin();
            for (; sa; sa = SC(SearchItem*, DataLIST->itemBelow(sa)))
                Arq.Exec("DELETE FROM VData WHERE DataIdx = %d", sa->Idx);
            Arq.Commit();
            break;
        default:
            ;
        }
#ifdef IFEXCEPT
    }
    catch (AstroException& ae)
    {
        Arq.Rollback();
        Exception(ae);
    }
#endif
    Arq.SetException(false);
}

void SearchData::on_DumpValButton_clicked()
{
    if (!AstroQuestion(i18n("Do you want to Extract & Save the values from all the displayed Datasets ?\n(Default restriction set used)"))) return;
    AstroChart ac;
    ac.SetCt(NullChart);
    AstroData ad;
    QString qs;
    AstroFoundAspectsList afal;
    bool cn;
    ad.Automatic = false;
    ac.Cbp->PlanetsRank = true;
    auto sa = SC(SearchItem*, DataLIST->topLevelItem(0));
    const AstroAspects aa(Drs);
    for (int i = 0; sa; sa = SC(SearchItem*, DataLIST->itemBelow(sa)))
    {
        if (Arq.Exec("SELECT Idx FROM Data WHERE Idx = %d", sa->Idx) && Arq.Valid())
        {
            Index Idx = Arq.GetInt("Idx");
            if (ad.DbFetch(Idx))
            {
                ac.SetData(&ad, 0);
                ac.Display();
                ac[0]->Modified = false;

                afal.GetAspects(aa, *ac[0], *ac[0], MPa);
                ac[0]->GetPlanetsRank(&afal);
                ac.ExtractandSave(0, Idx, cn, &afal);
                qs.setNum(++i);
                emit Count->setText(qs);
            }
        }
        P;
    }
}

