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
#include "SVGFECompositeElement.h"

#include "SVGNames.h"
#include "SVGResourceFilter.h"

namespace WebCore {

SVGFECompositeElement::SVGFECompositeElement(const QualifiedName& tagName, Document* doc)
    : SVGFilterPrimitiveStandardAttributes(tagName, doc)
    , m__operator(0)
    , m_k1(0.0)
    , m_k2(0.0)
    , m_k3(0.0)
    , m_k4(0.0)
    , m_filterEffect(0)
{
}

SVGFECompositeElement::~SVGFECompositeElement()
{
    delete m_filterEffect;
}

ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, String, String, string, In1, in1, SVGNames::inAttr.localName(), m_in1)
ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, String, String, string, In2, in2, SVGNames::in2Attr.localName(), m_in2)
ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, int, Enumeration, enumeration, _operator, _operator, SVGNames::operatorAttr.localName(), m__operator)
ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, double, Number, number, K1, k1, SVGNames::k1Attr.localName(), m_k1)
ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, double, Number, number, K2, k2, SVGNames::k2Attr.localName(), m_k2)
ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, double, Number, number, K3, k3, SVGNames::k3Attr.localName(), m_k3)
ANIMATED_PROPERTY_DEFINITIONS(SVGFECompositeElement, double, Number, number, K4, k4, SVGNames::k4Attr.localName(), m_k4)

void SVGFECompositeElement::parseMappedAttribute(MappedAttribute *attr)
{
    const String& value = attr->value();
    if (attr->name() == SVGNames::operatorAttr)
    {
        if (value == "over")
            set_operatorBaseValue(SVG_FECOMPOSITE_OPERATOR_OVER);
        else if (value == "in")
            set_operatorBaseValue(SVG_FECOMPOSITE_OPERATOR_IN);
        else if (value == "out")
            set_operatorBaseValue(SVG_FECOMPOSITE_OPERATOR_OUT);
        else if (value == "atop")
            set_operatorBaseValue(SVG_FECOMPOSITE_OPERATOR_ATOP);
        else if (value == "xor")
            set_operatorBaseValue(SVG_FECOMPOSITE_OPERATOR_XOR);
        else if (value == "arithmetic")
            set_operatorBaseValue(SVG_FECOMPOSITE_OPERATOR_ARITHMETIC);
    }
    else if (attr->name() == SVGNames::inAttr)
        setIn1BaseValue(value);
    else if (attr->name() == SVGNames::in2Attr)
        setIn2BaseValue(value);
    else if (attr->name() == SVGNames::k1Attr)
        setK1BaseValue(value.toDouble());
    else if (attr->name() == SVGNames::k2Attr)
        setK2BaseValue(value.toDouble());
    else if (attr->name() == SVGNames::k3Attr)
        setK3BaseValue(value.toDouble());
    else if (attr->name() == SVGNames::k4Attr)
        setK4BaseValue(value.toDouble());
    else
        SVGFilterPrimitiveStandardAttributes::parseMappedAttribute(attr);
}

SVGFEComposite* SVGFECompositeElement::filterEffect() const
{
    if (!m_filterEffect)
        m_filterEffect = static_cast<SVGFEComposite*>(SVGResourceFilter::createFilterEffect(FE_COMPOSITE));
    if (!m_filterEffect)
        return 0;
    m_filterEffect->setOperation((SVGCompositeOperationType) _operator());
    m_filterEffect->setIn(in1());
    m_filterEffect->setIn2(in2());
    setStandardAttributes(m_filterEffect);
    m_filterEffect->setK1(k1());
    m_filterEffect->setK2(k2());
    m_filterEffect->setK3(k3());
    m_filterEffect->setK4(k4());
    return m_filterEffect;
}

}

#endif // ENABLE(SVG)

// vim:ts=4:noet
