// -*- mode: c++; c-basic-offset: 4 -*-
/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef JSBase_h
#define JSBase_h

#include <stdbool.h>

/* JavaScript engine interface */

/*! @typedef JSContextRef A JavaScript execution context. Holds the global object and other execution state. */
typedef const struct OpaqueJSContext* JSContextRef;

/*! @typedef JSGlobalContextRef A global JavaScript execution context. A JSGlobalContext is a JSContext. */
typedef struct OpaqueJSContext* JSGlobalContextRef;

/*! @typedef JSString A UTF16 character buffer. The fundamental string representation in JavaScript. */
typedef struct OpaqueJSString* JSStringRef;

/*! @typedef JSClassRef A JavaScript class. Used with JSObjectMake to construct objects with custom behavior. */
typedef struct OpaqueJSClass* JSClassRef;

/*! @typedef JSPropertyNameArrayRef An array of JavaScript property names. */
typedef struct OpaqueJSPropertyNameArray* JSPropertyNameArrayRef;

/*! @typedef JSPropertyNameAccumulatorRef An ordered set used to collect the names of a JavaScript object's properties. */
typedef struct OpaqueJSPropertyNameAccumulator* JSPropertyNameAccumulatorRef;


/* JavaScript data types */

/*! @typedef JSValueRef A JavaScript value. The base type for all JavaScript values, and polymorphic functions on them. */
typedef const struct OpaqueJSValue* JSValueRef;

/*! @typedef JSObjectRef A JavaScript object. A JSObject is a JSValue. */
typedef struct OpaqueJSValue* JSObjectRef;

#ifdef __cplusplus
extern "C" {
#endif

/* Script Evaluation */

/*!
@function
@abstract Evaluates a string of JavaScript.
@param ctx The execution context to use.
@param script A JSString containing the script to evaluate.
@param thisObject The object to use as "this," or NULL to use the global object as "this."
@param sourceURL A JSString containing a URL for the script's source file. This is only used when reporting exceptions. Pass NULL if you do not care to include source file information in exceptions.
@param startingLineNumber An integer value specifying the script's starting line number in the file located at sourceURL. This is only used when reporting exceptions.
@param exception A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
@result The JSValue that results from evaluating script, or NULL if an exception is thrown.
*/
JSValueRef JSEvaluateScript(JSContextRef ctx, JSStringRef script, JSObjectRef thisObject, JSStringRef sourceURL, int startingLineNumber, JSValueRef* exception);

/*!
@function JSCheckScriptSyntax
@abstract Checks for syntax errors in a string of JavaScript.
@param ctx The execution context to use.
@param script A JSString containing the script to check for syntax errors.
@param sourceURL A JSString containing a URL for the script's source file. This is only used when reporting exceptions. Pass NULL if you do not care to include source file information in exceptions.
@param startingLineNumber An integer value specifying the script's starting line number in the file located at sourceURL. This is only used when reporting exceptions.
@param exception A pointer to a JSValueRef in which to store a syntax error exception, if any. Pass NULL if you do not care to store a syntax error exception.
@result true if the script is syntactically correct, otherwise false.
*/
bool JSCheckScriptSyntax(JSContextRef ctx, JSStringRef script, JSStringRef sourceURL, int startingLineNumber, JSValueRef* exception);

/*!
@function
@abstract Performs a JavaScript garbage collection. 
@param ctx This parameter is currently unused. Pass NULL.
@discussion JavaScript values that are on the machine stack, in a register, 
 protected by JSValueProtect, set as the global object of an execution context, 
 or reachable from any such value will not be collected. 
 
 During JavaScript execution, you are not required to call this function; the 
 JavaScript engine will garbage collect as needed. One place you may want to call 
 this function, however, is after releasing the last reference to a JSGlobalContextRef. 
 At that point, a garbage collection can free the objects still referenced by the 
 JSGlobalContextRef's global object, along with the global object itself.
*/
void JSGarbageCollect(JSContextRef ctx);

#ifdef __cplusplus
}
#endif

#endif // JSBase_h
