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

#include "SVGElement.h"
#include "JSSVGAnimatedAngle.h"

#include <wtf/GetPtr.h>

#include "JSSVGAngle.h"
#include "SVGAngle.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGAnimatedAngle)

/* Hash table */

static const HashTableValue JSSVGAnimatedAngleTableValues[3] =
{
    { "baseVal", DontDelete|ReadOnly, (intptr_t)jsSVGAnimatedAngleBaseVal, (intptr_t)0 },
    { "animVal", DontDelete|ReadOnly, (intptr_t)jsSVGAnimatedAngleAnimVal, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedAngleTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGAnimatedAngleTableValues, 0 };
#else
    { 4, 3, JSSVGAnimatedAngleTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGAnimatedAnglePrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedAnglePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGAnimatedAnglePrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGAnimatedAnglePrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGAnimatedAnglePrototype::s_info = { "SVGAnimatedAnglePrototype", 0, &JSSVGAnimatedAnglePrototypeTable, 0 };

JSObject* JSSVGAnimatedAnglePrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSSVGAnimatedAngle>(exec);
}

const ClassInfo JSSVGAnimatedAngle::s_info = { "SVGAnimatedAngle", 0, &JSSVGAnimatedAngleTable, 0 };

JSSVGAnimatedAngle::JSSVGAnimatedAngle(PassRefPtr<Structure> structure, PassRefPtr<SVGAnimatedAngle> impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGAnimatedAngle::~JSSVGAnimatedAngle()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());

}

JSObject* JSSVGAnimatedAngle::createPrototype(ExecState* exec)
{
    return new (exec) JSSVGAnimatedAnglePrototype(JSSVGAnimatedAnglePrototype::createStructure(exec->lexicalGlobalObject()->objectPrototype()));
}

bool JSSVGAnimatedAngle::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGAnimatedAngle, Base>(exec, &JSSVGAnimatedAngleTable, this, propertyName, slot);
}

JSValuePtr jsSVGAnimatedAngleBaseVal(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGAnimatedAngle* imp = static_cast<SVGAnimatedAngle*>(static_cast<JSSVGAnimatedAngle*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->baseVal()), static_cast<JSSVGAnimatedAngle*>(asObject(slot.slotBase()))->context());
}

JSValuePtr jsSVGAnimatedAngleAnimVal(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGAnimatedAngle* imp = static_cast<SVGAnimatedAngle*>(static_cast<JSSVGAnimatedAngle*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->animVal()), static_cast<JSSVGAnimatedAngle*>(asObject(slot.slotBase()))->context());
}

JSC::JSValuePtr toJS(JSC::ExecState* exec, SVGAnimatedAngle* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGAnimatedAngle>(exec, object, context);
}
SVGAnimatedAngle* toSVGAnimatedAngle(JSC::JSValuePtr value)
{
    return value->isObject(&JSSVGAnimatedAngle::s_info) ? static_cast<JSSVGAnimatedAngle*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)
