/****************************************************************************
** Meta object code from reading C++ file 'qdbuspendingcall.h'
**
** Created: Thu Mar 5 19:07:13 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qdbuspendingcall.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdbuspendingcall.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDBusPendingCallWatcher[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      30,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QDBusPendingCallWatcher[] = {
    "QDBusPendingCallWatcher\0\0self\0"
    "finished(QDBusPendingCallWatcher*)\0"
    "_q_finished()\0"
};

const QMetaObject QDBusPendingCallWatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QDBusPendingCallWatcher,
      qt_meta_data_QDBusPendingCallWatcher, 0 }
};

const QMetaObject *QDBusPendingCallWatcher::metaObject() const
{
    return &staticMetaObject;
}

void *QDBusPendingCallWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDBusPendingCallWatcher))
        return static_cast<void*>(const_cast< QDBusPendingCallWatcher*>(this));
    if (!strcmp(_clname, "QDBusPendingCall"))
        return static_cast< QDBusPendingCall*>(const_cast< QDBusPendingCallWatcher*>(this));
    return QObject::qt_metacast(_clname);
}

int QDBusPendingCallWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finished((*reinterpret_cast< QDBusPendingCallWatcher*(*)>(_a[1]))); break;
        case 1: d_func()->_q_finished(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QDBusPendingCallWatcher::finished(QDBusPendingCallWatcher * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
