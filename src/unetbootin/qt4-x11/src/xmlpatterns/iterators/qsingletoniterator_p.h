/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtXMLPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_SingletonIterator_H
#define Patternist_SingletonIterator_H

#include <QtXmlPatterns/private/qabstractxmlforwarditerator_p.h>

#include <QtXmlPatterns/private/qprimitives_p.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short An QAbstractXmlForwardIterator over exactly one item.
     *
     * SingletonIterator's constructor takes one value which is
     * the item it forms an QAbstractXmlForwardIterator over. Other QAbstractXmlForwardIterator instances can
     * also form an QAbstractXmlForwardIterator with one in length, but by that SingletonIterator
     * has this as it only task, it means it is efficient at it.
     *
     * Having to represent single items in Iterators is relatively common.
     *
     * @author Frans Englich <fenglich@trolltech.com>
     * @ingroup Patternist_iterators
     */
    template<typename T>
    class SingletonIterator : public QAbstractXmlForwardIterator<T>
    {
    public:
        /**
         * Creates an iterator over @p item.
         *
         * @note item may not be @c null. Use the EmptyIterator for
         * the empty sequence
         */
        SingletonIterator(const T &item) : m_item(item),
                                           m_position(0)
        {
            Q_ASSERT(!qIsForwardIteratorEnd(item));
        }

        virtual T next()
        {
            switch(m_position)
            {
                case 0:
                {
                    ++m_position;
                    return m_item;
                }
                case 1:
                {
                    m_position = -1;
                    return T();
                }
                default:
                {
                    Q_ASSERT(m_position == -1);
                    return T();
                }
            }
        }

        virtual T current() const
        {
            if(m_position == 1)
                return m_item;
            else
                return T();
        }

        virtual xsInteger position() const
        {
            return m_position;
        }

        /**
         * @returns a copy of this instance, rewinded to the beginning.
         */
        virtual typename QAbstractXmlForwardIterator<T>::Ptr toReversed()
        {
            return typename QAbstractXmlForwardIterator<T>::Ptr(new SingletonIterator<T>(m_item));
        }

        /**
         * @returns always 1
         */
        virtual xsInteger count()
        {
            return 1;
        }

        virtual typename QAbstractXmlForwardIterator<T>::Ptr copy() const
        {
            return typename QAbstractXmlForwardIterator<T>::Ptr(new SingletonIterator(m_item));
        }

    private:
        const T m_item;
        qint8 m_position;
    };

    /**
     * @short An object generator for SingletonIterator.
     *
     * makeSingletonIterator() is a convenience function for avoiding specifying
     * the full template instantiation for SingletonIterator. Conceptually, it
     * is identical to Qt's qMakePair().
     *
     * @relates SingletonIterator
     */
    template<typename T>
    inline
    typename SingletonIterator<T>::Ptr
    makeSingletonIterator(const T &item)
    {
        return typename SingletonIterator<T>::Ptr(new SingletonIterator<T>(item));
    }
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
