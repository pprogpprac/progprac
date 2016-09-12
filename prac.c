/*
// Method 1 to find whether your machine is little or big endian or bi-endian:
#include <stdio.h>
int main()
{
   unsigned int i = 1;
   char *c = (char*)&i;
   if (*c)
       printf("Little endian");
   else
       printf("Big endian");
   getchar();
   return 0;
}
*/

/*
// Method 2 to find whether your machine is little or big endian or bi-endian:
#include <stdio.h>

// function to show bytes in memory, from location start to start+n.
void show_mem_rep(char *start, int n)
{
    int i;
    for (i = 0; i < n; i++)
         printf(" %.2x", start[i]);
    printf("\n");
}

// Main function to call above function for 0x01234567.
int main()
{
   int i = 0x01234567;
   show_mem_rep((char *)&i, sizeof(i));
   getchar();
   return 0;
}

*/
// Method 3:

#include <stdio.h>
#include <stdint.h> // For uint8_t, uint16_t, etc.

void main()
{
    int x = 1, nri = 18, m = 0;
    uint8_t foo = 18;
    uint16_t foo1 = 18;
    uint32_t foo2 = 18;

    char *y = (char*)&x;
    printf("%c\n",*y+48);

    //for (m = 0; m < 64; m++)
    //{
        printf ("%d,", (int) (((char *)&nri)[m])); //If it prints 18, then little endian.
        printf ("\n%d,", (int) (((char *)&foo)[m])); //If it prints 18, then little endian.
        printf ("\n%d,", (int) (((char *)&foo1)[m])); //If it prints 18, then little endian.
        printf ("\n%d,", (int) (((char *)&foo2)[m])); //If it prints 18, then little endian.
    //}
    printf ("\n");

    printf("sizeof(uint8_t) = %zu\n", sizeof(uint8_t));
    printf("sizeof(uint16_t) = %zu\n", sizeof(uint16_t));
    printf("sizeof(uint32_t) = %zu\n", sizeof(uint32_t));
}

/* Explanation:
Problem Statement:
If it's little endian it will print 1. If it's big endian it will print 0. Is that correct? Or will setting a char* to int x always point to the least significant bit, regardless of endianness?

Solution:
In short, yes.

Suppose we are on a 32-bit machine.

If it is little endian, the x in the memory will be something like:

       higher memory
          ----->
    +----+----+----+----+
    |0x01|0x00|0x00|0x00|
    +----+----+----+----+
    A
    |
   &x
so (char*)(*x) == 1, and *y+48 == '1'.

If it is big endian, it will be:

    +----+----+----+----+
    |0x00|0x00|0x00|0x01|
    +----+----+----+----+
    A
    |
   &x
so this one will be '0'.

shareedit
answered Oct 9 '12 at 3:05

Marcus
3,979921

What is the significance of the value 48 added to y? – Abin Mathew Abraham Feb 1 at 15:57
2
@AbinMathewAbraham 48 is the ascii code of '0' :) – Marcus Feb 18 at 8:37

I am using MAC OS with intel processors. It is supposed to be Little Endian. However, 1 seems to be a special case because when 1 is stored inside the memory, it is in big endian.
/*
void main()
{
    unsigned int x = 1;
    printf ("%d\n", (int) (((char *)&x)[0]));
//And setting &x to char * will enable you to access the individual bytes of the integer, and the ordering of bytes will depend on the endianness of the system.
}
*/
