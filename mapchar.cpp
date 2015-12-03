/***************************************************************
 * Name:      mapchar.cpp
 * Purpose:   Defines Application Frame
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2014-12-20
 * Copyright: Peter Kwan (http://www.teastop.co.uk)
 * License:
 *
 * Copyright (C) 2014, Peter Kwan
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
    switch (region)
    {
    case 0:
        return mapRegion0(ch,language);
    case 1:
        return mapRegion1(ch,language);
    case 2:
        return mapRegion2(ch,language);
    case 3:
        return mapRegion3(ch,language);
    case 4:
        return mapRegion4(ch,language);
    case 6:
        return mapRegion6(ch,language);
    case 8:
        return mapRegion8(ch,language);
    case 10:
        return mapRegion10(ch,language);
    default:
        std::cout << "Sorry, region not implemented: " << region << std::endl;
        return '?';
    }
}

wchar_t mapRegion0(wchar_t ch, int language)
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
    case 0 : // English
        // std::cout << "trace2" << std::endl;

        // Nat. opt. 1
        if (ch=='#')  ch=0x00A3; // 2/3 # is mapped to pound sign
        //if (ch=='$')  ch=0x0024; // 2/4 Dollar sign (no change!)
        //if (ch=='@')  ch=0x0040; // 4/0 No change
        if (ch=='[')  ch=0x2190; // 5/B Left arrow.
        if (ch=='\\') ch=0xbd;   // 5/C Half
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D Right arrow.
        if (ch=='^')  ch=0x2191; // 5/E Up arrow.
        if (ch=='_')  ch=0x0023; // 5/F Underscore is hash sign
        if (ch=='`')  ch=0x2014; // 6/0 Centre dash. The full width dash e731
        if (ch=='{')  ch=0xbc;   // 7/B Quarter
        if (ch=='|')  ch=0x2016; // 7/C Double pipe
        if (ch=='}')  ch=0xbe;   // 7/D Three quarters
        if (ch=='~')  ch=0x00f7; // 7/E Divide
        // std::cout << "trace3" << std::endl;
        break;
    case 1 : // French
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e9; // 2/3 e acute
        if (ch=='$')  ch=0x00ef; // 2/4 i umlaut
        if (ch=='@')  ch=0x00e0; // 4/0 a grave
        if (ch=='[')  ch=0x00eb; // 5/B e umlaut
        if (ch=='\\') ch=0x00ea; // 5/C e circumflex
        // Nat. opt. 2
        if (ch==']')  ch=0x00f9; // 5/D u grave
        if (ch=='^')  ch=0x00ee; // 5/E i circumflex
        if (ch=='_')  ch='#';    // 5/F #
        if (ch=='`')  ch=0x00e8; // 6/0 e grave
        if (ch=='{')  ch=0x00e2; // 7/B a circumflex
        if (ch=='|')  ch=0x00f4; // 7/C o circumflex
        if (ch=='}')  ch=0x00fb; // 7/D u circumflex
        if (ch=='~')  ch=0x00e7; // 7/E c cedilla
        break;
    case 2 : // Swedish
        // Nat. opt. 1
        if (ch=='#')  ch='#'; // 2/3 hash
        if (ch=='$')  ch=0x00a4; // 2/4 currency bug
        if (ch=='@')  ch=0x00c9; // 4/0 E acute
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d4; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00c5; // 5/D A ring
        if (ch=='^')  ch=0x00dc; // 5/E U umlaut
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00d6; // 7/C o umlaut
        if (ch=='}')  ch=0x00e5; // 7/D a ring
        if (ch=='~')  ch=0x00fc; // 7/E u umlaut
        break;
    case 3 : // Czech/Slovak
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 hash
        if (ch=='$')  ch=0x016f; // 2/4 u ring
        if (ch=='@')  ch=0x010d; // 4/0 c caron
        if (ch=='[')  ch=0x0165; // 5/B t caron
        if (ch=='\\') ch=0x017e; // 5/C z caron
        // Nat. opt. 2
        if (ch==']')  ch=0x00fd; // 5/D y acute
        if (ch=='^')  ch=0x00ed; // 5/E i acute
        if (ch=='_')  ch=0x0159; // 5/F r caron
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e1; // 7/B a acute
        if (ch=='|')  ch=0x011b; // 7/C e caron
        if (ch=='}')  ch=0x00fa; // 7/D u acute
        if (ch=='~')  ch=0x0161; // 7/E s caron
        break;
    case 4 : // German
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 # is not mapped
        if (ch=='$')  ch=0x0024; // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a7; // 4/0 Section sign
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d6; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00dc; // 5/D U umlaut
        if (ch=='^')  ch='^';    // 5/E Caret (not mapped)
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00b0; // 6/0 Masculine ordinal indicator
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00f6; // 7/C o umlaut
        if (ch=='}')  ch=0x00fc; // 7/D u umlaut
        if (ch=='~')  ch=0x00df; // 7/E SS
        break;
    case 5 : // Spanish/Portuguese
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e7; // 2/3 c cedilla
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a1; // 4/0 inverted exclamation mark
        if (ch=='[')  ch=0x00e1; // 5/B a acute
        if (ch=='\\') ch=0x00e9; // 5/C e acute
        // Nat. opt. 2
        if (ch==']')  ch=0x00ed; // 5/D i acute
        if (ch=='^')  ch=0x00f3; // 5/E o acute
        if (ch=='_')  ch=0x00fa; // 5/F u acute
        if (ch=='`')  ch=0x00bf; // 6/0 Inverted question mark
        if (ch=='{')  ch=0x00fc; // 7/B u umlaut
        if (ch=='|')  ch=0x00f1; // 7/C n tilde
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00e0; // 7/E a grave
        break;
    case 6 : // Italian
        // Nat. opt. 1
        if (ch=='#')  ch=0x00a3; // 2/3 Pound
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00e9; // 4/0 e acute
        if (ch=='[')  ch=0x00b0; // 5/B ring
        if (ch=='\\') ch=0x00e7; // 5/C c cedilla
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D right arrow
        if (ch=='^')  ch=0x2191; // 5/E up arrow
        if (ch=='_')  ch='#';    // 5/F hash
        if (ch=='`')  ch=0x00f9; // 6/0 u grave
        if (ch=='{')  ch=0x00e0; // 7/B a grave
        if (ch=='|')  ch=0x00f2; // 7/C o grave
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00ec; // 7/E i grave
        break;
    default:
        //std::cout << "Language not implemented yet: " << m_rootPage->GetLanguage() << std::endl;
        ;
    }
    // More language mappings including Greek
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
}


wchar_t mapRegion1(wchar_t ch, int language) // West Europe plus Polish
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
    case 0 : // Polish
        // std::cout << "trace2" << std::endl;

        // Nat. opt. 1
        if (ch=='#')  ch=0x0023; // 2/3 # is not mapped
        if (ch=='$')  ch=0x0144; // 2/4
        if (ch=='@')  ch=0x0105; // 4/0
        if (ch=='[')  ch=0x01b5; // 5/B
        if (ch=='\\') ch=0x015a; // 5/C
        if (ch==']')  ch=0x0141; // 5/D
        if (ch=='^')  ch=0x0107; // 5/E
        if (ch=='_')  ch=0x00f3; // 5/F
        if (ch=='`')  ch=0x0119; // 6/0
        if (ch=='{')  ch=0x017c; // 7/B
        if (ch=='|')  ch=0x015b; // 7/C
        if (ch=='}')  ch=0x0142; // 7/D
        if (ch=='~')  ch=0x017a; // 7/E
        // std::cout << "trace3" << std::endl;
        break;
    case 1 : // French
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e9; // 2/3 e acute
        if (ch=='$')  ch=0x00ef; // 2/4 i umlaut
        if (ch=='@')  ch=0x00e0; // 4/0 a grave
        if (ch=='[')  ch=0x00eb; // 5/B e umlaut
        if (ch=='\\') ch=0x00ea; // 5/C e circumflex
        // Nat. opt. 2
        if (ch==']')  ch=0x00f9; // 5/D u grave
        if (ch=='^')  ch=0x00ee; // 5/E i circumflex
        if (ch=='_')  ch='#';    // 5/F #
        if (ch=='`')  ch=0x00e8; // 6/0 e grave
        if (ch=='{')  ch=0x00e2; // 7/B a circumflex
        if (ch=='|')  ch=0x00f4; // 7/C o circumflex
        if (ch=='}')  ch=0x00fb; // 7/D u circumflex
        if (ch=='~')  ch=0x00e7; // 7/E c cedilla
        break;
    case 2 : // Swedish
        // Nat. opt. 1
        if (ch=='#')  ch='#'; // 2/3 hash
        if (ch=='$')  ch=0x00a4; // 2/4 currency bug
        if (ch=='@')  ch=0x00c9; // 4/0 E acute
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d4; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00c5; // 5/D A ring
        if (ch=='^')  ch=0x00dc; // 5/E U umlaut
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00d6; // 7/C o umlaut
        if (ch=='}')  ch=0x00e5; // 7/D a ring
        if (ch=='~')  ch=0x00fc; // 7/E u umlaut
        break;
    case 3 : // Czech/Slovak
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 hash
        if (ch=='$')  ch=0x016f; // 2/4 u ring
        if (ch=='@')  ch=0x010d; // 4/0 c caron
        if (ch=='[')  ch=0x0165; // 5/B t caron
        if (ch=='\\') ch=0x017e; // 5/C z caron
        // Nat. opt. 2
        if (ch==']')  ch=0x00fd; // 5/D y acute
        if (ch=='^')  ch=0x00ed; // 5/E i acute
        if (ch=='_')  ch=0x0159; // 5/F r caron
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e1; // 7/B a acute
        if (ch=='|')  ch=0x011b; // 7/C e caron
        if (ch=='}')  ch=0x00fa; // 7/D u acute
        if (ch=='~')  ch=0x0161; // 7/E s caron
        break;
    case 4 : // German
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 # is not mapped
        if (ch=='$')  ch=0x0024; // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a7; // 4/0 Section sign
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d6; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00dc; // 5/D U umlaut
        if (ch=='^')  ch='^';    // 5/E Caret (not mapped)
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00b0; // 6/0 Masculine ordinal indicator
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00f6; // 7/C o umlaut
        if (ch=='}')  ch=0x00fc; // 7/D u umlaut
        if (ch=='~')  ch=0x00df; // 7/E SS
        break;
    // 5 is not used in region 0
    case 6 : // Italian
        // Nat. opt. 1
        if (ch=='#')  ch=0x00a3; // 2/3 Pound
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00e9; // 4/0 e acute
        if (ch=='[')  ch=0x00b0; // 5/B ring
        if (ch=='\\') ch=0x00e7; // 5/C c cedilla
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D right arrow
        if (ch=='^')  ch=0x2191; // 5/E up arrow
        if (ch=='_')  ch='#';    // 5/F hash
        if (ch=='`')  ch=0x00f9; // 6/0 u grave
        if (ch=='{')  ch=0x00e0; // 7/B a grave
        if (ch=='|')  ch=0x00f2; // 7/C o grave
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00ec; // 7/E i grave
        break;
    default:
        //std::cout << "Language not implemented yet: " << m_rootPage->GetLanguage() << std::endl;
        ;
    }
    // More language mappings including Greek
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
} // region 1

wchar_t mapRegion2(wchar_t ch, int language) // West Europe plus Turkish
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
    case 0 : // English
        // std::cout << "trace2" << std::endl;

        // Nat. opt. 2
        if (ch=='#')  ch=0x00A3; // 2/3 # is mapped to pound sign
        //if (ch=='$')  ch=0x0024; // 2/4 Dollar sign (no change!)
        //if (ch=='@')  ch=0x0040; // 4/0 No change
        if (ch=='[')  ch=0x2190; // 5/B Left arrow.
        if (ch=='\\') ch=0xbd;   // 5/C Half
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D Right arrow.
        if (ch=='^')  ch=0x2191; // 5/E Up arrow.
        if (ch=='_')  ch=0x0023; // 5/F Underscore is hash sign
        if (ch=='`')  ch=0x2014; // 6/0 Centre dash. The full width dash e731
        if (ch=='{')  ch=0xbc;   // 7/B Quarter
        if (ch=='|')  ch=0x2016; // 7/C Double pipe
        if (ch=='}')  ch=0xbe;   // 7/D Three quarters
        if (ch=='~')  ch=0x00f7; // 7/E Divide
        // std::cout << "trace3" << std::endl;
        break;
    case 1 : // French
        // Nat. opt
        if (ch=='#')  ch=0x00e9; // 2/3 e acute
        if (ch=='$')  ch=0x00ef; // 2/4 i umlaut
        if (ch=='@')  ch=0x00e0; // 4/0 a grave
        if (ch=='[')  ch=0x00eb; // 5/B e umlaut
        if (ch=='\\') ch=0x00ea; // 5/C e circumflex
        // Nat. opt. 2
        if (ch==']')  ch=0x00f9; // 5/D u grave
        if (ch=='^')  ch=0x00ee; // 5/E i circumflex
        if (ch=='_')  ch='#';    // 5/F #
        if (ch=='`')  ch=0x00e8; // 6/0 e grave
        if (ch=='{')  ch=0x00e2; // 7/B a circumflex
        if (ch=='|')  ch=0x00f4; // 7/C o circumflex
        if (ch=='}')  ch=0x00fb; // 7/D u circumflex
        if (ch=='~')  ch=0x00e7; // 7/E c cedilla
        break;
    case 2 : // Swedish
        // Nat. opt. 2
        if (ch=='#')  ch='#'; // 2/3 hash
        if (ch=='$')  ch=0x00a4; // 2/4 currency bug
        if (ch=='@')  ch=0x00c9; // 4/0 E acute
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d6; // 5/C O umlaut (was d4)
        // Nat. opt. 2
        if (ch==']')  ch=0x00c5; // 5/D A ring
        if (ch=='^')  ch=0x00dc; // 5/E U umlaut
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00d6; // 7/C o umlaut
        if (ch=='}')  ch=0x00e5; // 7/D a ring
        if (ch=='~')  ch=0x00fc; // 7/E u umlaut
        break;
    case 3 : // Turkish
        // Nat. opt
        if (ch=='#')  ch=0x0167; // 2/3
        if (ch=='$')  ch=0x011f; // 2/4
        if (ch=='@')  ch=0x0130; // 4/0
        if (ch=='[')  ch=0x015e; // 5/B
        if (ch=='\\') ch=0x00d6; // 5/C
        if (ch==']')  ch=0x00c7; // 5/D
        if (ch=='^')  ch=0x00dc; // 5/E
        if (ch=='_')  ch=0x011e; // 5/F
        if (ch=='`')  ch=0x0131; // 6/0
        if (ch=='{')  ch=0x015f; // 7/B
        if (ch=='|')  ch=0x00f6; // 7/C
        if (ch=='}')  ch=0x00e7; // 7/D
        if (ch=='~')  ch=0x00fc; // 7/E
        break;

    case 4 : // German
        // Nat. opt. 2
        if (ch=='#')  ch='#';    // 2/3 # is not mapped
        if (ch=='$')  ch=0x0024; // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a7; // 4/0 Section sign
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d6; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00dc; // 5/D U umlaut
        if (ch=='^')  ch='^';    // 5/E Caret (not mapped)
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00b0; // 6/0 Masculine ordinal indicator
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00f6; // 7/C o umlaut
        if (ch=='}')  ch=0x00fc; // 7/D u umlaut
        if (ch=='~')  ch=0x00df; // 7/E SS
        break;
    case 5 : // Spanish/Portuguese
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e7; // 2/3 c cedilla
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a1; // 4/0 inverted exclamation mark
        if (ch=='[')  ch=0x00e1; // 5/B a acute
        if (ch=='\\') ch=0x00e9; // 5/C e acute
        // Nat. opt. 2
        if (ch==']')  ch=0x00ed; // 5/D i acute
        if (ch=='^')  ch=0x00f3; // 5/E o acute
        if (ch=='_')  ch=0x00fa; // 5/F u acute
        if (ch=='`')  ch=0x00bf; // 6/0 Inverted question mark
        if (ch=='{')  ch=0x00fc; // 7/B u umlaut
        if (ch=='|')  ch=0x00f1; // 7/C n tilde
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00e0; // 7/E a grave
        break;
    case 6 : // Italian
        // Nat. opt. 2
        if (ch=='#')  ch=0x00a3; // 2/3 Pound
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00e9; // 4/0 e acute
        if (ch=='[')  ch=0x00b0; // 5/B ring
        if (ch=='\\') ch=0x00e7; // 5/C c cedilla
        if (ch==']')  ch=0x2192; // 5/D right arrow
        if (ch=='^')  ch=0x2191; // 5/E up arrow
        if (ch=='_')  ch='#';    // 5/F hash
        if (ch=='`')  ch=0x00f9; // 6/0 u grave
        if (ch=='{')  ch=0x00e0; // 7/B a grave
        if (ch=='|')  ch=0x00f2; // 7/C o grave
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00ec; // 7/E i grave
        break;
    // 7 is not used
    default:
        //std::cout << "Language not implemented yet: " << m_rootPage->GetLanguage() << std::endl;
        ;
    }
    // More language mappings including Greek
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    return ch;
} // region 2

wchar_t mapRegion3(wchar_t ch, int language) // Serbian/Croatian/Slovenian/Rumanian
{
    ch&=0x7f;
    switch (language)
    {
       case 5 : // Latin G0 Set - Option 2 Serbian/Croatian/Slovenian
        // Nat. opt
        if (ch=='#')  ch=0x0023; // 2/3
        if (ch=='$')  ch=0x00cb; // 2/4
        if (ch=='@')  ch=0x010c; // 4/0
        if (ch=='[')  ch=0x0106; // 5/B
        if (ch=='\\') ch=0x017d; // 5/C
        if (ch==']')  ch=0x0110; // 5/D
        if (ch=='^')  ch=0x0160; // 5/E
        if (ch=='_')  ch=0x00eb; // 5/F
        if (ch=='`')  ch=0x010d; // 6/0
        if (ch=='{')  ch=0x0107; // 7/B
        if (ch=='|')  ch=0x017e; // 7/C
        if (ch=='}')  ch=0x0111; // 7/D
        if (ch=='~')  ch=0x0161; // 7/E
        break;

    case 7 : // Rumanian
        // Nat. opt
        if (ch=='#')  ch=0x0023; // 2/3
        if (ch=='$')  ch=0x00a4; // 2/4
        if (ch=='@')  ch=0x0162; // 4/0
        if (ch=='[')  ch=0x00c2; // 5/B
        if (ch=='\\') ch=0x015e; // 5/C
        if (ch==']')  ch=0x0102; // 5/D
        if (ch=='^')  ch=0x00ce; // 5/E
        if (ch=='_')  ch=0x0131; // 5/F
        if (ch=='`')  ch=0x0163; // 6/0
        if (ch=='{')  ch=0x00e2; // 7/B
        if (ch=='|')  ch=0x015f; // 7/C
        if (ch=='}')  ch=0x0103; // 7/D
        if (ch=='~')  ch=0x00ee; // 7/E
        break;
    default:
        return '?';
    }
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
} // mapRegion3


wchar_t mapRegion4(wchar_t ch, int language) // Rus/Bul
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
       case 0 : // Latin G0 Set - Option 2 Serbian/Croatian/Slovenian
        // Nat. opt
        if (ch=='#')  ch=0x0023; // 2/3
        if (ch=='$')  ch=0x00cb; // 2/4
        if (ch=='@')  ch=0x010c; // 4/0
        if (ch=='[')  ch=0x0106; // 5/B
        if (ch=='\\') ch=0x017d; // 5/C
        if (ch==']')  ch=0x0110; // 5/D
        if (ch=='^')  ch=0x0160; // 5/E
        if (ch=='_')  ch=0x00eb; // 5/F
        if (ch=='`')  ch=0x010d; // 6/0
        if (ch=='{')  ch=0x0107; // 7/B
        if (ch=='|')  ch=0x017e; // 7/C
        if (ch=='}')  ch=0x0111; // 7/D
        if (ch=='~')  ch=0x0161; // 7/E
        break;
       case 1 : // Cyrillic G0 Set - Option 2 Russian/Bulgarian
        // Sadly, much of this needs fixing up
        // Nat. opt. 2. Column 40-4f
        if (ch=='@')  ch=0x042e;    // Cyrillic Capital Letter Yu
        if (ch=='C')  ch=0x0426; // Cyrillic
        if (ch=='D')  ch=0x0414; //
        if (ch=='E')  ch=0x0415;
        if (ch=='F')  ch=0x0424;
        if (ch=='G')  ch=0x0413; //
        if (ch=='H')  ch=0x0425; //
        // Cyrillic G0 Column 50-5f
        if (ch=='Q')  ch=0x042f;
        if (ch=='R')  ch=0x0420;
        if (ch=='S')  ch=0x0421;
        if (ch=='T')  ch=0x0422;
        if (ch=='U')  ch=0x0423;
        if (ch=='V')  ch=0x0416;
        if (ch=='W')  ch=0x0412;
        if (ch=='X')  ch=0x042c;
        if (ch=='Y')  ch=0x042a;
        if (ch=='Z')  ch=0x0417;
        if (ch=='[')  ch=0x0428; // Nap opt 2 starts here
        if (ch=='\\') ch=0x042d;
        if (ch==']')  ch=0x0429;
        if (ch=='^')  ch=0x0427;
        if (ch=='_')  ch=0x042b;
        // Cyrillic G0 Column 60-6f
        if (ch=='`')  ch=0x044e; // Nat opt 2 stops here
        // if (ch=='a')  ch=0x0430;
        // if (ch=='b')  ch=0x0431;
        if (ch=='c')  ch=0x0446;
        if (ch=='d')  ch=0x0434;
        if (ch=='e')  ch=0x0435;
        if (ch=='f')  ch=0x0444;
        if (ch=='g')  ch=0x0433;
        if (ch=='h')  ch=0x0445;
        if (ch=='i')  ch=0x0438;
        if (ch=='j')  ch=0x0439;
        // Remaining are OK
        // Cyrillic G0 Column 70-7f
        // 70 is OK
        if (ch=='q')  ch=0x044f;
        if (ch=='r')  ch=0x0440;
        if (ch=='s')  ch=0x0441;
        if (ch=='t')  ch=0x0442;
        if (ch=='u')  ch=0x0443;
        if (ch=='v')  ch=0x0436;
        if (ch=='w')  ch=0x0432;
        if (ch=='x')  ch=0x044c;
        if (ch=='y')  ch=0x044a;
        if (ch=='z')  ch=0x0437;
        if (ch=='{')  ch=0x0448;
        if (ch=='|')  ch=0x044d;
        if (ch=='}')  ch=0x0449;
        if (ch=='~')  ch=0x0447;
        // Remaining are OK

        // Other mappings that just happen to be in the right place
        if ((ch>='@') && (ch<='~')) ch=ch+(0x040f)-'@'; // Map anything left over
        break;

    case 2 : // Latin G0 Set - Option 2 Estonian
        // Nat. opt

    case 3 : // Czech/Slovak
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 hash
        if (ch=='$')  ch=0x016f; // 2/4 u ring
        if (ch=='@')  ch=0x010d; // 4/0 c caron
        if (ch=='[')  ch=0x0165; // 5/B t caron
        if (ch=='\\') ch=0x017e; // 5/C z caron
        // Nat. opt. 2
        if (ch==']')  ch=0x00fd; // 5/D y acute
        if (ch=='^')  ch=0x00ed; // 5/E i acute
        if (ch=='_')  ch=0x0159; // 5/F r caron
        if (ch=='`')  ch=0x00e9; // 6/0 e acute
        if (ch=='{')  ch=0x00e1; // 7/B a acute
        if (ch=='|')  ch=0x011b; // 7/C e caron
        if (ch=='}')  ch=0x00fa; // 7/D u acute
        if (ch=='~')  ch=0x0161; // 7/E s caron
        break;
    case 4 : // German
        // Nat. opt. 1
        if (ch=='#')  ch='#';    // 2/3 # is not mapped
        if (ch=='$')  ch=0x0024; // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00a7; // 4/0 Section sign
        if (ch=='[')  ch=0x00c4; // 5/B A umlaut
        if (ch=='\\') ch=0x00d6; // 5/C O umlaut
        // Nat. opt. 2
        if (ch==']')  ch=0x00dc; // 5/D U umlaut
        if (ch=='^')  ch='^';    // 5/E Caret (not mapped)
        if (ch=='_')  ch=0x005f; // 5/F Underscore (not mapped)
        if (ch=='`')  ch=0x00b0; // 6/0 Masculine ordinal indicator
        if (ch=='{')  ch=0x00e4; // 7/B a umlaut
        if (ch=='|')  ch=0x00f6; // 7/C o umlaut
        if (ch=='}')  ch=0x00fc; // 7/D u umlaut
        if (ch=='~')  ch=0x00df; // 7/E SS
        break;


    case 5 : // Ukrainian (Cyrillic)

        // Nat. opt. 2. Column 40-4f
        if (ch=='@')  ch=0x042e;    // Cyrillic Capital Letter Yu
        if (ch=='C')  ch=0x0426; // Cyrillic
        if (ch=='D')  ch=0x0414; //
        if (ch=='E')  ch=0x0415;
        if (ch=='F')  ch=0x0424;
        if (ch=='G')  ch=0x0413; //
        if (ch=='H')  ch=0x0425; //
        // Cyrillic G0 Column 50-5f
        if (ch=='Q')  ch=0x042f; // 5/1
        if (ch=='R')  ch=0x0420; // 5/2
        if (ch=='S')  ch=0x0421;
        if (ch=='T')  ch=0x0422;
        if (ch=='U')  ch=0x0423;
        if (ch=='V')  ch=0x0416;
        if (ch=='W')  ch=0x0412;
        if (ch=='X')  ch=0x042c;
        if (ch=='Y')  ch=0x0406; // 5/8 042a russian
        if (ch=='Z')  ch=0x0417; // 5/9
        if (ch=='[')  ch=0x0428; // Nap opt 2 starts here
        if (ch=='\\') ch=0x0404; // 5/c Russian 042d
        if (ch==']')  ch=0x0429; // 5/d
        if (ch=='^')  ch=0x0427; // 5/e
        if (ch=='_')  ch=0x0407; // 5/f russian 042b
        // Cyrillic G0 Column 60-6f
        if (ch=='`')  ch=0x044e; // 6/0
        // if (ch=='a')  ch=0x0430; // 6/1
        // if (ch=='b')  ch=0x0431;
        if (ch=='c')  ch=0x0446;
        if (ch=='d')  ch=0x0434;
        if (ch=='e')  ch=0x0435;
        if (ch=='f')  ch=0x0444;
        if (ch=='g')  ch=0x0433;
        if (ch=='h')  ch=0x0445;
        if (ch=='i')  ch=0x0438;
        if (ch=='j')  ch=0x0439;
        // Remaining are OK
        // Cyrillic G0 Column 70-7f
        if (ch=='p')  ch=0x006e; // 7/0 Use lower case n for Ukrainian
        if (ch=='q')  ch=0x044f; // 7/1
        if (ch=='r')  ch=0x0440; // 7/2
        if (ch=='s')  ch=0x0441; // 7/3
        if (ch=='t')  ch=0x0442; // 7/4
        if (ch=='u')  ch=0x0443; // 7/5
        if (ch=='v')  ch=0x0436; // 7/6
        if (ch=='w')  ch=0x0432; // 7/7
        if (ch=='x')  ch=0x044c; // 7/8
        if (ch=='y')  ch=0x0456; // 7/9 russian 044a
        if (ch=='z')  ch=0x0437; // 7/a
        if (ch=='{')  ch=0x0448; // 7/b
        if (ch=='|')  ch=0x0454; // 7/c russian 044d
        if (ch=='}')  ch=0x0449; // 7/d
        if (ch=='~')  ch=0x0447; // 7/e russian 0447
        // Remaining are OK


        // Stuff we map automatically ('n' is an exception because this is the only latin character)
        if ((ch>='@') && (ch<='~') && ch!='n') ch=ch+(0x040f)-'@';

        if (ch=='p')  ch=0x006e; // 7/0 - redo this
        break;
    case 6 : // Lettish/Lithuanian (Latin)
        if (ch=='#')  ch=0x0023; // 2/3
        if (ch=='$')  ch=0x0024; // 2/4
        if (ch=='@')  ch=0x0160; // 4/0
        if (ch=='[')  ch=0x0117; // 5/B
        if (ch=='\\') ch=0x0229; // 5/C
        if (ch==']')  ch=0x017d; // 5/D
        if (ch=='^')  ch=0x010d; // 5/E
        if (ch=='_')  ch=0x016b; // 5/F
        if (ch=='`')  ch=0x0161; // 6/0
        if (ch=='{')  ch=0x0105; // 7/B
        if (ch=='|')  ch=0x0173; // 7/C
        if (ch=='}')  ch=0x017e; // 7/D
        if (ch=='~')  ch=0x012f; // 7/E This is the best match in teletext2
        break;
    // case 7 : // Unused

    default:
        return '?';
    }
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
} // mapRegion4


wchar_t mapRegion6(wchar_t ch, int language) // Turkish=3, Greek=7
{
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
    case 3 : // Turkish
        // Nat. opt
        if (ch=='#')  ch=0x0167; // 2/3
        if (ch=='$')  ch=0x011f; // 2/4
        if (ch=='@')  ch=0x0130; // 4/0
        if (ch=='[')  ch=0x015e; // 5/B
        if (ch=='\\') ch=0x00d6; // 5/C
        if (ch==']')  ch=0x00c7; // 5/D
        if (ch=='^')  ch=0x00dc; // 5/E
        if (ch=='_')  ch=0x011e; // 5/F
        if (ch=='`')  ch=0x0131; // 6/0
        if (ch=='{')  ch=0x015f; // 7/B
        if (ch=='|')  ch=0x00f6; // 7/C
        if (ch=='}')  ch=0x00e7; // 7/D
        if (ch=='~')  ch=0x00fc; // 7/E
        break;

    case 7 : // Greek
        if (ch=='R')  ch=0x0374; // Top right dot thingy
        if ((ch>='@') && (ch<='~')) ch=ch+0x390-'@';
        if (ch=='<')  ch=0x00ab; // left chevron
        if (ch=='>')  ch=0x00bb; // right chevron
        // Nat. opt. 1
        /*
        if (ch=='#')  ch=0x00a3; // 2/3 Pound
        if (ch=='$')  ch='$';    // 2/4 Dollar sign not mapped
        if (ch=='@')  ch=0x00e9; // 4/0 e acute
        if (ch=='[')  ch=0x00b0; // 5/B ring
        if (ch=='\\') ch=0x00e7; // 5/C c cedilla
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D right arrow
        if (ch=='^')  ch=0x2191; // 5/E up arrow
        if (ch=='_')  ch='#';    // 5/F hash
        if (ch=='`')  ch=0x00f9; // 6/0 u grave
        if (ch=='{')  ch=0x00e0; // 7/B a grave
        if (ch=='|')  ch=0x00f2; // 7/C o grave
        if (ch=='}')  ch=0x00e8; // 7/D e grave
        if (ch=='~')  ch=0x00ec; // 7/E i grave
            */
        break;
    default:
        return '?';
    }
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
} // mapRegion6

wchar_t mapRegion8(wchar_t ch, int language)
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
    case 0 : // English
        // std::cout << "trace2" << std::endl;

        // Nat. opt. 1
        if (ch=='#')  ch=0x00A3; // 2/3 # is mapped to pound sign
        //if (ch=='$')  ch=0x0024; // 2/4 Dollar sign (no change!)
        //if (ch=='@')  ch=0x0040; // 4/0 No change
        if (ch=='[')  ch=0x2190; // 5/B Left arrow.
        if (ch=='\\') ch=0xbd;   // 5/C Half
        // Nat. opt. 2
        if (ch==']')  ch=0x2192; // 5/D Right arrow.
        if (ch=='^')  ch=0x2191; // 5/E Up arrow.
        if (ch=='_')  ch=0x0023; // 5/F Underscore is hash sign
        if (ch=='`')  ch=0x2014; // 6/0 Centre dash. The full width dash e731
        if (ch=='{')  ch=0xbc;   // 7/B Quarter
        if (ch=='|')  ch=0x2016; // 7/C Double pipe
        if (ch=='}')  ch=0xbe;   // 7/D Three quarters
        if (ch=='~')  ch=0x00f7; // 7/E Divide
        // std::cout << "trace3" << std::endl;
        break;
    case 1 : // French
        // Nat. opt. 1
        if (ch=='#')  ch=0x00e9; // 2/3 e acute
        if (ch=='$')  ch=0x00ef; // 2/4 i umlaut
        if (ch=='@')  ch=0x00e0; // 4/0 a grave
        if (ch=='[')  ch=0x00eb; // 5/B e umlaut
        if (ch=='\\') ch=0x00ea; // 5/C e circumflex
        // Nat. opt. 2
        if (ch==']')  ch=0x00f9; // 5/D u grave
        if (ch=='^')  ch=0x00ee; // 5/E i circumflex
        if (ch=='_')  ch='#';    // 5/F #
        if (ch=='`')  ch=0x00e8; // 6/0 e grave
        if (ch=='{')  ch=0x00e2; // 7/B a circumflex
        if (ch=='|')  ch=0x00f4; // 7/C o circumflex
        if (ch=='}')  ch=0x00fb; // 7/D u circumflex
        if (ch=='~')  ch=0x00e7; // 7/E c cedilla
        break;
    case 7 : // Arabic
        switch (ch)
        {
        case ' ':; // 2/0
        case '!':; // 2/1
        case '"':; // 2/2
        case '£':; // 2/3
        case '$':; // 2/4
        case '%':; // 2/5
        case ')':; // 2/8
        case '(':; // 2/9
        case '*':; // 2/A
        case '+':; // 2/B
        case '-':; // 2/D
        case '.':; // 2/E
        case '/':; // 2/F
        case '0':; // 3/0
        case '1':; // 3/1
        case '2':; // 3/2
        case '3':; // 3/3
        case '4':; // 3/4
        case '5':; // 3/5
        case '6':; // 3/6
        case '7':; // 3/7
        case '8':; // 3/8
        case '9':; // 3/9
        case ':':; // 3/a
        //case '0':; // 3/b
            break;
        case '>': ch='<'; // 3/c
            break;
        case '=':; // 3/d
            break;
        case '<': ch='>'; // 3/e
            break;
        // case '?':; // 3/f
        default :
            ch=ch+0xe606-'&'; // 2/6 onwards
        }
        break;
    default:
        //std::cout << "Language not implemented yet: " << m_rootPage->GetLanguage() << std::endl;
        ;
    }
    // More language mappings including Greek
    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
} // region 8

wchar_t mapRegion10(wchar_t ch, int language)
{
    // These mappings are for when using the teletext2 font
    // Some mappings are required from true Teletext to teletext2
    // There is one set of national options for each language
    // Could put in an enum for the languages, but that would only apply to west europe
    /* See ETSI "Latin National Option Sub-Sets" in ETSI EN 300 706 V1.2.1 (2003-04)
       The only exception is 7/F which is common to all languages*/
    ch&=0x7f;
    // std::cout << "trace1" << std::endl;
    switch (language)
    {
    case 5 : // Hebrew
        switch (ch) // Mostly the same as English nat. opts.
        {
        case '#':  ch=0x00A3;  break;// 2/3 # is mapped to pound sign
        case '[':  ch=0x2190;  break;// 5/B Left arrow.
        case '\\': ch=0xbd;    break;// 5/C Half
        case ']':  ch=0x2192;  break;// 5/D Right arrow.
        case '^':  ch=0x2191;  break;// 5/E Up arrow.
        case '_':  ch=0x0023;  break;// 5/F Underscore is hash sign
        case '{':  ch=0x20aa;  break;// 7/B sheqel
        case '|':  ch=0x2016;  break;// 7/C Double pipe
        case '}':  ch=0xbe;    break;// 7/D Three quarters
        case '~':  ch=0x00f7;  break;// 7/E Divide
        default:
            if ((ch>0x5f) && (ch<0x7b)) // Hebrew characters
            {
                ch=ch+0x05d0-0x60;
            }
        }
        break;

    case 7 : // Arabic
        switch (ch)
        {
        case ' ':; // 2/0
        case '!':; // 2/1
        case '"':; // 2/2
            break;
        case '£': ch='#'; // 2/3
            break;
        case '$':; // 2/4
        case '%':; // 2/5
        case ')':; // 2/8
        case '(':; // 2/9
        case '*':; // 2/A
        case '+':; // 2/B
        case '-':; // 2/D
        case '.':; // 2/E
        case '/':; // 2/F
        case '0':; // 3/0
        case '1':; // 3/1
        case '2':; // 3/2
        case '3':; // 3/3
        case '4':; // 3/4
        case '5':; // 3/5
        case '6':; // 3/6
        case '7':; // 3/7
        case '8':; // 3/8
        case '9':; // 3/9
        case ':':; // 3/a
        //case '0':; // 3/b
            break;
        case '>': ch='<'; // 3/c
            break;
        case '=':; // 3/d
            break;
        case '<': ch='>'; // 3/e
            break;
        // case '?':; // 3/f
        default :
            ch=ch+0xe606-'&'; // 2/6 onwards
        }
        break;
    default:
        //std::cout << "Language not implemented yet: " << m_rootPage->GetLanguage() << std::endl;
        ;
    }

    if (ch==0x7f) ch=0xe65f; // 7/F Bullet (rectangle block)

    //std::cout << "trace4" << std::endl;

    return ch;
} // region 10
