/****************************************************************************
** Meta object code from reading C++ file 'qabstractnetworkcache.h'
**
** Created: Thu Mar 5 18:42:45 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../access/qabstractnetworkcache.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qabstractnetworkcache.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QAbstractNetworkCache[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QAbstractNetworkCache[] = {
    "QAbstractNetworkCache\0\0clear()\0"
};

const QMetaObject QAbstractNetworkCache::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QAbstractNetworkCache,
      qt_meta_data_QAbstractNetworkCache, 0 }
};

const QMetaObject *QAbstractNetworkCache::metaObject() const
{
    return &staticMetaObject;
}

void *QAbstractNetworkCache::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QAbstractNetworkCache))
        return static_cast<void*>(const_cast< QAbstractNetworkCache*>(this));
    return QObject::qt_metacast(_clname);
}

int QAbstractNetworkCache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clear(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
