#ifndef MAPCHAR_H_INCLUDED
#define MAPCHAR_H_INCLUDED

#include <iostream>
#include <wx/string.h>

/** MapChar
 * Maps a character from teletext space to teletext2.ttf space
 * using the region code and the sub language in that region
 * \param ch - Character to transform
 * \param region - Small number bits 14 to 11 from Table 32 Function of Default G0 and G2 Character Set Designation and National Option Selectionbits in packets X/28/0 Format 1, X/28/4, M/29/0 and M/29/4
 * \param language - Sub language 0..7 from bits C12 to C14 (reverse order!)
 * \return Transformed character ready to display
 */
wchar_t MapChar(wchar_t ch, int language, int region);

/**
 * mapEnglish - Translate from ASCII to corresponding teletext2 font character/
 * \param ch - Character to transform
 * \return Transformed character ready to display
 */

wchar_t mapEnglish(wchar_t ch);
wchar_t mapFrench(wchar_t ch);
wchar_t mapSwedish(wchar_t ch);
wchar_t mapCzechSlovak(wchar_t ch);
wchar_t mapGerman(wchar_t ch);
wchar_t mapSpanishPortuguese(wchar_t ch);
wchar_t mapItalian(wchar_t ch);
wchar_t mapPolish(wchar_t ch);
wchar_t mapTurkish(wchar_t ch);
wchar_t mapSerbian(wchar_t ch);
wchar_t mapRumanian(wchar_t ch);
wchar_t mapRussianBulgarian(wchar_t ch);
wchar_t mapEstonian(wchar_t ch);
wchar_t mapUkranian(wchar_t ch);
wchar_t mapLettishLithuanian(wchar_t ch);
wchar_t mapGreek(wchar_t ch);
wchar_t mapArabic(wchar_t ch);
wchar_t mapHebrew(wchar_t ch);

#endif // MAPCHAR_H_INCLUDED
