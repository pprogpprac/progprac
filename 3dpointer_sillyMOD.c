#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void main()
{
   //int a = 7;
   //int *pa = malloc(sizeof(int));
   int x = 2, y = 5, z = 5;
   int i,j,k;
   char ***b;

   b = (char ***) malloc(x * sizeof(char**));
   for (i = 0; i < x; i++)
   {
       b[i] = (char**)malloc(y * sizeof(char*));
       for(j = 0; j < y; j++)
       {
           b[i][j] = (char*)malloc(z * sizeof(char));
       }
   }

   *b[0][4] = 'a';
   *b[0][0] = 'f';
   b[0][4][0] = 'e';
   int count = 0;
   for(i = 0; i < x; i++)
   {
       for(j = 0; j < y; j++)
       {
           for(k = 0; k < z; k++)
           {
               count++;
               printf("Count %d: b[%d][%d][%d]\tAddress = %p\tChar value = %c\n", count, i, j, k, &b[i][j][k], b[i][j][k]);
           }
       }
   }
}
