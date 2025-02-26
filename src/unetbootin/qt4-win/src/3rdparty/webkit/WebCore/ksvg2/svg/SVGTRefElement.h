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

#ifndef SVGTRefElement_h
#define SVGTRefElement_h
#if ENABLE(SVG)

#include "SVGTextPositioningElement.h"
#include "SVGURIReference.h"

namespace WebCore
{
    class SVGTRefElement : public SVGTextPositioningElement, public SVGURIReference
    {
    public:
        SVGTRefElement(const QualifiedName&, Document*);
        virtual ~SVGTRefElement();

        virtual void attributeChanged(Attribute* attr, bool preserveDecls);
        virtual void parseMappedAttribute(MappedAttribute*);

        virtual RenderObject* createRenderer(RenderArena*, RenderStyle*);
        bool childShouldCreateRenderer(Node*) const;

    protected:
        virtual const SVGElement* contextElement() const { return this; }

    private:
        ANIMATED_PROPERTY_FORWARD_DECLARATIONS(SVGURIReference, String, Href, href)

        void updateReferencedText();
    };

} // namespace WebCore

#endif // ENABLE(SVG)
#endif

// vim:ts=4:noet
