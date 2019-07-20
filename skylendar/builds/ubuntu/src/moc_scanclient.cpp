/****************************************************************************
** Meta object code from reading C++ file 'scanclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/scanclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScanClient_t {
    QByteArrayData data[23];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanClient_t qt_meta_stringdata_ScanClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ScanClient"
QT_MOC_LITERAL(1, 11, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 27, 24), // "org.skylendar.scanclient"
QT_MOC_LITERAL(3, 52, 9), // "GetAspect"
QT_MOC_LITERAL(4, 62, 9), // "Q_NOREPLY"
QT_MOC_LITERAL(5, 72, 1), // "i"
QT_MOC_LITERAL(6, 74, 4), // "ipos"
QT_MOC_LITERAL(7, 79, 1), // "j"
QT_MOC_LITERAL(8, 81, 4), // "jpos"
QT_MOC_LITERAL(9, 86, 6), // "aspect"
QT_MOC_LITERAL(10, 93, 4), // "date"
QT_MOC_LITERAL(11, 98, 2), // "ap"
QT_MOC_LITERAL(12, 101, 11), // "GetMPAspect"
QT_MOC_LITERAL(13, 113, 3), // "pos"
QT_MOC_LITERAL(14, 117, 1), // "k"
QT_MOC_LITERAL(15, 119, 4), // "kpos"
QT_MOC_LITERAL(16, 124, 8), // "GetRetro"
QT_MOC_LITERAL(17, 133, 12), // "GetSignTrans"
QT_MOC_LITERAL(18, 146, 4), // "sign"
QT_MOC_LITERAL(19, 151, 12), // "GetDirection"
QT_MOC_LITERAL(20, 164, 8), // "converse"
QT_MOC_LITERAL(21, 173, 8), // "Progress"
QT_MOC_LITERAL(22, 182, 7) // "EndScan"

    },
    "ScanClient\0D-Bus Interface\0"
    "org.skylendar.scanclient\0GetAspect\0"
    "Q_NOREPLY\0i\0ipos\0j\0jpos\0aspect\0date\0"
    "ap\0GetMPAspect\0pos\0k\0kpos\0GetRetro\0"
    "GetSignTrans\0sign\0GetDirection\0converse\0"
    "Progress\0EndScan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanClient[] = {

 // content:
       7,       // revision
       0,       // classname
       1,   14, // classinfo
       8,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // slots: name, argc, parameters, tag, flags
       3,    7,   56,    4, 0x0a /* Public */,
       3,    6,   71,    4, 0x2a /* Public | MethodCloned */,
      12,    7,   84,    4, 0x0a /* Public */,
      16,    3,   99,    4, 0x0a /* Public */,
      17,    3,  106,    4, 0x0a /* Public */,
      19,    7,  113,    4, 0x0a /* Public */,
      21,    1,  128,    4, 0x0a /* Public */,
      22,    0,  131,    4, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double, QMetaType::Bool,    5,    6,    7,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double,    5,    6,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double,    5,    7,   13,   14,   15,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,    5,    6,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double,    5,   18,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double, QMetaType::Int, QMetaType::Double, QMetaType::Bool,    5,    6,    7,    8,    9,   10,   20,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void ScanClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScanClient *_t = static_cast<ScanClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetAspect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 1: _t->GetAspect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 2: _t->GetMPAspect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7]))); break;
        case 3: _t->GetRetro((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: _t->GetSignTrans((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->GetDirection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 6: _t->Progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->EndScan(); break;
        default: ;
        }
    }
}

const QMetaObject ScanClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScanClient.data,
      qt_meta_data_ScanClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScanClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScanClient.stringdata0))
        return static_cast<void*>(const_cast< ScanClient*>(this));
    return QObject::qt_metacast(_clname);
}

int ScanClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
