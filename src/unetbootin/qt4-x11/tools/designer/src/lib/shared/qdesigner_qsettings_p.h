/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
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
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef QDESIGNER_QSETTINGS_H
#define QDESIGNER_QSETTINGS_H

#include "abstractsettings_p.h"
#include "shared_global_p.h"

#include <QtCore/QSettings>

QT_BEGIN_NAMESPACE

//  Implements QDesignerSettingsInterface by calls to QSettings
class QDESIGNER_SHARED_EXPORT QDesignerQSettings : public QDesignerSettingsInterface
{
public:
    QDesignerQSettings();

    virtual void beginGroup(const QString &prefix);
    virtual void endGroup();

    virtual bool contains(const QString &key) const;
    virtual void setValue(const QString &key, const QVariant &value);
    virtual QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
    virtual void remove(const QString &key);

    // The application name to be used for settings. Allows for including
    // the Qt version to prevent settings of different Qt versions from
    // interfering.
    static QString settingsApplicationName();

private:
    QSettings m_settings;
};

QT_END_NAMESPACE

#endif // QDESIGNER_QSETTINGS_H
