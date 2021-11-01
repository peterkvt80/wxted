#include "T42.h"

T42::T42()
{
    //ctor
}

T42::~T42()
{
    //dtor
}

T42::T42(char* raw_text)
{
    strncpy(text_ptr, raw_text, 42);
    //std::clog << "[T42::T42] raw 0 = " << std::hex << std::setw(2)
      //<< ((unsigned int)text_ptr[0] & 0xff)
      //<< " , 1 = "
     //<< ((unsigned int)text_ptr[1] &0xff)
     //<< std::endl;
    DecodeMRAG();
}

void T42::DecodeMRAG()
{
    uint8_t val0 = _vbi_hamm8_inv[(unsigned int)text[0] & 0xff];
    uint8_t val1 = _vbi_hamm8_inv[(unsigned int)text[1] & 0xff];
    // @todo If deham failed, check for 0xff
    //std::clog << "[T42::DecodeMRAG] deham 0 = " << std::hex << std::setw(2)
//      << ((unsigned int)val0 & 0xff)
      //<< " , 1 = "
     //<<  ((unsigned int)val1 & 0xff)
     //<< std::endl;
    mag = val0 & 0x07;

    int lsb = ((unsigned int)val0  & 0x08) >> 3; // Get the least significant bit of the rowaddress
    int msb = ((unsigned int) val1 & 0xff) << 1; // Shift the most significant bits of the row address
    row = lsb + msb;
    //std::cout << "[T42::DecodeMRAG] mag = " << std::hex
    //<< ((unsigned int)magazine & 0xff)
    //<< " packet = "
    //<< (packet & 0xff)
    //<< std::endl;
}


