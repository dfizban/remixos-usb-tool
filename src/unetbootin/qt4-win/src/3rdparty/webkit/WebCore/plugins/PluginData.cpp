/*
    Copyright (C) 2000 Harri Porten (porten@kde.org)
    Copyright (C) 2000 Daniel Molkentin (molkentin@kde.org)
    Copyright (C) 2000 Stefan Schimanski (schimmi@kde.org)
    Copyright (C) 2003, 2004, 2005, 2006, 2007 Apple Inc. All Rights Reserved.
    Copyright (C) 2008 Trolltech ASA

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
#include "PluginData.h"

namespace WebCore {

PluginData::PluginData(const Page* page)
    : m_page(page)
{
    initPlugins();

    for (unsigned i = 0; i < m_plugins.size(); ++i) {
        const PluginInfo* plugin = m_plugins[i];
        for (unsigned j = 0; j < plugin->mimes.size(); ++j)
            m_mimes.append(plugin->mimes[j]);
    }
}

PluginData::~PluginData()
{
    deleteAllValues(m_plugins);
    deleteAllValues(m_mimes);
}

bool PluginData::supportsMimeType(const String& mimeType) const
{
    for (unsigned i = 0; i < m_mimes.size(); ++i)
        if (m_mimes[i]->type == mimeType)
            return true;
    return false;
}

}
