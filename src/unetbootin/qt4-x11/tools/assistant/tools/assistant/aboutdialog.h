/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Qt Assistant of the Qt Toolkit.
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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtGui/QTextBrowser>
#include <QtGui/QDialog>

QT_BEGIN_NAMESPACE

class QLabel;
class QPushButton;
class QGridLayout;

class AboutLabel : public QTextBrowser
{
    Q_OBJECT

public:
    AboutLabel(QWidget *parent = 0);
    void setText(const QString &text, const QByteArray &resources);
    QSize minimumSizeHint() const;
    
private:
    QVariant loadResource(int type, const QUrl &name);
    void setSource(const QUrl &url);

    QMap<QString, QByteArray> m_resourceMap;
};

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = 0);
    void setText(const QString &text, const QByteArray &resources);
    void setPixmap(const QPixmap &pixmap);
    QString documentTitle() const;

private:
    void updateSize();

    QLabel *m_pixmapLabel;
    AboutLabel *m_aboutLabel;
    QPushButton *m_closeButton;
    QGridLayout *m_layout;
};

QT_END_NAMESPACE

#endif
