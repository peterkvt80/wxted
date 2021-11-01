#ifndef T42_H
#define T42_H

#include <cstdint>

#include "../hamm.h"

#include "stdio.h"
#include "string.h"
#include "iostream"
#include "iomanip"

// T42 is a teletext packet representing the 42 characters not including clock run-in and framing code
// The magazine and row address group are the first two bytes
// The packet body is forty characters
// All other packet classes inherit this class

class T42
{
    public:
        T42();
        T42(char[42]); /// Construct a T42 using a raw packet

        virtual ~T42();

        uint8_t GetMag() { return mag; }
        void SetMag(uint8_t val) { mag = val; }
        uint8_t GetRow() { return row; }
        void SetRow(uint8_t val) { row = val; }
        char* GetText() { return text_ptr; }
        void SetText(char* val) { strncpy(text_ptr, val, 40); }
    protected:

    private:
        uint8_t mag{1};
        uint8_t row{0};
        char text[42];
        char* text_ptr{&text[0]};

        void DecodeMRAG(); /// Extract the magazine and row addresses
};

#endif // T42_H
