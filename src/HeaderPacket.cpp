#include "HeaderPacket.h"

HeaderPacket::HeaderPacket()
{
    //ctor
}

/// Expect a T42 row address 0(
HeaderPacket::HeaderPacket(T42& t42)
{
    if (t42.GetRow() != 0)
    {
        //                    0123456789012345678901234567890123456789
        strncpy(&heading[0], "This is not a header    ", 24);
    }
    else
    {
        char* packet = &t42.GetText()[2]; // Skip past MRAG
        strncpy(&heading[0], packet+8, 24 );
        // Extract the page number
        uint8_t units = _vbi_hamm8_inv[(unsigned int)packet[0] & 0xff];
        uint8_t tens = _vbi_hamm8_inv[(unsigned int)packet[1] & 0xff];
        page_number = tens * 0x10 + units;

        // @todo Guess date/time/page fields

        // @todo Extract flags
        // @todo Make a guess about time. Hours/Minutes/Seconds

        strncpy(time, packet+32, 8);

        std::cout << "[HeaderPacket::HeaderPacket] heading = <" << heading
            << "> pagenumber = " << (unsigned int)page_number
            << " time = " << time
            << std::endl;
    }
}

HeaderPacket::~HeaderPacket()
{
    //dtor
}
