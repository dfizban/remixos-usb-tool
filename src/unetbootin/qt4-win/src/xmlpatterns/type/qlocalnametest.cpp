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

#include <QHash>

#include "qbuiltintypes_p.h"
#include "qitem_p.h"
#include "qitem_p.h"
#include "qxpathhelper_p.h"

#include "qlocalnametest_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

LocalNameTest::LocalNameTest(const ItemType::Ptr &primaryType,
                             const QXmlName::LocalNameCode &ncName) : AbstractNodeTest(primaryType),
                                                                   m_ncName(ncName)
{
}

ItemType::Ptr LocalNameTest::create(const ItemType::Ptr &primaryType, const QXmlName::LocalNameCode localName)
{
    Q_ASSERT(primaryType);

    return ItemType::Ptr(new LocalNameTest(primaryType, localName));
}

bool LocalNameTest::itemMatches(const Item &item) const
{
    Q_ASSERT(item.isNode());
    return m_primaryType->itemMatches(item) &&
           item.asNode().name().localName() == m_ncName;
}

QString LocalNameTest::displayName(const NamePool::Ptr &np) const
{
    QString displayOther(m_primaryType->displayName(np));

    return displayOther.insert(displayOther.size() - 1,
                               QString::fromLatin1("*:") + np->stringForLocalName(m_ncName));
}

ItemType::InstanceOf LocalNameTest::instanceOf() const
{
    return ClassLocalNameTest;
}

bool LocalNameTest::operator==(const ItemType &other) const
{
    return other.instanceOf() == ClassLocalNameTest &&
           static_cast<const LocalNameTest &>(other).m_ncName == m_ncName;
}

QT_END_NAMESPACE
