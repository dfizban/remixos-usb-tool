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

#include "qfilesystemwatcher.h"
#include "qfilesystemwatcher_dnotify_p.h"

#ifndef QT_NO_FILESYSTEMWATCHER

#include <qsocketnotifier.h>
#include <qcoreapplication.h>
#include <qfileinfo.h>
#include <qtimer.h>
#include <qwaitcondition.h>
#include <qmutex.h>
#include <dirent.h>
#include <qdir.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

QT_BEGIN_NAMESPACE

static int qfswd_fileChanged_pipe[2];
static void (*qfswd_old_sigio_handler)(int) = 0;
static void (*qfswd_old_sigio_action)(int, siginfo_t *, void *) = 0;
static void qfswd_sigio_monitor(int signum, siginfo_t *i, void *v)
{
    ::write(qfswd_fileChanged_pipe[1], &i->si_fd, sizeof(int));

    if (qfswd_old_sigio_handler && qfswd_old_sigio_handler != SIG_IGN)
        qfswd_old_sigio_handler(signum);
    if (qfswd_old_sigio_action)
        qfswd_old_sigio_action(signum, i, v);
}

class QDnotifySignalThread : public QThread
{
Q_OBJECT
public:
    QDnotifySignalThread();
    virtual ~QDnotifySignalThread();

    void startNotify();

    virtual void run();

signals:
    void fdChanged(int);

protected:
    virtual bool event(QEvent *);

private slots:
    void readFromDnotify();

private:
    QMutex mutex;
    QWaitCondition wait;
    bool isExecing;
};

Q_GLOBAL_STATIC(QDnotifySignalThread, dnotifySignal);

QDnotifySignalThread::QDnotifySignalThread()
: isExecing(false)
{
    moveToThread(this);

    ::pipe(qfswd_fileChanged_pipe);
    ::fcntl(qfswd_fileChanged_pipe[0], F_SETFL,
            ::fcntl(qfswd_fileChanged_pipe[0], F_GETFL) | O_NONBLOCK);

    struct sigaction oldAction;
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = qfswd_sigio_monitor;
    action.sa_flags = SA_SIGINFO;
    ::sigaction(SIGIO, &action, &oldAction);
    if (!(oldAction.sa_flags & SA_SIGINFO))
        qfswd_old_sigio_handler = oldAction.sa_handler;
    else
        qfswd_old_sigio_action = oldAction.sa_sigaction;
}

QDnotifySignalThread::~QDnotifySignalThread()
{
    if(isRunning()) {
        quit();
        QThread::wait();
    }
}

bool QDnotifySignalThread::event(QEvent *e)
{
    if(e->type() == QEvent::User) {
        QMutexLocker locker(&mutex);
        isExecing = true;
        wait.wakeAll();
        return true;
    } else {
        return QThread::event(e);
    }
}

void QDnotifySignalThread::startNotify()
{
    // Note: All this fancy waiting for the thread to enter its event
    // loop is to avoid nasty messages at app shutdown when the
    // QDnotifySignalThread singleton is deleted
    start();
    mutex.lock();
    while(!isExecing)
        wait.wait(&mutex);
    mutex.unlock();
}

void QDnotifySignalThread::run()
{
    QSocketNotifier sn(qfswd_fileChanged_pipe[0], QSocketNotifier::Read, this);
    connect(&sn, SIGNAL(activated(int)), SLOT(readFromDnotify()));

    QCoreApplication::instance()->postEvent(this, new QEvent(QEvent::User));
    (void) exec();
}

void QDnotifySignalThread::readFromDnotify()
{
    int fd;
    int readrv = ::read(qfswd_fileChanged_pipe[0], &fd,sizeof(int));
    // Only expect EAGAIN or EINTR.  Other errors are assumed to be impossible.
    if(readrv != -1) {
        Q_ASSERT(readrv == sizeof(int));
        Q_UNUSED(readrv);

        if(0 == fd)
            quit();
        else
            emit fdChanged(fd);
    }
}

QDnotifyFileSystemWatcherEngine::QDnotifyFileSystemWatcherEngine()
{
    QObject::connect(dnotifySignal(), SIGNAL(fdChanged(int)),
                     this, SLOT(refresh(int)), Qt::DirectConnection);
}

QDnotifyFileSystemWatcherEngine::~QDnotifyFileSystemWatcherEngine()
{
    QMutexLocker locker(&mutex);

    for(QHash<int, Directory>::ConstIterator iter = fdToDirectory.begin();
            iter != fdToDirectory.end();
            ++iter) {
        ::close(iter->fd);
        if(iter->parentFd)
            ::close(iter->parentFd);
    }
}

QDnotifyFileSystemWatcherEngine *QDnotifyFileSystemWatcherEngine::create()
{
    return new QDnotifyFileSystemWatcherEngine();
}

void QDnotifyFileSystemWatcherEngine::run()
{
    qFatal("QDnotifyFileSystemWatcherEngine thread should not be run");
}

QStringList QDnotifyFileSystemWatcherEngine::addPaths(const QStringList &paths, QStringList *files, QStringList *directories)
{
    QMutexLocker locker(&mutex);

    QStringList p = paths;
    QMutableListIterator<QString> it(p);

    while (it.hasNext()) {
        QString path = it.next();

        QFileInfo fi(path);

        if(!fi.exists()) {
            continue;
        }

        bool isDir = fi.isDir();

        if (isDir && directories->contains(path)) {
            continue; // Skip monitored directories
        } else if(!isDir && files->contains(path)) {
            continue; // Skip monitored files
        }

        QString fileName;
        if(!isDir) {
            path = fi.path();
            fileName = fi.fileName();
        }

        // Locate the directory entry (creating if needed)
        int fd = pathToFD[path];

        if(fd == 0) {

            DIR *d = ::opendir(path.toUtf8().constData());
            if(!d) continue; // Could not open directory
            DIR *parent = 0;

            QDir parentDir(path);
            if(!parentDir.isRoot()) {
                parentDir.cdUp();
                parent = ::opendir(parentDir.path().toUtf8().constData());
                if(!parent) {
                    ::closedir(d);
                    continue;
                }
            }

            fd = ::dirfd(d);
            int parentFd = parent?::dirfd(parent):0;

            Q_ASSERT(fd);
            if(::fcntl(fd, F_SETSIG, SIGIO) ||
               ::fcntl(fd, F_NOTIFY, DN_MODIFY | DN_CREATE | DN_DELETE |
                                     DN_RENAME | DN_ATTRIB | DN_MULTISHOT) ||
               (parent && ::fcntl(parentFd, F_SETSIG, SIGIO)) ||
               (parent && ::fcntl(parentFd, F_NOTIFY, DN_DELETE | DN_RENAME |
                                            DN_MULTISHOT))) {

                ::closedir(d);
                if(parent) ::closedir(parent);

                continue; // Could not set appropriate flags
            }

            Directory dir;
            dir.path = path;
            dir.fd = fd;
            dir.parentFd = parentFd;

            fdToDirectory.insert(fd, dir);
            pathToFD.insert(path, fd);
            if(parentFd)
                parentToFD.insert(parentFd, fd);
        }

        Directory &directory = fdToDirectory[fd];

        if(isDir) {
            directory.isMonitored = true;
        } else {
            Directory::File file;
            file.name = fileName;
            file.lastWrite = fi.lastModified();
            directory.files.append(file);
            pathToFD.insert(fi.filePath(), fd);
        }

        it.remove();

        if(isDir) {
            directories->append(path);
        } else {
            files->append(fi.filePath());
        }
    }

    dnotifySignal()->startNotify();

    return p;
}

QStringList QDnotifyFileSystemWatcherEngine::removePaths(const QStringList &paths, QStringList *files, QStringList *directories)
{
    QMutexLocker locker(&mutex);

    QStringList p = paths;
    QMutableListIterator<QString> it(p);
    while (it.hasNext()) {

        QString path = it.next();
        int fd = pathToFD.take(path);

        if(!fd)
            continue;

        Directory &directory = fdToDirectory[fd];
        bool isDir = false;
        if(directory.path == path) {
            isDir = true;
            directory.isMonitored = false;
        } else {
            for(int ii = 0; ii < directory.files.count(); ++ii) {
                if(directory.files.at(ii).name == path) {
                    directory.files.removeAt(ii);
                    break;
                }
            }
        }

        if(!directory.isMonitored && directory.files.isEmpty()) {
            // No longer needed
            ::close(directory.fd);
            pathToFD.remove(directory.path);
            fdToDirectory.remove(fd);
        }

        if(isDir) {
            directories->removeAll(path);
        } else {
            files->removeAll(path);
        }

        it.remove();
    }

    return p;
}

void QDnotifyFileSystemWatcherEngine::refresh(int fd)
{
    QMutexLocker locker(&mutex);

    bool wasParent = false;
    QHash<int, Directory>::Iterator iter = fdToDirectory.find(fd);
    if(iter == fdToDirectory.end()) {
        QHash<int, int>::Iterator pIter = parentToFD.find(fd);
        if(pIter == parentToFD.end())
            return;

        iter = fdToDirectory.find(*pIter);
        if (iter == fdToDirectory.end())
            return;
        wasParent = true;
    }

    Directory &directory = *iter;

    if(!wasParent) {
        for(int ii = 0; ii < directory.files.count(); ++ii) {
            Directory::File &file = directory.files[ii];
            if(file.updateInfo()) {
                // Emit signal
                QString filename = file.name;
                bool removed = !QFileInfo(file.name).exists();

                if(removed) {
                    directory.files.removeAt(ii);
                    --ii;
                }

                emit fileChanged(filename, removed);
            }
        }
    }

    if(directory.isMonitored) {
        // Emit signal
        bool removed = !QFileInfo(directory.path).exists();
        QString path = directory.path;

        if(removed)
            directory.isMonitored = false;

        emit directoryChanged(path, removed);
    }

    if(!directory.isMonitored && directory.files.isEmpty()) {
        ::close(directory.fd);
        if(directory.parentFd) {
            ::close(directory.parentFd);
            parentToFD.remove(directory.parentFd);
        }
        fdToDirectory.erase(iter);
    }
}

void QDnotifyFileSystemWatcherEngine::stop()
{
}

bool QDnotifyFileSystemWatcherEngine::Directory::File::updateInfo()
{
    QFileInfo fi(name);
    QDateTime nLastWrite = fi.lastModified();
    uint nOwnerId = fi.ownerId();
    uint nGroupId = fi.groupId();
    QFile::Permissions nPermissions = fi.permissions();

    if(nLastWrite != lastWrite ||
       nOwnerId != ownerId ||
       nGroupId != groupId ||
       nPermissions != permissions) {
        ownerId = nOwnerId;
        groupId = nGroupId;
        permissions = nPermissions;
        lastWrite = nLastWrite;
        return true;
    } else {
        return false;
    }
}

QT_END_NAMESPACE

#include "qfilesystemwatcher_dnotify.moc"

#endif // QT_NO_FILESYSTEMWATCHER
