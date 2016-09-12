#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>


int main(int argc, char **argv)
{
   int a = atoi(argv[1]);
   int b = atoi(argv[2]);
   //printf("If a = 21 and b = 37, then ur script worked !\n");
   printf("a = %d and b = %d\n", a, b);
   if((a == 21) && (b == 37))
       printf("Ur script worked !\n");
   else
       printf("FAILED ! :(\n");
}
