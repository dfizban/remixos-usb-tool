/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
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

#ifndef QTGRADIENTWIDGET_H
#define QTGRADIENTWIDGET_H

#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class QtGradientWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool backgroundCheckered READ isBackgroundCheckered WRITE setBackgroundCheckered)
public:
    QtGradientWidget(QWidget *parent = 0);
    ~QtGradientWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    int heightForWidth(int w) const;

    bool isBackgroundCheckered() const;
    void setBackgroundCheckered(bool checkered);

    QGradientStops gradientStops() const;

    void setGradientType(QGradient::Type type);
    QGradient::Type gradientType() const;

    void setGradientSpread(QGradient::Spread spread);
    QGradient::Spread gradientSpread() const;

    void setStartLinear(const QPointF &point);
    QPointF startLinear() const;

    void setEndLinear(const QPointF &point);
    QPointF endLinear() const;

    void setCentralRadial(const QPointF &point);
    QPointF centralRadial() const;

    void setFocalRadial(const QPointF &point);
    QPointF focalRadial() const;

    void setRadiusRadial(qreal radius);
    qreal radiusRadial() const;

    void setCentralConical(const QPointF &point);
    QPointF centralConical() const;

    void setAngleConical(qreal angle);
    qreal angleConical() const;

public slots:
    void setGradientStops(const QGradientStops &stops);
signals:

    void startLinearChanged(const QPointF &point);
    void endLinearChanged(const QPointF &point);
    void centralRadialChanged(const QPointF &point);
    void focalRadialChanged(const QPointF &point);
    void radiusRadialChanged(qreal radius);
    void centralConicalChanged(const QPointF &point);
    void angleConicalChanged(qreal angle);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
    class QtGradientWidgetPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QtGradientWidget)
    Q_DISABLE_COPY(QtGradientWidget)
};

QT_END_NAMESPACE

#endif
