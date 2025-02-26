/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QFONTENGINE_QPF_P_H
#define QFONTENGINE_QPF_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qfontengine_p.h"
#include <qendian.h>
#include <qbuffer.h>

#ifndef QT_NO_QWS_QPF2
#if !defined(QT_NO_FREETYPE)
#   include "qfontengine_ft_p.h"
#endif
#endif

QT_BEGIN_NAMESPACE

#ifndef QT_NO_QWS_QPF2

class QFontEngine;
class QFreetypeFace;

class Q_GUI_EXPORT QFontEngineQPF : public QFontEngine
{
public:
    // if you add new tags please make sure to update the tables in
    // qpfutil.cpp and tools/makeqpf/qpf2.cpp
    enum HeaderTag {
        Tag_FontName,          // 0 string
        Tag_FileName,          // 1 string
        Tag_FileIndex,         // 2 quint32
        Tag_FontRevision,      // 3 quint32
        Tag_FreeText,          // 4 string
        Tag_Ascent,            // 5 QFixed
        Tag_Descent,           // 6 QFixed
        Tag_Leading,           // 7 QFixed
        Tag_XHeight,           // 8 QFixed
        Tag_AverageCharWidth,  // 9 QFixed
        Tag_MaxCharWidth,      // 10 QFixed
        Tag_LineThickness,     // 11 QFixed
        Tag_MinLeftBearing,    // 12 QFixed
        Tag_MinRightBearing,   // 13 QFixed
        Tag_UnderlinePosition, // 14 QFixed
        Tag_GlyphFormat,       // 15 quint8
        Tag_PixelSize,         // 16 quint8
        Tag_Weight,            // 17 quint8
        Tag_Style,             // 18 quint8
        Tag_EndOfHeader,       // 19 string
        Tag_WritingSystems,    // 20 bitfield

        NumTags
    };

    enum TagType {
        StringType,
        FixedType,
        UInt8Type,
        UInt32Type,
        BitFieldType
    };

    struct Tag
    {
        quint16 tag;
        quint16 size;
    };

    enum GlyphFormat {
        BitmapGlyphs = 1,
        AlphamapGlyphs = 8
    };

    enum {
        CurrentMajorVersion = 2,
        CurrentMinorVersion = 0
    };

    // The CMap is identical to the TrueType CMap table format
    // The GMap table is a normal array with the total number of
    // covered glyphs in the TrueType font
    enum BlockTag {
        CMapBlock,
        GMapBlock,
        GlyphBlock
    };

    struct Q_PACKED Header
    {
        char magic[4]; // 'QPF2'
        quint32 lock;  // values: 0 = unlocked, 0xffffffff = read-only, otherwise qws client id of locking process
        quint8 majorVersion;
        quint8 minorVersion;
        quint16 dataSize;
    };

    struct Q_PACKED Block
    {
        quint16 tag;
        quint16 pad;
        quint32 dataSize;
    };

    struct Q_PACKED Glyph
    {
        quint8 width;
        quint8 height;
        quint8 bytesPerLine;
        qint8 x;
        qint8 y;
        qint8 advance;
    };

#ifdef QT_FONTS_ARE_RESOURCES
    QFontEngineQPF(const QFontDef &def, const uchar *bytes, int size);
#else
    QFontEngineQPF(const QFontDef &def, int fd, QFontEngine *renderingFontEngine = 0);
#endif
    ~QFontEngineQPF();

    FaceId faceId() const { return face_id; }
    bool getSfntTableData(uint tag, uchar *buffer, uint *length) const;

    bool stringToCMap(const QChar *str, int len, QGlyphLayout *glyphs, int *nglyphs, QTextEngine::ShaperFlags flags) const;
    void recalcAdvances(QGlyphLayout *, QTextEngine::ShaperFlags) const;

    void draw(QPaintEngine *p, qreal x, qreal y, const QTextItemInt &si);
    void addOutlineToPath(qreal x, qreal y, const QGlyphLayout &glyphs, QPainterPath *path, QTextItem::RenderFlags flags);
    QImage alphaMapForGlyph(glyph_t t);

    glyph_metrics_t boundingBox(const QGlyphLayout &glyphs);
    glyph_metrics_t boundingBox(glyph_t glyph);

    QFixed ascent() const;
    QFixed descent() const;
    QFixed leading() const;
    qreal maxCharWidth() const;
    qreal minLeftBearing() const;
    qreal minRightBearing() const;
    QFixed underlinePosition() const;
    QFixed lineThickness() const;

    Type type() const;

    bool canRender(const QChar *string, int len);
    inline const char *name() const { return "QPF2"; }

    virtual int glyphCount() const { return glyphMapEntries; }

    bool isValid() const;

    const Glyph *findGlyph(glyph_t g) const;

    static bool verifyHeader(const uchar *data, int size);
    static QVariant extractHeaderField(const uchar *data, HeaderTag tag);
    static QList<QByteArray> cleanUpAfterClientCrash(const QList<int> &crashedClientIds);

#if !defined(QT_NO_FREETYPE)
    FT_Face lockFace() const;
    void unlockFace() const;
    void doKerning(QGlyphLayout *g, QTextEngine::ShaperFlags flags) const;
    virtual HB_Error getPointInOutline(HB_Glyph glyph, int flags, hb_uint32 point, HB_Fixed *xpos, HB_Fixed *ypos, hb_uint32 *nPoints);
    virtual QFixed emSquareSize() const;
#endif

    inline QString fontFile() const { return fileName; }

    QFontEngine *renderingEngine() const { return renderingFontEngine; }

    QFontEngine *takeRenderingEngine()
    {
        QFontEngine *engine = renderingFontEngine;
        renderingFontEngine = 0;
        return engine;
    }

private:
#if !defined(QT_NO_FREETYPE)
    void ensureGlyphsLoaded(const QGlyphLayout &glyphs);
    void loadGlyph(glyph_t glyph);
    bool lockFile();
    void unlockFile();
    void remapFontData();
#endif

    int fd;
    const uchar *fontData;
    int dataSize;
    const uchar *externalCMap;
    quint32 cmapOffset;
    int cmapSize;
    quint32 glyphMapOffset;
    quint32 glyphMapEntries;
    quint32 glyphDataOffset;
    quint32 glyphDataSize;
    QString fileName;
    bool readOnly;

    QFreetypeFace *freetype;
    FaceId face_id;
    QByteArray freetypeCMapTable;
    mutable bool kerning_pairs_loaded;
    QFontEngine *renderingFontEngine;
};

struct QPFGenerator
{
    QPFGenerator(QBuffer *device, QFontEngine *engine)
        : dev(device), fe(engine) {}

    void generate();
    void writeHeader();
    void writeGMap();
    void writeBlock(QFontEngineQPF::BlockTag tag, const QByteArray &data);

    void writeTaggedString(QFontEngineQPF::HeaderTag tag, const QByteArray &string);
    void writeTaggedUInt32(QFontEngineQPF::HeaderTag tag, quint32 value);
    void writeTaggedUInt8(QFontEngineQPF::HeaderTag tag, quint8 value);
    void writeTaggedQFixed(QFontEngineQPF::HeaderTag tag, QFixed value);

    void writeUInt16(quint16 value) { value = qToBigEndian(value); dev->write((const char *)&value, sizeof(value)); }
    void writeUInt32(quint32 value) { value = qToBigEndian(value); dev->write((const char *)&value, sizeof(value)); }
    void writeUInt8(quint8 value) { dev->write((const char *)&value, sizeof(value)); }
    void writeInt8(qint8 value) { dev->write((const char *)&value, sizeof(value)); }

    void align4() { while (dev->pos() & 3) { dev->putChar('\0'); } }

    QBuffer *dev;
    QFontEngine *fe;
};

#endif // QT_NO_QWS_QPF2

class QFontEngineMultiQWS : public QFontEngineMulti
{
public:
    QFontEngineMultiQWS(QFontEngine *fe, int script, const QStringList &fallbacks);

    void loadEngine(int at);
    void draw(QPaintEngine *p, qreal x, qreal y, const QTextItemInt &si);

private:
    QStringList fallbackFamilies;
    int script;
};

QT_END_NAMESPACE

#endif // QFONTENGINE_QPF_P_H
