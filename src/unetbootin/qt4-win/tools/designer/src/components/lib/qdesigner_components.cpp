/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#include <QtDesigner/QDesignerComponents>

#include <actioneditor_p.h>
#include <widgetdatabase_p.h>
#include <widgetfactory_p.h>

#include <formeditor/formeditor.h>
#include <widgetbox/widgetbox.h>
#include <propertyeditor/propertyeditor.h>
#include <objectinspector/objectinspector.h>
#include <taskmenu/taskmenu_component.h>
#include "qtresourceview_p.h"
#include <qdesigner_integration_p.h>
#include <signalsloteditor/signalsloteditorwindow.h>

#include <buddyeditor/buddyeditor_plugin.h>
#include <signalsloteditor/signalsloteditor_plugin.h>
#include <tabordereditor/tabordereditor_plugin.h>

#include <QtDesigner/QDesignerLanguageExtension>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerResourceBrowserInterface>

#include <QtCore/qplugin.h>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

// ### keep it in sync with Q_IMPORT_PLUGIN in qplugin.h
#define DECLARE_PLUGIN_INSTANCE(PLUGIN) \
    extern QT_PREPEND_NAMESPACE(QObject) *qt_plugin_instance_##PLUGIN(); \
    class Static##PLUGIN##PluginInstance { public: \
        Static##PLUGIN##PluginInstance() {                      \
            QT_PREPEND_NAMESPACE(qRegisterStaticPluginInstanceFunction) \
                (&qt_plugin_instance_##PLUGIN); \
        } \
    };

#define INIT_PLUGIN_INSTANCE(PLUGIN) \
    do { \
        Static##PLUGIN##PluginInstance instance; \
        Q_UNUSED(instance); \
    } while (0)

DECLARE_PLUGIN_INSTANCE(SignalSlotEditorPlugin)
DECLARE_PLUGIN_INSTANCE(BuddyEditorPlugin)
DECLARE_PLUGIN_INSTANCE(TabOrderEditorPlugin)

static void initResources()
{
    // Q_INIT_RESOURCE only usable in functions in global namespace
    Q_INIT_RESOURCE(formeditor);
    Q_INIT_RESOURCE(widgetbox);
}


static void initInstances()
{
    static bool plugins_initialized = false;

    if (!plugins_initialized) {
        INIT_PLUGIN_INSTANCE(SignalSlotEditorPlugin);
        INIT_PLUGIN_INSTANCE(BuddyEditorPlugin);
        INIT_PLUGIN_INSTANCE(TabOrderEditorPlugin);
        plugins_initialized = true;
    }
}

QT_BEGIN_NAMESPACE

/*!
    \class QDesignerComponents
    \brief The QDesignerComponents class provides a central resource for the various components
    used in the \QD user interface.
    \inmodule QtDesigner
    \internal

    The QDesignerComponents class is a factory for each of the standard components present
    in the \QD user interface. It is mostly useful for developers who want to implement
    a standalone form editing environment using \QD's components, or who need to integrate
    \QD's components into an existing integrated development environment (IDE).

    \sa QDesignerFormEditorInterface, QDesignerObjectInspectorInterface,
        QDesignerPropertyEditorInterface, QDesignerWidgetBoxInterface
*/

/*!
    Initializes the resources used by the components.*/
void QDesignerComponents::initializeResources()
{
    initResources();
}

/*!
    Initializes the plugins used by the components.*/
void QDesignerComponents::initializePlugins(QDesignerFormEditorInterface *core)
{
    qdesigner_internal::QDesignerIntegration::initializePlugins(core);
}

/*!
    Constructs a form editor interface with the given \a parent.*/
QDesignerFormEditorInterface *QDesignerComponents::createFormEditor(QObject *parent)
{
    initInstances();
    return new qdesigner_internal::FormEditor(parent);
}

/*!
    Returns a new task menu with the given \a parent for the \a core interface.*/
QObject *QDesignerComponents::createTaskMenu(QDesignerFormEditorInterface *core, QObject *parent)
{
    return new qdesigner_internal::TaskMenuComponent(core, parent);
}

static inline int qtMajorVersion(int qtVersion) { return qtVersion >> 16; }
static inline int qtMinorVersion(int qtVersion) { return (qtVersion >> 8) & 0xFF; }
static inline void setMinorVersion(int minorVersion, int *qtVersion)
{
    *qtVersion &= ~0xFF00;
    *qtVersion |= minorVersion << 8;
}

// Build the version-dependent name of the user widget box file, '$HOME.designer/widgetbox4.4.xml'
static inline QString widgetBoxFileName(int qtVersion, const QDesignerLanguageExtension *lang = 0)
{
    QString rc; {
        const QChar dot = QLatin1Char('.');
        QTextStream str(&rc);
        str << QDir::homePath() << QDir::separator() << QLatin1String(".designer") << QDir::separator()
            << QLatin1String("widgetbox");
        // The naming convention using the version was introduced with 4.4
        const int major = qtMajorVersion(qtVersion);
        const int minor = qtMinorVersion(qtVersion);
        if (major >= 4 &&  minor >= 4)
            str << major << dot << minor;
        if (lang)
            str << dot << lang->uiExtension();
        str << QLatin1String(".xml");
    }
    return rc;
}

/*!
    Returns a new widget box interface with the given \a parent for the \a core interface.*/
QDesignerWidgetBoxInterface *QDesignerComponents::createWidgetBox(QDesignerFormEditorInterface *core, QWidget *parent)
{
    qdesigner_internal::WidgetBox *widgetBox = new qdesigner_internal::WidgetBox(core, parent);

    const QDesignerLanguageExtension *lang = qt_extension<QDesignerLanguageExtension*>(core->extensionManager(), core);

    do {
        if (lang) {
            const QString languageWidgetBox = lang->widgetBoxContents();
            if (!languageWidgetBox.isEmpty()) {
                widgetBox->loadContents(lang->widgetBoxContents());
                break;
            }
        }

        widgetBox->setFileName(QLatin1String(":/trolltech/widgetbox/widgetbox.xml"));
        widgetBox->load();
    } while (false);

    const QString userWidgetBoxFile = widgetBoxFileName(QT_VERSION, lang);

    widgetBox->setFileName(userWidgetBoxFile);
    if (!QFileInfo(userWidgetBoxFile).exists()) {
        // check previous version, that is, are we running the new version for the first time
        // If so, try to copy the old widget box file
        if (const int minv = qtMinorVersion(QT_VERSION)) {
            int oldVersion = QT_VERSION;
            setMinorVersion(minv - 1, &oldVersion);
            const QString oldWidgetBoxFile = widgetBoxFileName(oldVersion, lang);
            if (QFileInfo(oldWidgetBoxFile).exists())
                QFile::copy(oldWidgetBoxFile, userWidgetBoxFile);
        }
    }
    widgetBox->load();

    return widgetBox;
}

/*!
    Returns a new property editor interface with the given \a parent for the \a core interface.*/
QDesignerPropertyEditorInterface *QDesignerComponents::createPropertyEditor(QDesignerFormEditorInterface *core, QWidget *parent)
{
    return new qdesigner_internal::PropertyEditor(core, parent);
}

/*!
    Returns a new object inspector interface with the given \a parent for the \a core interface.*/
QDesignerObjectInspectorInterface *QDesignerComponents::createObjectInspector(QDesignerFormEditorInterface *core, QWidget *parent)
{
    return new qdesigner_internal::ObjectInspector(core, parent);
}

/*!
    Returns a new action editor interface with the given \a parent for the \a core interface.*/
QDesignerActionEditorInterface *QDesignerComponents::createActionEditor(QDesignerFormEditorInterface *core, QWidget *parent)
{
    return new qdesigner_internal::ActionEditor(core, parent);
}

/*!
    Returns a new resource editor with the given \a parent for the \a core interface.*/
QWidget *QDesignerComponents::createResourceEditor(QDesignerFormEditorInterface *core, QWidget *parent)
{
    if (QDesignerLanguageExtension *lang = qt_extension<QDesignerLanguageExtension*>(core->extensionManager(), core)) {
        QWidget *w = lang->createResourceBrowser(parent);
        if (w)
            return w;
    }
    QtResourceView *resourceView = new QtResourceView(core, parent);
    resourceView->setResourceModel(core->resourceModel());
    return resourceView;
}

/*!
    Returns a new signal-slot editor with the given \a parent for the \a core interface.*/
QWidget *QDesignerComponents::createSignalSlotEditor(QDesignerFormEditorInterface *core, QWidget *parent)
{
    return new qdesigner_internal::SignalSlotEditorWindow(core, parent);
}

QT_END_NAMESPACE

