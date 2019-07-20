/****************************************************************************
** Meta object code from reading C++ file 'scanspan.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/scanspan.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanspan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditScanSpan_t {
    QByteArrayData data[4];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditScanSpan_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditScanSpan_t qt_meta_stringdata_EditScanSpan = {
    {
QT_MOC_LITERAL(0, 0, 12), // "EditScanSpan"
QT_MOC_LITERAL(1, 13, 10), // "ButtonSlot"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 19) // "on_OkButton_clicked"

    },
    "EditScanSpan\0ButtonSlot\0\0on_OkButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditScanSpan[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       3,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void EditScanSpan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditScanSpan *_t = static_cast<EditScanSpan *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ButtonSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_OkButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject EditScanSpan::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditScanSpan.data,
      qt_meta_data_EditScanSpan,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditScanSpan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditScanSpan::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditScanSpan.stringdata0))
        return static_cast<void*>(const_cast< EditScanSpan*>(this));
    if (!strcmp(_clname, "Ui_EditScanSpan"))
        return static_cast< Ui_EditScanSpan*>(const_cast< EditScanSpan*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditScanSpan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
