/****************************************************************************
** Meta object code from reading C++ file 'searchchart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/searchchart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchchart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SearchChart_t {
    QByteArrayData data[8];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchChart_t qt_meta_stringdata_SearchChart = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SearchChart"
QT_MOC_LITERAL(1, 12, 23), // "on_CancelButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "Clicked"
QT_MOC_LITERAL(4, 45, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 62, 19), // "on_OkButton_clicked"
QT_MOC_LITERAL(6, 82, 18), // "on_Destroy_clicked"
QT_MOC_LITERAL(7, 101, 23) // "on_SearchButton_clicked"

    },
    "SearchChart\0on_CancelButton_clicked\0"
    "\0Clicked\0QTreeWidgetItem*\0on_OkButton_clicked\0"
    "on_Destroy_clicked\0on_SearchButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchChart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    2,   40,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SearchChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchChart *_t = static_cast<SearchChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_CancelButton_clicked(); break;
        case 1: _t->Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_OkButton_clicked(); break;
        case 3: _t->on_Destroy_clicked(); break;
        case 4: _t->on_SearchButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SearchChart::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SearchChart.data,
      qt_meta_data_SearchChart,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchChart::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchChart.stringdata0))
        return static_cast<void*>(const_cast< SearchChart*>(this));
    if (!strcmp(_clname, "Ui_SearchChart"))
        return static_cast< Ui_SearchChart*>(const_cast< SearchChart*>(this));
    return QDialog::qt_metacast(_clname);
}

int SearchChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
