/****************************************************************************
** Meta object code from reading C++ file 'buccigame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Bucci-Source/buccigame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buccigame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BucciGame_t {
    QByteArrayData data[4];
    char stringdata[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BucciGame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BucciGame_t qt_meta_stringdata_BucciGame = {
    {
QT_MOC_LITERAL(0, 0, 9), // "BucciGame"
QT_MOC_LITERAL(1, 10, 11), // "updateField"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11) // "pickupCards"

    },
    "BucciGame\0updateField\0\0pickupCards"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BucciGame[] = {

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
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BucciGame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BucciGame *_t = static_cast<BucciGame *>(_o);
        switch (_id) {
        case 0: _t->updateField(); break;
        case 1: _t->pickupCards(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BucciGame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BucciGame.data,
      qt_meta_data_BucciGame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BucciGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BucciGame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BucciGame.stringdata))
        return static_cast<void*>(const_cast< BucciGame*>(this));
    return QWidget::qt_metacast(_clname);
}

int BucciGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
