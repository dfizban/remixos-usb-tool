/****************************************************************************
** Meta object code from reading C++ file 'qtemporaryfile.h'
**
** Created: Fri May 30 22:18:23 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../io/qtemporaryfile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtemporaryfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTemporaryFile[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_QTemporaryFile[] = {
    "QTemporaryFile\0"
};

const QMetaObject QTemporaryFile::staticMetaObject = {
    { &QFile::staticMetaObject, qt_meta_stringdata_QTemporaryFile,
      qt_meta_data_QTemporaryFile, 0 }
};

const QMetaObject *QTemporaryFile::metaObject() const
{
    return &staticMetaObject;
}

void *QTemporaryFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTemporaryFile))
	return static_cast<void*>(const_cast< QTemporaryFile*>(this));
    return QFile::qt_metacast(_clname);
}

int QTemporaryFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFile::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
