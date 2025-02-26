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
#include "StyleSheet.h"

#include "MediaList.h"

namespace WebCore {

StyleSheet::StyleSheet(StyleSheet* parentSheet, const String& href)
    : StyleList(parentSheet)
    , m_parentNode(0)
    , m_strHref(href)
    , m_disabled(false)
{
}


StyleSheet::StyleSheet(Node* parentNode, const String& href)
    : StyleList(0)
    , m_parentNode(parentNode)
    , m_strHref(href)
    , m_disabled(false)
{
}

StyleSheet::StyleSheet(StyleBase* owner, const String& href)
    : StyleList(owner)
    , m_parentNode(0)
    , m_strHref(href)
    , m_disabled(false)
{
}

StyleSheet::~StyleSheet()
{
    if (m_media)
        m_media->setParent(0);
}

StyleSheet* StyleSheet::parentStyleSheet() const
{
    return (parent() && parent()->isStyleSheet()) ? static_cast<StyleSheet*>(parent()) : 0;
}

void StyleSheet::setMedia(MediaList* media)
{
    if (m_media)
        m_media->setParent(0);

    m_media = media;
    m_media->setParent(this);
}

}
