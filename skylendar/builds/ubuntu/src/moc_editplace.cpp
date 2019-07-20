/****************************************************************************
** Meta object code from reading C++ file 'editplace.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/editplace.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editplace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditPlace_t {
    QByteArrayData data[17];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditPlace_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditPlace_t qt_meta_stringdata_EditPlace = {
    {
QT_MOC_LITERAL(0, 0, 9), // "EditPlace"
QT_MOC_LITERAL(1, 10, 11), // "OffTzRecomp"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 23), // "on_DeleteButton_clicked"
QT_MOC_LITERAL(4, 47, 24), // "on_Altitude_valueChanged"
QT_MOC_LITERAL(5, 72, 24), // "on_PlaceName_textChanged"
QT_MOC_LITERAL(6, 97, 20), // "on_NewButton_clicked"
QT_MOC_LITERAL(7, 118, 23), // "on_ModifyButton_clicked"
QT_MOC_LITERAL(8, 142, 23), // "on_SearchButton_clicked"
QT_MOC_LITERAL(9, 166, 22), // "on_Country_highlighted"
QT_MOC_LITERAL(10, 189, 22), // "on_CleanButton_clicked"
QT_MOC_LITERAL(11, 212, 24), // "on_CountryButton_clicked"
QT_MOC_LITERAL(12, 237, 7), // "Clicked"
QT_MOC_LITERAL(13, 245, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(14, 262, 20), // "on_ExtSearch_clicked"
QT_MOC_LITERAL(15, 283, 7), // "gotData"
QT_MOC_LITERAL(16, 291, 8) // "gotError"

    },
    "EditPlace\0OffTzRecomp\0\0on_DeleteButton_clicked\0"
    "on_Altitude_valueChanged\0"
    "on_PlaceName_textChanged\0on_NewButton_clicked\0"
    "on_ModifyButton_clicked\0on_SearchButton_clicked\0"
    "on_Country_highlighted\0on_CleanButton_clicked\0"
    "on_CountryButton_clicked\0Clicked\0"
    "QTreeWidgetItem*\0on_ExtSearch_clicked\0"
    "gotData\0gotError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditPlace[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   85,    2, 0x0a /* Public */,
       4,    1,   86,    2, 0x0a /* Public */,
       5,    1,   89,    2, 0x0a /* Public */,
       6,    0,   92,    2, 0x0a /* Public */,
       7,    0,   93,    2, 0x0a /* Public */,
       8,    0,   94,    2, 0x0a /* Public */,
       9,    1,   95,    2, 0x0a /* Public */,
      10,    0,   98,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    2,  100,    2, 0x0a /* Public */,
      14,    0,  105,    2, 0x0a /* Public */,
      15,    2,  106,    2, 0x0a /* Public */,
      16,    3,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList, QMetaType::QVariant,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QVariant,    2,    2,    2,

       0        // eod
};

void EditPlace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditPlace *_t = static_cast<EditPlace *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OffTzRecomp(); break;
        case 1: _t->on_DeleteButton_clicked(); break;
        case 2: _t->on_Altitude_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_PlaceName_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_NewButton_clicked(); break;
        case 5: _t->on_ModifyButton_clicked(); break;
        case 6: _t->on_SearchButton_clicked(); break;
        case 7: _t->on_Country_highlighted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_CleanButton_clicked(); break;
        case 9: _t->on_CountryButton_clicked(); break;
        case 10: _t->Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->on_ExtSearch_clicked(); break;
        case 12: _t->gotData((*reinterpret_cast< const QList<QVariant>(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 13: _t->gotError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariant(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EditPlace::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EditPlace::OffTzRecomp)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject EditPlace::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EditPlace.data,
      qt_meta_data_EditPlace,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditPlace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditPlace::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditPlace.stringdata0))
        return static_cast<void*>(const_cast< EditPlace*>(this));
    if (!strcmp(_clname, "Ui_EditPlace"))
        return static_cast< Ui_EditPlace*>(const_cast< EditPlace*>(this));
    return QWidget::qt_metacast(_clname);
}

int EditPlace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void EditPlace::OffTzRecomp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
