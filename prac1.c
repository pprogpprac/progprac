#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>


void main()
{
    int i = 0, j = 0, val = 0, n;
    printf("Enter n:\n");
    scanf("%d", &n);
    printf("\n");
    for(i = 1; i <= n; i++)
    {
        if(i%2 == 0)
            val = 0;
        else
            val = 1;

        for(j = 1; j <= i; j++)
        {
            printf("%d ", val);
            if(val < 1)
                val = 1;
            else
                val = 0;
        }
        printf("\n");
    }
}
