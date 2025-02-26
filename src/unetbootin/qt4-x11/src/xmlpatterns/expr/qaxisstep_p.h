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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_AxisStep_H
#define Patternist_AxisStep_H

#include "qemptycontainer_p.h"
#include "qitem_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short A step in a path expression that with an axis and a node test evaluates
     * to a sequence of nodes from the context item.
     *
     * @author Frans Englich <fenglich@trolltech.com>
     * @ingroup Patternist_expressions
     */
    class Q_AUTOTEST_EXPORT AxisStep : public EmptyContainer
    {
    public:
        AxisStep(const QXmlNodeModelIndex::Axis axis,
                 const ItemType::Ptr &nodeTest);

        virtual Item::Iterator::Ptr evaluateSequence(const DynamicContext::Ptr &) const;
        virtual Item evaluateSingleton(const DynamicContext::Ptr &) const;

        /**
         * Returns @p node if it matches the node test this step is using, otherwise @c null.
         */
        inline Item mapToItem(const QXmlNodeModelIndex &node,
                              const DynamicContext::Ptr &context) const;

        virtual SequenceType::List expectedOperandTypes() const;
        virtual SequenceType::Ptr staticType() const;

        /**
         * Rewrites to ParentNodeAxis, if possible.
         */
        virtual Expression::Ptr typeCheck(const StaticContext::Ptr &context,
                                          const SequenceType::Ptr &reqType);

        /**
         * @returns always BuiltinTypes::node;
         */
        virtual ItemType::Ptr expectedContextItemType() const;

        virtual ExpressionVisitorResult::Ptr accept(const ExpressionVisitor::Ptr &visitor) const;

        virtual Properties properties() const;

        /**
         * @returns the axis this step is using.
         */
        QXmlNodeModelIndex::Axis axis() const;

        /**
         * @returns the node test this step is using.
         */
        inline ItemType::Ptr nodeTest() const
        {
            return m_nodeTest;
        }

        void setNodeTest(const ItemType::Ptr &nev)
        {
            m_nodeTest = nev;
        }

        /**
         * @short Prints the EBNF name corresponding to @p axis.
         *
         * For instance, for QXmlNodeModelIndex::Child, "child" is returned.
         *
         * Apart from being used in this class, it is used in the SDK.
         */
        static QString axisName(const QXmlNodeModelIndex::Axis axis);

        virtual ID id() const;
        virtual PatternPriority patternPriority() const;

        inline void setAxis(const QXmlNodeModelIndex::Axis newAxis);

    private:
        typedef QExplicitlySharedDataPointer<const AxisStep> ConstPtr;

        static const QXmlNodeModelIndex::NodeKind s_whenAxisNodeKindEmpty[];

        /**
         * @returns @c true when the axis @p axis and a node test testing node of
         * type @p nodeKind always produces an empty sequence. One such example
         * is <tt>attribute::comment()</tt>.
         */
        static bool isAlwaysEmpty(const QXmlNodeModelIndex::Axis axis,
                                  const QXmlNodeModelIndex::NodeKind nodeKind);

        /**
         * The reason this variable is mutable, is that in the case of XSL-T patterns,
         * we do quite some reordering.
         */
        QXmlNodeModelIndex::Axis    m_axis;
        ItemType::Ptr               m_nodeTest;
    };

    void AxisStep::setAxis(const QXmlNodeModelIndex::Axis newAxis)
    {
        m_axis = newAxis;
    }

}

QT_END_NAMESPACE

QT_END_HEADER

#endif
