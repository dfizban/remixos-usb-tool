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

#include "JSHTMLStyleElement.h"

#include <wtf/GetPtr.h>

#include "HTMLStyleElement.h"
#include "JSStyleSheet.h"
#include "KURL.h"
#include "StyleSheet.h"

#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLStyleElement)

/* Hash table */

static const HashTableValue JSHTMLStyleElementTableValues[6] =
{
    { "disabled", DontDelete, (intptr_t)jsHTMLStyleElementDisabled, (intptr_t)setJSHTMLStyleElementDisabled },
    { "media", DontDelete, (intptr_t)jsHTMLStyleElementMedia, (intptr_t)setJSHTMLStyleElementMedia },
    { "type", DontDelete, (intptr_t)jsHTMLStyleElementType, (intptr_t)setJSHTMLStyleElementType },
    { "sheet", DontDelete|ReadOnly, (intptr_t)jsHTMLStyleElementSheet, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLStyleElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLStyleElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 31, JSHTMLStyleElementTableValues, 0 };
#else
    { 17, 15, JSHTMLStyleElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLStyleElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLStyleElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLStyleElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLStyleElementConstructorTableValues, 0 };
#endif

class JSHTMLStyleElementConstructor : public DOMObject {
public:
    JSHTMLStyleElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLStyleElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLStyleElementPrototype::self(exec), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLStyleElementConstructor::s_info = { "HTMLStyleElementConstructor", 0, &JSHTMLStyleElementConstructorTable, 0 };

bool JSHTMLStyleElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLStyleElementConstructor, DOMObject>(exec, &JSHTMLStyleElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLStyleElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLStyleElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLStyleElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLStyleElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLStyleElementPrototype::s_info = { "HTMLStyleElementPrototype", 0, &JSHTMLStyleElementPrototypeTable, 0 };

JSObject* JSHTMLStyleElementPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSHTMLStyleElement>(exec);
}

const ClassInfo JSHTMLStyleElement::s_info = { "HTMLStyleElement", &JSHTMLElement::s_info, &JSHTMLStyleElementTable, 0 };

JSHTMLStyleElement::JSHTMLStyleElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLStyleElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLStyleElement::createPrototype(ExecState* exec)
{
    return new (exec) JSHTMLStyleElementPrototype(JSHTMLStyleElementPrototype::createStructure(JSHTMLElementPrototype::self(exec)));
}

bool JSHTMLStyleElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLStyleElement, Base>(exec, &JSHTMLStyleElementTable, this, propertyName, slot);
}

JSValuePtr jsHTMLStyleElementDisabled(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->disabled());
}

JSValuePtr jsHTMLStyleElementMedia(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->media());
}

JSValuePtr jsHTMLStyleElementType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->type());
}

JSValuePtr jsHTMLStyleElementSheet(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->sheet()));
}

JSValuePtr jsHTMLStyleElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLStyleElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLStyleElement::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLStyleElement, Base>(exec, propertyName, value, &JSHTMLStyleElementTable, this, slot);
}

void setJSHTMLStyleElementDisabled(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(thisObject)->impl());
    imp->setDisabled(value->toBoolean(exec));
}

void setJSHTMLStyleElementMedia(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(thisObject)->impl());
    imp->setMedia(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLStyleElementType(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLStyleElement* imp = static_cast<HTMLStyleElement*>(static_cast<JSHTMLStyleElement*>(thisObject)->impl());
    imp->setType(valueToStringWithNullCheck(exec, value));
}

JSValuePtr JSHTMLStyleElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLStyleElementConstructor>(exec);
}


}
