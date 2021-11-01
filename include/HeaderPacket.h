#ifndef HEADERPACKET_H
#define HEADERPACKET_H

#include <T42.h>
#include "stdio.h"

class HeaderPacket : public T42
{
    public:
        HeaderPacket();
        HeaderPacket(T42& t42);
        virtual ~HeaderPacket();

        uint8_t Getmag() { return mag; }
        void Setmag(uint8_t val) { mag = val; }
        char* GetHeading() { return &heading[0]; }
        uint8_t GetPageNumber() { return page_number; }
        char* GetTime() { return time; }


    protected:

    private:
        uint8_t mag{1};
        uint16_t flags{0};
        char heading[25] = {"WXTED WXTED WXTED WXTED "};
        uint8_t page_number{0};
        char time[9] = {"00:00/00"};
};

#endif // HEADERPACKET_H
