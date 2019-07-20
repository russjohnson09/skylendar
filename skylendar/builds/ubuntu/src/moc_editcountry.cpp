/****************************************************************************
** Meta object code from reading C++ file 'editcountry.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/editcountry.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editcountry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditCountry_t {
    QByteArrayData data[10];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditCountry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditCountry_t qt_meta_stringdata_EditCountry = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EditCountry"
QT_MOC_LITERAL(1, 12, 7), // "Clicked"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 38, 23), // "on_DeleteButton_clicked"
QT_MOC_LITERAL(5, 62, 23), // "on_ModifyButton_clicked"
QT_MOC_LITERAL(6, 86, 20), // "on_NewButton_clicked"
QT_MOC_LITERAL(7, 107, 19), // "on_OkButton_clicked"
QT_MOC_LITERAL(8, 127, 23), // "on_SearchButton_clicked"
QT_MOC_LITERAL(9, 151, 25) // "on_FileListButton_clicked"

    },
    "EditCountry\0Clicked\0\0QTreeWidgetItem*\0"
    "on_DeleteButton_clicked\0on_ModifyButton_clicked\0"
    "on_NewButton_clicked\0on_OkButton_clicked\0"
    "on_SearchButton_clicked\0"
    "on_FileListButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditCountry[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x0a /* Public */,
       4,    0,   54,    2, 0x0a /* Public */,
       5,    0,   55,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,
       8,    0,   58,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditCountry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditCountry *_t = static_cast<EditCountry *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_DeleteButton_clicked(); break;
        case 2: _t->on_ModifyButton_clicked(); break;
        case 3: _t->on_NewButton_clicked(); break;
        case 4: _t->on_OkButton_clicked(); break;
        case 5: _t->on_SearchButton_clicked(); break;
        case 6: _t->on_FileListButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject EditCountry::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditCountry.data,
      qt_meta_data_EditCountry,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditCountry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditCountry::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditCountry.stringdata0))
        return static_cast<void*>(const_cast< EditCountry*>(this));
    if (!strcmp(_clname, "Ui_EditCountry"))
        return static_cast< Ui_EditCountry*>(const_cast< EditCountry*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditCountry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
