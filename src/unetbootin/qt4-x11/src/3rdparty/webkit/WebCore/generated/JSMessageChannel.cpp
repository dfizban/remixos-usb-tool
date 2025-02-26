/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

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

#include "JSMessageChannel.h"

#include <wtf/GetPtr.h>

#include "JSMessagePort.h"
#include "MessageChannel.h"
#include "MessagePort.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSMessageChannel)

/* Hash table */

static const HashTableValue JSMessageChannelTableValues[3] =
{
    { "port1", DontDelete|ReadOnly, (intptr_t)jsMessageChannelPort1, (intptr_t)0 },
    { "port2", DontDelete|ReadOnly, (intptr_t)jsMessageChannelPort2, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSMessageChannelTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 3, JSMessageChannelTableValues, 0 };
#else
    { 4, 3, JSMessageChannelTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSMessageChannelPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSMessageChannelPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSMessageChannelPrototypeTableValues, 0 };
#else
    { 1, 0, JSMessageChannelPrototypeTableValues, 0 };
#endif

static const HashTable* getJSMessageChannelPrototypeTable(ExecState* exec)
{
    return getHashTableForGlobalData(exec->globalData(), &JSMessageChannelPrototypeTable);
}
const ClassInfo JSMessageChannelPrototype::s_info = { "MessageChannelPrototype", 0, 0, getJSMessageChannelPrototypeTable };

JSObject* JSMessageChannelPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSMessageChannel>(exec);
}

static const HashTable* getJSMessageChannelTable(ExecState* exec)
{
    return getHashTableForGlobalData(exec->globalData(), &JSMessageChannelTable);
}
const ClassInfo JSMessageChannel::s_info = { "MessageChannel", 0, 0, getJSMessageChannelTable };

JSMessageChannel::JSMessageChannel(PassRefPtr<Structure> structure, PassRefPtr<MessageChannel> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSMessageChannel::~JSMessageChannel()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());

}

JSObject* JSMessageChannel::createPrototype(ExecState* exec)
{
    return new (exec) JSMessageChannelPrototype(JSMessageChannelPrototype::createStructure(exec->lexicalGlobalObject()->objectPrototype()));
}

bool JSMessageChannel::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSMessageChannel, Base>(exec, getJSMessageChannelTable(exec), this, propertyName, slot);
}

JSValuePtr jsMessageChannelPort1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MessageChannel* imp = static_cast<MessageChannel*>(static_cast<JSMessageChannel*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->port1()));
}

JSValuePtr jsMessageChannelPort2(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    MessageChannel* imp = static_cast<MessageChannel*>(static_cast<JSMessageChannel*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->port2()));
}

JSC::JSValuePtr toJS(JSC::ExecState* exec, MessageChannel* object)
{
    return getDOMObjectWrapper<JSMessageChannel>(exec, object);
}
MessageChannel* toMessageChannel(JSC::JSValuePtr value)
{
    return value->isObject(&JSMessageChannel::s_info) ? static_cast<JSMessageChannel*>(asObject(value))->impl() : 0;
}

}
