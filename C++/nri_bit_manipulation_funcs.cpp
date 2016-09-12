#include <iostream>
#include <stdint.h>
#include <bitset>


// Will work for minimum 4 bit representation.
template <typename tfoo>
tfoo bitreverse(tfoo x)
{
	int bit_size = num_of_binary_digits(x);

}

// Works with char also - unsigned char bytereverse(unsigned char b) { .... return b; }
uint32_t bitreverse(uint32_t b)
{
    b = (b & 0x55555555) << 1 | (b & 0xAAAAAAAA) >> 1; // swap adjacent bits   - Swap 1 bit
    b = (b & 0x33333333) << 2 | (b & 0xCCCCCCCC) >> 2; // swap adjacent pairs  - Swap 2 bits
    b = (b & 0x0F0F0F0F) << 4 | (b & 0xF0F0F0F0) >> 4; // swap nibbles         - Swap 4 bits
    b = (b & 0x00FF00FF) << 8 | (b & 0xFF00FF00) >> 8; // swap bytes           - Swap 8 bits
    b = (b & 0x0000FFFF) << 16 | (b & 0xFFFF0000) >> 16; // swap 2 bytes       - Swap 16 bits
    return b;
}

uint16_t bitreverse(uint16_t b)
{
    b = (b & 0x5555) << 1 | (b & 0xAAAA) >> 1; // swap adjacent bits   - Swap 1 bit
    b = (b & 0x3333) << 2 | (b & 0xCCCC) >> 2; // swap adjacent pairs  - Swap 2 bits
    b = (b & 0x0F0F) << 4 | (b & 0xF0F0) >> 4; // swap nibbles         - Swap 4 bits
    b = (b & 0x00FF) << 8 | (b & 0xFF00) >> 8; // swap bytes           - Swap 8 bits
    return b;
}

uint8_t bitreverse(uint8_t b)
{
    b = (b & 0x55) << 1 | (b & 0xAA) >> 1; // swap adjacent bits
    b = (b & 0x33) << 2 | (b & 0xCC) >> 2; // swap adjacent pairs
    b = (b & 0x0F) << 4 | (b & 0xF0) >> 4; // swap nibbles
    return b;
}



template <typename tfoo>
void swap(tfoo *a, tfoo *b) // Don't use XOR because there might be cases where it won't work & is also slow sometimes
{
    tfoo temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


template <typename foo_type>
int num_of_binary_digits(foo_type x)
{
	// Find the number of bits required to represent the number:
	int digits = 0;
	for (digits = 0; x > 0; x >>= 1)
		digits+= 1;
	return digits;
}

/*
int main()
{
	uint32_t v = 0x5; // 0x4ABCDEF5 = 0b 0100 1010 1011 1100 1101 1110 1111 0101
    //uint32_t v = 0x4ABCDEF5; // 0x4ABCDEF5 = 0b 0100 1010 1011 1100 1101 1110 1111 0101
    //std::cout << "before reverse, v = " << std::hex << v << std::endl;


	std::cout << "number of bits required to represent the number: = " << num_of_binary_digits(v) << std::endl;

    std::cout << "before reverse, v = " << std::bitset<32>(v) << std::endl;

    v = bitreverse((uint8_t) v);

    std::cout << "after reverse, v  = " << std::bitset<32>(v) << std::endl; // After reverse, result should be 0XAF7B3D52
    //std::cout << "after reverse, v  = " << std::hex << v << std::endl;
    return 0;
}
*/

// Method 2:
/*
int main()
{
    unsigned int v = 0x4ABCDEF5; // 32-bit word to reverse bit order
    //uint32_t v = 0x99999999;
    //std::cout << "before reverse, v = " << std::hex << v << std::endl;
    std::cout << "before reverse, v = " << std::bitset<32>(v) << std::endl;

    // swap odd and even bits
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    // swap consecutive pairs
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    // swap nibbles ...
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    // swap bytes
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    v = ( v >> 16             ) | ( v               << 16);


    std::cout << "after reverse, v  = " << std::bitset<32>(v) << std::endl;
    //std::cout << "after reverse, v  = " << std::hex << v << std::endl;
    return 0;
}
*/
