/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtSql module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qvariant.h"
#include "qhash.h"
#include "qregexp.h"
#include "qsqlerror.h"
#include "qsqlfield.h"
#include "qsqlrecord.h"
#include "qsqlresult.h"
#include "qvector.h"
#include "qsqldriver.h"

QT_BEGIN_NAMESPACE

struct QHolder {
    QHolder(const QString& hldr = QString(), int index = -1): holderName(hldr), holderPos(index) {}
    bool operator==(const QHolder& h) const { return h.holderPos == holderPos && h.holderName == holderName; }
    bool operator!=(const QHolder& h) const { return h.holderPos != holderPos || h.holderName != holderName; }
    QString holderName;
    int holderPos;
};

class QSqlResultPrivate
{
public:
    QSqlResultPrivate(QSqlResult* d)
    : q(d), sqldriver(0), idx(QSql::BeforeFirstRow), active(false),
      isSel(false), forwardOnly(false), bindCount(0), binds(QSqlResult::PositionalBinding)
    {}

    void clearValues()
    {
        values.clear();
        bindCount = 0;
    }

    void resetBindCount()
    {
        bindCount = 0;
    }

    void clearIndex()
    {
        indexes.clear();
        holders.clear();
        types.clear();
    }

    void clear()
    {
        clearValues();
        clearIndex();;
    }

    QString positionalToNamedBinding();
    QString namedToPositionalBinding();
    QString holderAt(int index) const;

public:
    QSqlResult* q;
    const QSqlDriver* sqldriver;
    int idx;
    QString sql;
    bool active;
    bool isSel;
    QSqlError error;
    bool forwardOnly;

    int bindCount;
    QSqlResult::BindingSyntax binds;

    QString executedQuery;
    QHash<int, QSql::ParamType> types;
    QVector<QVariant> values;
    typedef QHash<QString, int> IndexMap;
    IndexMap indexes;

    typedef QVector<QHolder> QHolderVector;
    QHolderVector holders;
};

QString QSqlResultPrivate::holderAt(int index) const
{
    return indexes.key(index);
}

// return a unique id for bound names
static QString qFieldSerial(int i)
{
    ushort arr[] = { ':', 'f', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ushort *ptr = &arr[1];

    while (i > 0) {
        *(++ptr) = 'a' + i % 16;
        i >>= 4;
    }

    return QString::fromUtf16(arr, int(ptr - arr) + 1);
}

static bool qIsAlnum(QChar ch)
{
    uint u = uint(ch.unicode());
    // matches [a-zA-Z0-9_]
    return u - 'a' < 26 || u - 'A' < 26 || u - '0' < 10 || u == '_';
}

QString QSqlResultPrivate::positionalToNamedBinding()
{
    int n = sql.size();

    QString result;
    result.reserve(n * 5 / 4);
    bool inQuote = false;
    int count = 0;

    for (int i = 0; i < n; ++i) {
        QChar ch = sql.at(i);
        if (ch == QLatin1Char('?') && !inQuote) {
            result += qFieldSerial(count++);
        } else {
            if (ch == QLatin1Char('\''))
                inQuote = !inQuote;
            result += ch;
        }
    }
    result.squeeze();
    return result;
}

QString QSqlResultPrivate::namedToPositionalBinding()
{
    int n = sql.size();

    QString result;
    result.reserve(n);
    bool inQuote = false;
    int count = 0;
    int i = 0;

    while (i < n) {
        QChar ch = sql.at(i);
        if (ch == QLatin1Char(':') && !inQuote
                && (i == 0 || sql.at(i - 1) != QLatin1Char(':'))
                && (i < n - 1 && qIsAlnum(sql.at(i + 1)))) {
            int pos = i + 2;
            while (pos < n && qIsAlnum(sql.at(pos)))
                ++pos;
            indexes[sql.mid(i, pos - i)] = count++;
            result += QLatin1Char('?');
            i = pos;
        } else {
            if (ch == QLatin1Char('\''))
                inQuote = !inQuote;
            result += ch;
            ++i;
        }
    }
    result.squeeze();
    return result;
}

/*!
    \class QSqlResult
    \brief The QSqlResult class provides an abstract interface for
    accessing data from specific SQL databases.

    \ingroup database
    \module sql

    Normally, you would use QSqlQuery instead of QSqlResult, since
    QSqlQuery provides a generic wrapper for database-specific
    implementations of QSqlResult.

    If you are implementing your own SQL driver (by subclassing
    QSqlDriver), you will need to provide your own QSqlResult
    subclass that implements all the pure virtual functions and other
    virtual functions that you need.

    \sa QSqlDriver
*/

/*!
    \enum QSqlResult::BindingSyntax

    This enum type specifies the different syntaxes for specifying
    placeholders in prepared queries.

    \value PositionalBinding Use the ODBC-style positional syntax, with "?" as placeholders.
    \value NamedBinding Use the Oracle-style syntax with named placeholders (e.g., ":id")
    \omitvalue BindByPosition
    \omitvalue BindByName

    \sa bindingSyntax()
*/

/*!
    \enum QSqlResult::VirtualHookOperation
    \internal
*/

/*!
    Creates a QSqlResult using database driver \a db. The object is
    initialized to an inactive state.

    \sa isActive(), driver()
*/

QSqlResult::QSqlResult(const QSqlDriver *db)
{
    d = new QSqlResultPrivate(this);
    d->sqldriver = db;
}

/*!
    Destroys the object and frees any allocated resources.
*/

QSqlResult::~QSqlResult()
{
    delete d;
}

/*!
    Sets the current query for the result to \a query. You must call
    reset() to execute the query on the database.

    \sa reset(), lastQuery()
*/

void QSqlResult::setQuery(const QString& query)
{
    d->sql = query;
}

/*!
    Returns the current SQL query text, or an empty string if there
    isn't one.

    \sa setQuery()
*/

QString QSqlResult::lastQuery() const
{
    return d->sql;
}

/*!
    Returns the current (zero-based) row position of the result. May
    return the special values QSql::BeforeFirstRow or
    QSql::AfterLastRow.

    \sa setAt(), isValid()
*/
int QSqlResult::at() const
{
    return d->idx;
}


/*!
    Returns true if the result is positioned on a valid record (that
    is, the result is not positioned before the first or after the
    last record); otherwise returns false.

    \sa at()
*/

bool QSqlResult::isValid() const
{
    return d->idx != QSql::BeforeFirstRow && d->idx != QSql::AfterLastRow;
}

/*!
    \fn bool QSqlResult::isNull(int index)

    Returns true if the field at position \a index in the current row
    is null; otherwise returns false.
*/

/*!
    Returns true if the result has records to be retrieved; otherwise
    returns false.
*/

bool QSqlResult::isActive() const
{
    return d->active;
}

/*!
    This function is provided for derived classes to set the
    internal (zero-based) row position to \a index.

    \sa at()
*/

void QSqlResult::setAt(int index)
{
    d->idx = index;
}


/*!
    This function is provided for derived classes to indicate whether
    or not the current statement is a SQL \c SELECT statement. The \a
    select parameter should be true if the statement is a \c SELECT
    statement; otherwise it should be false.

    \sa isSelect()
*/

void QSqlResult::setSelect(bool select)
{
    d->isSel = select;
}

/*!
    Returns true if the current result is from a \c SELECT statement;
    otherwise returns false.

    \sa setSelect()
*/

bool QSqlResult::isSelect() const
{
    return d->isSel;
}

/*!
    Returns the driver associated with the result. This is the object
    that was passed to the constructor.
*/

const QSqlDriver *QSqlResult::driver() const
{
    return d->sqldriver;
}


/*!
    This function is provided for derived classes to set the internal
    active state to \a active.

    \sa isActive()
*/

void QSqlResult::setActive(bool active)
{
    if (active && d->executedQuery.isEmpty())
        d->executedQuery = d->sql;

    d->active = active;
}

/*!
    This function is provided for derived classes to set the last
    error to \a error.

    \sa lastError()
*/

void QSqlResult::setLastError(const QSqlError &error)
{
    d->error = error;
}


/*!
    Returns the last error associated with the result.
*/

QSqlError QSqlResult::lastError() const
{
    return d->error;
}

/*!
    \fn int QSqlResult::size()

    Returns the size of the \c SELECT result, or -1 if it cannot be
    determined or if the query is not a \c SELECT statement.

    \sa numRowsAffected()
*/

/*!
    \fn int QSqlResult::numRowsAffected()

    Returns the number of rows affected by the last query executed, or
    -1 if it cannot be determined or if the query is a \c SELECT
    statement.

    \sa size()
*/

/*!
    \fn QVariant QSqlResult::data(int index)

    Returns the data for field \a index in the current row as
    a QVariant. This function is only called if the result is in
    an active state and is positioned on a valid record and \a index is
    non-negative. Derived classes must reimplement this function and
    return the value of field \a index, or QVariant() if it cannot be
    determined.
*/

/*!
    \fn  bool QSqlResult::reset(const QString &query)

    Sets the result to use the SQL statement \a query for subsequent
    data retrieval.

    Derived classes must reimplement this function and apply the \a
    query to the database. This function is only called after the
    result is set to an inactive state and is positioned before the
    first record of the new result. Derived classes should return
    true if the query was successful and ready to be used, or false
    otherwise.

    \sa setQuery()
*/

/*!
    \fn bool QSqlResult::fetch(int index)

    Positions the result to an arbitrary (zero-based) row \a index.

    This function is only called if the result is in an active state.
    Derived classes must reimplement this function and position the
    result to the row \a index, and call setAt() with an appropriate
    value. Return true to indicate success, or false to signify
    failure.

    \sa isActive(), fetchFirst(), fetchLast(), fetchNext(), fetchPrevious()
*/

/*!
    \fn bool QSqlResult::fetchFirst()

    Positions the result to the first record (row 0) in the result.

    This function is only called if the result is in an active state.
    Derived classes must reimplement this function and position the
    result to the first record, and call setAt() with an appropriate
    value. Return true to indicate success, or false to signify
    failure.

    \sa fetch(), fetchLast()
*/

/*!
    \fn bool QSqlResult::fetchLast()

    Positions the result to the last record (last row) in the result.

    This function is only called if the result is in an active state.
    Derived classes must reimplement this function and position the
    result to the last record, and call setAt() with an appropriate
    value. Return true to indicate success, or false to signify
    failure.

    \sa fetch(), fetchFirst()
*/

/*!
    Positions the result to the next available record (row) in the
    result.

    This function is only called if the result is in an active
    state. The default implementation calls fetch() with the next
    index. Derived classes can reimplement this function and position
    the result to the next record in some other way, and call setAt()
    with an appropriate value. Return true to indicate success, or
    false to signify failure.

    \sa fetch(), fetchPrevious()
*/

bool QSqlResult::fetchNext()
{
    return fetch(at() + 1);
}

/*!
    Positions the result to the previous record (row) in the result.

    This function is only called if the result is in an active state.
    The default implementation calls fetch() with the previous index.
    Derived classes can reimplement this function and position the
    result to the next record in some other way, and call setAt()
    with an appropriate value. Return true to indicate success, or
    false to signify failure.
*/

bool QSqlResult::fetchPrevious()
{
    return fetch(at() - 1);
}

/*!
    Returns true if you can only scroll forward through the result
    set; otherwise returns false.

    \sa setForwardOnly()
*/
bool QSqlResult::isForwardOnly() const
{
    return d->forwardOnly;
}

/*!
    Sets forward only mode to \a forward. If \a forward is true, only
    fetchNext() is allowed for navigating the results. Forward only
    mode needs much less memory since results do not have to be
    cached. By default, this feature is disabled.

    \sa isForwardOnly(), fetchNext()
*/
void QSqlResult::setForwardOnly(bool forward)
{
    d->forwardOnly = forward;
}

/*!
    Prepares the given \a query, using the underlying database
    functionality where possible. Returns true if the query is
    prepared successfully; otherwise returns false.

    \sa prepare()
*/
bool QSqlResult::savePrepare(const QString& query)
{
    if (!driver())
        return false;
    d->clear();
    d->sql = query;
    if (!driver()->hasFeature(QSqlDriver::PreparedQueries))
        return prepare(query);

    if (driver()->hasFeature(QSqlDriver::NamedPlaceholders)) {
        // parse the query to memorize parameter location
        d->namedToPositionalBinding();
        d->executedQuery = d->positionalToNamedBinding();
    } else {
        d->executedQuery = d->namedToPositionalBinding();
    }
    return prepare(d->executedQuery);
}

/*!
    Prepares the given \a query for execution; the query will normally
    use placeholders so that it can be executed repeatedly. Returns
    true if the query is prepared successfully; otherwise returns false.

    \sa exec()
*/
bool QSqlResult::prepare(const QString& query)
{
    int n = query.size();

    bool inQuote = false;
    int i = 0;

    while (i < n) {
        QChar ch = query.at(i);
        if (ch == QLatin1Char(':') && !inQuote
                && (i == 0 || query.at(i - 1) != QLatin1Char(':'))
                && (i < n - 1 && qIsAlnum(query.at(i + 1)))) {
            int pos = i + 2;
            while (pos < n && qIsAlnum(query.at(pos)))
                ++pos;

            d->holders.append(QHolder(query.mid(i, pos - i), i));
            i = pos;
        } else {
            if (ch == QLatin1Char('\''))
                inQuote = !inQuote;
            ++i;
        }
    }
    d->sql = query;
    return true; // fake prepares should always succeed
}

/*!
    Executes the query, returning true if successful; otherwise returns
    false.

    \sa prepare()
*/
bool QSqlResult::exec()
{
    bool ret;
    // fake preparation - just replace the placeholders..
    QString query = lastQuery();
    if (d->binds == NamedBinding) {
        int i;
        QVariant val;
        QString holder;
        for (i = d->holders.count() - 1; i >= 0; --i) {
            holder = d->holders.at(i).holderName;
            val = d->values.value(d->indexes.value(holder));
            QSqlField f(QLatin1String(""), val.type());
            f.setValue(val);
            query = query.replace(d->holders.at(i).holderPos,
                                   holder.length(), driver()->formatValue(f));
        }
    } else {
        QString val;
        int i = 0;
        int idx = 0;
        for (idx = 0; idx < d->values.count(); ++idx) {
            i = query.indexOf(QLatin1Char('?'), i);
            if (i == -1)
                continue;
            QVariant var = d->values.value(idx);
            QSqlField f(QLatin1String(""), var.type());
            if (var.isNull())
                f.clear();
            else
                f.setValue(var);
            val = driver()->formatValue(f);
            query = query.replace(i, 1, driver()->formatValue(f));
            i += val.length();
        }
    }

    // have to retain the original query with placeholders
    QString orig = lastQuery();
    ret = reset(query);
    d->executedQuery = query;
    setQuery(orig);
    d->resetBindCount();
    return ret;
}

/*!
    Binds the value \a val of parameter type \a paramType to position \a index
    in the current record (row).

    \sa addBindValue()
*/
void QSqlResult::bindValue(int index, const QVariant& val, QSql::ParamType paramType)
{
    d->binds = PositionalBinding;
    d->indexes[qFieldSerial(index)] = index;
    if (d->values.count() <= index)
        d->values.resize(index + 1);
    d->values[index] = val;
    if (paramType != QSql::In || !d->types.isEmpty())
        d->types[index] = paramType;
}

/*!
    \overload

    Binds the value \a val of parameter type \a paramType to the \a
    placeholder name in the current record (row).

    Note that binding an undefined placeholder will result in undefined behavior.
*/
void QSqlResult::bindValue(const QString& placeholder, const QVariant& val,
                           QSql::ParamType paramType)
{
    d->binds = NamedBinding;
    // if the index has already been set when doing emulated named
    // bindings - don't reset it
    int idx = d->indexes.value(placeholder, -1);
    if (idx >= 0) {
        if (d->values.count() <= idx)
            d->values.resize(idx + 1);
        d->values[idx] = val;
    } else {
        d->values.append(val);
        idx = d->values.count() - 1;
        d->indexes[placeholder] = idx;
    }

    if (paramType != QSql::In || !d->types.isEmpty())
        d->types[idx] = paramType;
}

/*!
    Binds the value \a val of parameter type \a paramType to the next
    available position in the current record (row).

    \sa bindValue()
*/
void QSqlResult::addBindValue(const QVariant& val, QSql::ParamType paramType)
{
    d->binds = PositionalBinding;
    bindValue(d->bindCount, val, paramType);
    ++d->bindCount;
}

/*!
    Returns the value bound at position \a index in the current record
    (row).

    \sa bindValue(), boundValues()
*/
QVariant QSqlResult::boundValue(int index) const
{
    return d->values.value(index);
}

/*!
    \overload

    Returns the value bound by the given \a placeholder name in the
    current record (row).

    \sa bindValueType()
*/
QVariant QSqlResult::boundValue(const QString& placeholder) const
{
    int idx = d->indexes.value(placeholder, -1);
    return d->values.value(idx);
}

/*!
    Returns the parameter type for the value bound at position \a index.

    \sa boundValue()
*/
QSql::ParamType QSqlResult::bindValueType(int index) const
{
    return d->types.value(index, QSql::In);
}

/*!
    \overload

    Returns the parameter type for the value bound with the given \a
    placeholder name.
*/
QSql::ParamType QSqlResult::bindValueType(const QString& placeholder) const
{
    return d->types.value(d->indexes.value(placeholder, -1), QSql::In);
}

/*!
    Returns the number of bound values in the result.

    \sa boundValues()
*/
int QSqlResult::boundValueCount() const
{
    return d->values.count();
}

/*!
    Returns a vector of the result's bound values for the current
    record (row).

    \sa boundValueCount()
*/
QVector<QVariant>& QSqlResult::boundValues() const
{
    return d->values;
}

/*!
    Returns the binding syntax used by prepared queries.
*/
QSqlResult::BindingSyntax QSqlResult::bindingSyntax() const
{
    return d->binds;
}

/*!
    Clears the entire result set and releases any associated
    resources.
*/
void QSqlResult::clear()
{
    d->clear();
}

/*!
    Returns the query that was actually executed. This may differ from
    the query that was passed, for example if bound values were used
    with a prepared query and the underlying database doesn't support
    prepared queries.

    \sa exec(), setQuery()
*/
QString QSqlResult::executedQuery() const
{
    return d->executedQuery;
}

void QSqlResult::resetBindCount()
{
    d->resetBindCount();
}

/*!
    Returns the name of the bound value at position \a index in the
    current record (row).

    \sa boundValue()
*/
QString QSqlResult::boundValueName(int index) const
{
    return d->holderAt(index);
}

/*!
    Returns true if at least one of the query's bound values is a \c
    QSql::Out or a QSql::InOut; otherwise returns false.

    \sa bindValueType()
*/
bool QSqlResult::hasOutValues() const
{
    if (d->types.isEmpty())
        return false;
    QHash<int, QSql::ParamType>::ConstIterator it;
    for (it = d->types.constBegin(); it != d->types.constEnd(); ++it) {
        if (it.value() != QSql::In)
            return true;
    }
    return false;
}

/*!
    Returns the current record if the query is active; otherwise
    returns an empty QSqlRecord.

    The default implementation always returns an empty QSqlRecord.

    \sa isActive()
*/
QSqlRecord QSqlResult::record() const
{
    return QSqlRecord();
}

/*!
    Returns the object ID of the most recent inserted row if the
    database supports it.
    An invalid QVariant will be returned if the query did not
    insert any value or if the database does not report the id back.
    If more than one row was touched by the insert, the behavior is
    undefined.

    Note that for Oracle databases the row's ROWID will be returned,
    while for MySQL databases the row's auto-increment field will
    be returned.

    \sa QSqlDriver::hasFeature()
*/
QVariant QSqlResult::lastInsertId() const
{
    return QVariant();
}

/*! \internal
*/
void QSqlResult::virtual_hook(int, void *)
{
    Q_ASSERT(false);
}

/*! \internal
    \since 4.2

    Executes a prepared query in batch mode if the driver supports it,
    otherwise emulates a batch execution using bindValue() and exec().
    QSqlDriver::hasFeature() can be used to find out whether a driver
    supports batch execution.

    Batch execution can be faster for large amounts of data since it
    reduces network roundtrips.

    For batch executions, bound values have to be provided as lists
    of variants (QVariantList).

    Each list must contain values of the same type. All lists must
    contain equal amount of values (rows).

    NULL values are passed in as typed QVariants, for example
    \c {QVariant(QVariant::Int)} for an integer NULL value.

    Example:

    \snippet doc/src/snippets/code/src.sql.kernel.qsqlresult.cpp 0

    Here, we insert two rows into a SQL table, with each row containing three values.

    \sa exec(), QSqlDriver::hasFeature()
*/
bool QSqlResult::execBatch(bool arrayBind)
{
    if (driver()->hasFeature(QSqlDriver::BatchOperations)) {
        virtual_hook(BatchOperation, &arrayBind);
        d->resetBindCount();
        return d->error.type() == QSqlError::NoError;
    } else {
        QVector<QVariant> values = d->values;
        if (values.count() == 0)
            return false;
        for (int i = 0; i < values.at(0).toList().count(); ++i) {
            for (int j = 0; j < values.count(); ++j)
                bindValue(j, values.at(j).toList().at(i), QSql::In);
            if (!exec())
                return false;
        }
        return true;
    }
    return false;
}

/*! \internal
 */
void QSqlResult::detachFromResultSet()
{
    if (driver()->hasFeature(QSqlDriver::FinishQuery) 
            || driver()->hasFeature(QSqlDriver::SimpleLocking))
        virtual_hook(DetachFromResultSet, 0);
}

/*! \internal
 */
void QSqlResult::setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy policy)
{
    if (driver()->hasFeature(QSqlDriver::LowPrecisionNumbers))
        virtual_hook(SetNumericalPrecision, &policy);
}

/*! \internal
*/
bool QSqlResult::nextResult()
{
    if (driver()->hasFeature(QSqlDriver::MultipleResultSets)) {
        bool result = false;
        virtual_hook(NextResult, &result);
        return result;
    }
    return false;
}

/*!
    Returns the low-level database handle for this result set
    wrapped in a QVariant or an invalid QVariant if there is no handle.

    \warning Use this with uttermost care and only if you know what you're doing.

    \warning The handle returned here can become a stale pointer if the result
    is modified (for example, if you clear it).

    \warning The handle can be NULL if the result was not executed yet.

    The handle returned here is database-dependent, you should query the type
    name of the variant before accessing it.

    This example retrieves the handle for a sqlite result:

    \snippet doc/src/snippets/code/src.sql.kernel.qsqlresult.cpp 1

    This snippet returns the handle for PostgreSQL or MySQL:

    \snippet doc/src/snippets/code/src.sql.kernel.qsqlresult.cpp 2

    \sa QSqlDriver::handle()
*/
QVariant QSqlResult::handle() const
{
    return QVariant();
}

QT_END_NAMESPACE
