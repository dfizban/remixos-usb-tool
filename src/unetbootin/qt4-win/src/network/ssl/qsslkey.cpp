/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtNetwork module of the Qt Toolkit.
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
** In addition, as a special exception, Trolltech gives permission to
** link the code of its release of Qt with the OpenSSL project's
** "OpenSSL" library (or modified versions of it that use the same
** license as the "OpenSSL" library), and distribute the linked
** executables.  You must comply with the GNU General Public License
** version 2 or the GNU General Public License version 3 in all
** respects for all of the code used other than the "OpenSSL" code.
** If you modify this file, you may extend this exception to your
** version of the file, but you are not obligated to do so.  If you do
** not wish to do so, delete this exception statement from your
** version of this file.
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


/*!
    \class QSslKey
    \brief The QSslKey class provides an interface for private and public keys.
    \since 4.3

    \reentrant
    \ingroup io
    \module network

    QSslKey provides a simple API for managing keys.

    \sa QSslSocket, QSslCertificate, QSslCipher
*/

#include "qsslsocket_openssl_symbols_p.h"
#include "qsslkey.h"
#include "qsslkey_p.h"
#include "qsslsocket.h"
#include "qsslsocket_p.h"

#include <QtCore/qatomic.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qiodevice.h>
#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE
#endif


/*!
    \internal
 */
void QSslKeyPrivate::clear(bool deep)
{
    isNull = true;
    if (!QSslSocket::supportsSsl())
        return;
    if (rsa) {
        if (deep)
            q_RSA_free(rsa);
        rsa = 0;
    }
    if (dsa) {
        if (deep)
            q_DSA_free(dsa);
        dsa = 0;
    }
}

/*!
    \internal

    Allocates a new rsa or dsa struct and decodes \a pem into it
    according to the current algorithm and type.

    If \a deepClear is true, the rsa/dsa struct is freed if it is was
    already allocated, otherwise we "leak" memory (which is exactly
    what we want for copy construction).

    If \a passPhrase is non-empty, it will be used for decrypting
    \a pem.
*/
void QSslKeyPrivate::decodePem(const QByteArray &pem, const QByteArray &passPhrase,
                               bool deepClear)
{
    if (pem.isEmpty())
        return;

    clear(deepClear);

    if (!QSslSocket::supportsSsl())
        return;

    BIO *bio = q_BIO_new_mem_buf(const_cast<char *>(pem.data()), pem.size());
    if (!bio)
        return;

    void *phrase = passPhrase.isEmpty()
        ? (void *)0
        : (void *)passPhrase.constData();

    if (algorithm == QSsl::Rsa) {
        RSA *result = (type == QSsl::PublicKey)
            ? q_PEM_read_bio_RSA_PUBKEY(bio, &rsa, 0, phrase)
            : q_PEM_read_bio_RSAPrivateKey(bio, &rsa, 0, phrase);
        if (rsa && rsa == result)
            isNull = false;
    } else {
        DSA *result = (type == QSsl::PublicKey)
            ? q_PEM_read_bio_DSA_PUBKEY(bio, &dsa, 0, phrase)
            : q_PEM_read_bio_DSAPrivateKey(bio, &dsa, 0, phrase);
        if (dsa && dsa == result)
            isNull = false;
    }

    q_BIO_free(bio);
}

/*!
    Constructs a null key.

    \sa isNull()
*/
QSslKey::QSslKey()
    : d(new QSslKeyPrivate)
{
}

/*!
    \internal
*/
QByteArray QSslKeyPrivate::pemHeader() const
{
    // ### use QByteArray::fromRawData() instead
    if (type == QSsl::PublicKey)
        return QByteArray("-----BEGIN PUBLIC KEY-----\n");
    else if (algorithm == QSsl::Rsa)
        return QByteArray("-----BEGIN RSA PRIVATE KEY-----\n");
    return QByteArray("-----BEGIN DSA PRIVATE KEY-----\n");
}

/*!
    \internal
*/
QByteArray QSslKeyPrivate::pemFooter() const
{
    // ### use QByteArray::fromRawData() instead
    if (type == QSsl::PublicKey)
        return QByteArray("-----END PUBLIC KEY-----\n");
    else if (algorithm == QSsl::Rsa)
        return QByteArray("-----END RSA PRIVATE KEY-----\n");
    return QByteArray("-----END DSA PRIVATE KEY-----\n");
}

/*!
    \internal

    Returns a DER key formatted as PEM.
*/
QByteArray QSslKeyPrivate::pemFromDer(const QByteArray &der) const
{
    QByteArray pem(der.toBase64());

    const int lineWidth = 64; // RFC 1421
    const int newLines = pem.size() / lineWidth;
    const bool rem = pem.size() % lineWidth;

    // ### optimize
    for (int i = 0; i < newLines; ++i)
        pem.insert((i + 1) * lineWidth + i, '\n');
    if (rem)
        pem.append('\n'); // ###

    pem.prepend(pemHeader());
    pem.append(pemFooter());

    return pem;
}

/*!
    \internal

    Returns a PEM key formatted as DER.
*/
QByteArray QSslKeyPrivate::derFromPem(const QByteArray &pem) const
{
    const QByteArray header = pemHeader();
    const QByteArray footer = pemFooter();

    QByteArray der(pem);

    const int headerIndex = der.indexOf(header);
    const int footerIndex = der.indexOf(footer);
    if (headerIndex == -1 || footerIndex == -1)
        return QByteArray();

    der = der.mid(headerIndex + header.size(), footerIndex - (headerIndex + header.size()));

    return QByteArray::fromBase64(der); // ignores newlines
}

/*!
    Constructs a QSslKey by decoding the string in the byte array
    \a encoded using a specified \a algorithm and \a encoding format.
    If the encoded key is encrypted, \a passPhrase is used to decrypt
    it. \a type specifies whether the key is public or private.

    After construction, use isNull() to check if \a encoded contained
    a valid key.
*/
QSslKey::QSslKey(const QByteArray &encoded, QSsl::KeyAlgorithm algorithm,
                 QSsl::EncodingFormat encoding, QSsl::KeyType type, const QByteArray &passPhrase)
    : d(new QSslKeyPrivate)
{
    d->type = type;
    d->algorithm = algorithm;
    d->decodePem((encoding == QSsl::Der)
                 ? d->pemFromDer(encoded) : encoded,
                 passPhrase);
}

/*!
    Constructs a QSslKey by reading and decoding data from a
    \a device using a specified \a algorithm and \a encoding format.
    If the encoded key is encrypted, \a passPhrase is used to decrypt
    it. \a type specifies whether the key is public or private.

    After construction, use isNull() to check if \a device provided
    a valid key.
*/
QSslKey::QSslKey(QIODevice *device, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat encoding,
		 QSsl::KeyType type, const QByteArray &passPhrase)
    : d(new QSslKeyPrivate)
{
    QByteArray encoded;
    if (device)
        encoded = device->readAll();
    d->type = type;
    d->algorithm = algorithm;
    d->decodePem((encoding == QSsl::Der) ?
                 d->pemFromDer(encoded) : encoded,
                 passPhrase);
}

/*!
    Constructs an identical copy of \a other.
*/
QSslKey::QSslKey(const QSslKey &other) : d(other.d)
{
    d->ref.ref();
}

/*!
    Destroys the QSslKey object.
*/
QSslKey::~QSslKey()
{
    if (!d->ref.deref())
        delete d;
}

/*!
    Copies the contents of \a other into this key, making the two keys
    identical.

    Returns a reference to this QSslKey.
*/
QSslKey &QSslKey::operator=(const QSslKey &other)
{
    qAtomicAssign(d, other.d);
    return *this;
}

/*!
    Returns true if this is a null key; otherwise false.

    \sa clear()
*/
bool QSslKey::isNull() const
{
    return d->isNull;
}

/*!
    Clears the contents of this key, making it a null key.

    \sa isNull()
*/
void QSslKey::clear()
{
    if (!d->ref.deref()) {
        delete d;
        d = new QSslKeyPrivate;
    }
}

/*!
    Returns the length of the key in bits, or -1 if the key is null.
*/
int QSslKey::length() const
{
    if (d->isNull)
        return -1;
    return (d->algorithm == QSsl::Rsa)
           ? q_BN_num_bits(d->rsa->n) : q_BN_num_bits(d->dsa->p);
}

/*!
    Returns the type of the key (i.e., PublicKey or PrivateKey).
*/
QSsl::KeyType QSslKey::type() const
{
    return d->type;
}

/*!
    Returns the key algorithm.
*/
QSsl::KeyAlgorithm QSslKey::algorithm() const
{
    return d->algorithm;
}

/*!
  Returns the key in DER encoding. The result is encrypted with
  \a passPhrase if the key is a private key and \a passPhrase is
  non-empty.
*/
// ### autotest failure for non-empty passPhrase and private key
QByteArray QSslKey::toDer(const QByteArray &passPhrase) const
{
    if (d->isNull)
        return QByteArray();
    return d->derFromPem(toPem(passPhrase));
}

/*!
  Returns the key in PEM encoding. The result is encrypted with
  \a passPhrase if the key is a private key and \a passPhrase is
  non-empty.
*/
QByteArray QSslKey::toPem(const QByteArray &passPhrase) const
{
    if (!QSslSocket::supportsSsl() || d->isNull)
        return QByteArray();

    BIO *bio = q_BIO_new(q_BIO_s_mem());
    if (!bio)
        return QByteArray();

    bool fail = false;

    if (d->algorithm == QSsl::Rsa) {
        if (d->type == QSsl::PublicKey) {
            if (!q_PEM_write_bio_RSA_PUBKEY(bio, d->rsa))
                fail = true;
        } else {
            if (!q_PEM_write_bio_RSAPrivateKey(
                    bio, d->rsa,
                    // ### the cipher should be selectable in the API:
                    passPhrase.isEmpty() ? (const EVP_CIPHER *)0 : q_EVP_des_ede3_cbc(),
                    (uchar *)passPhrase.data(), passPhrase.size(), 0, 0)) {
                fail = true;
            }
        }
    } else {
        if (d->type == QSsl::PublicKey) {
            if (!q_PEM_write_bio_DSA_PUBKEY(bio, d->dsa))
                fail = true;
        } else {
            if (!q_PEM_write_bio_DSAPrivateKey(
                    bio, d->dsa,
                    // ### the cipher should be selectable in the API:
                    passPhrase.isEmpty() ? (const EVP_CIPHER *)0 : q_EVP_des_ede3_cbc(),
                    (uchar *)passPhrase.data(), passPhrase.size(), 0, 0)) {
                fail = true;
            }
        }
    }

    QByteArray pem;
    if (!fail) {
        char *data;
        long size = q_BIO_get_mem_data(bio, &data);
        pem = QByteArray(data, size);
    }
    q_BIO_free(bio);
    return pem;
}

/*!
    Returns a pointer to the native key handle, if it is available;
    otherwise a null pointer is returned.

    You can use this handle together with the native API to access
    extended information about the key.

    \warning Use of this function has a high probability of being
    non-portable, and its return value may vary across platforms, and
    between minor Qt releases.
*/
Qt::HANDLE QSslKey::handle() const
{
    return (d->algorithm == QSsl::Rsa) ? Qt::HANDLE(d->rsa) : Qt::HANDLE(d->dsa);
}

/*!
    Returns true if this key is equal to \a other; otherwise returns false.
*/
bool QSslKey::operator==(const QSslKey &other) const
{
    if (isNull())
        return other.isNull();
    if (other.isNull())
        return isNull();
    if (algorithm() != other.algorithm())
        return false;
    if (type() != other.type())
        return false;
    if (length() != other.length())
        return false;
    return toDer() == other.toDer();
}

/*! \fn bool QSslKey::operator!=(const QSslKey &other) const

  Returns true if this key is not equal to key \a other; otherwise
  returns false.
*/

#ifndef QT_NO_DEBUG_STREAM
class QDebug;
QDebug operator<<(QDebug debug, const QSslKey &key)
{
    debug << "QSslKey("
          << (key.type() == QSsl::PublicKey ? "PublicKey" : "PrivateKey")
          << ", " << (key.algorithm() == QSsl::Rsa ? "RSA" : "DSA")
          << ", " << key.length()
          << ")";
    return debug;
}
#endif

QT_END_NAMESPACE
