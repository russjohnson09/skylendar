/****************************************************************************
** Meta object code from reading C++ file 'astromainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/astromainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'astromainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AstroAbout_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AstroAbout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AstroAbout_t qt_meta_stringdata_AstroAbout = {
    {
QT_MOC_LITERAL(0, 0, 10) // "AstroAbout"

    },
    "AstroAbout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AstroAbout[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void AstroAbout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject AstroAbout::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AstroAbout.data,
      qt_meta_data_AstroAbout,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AstroAbout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AstroAbout::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AstroAbout.stringdata0))
        return static_cast<void*>(const_cast< AstroAbout*>(this));
    if (!strcmp(_clname, "Ui_About"))
        return static_cast< Ui_About*>(const_cast< AstroAbout*>(this));
    return QWidget::qt_metacast(_clname);
}

int AstroAbout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_AstroMainWindow_t {
    QByteArrayData data[60];
    char stringdata0[610];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AstroMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AstroMainWindow_t qt_meta_stringdata_AstroMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "AstroMainWindow"
QT_MOC_LITERAL(1, 16, 7), // "NewData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "Read"
QT_MOC_LITERAL(4, 30, 5), // "Write"
QT_MOC_LITERAL(5, 36, 11), // "SetOwnTitle"
QT_MOC_LITERAL(6, 48, 13), // "SearchForData"
QT_MOC_LITERAL(7, 62, 13), // "SearchForRest"
QT_MOC_LITERAL(8, 76, 14), // "SearchForChart"
QT_MOC_LITERAL(9, 91, 15), // "NewRestrictions"
QT_MOC_LITERAL(10, 107, 13), // "StandardChart"
QT_MOC_LITERAL(11, 121, 15), // "ObjectListChart"
QT_MOC_LITERAL(12, 137, 13), // "TextListChart"
QT_MOC_LITERAL(13, 151, 17), // "LocalHorizonChart"
QT_MOC_LITERAL(14, 169, 17), // "AspectsTableChart"
QT_MOC_LITERAL(15, 187, 12), // "SquaredChart"
QT_MOC_LITERAL(16, 200, 11), // "SolarSystem"
QT_MOC_LITERAL(17, 212, 12), // "TarotsSpread"
QT_MOC_LITERAL(18, 225, 10), // "EditParams"
QT_MOC_LITERAL(19, 236, 12), // "EditDefParms"
QT_MOC_LITERAL(20, 249, 13), // "EditCountries"
QT_MOC_LITERAL(21, 263, 6), // "Export"
QT_MOC_LITERAL(22, 270, 9), // "SaveChart"
QT_MOC_LITERAL(23, 280, 4), // "Quit"
QT_MOC_LITERAL(24, 285, 4), // "Tile"
QT_MOC_LITERAL(25, 290, 7), // "Cascade"
QT_MOC_LITERAL(26, 298, 4), // "Edit"
QT_MOC_LITERAL(27, 303, 6), // "Delete"
QT_MOC_LITERAL(28, 310, 4), // "Save"
QT_MOC_LITERAL(29, 315, 9), // "Duplicate"
QT_MOC_LITERAL(30, 325, 9), // "DupWindow"
QT_MOC_LITERAL(31, 335, 15), // "DisplayDataTree"
QT_MOC_LITERAL(32, 351, 8), // "DupnDrop"
QT_MOC_LITERAL(33, 360, 10), // "ButtonType"
QT_MOC_LITERAL(34, 371, 5), // "Print"
QT_MOC_LITERAL(35, 377, 7), // "Preview"
QT_MOC_LITERAL(36, 385, 5), // "Close"
QT_MOC_LITERAL(37, 391, 12), // "AstroWindow*"
QT_MOC_LITERAL(38, 404, 9), // "Increment"
QT_MOC_LITERAL(39, 414, 9), // "Decrement"
QT_MOC_LITERAL(40, 424, 9), // "AnimOnOff"
QT_MOC_LITERAL(41, 434, 7), // "InvAnim"
QT_MOC_LITERAL(42, 442, 13), // "InvBackground"
QT_MOC_LITERAL(43, 456, 9), // "BackImage"
QT_MOC_LITERAL(44, 466, 8), // "Previous"
QT_MOC_LITERAL(45, 475, 4), // "Next"
QT_MOC_LITERAL(46, 480, 4), // "SetX"
QT_MOC_LITERAL(47, 485, 5), // "About"
QT_MOC_LITERAL(48, 491, 3), // "Doc"
QT_MOC_LITERAL(49, 495, 8), // "Finished"
QT_MOC_LITERAL(50, 504, 14), // "QNetworkReply*"
QT_MOC_LITERAL(51, 519, 2), // "Jr"
QT_MOC_LITERAL(52, 522, 8), // "QAction*"
QT_MOC_LITERAL(53, 531, 2), // "Jb"
QT_MOC_LITERAL(54, 534, 11), // "WinListSlot"
QT_MOC_LITERAL(55, 546, 15), // "WindowActivated"
QT_MOC_LITERAL(56, 562, 14), // "QMdiSubWindow*"
QT_MOC_LITERAL(57, 577, 9), // "Triggered"
QT_MOC_LITERAL(58, 587, 12), // "PaintPreview"
QT_MOC_LITERAL(59, 600, 9) // "QPrinter*"

    },
    "AstroMainWindow\0NewData\0\0Read\0Write\0"
    "SetOwnTitle\0SearchForData\0SearchForRest\0"
    "SearchForChart\0NewRestrictions\0"
    "StandardChart\0ObjectListChart\0"
    "TextListChart\0LocalHorizonChart\0"
    "AspectsTableChart\0SquaredChart\0"
    "SolarSystem\0TarotsSpread\0EditParams\0"
    "EditDefParms\0EditCountries\0Export\0"
    "SaveChart\0Quit\0Tile\0Cascade\0Edit\0"
    "Delete\0Save\0Duplicate\0DupWindow\0"
    "DisplayDataTree\0DupnDrop\0ButtonType\0"
    "Print\0Preview\0Close\0AstroWindow*\0"
    "Increment\0Decrement\0AnimOnOff\0InvAnim\0"
    "InvBackground\0BackImage\0Previous\0Next\0"
    "SetX\0About\0Doc\0Finished\0QNetworkReply*\0"
    "Jr\0QAction*\0Jb\0WinListSlot\0WindowActivated\0"
    "QMdiSubWindow*\0Triggered\0PaintPreview\0"
    "QPrinter*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AstroMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      54,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  284,    2, 0x0a /* Public */,
       3,    0,  285,    2, 0x0a /* Public */,
       4,    0,  286,    2, 0x0a /* Public */,
       5,    0,  287,    2, 0x0a /* Public */,
       6,    0,  288,    2, 0x0a /* Public */,
       7,    0,  289,    2, 0x0a /* Public */,
       8,    0,  290,    2, 0x0a /* Public */,
       9,    0,  291,    2, 0x0a /* Public */,
      10,    0,  292,    2, 0x0a /* Public */,
      11,    0,  293,    2, 0x0a /* Public */,
      12,    0,  294,    2, 0x0a /* Public */,
      13,    0,  295,    2, 0x0a /* Public */,
      14,    0,  296,    2, 0x0a /* Public */,
      15,    0,  297,    2, 0x0a /* Public */,
      16,    0,  298,    2, 0x0a /* Public */,
      17,    0,  299,    2, 0x0a /* Public */,
      18,    0,  300,    2, 0x0a /* Public */,
      19,    0,  301,    2, 0x0a /* Public */,
      20,    0,  302,    2, 0x0a /* Public */,
      21,    0,  303,    2, 0x0a /* Public */,
      22,    0,  304,    2, 0x0a /* Public */,
      23,    0,  305,    2, 0x0a /* Public */,
      24,    0,  306,    2, 0x0a /* Public */,
      25,    0,  307,    2, 0x0a /* Public */,
      26,    0,  308,    2, 0x0a /* Public */,
      27,    0,  309,    2, 0x0a /* Public */,
      28,    0,  310,    2, 0x0a /* Public */,
      29,    0,  311,    2, 0x0a /* Public */,
      30,    0,  312,    2, 0x0a /* Public */,
      31,    0,  313,    2, 0x0a /* Public */,
      32,    2,  314,    2, 0x0a /* Public */,
      34,    0,  319,    2, 0x0a /* Public */,
      35,    0,  320,    2, 0x0a /* Public */,
      36,    1,  321,    2, 0x0a /* Public */,
      38,    0,  324,    2, 0x0a /* Public */,
      39,    0,  325,    2, 0x0a /* Public */,
      40,    1,  326,    2, 0x0a /* Public */,
      41,    1,  329,    2, 0x0a /* Public */,
      42,    1,  332,    2, 0x0a /* Public */,
      43,    1,  335,    2, 0x0a /* Public */,
      44,    0,  338,    2, 0x0a /* Public */,
      45,    0,  339,    2, 0x0a /* Public */,
      46,    0,  340,    2, 0x0a /* Public */,
      47,    0,  341,    2, 0x0a /* Public */,
      48,    0,  342,    2, 0x0a /* Public */,
      49,    1,  343,    2, 0x0a /* Public */,
      51,    1,  346,    2, 0x0a /* Public */,
      51,    1,  349,    2, 0x0a /* Public */,
      53,    1,  352,    2, 0x0a /* Public */,
      53,    1,  355,    2, 0x0a /* Public */,
      54,    1,  358,    2, 0x0a /* Public */,
      55,    1,  361,    2, 0x08 /* Private */,
      57,    1,  364,    2, 0x08 /* Private */,
      58,    1,  367,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 37,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 50,    2,
    QMetaType::Void, 0x80000000 | 52,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 52,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 52,    2,
    QMetaType::Void, 0x80000000 | 56,    2,
    QMetaType::Void, 0x80000000 | 52,    2,
    QMetaType::Void, 0x80000000 | 59,    2,

       0        // eod
};

void AstroMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AstroMainWindow *_t = static_cast<AstroMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NewData(); break;
        case 1: _t->Read(); break;
        case 2: _t->Write(); break;
        case 3: _t->SetOwnTitle(); break;
        case 4: _t->SearchForData(); break;
        case 5: _t->SearchForRest(); break;
        case 6: _t->SearchForChart(); break;
        case 7: _t->NewRestrictions(); break;
        case 8: _t->StandardChart(); break;
        case 9: _t->ObjectListChart(); break;
        case 10: _t->TextListChart(); break;
        case 11: _t->LocalHorizonChart(); break;
        case 12: _t->AspectsTableChart(); break;
        case 13: _t->SquaredChart(); break;
        case 14: _t->SolarSystem(); break;
        case 15: _t->TarotsSpread(); break;
        case 16: _t->EditParams(); break;
        case 17: _t->EditDefParms(); break;
        case 18: _t->EditCountries(); break;
        case 19: _t->Export(); break;
        case 20: _t->SaveChart(); break;
        case 21: _t->Quit(); break;
        case 22: _t->Tile(); break;
        case 23: _t->Cascade(); break;
        case 24: _t->Edit(); break;
        case 25: _t->Delete(); break;
        case 26: _t->Save(); break;
        case 27: _t->Duplicate(); break;
        case 28: _t->DupWindow(); break;
        case 29: _t->DisplayDataTree(); break;
        case 30: _t->DupnDrop((*reinterpret_cast< ButtonType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 31: _t->Print(); break;
        case 32: _t->Preview(); break;
        case 33: _t->Close((*reinterpret_cast< AstroWindow*(*)>(_a[1]))); break;
        case 34: _t->Increment(); break;
        case 35: _t->Decrement(); break;
        case 36: _t->AnimOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->InvAnim((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->InvBackground((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->BackImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->Previous(); break;
        case 41: _t->Next(); break;
        case 42: _t->SetX(); break;
        case 43: _t->About(); break;
        case 44: _t->Doc(); break;
        case 45: _t->Finished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 46: _t->Jr((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 47: _t->Jr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->Jb((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 49: _t->Jb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->WinListSlot((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 51: _t->WindowActivated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 52: _t->Triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 53: _t->PaintPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 33:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AstroWindow* >(); break;
            }
            break;
        }
    }
}

const QMetaObject AstroMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AstroMainWindow.data,
      qt_meta_data_AstroMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AstroMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AstroMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AstroMainWindow.stringdata0))
        return static_cast<void*>(const_cast< AstroMainWindow*>(this));
    if (!strcmp(_clname, "AstroList<AstroWindow>"))
        return static_cast< AstroList<AstroWindow>*>(const_cast< AstroMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AstroMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 54)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 54;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 54)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 54;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
