#include "ttxrow28.h"

TTXRow28::TTXRow28()
{
  //ctor
  std::cout << "[TTXRow28::TTXRow28] called without parameters " << std::endl;
}

TTXRow28::TTXRow28(std::string line)
{
  //ctor
  std::cout << "[TTXRow28::TTXRow28] called. Line=" << line << std::endl;
  std::string str=validate(line);
  std::cout << "[TTXRow28::TTXRow28] called. str=" << str << std::endl;

  uint16_t triple[3];
  for (int i=1;i<40;i+=3)
  {
    auto ch=static_cast<uint16_t>(str.c_str()[i]);
    ch &= 0x007f;
    triple[0]=static_cast<uint16_t>(str.c_str()[i]);
    triple[1]=static_cast<uint16_t>(str.c_str()[i+1]);
    triple[2]=static_cast<uint16_t>(str.c_str()[i+2]);
    std::cout << std::hex << std::setw(2);
    std::cout << triple[0] << " " << triple[1] << " " << triple[2] << std::endl;
  }
  std::cout << std::endl;
  // TODO Get the designator, and type numbers
  // TODO Get the 14 triplets
}


TTXRow28::~TTXRow28()
{
  //dtor
}
