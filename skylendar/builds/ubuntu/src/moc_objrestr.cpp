/****************************************************************************
** Meta object code from reading C++ file 'objrestr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/objrestr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objrestr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ObjRestr_t {
    QByteArrayData data[6];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObjRestr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObjRestr_t qt_meta_stringdata_ObjRestr = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ObjRestr"
QT_MOC_LITERAL(1, 9, 23), // "on_IsRestricted_toggled"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 22), // "on_OrbAdd_valueChanged"
QT_MOC_LITERAL(4, 57, 25), // "on_Influence_valueChanged"
QT_MOC_LITERAL(5, 83, 10) // "IfRestrict"

    },
    "ObjRestr\0on_IsRestricted_toggled\0\0"
    "on_OrbAdd_valueChanged\0on_Influence_valueChanged\0"
    "IfRestrict"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjRestr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       3,    1,   37,    2, 0x0a /* Public */,
       4,    1,   40,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Bool,

       0        // eod
};

void ObjRestr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ObjRestr *_t = static_cast<ObjRestr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_IsRestricted_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_OrbAdd_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->on_Influence_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: { bool _r = _t->IfRestrict();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject ObjRestr::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ObjRestr.data,
      qt_meta_data_ObjRestr,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ObjRestr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjRestr::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ObjRestr.stringdata0))
        return static_cast<void*>(const_cast< ObjRestr*>(this));
    if (!strcmp(_clname, "Ui_ObjRestr"))
        return static_cast< Ui_ObjRestr*>(const_cast< ObjRestr*>(this));
    return QWidget::qt_metacast(_clname);
}

int ObjRestr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_ObjRestList_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObjRestList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObjRestList_t qt_meta_stringdata_ObjRestList = {
    {
QT_MOC_LITERAL(0, 0, 11) // "ObjRestList"

    },
    "ObjRestList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjRestList[] = {

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

void ObjRestList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ObjRestList::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_ObjRestList.data,
      qt_meta_data_ObjRestList,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ObjRestList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjRestList::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ObjRestList.stringdata0))
        return static_cast<void*>(const_cast< ObjRestList*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int ObjRestList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
