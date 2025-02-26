/*
 *  Copyright (C) 2000 Harri Porten (porten@kde.org)
 *  Copyright (C) 2003, 2004, 2005, 2006, 2007 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef kjs_dom_h
#define kjs_dom_h

#include "JSNode.h"
#include "Node.h"
#include "kjs_binding.h"

namespace WebCore {

    class Attr;
    class EventTarget;

    Attr* toAttr(KJS::JSValue*, bool& ok);

    bool checkNodeSecurity(KJS::ExecState*, Node*);
    KJS::JSValue* getRuntimeObject(KJS::ExecState*, Node*);
    KJS::JSValue* toJS(KJS::ExecState*, EventTarget*);
    KJS::JSObject* getNodeConstructor(KJS::ExecState*);

} // namespace WebCore

#endif // kjs_dom_h
