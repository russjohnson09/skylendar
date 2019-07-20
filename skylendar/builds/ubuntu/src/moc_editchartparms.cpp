/****************************************************************************
** Meta object code from reading C++ file 'editchartparms.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/editchartparms.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editchartparms.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditChartParms_t {
    QByteArrayData data[5];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditChartParms_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditChartParms_t qt_meta_stringdata_EditChartParms = {
    {
QT_MOC_LITERAL(0, 0, 14), // "EditChartParms"
QT_MOC_LITERAL(1, 15, 19), // "on_OkButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 23), // "on_CancelButton_clicked"
QT_MOC_LITERAL(4, 60, 11) // "SubringSlot"

    },
    "EditChartParms\0on_OkButton_clicked\0\0"
    "on_CancelButton_clicked\0SubringSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditChartParms[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void EditChartParms::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditChartParms *_t = static_cast<EditChartParms *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_OkButton_clicked(); break;
        case 1: _t->on_CancelButton_clicked(); break;
        case 2: _t->SubringSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EditChartParms::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditChartParms.data,
      qt_meta_data_EditChartParms,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditChartParms::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditChartParms::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditChartParms.stringdata0))
        return static_cast<void*>(const_cast< EditChartParms*>(this));
    if (!strcmp(_clname, "Ui_EditChartParms"))
        return static_cast< Ui_EditChartParms*>(const_cast< EditChartParms*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditChartParms::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
