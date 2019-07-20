/****************************************************************************
** Meta object code from reading C++ file 'astrowindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../skylendar-4.1nn/src/astrowindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'astrowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AstroPrintPage_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AstroPrintPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AstroPrintPage_t qt_meta_stringdata_AstroPrintPage = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AstroPrintPage"
QT_MOC_LITERAL(1, 15, 7), // "NewPage"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "AstroPrintPage\0NewPage\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AstroPrintPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AstroPrintPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AstroPrintPage *_t = static_cast<AstroPrintPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NewPage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AstroPrintPage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AstroPrintPage.data,
      qt_meta_data_AstroPrintPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AstroPrintPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AstroPrintPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AstroPrintPage.stringdata0))
        return static_cast<void*>(const_cast< AstroPrintPage*>(this));
    return QObject::qt_metacast(_clname);
}

int AstroPrintPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_AstroWindow_t {
    QByteArrayData data[9];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AstroWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AstroWindow_t qt_meta_stringdata_AstroWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AstroWindow"
QT_MOC_LITERAL(1, 12, 5), // "Close"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 12), // "AstroWindow*"
QT_MOC_LITERAL(4, 32, 8), // "DupnDrop"
QT_MOC_LITERAL(5, 41, 10), // "ButtonType"
QT_MOC_LITERAL(6, 52, 9), // "TimerSlot"
QT_MOC_LITERAL(7, 62, 9), // "Activated"
QT_MOC_LITERAL(8, 72, 8) // "QAction*"

    },
    "AstroWindow\0Close\0\0AstroWindow*\0"
    "DupnDrop\0ButtonType\0TimerSlot\0Activated\0"
    "QAction*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AstroWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   42,    2, 0x08 /* Private */,
       7,    1,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

void AstroWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AstroWindow *_t = static_cast<AstroWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Close((*reinterpret_cast< AstroWindow*(*)>(_a[1]))); break;
        case 1: _t->DupnDrop((*reinterpret_cast< ButtonType(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->TimerSlot(); break;
        case 3: _t->Activated((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AstroWindow* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AstroWindow::*_t)(AstroWindow * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AstroWindow::Close)) {
                *result = 0;
            }
        }
        {
            typedef void (AstroWindow::*_t)(ButtonType , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AstroWindow::DupnDrop)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AstroWindow::staticMetaObject = {
    { &AstroGraphicChart::staticMetaObject, qt_meta_stringdata_AstroWindow.data,
      qt_meta_data_AstroWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AstroWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AstroWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AstroWindow.stringdata0))
        return static_cast<void*>(const_cast< AstroWindow*>(this));
    return AstroGraphicChart::qt_metacast(_clname);
}

int AstroWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AstroGraphicChart::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AstroWindow::Close(AstroWindow * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AstroWindow::DupnDrop(ButtonType _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_AstroIconsWindow_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AstroIconsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AstroIconsWindow_t qt_meta_stringdata_AstroIconsWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AstroIconsWindow"
QT_MOC_LITERAL(1, 17, 7), // "Pressed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 43, 7), // "Clicked"
QT_MOC_LITERAL(5, 51, 13), // "DoubleClicked"
QT_MOC_LITERAL(6, 65, 9), // "Triggered"
QT_MOC_LITERAL(7, 75, 8) // "QAction*"

    },
    "AstroIconsWindow\0Pressed\0\0QTreeWidgetItem*\0"
    "Clicked\0DoubleClicked\0Triggered\0"
    "QAction*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AstroIconsWindow[] = {

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
       1,    2,   34,    2, 0x08 /* Private */,
       4,    2,   39,    2, 0x08 /* Private */,
       5,    2,   44,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void AstroIconsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AstroIconsWindow *_t = static_cast<AstroIconsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Pressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->DoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->Triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AstroIconsWindow::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_AstroIconsWindow.data,
      qt_meta_data_AstroIconsWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AstroIconsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AstroIconsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AstroIconsWindow.stringdata0))
        return static_cast<void*>(const_cast< AstroIconsWindow*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int AstroIconsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
