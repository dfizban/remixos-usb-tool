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


#if ENABLE(SVG)

#include "Document.h"
#include "Frame.h"
#include "SVGDocumentExtensions.h"
#include "SVGElement.h"
#include "SVGAnimatedTemplate.h"
#include "JSSVGAnimatedNumber.h"

#include <wtf/GetPtr.h>


using namespace KJS;

namespace WebCore {

/* Hash table */

static const HashEntry JSSVGAnimatedNumberTableEntries[] =
{
    { "baseVal", JSSVGAnimatedNumber::BaseValAttrNum, DontDelete, 0, 0 },
    { "animVal", JSSVGAnimatedNumber::AnimValAttrNum, DontDelete|ReadOnly, 0, 0 }
};

static const HashTable JSSVGAnimatedNumberTable = 
{
    2, 2, JSSVGAnimatedNumberTableEntries, 2
};

/* Hash table for prototype */

static const HashEntry JSSVGAnimatedNumberPrototypeTableEntries[] =
{
    { 0, 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedNumberPrototypeTable = 
{
    2, 1, JSSVGAnimatedNumberPrototypeTableEntries, 1
};

const ClassInfo JSSVGAnimatedNumberPrototype::info = { "SVGAnimatedNumberPrototype", 0, &JSSVGAnimatedNumberPrototypeTable, 0 };

JSObject* JSSVGAnimatedNumberPrototype::self(ExecState* exec)
{
    return KJS::cacheGlobalObject<JSSVGAnimatedNumberPrototype>(exec, "[[JSSVGAnimatedNumber.prototype]]");
}

const ClassInfo JSSVGAnimatedNumber::info = { "SVGAnimatedNumber", 0, &JSSVGAnimatedNumberTable, 0 };

JSSVGAnimatedNumber::JSSVGAnimatedNumber(ExecState* exec, SVGAnimatedNumber* impl)
    : m_impl(impl)
{
    setPrototype(JSSVGAnimatedNumberPrototype::self(exec));
}

JSSVGAnimatedNumber::~JSSVGAnimatedNumber()
{
    SVGDocumentExtensions::forgetGenericContext<SVGAnimatedNumber>(m_impl.get());
    ScriptInterpreter::forgetDOMObject(m_impl.get());
}

bool JSSVGAnimatedNumber::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGAnimatedNumber, KJS::DOMObject>(exec, &JSSVGAnimatedNumberTable, this, propertyName, slot);
}

JSValue* JSSVGAnimatedNumber::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case BaseValAttrNum: {
        SVGAnimatedNumber* imp = static_cast<SVGAnimatedNumber*>(impl());

        return jsNumber(imp->baseVal());
    }
    case AnimValAttrNum: {
        SVGAnimatedNumber* imp = static_cast<SVGAnimatedNumber*>(impl());

        return jsNumber(imp->animVal());
    }
    }
    return 0;
}

void JSSVGAnimatedNumber::put(ExecState* exec, const Identifier& propertyName, JSValue* value, int attr)
{
    lookupPut<JSSVGAnimatedNumber, KJS::DOMObject>(exec, propertyName, value, attr, &JSSVGAnimatedNumberTable, this);
}

void JSSVGAnimatedNumber::putValueProperty(ExecState* exec, int token, JSValue* value, int /*attr*/)
{
    switch (token) {
    case BaseValAttrNum: {
        SVGAnimatedNumber* imp = static_cast<SVGAnimatedNumber*>(impl());

        imp->setBaseVal(value->toFloat(exec));
        break;
    }
    }
    SVGAnimatedNumber* imp = static_cast<SVGAnimatedNumber*>(impl());

    ASSERT(exec && exec->dynamicInterpreter());
    Frame* activeFrame = static_cast<ScriptInterpreter*>(exec->dynamicInterpreter())->frame();
    if (!activeFrame)
        return;

    SVGDocumentExtensions* extensions = (activeFrame->document() ? activeFrame->document()->accessSVGExtensions() : 0);
    if (extensions && extensions->hasGenericContext<SVGAnimatedNumber>(imp)) {
        const SVGElement* context = extensions->genericContext<SVGAnimatedNumber>(imp);
        ASSERT(context);

        context->notifyAttributeChange();
    }

}

KJS::JSValue* toJS(KJS::ExecState* exec, SVGAnimatedNumber* obj)
{
    return KJS::cacheDOMObject<SVGAnimatedNumber, JSSVGAnimatedNumber>(exec, obj);
}
SVGAnimatedNumber* toSVGAnimatedNumber(KJS::JSValue* val)
{
    return val->isObject(&JSSVGAnimatedNumber::info) ? static_cast<JSSVGAnimatedNumber*>(val)->impl() : 0;
}

}

#endif // ENABLE(SVG)
