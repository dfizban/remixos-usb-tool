/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QATOMIC_S390_H
#define QATOMIC_S390_H

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isReferenceCountingNative()
{ return true; }
inline bool QBasicAtomicInt::isReferenceCountingWaitFree()
{ return false; }

#define Q_ATOMIC_INT_TEST_AND_SET_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isTestAndSetNative()
{ return true; }
inline bool QBasicAtomicInt::isTestAndSetWaitFree()
{ return false; }

#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isFetchAndStoreNative()
{ return true; }
inline bool QBasicAtomicInt::isFetchAndStoreWaitFree()
{ return false; }

#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isFetchAndAddNative()
{ return true; }
inline bool QBasicAtomicInt::isFetchAndAddWaitFree()
{ return false; }

#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetNative()
{ return true; }
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetWaitFree()
{ return false; }

#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreNative()
{ return true; }
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreWaitFree()
{ return false; }

#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddNative()
{ return true; }
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddWaitFree()
{ return false; }

#ifdef __GNUC__
#define __GNU_EXTENSION __extension__
#else
#define __GNU_EXTENSION
#endif

#define __CS_LOOP(ptr, op_val, op_string, pre, post) __GNU_EXTENSION ({   \
	volatile int old_val, new_val;					\
        __asm__ __volatile__(pre                                        \
                             "   l     %0,0(%3)\n"                      \
                             "0: lr    %1,%0\n"				\
                             op_string "  %1,%4\n"			\
                             "   cs    %0,%1,0(%3)\n"			\
                             "   jl    0b\n"				\
                             post                                       \
                             : "=&d" (old_val), "=&d" (new_val),	\
			       "=m" (*ptr)	\
			     : "a" (ptr), "d" (op_val),			\
			       "m" (*ptr)	\
			     : "cc", "memory" );			\
	new_val;							\
})

#define __CS_OLD_LOOP(ptr, op_val, op_string, pre, post ) __GNU_EXTENSION ({ \
	volatile int old_val, new_val;					\
        __asm__ __volatile__(pre                                        \
                             "   l     %0,0(%3)\n"			\
                             "0: lr    %1,%0\n"				\
                             op_string "  %1,%4\n"			\
                             "   cs    %0,%1,0(%3)\n"			\
                             "   jl    0b\n"				\
                             post                                       \
                             : "=&d" (old_val), "=&d" (new_val),	\
			       "=m" (*ptr)	\
			     : "a" (ptr), "d" (op_val),			\
			       "m" (*ptr)	\
			     : "cc", "memory" );			\
	old_val;							\
})

#ifdef __s390x__
#define __CSG_OLD_LOOP(ptr, op_val, op_string, pre, post) __GNU_EXTENSION ({ \
	long old_val, new_val;						\
        __asm__ __volatile__(pre                                        \
                             "   lg    %0,0(%3)\n"                      \
                             "0: lgr   %1,%0\n"				\
                             op_string "  %1,%4\n"			\
                             "   csg   %0,%1,0(%3)\n"			\
                             "   jl    0b\n"				\
                             post                                       \
                             : "=&d" (old_val), "=&d" (new_val),	\
			       "=m" (*ptr)	\
			     : "a" (ptr), "d" (op_val),			\
			       "m" (*ptr)	\
			     : "cc", "memory" );			\
	old_val;							\
})
#endif

inline bool QBasicAtomicInt::ref()
{
    return __CS_LOOP(&_q_value, 1, "ar", "", "") != 0;
}

inline bool QBasicAtomicInt::deref()
{
    return __CS_LOOP(&_q_value, 1, "sr", "", "") != 0;
}

inline bool QBasicAtomicInt::testAndSetRelaxed(int expectedValue, int newValue)
{
    int retval;
    __asm__ __volatile__(
                         "  lr   %0,%3\n"
                         "  cs   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
    return retval == 0;
}

inline bool QBasicAtomicInt::testAndSetAcquire(int expectedValue, int newValue)
{
    int retval;
    __asm__ __volatile__(
                         "  lr   %0,%3\n"
                         "  cs   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:\n"
                         "  bcr 15,0\n"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
    return retval == 0;
}

inline bool QBasicAtomicInt::testAndSetRelease(int expectedValue, int newValue)
{
    int retval;
    __asm__ __volatile__(
                         "  bcr 15,0\n"
                         "  lr   %0,%3\n"
                         "  cs   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
    return retval == 0;
}

inline bool QBasicAtomicInt::testAndSetOrdered(int expectedValue, int newValue)
{
    return testAndSetAcquire(expectedValue, newValue);
}

inline int QBasicAtomicInt::fetchAndStoreRelaxed(int newValue)
{
    return __CS_OLD_LOOP(&_q_value, newValue, "lr", "", "");
}

inline int QBasicAtomicInt::fetchAndStoreAcquire(int newValue)
{
    return __CS_OLD_LOOP(&_q_value, newValue, "lr", "", "bcr 15,0\n");
}

inline int QBasicAtomicInt::fetchAndStoreRelease(int newValue)
{
    return __CS_OLD_LOOP(&_q_value, newValue, "lr", "bcr 15,0\n", "");
}

inline int QBasicAtomicInt::fetchAndStoreOrdered(int newValue)
{
    return fetchAndStoreAcquire(newValue);
}

inline int QBasicAtomicInt::fetchAndAddRelaxed(int valueToAdd)
{
    return fetchAndAddOrdered(valueToAdd);
}

inline int QBasicAtomicInt::fetchAndAddAcquire(int valueToAdd)
{
    return fetchAndAddOrdered(valueToAdd);
}

inline int QBasicAtomicInt::fetchAndAddRelease(int valueToAdd)
{
    return fetchAndAddOrdered(valueToAdd);
}

inline int QBasicAtomicInt::fetchAndAddOrdered(int valueToAdd)
{
    return __CS_OLD_LOOP(&_q_value, valueToAdd, "ar", "", "bcr 15,0\n");
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelaxed(T *expectedValue, T *newValue)
{
    int retval;

#ifndef __s390x__
    __asm__ __volatile__(
                         "  lr   %0,%3\n"
                         "  cs   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
#else
    __asm__ __volatile__(
                         "  lgr   %0,%3\n"
                         "  csg   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
#endif

    return retval == 0;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetAcquire(T *expectedValue, T *newValue)
{
    int retval;

#ifndef __s390x__
    __asm__ __volatile__(
                         "  lr   %0,%3\n"
                         "  cs   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:\n"
                         "  bcr 15,0\n"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
#else
    __asm__ __volatile__(
                         "  lgr   %0,%3\n"
                         "  csg   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:\n"
                         "  bcr 15,0\n"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
#endif

    return retval == 0;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelease(T *expectedValue, T *newValue)
{
    int retval;

#ifndef __s390x__
    __asm__ __volatile__(
                         "  bcr 15,0\n"
                         "  lr   %0,%3\n"
                         "  cs   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
#else
    __asm__ __volatile__(
                         "  bcr 15,0\n"
                         "  lgr   %0,%3\n"
                         "  csg   %0,%4,0(%2)\n"
                         "  ipm  %0\n"
                         "  srl  %0,28\n"
                         "0:"
                         : "=&d" (retval), "=m" (_q_value)
                         : "a" (&_q_value), "d" (expectedValue) , "d" (newValue),
                           "m" (_q_value) : "cc", "memory" );
#endif

    return retval == 0;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetOrdered(T *expectedValue, T *newValue)
{
    return testAndSetAcquire(expectedValue, newValue);
}

template <typename T>
Q_INLINE_TEMPLATE T* QBasicAtomicPointer<T>::fetchAndStoreRelaxed(T *newValue)
{
#ifndef __s390x__
    return (T*)__CS_OLD_LOOP(reinterpret_cast<volatile long*>(_q_value), (int)newValue, "lr",
                             "", "bcr 15,0\n");
#else
    return (T*)__CSG_OLD_LOOP(reinterpret_cast<volatile long*>(_q_value), (long)newValue, "lgr",
                              "", "bcr 15,0\n");
#endif
}

template <typename T>
Q_INLINE_TEMPLATE T* QBasicAtomicPointer<T>::fetchAndStoreAcquire(T *newValue)
{
#ifndef __s390x__
    return (T*)__CS_OLD_LOOP(reinterpret_cast<volatile long*>(_q_value), (int)newValue, "lr", "", "");
#else
    return (T*)__CSG_OLD_LOOP(reinterpret_cast<volatile long*>(_q_value), (long)newValue, "lgr", "", "");
#endif
}

template <typename T>
Q_INLINE_TEMPLATE T* QBasicAtomicPointer<T>::fetchAndStoreRelease(T *newValue)
{
#ifndef __s390x__
    return (T*)__CS_OLD_LOOP(reinterpret_cast<volatile long*>(_q_value), (int)newValue, "lr",
                             "bcr 15,0 \n", "");
#else
    return (T*)__CSG_OLD_LOOP(reinterpret_cast<volatile long*>(_q_value), (long)newValue, "lgr",
                              "bcr 15,0\n", "");
#endif
}

template <typename T>
Q_INLINE_TEMPLATE T* QBasicAtomicPointer<T>::fetchAndStoreOrdered(T *newValue)
{
    return fetchAndStoreAcquire(newValue);
}


template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelaxed(qptrdiff valueToAdd)
{
    return fetchAndAddOrdered(valueToAdd);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddAcquire(qptrdiff valueToAdd)
{
    return fetchAndAddOrdered(valueToAdd);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelease(qptrdiff valueToAdd)
{
    return fetchAndAddOrdered(valueToAdd);
}

#undef __GNU_EXTENSION

QT_END_NAMESPACE

QT_END_HEADER

#endif // QATOMIC_S390_H
