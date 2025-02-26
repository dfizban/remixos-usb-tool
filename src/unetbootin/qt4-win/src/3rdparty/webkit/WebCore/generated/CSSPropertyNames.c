/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf -a -L ANSI-C -E -C -c -o -t --key-positions='*' -NfindProp -Hhash_prop -Wwordlist_prop -D -s 2 CSSPropertyNames.gperf  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "CSSPropertyNames.gperf"

/* This file is automatically generated from CSSPropertyNames.in by makeprop, do not edit */
#include "CSSPropertyNames.h"
#line 5 "CSSPropertyNames.gperf"
struct props {
    const char* name;
    int id;
};
/* maximum key range = 1049, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash_prop (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052,    0, 1052, 1052, 1052, 1052,
      1052,    0, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052,   20,    5,    0,
         0,    0,  280,   15,  125,    0,    0,    5,    0,   85,
        10,    0,    0,  100,    0,    5,    0,   50,  135,   30,
       135,  365,   40, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
      1052, 1052, 1052, 1052, 1052, 1052
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[42]];
      /*FALLTHROUGH*/
      case 42:
        hval += asso_values[(unsigned char)str[41]];
      /*FALLTHROUGH*/
      case 41:
        hval += asso_values[(unsigned char)str[40]];
      /*FALLTHROUGH*/
      case 40:
        hval += asso_values[(unsigned char)str[39]];
      /*FALLTHROUGH*/
      case 39:
        hval += asso_values[(unsigned char)str[38]];
      /*FALLTHROUGH*/
      case 38:
        hval += asso_values[(unsigned char)str[37]];
      /*FALLTHROUGH*/
      case 37:
        hval += asso_values[(unsigned char)str[36]];
      /*FALLTHROUGH*/
      case 36:
        hval += asso_values[(unsigned char)str[35]];
      /*FALLTHROUGH*/
      case 35:
        hval += asso_values[(unsigned char)str[34]];
      /*FALLTHROUGH*/
      case 34:
        hval += asso_values[(unsigned char)str[33]];
      /*FALLTHROUGH*/
      case 33:
        hval += asso_values[(unsigned char)str[32]];
      /*FALLTHROUGH*/
      case 32:
        hval += asso_values[(unsigned char)str[31]];
      /*FALLTHROUGH*/
      case 31:
        hval += asso_values[(unsigned char)str[30]];
      /*FALLTHROUGH*/
      case 30:
        hval += asso_values[(unsigned char)str[29]];
      /*FALLTHROUGH*/
      case 29:
        hval += asso_values[(unsigned char)str[28]];
      /*FALLTHROUGH*/
      case 28:
        hval += asso_values[(unsigned char)str[27]];
      /*FALLTHROUGH*/
      case 27:
        hval += asso_values[(unsigned char)str[26]];
      /*FALLTHROUGH*/
      case 26:
        hval += asso_values[(unsigned char)str[25]];
      /*FALLTHROUGH*/
      case 25:
        hval += asso_values[(unsigned char)str[24]];
      /*FALLTHROUGH*/
      case 24:
        hval += asso_values[(unsigned char)str[23]];
      /*FALLTHROUGH*/
      case 23:
        hval += asso_values[(unsigned char)str[22]];
      /*FALLTHROUGH*/
      case 22:
        hval += asso_values[(unsigned char)str[21]];
      /*FALLTHROUGH*/
      case 21:
        hval += asso_values[(unsigned char)str[20]];
      /*FALLTHROUGH*/
      case 20:
        hval += asso_values[(unsigned char)str[19]];
      /*FALLTHROUGH*/
      case 19:
        hval += asso_values[(unsigned char)str[18]];
      /*FALLTHROUGH*/
      case 18:
        hval += asso_values[(unsigned char)str[17]];
      /*FALLTHROUGH*/
      case 17:
        hval += asso_values[(unsigned char)str[16]];
      /*FALLTHROUGH*/
      case 16:
        hval += asso_values[(unsigned char)str[15]];
      /*FALLTHROUGH*/
      case 15:
        hval += asso_values[(unsigned char)str[14]];
      /*FALLTHROUGH*/
      case 14:
        hval += asso_values[(unsigned char)str[13]];
      /*FALLTHROUGH*/
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct props *
findProp (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 196,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 43,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 1051
    };

  static const struct props wordlist_prop[] =
    {
#line 130 "CSSPropertyNames.gperf"
      {"top", CSS_PROP_TOP},
#line 43 "CSSPropertyNames.gperf"
      {"clip", CSS_PROP_CLIP},
#line 44 "CSSPropertyNames.gperf"
      {"color", CSS_PROP_COLOR},
#line 18 "CSSPropertyNames.gperf"
      {"border", CSS_PROP_BORDER},
#line 35 "CSSPropertyNames.gperf"
      {"border-top", CSS_PROP_BORDER_TOP},
#line 24 "CSSPropertyNames.gperf"
      {"border-color", CSS_PROP_BORDER_COLOR},
#line 49 "CSSPropertyNames.gperf"
      {"direction", CSS_PROP_DIRECTION},
#line 36 "CSSPropertyNames.gperf"
      {"border-top-color", CSS_PROP_BORDER_TOP_COLOR},
#line 96 "CSSPropertyNames.gperf"
      {"position", CSS_PROP_POSITION},
#line 42 "CSSPropertyNames.gperf"
      {"clear", CSS_PROP_CLEAR},
#line 45 "CSSPropertyNames.gperf"
      {"content", CSS_PROP_CONTENT},
#line 92 "CSSPropertyNames.gperf"
      {"page", CSS_PROP_PAGE},
#line 23 "CSSPropertyNames.gperf"
      {"border-collapse", CSS_PROP_BORDER_COLLAPSE},
#line 41 "CSSPropertyNames.gperf"
      {"caption-side", CSS_PROP_CAPTION_SIDE},
#line 107 "CSSPropertyNames.gperf"
      {"size", CSS_PROP_SIZE},
#line 98 "CSSPropertyNames.gperf"
      {"resize", CSS_PROP_RESIZE},
#line 87 "CSSPropertyNames.gperf"
      {"padding", CSS_PROP_PADDING},
#line 91 "CSSPropertyNames.gperf"
      {"padding-top", CSS_PROP_PADDING_TOP},
#line 48 "CSSPropertyNames.gperf"
      {"cursor", CSS_PROP_CURSOR},
#line 62 "CSSPropertyNames.gperf"
      {"letter-spacing", CSS_PROP_LETTER_SPACING},
#line 79 "CSSPropertyNames.gperf"
      {"outline", CSS_PROP_OUTLINE},
#line 33 "CSSPropertyNames.gperf"
      {"border-spacing", CSS_PROP_BORDER_SPACING},
#line 137 "CSSPropertyNames.gperf"
      {"word-break", CSS_PROP_WORD_BREAK},
#line 135 "CSSPropertyNames.gperf"
      {"widows", CSS_PROP_WIDOWS},
#line 80 "CSSPropertyNames.gperf"
      {"outline-color", CSS_PROP_OUTLINE_COLOR},
#line 106 "CSSPropertyNames.gperf"
      {"scrollbar-track-color", CSS_PROP_SCROLLBAR_TRACK_COLOR},
#line 131 "CSSPropertyNames.gperf"
      {"unicode-bidi", CSS_PROP_UNICODE_BIDI},
#line 47 "CSSPropertyNames.gperf"
      {"counter-reset", CSS_PROP_COUNTER_RESET},
#line 195 "CSSPropertyNames.gperf"
      {"-webkit-rtl-ordering", CSS_PROP__WEBKIT_RTL_ORDERING},
#line 139 "CSSPropertyNames.gperf"
      {"word-wrap", CSS_PROP_WORD_WRAP},
#line 138 "CSSPropertyNames.gperf"
      {"word-spacing", CSS_PROP_WORD_SPACING},
#line 146 "CSSPropertyNames.gperf"
      {"-webkit-binding", CSS_PROP__WEBKIT_BINDING},
#line 40 "CSSPropertyNames.gperf"
      {"bottom", CSS_PROP_BOTTOM},
#line 95 "CSSPropertyNames.gperf"
      {"page-break-inside", CSS_PROP_PAGE_BREAK_INSIDE},
#line 180 "CSSPropertyNames.gperf"
      {"-webkit-line-break", CSS_PROP__WEBKIT_LINE_BREAK},
#line 101 "CSSPropertyNames.gperf"
      {"scrollbar-arrow-color", CSS_PROP_SCROLLBAR_ARROW_COLOR},
#line 19 "CSSPropertyNames.gperf"
      {"border-bottom", CSS_PROP_BORDER_BOTTOM},
#line 20 "CSSPropertyNames.gperf"
      {"border-bottom-color", CSS_PROP_BORDER_BOTTOM_COLOR},
#line 10 "CSSPropertyNames.gperf"
      {"background", CSS_PROP_BACKGROUND},
#line 205 "CSSPropertyNames.gperf"
      {"-webkit-user-select", CSS_PROP__WEBKIT_USER_SELECT},
#line 12 "CSSPropertyNames.gperf"
      {"background-color", CSS_PROP_BACKGROUND_COLOR},
#line 141 "CSSPropertyNames.gperf"
      {"-webkit-appearance", CSS_PROP__WEBKIT_APPEARANCE},
#line 194 "CSSPropertyNames.gperf"
      {"-webkit-padding-start", CSS_PROP__WEBKIT_PADDING_START},
#line 68 "CSSPropertyNames.gperf"
      {"margin", CSS_PROP_MARGIN},
#line 14 "CSSPropertyNames.gperf"
      {"background-position", CSS_PROP_BACKGROUND_POSITION},
#line 72 "CSSPropertyNames.gperf"
      {"margin-top", CSS_PROP_MARGIN_TOP},
#line 152 "CSSPropertyNames.gperf"
      {"-webkit-border-radius", CSS_PROP__WEBKIT_BORDER_RADIUS},
#line 17 "CSSPropertyNames.gperf"
      {"background-repeat", CSS_PROP_BACKGROUND_REPEAT},
#line 99 "CSSPropertyNames.gperf"
      {"right", CSS_PROP_RIGHT},
#line 203 "CSSPropertyNames.gperf"
      {"-webkit-user-drag", CSS_PROP__WEBKIT_USER_DRAG},
#line 88 "CSSPropertyNames.gperf"
      {"padding-bottom", CSS_PROP_PADDING_BOTTOM},
#line 29 "CSSPropertyNames.gperf"
      {"border-right", CSS_PROP_BORDER_RIGHT},
#line 136 "CSSPropertyNames.gperf"
      {"width", CSS_PROP_WIDTH},
#line 97 "CSSPropertyNames.gperf"
      {"quotes", CSS_PROP_QUOTES},
#line 193 "CSSPropertyNames.gperf"
      {"-webkit-nbsp-mode", CSS_PROP__WEBKIT_NBSP_MODE},
#line 30 "CSSPropertyNames.gperf"
      {"border-right-color", CSS_PROP_BORDER_RIGHT_COLOR},
#line 111 "CSSPropertyNames.gperf"
      {"text-indent", CSS_PROP_TEXT_INDENT},
#line 78 "CSSPropertyNames.gperf"
      {"orphans", CSS_PROP_ORPHANS},
#line 142 "CSSPropertyNames.gperf"
      {"-webkit-background-clip", CSS_PROP__WEBKIT_BACKGROUND_CLIP},
#line 39 "CSSPropertyNames.gperf"
      {"border-width", CSS_PROP_BORDER_WIDTH},
#line 181 "CSSPropertyNames.gperf"
      {"-webkit-line-clamp", CSS_PROP__WEBKIT_LINE_CLAMP},
#line 38 "CSSPropertyNames.gperf"
      {"border-top-width", CSS_PROP_BORDER_TOP_WIDTH},
#line 110 "CSSPropertyNames.gperf"
      {"text-decoration", CSS_PROP_TEXT_DECORATION},
#line 46 "CSSPropertyNames.gperf"
      {"counter-increment", CSS_PROP_COUNTER_INCREMENT},
#line 151 "CSSPropertyNames.gperf"
      {"-webkit-border-image", CSS_PROP__WEBKIT_BORDER_IMAGE},
#line 109 "CSSPropertyNames.gperf"
      {"text-align", CSS_PROP_TEXT_ALIGN},
#line 134 "CSSPropertyNames.gperf"
      {"white-space", CSS_PROP_WHITE_SPACE},
#line 140 "CSSPropertyNames.gperf"
      {"z-index", CSS_PROP_Z_INDEX},
#line 100 "CSSPropertyNames.gperf"
      {"scrollbar-3dlight-color", CSS_PROP_SCROLLBAR_3DLIGHT_COLOR},
#line 144 "CSSPropertyNames.gperf"
      {"-webkit-background-origin", CSS_PROP__WEBKIT_BACKGROUND_ORIGIN},
#line 90 "CSSPropertyNames.gperf"
      {"padding-right", CSS_PROP_PADDING_RIGHT},
#line 200 "CSSPropertyNames.gperf"
      {"-webkit-text-stroke", CSS_PROP__WEBKIT_TEXT_STROKE},
#line 176 "CSSPropertyNames.gperf"
      {"-webkit-columns", CSS_PROP__WEBKIT_COLUMNS},
#line 162 "CSSPropertyNames.gperf"
      {"-webkit-box-orient", CSS_PROP__WEBKIT_BOX_ORIENT},
#line 201 "CSSPropertyNames.gperf"
      {"-webkit-text-stroke-color", CSS_PROP__WEBKIT_TEXT_STROKE_COLOR},
#line 157 "CSSPropertyNames.gperf"
      {"-webkit-box-direction", CSS_PROP__WEBKIT_BOX_DIRECTION},
#line 160 "CSSPropertyNames.gperf"
      {"-webkit-box-lines", CSS_PROP__WEBKIT_BOX_LINES},
#line 145 "CSSPropertyNames.gperf"
      {"-webkit-background-size", CSS_PROP__WEBKIT_BACKGROUND_SIZE},
#line 132 "CSSPropertyNames.gperf"
      {"vertical-align", CSS_PROP_VERTICAL_ALIGN},
#line 184 "CSSPropertyNames.gperf"
      {"-webkit-margin-start", CSS_PROP__WEBKIT_MARGIN_START},
#line 183 "CSSPropertyNames.gperf"
      {"-webkit-margin-collapse", CSS_PROP__WEBKIT_MARGIN_COLLAPSE},
#line 125 "CSSPropertyNames.gperf"
      {"text-underline", CSS_PROP_TEXT_UNDERLINE},
#line 163 "CSSPropertyNames.gperf"
      {"-webkit-box-pack", CSS_PROP__WEBKIT_BOX_PACK},
#line 185 "CSSPropertyNames.gperf"
      {"-webkit-margin-top-collapse", CSS_PROP__WEBKIT_MARGIN_TOP_COLLAPSE},
#line 126 "CSSPropertyNames.gperf"
      {"text-underline-color", CSS_PROP_TEXT_UNDERLINE_COLOR},
#line 83 "CSSPropertyNames.gperf"
      {"outline-width", CSS_PROP_OUTLINE_WIDTH},
#line 105 "CSSPropertyNames.gperf"
      {"scrollbar-shadow-color", CSS_PROP_SCROLLBAR_SHADOW_COLOR},
#line 69 "CSSPropertyNames.gperf"
      {"margin-bottom", CSS_PROP_MARGIN_BOTTOM},
#line 170 "CSSPropertyNames.gperf"
      {"-webkit-column-gap", CSS_PROP__WEBKIT_COLUMN_GAP},
#line 13 "CSSPropertyNames.gperf"
      {"background-image", CSS_PROP_BACKGROUND_IMAGE},
#line 156 "CSSPropertyNames.gperf"
      {"-webkit-box-align", CSS_PROP__WEBKIT_BOX_ALIGN},
#line 171 "CSSPropertyNames.gperf"
      {"-webkit-column-rule", CSS_PROP__WEBKIT_COLUMN_RULE},
#line 168 "CSSPropertyNames.gperf"
      {"-webkit-column-break-inside", CSS_PROP__WEBKIT_COLUMN_BREAK_INSIDE},
#line 76 "CSSPropertyNames.gperf"
      {"min-width", CSS_PROP_MIN_WIDTH},
#line 172 "CSSPropertyNames.gperf"
      {"-webkit-column-rule-color", CSS_PROP__WEBKIT_COLUMN_RULE_COLOR},
#line 102 "CSSPropertyNames.gperf"
      {"scrollbar-darkshadow-color", CSS_PROP_SCROLLBAR_DARKSHADOW_COLOR},
#line 143 "CSSPropertyNames.gperf"
      {"-webkit-background-composite", CSS_PROP__WEBKIT_BACKGROUND_COMPOSITE},
#line 177 "CSSPropertyNames.gperf"
      {"-webkit-dashboard-region", CSS_PROP__WEBKIT_DASHBOARD_REGION},
#line 169 "CSSPropertyNames.gperf"
      {"-webkit-column-count", CSS_PROP__WEBKIT_COLUMN_COUNT},
#line 165 "CSSPropertyNames.gperf"
      {"-webkit-box-sizing", CSS_PROP__WEBKIT_BOX_SIZING},
#line 22 "CSSPropertyNames.gperf"
      {"border-bottom-width", CSS_PROP_BORDER_BOTTOM_WIDTH},
#line 60 "CSSPropertyNames.gperf"
      {"height", CSS_PROP_HEIGHT},
#line 15 "CSSPropertyNames.gperf"
      {"background-position-x", CSS_PROP_BACKGROUND_POSITION_X},
#line 155 "CSSPropertyNames.gperf"
      {"-webkit-border-vertical-spacing", CSS_PROP__WEBKIT_BORDER_VERTICAL_SPACING},
#line 71 "CSSPropertyNames.gperf"
      {"margin-right", CSS_PROP_MARGIN_RIGHT},
#line 61 "CSSPropertyNames.gperf"
      {"left", CSS_PROP_LEFT},
#line 63 "CSSPropertyNames.gperf"
      {"line-height", CSS_PROP_LINE_HEIGHT},
#line 154 "CSSPropertyNames.gperf"
      {"-webkit-border-top-right-radius", CSS_PROP__WEBKIT_BORDER_TOP_RIGHT_RADIUS},
#line 118 "CSSPropertyNames.gperf"
      {"text-overline", CSS_PROP_TEXT_OVERLINE},
#line 53 "CSSPropertyNames.gperf"
      {"font", CSS_PROP_FONT},
#line 25 "CSSPropertyNames.gperf"
      {"border-left", CSS_PROP_BORDER_LEFT},
#line 119 "CSSPropertyNames.gperf"
      {"text-overline-color", CSS_PROP_TEXT_OVERLINE_COLOR},
#line 161 "CSSPropertyNames.gperf"
      {"-webkit-box-ordinal-group", CSS_PROP__WEBKIT_BOX_ORDINAL_GROUP},
#line 26 "CSSPropertyNames.gperf"
      {"border-left-color", CSS_PROP_BORDER_LEFT_COLOR},
#line 52 "CSSPropertyNames.gperf"
      {"float", CSS_PROP_FLOAT},
#line 127 "CSSPropertyNames.gperf"
      {"text-underline-mode", CSS_PROP_TEXT_UNDERLINE_MODE},
#line 186 "CSSPropertyNames.gperf"
      {"-webkit-marquee", CSS_PROP__WEBKIT_MARQUEE},
#line 182 "CSSPropertyNames.gperf"
      {"-webkit-margin-bottom-collapse", CSS_PROP__WEBKIT_MARGIN_BOTTOM_COLLAPSE},
#line 32 "CSSPropertyNames.gperf"
      {"border-right-width", CSS_PROP_BORDER_RIGHT_WIDTH},
#line 199 "CSSPropertyNames.gperf"
      {"-webkit-text-size-adjust", CSS_PROP__WEBKIT_TEXT_SIZE_ADJUST},
#line 190 "CSSPropertyNames.gperf"
      {"-webkit-marquee-speed", CSS_PROP__WEBKIT_MARQUEE_SPEED},
#line 150 "CSSPropertyNames.gperf"
      {"-webkit-border-horizontal-spacing", CSS_PROP__WEBKIT_BORDER_HORIZONTAL_SPACING},
#line 123 "CSSPropertyNames.gperf"
      {"text-shadow", CSS_PROP_TEXT_SHADOW},
#line 187 "CSSPropertyNames.gperf"
      {"-webkit-marquee-direction", CSS_PROP__WEBKIT_MARQUEE_DIRECTION},
#line 189 "CSSPropertyNames.gperf"
      {"-webkit-marquee-repetition", CSS_PROP__WEBKIT_MARQUEE_REPETITION},
#line 89 "CSSPropertyNames.gperf"
      {"padding-left", CSS_PROP_PADDING_LEFT},
#line 149 "CSSPropertyNames.gperf"
      {"-webkit-border-fit", CSS_PROP__WEBKIT_BORDER_FIT},
#line 55 "CSSPropertyNames.gperf"
      {"font-size", CSS_PROP_FONT_SIZE},
#line 103 "CSSPropertyNames.gperf"
      {"scrollbar-face-color", CSS_PROP_SCROLLBAR_FACE_COLOR},
#line 175 "CSSPropertyNames.gperf"
      {"-webkit-column-width", CSS_PROP__WEBKIT_COLUMN_WIDTH},
#line 202 "CSSPropertyNames.gperf"
      {"-webkit-text-stroke-width", CSS_PROP__WEBKIT_TEXT_STROKE_WIDTH},
#line 94 "CSSPropertyNames.gperf"
      {"page-break-before", CSS_PROP_PAGE_BREAK_BEFORE},
#line 75 "CSSPropertyNames.gperf"
      {"min-height", CSS_PROP_MIN_HEIGHT},
#line 164 "CSSPropertyNames.gperf"
      {"-webkit-box-shadow", CSS_PROP__WEBKIT_BOX_SHADOW},
#line 129 "CSSPropertyNames.gperf"
      {"text-underline-width", CSS_PROP_TEXT_UNDERLINE_WIDTH},
#line 93 "CSSPropertyNames.gperf"
      {"page-break-after", CSS_PROP_PAGE_BREAK_AFTER},
#line 120 "CSSPropertyNames.gperf"
      {"text-overline-mode", CSS_PROP_TEXT_OVERLINE_MODE},
#line 148 "CSSPropertyNames.gperf"
      {"-webkit-border-bottom-right-radius", CSS_PROP__WEBKIT_BORDER_BOTTOM_RIGHT_RADIUS},
#line 64 "CSSPropertyNames.gperf"
      {"list-style", CSS_PROP_LIST_STYLE},
#line 11 "CSSPropertyNames.gperf"
      {"background-attachment", CSS_PROP_BACKGROUND_ATTACHMENT},
#line 34 "CSSPropertyNames.gperf"
      {"border-style", CSS_PROP_BORDER_STYLE},
#line 37 "CSSPropertyNames.gperf"
      {"border-top-style", CSS_PROP_BORDER_TOP_STYLE},
#line 77 "CSSPropertyNames.gperf"
      {"opacity", CSS_PROP_OPACITY},
#line 50 "CSSPropertyNames.gperf"
      {"display", CSS_PROP_DISPLAY},
#line 74 "CSSPropertyNames.gperf"
      {"max-width", CSS_PROP_MAX_WIDTH},
#line 66 "CSSPropertyNames.gperf"
      {"list-style-position", CSS_PROP_LIST_STYLE_POSITION},
#line 174 "CSSPropertyNames.gperf"
      {"-webkit-column-rule-width", CSS_PROP__WEBKIT_COLUMN_RULE_WIDTH},
#line 178 "CSSPropertyNames.gperf"
      {"-webkit-font-size-delta", CSS_PROP__WEBKIT_FONT_SIZE_DELTA},
#line 70 "CSSPropertyNames.gperf"
      {"margin-left", CSS_PROP_MARGIN_LEFT},
#line 188 "CSSPropertyNames.gperf"
      {"-webkit-marquee-increment", CSS_PROP__WEBKIT_MARQUEE_INCREMENT},
#line 153 "CSSPropertyNames.gperf"
      {"-webkit-border-top-left-radius", CSS_PROP__WEBKIT_BORDER_TOP_LEFT_RADIUS},
#line 56 "CSSPropertyNames.gperf"
      {"font-stretch", CSS_PROP_FONT_STRETCH},
#line 82 "CSSPropertyNames.gperf"
      {"outline-style", CSS_PROP_OUTLINE_STYLE},
#line 84 "CSSPropertyNames.gperf"
      {"overflow", CSS_PROP_OVERFLOW},
#line 122 "CSSPropertyNames.gperf"
      {"text-overline-width", CSS_PROP_TEXT_OVERLINE_WIDTH},
#line 28 "CSSPropertyNames.gperf"
      {"border-left-width", CSS_PROP_BORDER_LEFT_WIDTH},
#line 104 "CSSPropertyNames.gperf"
      {"scrollbar-highlight-color", CSS_PROP_SCROLLBAR_HIGHLIGHT_COLOR},
#line 179 "CSSPropertyNames.gperf"
      {"-webkit-highlight", CSS_PROP__WEBKIT_HIGHLIGHT},
#line 51 "CSSPropertyNames.gperf"
      {"empty-cells", CSS_PROP_EMPTY_CELLS},
#line 59 "CSSPropertyNames.gperf"
      {"font-weight", CSS_PROP_FONT_WEIGHT},
#line 108 "CSSPropertyNames.gperf"
      {"table-layout", CSS_PROP_TABLE_LAYOUT},
#line 112 "CSSPropertyNames.gperf"
      {"text-line-through", CSS_PROP_TEXT_LINE_THROUGH},
#line 197 "CSSPropertyNames.gperf"
      {"-webkit-text-fill-color", CSS_PROP__WEBKIT_TEXT_FILL_COLOR},
#line 113 "CSSPropertyNames.gperf"
      {"text-line-through-color", CSS_PROP_TEXT_LINE_THROUGH_COLOR},
#line 21 "CSSPropertyNames.gperf"
      {"border-bottom-style", CSS_PROP_BORDER_BOTTOM_STYLE},
#line 58 "CSSPropertyNames.gperf"
      {"font-variant", CSS_PROP_FONT_VARIANT},
#line 16 "CSSPropertyNames.gperf"
      {"background-position-y", CSS_PROP_BACKGROUND_POSITION_Y},
#line 65 "CSSPropertyNames.gperf"
      {"list-style-image", CSS_PROP_LIST_STYLE_IMAGE},
#line 73 "CSSPropertyNames.gperf"
      {"max-height", CSS_PROP_MAX_HEIGHT},
#line 133 "CSSPropertyNames.gperf"
      {"visibility", CSS_PROP_VISIBILITY},
#line 147 "CSSPropertyNames.gperf"
      {"-webkit-border-bottom-left-radius", CSS_PROP__WEBKIT_BORDER_BOTTOM_LEFT_RADIUS},
#line 167 "CSSPropertyNames.gperf"
      {"-webkit-column-break-before", CSS_PROP__WEBKIT_COLUMN_BREAK_BEFORE},
#line 31 "CSSPropertyNames.gperf"
      {"border-right-style", CSS_PROP_BORDER_RIGHT_STYLE},
#line 166 "CSSPropertyNames.gperf"
      {"-webkit-column-break-after", CSS_PROP__WEBKIT_COLUMN_BREAK_AFTER},
#line 124 "CSSPropertyNames.gperf"
      {"text-transform", CSS_PROP_TEXT_TRANSFORM},
#line 114 "CSSPropertyNames.gperf"
      {"text-line-through-mode", CSS_PROP_TEXT_LINE_THROUGH_MODE},
#line 85 "CSSPropertyNames.gperf"
      {"overflow-x", CSS_PROP_OVERFLOW_X},
#line 117 "CSSPropertyNames.gperf"
      {"text-overflow", CSS_PROP_TEXT_OVERFLOW},
#line 128 "CSSPropertyNames.gperf"
      {"text-underline-style", CSS_PROP_TEXT_UNDERLINE_STYLE},
#line 158 "CSSPropertyNames.gperf"
      {"-webkit-box-flex", CSS_PROP__WEBKIT_BOX_FLEX},
#line 192 "CSSPropertyNames.gperf"
      {"-webkit-match-nearest-mail-blockquote-color", CSS_PROP__WEBKIT_MATCH_NEAREST_MAIL_BLOCKQUOTE_COLOR},
#line 198 "CSSPropertyNames.gperf"
      {"-webkit-text-security", CSS_PROP__WEBKIT_TEXT_SECURITY},
#line 173 "CSSPropertyNames.gperf"
      {"-webkit-column-rule-style", CSS_PROP__WEBKIT_COLUMN_RULE_STYLE},
#line 116 "CSSPropertyNames.gperf"
      {"text-line-through-width", CSS_PROP_TEXT_LINE_THROUGH_WIDTH},
#line 81 "CSSPropertyNames.gperf"
      {"outline-offset", CSS_PROP_OUTLINE_OFFSET},
#line 121 "CSSPropertyNames.gperf"
      {"text-overline-style", CSS_PROP_TEXT_OVERLINE_STYLE},
#line 57 "CSSPropertyNames.gperf"
      {"font-style", CSS_PROP_FONT_STYLE},
#line 27 "CSSPropertyNames.gperf"
      {"border-left-style", CSS_PROP_BORDER_LEFT_STYLE},
#line 159 "CSSPropertyNames.gperf"
      {"-webkit-box-flex-group", CSS_PROP__WEBKIT_BOX_FLEX_GROUP},
#line 191 "CSSPropertyNames.gperf"
      {"-webkit-marquee-style", CSS_PROP__WEBKIT_MARQUEE_STYLE},
#line 67 "CSSPropertyNames.gperf"
      {"list-style-type", CSS_PROP_LIST_STYLE_TYPE},
#line 196 "CSSPropertyNames.gperf"
      {"-webkit-text-decorations-in-effect", CSS_PROP__WEBKIT_TEXT_DECORATIONS_IN_EFFECT},
#line 86 "CSSPropertyNames.gperf"
      {"overflow-y", CSS_PROP_OVERFLOW_Y},
#line 204 "CSSPropertyNames.gperf"
      {"-webkit-user-modify", CSS_PROP__WEBKIT_USER_MODIFY},
#line 115 "CSSPropertyNames.gperf"
      {"text-line-through-style", CSS_PROP_TEXT_LINE_THROUGH_STYLE},
#line 54 "CSSPropertyNames.gperf"
      {"font-family", CSS_PROP_FONT_FAMILY}
    };

  static const short lookup[] =
    {
       -1,  -1,  -1,   0,   1,   2,  -1,  -1,  -1,  -1,
       -1,   3,  -1,  -1,  -1,   4,  -1,   5,  -1,   6,
       -1,   7,  -1,   8,  -1,   9,  -1,  10,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  11,
       -1,  -1,  -1,  -1,  -1,  12,  -1,  13,  -1,  14,
       -1,  15,  16,  -1,  -1,  -1,  17,  -1,  -1,  -1,
       -1,  18,  -1,  -1,  19,  -1,  -1,  20,  -1,  21,
       22,  23,  -1,  24,  -1,  -1,  25,  26,  27,  -1,
       -1,  -1,  -1,  -1,  -1,  28,  -1,  -1,  -1,  29,
       -1,  -1,  30,  -1,  -1,  31,  32,  33,  34,  -1,
       -1,  35,  -1,  -1,  -1,  -1,  -1,  -1,  36,  -1,
       -1,  -1,  -1,  -1,  37,  38,  -1,  -1,  -1,  39,
       -1,  40,  -1,  -1,  -1,  -1,  -1,  -1,  41,  -1,
       -1,  42,  -1,  -1,  -1,  -1,  43,  -1,  -1,  44,
       45,  46,  47,  -1,  -1,  48,  -1,  49,  -1,  50,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  51,  -1,  -1,
       52,  53,  54,  55,  -1,  -1,  56,  57,  58,  -1,
       -1,  -1,  59,  60,  -1,  -1,  61,  -1,  -1,  -1,
       62,  -1,  63,  -1,  -1,  64,  -1,  -1,  -1,  -1,
       65,  66,  67,  68,  -1,  69,  -1,  -1,  70,  -1,
       -1,  -1,  -1,  -1,  71,  72,  -1,  -1,  73,  -1,
       74,  75,  76,  77,  78,  79,  -1,  -1,  80,  81,
       -1,  82,  83,  -1,  -1,  84,  -1,  -1,  85,  -1,
       -1,  -1,  86,  87,  -1,  -1,  -1,  -1,  88,  -1,
       -1,  89,  90,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  91,  -1,  -1,  92,  -1,  93,
       94,  95,  -1,  96,  97,  98,  -1,  -1,  99, 100,
       -1, 101,  -1,  -1,  -1,  -1, 102,  -1,  -1,  -1,
       -1, 103, 104,  -1, 105,  -1, 106,  -1,  -1,  -1,
       -1, 107,  -1, 108, 109,  -1, 110,  -1,  -1, 111,
      112,  -1, 113,  -1,  -1, 114,  -1,  -1,  -1, 115,
      116,  -1,  -1,  -1,  -1, 117,  -1,  -1, 118, 119,
       -1, 120,  -1, 121,  -1,  -1, 122,  -1,  -1,  -1,
      123, 124,  -1,  -1,  -1,  -1,  -1, 125,  -1,  -1,
       -1,  -1,  -1, 126, 127,  -1,  -1,  -1,  -1,  -1,
      128,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
      129,  -1,  -1,  -1,  -1, 130,  -1, 131,  -1,  -1,
      132,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 133,  -1,
      134, 135,  -1, 136, 137, 138, 139, 140,  -1,  -1,
       -1, 141, 142,  -1,  -1,  -1,  -1, 143,  -1,  -1,
       -1,  -1,  -1,  -1, 144,  -1,  -1,  -1,  -1, 145,
       -1,  -1,  -1,  -1,  -1, 146,  -1,  -1, 147,  -1,
       -1, 148,  -1,  -1,  -1, 149,  -1,  -1,  -1,  -1,
      150,  -1, 151,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1, 152,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1, 153, 154,  -1,  -1, 155,  -1,  -1,
      156,  -1, 157,  -1,  -1,  -1, 158,  -1,  -1,  -1,
       -1, 159, 160,  -1,  -1,  -1,  -1, 161, 162,  -1,
       -1,  -1,  -1, 163, 164,  -1,  -1, 165,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1, 166,  -1,  -1,  -1,
       -1, 167,  -1,  -1,  -1, 168,  -1,  -1,  -1,  -1,
      169,  -1,  -1, 170,  -1,  -1,  -1, 171,  -1,  -1,
       -1,  -1,  -1, 172,  -1,  -1,  -1,  -1,  -1,  -1,
       -1, 173,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 174,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1, 175,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
      176,  -1,  -1, 177,  -1, 178,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1, 179,  -1, 180,  -1,  -1, 181,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
      182,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 183, 184,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 185,
      186,  -1, 187,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1, 188,  -1,  -1,  -1, 189,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1, 190,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1, 191,  -1,  -1,  -1,  -1,  -1,
      192,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1, 193,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1, 194,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
       -1, 195
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_prop (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist_prop[index].name;

              if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
                return &wordlist_prop[index];
            }
        }
    }
  return 0;
}
#line 206 "CSSPropertyNames.gperf"

static const char * const propertyList[] = {
"",
"background", 
"background-attachment", 
"background-color", 
"background-image", 
"background-position", 
"background-position-x", 
"background-position-y", 
"background-repeat", 
"border", 
"border-bottom", 
"border-bottom-color", 
"border-bottom-style", 
"border-bottom-width", 
"border-collapse", 
"border-color", 
"border-left", 
"border-left-color", 
"border-left-style", 
"border-left-width", 
"border-right", 
"border-right-color", 
"border-right-style", 
"border-right-width", 
"border-spacing", 
"border-style", 
"border-top", 
"border-top-color", 
"border-top-style", 
"border-top-width", 
"border-width", 
"bottom", 
"caption-side", 
"clear", 
"clip", 
"color", 
"content", 
"counter-increment", 
"counter-reset", 
"cursor", 
"direction", 
"display", 
"empty-cells", 
"float", 
"font", 
"font-family", 
"font-size", 
"font-stretch", 
"font-style", 
"font-variant", 
"font-weight", 
"height", 
"left", 
"letter-spacing", 
"line-height", 
"list-style", 
"list-style-image", 
"list-style-position", 
"list-style-type", 
"margin", 
"margin-bottom", 
"margin-left", 
"margin-right", 
"margin-top", 
"max-height", 
"max-width", 
"min-height", 
"min-width", 
"opacity", 
"orphans", 
"outline", 
"outline-color", 
"outline-offset", 
"outline-style", 
"outline-width", 
"overflow", 
"overflow-x", 
"overflow-y", 
"padding", 
"padding-bottom", 
"padding-left", 
"padding-right", 
"padding-top", 
"page", 
"page-break-after", 
"page-break-before", 
"page-break-inside", 
"position", 
"quotes", 
"resize", 
"right", 
"scrollbar-3dlight-color", 
"scrollbar-arrow-color", 
"scrollbar-darkshadow-color", 
"scrollbar-face-color", 
"scrollbar-highlight-color", 
"scrollbar-shadow-color", 
"scrollbar-track-color", 
"size", 
"table-layout", 
"text-align", 
"text-decoration", 
"text-indent", 
"text-line-through", 
"text-line-through-color", 
"text-line-through-mode", 
"text-line-through-style", 
"text-line-through-width", 
"text-overflow", 
"text-overline", 
"text-overline-color", 
"text-overline-mode", 
"text-overline-style", 
"text-overline-width", 
"text-shadow", 
"text-transform", 
"text-underline", 
"text-underline-color", 
"text-underline-mode", 
"text-underline-style", 
"text-underline-width", 
"top", 
"unicode-bidi", 
"vertical-align", 
"visibility", 
"white-space", 
"widows", 
"width", 
"word-break", 
"word-spacing", 
"word-wrap", 
"z-index", 
"-webkit-appearance", 
"-webkit-background-clip", 
"-webkit-background-composite", 
"-webkit-background-origin", 
"-webkit-background-size", 
"-webkit-binding", 
"-webkit-border-bottom-left-radius", 
"-webkit-border-bottom-right-radius", 
"-webkit-border-fit", 
"-webkit-border-horizontal-spacing", 
"-webkit-border-image", 
"-webkit-border-radius", 
"-webkit-border-top-left-radius", 
"-webkit-border-top-right-radius", 
"-webkit-border-vertical-spacing", 
"-webkit-box-align", 
"-webkit-box-direction", 
"-webkit-box-flex", 
"-webkit-box-flex-group", 
"-webkit-box-lines", 
"-webkit-box-ordinal-group", 
"-webkit-box-orient", 
"-webkit-box-pack", 
"-webkit-box-shadow", 
"-webkit-box-sizing", 
"-webkit-column-break-after", 
"-webkit-column-break-before", 
"-webkit-column-break-inside", 
"-webkit-column-count", 
"-webkit-column-gap", 
"-webkit-column-rule", 
"-webkit-column-rule-color", 
"-webkit-column-rule-style", 
"-webkit-column-rule-width", 
"-webkit-column-width", 
"-webkit-columns", 
"-webkit-dashboard-region", 
"-webkit-font-size-delta", 
"-webkit-highlight", 
"-webkit-line-break", 
"-webkit-line-clamp", 
"-webkit-margin-bottom-collapse", 
"-webkit-margin-collapse", 
"-webkit-margin-start", 
"-webkit-margin-top-collapse", 
"-webkit-marquee", 
"-webkit-marquee-direction", 
"-webkit-marquee-increment", 
"-webkit-marquee-repetition", 
"-webkit-marquee-speed", 
"-webkit-marquee-style", 
"-webkit-match-nearest-mail-blockquote-color", 
"-webkit-nbsp-mode", 
"-webkit-padding-start", 
"-webkit-rtl-ordering", 
"-webkit-text-decorations-in-effect", 
"-webkit-text-fill-color", 
"-webkit-text-security", 
"-webkit-text-size-adjust", 
"-webkit-text-stroke", 
"-webkit-text-stroke-color", 
"-webkit-text-stroke-width", 
"-webkit-user-drag", 
"-webkit-user-modify", 
"-webkit-user-select", 
    0
};
const char* getPropertyName(CSSPropertyID id)
{
    if (id >= numCSSProperties || id <= 0)
        return 0;
    return propertyList[id];
}
