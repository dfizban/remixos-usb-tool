/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#include "qsocketnotifier.h"

#include "qplatformdefs.h"

#include "qabstracteventdispatcher.h"
#include "qcoreapplication.h"

#include "qobject_p.h"
#include <private/qthread_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QSocketNotifier
    \brief The QSocketNotifier class provides support for monitoring
    activity on a file descriptor.

    \ingroup io

    The QSocketNotifier makes it possible to integrate Qt's event
    loop with other event loops based on file descriptors. For
    example, the \l{CORBA Framework} uses it to process CORBA
    events.  File descriptor action is detected in Qt's main event
    loop (QCoreApplication::exec()).

    \target write notifiers

    Once you have opened a device using a low-level (usually
    platform-specific) API, you can create a socket notifier to
    monitor the file descriptor. The socket notifier is enabled by
    default, i.e. it emits the activated() signal whenever a socket
    event corresponding to its type occurs. Connect the activated()
    signal to the slot you want to be called when an event
    corresponding to your socket notifier's type occurs.

    There are three types of socket notifiers: read, write, and
    exception. The type is described by the \l Type enum, and must be
    specified when constructing the socket notifier. After
    construction it can be determined using the type() function. Note
    that if you need to monitor both reads and writes for the same
    file descriptor, you must create two socket notifiers. Note also
    that it is not possible to install two socket notifiers of the
    same type (\l Read, \l Write, \l Exception) on the same socket.

    The setEnabled() function allows you to disable as well as enable
    the socket notifier. It is generally advisable to explicitly
    enable or disable the socket notifier, especially for write
    notifiers. A disabled notifier ignores socket events (the same
    effect as not creating the socket notifier). Use the isEnabled()
    function to determine the notifier's current status.

    Finally, you can use the socket() function to retrieve the
    socket identifier.  Although the class is called QSocketNotifier,
    it is normally used for other types of devices than sockets.
    QTcpSocket and QUdpSocket provide notification through signals, so
    there is normally no need to use a QSocketNotifier on them.

    \section1 Notes for Windows Users

    The socket passed to QSocketNotifier will become non-blocking, even if
    it was created as a blocking socket.
    The activated() signal is sometimes triggered by high general activity
    on the host, even if there is nothing to read. A subsequent read from
    the socket can then fail, the error indicating that there is no data
    available (e.g., \c{WSAEWOULDBLOCK}). This is an operating system
    limitation, and not a bug in QSocketNotifier.

    To ensure that the socket notifier handles read notifications correctly,
    follow these steps when you receive a notification:

    \list 1
    \o Disable the notifier.
    \o Read data from the socket.
    \o Re-enable the notifier if you are interested in more data (such as after
       having written a new command to a remote server).
    \endlist

    To ensure that the socket notifier handles write notifications correctly,
    follow these steps when you receive a notification:

    \list 1
    \o Disable the notifier.
    \o Write as much data as you can (before \c EWOULDBLOCK is returned).
    \o Re-enable notifier if you have more data to write.
    \endlist

    \bold{Further information:}
    On Windows, Qt always disables the notifier after getting a notification,
    and only re-enables it if more data is expected. For example, if data is
    read from the socket and it can be used to read more, or if reading or
    writing is not possible because the socket would block, in which case
    it is necessary to wait before attempting to read or write again.

    \sa QFile, QProcess, QTcpSocket, QUdpSocket
*/

/*!
    \enum QSocketNotifier::Type

    This enum describes the various types of events that a socket
    notifier can recognize. The type must be specified when
    constructing the socket notifier.

    Note that if you need to monitor both reads and writes for the
    same file descriptor, you must create two socket notifiers. Note
    also that it is not possible to install two socket notifiers of
    the same type (Read, Write, Exception) on the same socket.

    \value Read      There is data to be read.
    \value Write      Data can be written.
    \value Exception  An exception has occurred. We recommend against using this.

    \sa QSocketNotifier(), type()
*/

/*!
    Constructs a socket notifier with the given \a parent. It enables
    the \a socket, and watches for events of the given \a type.

    It is generally advisable to explicitly enable or disable the
    socket notifier, especially for write notifiers.

    \bold{Note for Windows users:} The socket passed to QSocketNotifier
    will become non-blocking, even if it was created as a blocking socket.

    \sa setEnabled(), isEnabled()
*/

QSocketNotifier::QSocketNotifier(int socket, Type type, QObject *parent)
    : QObject(parent)
{
    if (socket < 0)
        qWarning("QSocketNotifier: Invalid socket specified");
    sockfd = socket;
    sntype = type;
    snenabled = true;

    Q_D(QObject);
    if (!d->threadData->eventDispatcher) {
        qWarning("QSocketNotifier: Can only be used with threads started with QThread");
    } else {
        d->threadData->eventDispatcher->registerSocketNotifier(this);
    }
}

#ifdef QT3_SUPPORT
/*!
    \obsolete

    Use the QSocketNotifier() constructor combined with the
    QObject::setObjectName() function instead.

    \oldcode
        QSocketNotifier *notifier = new QSocketNotifier(socket, type, parent, name);
    \newcode
        QSocketNotifier *notifier = new QSocketNotifier(socket, type, parent);
        notifier->setObjectName(name);
    \endcode
*/

QSocketNotifier::QSocketNotifier(int socket, Type type, QObject *parent,
                                  const char *name)
    : QObject(parent)
{
    setObjectName(QString::fromAscii(name));
    if (socket < 0)
        qWarning("QSocketNotifier: Invalid socket specified");
    sockfd = socket;
    sntype = type;
    snenabled = true;

    Q_D(QObject);
    if (!d->threadData->eventDispatcher) {
        qWarning("QSocketNotifier: Can only be used with threads started with QThread");
    } else {
        d->threadData->eventDispatcher->registerSocketNotifier(this);
    }
}
#endif
/*!
    Destroys this socket notifier.
*/

QSocketNotifier::~QSocketNotifier()
{
    setEnabled(false);
}


/*!
    \fn void QSocketNotifier::activated(int socket)

    This signal is emitted whenever the socket notifier is enabled and
    a socket event corresponding to its \l {Type}{type} occurs.

    The socket identifier is passed in the \a socket parameter.

    \sa type(), socket()
*/


/*!
    \fn int QSocketNotifier::socket() const

    Returns the socket identifier specified to the constructor.

    \sa type()
*/

/*!
    \fn Type QSocketNotifier::type() const

    Returns the socket event type specified to the constructor.

    \sa socket()
*/


/*!
    \fn bool QSocketNotifier::isEnabled() const

    Returns true if the notifier is enabled; otherwise returns false.

    \sa setEnabled()
*/

/*!
    If \a enable is true, the notifier is enabled; otherwise the notifier
    is disabled.

    The notifier is enabled by default, i.e. it emits the activated()
    signal whenever a socket event corresponding to its
    \l{type()}{type} occurs. If it is disabled, it ignores socket
    events (the same effect as not creating the socket notifier).

    Write notifiers should normally be disabled immediately after the
    activated() signal has been emitted

    \sa isEnabled(), activated()
*/

void QSocketNotifier::setEnabled(bool enable)
{
    if (sockfd < 0)
        return;
    if (snenabled == enable)                        // no change
        return;
    snenabled = enable;

    Q_D(QObject);
    if (!d->threadData->eventDispatcher) // perhaps application/thread is shutting down
        return;
    if (snenabled)
        d->threadData->eventDispatcher->registerSocketNotifier(this);
    else
        d->threadData->eventDispatcher->unregisterSocketNotifier(this);
}


/*!\reimp
*/
bool QSocketNotifier::event(QEvent *e)
{
    // Emits the activated() signal when a QEvent::SockAct is
    // received.
    if (e->type() == QEvent::ThreadChange) {
        if (snenabled) {
            QMetaObject::invokeMethod(this, "setEnabled", Qt::QueuedConnection,
                                      Q_ARG(bool, snenabled));
            setEnabled(false);
        }
    }
    QObject::event(e);                        // will activate filters
    if (e->type() == QEvent::SockAct) {
        emit activated(sockfd);
        return true;
    }
    return false;
}

QT_END_NAMESPACE
