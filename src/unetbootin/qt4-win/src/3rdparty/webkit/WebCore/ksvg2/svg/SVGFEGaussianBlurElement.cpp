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
#include "SVGFEGaussianBlurElement.h"

#include "SVGNames.h"
#include "SVGParserUtilities.h"
#include "SVGResourceFilter.h"

namespace WebCore {

SVGFEGaussianBlurElement::SVGFEGaussianBlurElement(const QualifiedName& tagName, Document* doc)
    : SVGFilterPrimitiveStandardAttributes(tagName, doc)
    , m_stdDeviationX(0.0)
    , m_stdDeviationY(0.0)
    , m_filterEffect(0)
{
}

SVGFEGaussianBlurElement::~SVGFEGaussianBlurElement()
{
    delete m_filterEffect;
}

ANIMATED_PROPERTY_DEFINITIONS(SVGFEGaussianBlurElement, String, String, string, In1, in1, SVGNames::inAttr.localName(), m_in1)
ANIMATED_PROPERTY_DEFINITIONS(SVGFEGaussianBlurElement, double, Number, number, StdDeviationX, stdDeviationX, "stdDeviationX", m_stdDeviationX)
ANIMATED_PROPERTY_DEFINITIONS(SVGFEGaussianBlurElement, double, Number, number, StdDeviationY, stdDeviationY, "stdDeviationY", m_stdDeviationY)

void SVGFEGaussianBlurElement::setStdDeviation(float stdDeviationX, float stdDeviationY)
{
}

void SVGFEGaussianBlurElement::parseMappedAttribute(MappedAttribute* attr)
{
    const String& value = attr->value();
    if (attr->name() == SVGNames::stdDeviationAttr) {
        double x, y;
        if (parseNumberOptionalNumber(value, x, y)) {
            setStdDeviationXBaseValue(x);
            setStdDeviationYBaseValue(y);
        }
    } else if (attr->name() == SVGNames::inAttr)
        setIn1BaseValue(value);
    else
        SVGFilterPrimitiveStandardAttributes::parseMappedAttribute(attr);
}

SVGFEGaussianBlur* SVGFEGaussianBlurElement::filterEffect() const
{
    if (!m_filterEffect)
        m_filterEffect = static_cast<SVGFEGaussianBlur*>(SVGResourceFilter::createFilterEffect(FE_GAUSSIAN_BLUR));
    if (!m_filterEffect)
        return 0;
    m_filterEffect->setIn(in1());
    setStandardAttributes(m_filterEffect);
    m_filterEffect->setStdDeviationX(stdDeviationX());
    m_filterEffect->setStdDeviationY(stdDeviationY());
    return m_filterEffect;
}

}

#endif // ENABLE(SVG)

// vim:ts=4:noet
