/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtSVG module of the Qt Toolkit.
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

#include "qsvgstructure_p.h"

#ifndef QT_NO_SVG

#include "qsvgnode_p.h"
#include "qsvgstyle_p.h"

#include "qpainter.h"
#include "qlocale.h"
#include "qdebug.h"

QT_BEGIN_NAMESPACE

QSvgG::QSvgG(QSvgNode *parent)
    : QSvgStructureNode(parent)
{

}

QSvgStructureNode::~QSvgStructureNode()
{
    qDeleteAll(m_renderers);
}

void QSvgG::draw(QPainter *p)
{
    QList<QSvgNode*>::iterator itr = m_renderers.begin();
    applyStyle(p);

    if (displayMode() != QSvgNode::NoneMode) {
        while (itr != m_renderers.end()) {
            QSvgNode *node = *itr;
            if (node->isVisible())
                node->draw(p);
            ++itr;
        }
    }
    revertStyle(p);
}

QSvgNode::Type QSvgG::type() const
{
    return G;
}

QSvgStructureNode::QSvgStructureNode(QSvgNode *parent)
    :QSvgNode(parent)
{

}

QSvgNode * QSvgStructureNode::scopeNode(const QString &id) const
{
    const QSvgStructureNode *group = this;
    while (group && group->type() != QSvgNode::DOC) {
        group = static_cast<QSvgStructureNode*>(group->parent());
    }
    if (group)
        return group->m_scope[id];
    return 0;
}

void QSvgStructureNode::addChild(QSvgNode *child, const QString &id, bool def)
{
    if (!def)
        m_renderers.append(child);

    if (child->type() == QSvgNode::DEFS) {
        QSvgDefs *defs =
            static_cast<QSvgDefs*>(child);
        m_linkedScopes.append(defs);
    }

    if (id.isEmpty())
        return; //we can't add it to scope without id

    QSvgStructureNode *group = this;
    while (group && group->type() != QSvgNode::DOC) {
        group = static_cast<QSvgStructureNode*>(group->parent());
    }
    if (group)
        group->m_scope.insert(id, child);
}

QSvgDefs::QSvgDefs(QSvgNode *parent)
    : QSvgStructureNode(parent)
{
}

void QSvgDefs::draw(QPainter *)
{
    //noop
}

QSvgNode::Type QSvgDefs::type() const
{
    return DEFS;
}

QSvgStyleProperty * QSvgStructureNode::scopeStyle(const QString &id) const
{
    const QSvgStructureNode *group = this;
    while (group) {
        QSvgStyleProperty *prop = group->styleProperty(id);
        if (prop)
            return prop;
        QList<QSvgStructureNode*>::const_iterator itr = group->m_linkedScopes.constBegin();
        while (itr != group->m_linkedScopes.constEnd()) {
            prop = (*itr)->styleProperty(id);
            if (prop)
                return prop;
            ++itr;
        }
        group = static_cast<QSvgStructureNode*>(group->parent());
    }
    return 0;
}


/*
  Below is a lookup function based on the gperf output using the following set:

  http://www.w3.org/Graphics/SVG/feature/1.2/#SVG
  http://www.w3.org/Graphics/SVG/feature/1.2/#SVG-static
  http://www.w3.org/Graphics/SVG/feature/1.2/#CoreAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#Structure
  http://www.w3.org/Graphics/SVG/feature/1.2/#ConditionalProcessing
  http://www.w3.org/Graphics/SVG/feature/1.2/#ConditionalProcessingAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#Image
  http://www.w3.org/Graphics/SVG/feature/1.2/#Prefetch
  http://www.w3.org/Graphics/SVG/feature/1.2/#Shape
  http://www.w3.org/Graphics/SVG/feature/1.2/#Text
  http://www.w3.org/Graphics/SVG/feature/1.2/#PaintAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#OpacityAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#GraphicsAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#Gradient
  http://www.w3.org/Graphics/SVG/feature/1.2/#SolidColor
  http://www.w3.org/Graphics/SVG/feature/1.2/#XlinkAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#ExternalResourcesRequiredAttribute
  http://www.w3.org/Graphics/SVG/feature/1.2/#Font
  http://www.w3.org/Graphics/SVG/feature/1.2/#Hyperlinking
  http://www.w3.org/Graphics/SVG/feature/1.2/#Extensibility
*/

// ----- begin of generated code -----

/* C code produced by gperf version 3.0.2 */
/* Command-line: gperf -c -L c svg  */
/* Computed positions: -k'45-46' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

enum {
    TOTAL_KEYWORDS = 20,
    MIN_WORD_LENGTH = 47,
    MAX_WORD_LENGTH = 78,
    MIN_HASH_VALUE = 48,
    MAX_HASH_VALUE = 88
};
/* maximum key range = 41, duplicates = 0 */

inline static bool isSupportedSvgFeature(const QString &str)
{
    static const unsigned char asso_values[] = {
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89,  0, 89,  5,
        15,  5,  0, 10, 89, 89, 89, 89, 89,  0,
        15, 89, 89,  0,  0, 89,  5, 89,  0, 89,
        89, 89, 89, 89, 89, 89, 89,  0, 89, 89,
        89,  0, 89, 89,  0, 89, 89, 89,  0,  5,
        89,  0,  0, 89,  5, 89,  0, 89, 89, 89,
        5,  0, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
        89, 89, 89, 89, 89, 89
    };

    static const char * wordlist[] = {
        "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "",
        "", "", "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Text",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Shape",
        "", "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#SVG",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Structure",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#SolidColor",
        "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Hyperlinking",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#CoreAttribute",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#XlinkAttribute",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#SVG-static",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#OpacityAttribute",
        "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Gradient",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Font",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Image",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#ConditionalProcessing",
        "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Extensibility",
        "", "", "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#GraphicsAttribute",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#Prefetch",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#PaintAttribute",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#ConditionalProcessingAttribute",
        "", "", "", "", "", "", "", "", "",
        "", "", "", "",
        "http://www.w3.org/Graphics/SVG/feature/1.2/#ExternalResourcesRequiredAttribute"
    };

    if (str.length() <= MAX_WORD_LENGTH && str.length() >= MIN_WORD_LENGTH) {
        const int key = str.length()
                        + asso_values[str.at(45).unicode()]
                        + asso_values[str.at(44).unicode()];
        if (key <= MAX_HASH_VALUE && key >= 0)
            return str == QLatin1String(wordlist[key]);
    }
    return false;
}

// ----- end of generated code -----

static inline bool isSupportedSvgExtension(const QString &)
{
    return false;
}


QSvgSwitch::QSvgSwitch(QSvgNode *parent)
    : QSvgStructureNode(parent)
{
    init();
}

void QSvgSwitch::draw(QPainter *p)
{
    QList<QSvgNode*>::iterator itr = m_renderers.begin();
    applyStyle(p);

    if (displayMode() != QSvgNode::NoneMode) {
        while (itr != m_renderers.end()) {
            QSvgNode *node = *itr;
            if (node->isVisible()) {
                const QStringList &features  = node->requiredFeatures();
                const QStringList &extensions = node->requiredExtensions();
                const QStringList &languages = node->requiredLanguages();
                const QStringList &formats = node->requiredFormats();
                const QStringList &fonts = node->requiredFonts();

                bool okToRender = true;
                if (!features.isEmpty()) {
                    QStringList::const_iterator sitr = features.constBegin();
                    for (; sitr != features.constEnd(); ++sitr) {
                        if (!isSupportedSvgFeature(*sitr)) {
                            okToRender = false;
                            break;
                        }
                    }
                }

                if (okToRender && !extensions.isEmpty()) {
                    QStringList::const_iterator sitr = extensions.constBegin();
                    for (; sitr != extensions.constEnd(); ++sitr) {
                        if (!isSupportedSvgExtension(*sitr)) {
                            okToRender = false;
                            break;
                        }
                    }
                }

                if (okToRender && !languages.isEmpty()) {
                    QStringList::const_iterator sitr = languages.constBegin();
                    okToRender = false;
                    for (; sitr != languages.constEnd(); ++sitr) {
                        if ((*sitr).startsWith(m_systemLanguagePrefix)) {
                            okToRender = true;
                            break;
                        }
                    }
                }

                if (okToRender && !formats.isEmpty()) {
                    okToRender = false;
                }

                if (okToRender && !fonts.isEmpty()) {
                    okToRender = false;
                }

                if (okToRender) {
                    node->draw(p);
                    break;
                }
            }
            ++itr;
        }
    }
    revertStyle(p);
}

QSvgNode::Type QSvgSwitch::type() const
{
    return SWITCH;
}

void QSvgSwitch::init()
{
    QLocale locale;
    m_systemLanguage = locale.name().replace(QLatin1Char('_'), QLatin1Char('-'));
    int idx = m_systemLanguage.indexOf(QLatin1Char('-'));
    m_systemLanguagePrefix = m_systemLanguage.mid(0, idx);
}

QRectF QSvgStructureNode::bounds() const
{
    if (m_bounds.isEmpty()) {
        foreach(QSvgNode *node, m_renderers) {
            m_bounds |= node->bounds();
        }
    }

    return m_bounds;
}

QRectF QSvgStructureNode::transformedBounds(const QMatrix &mat) const
{
    QMatrix m = mat;
    QSvgTransformStyle *trans = m_style.transform;
    if (trans) {
        m = trans->qmatrix() * m;
    }

    QRectF bounds;
    foreach(QSvgNode *node, m_renderers) {
        bounds |= node->transformedBounds(m);
    }

    return bounds;
}

QSvgNode * QSvgStructureNode::previousSiblingNode(QSvgNode *n) const
{
    QSvgNode *prev = 0;
    QList<QSvgNode*>::const_iterator itr = m_renderers.constBegin();
    while (itr != m_renderers.constEnd()) {
        QSvgNode *node = *itr;
        if (node == n)
            return prev;
        prev = node;
    }
    return prev;
}

QT_END_NAMESPACE

#endif // QT_NO_SVG
