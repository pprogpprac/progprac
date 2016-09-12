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


void *maintf(void * arg)
{
    //int tid1 = gettid();
    int tid = syscall(SYS_gettid);
    printf("THREAD: My TID is %d\n", tid);
    //printf("THREAD: my PID is %d\n", getpid());
}

int main(int argc, char **argv)
{
   int ivar = 10;
   char cvar[100] = "main";

   pthread_t maint;
   //pthread_create(&maint, NULL, maintf, NULL);
   //pthread_join(maint, NULL);
   //pthread_create(&maint, NULL, maintf, NULL);

   int p1 = fork();
   if(p1 == 0)
   {
       int test = 7;
       printf("CHILD p1: My ID is %d\n", getpid());
       int p2 = fork();
       if(p2 == 0)
       {
           printf("CHILD p2: My ID is %d\n", getpid());
           //printf("CHILD p2:test (shud b 7) = %d\n", test);
       }
       else if(p2 < 0)
       {
           perror("perror: Fork failed !\n");
           printf("printf: Fork failed !\n");
       }
       else
       {
           wait();
           //printf("I am p2's parent: My ID is %d\n", getpid());
       }
   }
   else if(p1 < 0)
   {
       perror("perror: Fork failed !\n");
       printf("printf: Fork failed !\n");
   }
   else
   {
       wait();
       pthread_create(&maint, NULL, maintf, NULL);
       pthread_join(maint, NULL);
       printf("PARENT: My ID is %d\n", getpid());
   }
   //pthread_join(maint, NULL);
   exit(0);
}
