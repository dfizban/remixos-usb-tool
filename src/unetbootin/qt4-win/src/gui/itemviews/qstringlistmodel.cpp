/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

/*
    A simple model that uses a QStringList as its data source.
*/

#include "qstringlistmodel.h"

#ifndef QT_NO_STRINGLISTMODEL

QT_BEGIN_NAMESPACE

/*!
    \class QStringListModel
    \brief The QStringListModel class provides a model that supplies strings to views.

    \ingroup model-view
    \mainclass

    QStringListModel is an editable model that can be used for simple
    cases where you need to display a number of strings in a view
    widget, such as a QListView or a QComboBox.

    The model provides all the standard functions of an editable
    model, representing the data in the string list as a model with
    one column and a number of rows equal to the number of items in
    the list.

    Model indexes corresponding to items are obtained with the
    \l{QAbstractListModel::index()}{index()} function, and item flags
    are obtained with flags().  Item data is read with the data()
    function and written with setData().  The number of rows (and
    number of items in the string list) can be found with the
    rowCount() function.

    The model can be constructed with an existing string list, or
    strings can be set later with the setStringList() convenience
    function. Strings can also be inserted in the usual way with the
    insertRows() function, and removed with removeRows(). The contents
    of the string list can be retrieved with the stringList()
    convenience function.

    An example usage of QStringListModel:

    \snippet doc/src/snippets/qstringlistmodel/main.cpp 0

    \sa QAbstractListModel, QAbstractItemModel, {Model Classes}
*/

/*!
    Constructs a string list model with the given \a parent.
*/

QStringListModel::QStringListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

/*!
    Constructs a string list model containing the specified \a strings
    with the given \a parent.
*/

QStringListModel::QStringListModel(const QStringList &strings, QObject *parent)
    : QAbstractListModel(parent), lst(strings)
{
}

/*!
    Returns the number of rows in the model. This value corresponds to the
    number of items in the model's internal string list.

    The optional \a parent argument is in most models used to specify
    the parent of the rows to be counted. Because this is a list if a
    valid parent is specified, the result will always be 0.

    \sa insertRows(), removeRows(), QAbstractItemModel::rowCount()
*/

int QStringListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return lst.count();
}

/*!
    Returns data for the specified \a role, from the item with the
    given \a index.

    If the view requests an invalid index, an invalid variant is returned.

    \sa setData()
*/

QVariant QStringListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= lst.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return lst.at(index.row());

    return QVariant();
}

/*!
    Returns the flags for the item with the given \a index.

    Valid items are enabled, selectable, and editable.

    \sa QAbstractItemModel::flags()
*/

Qt::ItemFlags QStringListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

/*!
    Sets the data for the specified \a role in the item with the given
    \a index in the model, to the provided \a value.

    The dataChanged() signal is emitted if the item is changed.

    \sa Qt::ItemDataRole, data()
*/

bool QStringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < lst.size()
        && (role == Qt::EditRole || role == Qt::DisplayRole)) {
        lst.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/*!
    Inserts \a count rows into the model, beginning at the given \a row.

    The \a parent index of the rows is optional and is only used for
    consistency with QAbstractItemModel. By default, a null index is
    specified, indicating that the rows are inserted in the top level of
    the model.

    \sa QAbstractItemModel::insertRows()
*/

bool QStringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        lst.insert(row, QString());

    endInsertRows();

    return true;
}

/*!
    Removes \a count rows from the model, beginning at the given \a row.

    The \a parent index of the rows is optional and is only used for
    consistency with QAbstractItemModel. By default, a null index is
    specified, indicating that the rows are removed in the top level of
    the model.

    \sa QAbstractItemModel::removeRows()
*/

bool QStringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        lst.removeAt(row);

    endRemoveRows();

    return true;
}

static bool ascendingLessThan(const QPair<QString, int> &s1, const QPair<QString, int> &s2)
{
    return s1.first < s2.first;
}

static bool decendingLessThan(const QPair<QString, int> &s1, const QPair<QString, int> &s2)
{
    return s1.first > s2.first;
}

/*!
  \reimp
*/
void QStringListModel::sort(int, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();

    QList<QPair<QString, int> > list;
    for (int i = 0; i < lst.count(); ++i)
        list.append(QPair<QString, int>(lst.at(i), i));

    if (order == Qt::AscendingOrder)
        qSort(list.begin(), list.end(), ascendingLessThan);
    else
        qSort(list.begin(), list.end(), decendingLessThan);

    lst.clear();
    QVector<int> forwarding(list.count());
    for (int i = 0; i < list.count(); ++i) {
        lst.append(list.at(i).first);
        forwarding[list.at(i).second] = i;
    }

    QModelIndexList oldList = persistentIndexList();
    QModelIndexList newList;
    for (int i = 0; i < oldList.count(); ++i)
        newList.append(index(forwarding.at(oldList.at(i).row()), 0));
    changePersistentIndexList(oldList, newList);

    emit layoutChanged();
}

/*!
    Returns the string list used by the model to store data.
*/
QStringList QStringListModel::stringList() const
{
    return lst;
}

/*!
    Sets the model's internal string list to \a strings. The model will
    notify any attached views that its underlying data has changed.

    \sa dataChanged()
*/
void QStringListModel::setStringList(const QStringList &strings)
{
    lst = strings;
    reset();
}

/*!
  \reimp
*/
Qt::DropActions QStringListModel::supportedDropActions() const
{
    return QAbstractItemModel::supportedDropActions() | Qt::MoveAction;
}

QT_END_NAMESPACE

#endif // QT_NO_STRINGLISTMODEL
