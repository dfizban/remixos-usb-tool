/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "TextCodecUTF16.h"

#include "CString.h"
#include "PlatformString.h"

using std::auto_ptr;

namespace WebCore {

const UChar BOM = 0xFEFF;

void TextCodecUTF16::registerEncodingNames(EncodingNameRegistrar registrar)
{
    registrar("UTF-16LE", "UTF-16LE");
    registrar("UTF-16BE", "UTF-16BE");

    registrar("ISO-10646-UCS-2", "UTF-16LE");
    registrar("UCS-2", "UTF-16LE");
    registrar("UTF-16", "UTF-16LE");
    registrar("Unicode", "UTF-16LE");
    registrar("csUnicode", "UTF-16LE");
    registrar("unicodeFEFF", "UTF-16LE");

    registrar("unicodeFFFE", "UTF-16BE");
}

static auto_ptr<TextCodec> newStreamingTextDecoderUTF16LE(const TextEncoding&, const void*)
{
    return auto_ptr<TextCodec>(new TextCodecUTF16(true));
}

static auto_ptr<TextCodec> newStreamingTextDecoderUTF16BE(const TextEncoding&, const void*)
{
    return auto_ptr<TextCodec>(new TextCodecUTF16(false));
}

void TextCodecUTF16::registerCodecs(TextCodecRegistrar registrar)
{
    registrar("UTF-16LE", newStreamingTextDecoderUTF16LE, 0);
    registrar("UTF-16BE", newStreamingTextDecoderUTF16BE, 0);
}

String TextCodecUTF16::decode(const char* bytes, size_t length, bool)
{
    if (!length)
        return String();

    const unsigned char* p = reinterpret_cast<const unsigned char*>(bytes);
    size_t numBytes = length + m_haveBufferedByte;
    size_t numChars = numBytes / 2;

    UChar* buffer;
    String result = String::newUninitialized(numChars, buffer);
    UChar* q = buffer;

    if (m_haveBufferedByte) {
        UChar c;
        if (m_littleEndian)
            c = m_bufferedByte | (p[0] << 8);
        else
            c = (m_bufferedByte << 8) | p[0];
        if (c != BOM)
            *q++ = c;
        m_haveBufferedByte = false;
        p += 1;
        numChars -= 1;
    }

    if (m_littleEndian)
        for (size_t i = 0; i < numChars; ++i) {
            UChar c = p[0] | (p[1] << 8);
            p += 2;
            if (c != BOM)
                *q++ = c;
        }
    else
        for (size_t i = 0; i < numChars; ++i) {
            UChar c = (p[0] << 8) | p[1];
            p += 2;
            if (c != BOM)
                *q++ = c;
        }

    if (numBytes & 1) {
        ASSERT(!m_haveBufferedByte);
        m_haveBufferedByte = true;
        m_bufferedByte = p[0];
    }

    result.truncate(q - buffer);
    return result;
}

CString TextCodecUTF16::encode(const UChar* characters, size_t length, bool)
{
    char* bytes;
    CString string = CString::newUninitialized(length * 2, bytes);

    // FIXME: CString is not a reasonable data structure for encoded UTF-16, which will have
    // null characters inside it. Perhaps the result of encode should not be a CString?
    if (m_littleEndian)
        for (size_t i = 0; i < length; ++i) {
            UChar c = characters[i];
            bytes[i * 2] = c;
            bytes[i * 2 + 1] = c >> 8;
        }
    else
        for (size_t i = 0; i < length; ++i) {
            UChar c = characters[i];
            bytes[i * 2] = c >> 8;
            bytes[i * 2 + 1] = c;
        }

    return string;
}

} // namespace WebCore
