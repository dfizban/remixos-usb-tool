/****************************************************************************
**
** Copyright (C) 2006-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtXMLPatterns module of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_ParentNodeAxis_H
#define Patternist_ParentNodeAxis_H

#include "qemptycontainer_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Corresponds to the expression <tt>parent::node()</tt>.
     *
     * This AST node is now useless, due to refactorings. Prevously we had
     * Item QAbstractXmlNodeModel::parent(), which didn't have the overhead of
     * allocating an iterator for a single node. However, in order to stream
     * line the API it is now gone and hence the node performs exactly the same
     * as AxisStep.
     *
     * @author Frans Englich <fenglich@trolltech.com>
     * @ingroup Patternist_expressions
     */
    class ParentNodeAxis : public EmptyContainer
    {
    public:
        virtual Item evaluateSingleton(const DynamicContext::Ptr &context) const;

        /**
         * @returns always DisableElimination
         */
        virtual Expression::Properties properties() const;

        virtual ExpressionVisitorResult::Ptr accept(const ExpressionVisitor::Ptr &visitor) const;

        /**
         * @returns always CommonSequenceTypes::ExactlyOneNode;
         */
        virtual SequenceType::Ptr staticType() const;

        /**
         * @returns always BuiltinTypes::node;
         */
        virtual ItemType::Ptr expectedContextItemType() const;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
