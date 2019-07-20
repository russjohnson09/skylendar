/****************************************************************************
** Meta object code from reading C++ file 'searchrest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/searchrest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchrest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SearchRest_t {
    QByteArrayData data[7];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchRest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchRest_t qt_meta_stringdata_SearchRest = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SearchRest"
QT_MOC_LITERAL(1, 11, 23), // "on_CancelButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "Clicked"
QT_MOC_LITERAL(4, 44, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 61, 19), // "on_OkButton_clicked"
QT_MOC_LITERAL(6, 81, 23) // "on_SearchButton_clicked"

    },
    "SearchRest\0on_CancelButton_clicked\0\0"
    "Clicked\0QTreeWidgetItem*\0on_OkButton_clicked\0"
    "on_SearchButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchRest[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SearchRest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchRest *_t = static_cast<SearchRest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_CancelButton_clicked(); break;
        case 1: _t->Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_OkButton_clicked(); break;
        case 3: _t->on_SearchButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SearchRest::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SearchRest.data,
      qt_meta_data_SearchRest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchRest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchRest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchRest.stringdata0))
        return static_cast<void*>(const_cast< SearchRest*>(this));
    if (!strcmp(_clname, "Ui_SearchRest"))
        return static_cast< Ui_SearchRest*>(const_cast< SearchRest*>(this));
    return QDialog::qt_metacast(_clname);
}

int SearchRest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
