/*
    Copyright (C) 2004, 2005, 2006 Nikolas Zimmermann <wildfox@kde.org>
                  2004, 2005 Rob Buis <buis@kde.org>
                  2005 Eric Seidel <eric.seidel@kdemail.net>

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
    aint with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef SVGFEMerge_h
#define SVGFEMerge_h

#if ENABLE(SVG) && ENABLE(SVG_EXPERIMENTAL_FEATURES)
#include "SVGFilterEffect.h"

namespace WebCore {

class SVGFEMerge : public SVGFilterEffect {
public:
    const Vector<String>& mergeInputs() const;
    void setMergeInputs(const Vector<String>& mergeInputs);

    virtual TextStream& externalRepresentation(TextStream&) const;

#if PLATFORM(CI)
    virtual CIFilter* getCIFilter(SVGResourceFilter*) const;
#endif

private:
    Vector<String> m_mergeInputs;
};

} // namespace WebCore

#endif // ENABLE(SVG) && ENABLE(SVG_EXPERIMENTAL_FEATURES)

#endif // SVGFEMerge_h
