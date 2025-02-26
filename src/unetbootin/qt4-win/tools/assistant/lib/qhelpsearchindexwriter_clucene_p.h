/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the Qt Assistant of the Qt Toolkit.
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

#ifndef QHELPSEARCHINDEXWRITERCLUCENE_H
#define QHELPSEARCHINDEXWRITERCLUCENE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists for the convenience
// of the help generator tools. This header file may change from version
// to version without notice, or even be removed.
//
// We mean it.
//

#include "qhelpenginecore.h"
#include "fulltextsearch/qanalyzer_p.h"

#include <QtCore/QUrl>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QWaitCondition>

QT_BEGIN_NAMESPACE

class QCLuceneIndexWriter;

namespace qt {
    namespace fulltextsearch {
        namespace clucene {

class QHelpSearchIndexWriter : public QThread
{
    Q_OBJECT

public:
    QHelpSearchIndexWriter();
    ~QHelpSearchIndexWriter();

    void cancelIndexing();
    void updateIndex(const QString &collectionFile, bool reindex);
    void optimizeIndex(const QString &indexFilesPath);

signals:
    void indexingStarted();
    void indexingFinished();
 
private:
    void run();

    bool addDocuments(const QList<QUrl> docFiles, const QHelpEngineCore &engine,
        const QStringList &attributes, const QString &namespaceName, 
        QCLuceneIndexWriter *writer, QCLuceneAnalyzer &analyzer);
    void removeDocuments(const QString &indexPath, const QString &namespaceName);

    QString addNamespace(const QString namespaces, const QString &namespaceName);
    QString removeNamespace(const QString namespaces, const QString &namespaceName);
    

private:
    QMutex mutex;
    QWaitCondition waitCondition;

    bool m_cancel;
    bool m_reindex;
    QString m_collectionFile;
};

        }   // namespace clucene
    }   // namespace fulltextsearch
}   // namespace clucene

QT_END_NAMESPACE

#endif  // QHELPSEARCHINDEXWRITERCLUCENE_H
