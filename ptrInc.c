#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>


void main()
{
    int i;
    int j =1;

    int n = 18;
    int *ptr = malloc(sizeof(int) * 10);

    memset(ptr, '\0', sizeof(ptr));

    *ptr = 17;
    ptr[1] = 16;
    ptr[2] = 15;
    ptr[3] = 14;
    ptr[4] = 13;
    ptr[5] = 12;
    ptr[6] = 11;
    ptr[7] = 10;
    ptr[8] = 9;
    ptr[9] = 8;

    printf("*ptr = %d\n", *ptr);
    printf("ptr[0] = %d\n", ptr[0]);
    printf("ptr[1] = %d\n", ptr[1]);
    printf("*ptr = %d\tAddress of ptr = %p\n", *ptr, ptr);

    for(i = 0; i < 10; i++)
    {
        //printf("Iteration %d: Value = %u\n", i, ptr[i]);
        printf("Iteration %d: Value = %d\t ptr++ = %p\n", i, ptr[i], ptr++);
        //printf("Iteration %d: Value = %d\t ptr = %p\t ptr-- = %p\t ptr++ = %p\n", i, ptr[i], ptr, ptr--, ptr++);
        //ptr++;
        /*printf("B4 j = %d\n", j);
        printf("j++ = %d\n", j++);
        printf("Af j = %d\n", j);*/
        printf("Iteration %d: Value of n = %d\t Address of n = %p\n\n", i, n, &n);
    }

    for(i = 0; i < 10; i++)
        ptr--;

    free(ptr);
}
