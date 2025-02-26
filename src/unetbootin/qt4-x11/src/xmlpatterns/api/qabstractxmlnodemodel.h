/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtXMLPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QABSTRACTXMLNODEMODEL_H
#define QABSTRACTXMLNODEMODEL_H

#include <QtXmlPatterns/QXmlName>
#include <QtCore/QSharedData>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

QT_MODULE(XmlPatterns)

/* This file contains the classes QXmlNodeModelIndex, QAbstractXmlNodeModel,
 * QXmlItem and QPatternist::NodeIndexStorage. */

class QAbstractXmlNodeModel;
class QAbstractXmlNodeModelPrivate;
class QAbstractXmlReceiver;
class QUrl;
class QXmlName;
class QXmlNodeModelIndex;
template<typename T> class QAbstractXmlForwardIterator;
template<typename T> class QVector;

/* The members in the namespace QPatternist are internal, not part of the public API, and
 * unsupported. Using them leads to undefined behavior. */
namespace QPatternist
{
    class DynamicContext;
    class Item;
    class ItemType;
    template<typename TResult, typename TSource, typename TMapper, typename Context> class ItemMappingIterator;
    template<typename TResult, typename TSource, typename TMapper> class SequenceMappingIterator;
    typedef QExplicitlySharedDataPointer<ItemType> ItemTypePtr;
    typedef QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<Item> > ItemIteratorPtr;
    typedef QVector<QXmlName> QXmlNameVector;

    class NodeIndexStorage
    {
    public:
        typedef qint64 Data;

        /*!
          \note Changing merely the order of these two members, ptr and data,
                is a binary incompatible change on Mac Power PC.
         */
        union
        {
            void *ptr; // Do not use ptr directy, use pointer() instead.
            Data data;
        };
        void *pointer() const
        {
            /* Constructing to qptrdiff means we avoid the warning "cast to pointer
             * from integer of different size."
             */
            return (void *)qptrdiff(data);
        }

        Data additionalData;
        const QAbstractXmlNodeModel *model;

        /* Implementation is in qabstractxmlnodemodel.cpp. */
        inline bool operator!=(const NodeIndexStorage &other) const;
    };
}

class Q_XMLPATTERNS_EXPORT QXmlNodeModelIndex
{
    enum Constants
    {
        ForwardAxis         = 8192,
        ReverseAxis         = 16384
    };

public:
    inline QXmlNodeModelIndex()
    {
        reset();
    }

    inline QXmlNodeModelIndex(const QXmlNodeModelIndex &other) : m_storage(other.m_storage)
    {
    }

    bool operator==(const QXmlNodeModelIndex &other) const;
    bool operator!=(const QXmlNodeModelIndex &other) const;

    typedef QAbstractXmlForwardIterator<QXmlNodeModelIndex> Iterator;
    typedef QList<QXmlNodeModelIndex> List;

    enum NodeKind
    {
        Attribute               = 1,
        Comment                 = 2,
        Document                = 4,
        Element                 = 8,
        Namespace               = 16,
        ProcessingInstruction   = 32,
        Text                    = 64
    };

    enum DocumentOrder
    {
        Precedes = -1,
        Is       = 0,
        Follows  = 1
    };

    enum Axis
    {
        AxisChild               = 1 | ForwardAxis,
        AxisDescendant          = 2 | ForwardAxis,
        AxisAttribute           = 4 | ForwardAxis,
        AxisSelf                = 8 | ForwardAxis,
        AxisDescendantOrSelf    = 16 | ForwardAxis,
        AxisFollowingSibling    = 32 | ForwardAxis,
        AxisNamespace           = 64 | ForwardAxis,
        AxisFollowing           = 128 | ReverseAxis,
        AxisParent              = 256 | ReverseAxis,
        AxisAncestor            = 512 | ReverseAxis,
        AxisPrecedingSibling    = 1024 | ReverseAxis,
        AxisPreceding           = 2048 | ReverseAxis,
        AxisAncestorOrSelf      = 4096 | ReverseAxis,
        /* Note that we cannot clash with the values of ForwardAxis and
         * ReverseAxis. */
        AxisChildOrTop          = 32768 | ForwardAxis,
        AxisAttributeOrTop      = 65536 | ForwardAxis
    };

    inline qint64 data() const
    {
        return m_storage.data;
    }

    inline void *internalPointer() const
    {
        return m_storage.pointer();
    }

    inline const QAbstractXmlNodeModel *model() const
    {
        return m_storage.model;
    }

    inline qint64 additionalData() const
    {
        return m_storage.additionalData;
    }

    inline bool isNull() const
    {
        return !m_storage.model;
    }

    /* The members below are internal, not part of the public API, and
     * unsupported. Using them leads to undefined behavior. */

    inline QXmlName name() const;
    inline QXmlNodeModelIndex root() const;
    inline QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<QXmlNodeModelIndex> > iterate(const Axis axis) const;
    inline QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<QPatternist::Item> > sequencedTypedValue() const;
    inline QUrl documentUri() const;
    inline QUrl baseUri() const;
    inline NodeKind kind() const;
    inline bool isDeepEqual(const QXmlNodeModelIndex &other) const;
    inline DocumentOrder compareOrder(const QXmlNodeModelIndex &other) const;
    inline void sendNamespaces(QAbstractXmlReceiver *const receiver) const;
    inline QVector<QXmlName> namespaceBindings() const;
    inline QXmlName::NamespaceCode namespaceForPrefix(const QXmlName::PrefixCode prefix) const;
    inline QString stringValue() const;
    inline QPatternist::ItemTypePtr type() const;
    inline bool is(const QXmlNodeModelIndex &other) const;

    inline void reset()
    {
        m_storage.data = 0;
        m_storage.additionalData = 0;
        m_storage.model = 0;
    }

private:
    static inline QXmlNodeModelIndex create(const qint64 d,
                                            const QAbstractXmlNodeModel *const nm)
    {
        QXmlNodeModelIndex n;
        n.m_storage.data = d;
        n.m_storage.model = nm;
        n.m_storage.additionalData = 0;
        return n;
    }

    static inline QXmlNodeModelIndex create(const qint64 data,
                                            const QAbstractXmlNodeModel *const nm,
                                            const qint64 addData)
    {
        QXmlNodeModelIndex n;
        n.m_storage.data = data;
        n.m_storage.model = nm;
        n.m_storage.additionalData = addData;
        return n;
    }

    inline QXmlNodeModelIndex(const QPatternist::NodeIndexStorage &storage) : m_storage(storage)
    {
    }

    friend class QAbstractXmlNodeModel;
    friend class QPatternist::Item;
    friend class QXmlItem;
    inline operator int() const; // Disable

    QPatternist::NodeIndexStorage m_storage;
};

Q_XMLPATTERNS_EXPORT uint qHash(const QXmlNodeModelIndex &index);

inline bool qIsForwardIteratorEnd(const QXmlNodeModelIndex &item)
{
    return item.isNull();
}

class Q_XMLPATTERNS_EXPORT QAbstractXmlNodeModel : public QSharedData
{
public:
    enum SimpleAxis
    {
        Parent,
        FirstChild,
        PreviousSibling,
        NextSibling
    };

    typedef QExplicitlySharedDataPointer<QAbstractXmlNodeModel> Ptr;
    typedef QList<Ptr> List;

    QAbstractXmlNodeModel();
    virtual ~QAbstractXmlNodeModel();

    virtual QUrl baseUri(const QXmlNodeModelIndex &ni) const = 0;
    virtual QUrl documentUri(const QXmlNodeModelIndex &ni) const = 0;
    virtual QXmlNodeModelIndex::NodeKind kind(const QXmlNodeModelIndex &ni) const = 0;
    virtual QXmlNodeModelIndex::DocumentOrder compareOrder(const QXmlNodeModelIndex &ni1,
                                                           const QXmlNodeModelIndex &ni2) const = 0;
    virtual QXmlNodeModelIndex root(const QXmlNodeModelIndex &n) const = 0;
    virtual QXmlName name(const QXmlNodeModelIndex &ni) const = 0;
    virtual QString stringValue(const QXmlNodeModelIndex &n) const = 0;
    virtual QVariant typedValue(const QXmlNodeModelIndex &n) const = 0;

    /* The members below are internal, not part of the public API, and
     * unsupported. Using them leads to undefined behavior. */
    virtual QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<QXmlNodeModelIndex> > iterate(const QXmlNodeModelIndex &ni, QXmlNodeModelIndex::Axis axis) const;
    virtual QPatternist::ItemIteratorPtr sequencedTypedValue(const QXmlNodeModelIndex &ni) const;
    virtual QPatternist::ItemTypePtr type(const QXmlNodeModelIndex &ni) const;
    virtual QXmlName::NamespaceCode namespaceForPrefix(const QXmlNodeModelIndex &ni,
                                                       const QXmlName::PrefixCode prefix) const;
    virtual bool isDeepEqual(const QXmlNodeModelIndex &ni1,
                             const QXmlNodeModelIndex &ni2) const;
    virtual void sendNamespaces(const QXmlNodeModelIndex &n,
                                QAbstractXmlReceiver *const receiver) const;
    virtual QVector<QXmlName> namespaceBindings(const QXmlNodeModelIndex &n) const = 0;


    virtual QXmlNodeModelIndex elementById(const QXmlName &NCName) const = 0;
    virtual QVector<QXmlNodeModelIndex> nodesByIdref(const QXmlName &NCName) const = 0;

    enum NodeCopySetting
    {
        InheritNamespaces   = 0x1,
        PreserveNamespaces  = 0x2
    };

    typedef QFlags<NodeCopySetting> NodeCopySettings;
    virtual void copyNodeTo(const QXmlNodeModelIndex &node,
                            QAbstractXmlReceiver *const receiver,
                            const NodeCopySettings &) const;

protected:

    virtual QXmlNodeModelIndex nextFromSimpleAxis(SimpleAxis axis, const QXmlNodeModelIndex &origin) const = 0;
    virtual QVector<QXmlNodeModelIndex> attributes(const QXmlNodeModelIndex &element) const = 0;

    QAbstractXmlNodeModel(QAbstractXmlNodeModelPrivate *d);

    inline QXmlNodeModelIndex createIndex(qint64 data) const
    {
        return QXmlNodeModelIndex::create(data, this);
    }

    inline QXmlNodeModelIndex createIndex(void * pointer,
                                          qint64 additionalData = 0) const
    {
        return QXmlNodeModelIndex::create(qptrdiff(pointer), this, additionalData);
    }

    inline QXmlNodeModelIndex createIndex(qint64 data,
                                          qint64 additionalData) const
    {
        return QXmlNodeModelIndex::create(data, this, additionalData);
    }

    QAbstractXmlNodeModelPrivate *d_ptr;
private:
    friend class QPatternist::ItemMappingIterator<QXmlNodeModelIndex, QXmlNodeModelIndex, const QAbstractXmlNodeModel *, QExplicitlySharedDataPointer<QPatternist::DynamicContext> >;
    friend class QPatternist::SequenceMappingIterator<QXmlNodeModelIndex, QXmlNodeModelIndex, const QAbstractXmlNodeModel *>;

    inline QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<QXmlNodeModelIndex> > mapToSequence(const QXmlNodeModelIndex &ni,
                                                                           const QExplicitlySharedDataPointer<QPatternist::DynamicContext> &) const;

    static inline bool isIgnorableInDeepEqual(const QXmlNodeModelIndex &n);
    Q_DISABLE_COPY(QAbstractXmlNodeModel)
};

Q_DECLARE_TYPEINFO(QXmlNodeModelIndex, Q_MOVABLE_TYPE);

template<typename T> class QAbstractXmlForwardIterator;
class QVariant;
class QXmlItemPrivate;

namespace QPatternist
{
    class AtomicValue;
    class VariableLoader;
    class IteratorBridge;
    class ToQXmlItemMapper;
    class ToItemMapper;
}

class Q_XMLPATTERNS_EXPORT QXmlItem
{
public:
    typedef QAbstractXmlForwardIterator<QXmlItem> Iterator;

    QXmlItem();
    QXmlItem(const QXmlItem &other);
    QXmlItem(const QXmlNodeModelIndex &node);
    QXmlItem(const QVariant &atomicValue);
    ~QXmlItem();
    QXmlItem &operator=(const QXmlItem &other);

    bool isNull() const;
    bool isNode() const;
    bool isAtomicValue() const;

    QVariant toAtomicValue() const;
    QXmlNodeModelIndex toNodeModelIndex() const;

private:
    friend class QPatternist::IteratorBridge;
    friend class QPatternist::VariableLoader;
    friend class QPatternist::ToQXmlItemMapper;
    friend class QPatternist::ToItemMapper;
    friend class QPatternist::Item;

    inline bool internalIsAtomicValue() const;

    inline QXmlItem(const QPatternist::Item &i);

    union
    {
        QPatternist::NodeIndexStorage   m_node;

        /* These two sits at the position of NodeIndexStorage::data.
         * NodeIndexStorage::{additionalData,model} are free. */
        const QPatternist::AtomicValue *m_atomicValue;
        QXmlItemPrivate *               m_ptr; /* Not currently used. */
    };
};

inline bool qIsForwardIteratorEnd(const QXmlItem &item)
{
    return item.isNull();
}

Q_DECLARE_TYPEINFO(QXmlItem, Q_MOVABLE_TYPE);

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QXmlItem) /* This macro must appear after QT_END_NAMESPACE. */

QT_END_HEADER

#endif
