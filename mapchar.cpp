/***************************************************************
 * Name:      mapchar.cpp
 * Purpose:   Defines Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-12-20
 * Copyright: Peter Kwan
 * License:
 *
 * Copyright (C) 2014 - 2026, Peter Kwan
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 *****************************************************************************/
#include "mapchar.h"

wchar_t MapChar(wchar_t ch, int language, int region)
{
  // All char sets have this mapping (except maybe Cyrillic G2?)
  if (ch == 0x7f)
  {
    return 0xe65f;
  }
  switch (region)
  {
  case 0: // West Europe
      switch (language)
      {
      case 0: return mapEnglish(ch);
      case 1: return mapFrench(ch);
      case 2: return mapSwedish(ch);
      case 3: return mapCzechSlovak(ch);
      case 4: return mapGerman(ch);
      case 5: return mapSpanishPortuguese(ch);
      case 6: return mapItalian(ch);
      }
  case 1: // West Europe with Polish
      switch (language)
      {
      case 0: return mapPolish(ch);
      case 1: return mapFrench(ch);
      case 2: return mapSwedish(ch);
      case 3: return mapCzechSlovak(ch);
      case 4: return mapGerman(ch);
      case 6: return mapItalian(ch);
      }
  case 2: // West Europe plus Turkish
      switch (language)
      {
      case 0: return mapEnglish(ch);
      case 1: return mapFrench(ch);
      case 2: return mapSwedish(ch);
      case 3: return mapTurkish(ch);
      case 4: return mapGerman(ch);
      case 5: return mapSpanishPortuguese(ch);
      case 6: return mapItalian(ch);
      }
  case 3: // Serbian/Croatian/Slovenian/Rumanian
      switch (language)
      {
      case 5: return mapSerbian(ch);
      case 7: return mapRumanian(ch);
      }
  case 4: // Russian/Bulgarian
      switch (language)
      {
      case 0: return mapSerbian(ch);
      case 1: return mapRussianBulgarian(ch);
      case 2: return mapEstonian(ch);
      case 3: return mapCzechSlovak(ch);
      case 4: return mapGerman(ch);
      case 5: return mapUkranian(ch);
      case 6: return mapLettishLithuanian(ch);
      }
  case 6: // Turkish/Greek
      switch (language)
      {
      case 3: return mapTurkish(ch);
      case 7: return mapGreek(ch);
      }
  case 8: // Arabic
      switch (language)
      {
      case 0: return mapEnglish(ch);
      case 1: return mapFrench(ch);
      case 7: return mapArabic(ch);
      }
  case 10: // Hebrew
      switch (language)
      {
      case 5: return mapHebrew(ch);
      case 7: return mapArabic(ch);
      }
  default:
      std::cout << "Sorry, region not implemented: " << region << std::endl;
      return ch;
  }
}

wchar_t mapEnglish(wchar_t ch)
{
  switch (ch)
  {
    // Nat. opt. 1
    case '#': return 0x00A3; // 2/3 # is mapped to pound sign
    case '[': return 0x2190; // 5/B Left arrow.
    case '\\': return 0xbd;   // 5/C Half
    // Nat. opt. 2
    case ']': return 0x2192; // 5/D Right arrow.
    case '^': return 0x2191; // 5/E Up arrow.
    case '_': return 0x0023; // 5/F Underscore is hash sign
    case '`': return 0x2014; // 6/0 Centre dash. The full width dash e731
    case '{': return 0xbc;   // 7/B Quarter
    case '|': return 0x2016; // 7/C Double pipe
    case '}': return 0xbe;   // 7/D Three quarters
    case '~': return 0x00f7; // 7/E Divide
    default:
      return ch;
  }
} // mapEnglish

wchar_t mapFrench(wchar_t ch)
{ // 0:1
  switch (ch)
  {
    // Nat. opt. 1
    case '#' : return 0x00e9; // 2/3 e acute
    case '$' : return 0x00ef; // 2/4 i umlaut
    case '@' : return 0x00e0; // 4/0 a grave
    case '[' : return 0x00eb; // 5/B e umlaut
    case '\\' : return 0x00ea; // 5/C e circumflex
    // Nat. opt. 2
    case ']' : return 0x00f9; // 5/D u grave
    case '^' : return 0x00ee; // 5/E i circumflex
    case '_' : return 0x0023; // 5/F #
    case '`' : return 0x00e8; // 6/0 e grave
    case '{' : return 0x00e2; // 7/B a circumflex
    case '|' : return 0x00f4; // 7/C o circumflex
    case '}' : return 0x00fb; // 7/D u circumflex
    case '~' : return 0x00e7; // 7/E c cedilla
    default:
      return ch;
  }
} // MapFrench

wchar_t mapSwedish (wchar_t ch) { // 0:2
  switch (ch)
  {
    // Nat. opt. 1
    case '£' : return '#'; // 2/3 hash
    case '$' : return 0x00a4; // 2/4 currency bug
    case '@' : return 0x00c9; // 4/0 E acute
    case '[' : return 0x00c4; // 5/B A umlaut
    case '\\': return 0x00d6; // 5/C O umlaut
    // Nat. opt. 2
    case ']' : return 0x00c5; // 5/D A ring
    case '^' : return 0x00dc; // 5/E U umlaut
    case '_' : return 0x005f; // 5/F Underscore (not mapped)
    case '`' : return 0x00e9; // 6/0 e acute
    case '{' : return 0x00e4; // 7/B a umlaut
    case '|' : return 0x00f6; // 7/C o umlaut
    case '}' : return 0x00e5; // 7/D a ring
    case '~' : return 0x00fc; // 7/E u umlaut
    default:
      return ch;
  }
} // MapSwedish

wchar_t mapCzechSlovak (wchar_t ch)
{ // 0:3
    switch (ch)
    {
      // Nat. opt. 1
      case '£' : return '#'; // # // 2/3 hash
      case '$' : return 0x016f; // 2/4 u ring
      case '@' : return 0x010d; // 4/0 c caron
      case '[' : return 0x0165; // 5/B t caron
      case '\\': return 0x017e;// 5/C z caron
      // Nat. opt. 2
      case ']' : return 0x00fd; // 5/D y acute
      case '^' : return 0x00ed; // 5/E i acute
      case '_' : return 0x0159; // ř // 5/F r caron
      case '`' : return 0x00e9; // 6/0 e acute
      case '{' : return 0x00e1; // 7/B a acute
      case '|' : return 0x011b; // 7/C e caron
      case '}' : return 0x00fa; // 7/D u acute
      case '~' : return 0x0161; // 7/E s caron
      default:
        return ch;
    }
  } // MapCzechSlovak

  wchar_t mapGerman (wchar_t ch)
  { // 0:4
    switch (ch)
    {
      // Nat. opt. 1
      case '£' : return '#'; // 2/3 Hash
      case '$' : return 0x0024; // 2/4 Dollar sign not mapped
      case '@' : return 0x00a7; // 4/0 Section sign
      case '[' : return 0x00c4; // 5/B A umlaut
      case '\\': return 0x00d6; // 5/C O umlaut
      // Nat. opt. 2
      case ']' : return 0x00dc; // 5/D U umlaut
      case '^' : return 0x005e; // 5/E Caret
      case '_' : return 0x005f; // 5/F Underscore (not mapped)
      case '`' : return 0x00b0; // 6/0 Masculine ordinal indicator
      case '{' : return 0x00e4; // 7/B a umlaut
      case '|' : return 0x00f6; // 7/C o umlaut
      case '}' : return 0x00fc; // 7/D u umlaut
      case '~' : return 0x00df; // 7/E SS
      default:
        return ch;
    }
  } // MapGerman

  wchar_t mapSpanishPortuguese (wchar_t ch)
  { // 0:5
    switch (ch)
    {
      // Nat. opt. 1
      case '#' : return 0x00e7; // 2/3 c cedilla
      case '£' : return '$'; // 2/4 Dollar
      case '@' : return 0x00a1; // 4/0 inverted exclamation mark
      case '[' : return 0x00e1; // 5/B a acute
      case '\\': return 0x00e9; // 5/C e acute
      // Nat. opt. 2
      case ']' : return 0x00ed; // 5/D i acute
      case '^' : return 0x00f3; // 5/E o acute
      case '_' : return 0x00fa; // 5/F u acute
      case '`' : return 0x00bf; // 6/0 Inverted question mark
      case '{' : return 0x00fc; // 7/B u umlaut
      case '|' : return 0x00f1; // 7/C n tilde
      case '}' : return 0x00e8; // 7/D e grave
      case '~' : return 0x00e0; // 7/E a grave
      default:
        return ch;
    }
  } // MapSpanishPortuguese

  wchar_t mapItalian(wchar_t ch)
  { // 0:6
    switch (ch)
    {
      // Nat. opt. 1
      case '#' : return 0x00a3; // 2/3 Pound
      case '£' : return '$'; // 2/4 Dollar
      case '@' : return 0x00e9; // 4/0 e acute
      case '[' : return 0x00b0; // 5/B ring
      case '\\': return 0x00e7; // 5/C c cedilla
      // Nat. opt. 2
      case ']' : return 0x2192; // 5/D right arrow
      case '^' : return 0x2191; // 5/E up arrow
      case '_' : return 0x0023; // 5/F #
      case '`' : return 0x00f9; // 6/0 u grave
      case '{' : return 0x00e0; // 7/B a grave
      case '|' : return 0x00f2; // 7/C o grave
      case '}' : return 0x00e8; // 7/D e grave
      case '~' : return 0x00ec; // 7/E i grave
      default:
        return ch;
    }
  } // MapItalian

  wchar_t mapPolish (wchar_t ch)
  { // 1:0
    switch (ch)
    {
      case '#' : return 0x0023; // 2/3 # is not mapped
      case '$' : return 0x0144; // 2/4
      case '@' : return 0x0105; // 4/0
      case '[' : return 0x01b5; // 5/B
      case '\\': return 0x015a; // 5/C
      case ']' : return 0x0141; // 5/D
      case '^' : return 0x0107; // 5/E
      case '_' : return 0x00f3; // 5/F
      case '`' : return 0x0119; // 6/0
      case '{' : return 0x017c; // 7/B
      case '|' : return 0x015b; // 7/C
      case '}' : return 0x0142; // 7/D
      case '~' : return 0x017a; // 7/E
      default:
        return ch;
    }
  } // MapPolish

  wchar_t mapTurkish (wchar_t ch)
  { // 2:3
    switch (ch)
    {
      case '#' : return 0x0167; // 2/3
      case '$' : return 0x011f; // 2/4
      case '@' : return 0x0130; // 4/0
      case '[' : return 0x015e; // 5/B
      case '\\': return 0x00d6; // 5/C
      case ']' : return 0x00c7; // 5/D
      case '^' : return 0x00dc; // 5/E
      case '_' : return 0x011e; // 5/F
      case '`' : return 0x0131; // 6/0
      case '{' : return 0x015f; // 7/B
      case '|' : return 0x00f6; // 7/C
      case '}' : return 0x00e7; // 7/D
      case '~' : return 0x00fc; // 7/E
      default:
        return ch;
    }
  } // mapTurkish

  wchar_t mapSerbian(wchar_t ch)
  { // 3:5
    switch (ch)
    {
      case '#' : return 0x0023; // 2/3
      case '$' : return 0x00cb; // 2/4
      case '@' : return 0x010c; // 4/0
      case '[' : return 0x0106; // 5/B
      case '\\': return 0x017d; // 5/C
      case ']' : return 0x0110; // 5/D
      case '^' : return 0x0160; // 5/E
      case '_' : return 0x00eb; // 5/F
      case '`' : return 0x010d; // 6/0
      case '{' : return 0x0107; // 7/B
      case '|' : return 0x017e; // 7/C
      case '}' : return 0x0111; // 7/D
      case '~' : return 0x0161; // 7/E
      default:
        return ch;
    }
  } // mapSerbian

  wchar_t mapRumanian (wchar_t ch)
  { // 3:7
    switch (ch)
    {
      case '#' : return 0x0023; // 2/3
      case '$' : return 0x00a4; // 2/4
      case '@' : return 0x0162; // 4/0
      case '[' : return 0x00c2; // 5/B
      case '\\': return 0x015e; // 5/C
      case ']' : return 0x0102; // 5/D
      case '^' : return 0x00ce; // 5/E
      case '_' : return 0x0131; // 5/F
      case '`' : return 0x0163; // 6/0
      case '{' : return 0x00e2; // 7/B
      case '|' : return 0x015f; // 7/C
      case '}' : return 0x0103; // 7/D
      case '~' : return 0x00ee; // 7/E
      default:
        return ch;
    }
  } // mapRumanian

  wchar_t mapRussianBulgarian(wchar_t ch)
  { // 4:0
    switch (ch)
    {
      // Column 20-2f
      case '&' : return 0x044B; // ы
      // Nat. opt. 2. Column 40-4f
      case '@' : return 0x042e; // Cyrillic Capital Letter Yu
      case 'A' : return 0x0410; // Cyrillic A
      case 'B' : return 0x0411;
      case 'C' : return 0x0426; // Cyrillic
      case 'D' : return 0x0414; //
      case 'E' : return 0x0415;
      case 'F' : return 0x0424;
      case 'G' : return 0x0413; //
      case 'H' : return 0x0425; //
      case 'I' : return 0x0418; // И
      case 'J' : return 0x0419; // Й
      case 'K' : return 0x041A; // К
      case 'L' : return 0x041B; // Л
      case 'M' : return 0x041C; // М
      case 'N' : return 0x041D; // Н
      case 'O' : return 0x041E; // О
      // Cyrillic G0 Column 50-5f
      case 'P' : return 0x041f; // П
      case 'Q' : return 0x042f;
      case 'R' : return 0x0420;
      case 'S' : return 0x0421;
      case 'T' : return 0x0422;
      case 'U' : return 0x0423;
      case 'V' : return 0x0416;
      case 'W' : return 0x0412;
      case 'X' : return 0x042c;
      case 'Y' : return 0x042a;
      case 'Z' : return 0x0417;
      case '[' : return 0x0428; // Nap opt 2 starts here
      case '\\': return 0x042d;
      case ']' : return 0x0429;
      case '^' : return 0x0427;
      case '_' : return 0x042b;
      // Cyrillic G0 Column 60-6f
      case '`' : return 0x044e; // Nat opt 2 stops here
      case 'a' : return 0x0430; // а
      case 'b' : return 0x0431; // б
      case 'c' : return 0x0446;
      case 'd' : return 0x0434;
      case 'e' : return 0x0435;
      case 'f' : return 0x0444;
      case 'g' : return 0x0433;
      case 'h' : return 0x0445;
      case 'i' : return 0x0438;
      case 'j' : return 0x0439;
      case 'k' : return 0x043a; // к
      case 'l' : return 0x043b; // л
      case 'm' : return 0x043c; // м
      case 'n' : return 0x043d; // н
      case 'o' : return 0x043e; // о
      // Remaining are OK
      // Cyrillic G0 Column 70-7f
      // 70 is OK
      case 'p' : return 0x043f; // п
      case 'q' : return 0x044f; //
      case 'r' : return 0x0440; // р
      case 's' : return 0x0441;
      case 't' : return 0x0442;
      case 'u' : return 0x0443;
      case 'v' : return 0x0436;
      case 'w' : return 0x0432;
      case 'x' : return 0x044c;
      case 'y' : return 0x044a;
      case 'z' : return 0x0437;
      case '{' : return 0x0448;
      case '|' : return 0x044d;
      case '}' : return 0x0449;
      case '~' : return 0x0447;
      default:
        // Other mappings that just happen to be in the right place
        if ((ch >= '@') && (ch <= '~')) {
          ch = ch + (0x040f) - '@'; // [!] probably need to do some char<-->ascii conversions
        }
        return ch;
    }
  } // mapRussianBulgarian

  wchar_t mapEstonian(wchar_t ch)
  { // 4:2 Latin G0 Set - Option 2 Estonian
    switch (ch)
    {
      case '$' : return 0x00f5; // õ
      case '@' : return 0x0160; // Š
      case '[' : return 0x00c4; // Ä
      case '\\' : return 0x00d6; // Ö
      case ']' : return 0x017d; // Ž
      case '^' : return 0x00dc; // Ü
      case '_' : return 0x00d5; // Õ
      case '{' : return 0x00e4; // ä
      case '|' : return 0x00f6; // ö
      case '}' : return 0x017e; // ž
      case '~' : return 0x00fc; // ü
      default:
        return ch;
    }
  } // mapEstonian

  wchar_t mapUkranian(wchar_t ch)
  { // 4:5
    switch (ch)
    {
      // Nat. opt. 2. Column 40-4f
      case '@' : return 0x042e; // Ю Cyrillic Capital Letter Yu
      case 'A' : return 0x0410; // А
      case 'B' : return 0x0411; // Б
      case 'C' : return 0x0426; // Cyrillic
      case 'D' : return 0x0414; //
      case 'E' : return 0x0415;
      case 'F' : return 0x0424;
      case 'G' : return 0x0413; //
      case 'H' : return 0x0425; //
      case 'I' : return 0x0418; // И
      case 'J' : return 0x0419; // Й
      case 'K' : return 0x041a; // К
      case 'L' : return 0x041b; // Л
      case 'M' : return 0x041c; // М
      case 'N' : return 0x041d; // Н
      case 'O' : return 0x041e; // О

      // Cyrillic G0 Column 50-5f
      case 'P' : return 0x041f; // П
      case 'Q' : return 0x042f; // 5/1
      case 'R' : return 0x0420; // 5/2
      case 'S' : return 0x0421;
      case 'T' : return 0x0422;
      case 'U' : return 0x0423;
      case 'V' : return 0x0416;
      case 'W' : return 0x0412;
      case 'X' : return 0x042c;
      case 'Y' : return 0x0406; // 5/8 042a russian
      case 'Z' : return 0x0417; // 5/9
      case '[' : return 0x0428; // Nap opt 2 starts here
      case '\\': return 0x0404; // 5/c Russian 042d
      case ']' : return 0x0429; // 5/d
      case '^' : return 0x0427; // 5/e
      case '_' : return 0x0407; // 5/f russian 042b
      // Cyrillic G0 Column 60-6f
      case '`' : return 0x044e; // 6/0
      case 'a' : return 0x0430; // а 6/1
      case 'b' : return 0x0431; // б
      case 'c' : return 0x0446;
      case 'd' : return 0x0434;
      case 'e' : return 0x0435;
      case 'f' : return 0x0444;
      case 'g' : return 0x0433;
      case 'h' : return 0x0445;
      case 'i' : return 0x0438;
      case 'j' : return 0x0439;

      case 'k' : return 0x043a; // к
      case 'l' : return 0x043b; // л
      case 'm' : return 0x043c; // м
      case 'n' : return 0x043d; // н
      case 'o' : return 0x043e; // о
      // Cyrillic G0 Column 70-7f
      case 'p' : return 0x043f; // п 7/0
      case 'q' : return 0x044f; // 7/1
      case 'r' : return 0x0440; // 7/2
      case 's' : return 0x0441; // 7/3
      case 't' : return 0x0442; // 7/4
      case 'u' : return 0x0443; // 7/5
      case 'v' : return 0x0436; // 7/6
      case 'w' : return 0x0432; // 7/7
      case 'x' : return 0x044c; // 7/8
      case 'y' : return 0x0456; // 7/9 russian 044a
      case 'z' : return 0x0437; // 7/a
      case '{' : return 0x0448; // 7/b
      case '|' : return 0x0454; // 7/c russian 044d
      case '}' : return 0x0449; // 7/d
      case '~' : return 0x0447; // 7/e russian 0447
      default:
        return ch;
    }
  } // mapUkrainian

  wchar_t mapLettishLithuanian(wchar_t ch)
  { // 4:6
    switch (ch)
    {
      case '#' : return 0x0023; // 2/3
      case '$' : return 0x0024; // 2/4
      case '@' : return 0x0160; // 4/0
      case '[' : return 0x0117; // 5/B
      case '\\': return 0x0229; // 5/C
      case ']' : return 0x017d; // 5/D
      case '^' : return 0x010d; // 5/E
      case '_' : return 0x016b; // 5/F
      case '`' : return 0x0161; // 6/0
      case '{' : return 0x0105; // 7/B
      case '|' : return 0x0173; // 7/C
      case '}' : return 0x017e; // 7/D
      case '~' : return 0x012f; // 7/E This is the best match in teletext2
      default:
        return ch;
    }
  } // mapLettish

  wchar_t mapGreek (wchar_t ch)
  { // 6:7
    switch (ch)
    {
      case 'R' : return 0x0374; // Top right dot thingy
      case '<' : return 0x00ab; // left chevron
      case '>' : return 0x00bb; // right chevron
      default:
        // Most mappings are direct
        if ((ch >= '@') && (ch <= '~'))
        {
          const wchar_t p1 = ch;
          const wchar_t p2 = 0x390;
          const wchar_t p3 = '@';
          const wchar_t p4 = p1 + p2 - p3;
          const wchar_t ch2 = p4;
          return ch2;
        }
        return ch;
    }
  } // mapGreek

  wchar_t mapArabic(wchar_t ch)
  { // 8:7
    switch (ch)
    {
      case ' ': // 2/0
      case '!': // 2/1
      case '"': // 2/2
      case '$': // 2/4
      case '%': // 2/5
      case ')': // 2/8
      case '(': // 2/9
      case '*': // 2/A
      case '+': // 2/B
      case '-': // 2/D
      case '.': // 2/E
      case '/': // 2/F
      case '0': // 3/0
      case '1': // 3/1
      case '2': // 3/2
      case '3': // 3/3
      case '4': // 3/4
      case '5': // 3/5
      case '6': // 3/6
      case '7': // 3/7
      case '8': // 3/8
      case '9': // 3/9
      case ':': // 3/a
      // case '0':) // 3/b
        return ch;
      case '#': return '£'; // 2/3
      case '>':
        return '<'; // 3/c
      case '=': // 3/d
        return ch;
      case '<':
        return '>'; // 3/e
      // case '?':) // 3/f
      default :
        return ch + 0xe606 - '&'; // 2/6 onwards
    }
  } // mapArabic

  wchar_t mapHebrew(wchar_t ch)
  { // 10:5
    if ((ch > 0x5f) && (ch < 0x7b))
    { // Hebrew characters
      return ch + 0x05d0 - 0x60; //
    }
    switch (ch)
    { // Mostly the same as English nat. opts.
      case '#': return 0x00A3; // 2/3 # is mapped to pound sign
      case '[': return 0x2190; // 5/B Left arrow.
      case '\\': return 0xbd; // 5/C Half
      case ']': return 0x2192; // 5/D Right arrow.
      case '^': return 0x2191; // 5/E Up arrow.
      case '_': return 0x0023; // 5/F Underscore is hash sign
      case '{': return 0x20aa; // 7/B sheqel
      case '|': return 0x2016; // 7/C Double pipe
      case '}': return 0xbe; // 7/D Three quarters
      case '~': return 0x00f7; // 7/E Divide
      default:
        return ch;
    }
  } // mapHebrew


