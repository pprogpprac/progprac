#include <iostream>
#include <stdint.h>
#include <bitset>

// Works with char also - unsigned char bytereverse(unsigned char b) { .... return b; }
uint8_t bytereverse(uint8_t b)
{
    b = (b & 0x55) << 1 | (b & 0xAA) >> 1; // swap adjacent bits
    b = (b & 0x33) << 2 | (b & 0xCC) >> 2; // swap adjacent pairs
    b = (b & 0x0F) << 4 | (b & 0xF0) >> 4; // swap nibbles
    return b;
}

int main()
{
    uint8_t v = 0x4a;
    //std::cout << "before reverse, v = " << std::hex << v << std::endl;
    std::cout << "before reverse, v = " << std::bitset<8>(v) << std::endl;

    v = bytereverse(v);

    std::cout << "after reverse, v  = " << std::bitset<8>(v) << std::endl;
    //std::cout << "after reverse, v  = " << std::hex << v << std::endl;
    return 0;
}


/*
int main()
{
    std::cout << "Hello World !\n";

    uint8_t num = 0x9A;
    uint8_t temp = 0x00;
    int i = 0;

    int nbits = sizeof(num) * 8;

    std::cout << "nbits = " << nbits << std::endl;

    for(i = 0; i < nbits; i+=2)
    {
        //temp = temp & num;
        temp = num << ((nbits-1) - i);
        temp = ~(temp ^ num);
        //temp = temp >> ((nbits-1) - i);
        std::cout << "Iteration " << i << ": temp = " << std::bitset<8>(temp) << std::endl;
    }
    std::cout << "num  = " << std::bitset<8>(num) << std::endl;
    std::cout << "temp = " << std::bitset<8>(temp) << std::endl;
    return 0;
}
*/
