#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>

void main()
{
    int a = 112;
    int *ptr;
    ptr = &a;
    printf("ptr = %d\n", *ptr);
}
