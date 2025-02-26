/*
    Copyright (C) 2004, 2005 Nikolas Zimmermann <wildfox@kde.org>
                  2004, 2005, 2006 Rob Buis <buis@kde.org>

    This file is part of the KDE project

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(SVG) && ENABLE(SVG_EXPERIMENTAL_FEATURES)
#include "SVGFEMergeElement.h"

#include "SVGFEMergeNodeElement.h"
#include "SVGResourceFilter.h"

namespace WebCore {

SVGFEMergeElement::SVGFEMergeElement(const QualifiedName& tagName, Document* doc)
    : SVGFilterPrimitiveStandardAttributes(tagName, doc)
    , m_filterEffect(0)
{
}

SVGFEMergeElement::~SVGFEMergeElement()
{
    delete m_filterEffect;
}

SVGFEMerge* SVGFEMergeElement::filterEffect() const
{
    if (!m_filterEffect)
        m_filterEffect = static_cast<SVGFEMerge*>(SVGResourceFilter::createFilterEffect(FE_MERGE));
    if (!m_filterEffect)
        return 0;
    setStandardAttributes(m_filterEffect);

    Vector<String> mergeInputs;
    for (Node* n = firstChild(); n != 0; n = n->nextSibling()) {
        if (n->hasTagName(SVGNames::feMergeNodeTag))
            mergeInputs.append(static_cast<SVGFEMergeNodeElement*>(n)->in1());
    }

    m_filterEffect->setMergeInputs(mergeInputs);
    return m_filterEffect;
}

}


#endif // ENABLE(SVG)

// vim:ts=4:noet
