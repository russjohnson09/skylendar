/****************************************************************************
** Meta object code from reading C++ file 'skydmin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/skydmin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skydmin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SkyDmin_t {
    QByteArrayData data[17];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SkyDmin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SkyDmin_t qt_meta_stringdata_SkyDmin = {
    {
QT_MOC_LITERAL(0, 0, 7), // "SkyDmin"
QT_MOC_LITERAL(1, 8, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "on_LoginButton_clicked"
QT_MOC_LITERAL(4, 60, 17), // "on_Insert_clicked"
QT_MOC_LITERAL(5, 78, 12), // "UpdateAccess"
QT_MOC_LITERAL(6, 91, 11), // "QSqlRecord&"
QT_MOC_LITERAL(7, 103, 17), // "on_Delete_clicked"
QT_MOC_LITERAL(8, 121, 24), // "on_InstallButton_clicked"
QT_MOC_LITERAL(9, 146, 26), // "on_UninstallButton_clicked"
QT_MOC_LITERAL(10, 173, 24), // "on_DeleteSources_clicked"
QT_MOC_LITERAL(11, 198, 22), // "on_DownloadSe1_clicked"
QT_MOC_LITERAL(12, 221, 24), // "on_DownloadAster_clicked"
QT_MOC_LITERAL(13, 246, 7), // "Clicked"
QT_MOC_LITERAL(14, 254, 8), // "Progress"
QT_MOC_LITERAL(15, 263, 13), // "bytesReceived"
QT_MOC_LITERAL(16, 277, 10) // "bytesTotal"

    },
    "SkyDmin\0on_tabWidget_currentChanged\0"
    "\0on_LoginButton_clicked\0on_Insert_clicked\0"
    "UpdateAccess\0QSqlRecord&\0on_Delete_clicked\0"
    "on_InstallButton_clicked\0"
    "on_UninstallButton_clicked\0"
    "on_DeleteSources_clicked\0"
    "on_DownloadSe1_clicked\0on_DownloadAster_clicked\0"
    "Clicked\0Progress\0bytesReceived\0"
    "bytesTotal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SkyDmin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       3,    0,   77,    2, 0x0a /* Public */,
       4,    0,   78,    2, 0x0a /* Public */,
       5,    2,   79,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    1,   90,    2, 0x0a /* Public */,
      14,    2,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   15,   16,

       0        // eod
};

void SkyDmin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SkyDmin *_t = static_cast<SkyDmin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_LoginButton_clicked(); break;
        case 2: _t->on_Insert_clicked(); break;
        case 3: _t->UpdateAccess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QSqlRecord(*)>(_a[2]))); break;
        case 4: _t->on_Delete_clicked(); break;
        case 5: _t->on_InstallButton_clicked(); break;
        case 6: _t->on_UninstallButton_clicked(); break;
        case 7: _t->on_DeleteSources_clicked(); break;
        case 8: _t->on_DownloadSe1_clicked(); break;
        case 9: _t->on_DownloadAster_clicked(); break;
        case 10: _t->Clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->Progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SkyDmin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SkyDmin.data,
      qt_meta_data_SkyDmin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SkyDmin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkyDmin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SkyDmin.stringdata0))
        return static_cast<void*>(const_cast< SkyDmin*>(this));
    if (!strcmp(_clname, "Ui_Skydmin"))
        return static_cast< Ui_Skydmin*>(const_cast< SkyDmin*>(this));
    return QDialog::qt_metacast(_clname);
}

int SkyDmin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
