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
 *
 * \param ch - Character to transform
 * \param language - Sub language 0..7 from bits C12 to C14 (reverse order!)
 * \return Transformed character ready to display
 */
wchar_t mapRegion0(wchar_t ch, int language); // west europe
wchar_t mapRegion1(wchar_t ch, int language); // west europe + polish
wchar_t mapRegion2(wchar_t ch, int language); // west europe + turkish
wchar_t mapRegion3(wchar_t ch, int language); // west europe + turkish
wchar_t mapRegion4(wchar_t ch, int language); // 4: Ser/Cro/Ger/Est/Lit/Rus/Bul/Ukr/Cze/Slo
wchar_t mapRegion6(wchar_t ch, int language);
wchar_t mapRegion8(wchar_t ch, int language); // 8: English/French/Arabic
wchar_t mapRegion10(wchar_t ch, int language); // 10: Hebrew/Arabic



#endif // MAPCHAR_H_INCLUDED
