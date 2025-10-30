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
