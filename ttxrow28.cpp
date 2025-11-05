/***************************************************************
 * Name:      ttxrow28.h
 * Purpose:   Handle packet 28 usage and import/export TTI
 * Author:    Peter Kwan (peterk.vt80@gmail.com)
 * Created:   2025-11-01
 * Copyright: Peter Kwan (c) 2025
 * License:
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
 *************************************************************************** **/
 #include "ttxrow28.h"
/**
 * @brief Read tti packet 28 line and decode it to a packet 28 structure.
 * Access routines to read and set X28 parameters
 * Write back to X28 tti
 */

TTXRow28::TTXRow28()
{
  //ctor
  std::cout << "[TTXRow28::TTXRow28] called without parameters " << std::endl;
  this->defaultClut();
}

TTXRow28::TTXRow28(std::string line)
{
  //ctor
  std::cout << "[TTXRow28::TTXRow28] called. Line=" << line << std::endl;
  std::string str=validate(line);
  std::cout << "[TTXRow28::TTXRow28] called. str=" << str << std::endl;
  this->defaultClut();
  if (this->decode(str))
  {
    std::cout << "Good X28" << std::endl;
  }
}


TTXRow28::~TTXRow28()
{
  //dtor
}

/// @todo Encode a TTI formatted packet

/// Decode a tti formatted packet 28
bool TTXRow28::decode(std::string line)
{
  bool result = true;
  unsigned triples[13];
  unsigned int triple[3];

  // Extract the triples
  for (unsigned int i = 0; i < 13; ++i)
  {
    triple[0]=(static_cast<unsigned int>(line.c_str()[i * 3 + 1])) & 0x3f;
    triple[1]=(static_cast<unsigned int>(line.c_str()[i * 3 + 2])) & 0x3f;
    triple[2]=(static_cast<unsigned int>(line.c_str()[i * 3 + 3])) & 0x3f;
    std::cout << std::hex << std::setw(2);
    std::cout << triple[0] << " " << triple[1] << " " << triple[2] << std::endl;

    triples[i] = (triple[2] << 12) | (triple[1] << 6) | triple[0];

    std::cout << triples[i] << " ";
  }
  std::cout << std::endl;

  this->dc = line.c_str()[0] & 0x3f;

  // Extract all of the TTI X28 parameters
  this->pageFunction = triples[0] & 0x0f; // t1, 1..4
  this->pageCoding = (triples[0] >> 4) & 0x07; // t1, 5..7
  this->defaultG0G2CharacterSet = (triples[0] >> 7) & 0x7f; // t1, 8..14
  this->secondG0G2CharacterSet = (  // t1, 15..18, t2, 1-3
    ((triples[0] >> 14) & 0x0f) | ((triples[1] & 0x07) << 4)
  );

  // Colours
    // Colour mappings
  // t2 11-18, t3-t12 1-18, t13 1-4 (RGB)
  const unsigned int bitIndex = 10;
  unsigned int tripletStart = 1;
  unsigned int colour = 0;
  for (unsigned int i = 0; i < 16*3; ++i) { // Sixteen R, G, B values
    // work out the indices
    unsigned int startBit = (i * 4) + bitIndex;
    unsigned int tripletIndex = tripletStart + /*std::trunc*/(startBit / 18);
    startBit = startBit % 18;
    unsigned int colourIndex = /*std::trunc*/(i / 3); // CLUT 0/1 for dc == 4
    unsigned int colourValue = i % 3; // RGB
    unsigned int clutIx = i < (8 * 3) ? 2 : 3; // [!] assume dc is 0, which it might not be in future
    // extract the four bit colour value
    unsigned int t =  triples[tripletIndex]; // Get the triplet
    t = (t >> startBit) & 0x0f; // Shift and mask
    // does the data cross a triplet boundary? (ie. the bits go past 18)
    if (startBit > 14) {
      unsigned int split = 18 - startBit; // This is always 2! Could assert that
      unsigned int t2 = triples[tripletIndex + 1] & 0x03; // Triplets only ever break on two bits
      t2 = t2 << split;
      t = t | t2;
    }
    colour = colour | t <<  ((2-colourValue) * 4);
    if (colourValue == 2) // Done an RGB value
    {
      this->clut[clutIx][colourIndex % 8] = colour;
      if (true) {
        std::cout << "Clut[" << clutIx << "][" << colourIndex % 8 << "] = " << colour << std::endl;
      }
      colour = 0;
    }
  }

  // Screen colour remapping
  this->defaultScreenColour = (triples[12] >> 4) & 0x1f; // t13, 5..9
  this->defaultRowColour = (triples[12] >> 9) & 0x1f; // t13, 10..14
  this->blackBackgroundSub = (triples[12] >> 14) & 0x01; // t13, 15
  this->remap = (triples[12] >> 15) & 0x07; // t13, 16..18
  std::cout << "[TTXRow28::TTXRow28] this->remap =  " << this->remap << std::endl;

  // left and right extension panels
  this->enableLeftPanel = (triples[1] & 0x08) > 0; // t2, 4
  this->enableRightPanel = (triples[1] & 0x10) > 0; // t2, 5
  this->sidePanelStatusFlag = (triples[1] & 0x20) > 0; // t2, 6
  this->leftColumns = (triples[1] >> 6) & 0x0f; // t2, 7..10
  // result.rightColumns = (triples[12]) Implied. Always 16-leftColumns  [!] Make this a function


  return result;
}

unsigned int TTXRow28::rightColumns()
{
  return 16 - this->leftColumns;
}


void TTXRow28::defaultClut()
{
  // Default clut 0 colours
  this->clut[0][0] = 0x000;
  this->clut[0][1] = 0xf00;
  this->clut[0][2] = 0x0f0;
  this->clut[0][3] = 0xff0;
  this->clut[0][4] = 0x00f;
  this->clut[0][5] = 0xf0f;
  this->clut[0][6] = 0x0ff;
  this->clut[0][7] = 0xfff;

  // Default clut 1 colours
  this->clut[1][0] = 0x000;
  this->clut[1][1] = 0x700;
  this->clut[1][2] = 0x070;
  this->clut[1][3] = 0x770;
  this->clut[1][4] = 0x007;
  this->clut[1][5] = 0x707;
  this->clut[1][6] = 0x077;
  this->clut[1][7] = 0x777;

  // Default clut 2 colours
  this->clut[2][0] = 0xf05; // crimsonish
  this->clut[2][1] = 0xf70; // orangish
  this->clut[2][2] = 0x0f7; // blueish green
  this->clut[2][3] = 0xffb; // pale yellow
  this->clut[2][4] = 0x0ca; // cyanish
  this->clut[2][5] = 0x500; // dark red
  this->clut[2][6] = 0x652; // hint of a tint of runny poo
  this->clut[2][7] = 0xc77; // gammon

  // Default clut 3 colours
  this->clut[3][0] = 0x333; // pastel black
  this->clut[3][1] = 0xf77; // pastel red
  this->clut[3][2] = 0x7f7; // pastel green
  this->clut[3][3] = 0xff7; // pastel yellow
  this->clut[3][4] = 0x77f; // pastel blue
  this->clut[3][5] = 0xf7f; // pastel magenta
  this->clut[3][6] = 0x7ff; // pastel cyan
  this->clut[3][7] = 0xddd; // pastel white
}

unsigned int TTXRow28::Remap(unsigned int colour, bool useForeground)
{
  unsigned int clutIndex = 0;
  colour = colour & 0x07;

  // Black Background Colour Substitution
  // If this is set, then colour 0 in a row is replaced by the default row colour
  if (blackBackgroundSub && !useForeground && colour == 0) {
    const auto value = defaultRowColour;
    clutIndex = (value >> 3) & 0x03;
    const auto colourIndex = value & 0x07;
    return clut[clutIndex][colourIndex];
  }

  if (useForeground)
  {
    if (this->remap > 4)
    {
      clutIndex = 2;
    }
    else if (this->remap < 3)
    {
      clutIndex = 0;
    }
    else
    {
      clutIndex = 1;
    }
  }
  else
  {
    if (this->remap < 3) // background
    {
      clutIndex = this->remap; // 0..2
    }
    else if (this->remap == 3 || this->remap == 5)
    {
      clutIndex = 1;
    }
    else if (this->remap == 4 || this->remap == 6)
    {
      clutIndex = 2;
    }
    else
    {
      clutIndex = 3; // 7
    }
  }
  return clut[clutIndex][colour];
}

unsigned int TTXRow28::Region(bool primary)
{
  if (primary)
  {
    return defaultG0G2CharacterSet >> 3;
  }
  else
  {
    return secondG0G2CharacterSet >> 3;
  }
}

void TTXRow28::SetRegion(int region, bool primary)
{
  region &= 0x0f;
  region <<= 3;
  if (primary)
  {
    defaultG0G2CharacterSet &= 0x07;
    defaultG0G2CharacterSet |= region;
  }
  else
  {
    secondG0G2CharacterSet &= 0x07;
    secondG0G2CharacterSet |= region;
  }
}


unsigned int TTXRow28::Language(bool primary)
{
  if (primary)
  {
    return defaultG0G2CharacterSet & 0x07;
  }
  else
  {
    return secondG0G2CharacterSet & 0x07;
  }
}

void TTXRow28::SetLanguage(int language, bool primary)
{
  language &= 0x07; // Mask language
  if (primary)
  {
    defaultG0G2CharacterSet &= 0x38;
    defaultG0G2CharacterSet |= language;
  }
  else
  {
    secondG0G2CharacterSet &= 0x38;
    secondG0G2CharacterSet |= language;
  }
}



/** Encode this object's X28/0/1 data into a tti OL,28 packet.
 * Packs the colour palette and colour remappings into triplets
 * as well as the language settings.
 * @return OL,28 line or "" if it fails
 */
std::string TTXRow28::encode()
{
  if (dc <0) { // Uninitialised?
    return "";
  }
  unsigned int triples[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  /** AddX28 - lambda has access to the triples array
   *  Places bitCount bits of value into the triple[tripleIndex] and can
   *  overflow into the next triple if needed.
   *  @param value : Data to add to the packet
   *  @param tripleIndex : Number of triple that the value starts in 1..13
   *  @param bitIndex : The bit offset where the value starts in the triple
   *  @param bitCount : The number of bits to use from value
   */
  auto AddX28 = [&](unsigned int value, unsigned int tripleIndex, unsigned int bitIndex, unsigned int bitCount)
  {
    // Mask off bitCount bits
    unsigned int mask = (1 << bitCount) - 1;
    unsigned int v2 = value & mask;

    // Shift to the required bit index and trim any overflow
    v2 = (v2 << (bitIndex-1)) & 0x3ffff;
    triples[tripleIndex-1] |= v2;

    // Overflow of high bits goes into the next triple
    if ((bitIndex + bitCount) > 18)
    {
      v2 = value >>= 18 - bitIndex + 1;
      triples[tripleIndex] |= v2;
    }
  };

  // Work our way along the packet
  AddX28(pageFunction, 1, 1, 4); // 1: 1-4 Page function. 4 bits
  AddX28(pageCoding, 1, 5, 3); // 1: 5-7 Page coding. 3 bits
  // @todo Implement X28 character sets
  AddX28(defaultG0G2CharacterSet, 1, 8, 7); // 1: 8-14 Default G0 and G2 character set designation. 7 bits
  AddX28(secondG0G2CharacterSet, 1, 15, 7); // 1: 15-18, 2: 1-3 Second G0 Set designation
  AddX28(enableLeftPanel, 2, 4, 1);
  AddX28(enableRightPanel, 2, 5, 1);
  AddX28(sidePanelStatusFlag, 2, 6, 1);
  AddX28(leftColumns, 2, 7, 4);
  // 2: 11-18, 3:1-18, 13: 1-4
  // 16x12 bit values
  unsigned int tr = 2; // triple
  unsigned int bi = 11; // bit offset
  for (unsigned int colourix = 0; colourix<16; ++colourix)
  {
    unsigned int c = clut[2 + colourix / 8][colourix % 8]; // X28 only encodes CLUT 2 and 3
    // Need to swap red and blue because X28 does colours backwards
    unsigned int colour = ((c & 0x00f) << 8) | (c & 0x0f0) | (c & 0xf00) >> 8;
    AddX28(colour, tr, bi, 12);
    bi += 12;
    if (bi >= 18)
    {
      bi = bi - 18;
      tr++;
    }
  }

  AddX28(defaultScreenColour, 13, 5, 5); // t13 5..9
  AddX28(defaultRowColour, 13, 10, 5); // t13 10..14
  AddX28(blackBackgroundSub, 13, 15, 1); // t13 15
  AddX28(remap, 13, 16, 3); // t13 16..18

  /*
  if (false) {
    let result = "                                        "
    let s = ""
    for (let i=0; i<13; ++i) {
      s+=hex(triples[i],5)+" "
    }
    console.log("triples enc = " + s)
  }
  */
  // Pack the triples into a tti OL,28
  std::string result = "";
  result += static_cast<char>(0x40);
  for (unsigned int tr(0); tr < 13; ++tr) {
    unsigned int t = triples[tr];
    result += static_cast<char>( (t & 0x3f) | 0x40 );
    result += static_cast<char>( ((t>>6) & 0x3f) | 0x40 );
    result += static_cast<char>( ((t>>12) & 0x3f) | 0x40 );
  }
  std::cout << "result = " << result << std::endl;
  return result;
} // EncodeOL28

