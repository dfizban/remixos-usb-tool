/****************************************************************************
** Meta object code from reading C++ file 'qcalendarwidget.h'
**
** Created: Fri May 30 22:26:55 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widgets/qcalendarwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcalendarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCalendarWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   10, // methods
      12,  125, // properties
       3,  161, // enums/sets

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      41,   36,   16,   16, 0x05,
      56,   36,   16,   16, 0x05,
      84,   73,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     112,   36,   16,   16, 0x0a,
     143,  135,   16,   16, 0x0a,
     169,   73,   16,   16, 0x0a,
     198,  193,   16,   16, 0x0a,
     227,  219,   16,   16, 0x0a,
     257,   16,   16,   16, 0x0a,
     273,   16,   16,   16, 0x0a,
     293,   16,   16,   16, 0x0a,
     308,   16,   16,   16, 0x0a,
     327,   16,   16,   16, 0x0a,
     346,   16,   16,   16, 0x0a,
     358,   36,   16,   16, 0x08,
     400,  383,   16,   16, 0x08,
     430,   16,   16,   16, 0x08,
     451,   16,   16,   16, 0x08,
     473,   16,   16,   16, 0x08,
     495,   16,   16,   16, 0x08,
     520,   16,   16,   16, 0x08,
     541,  537,   16,   16, 0x08,

 // properties: name, type, flags
     573,  567, 0x0e095103,
     586,  567, 0x0e095103,
     598,  567, 0x0e095103,
     624,  610, 0x0009510b,
     644,  639, 0x01095103,
     670,  656, 0x0009510b,
     707,  684, 0x0009510b,
     751,  730, 0x0009510b,
     772,  639, 0x01084103,
     786,  639, 0x01095103,
     807,  639, 0x01095103,
     827,  823, 0x02095103,

 // enums: name, flags, count, data
     684, 0x0,    4,  173,
     730, 0x0,    2,  181,
     656, 0x0,    2,  185,

 // enum data: key, value
     847, uint(QCalendarWidget::NoHorizontalHeader),
     866, uint(QCalendarWidget::SingleLetterDayNames),
     887, uint(QCalendarWidget::ShortDayNames),
     901, uint(QCalendarWidget::LongDayNames),
     914, uint(QCalendarWidget::NoVerticalHeader),
     931, uint(QCalendarWidget::ISOWeekNumbers),
     946, uint(QCalendarWidget::NoSelection),
     958, uint(QCalendarWidget::SingleSelection),

       0        // eod
};

static const char qt_meta_stringdata_QCalendarWidget[] = {
    "QCalendarWidget\0\0selectionChanged()\0"
    "date\0clicked(QDate)\0activated(QDate)\0"
    "year,month\0currentPageChanged(int,int)\0"
    "setSelectedDate(QDate)\0min,max\0"
    "setDateRange(QDate,QDate)\0"
    "setCurrentPage(int,int)\0show\0"
    "setGridVisible(bool)\0visible\0"
    "setNavigationBarVisible(bool)\0"
    "showNextMonth()\0showPreviousMonth()\0"
    "showNextYear()\0showPreviousYear()\0"
    "showSelectedDate()\0showToday()\0"
    "_q_slotChangeDate(QDate)\0date,changeMonth\0"
    "_q_slotChangeDate(QDate,bool)\0"
    "_q_editingFinished()\0_q_prevMonthClicked()\0"
    "_q_nextMonthClicked()\0_q_yearEditingFinished()\0"
    "_q_yearClicked()\0act\0_q_monthChanged(QAction*)\0"
    "QDate\0selectedDate\0minimumDate\0"
    "maximumDate\0Qt::DayOfWeek\0firstDayOfWeek\0"
    "bool\0gridVisible\0SelectionMode\0"
    "selectionMode\0HorizontalHeaderFormat\0"
    "horizontalHeaderFormat\0VerticalHeaderFormat\0"
    "verticalHeaderFormat\0headerVisible\0"
    "navigationBarVisible\0dateEditEnabled\0"
    "int\0dateEditAcceptDelay\0NoHorizontalHeader\0"
    "SingleLetterDayNames\0ShortDayNames\0"
    "LongDayNames\0NoVerticalHeader\0"
    "ISOWeekNumbers\0NoSelection\0SingleSelection\0"
};

const QMetaObject QCalendarWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCalendarWidget,
      qt_meta_data_QCalendarWidget, 0 }
};

const QMetaObject *QCalendarWidget::metaObject() const
{
    return &staticMetaObject;
}

void *QCalendarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCalendarWidget))
	return static_cast<void*>(const_cast< QCalendarWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCalendarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectionChanged(); break;
        case 1: clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 2: activated((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: currentPageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: setSelectedDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 5: setDateRange((*reinterpret_cast< const QDate(*)>(_a[1])),(*reinterpret_cast< const QDate(*)>(_a[2]))); break;
        case 6: setCurrentPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: setGridVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: setNavigationBarVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: showNextMonth(); break;
        case 10: showPreviousMonth(); break;
        case 11: showNextYear(); break;
        case 12: showPreviousYear(); break;
        case 13: showSelectedDate(); break;
        case 14: showToday(); break;
        case 15: d_func()->_q_slotChangeDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 16: d_func()->_q_slotChangeDate((*reinterpret_cast< const QDate(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 17: d_func()->_q_editingFinished(); break;
        case 18: d_func()->_q_prevMonthClicked(); break;
        case 19: d_func()->_q_nextMonthClicked(); break;
        case 20: d_func()->_q_yearEditingFinished(); break;
        case 21: d_func()->_q_yearClicked(); break;
        case 22: d_func()->_q_monthChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        }
        _id -= 23;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QDate*>(_v) = selectedDate(); break;
        case 1: *reinterpret_cast< QDate*>(_v) = minimumDate(); break;
        case 2: *reinterpret_cast< QDate*>(_v) = maximumDate(); break;
        case 3: *reinterpret_cast< Qt::DayOfWeek*>(_v) = firstDayOfWeek(); break;
        case 4: *reinterpret_cast< bool*>(_v) = isGridVisible(); break;
        case 5: *reinterpret_cast< SelectionMode*>(_v) = selectionMode(); break;
        case 6: *reinterpret_cast< HorizontalHeaderFormat*>(_v) = horizontalHeaderFormat(); break;
        case 7: *reinterpret_cast< VerticalHeaderFormat*>(_v) = verticalHeaderFormat(); break;
        case 8: *reinterpret_cast< bool*>(_v) = isHeaderVisible(); break;
        case 9: *reinterpret_cast< bool*>(_v) = isNavigationBarVisible(); break;
        case 10: *reinterpret_cast< bool*>(_v) = isDateEditEnabled(); break;
        case 11: *reinterpret_cast< int*>(_v) = dateEditAcceptDelay(); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSelectedDate(*reinterpret_cast< QDate*>(_v)); break;
        case 1: setMinimumDate(*reinterpret_cast< QDate*>(_v)); break;
        case 2: setMaximumDate(*reinterpret_cast< QDate*>(_v)); break;
        case 3: setFirstDayOfWeek(*reinterpret_cast< Qt::DayOfWeek*>(_v)); break;
        case 4: setGridVisible(*reinterpret_cast< bool*>(_v)); break;
        case 5: setSelectionMode(*reinterpret_cast< SelectionMode*>(_v)); break;
        case 6: setHorizontalHeaderFormat(*reinterpret_cast< HorizontalHeaderFormat*>(_v)); break;
        case 7: setVerticalHeaderFormat(*reinterpret_cast< VerticalHeaderFormat*>(_v)); break;
        case 8: setHeaderVisible(*reinterpret_cast< bool*>(_v)); break;
        case 9: setNavigationBarVisible(*reinterpret_cast< bool*>(_v)); break;
        case 10: setDateEditEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 11: setDateEditAcceptDelay(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QCalendarWidget::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QCalendarWidget::clicked(const QDate & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCalendarWidget::activated(const QDate & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCalendarWidget::currentPageChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
