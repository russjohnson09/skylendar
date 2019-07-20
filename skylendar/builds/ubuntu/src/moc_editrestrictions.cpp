/****************************************************************************
** Meta object code from reading C++ file 'editrestrictions.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/editrestrictions.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editrestrictions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditRestrictions_t {
    QByteArrayData data[19];
    char stringdata0[397];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditRestrictions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditRestrictions_t qt_meta_stringdata_EditRestrictions = {
    {
QT_MOC_LITERAL(0, 0, 16), // "EditRestrictions"
QT_MOC_LITERAL(1, 17, 13), // "on_Ok_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "on_Cancel_clicked"
QT_MOC_LITERAL(4, 50, 22), // "on_ToggleExtra_toggled"
QT_MOC_LITERAL(5, 73, 23), // "on_ToggleHouses_toggled"
QT_MOC_LITERAL(6, 97, 22), // "on_ToggleStars_toggled"
QT_MOC_LITERAL(7, 120, 22), // "on_RestrictAll_clicked"
QT_MOC_LITERAL(8, 143, 21), // "on_ReleaseAll_clicked"
QT_MOC_LITERAL(9, 165, 21), // "on_InverseSel_clicked"
QT_MOC_LITERAL(10, 187, 24), // "on_ReleaseAllAsp_clicked"
QT_MOC_LITERAL(11, 212, 25), // "on_RestrictAllAsp_clicked"
QT_MOC_LITERAL(12, 238, 24), // "on_InverseSelAsp_clicked"
QT_MOC_LITERAL(13, 263, 22), // "on_ToggleMinor_toggled"
QT_MOC_LITERAL(14, 286, 21), // "on_Scores_itemClicked"
QT_MOC_LITERAL(15, 308, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(16, 325, 22), // "on_Values_valueChanged"
QT_MOC_LITERAL(17, 348, 24), // "on_MPOrbSub_valueChanged"
QT_MOC_LITERAL(18, 373, 23) // "on_Heliocentric_toggled"

    },
    "EditRestrictions\0on_Ok_clicked\0\0"
    "on_Cancel_clicked\0on_ToggleExtra_toggled\0"
    "on_ToggleHouses_toggled\0on_ToggleStars_toggled\0"
    "on_RestrictAll_clicked\0on_ReleaseAll_clicked\0"
    "on_InverseSel_clicked\0on_ReleaseAllAsp_clicked\0"
    "on_RestrictAllAsp_clicked\0"
    "on_InverseSelAsp_clicked\0"
    "on_ToggleMinor_toggled\0on_Scores_itemClicked\0"
    "QListWidgetItem*\0on_Values_valueChanged\0"
    "on_MPOrbSub_valueChanged\0"
    "on_Heliocentric_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditRestrictions[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    1,   96,    2, 0x0a /* Public */,
       5,    1,   99,    2, 0x0a /* Public */,
       6,    1,  102,    2, 0x0a /* Public */,
       7,    0,  105,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x0a /* Public */,
      10,    0,  108,    2, 0x0a /* Public */,
      11,    0,  109,    2, 0x0a /* Public */,
      12,    0,  110,    2, 0x0a /* Public */,
      13,    1,  111,    2, 0x0a /* Public */,
      14,    1,  114,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      17,    1,  120,    2, 0x0a /* Public */,
      18,    1,  123,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void EditRestrictions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditRestrictions *_t = static_cast<EditRestrictions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Ok_clicked(); break;
        case 1: _t->on_Cancel_clicked(); break;
        case 2: _t->on_ToggleExtra_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_ToggleHouses_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_ToggleStars_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_RestrictAll_clicked(); break;
        case 6: _t->on_ReleaseAll_clicked(); break;
        case 7: _t->on_InverseSel_clicked(); break;
        case 8: _t->on_ReleaseAllAsp_clicked(); break;
        case 9: _t->on_RestrictAllAsp_clicked(); break;
        case 10: _t->on_InverseSelAsp_clicked(); break;
        case 11: _t->on_ToggleMinor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_Scores_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->on_Values_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_MPOrbSub_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->on_Heliocentric_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EditRestrictions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditRestrictions.data,
      qt_meta_data_EditRestrictions,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditRestrictions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditRestrictions::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditRestrictions.stringdata0))
        return static_cast<void*>(const_cast< EditRestrictions*>(this));
    if (!strcmp(_clname, "Ui_EditObjRestr"))
        return static_cast< Ui_EditObjRestr*>(const_cast< EditRestrictions*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditRestrictions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
