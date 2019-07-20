/****************************************************************************
** Meta object code from reading C++ file 'searchdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/searchdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SearchData_t {
    QByteArrayData data[20];
    char stringdata0[387];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchData_t qt_meta_stringdata_SearchData = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SearchData"
QT_MOC_LITERAL(1, 11, 11), // "ClickedSlot"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 41, 19), // "on_OkButton_clicked"
QT_MOC_LITERAL(5, 61, 11), // "ReqTypeSlot"
QT_MOC_LITERAL(6, 73, 23), // "on_SearchButton_clicked"
QT_MOC_LITERAL(7, 97, 23), // "on_CancelButton_clicked"
QT_MOC_LITERAL(8, 121, 20), // "on_ANDButton_clicked"
QT_MOC_LITERAL(9, 142, 20), // "on_Aspects_activated"
QT_MOC_LITERAL(10, 163, 20), // "on_Planets_activated"
QT_MOC_LITERAL(11, 184, 20), // "on_NOTButton_clicked"
QT_MOC_LITERAL(12, 205, 19), // "on_ORButton_clicked"
QT_MOC_LITERAL(13, 225, 21), // "on_TAspButton_clicked"
QT_MOC_LITERAL(14, 247, 23), // "on_THouseButton_clicked"
QT_MOC_LITERAL(15, 271, 21), // "on_TObjButton_clicked"
QT_MOC_LITERAL(16, 293, 22), // "on_TRestButton_clicked"
QT_MOC_LITERAL(17, 316, 21), // "on_SiblButton_clicked"
QT_MOC_LITERAL(18, 338, 23), // "on_DeleteButton_clicked"
QT_MOC_LITERAL(19, 362, 24) // "on_DumpValButton_clicked"

    },
    "SearchData\0ClickedSlot\0\0QTreeWidgetItem*\0"
    "on_OkButton_clicked\0ReqTypeSlot\0"
    "on_SearchButton_clicked\0on_CancelButton_clicked\0"
    "on_ANDButton_clicked\0on_Aspects_activated\0"
    "on_Planets_activated\0on_NOTButton_clicked\0"
    "on_ORButton_clicked\0on_TAspButton_clicked\0"
    "on_THouseButton_clicked\0on_TObjButton_clicked\0"
    "on_TRestButton_clicked\0on_SiblButton_clicked\0"
    "on_DeleteButton_clicked\0"
    "on_DumpValButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x0a /* Public */,
       4,    0,  102,    2, 0x0a /* Public */,
       5,    1,  103,    2, 0x0a /* Public */,
       6,    0,  106,    2, 0x0a /* Public */,
       7,    0,  107,    2, 0x0a /* Public */,
       8,    0,  108,    2, 0x0a /* Public */,
       9,    1,  109,    2, 0x0a /* Public */,
      10,    1,  112,    2, 0x0a /* Public */,
      11,    0,  115,    2, 0x0a /* Public */,
      12,    0,  116,    2, 0x0a /* Public */,
      13,    0,  117,    2, 0x0a /* Public */,
      14,    0,  118,    2, 0x0a /* Public */,
      15,    0,  119,    2, 0x0a /* Public */,
      16,    0,  120,    2, 0x0a /* Public */,
      17,    0,  121,    2, 0x0a /* Public */,
      18,    0,  122,    2, 0x0a /* Public */,
      19,    0,  123,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SearchData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchData *_t = static_cast<SearchData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ClickedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->on_OkButton_clicked(); break;
        case 2: _t->ReqTypeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_SearchButton_clicked(); break;
        case 4: _t->on_CancelButton_clicked(); break;
        case 5: _t->on_ANDButton_clicked(); break;
        case 6: _t->on_Aspects_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_Planets_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_NOTButton_clicked(); break;
        case 9: _t->on_ORButton_clicked(); break;
        case 10: _t->on_TAspButton_clicked(); break;
        case 11: _t->on_THouseButton_clicked(); break;
        case 12: _t->on_TObjButton_clicked(); break;
        case 13: _t->on_TRestButton_clicked(); break;
        case 14: _t->on_SiblButton_clicked(); break;
        case 15: _t->on_DeleteButton_clicked(); break;
        case 16: _t->on_DumpValButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SearchData::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SearchData.data,
      qt_meta_data_SearchData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchData.stringdata0))
        return static_cast<void*>(const_cast< SearchData*>(this));
    if (!strcmp(_clname, "Ui_SearchData"))
        return static_cast< Ui_SearchData*>(const_cast< SearchData*>(this));
    return QDialog::qt_metacast(_clname);
}

int SearchData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
