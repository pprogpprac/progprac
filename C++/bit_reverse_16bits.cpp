#include <iostream>
#include <stdint.h>
#include <bitset>

// Works with char also - unsigned char bytereverse(unsigned char b) { .... return b; }
uint16_t bitreverse(uint16_t b)
{
    b = (b & 0x5555) << 1 | (b & 0xAAAA) >> 1; // swap adjacent bits   - Swap 1 bit
    b = (b & 0x3333) << 2 | (b & 0xCCCC) >> 2; // swap adjacent pairs  - Swap 2 bits
    b = (b & 0x0F0F) << 4 | (b & 0xF0F0) >> 4; // swap nibbles         - Swap 4 bits
    b = (b & 0x00FF) << 8 | (b & 0xFF00) >> 8; // swap bytes           - Swap 8 bits
    return b;
}

int main()
{
    uint16_t v = 0x4ABC; // 0x4ABC = 0b 0100 1010 1011 1100
    //std::cout << "before reverse, v = " << std::hex << v << std::endl;
    std::cout << "before reverse, v = " << std::bitset<16>(v) << std::endl;

    v = bitreverse(v);

    std::cout << "after reverse, v  = " << std::bitset<16>(v) << std::endl;
    //std::cout << "after reverse, v  = " << std::hex << v << std::endl;
    return 0;
}
