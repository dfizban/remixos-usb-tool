/**
 * This file is part of the DOM implementation for KDE.
 *
 * (C) 1999-2003 Lars Knoll (knoll@kde.org)
 * Copyright (C) 2004, 2006 Apple Computer, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#include "config.h"
#include "StyleSheetList.h"

#include "CSSStyleSheet.h"

namespace WebCore {

StyleSheetList::~StyleSheetList()
{
    for (DeprecatedPtrListIterator<StyleSheet> it (styleSheets); it.current(); ++it)
        it.current()->deref();
}

void StyleSheetList::add(StyleSheet* s)
{
    if (!styleSheets.containsRef(s)) {
        s->ref();
        styleSheets.append(s);
    }
}

void StyleSheetList::remove(StyleSheet* s)
{
    if (styleSheets.removeRef(s))
        s->deref();
}

unsigned StyleSheetList::length() const
{
    return styleSheets.count();
}

StyleSheet* StyleSheetList::item(unsigned index)
{
    return index < length() ? styleSheets.at(index) : 0;
}

}
