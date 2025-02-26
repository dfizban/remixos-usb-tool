/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#include <private/qabstractspinbox_p.h>
#include <qspinbox.h>

#ifndef QT_NO_SPINBOX

#include <qlineedit.h>
#include <qlocale.h>
#include <qvalidator.h>
#include <qdebug.h>

#include <math.h>

QT_BEGIN_NAMESPACE

//#define QSPINBOX_QSBDEBUG
#ifdef QSPINBOX_QSBDEBUG
#  define QSBDEBUG qDebug
#else
#  define QSBDEBUG if (false) qDebug
#endif

static bool isIntermediateValueHelper(qint64 num, qint64 minimum, qint64 maximum, qint64 *match = 0);

class QSpinBoxPrivate : public QAbstractSpinBoxPrivate
{
    Q_DECLARE_PUBLIC(QSpinBox)
public:
    QSpinBoxPrivate(QWidget *parent = 0);
    void emitSignals(EmitPolicy ep, const QVariant &);

    virtual QVariant valueFromText(const QString &n) const;
    virtual QString textFromValue(const QVariant &n) const;
    QVariant validateAndInterpret(QString &input, int &pos,
                                  QValidator::State &state) const;
    bool isIntermediateValue(const QString &str) const;
    QChar thousand;

    inline void init() {
        setLayoutItemMargins(QStyle::SE_SpinBoxLayoutItem);
    }
};

class QDoubleSpinBoxPrivate : public QAbstractSpinBoxPrivate
{
    Q_DECLARE_PUBLIC(QDoubleSpinBox)
public:
    QDoubleSpinBoxPrivate(QWidget *parent = 0);
    void emitSignals(EmitPolicy ep, const QVariant &);
    bool isIntermediateValue(const QString &str) const;

    virtual QVariant valueFromText(const QString &n) const;
    virtual QString textFromValue(const QVariant &n) const;
    QVariant validateAndInterpret(QString &input, int &pos,
                                  QValidator::State &state) const;
    double round(double input) const;
    // variables
    int decimals;
    QChar delimiter, thousand;
};


/*!
    \class QSpinBox
    \brief The QSpinBox class provides a spin box widget.

    \ingroup basicwidgets
    \mainclass

    QSpinBox is designed to handle integers and discrete sets of
    values (e.g., month names); use QDoubleSpinBox for floating point
    values.

    QSpinBox allows the user to choose a value by clicking the up/down
    buttons or pressing up/down on the keyboard to increase/decrease
    the value currently displayed. The user can also type the value in
    manually. The spin box supports integer values but can be extended to
    use different strings with validate(), textFromValue() and valueFromText().

    Every time the value changes QSpinBox emits the valueChanged()
    signals. The current value can be fetched with value() and set
    with setValue().

    Clicking the up/down buttons or using the keyboard accelerator's
    up and down arrows will increase or decrease the current value in
    steps of size singleStep(). If you want to change this behaviour you
    can reimplement the virtual function stepBy(). The minimum and
    maximum value and the step size can be set using one of the
    constructors, and can be changed later with setMinimum(),
    setMaximum() and setSingleStep().

    Most spin boxes are directional, but QSpinBox can also operate as
    a circular spin box, i.e. if the range is 0-99 and the current
    value is 99, clicking "up" will give 0 if wrapping() is set to
    true. Use setWrapping() if you want circular behavior.

    The displayed value can be prepended and appended with arbitrary
    strings indicating, for example, currency or the unit of
    measurement. See setPrefix() and setSuffix(). The text in the spin
    box is retrieved with text() (which includes any prefix() and
    suffix()), or with cleanText() (which has no prefix(), no suffix()
    and no leading or trailing whitespace).

    It is often desirable to give the user a special (often default)
    choice in addition to the range of numeric values. See
    setSpecialValueText() for how to do this with QSpinBox.

    \table 100%
    \row \o \inlineimage windowsxp-spinbox.png Screenshot of a Windows XP spin box
         \o A spin box shown in the \l{Windows XP Style Widget Gallery}{Windows XP widget style}.
    \row \o \inlineimage plastique-spinbox.png Screenshot of a Plastique spin box
         \o A spin box shown in the \l{Plastique Style Widget Gallery}{Plastique widget style}.
    \row \o \inlineimage macintosh-spinbox.png Screenshot of a Macintosh spin box
         \o A spin box shown in the \l{Macintosh Style Widget Gallery}{Macintosh widget style}.
    \endtable

    \section1 Subclassing QSpinBox

    If using prefix(), suffix(), and specialValueText() don't provide
    enough control, you subclass QSpinBox and reimplement
    valueFromText() and textFromValue(). For example, here's the code
    for a custom spin box that allows the user to enter icon sizes
    (e.g., "32 x 32"):

    \snippet examples/widgets/icons/iconsizespinbox.cpp 1
    \codeline
    \snippet examples/widgets/icons/iconsizespinbox.cpp 2

    See the \l{widgets/icons}{Icons} example for the full source
    code.

    \sa QDoubleSpinBox, QDateTimeEdit, QSlider, {Spin Boxes Example}
*/

/*!
    \fn void QSpinBox::valueChanged(int i)

    This signal is emitted whenever the spin box's value is changed.
    The new value's integer value is passed in \a i.
*/

/*!
    \fn void QSpinBox::valueChanged(const QString &text)

    \overload

    The new value is passed literally in \a text with no prefix() or
    suffix().
*/

/*!
    Constructs a spin box with 0 as minimum value and 99 as maximum value, a
    step value of 1. The value is initially set to 0. It is parented to \a
    parent.

    \sa setMinimum(), setMaximum(), setSingleStep()
*/

QSpinBox::QSpinBox(QWidget *parent)
    : QAbstractSpinBox(*new QSpinBoxPrivate(parent), parent)
{
    Q_D(QSpinBox);
    d->init();
}

#ifdef QT3_SUPPORT
/*!
    Use one of the constructors that doesn't take the \a name
    argument and then use setObjectName() instead.
*/
QSpinBox::QSpinBox(QWidget *parent, const char *name)
    : QAbstractSpinBox(*new QSpinBoxPrivate(parent), parent)
{
    Q_D(QSpinBox);
    setObjectName(QString::fromAscii(name));
    d->init();
}

/*!
    Use one of the constructors that doesn't take the \a name
    argument and then use setObjectName() instead.
*/
QSpinBox::QSpinBox(int minimum, int maximum, int step, QWidget *parent, const char *name)
    : QAbstractSpinBox(*new QSpinBoxPrivate(parent), parent)
{
    Q_D(QSpinBox);
    d->minimum = QVariant(qMin<int>(minimum, maximum));
    d->maximum = QVariant(qMax<int>(minimum, maximum));
    d->singleStep = QVariant(step);
    setObjectName(QString::fromAscii(name));
    d->init();
}

#endif

/*!
    \property QSpinBox::value
    \brief the value of the spin box

    setValue() will emit valueChanged() if the new value is different
    from the old one.
*/

int QSpinBox::value() const
{
    Q_D(const QSpinBox);
    return d->value.toInt();
}

void QSpinBox::setValue(int value)
{
    Q_D(QSpinBox);
    d->setValue(QVariant(value), EmitIfChanged);
}

/*!
    \property QSpinBox::prefix
    \brief the spin box's prefix

    The prefix is prepended to the start of the displayed value.
    Typical use is to display a unit of measurement or a currency
    symbol. For example:

    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 0

    To turn off the prefix display, set this property to an empty
    string. The default is no prefix. The prefix is not displayed when
    value() == minimum() and specialValueText() is set.

    If no prefix is set, prefix() returns an empty string.

    \sa suffix(), setSuffix(), specialValueText(), setSpecialValueText()
*/

QString QSpinBox::prefix() const
{
    Q_D(const QSpinBox);
    return d->prefix;
}

void QSpinBox::setPrefix(const QString &prefix)
{
    Q_D(QSpinBox);

    d->prefix = prefix;
    d->updateEdit();
}

/*!
    \property QSpinBox::suffix
    \brief the suffix of the spin box

    The suffix is appended to the end of the displayed value. Typical
    use is to display a unit of measurement or a currency symbol. For
    example:

    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 1

    To turn off the suffix display, set this property to an empty
    string. The default is no suffix. The suffix is not displayed for
    the minimum() if specialValueText() is set.

    If no suffix is set, suffix() returns an empty string.

    \sa prefix(), setPrefix(), specialValueText(), setSpecialValueText()
*/

QString QSpinBox::suffix() const
{
    Q_D(const QSpinBox);

    return d->suffix;
}

void QSpinBox::setSuffix(const QString &suffix)
{
    Q_D(QSpinBox);

    d->suffix = suffix;
    d->updateEdit();
}

/*!
    \property QSpinBox::cleanText

    \brief the text of the spin box excluding any prefix, suffix,
    or leading or trailing whitespace.

    \sa text, QSpinBox::prefix, QSpinBox::suffix
*/

QString QSpinBox::cleanText() const
{
    Q_D(const QSpinBox);

    return d->stripped(d->edit->displayText());
}


/*!
    \property QSpinBox::singleStep
    \brief the step value

    When the user uses the arrows to change the spin box's value the
    value will be incremented/decremented by the amount of the
    singleStep. The default value is 1. Setting a singleStep value of
    less than 0 does nothing.
*/

int QSpinBox::singleStep() const
{
    Q_D(const QSpinBox);

    return d->singleStep.toInt();
}

void QSpinBox::setSingleStep(int value)
{
    Q_D(QSpinBox);
    if (value >= 0) {
        d->singleStep = QVariant(value);
        d->updateEdit();
    }
}

/*!
    \property QSpinBox::minimum

    \brief the minimum value of the spin box

    When setting this property the \l maximum is adjusted
    if necessary to ensure that the range remains valid.

    The default minimum value is 0.

    \sa setRange()  specialValueText
*/

int QSpinBox::minimum() const
{
    Q_D(const QSpinBox);

    return d->minimum.toInt();
}

void QSpinBox::setMinimum(int minimum)
{
    Q_D(QSpinBox);
    const QVariant m(minimum);
    d->setRange(m, (d->variantCompare(d->maximum, m) > 0 ? d->maximum : m));
}

/*!
    \property QSpinBox::maximum

    \brief the maximum value of the spin box

    When setting this property the \l minimum is adjusted
    if necessary, to ensure that the range remains valid.

    The default maximum value is 99.

    \sa setRange() specialValueText

*/

int QSpinBox::maximum() const
{
    Q_D(const QSpinBox);

    return d->maximum.toInt();
}

void QSpinBox::setMaximum(int maximum)
{
    Q_D(QSpinBox);
    const QVariant m(maximum);
    d->setRange((d->variantCompare(d->minimum, m) < 0 ? d->minimum : m), m);
}

/*!
    Convenience function to set the \a minimum, and \a maximum values
    with a single function call.

    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 2
    is equivalent to:
    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 3

    \sa minimum maximum
*/

void QSpinBox::setRange(int minimum, int maximum)
{
    Q_D(QSpinBox);
    d->setRange(QVariant(minimum), QVariant(maximum));
}

/*!
    This virtual function is used by the spin box whenever it needs
    to display the given \a value. The default implementation returns
    a string containing \a value printed in the standard way using
    QWidget::locale().toString(). Reimplementations may return anything. (See
    the example in the detailed description.)

    Note: QSpinBox does not call this function for specialValueText()
    and that neither prefix() nor suffix() should be included in the
    return value.

    If you reimplement this, you may also need to reimplement
    valueFromText() and validate()

    \sa valueFromText(), validate()
*/

QString QSpinBox::textFromValue(int value) const
{
    Q_D(const QSpinBox);
    QString str = locale().toString(value);
    if (qAbs(value) >= 1000) {
        str.remove(d->thousand);
    }

    return str;
}

/*!
    \fn int QSpinBox::valueFromText(const QString &text) const

    This virtual function is used by the spin box whenever it needs to
    interpret \a text entered by the user as a value.

    Subclasses that need to display spin box values in a non-numeric
    way need to reimplement this function.

    Note: QSpinBox handles specialValueText() separately; this
    function is only concerned with the other values.

    \sa textFromValue(), validate()
*/

int QSpinBox::valueFromText(const QString &text) const
{
    Q_D(const QSpinBox);

    QString copy = text;
    int pos = d->edit->cursorPosition();
    QValidator::State state = QValidator::Acceptable;
    return d->validateAndInterpret(copy, pos, state).toInt();
}

/*!
  \reimp
*/
QValidator::State QSpinBox::validate(QString &text, int &pos) const
{
    Q_D(const QSpinBox);

    QValidator::State state;
    d->validateAndInterpret(text, pos, state);
    return state;
}


/*!
  \reimp
*/
void QSpinBox::fixup(QString &input) const
{
    Q_D(const QSpinBox);

    input.remove(d->thousand);
}


// --- QDoubleSpinBox ---

/*!
    \class QDoubleSpinBox
    \brief The QDoubleSpinBox class provides a spin box widget that
    takes doubles.

    \ingroup basicwidgets
    \mainclass

    QDoubleSpinBox allows the user to choose a value by clicking the
    up and down buttons or by pressing Up or Down on the keyboard to
    increase or decrease the value currently displayed. The user can
    also type the value in manually. The spin box supports double
    values but can be extended to use different strings with
    validate(), textFromValue() and valueFromText().

    Every time the value changes QDoubleSpinBox emits the
    valueChanged() signal. The current value can be fetched with
    value() and set with setValue().

    Note: QDoubleSpinBox will round numbers so they can be displayed
    with the current precision. In a QDoubleSpinBox with decimals set
    to 2, calling setValue(2.555) will cause value() to return 2.56.

    Clicking the up and down buttons or using the keyboard accelerator's
    Up and Down arrows will increase or decrease the current value in
    steps of size singleStep(). If you want to change this behavior you
    can reimplement the virtual function stepBy(). The minimum and
    maximum value and the step size can be set using one of the
    constructors, and can be changed later with setMinimum(),
    setMaximum() and setSingleStep(). The spinbox has a default
    precision of 2 decimal places but this can be changed using
    setDecimals().

    Most spin boxes are directional, but QDoubleSpinBox can also
    operate as a circular spin box, i.e. if the range is 0.0-99.9 and
    the current value is 99.9, clicking "up" will give 0 if wrapping()
    is set to true. Use setWrapping() if you want circular behavior.

    The displayed value can be prepended and appended with arbitrary
    strings indicating, for example, currency or the unit of
    measurement. See setPrefix() and setSuffix(). The text in the spin
    box is retrieved with text() (which includes any prefix() and
    suffix()), or with cleanText() (which has no prefix(), no suffix()
    and no leading or trailing whitespace).

    It is often desirable to give the user a special (often default)
    choice in addition to the range of numeric values. See
    setSpecialValueText() for how to do this with QDoubleSpinBox.

    \sa QSpinBox, QDateTimeEdit, QSlider, {Spin Boxes Example}
*/

/*!
    \fn void QDoubleSpinBox::valueChanged(double d);

    This signal is emitted whenever the spin box's value is changed.
    The new value is passed in \a d.
*/

/*!
    \fn void QDoubleSpinBox::valueChanged(const QString &text);

    \overload

    The new value is passed literally in \a text with no prefix() or
    suffix().
*/

/*!
    Constructs a spin box with 0.0 as minimum value and 99.99 as maximum value,
    a step value of 1.0 and a precision of 2 decimal places. The value is
    initially set to 0.00. The spin box has the given \a parent.

    \sa setMinimum(), setMaximum(), setSingleStep()
*/
QDoubleSpinBox::QDoubleSpinBox(QWidget *parent)
    : QAbstractSpinBox(*new QDoubleSpinBoxPrivate(parent), parent)
{
}

/*!
    \property QDoubleSpinBox::value
    \brief the value of the spin box

    setValue() will emit valueChanged() if the new value is different
    from the old one.

    Note: The value will be rounded so it can be displayed with the
    current setting of decimals.

    \sa decimals
*/
double QDoubleSpinBox::value() const
{
    Q_D(const QDoubleSpinBox);

    return d->value.toDouble();
}

void QDoubleSpinBox::setValue(double value)
{
    Q_D(QDoubleSpinBox);
    QVariant v(d->round(value));
    d->setValue(v, EmitIfChanged);
}
/*!
    \property QDoubleSpinBox::prefix
    \brief the spin box's prefix

    The prefix is prepended to the start of the displayed value.
    Typical use is to display a unit of measurement or a currency
    symbol. For example:

    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 4

    To turn off the prefix display, set this property to an empty
    string. The default is no prefix. The prefix is not displayed when
    value() == minimum() and specialValueText() is set.

    If no prefix is set, prefix() returns an empty string.

    \sa suffix(), setSuffix(), specialValueText(), setSpecialValueText()
*/

QString QDoubleSpinBox::prefix() const
{
    Q_D(const QDoubleSpinBox);

    return d->prefix;
}

void QDoubleSpinBox::setPrefix(const QString &prefix)
{
    Q_D(QDoubleSpinBox);

    d->prefix = prefix;
    d->updateEdit();
}

/*!
    \property QDoubleSpinBox::suffix
    \brief the suffix of the spin box

    The suffix is appended to the end of the displayed value. Typical
    use is to display a unit of measurement or a currency symbol. For
    example:

    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 5

    To turn off the suffix display, set this property to an empty
    string. The default is no suffix. The suffix is not displayed for
    the minimum() if specialValueText() is set.

    If no suffix is set, suffix() returns an empty string.

    \sa prefix(), setPrefix(), specialValueText(), setSpecialValueText()
*/

QString QDoubleSpinBox::suffix() const
{
    Q_D(const QDoubleSpinBox);

    return d->suffix;
}

void QDoubleSpinBox::setSuffix(const QString &suffix)
{
    Q_D(QDoubleSpinBox);

    d->suffix = suffix;
    d->updateEdit();
}

/*!
    \property QDoubleSpinBox::cleanText

    \brief the text of the spin box excluding any prefix, suffix,
    or leading or trailing whitespace.

    \sa text, QDoubleSpinBox::prefix, QDoubleSpinBox::suffix
*/

QString QDoubleSpinBox::cleanText() const
{
    Q_D(const QDoubleSpinBox);

    return d->stripped(d->edit->displayText());
}

/*!
    \property QDoubleSpinBox::singleStep
    \brief the step value

    When the user uses the arrows to change the spin box's value the
    value will be incremented/decremented by the amount of the
    singleStep. The default value is 1.0. Setting a singleStep value
    of less than 0 does nothing.
*/
double QDoubleSpinBox::singleStep() const
{
    Q_D(const QDoubleSpinBox);

    return d->singleStep.toDouble();
}

void QDoubleSpinBox::setSingleStep(double value)
{
    Q_D(QDoubleSpinBox);

    if (value >= 0) {
        d->singleStep = value;
        d->updateEdit();
    }
}

/*!
    \property QDoubleSpinBox::minimum

    \brief the minimum value of the spin box

    When setting this property the \l maximum is adjusted
    if necessary to ensure that the range remains valid.

    The default minimum value is 0.0.

    Note: The minimum value will be rounded to match the decimals
    property.

    \sa decimals, setRange() specialValueText
*/

double QDoubleSpinBox::minimum() const
{
    Q_D(const QDoubleSpinBox);

    return d->minimum.toDouble();
}

void QDoubleSpinBox::setMinimum(double minimum)
{
    Q_D(QDoubleSpinBox);
    const QVariant m(d->round(minimum));
    d->setRange(m, (d->variantCompare(d->maximum, m) > 0 ? d->maximum : m));
}

/*!
    \property QDoubleSpinBox::maximum

    \brief the maximum value of the spin box

    When setting this property the \l minimum is adjusted
    if necessary, to ensure that the range remains valid.

    The default maximum value is 99.99.

    Note: The maximum value will be rounded to match the decimals
    property.

    \sa decimals, setRange()
*/

double QDoubleSpinBox::maximum() const
{
    Q_D(const QDoubleSpinBox);

    return d->maximum.toDouble();
}

void QDoubleSpinBox::setMaximum(double maximum)
{
    Q_D(QDoubleSpinBox);
    const QVariant m(d->round(maximum));
    d->setRange((d->variantCompare(d->minimum, m) < 0 ? d->minimum : m), m);
}

/*!
    Convenience function to set the \a minimum and \a maximum values
    with a single function call.

    Note: The maximum and minimum values will be rounded to match the
    decimals property.

    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 6
    is equivalent to:
    \snippet doc/src/snippets/code/src.gui.widgets.qspinbox.cpp 7

    \sa minimum maximum
*/

void QDoubleSpinBox::setRange(double minimum, double maximum)
{
    Q_D(QDoubleSpinBox);
    d->setRange(QVariant(d->round(minimum)), QVariant(d->round(maximum)));
}

/*!
     \property QDoubleSpinBox::decimals

     \brief the precision of the spin box, in decimals

     Sets how many decimals the spinbox will use for displaying and
     interpreting doubles.

     \warning The results might not be reliable with very high values
     for \a decimals.

     Note: The maximum, minimum and value might change as a result of
     changing this property.
*/

int QDoubleSpinBox::decimals() const
{
    Q_D(const QDoubleSpinBox);

    return d->decimals;
}

void QDoubleSpinBox::setDecimals(int decimals)
{
    Q_D(QDoubleSpinBox);
    d->decimals = qMax(0, decimals);

    setRange(minimum(), maximum()); // make sure values are rounded
    setValue(value());
}

/*!
    This virtual function is used by the spin box whenever it needs to
    display the given \a value. The default implementation returns a string
    containing \a value printed using QWidget::locale().toString(\a value,
    QLatin1Char('f'), decimals()) and will remove the thousand
    separator. Reimplementations may return anything.

    Note: QDoubleSpinBox does not call this function for
    specialValueText() and that neither prefix() nor suffix() should
    be included in the return value.

    If you reimplement this, you may also need to reimplement
    valueFromText().

    \sa valueFromText()
*/


QString QDoubleSpinBox::textFromValue(double value) const
{
    Q_D(const QDoubleSpinBox);
    QString str = locale().toString(value, 'f', d->decimals);
    if (qAbs(value) >= 1000.0) {
        str.remove(d->thousand);
    }
    return str;
}

/*!
    This virtual function is used by the spin box whenever it needs to
    interpret \a text entered by the user as a value.

    Subclasses that need to display spin box values in a non-numeric
    way need to reimplement this function.

    Note: QDoubleSpinBox handles specialValueText() separately; this
    function is only concerned with the other values.

    \sa textFromValue(), validate()
*/
double QDoubleSpinBox::valueFromText(const QString &text) const
{
    Q_D(const QDoubleSpinBox);

    QString copy = text;
    int pos = d->edit->cursorPosition();
    QValidator::State state = QValidator::Acceptable;
    return d->validateAndInterpret(copy, pos, state).toDouble();
}

/*!
  \reimp
*/
QValidator::State QDoubleSpinBox::validate(QString &text, int &pos) const
{
    Q_D(const QDoubleSpinBox);

    QValidator::State state;
    d->validateAndInterpret(text, pos, state);
    return state;
}


/*!
  \reimp
*/
void QDoubleSpinBox::fixup(QString &input) const
{
    Q_D(const QDoubleSpinBox);

    input.remove(d->thousand);
}

// --- QSpinBoxPrivate ---

/*!
    \internal
    Constructs a QSpinBoxPrivate object
*/

QSpinBoxPrivate::QSpinBoxPrivate(QWidget *parent)
{
    minimum = QVariant((int)0);
    maximum = QVariant((int)99);
    value = minimum;
    singleStep = QVariant((int)1);
    type = QVariant::Int;
    const QString str = (parent ? parent->locale() : QLocale()).toString(4567);
    if (str.size() == 5) {
        thousand = QChar(str.at(1));
    }

}

/*!
    \internal
    \reimp
*/

void QSpinBoxPrivate::emitSignals(EmitPolicy ep, const QVariant &old)
{
    Q_Q(QSpinBox);
    if (ep != NeverEmit) {
        pendingEmit = false;
        if (ep == AlwaysEmit || value != old) {
            emit q->valueChanged(edit->displayText());
            emit q->valueChanged(value.toInt());
        }
    }
}

/*!
    \internal
    \reimp
*/

QString QSpinBoxPrivate::textFromValue(const QVariant &value) const
{
    Q_Q(const QSpinBox);
    return q->textFromValue(value.toInt());
}
/*!
    \internal
    \reimp
*/

QVariant QSpinBoxPrivate::valueFromText(const QString &text) const
{
    Q_Q(const QSpinBox);

    return QVariant(q->valueFromText(text));
}


/*!
  \internal

  Return true if str can become a number which is between minimum and
  maximum or false if this is not possible.
*/

bool QSpinBoxPrivate::isIntermediateValue(const QString &str) const
{
    const int num = q_func()->locale().toInt(str, 0, 10);
    const int min = minimum.toInt();
    const int max = maximum.toInt();

    int numDigits = 0;
    int digits[10];
    int tmp = num;
    if (tmp == 0) {
        numDigits = 1;
        digits[0] = 0;
    } else {
        tmp = num;
        for (int i=0; tmp != 0; ++i) {
            digits[numDigits++] = qAbs(tmp % 10);
            tmp /= 10;
        }
    }

    int failures = 0;
    for (int number=min; /*number<=max*/; ++number) {
        tmp = number;
        for (int i=0; tmp != 0;) {
            if (digits[i] == qAbs(tmp % 10)) {
                if (++i == numDigits)
                    return true;
            }
            tmp /= 10;
        }
        if (failures++ == 500000) //upper bound
            return true;
        if (number == max) // needed for INT_MAX
            break;
    }
    return false;
}

/*!
    \internal Multi purpose function that parses input, sets state to
    the appropriate state and returns the value it will be interpreted
    as.
*/

QVariant QSpinBoxPrivate::validateAndInterpret(QString &input, int &pos,
                                               QValidator::State &state) const
{
    if (cachedText == input && !input.isEmpty()) {
        state = cachedState;
        QSBDEBUG() << "cachedText was" << "'" << cachedText << "'" << "state was "
                   << state << " and value was " << cachedValue;

        return cachedValue;
    }
    const int max = maximum.toInt();
    const int min = minimum.toInt();

    QString copy = stripped(input, &pos);
    QSBDEBUG() << "input" << input << "copy" << copy;
    state = QValidator::Acceptable;
    int num = min;

    if (max != min && (copy.isEmpty()
                       || (min < 0 && copy == QLatin1String("-"))
                       || (min >= 0 && copy == QLatin1String("+")))) {
        state = QValidator::Intermediate;
        QSBDEBUG() << __FILE__ << __LINE__<< "num is set to" << num;
    } else if (copy.startsWith(QLatin1String("-")) && min >= 0) {
        state = QValidator::Invalid; // special-case -0 will be interpreted as 0 and thus not be invalid with a range from 0-100
    } else {
        bool ok = false;
        bool removedThousand = false;
        num = q_func()->locale().toInt(copy, &ok, 10);
        if (!ok && copy.contains(thousand) && (max >= 1000 || min <= -1000)) {
            const int s = copy.size();
            copy.remove(thousand);
            pos = qMax(0, pos - (s - copy.size()));
            removedThousand = true;
            num = q_func()->locale().toInt(copy, &ok, 10);
        }
        QSBDEBUG() << __FILE__ << __LINE__<< "num is set to" << num;
        if (!ok) {
            state = QValidator::Invalid;
        } else if (num >= min && num <= max) {
            state = removedThousand ? QValidator::Intermediate : QValidator::Acceptable;
        } else if (max == min) {
            state = QValidator::Invalid;
        } else {
            if ((num >= 0 && num > max) || (num < 0 && num < min)) {
                state = QValidator::Invalid;
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
            } else {
                state = isIntermediateValue(copy) ? QValidator::Intermediate : QValidator::Invalid;
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to "
                           << (state == QValidator::Intermediate ? "Intermediate" : "Acceptable");
            }
        }
    }
    if (state != QValidator::Acceptable)
        num = max > 0 ? min : max;
    input = prefix + copy + suffix;
    cachedText = input;
    cachedState = state;
    cachedValue = QVariant((int)num);

    QSBDEBUG() << "cachedText is set to '" << cachedText << "' state is set to "
               << state << " and value is set to " << cachedValue;
    return cachedValue;
}

// --- QDoubleSpinBoxPrivate ---

/*!
    \internal
    Constructs a QSpinBoxPrivate object
*/

QDoubleSpinBoxPrivate::QDoubleSpinBoxPrivate(QWidget *parent)
{
    minimum = QVariant(0.0);
    maximum = QVariant(99.99);
    value = minimum;
    singleStep = QVariant(1.0);
    decimals = 2;
    type = QVariant::Double;
    const QString str = (parent ? parent->locale() : QLocale()).toString(4567.1);
    if (str.size() == 6) {
        delimiter = str.at(4);
        thousand = QChar((ushort)0);
    } else if (str.size() == 7) {
        thousand = str.at(1);
        delimiter = str.at(5);
    }
    Q_ASSERT(!delimiter.isNull());
}

/*!
    \internal
    \reimp
*/

void QDoubleSpinBoxPrivate::emitSignals(EmitPolicy ep, const QVariant &old)
{
    Q_Q(QDoubleSpinBox);
    if (ep != NeverEmit) {
        pendingEmit = false;
        if (ep == AlwaysEmit || value != old) {
            emit q->valueChanged(edit->displayText());
            emit q->valueChanged(value.toDouble());
        }
    }
}


bool QDoubleSpinBoxPrivate::isIntermediateValue(const QString &str) const
{
    QSBDEBUG() << "input is" << str << minimum << maximum;
    qint64 dec = 1;
    for (int i=0; i<decimals; ++i)
        dec *= 10;

    const QLatin1Char dot('.');

    // I know QString::number() uses CLocale so I use dot
    const QString minstr = QString::number(minimum.toDouble(), 'f', decimals);
    qint64 min_left = minstr.left(minstr.indexOf(dot)).toLongLong();
    qint64 min_right = minstr.mid(minstr.indexOf(dot) + 1).toLongLong();

    const QString maxstr = QString::number(maximum.toDouble(), 'f', decimals);
    qint64 max_left = maxstr.left(maxstr.indexOf(dot)).toLongLong();
    qint64 max_right = maxstr.mid(maxstr.indexOf(dot) + 1).toLongLong();

    const int dotindex = str.indexOf(delimiter);
    const bool negative = maximum.toDouble() < 0;
    qint64 left = 0, right = 0;
    bool doleft = true;
    bool doright = true;
    if (dotindex == -1) {
        left = str.toLongLong();
        doright = false;
    } else if (dotindex == 0 || (dotindex == 1 && str.at(0) == QLatin1Char('+'))) {
        if (negative) {
            QSBDEBUG() << __FILE__ << __LINE__ << "returns false";
            return false;
        }
        doleft = false;
        right = str.mid(dotindex + 1).toLongLong();
    } else if (dotindex == 1 && str.at(0) == QLatin1Char('-')) {
        if (!negative) {
            QSBDEBUG() << __FILE__ << __LINE__ << "returns false";
            return false;
        }
        doleft = false;
        right = str.mid(dotindex + 1).toLongLong();
    } else {
        left = str.left(dotindex).toLongLong();
        if (dotindex == str.size() - 1) {
            doright = false;
        } else {
            right = str.mid(dotindex + 1).toLongLong();
        }
    }
    if ((left >= 0 && max_left < 0 && !str.startsWith(QLatin1Char('-'))) || (left < 0 && min_left >= 0)) {
        QSBDEBUG("returns false 0");
        return false;
    }

    qint64 match = min_left;
    if (doleft && !isIntermediateValueHelper(left, min_left, max_left, &match)) {
        QSBDEBUG() << __FILE__ << __LINE__ << "returns false";
        return false;
    }
    if (doright) {
        QSBDEBUG("match %lld min_left %lld max_left %lld", match, min_left, max_left);
        if (!doleft) {
            if (min_left == max_left) {
                const bool ret = isIntermediateValueHelper(qAbs(left),
                                                           negative ? max_right : min_right,
                                                           negative ? min_right : max_right);
                QSBDEBUG() << __FILE__ << __LINE__ << "returns" << ret;
                return ret;
            } else if (qAbs(max_left - min_left) == 1) {
                const bool ret = isIntermediateValueHelper(qAbs(left), min_right, negative ? 0 : dec)
                                 || isIntermediateValueHelper(qAbs(left), negative ? dec : 0, max_right);
                QSBDEBUG() << __FILE__ << __LINE__ << "returns" << ret;
                return ret;
            } else {
                const bool ret = isIntermediateValueHelper(qAbs(left), 0, dec);
                QSBDEBUG() << __FILE__ << __LINE__ << "returns" << ret;
                return ret;
            }
        }
        if (match != min_left) {
            min_right = negative ? dec : 0;
        }
        if (match != max_left) {
            max_right = negative ? 0 : dec;
        }
        qint64 tmpl = negative ? max_right : min_right;
        qint64 tmpr = negative ? min_right : max_right;
        const bool ret = isIntermediateValueHelper(right, tmpl, tmpr);
        QSBDEBUG() << __FILE__ << __LINE__ << "returns" << ret;
        return ret;
    }
    QSBDEBUG() << __FILE__ << __LINE__ << "returns true";
    return true;
}

/*!
    \internal
    \reimp
*/
QVariant QDoubleSpinBoxPrivate::valueFromText(const QString &f) const
{
    Q_Q(const QDoubleSpinBox);
    return QVariant(q->valueFromText(f));
}

/*!
    \internal
    Rounds to a double value that is restricted to decimals.
    E.g. // decimals = 2

    round(5.555) => 5.56
    */

double QDoubleSpinBoxPrivate::round(double value) const
{
    Q_Q(const QDoubleSpinBox);
    const QString strDbl = q->locale().toString(value, 'f', decimals);
    return q->locale().toDouble(strDbl);
}


/*!
    \internal Multi purpose function that parses input, sets state to
    the appropriate state and returns the value it will be interpreted
    as.
*/

QVariant QDoubleSpinBoxPrivate::validateAndInterpret(QString &input, int &pos,
                                                     QValidator::State &state) const
{
    if (cachedText == input && !input.isEmpty()) {
        state = cachedState;
        QSBDEBUG() << "cachedText was" << "'" << cachedText << "'" << "state was "
                   << state << " and value was " << cachedValue;
        return cachedValue;
    }
    const double max = maximum.toDouble();
    const double min = minimum.toDouble();

    QString copy = stripped(input, &pos);
    QSBDEBUG() << "input" << input << "copy" << copy;
    int len = copy.size();
    double num = min;
    const bool plus = max >= 0;
    const bool minus = min <= 0;

    switch (len) {
    case 0:
        state = max != min ? QValidator::Intermediate : QValidator::Invalid;
        goto end;
    case 1:
        if (copy.at(0) == delimiter
            || (plus && copy.at(0) == QLatin1Char('+'))
            || (minus && copy.at(0) == QLatin1Char('-'))) {
            state = QValidator::Intermediate;
            goto end;
        }
        break;
    case 2:
        if (copy.at(1) == delimiter
            && ((plus && copy.at(0) == QLatin1Char('+')) || (minus && copy.at(0) == QLatin1Char('-')))) {
            state = QValidator::Intermediate;
            goto end;
        }
        break;
    default: break;
    }

    if (copy.at(0) == thousand) {
        QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
        state = QValidator::Invalid;
        goto end;
    } else if (len > 1) {
        const int dec = copy.indexOf(delimiter);
        if (dec != -1) {
            if (dec + 1 < copy.size() && copy.at(dec + 1) == delimiter && pos == dec + 1) {
                copy.remove(dec + 1, 1); // typing a delimiter when you are on the delimiter
            } // should be treated as typing right arrow

            if (copy.size() - dec > decimals + 1) {
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                state = QValidator::Invalid;
                goto end;
            }
            for (int i=dec + 1; i<copy.size(); ++i) {
                if (copy.at(i).isSpace() || copy.at(i) == thousand) {
                    QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                    state = QValidator::Invalid;
                    goto end;
                }
            }
        } else {
            const QChar &last = copy.at(len - 1);
            const QChar &secondLast = copy.at(len - 2);
            if ((last == thousand || last.isSpace())
                && (secondLast == thousand || secondLast.isSpace())) {
                state = QValidator::Invalid;
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                goto end;
            } else if (last.isSpace() && (!thousand.isSpace() || secondLast.isSpace())) {
                state = QValidator::Invalid;
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                goto end;
            }
        }
    }

    {
        bool ok = false;
        QLocale loc(q_func()->locale());
        num = loc.toDouble(copy, &ok);
        QSBDEBUG() << __FILE__ << __LINE__ << loc << copy << num << ok;
        bool notAcceptable = false;

        if (!ok) {
            if (thousand.isPrint()) {
                if (max < 1000 && min > -1000 && copy.contains(thousand)) {
                    state = QValidator::Invalid;
                    QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                    goto end;
                }

                const int len = copy.size();
                for (int i=0; i<len- 1; ++i) {
                    if (copy.at(i) == thousand && copy.at(i + 1) == thousand) {
                        QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                        state = QValidator::Invalid;
                        goto end;
                    }
                }

                const int s = copy.size();
                copy.remove(thousand);
                pos = qMax(0, pos - (s - copy.size()));


                num = loc.toDouble(copy, &ok);
                QSBDEBUG() << thousand << num << copy << ok;

                if (!ok) {
                    state = QValidator::Invalid;
                    QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
                    goto end;
                }
                notAcceptable = true;
            }
        }

        if (!ok) {
            state = QValidator::Invalid;
            QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
        } else if (num >= min && num <= max) {
            state = notAcceptable ? QValidator::Intermediate : QValidator::Acceptable;
            QSBDEBUG() << __FILE__ << __LINE__<< "state is set to "
                       << (state == QValidator::Intermediate ? "Intermediate" : "Acceptable");
        } else if (max == min) { // when max and min is the same the only non-Invalid input is max (or min)
            state = QValidator::Invalid;
            QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
        } else {
            if ((num >= 0 && num > max) || (num < 0 && num < min)) {
                state = QValidator::Invalid;
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to Invalid";
            } else {
                state = isIntermediateValue(copy) ? QValidator::Intermediate : QValidator::Invalid;
                QSBDEBUG() << __FILE__ << __LINE__<< "state is set to "
                           << (state == QValidator::Intermediate ? "Intermediate" : "Acceptable");
            }
        }
    }

end:
    if (state != QValidator::Acceptable) {
        num = max > 0 ? min : max;
    }

    input = prefix + copy + suffix;
    cachedText = input;
    cachedState = state;
    cachedValue = QVariant(num);
    return QVariant(num);
}

/*
    \internal
    \reimp
*/

QString QDoubleSpinBoxPrivate::textFromValue(const QVariant &f) const
{
    Q_Q(const QDoubleSpinBox);
    return q->textFromValue(f.toDouble());
}

/*!
    \fn void QSpinBox::setLineStep(int step)

    Use setSingleStep() instead.
*/

/*!
    \fn void QSpinBox::setMaxValue(int value)

    Use setMaximum() instead.
*/

/*!
    \fn void QSpinBox::setMinValue(int value)

    Use setMinimum() instead.
*/

/*!
    \fn int QSpinBox::maxValue() const

    Use maximum() instead.
*/

/*!
    \fn int QSpinBox::minValue() const

    Use minimum() instead.
*/

/*!
    \internal Returns whether \a str is a string which value cannot be
    parsed but still might turn into something valid.
*/

static bool isIntermediateValueHelper(qint64 num, qint64 min, qint64 max, qint64 *match)
{
    QSBDEBUG("%lld %lld %lld", num, min, max);

    if (num >= min && num <= max) {
        if (match)
            *match = num;
        QSBDEBUG("returns true 0");
        return true;
    }
    qint64 tmp = num;

    int numDigits = 0;
    int digits[10];
    if (tmp == 0) {
        numDigits = 1;
        digits[0] = 0;
    } else {
        tmp = qAbs(num);
        for (int i=0; tmp > 0; ++i) {
            digits[numDigits++] = tmp % 10;
            tmp /= 10;
        }
    }

    int failures = 0;
    qint64 number;
    for (number=max; number>=min; --number) {
        tmp = qAbs(number);
        for (int i=0; tmp > 0;) {
            if (digits[i] == (tmp % 10)) {
                if (++i == numDigits) {
                    if (match)
                        *match = number;
                    QSBDEBUG("returns true 1");
                    return true;
                }
            }
            tmp /= 10;
        }
        if (failures++ == 500000) { //upper bound
            if (match)
                *match = num;
            QSBDEBUG("returns true 2");
            return true;
        }
    }
    QSBDEBUG("returns false");
    return false;
}

/*! \reimp */
bool QSpinBox::event(QEvent *event)
{
    Q_D(QSpinBox);
    if (event->type() == QEvent::StyleChange
#ifdef Q_WS_MAC
            || event->type() == QEvent::MacSizeChange
#endif
            )
        d->setLayoutItemMargins(QStyle::SE_SpinBoxLayoutItem);
    return QAbstractSpinBox::event(event);
}

QT_END_NAMESPACE

#endif // QT_NO_SPINBOX
