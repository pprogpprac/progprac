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
   int i = 1, j = 7, k = 7;
   char ***b;

   b = (char ***) malloc(i * sizeof(char**));
   for (i = 0; i < 1; i++)  {
       b[i] = (char**)malloc(j * sizeof(char*));
       for(j = 0; j < 7; j++)   {
           b[i][j] = (char*)malloc(k * sizeof(char));
       }
   }

   //b[0][0][0] = '5';
   //char *pb = malloc(sizeof(char));

   //char *pb;
   //pb = &b;

   //char *pbb = malloc(sizeof(char));

   //char **pbb;
   //pbb = &pb;

   //char *pbbb = malloc(sizeof(char));

   //char ***pbbb;
   //pbbb = &pbb;

   //printf("***pbbb = %c\n", ***pbbb);

   *b[0][4] = 'a';
   *b[0][0] = 'f';
   b[0][4][0] = 'e';

   for(i = 0; i < 1; i++)   {
       for(j = 0; j < 7; j++)   {
           for(k = 0; k < 7; k++)
               printf("b[%d][%d][%d] = %p \t %c\n", i, j, k, &b[i][j][k], b[i][j][k]);
       }
   }

   /*printf("Addresses involved:\n");
   printf("&b = %p\n", &b);
   printf("&b[] = %p\n", &b[0]);
   printf("&b[0][0] = %p\n", &b[0][0]);
   printf("&b[0][1] = %p\n", &b[0][1]);
   printf("&b[0][2] = %p\n", &b[0][2]);
   printf("&b[0][3] = %p\n", &b[0][3]);
   printf("&b[0][4] = %p\t *b[][] = %c\n", &b[0][4], *b[0][4]);
   printf("&b[0][5] = %p\n", &b[0][5]);
   printf("&b[][][] = %p\t b[][][] = %c\n", &b[0][0][0], b[0][0][0]);
   printf("&b[][][1] = %p\n", &b[0][0][1]);*/

   //pa = &a;
   //pb = &b;

   /*printf("a = %d and *pa = %d and pa = %p\n", a, *pa, pa);
   printf("b = %c and *pb = %c and pb = %p\n", b, *pb, pb);
   printf("pa = %p\n", ++pa);*/
}
