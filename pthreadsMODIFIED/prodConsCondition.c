#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define N 20
#define NUM_ITERATIONS 1
#define NUM_PRODSCONS 2
#define DONE (totalItems == NUM_ITERATIONS * NUM_PRODSCONS)

struct buffer_t
{
  char data[N];
  int in;
  int out;
  pthread_mutex_t mutex;
  pthread_cond_t empty;
  pthread_cond_t full;
} buffer;

int totalItems = 0;

#define EMPTY (buffer.in == buffer.out)
#define FULL ((buffer.in + 1) % N == buffer.out)

pthread_t producer[NUM_PRODSCONS], consumer[NUM_PRODSCONS];
pthread_t terminatorThread;

void *produce(void *tid)
{
  int i;
  for(i=0; i<NUM_ITERATIONS; i++)
  {
     printf("producer %ld going to grab the lock\n", (long)tid);
     pthread_mutex_lock(&(buffer.mutex));
     while (FULL)
     {
       printf("producer %ld is waiting\n", (long)tid);
       pthread_cond_wait(&(buffer.full), &(buffer.mutex));
     }
     if (EMPTY)
       pthread_cond_signal(&(buffer.empty));
     buffer.data[buffer.in] = rand();
     printf("producer %ld inserted an item: %d\n", (long)tid, buffer.data[buffer.in]);
     buffer.in = (buffer.in + 1) % N;
     pthread_mutex_unlock(&(buffer.mutex));
  }
  printf("producer %ld is done!\n", (long)tid);
  pthread_exit(NULL);
}

void *consume(void *tid)
{
  int done = 0;
  int i;
  while(1)
  {
     printf("consumer %ld will grab the lock\n", (long)tid);
     pthread_mutex_lock(&(buffer.mutex));
     if (DONE)
     {
        done = 1;
        printf("consumer %ld done 1\n", (long)tid);
        pthread_mutex_unlock(&(buffer.mutex));
     }
     else
     {
       while (EMPTY && !DONE)
       {
          printf("consumer %ld waiting\n", (long)tid);
          pthread_cond_wait(&(buffer.empty), &(buffer.mutex));
       }
       pthread_cond_signal(&(buffer.full));
       if (DONE)
       {
          done = 1;
          printf("consumer %ld done 2\n", (long)tid);
          pthread_mutex_unlock(&(buffer.mutex));
       }
       else
       {
	      printf("consumer %ld removing an item: %d count=%d\n", (long)tid, buffer.data[buffer.out], totalItems);
          buffer.out = (buffer.out + 1) % N;
          totalItems++;
          // Am I the lucky one to remove the very last item?
          // If so, I should be a responsible citizen :)
          if (DONE)
          {
             printf("consumer %ld is the lucky one!\n", (long)tid);
	         done = 1;
             for(i=0; i < NUM_PRODSCONS; i++)
	            pthread_cond_signal(&(buffer.empty));
          }
          pthread_mutex_unlock(&(buffer.mutex));
      }//else
   }//else
     if (done) break;
 }//while loop
  pthread_exit(NULL);
}//consumer function



int main(char *argc[], int argv)
{
   int failed, i;
   void *status;

   srand(time(NULL));

   pthread_mutex_init(&(buffer.mutex), NULL);
   pthread_cond_init(&(buffer.empty), NULL);
   pthread_cond_init(&(buffer.full), NULL);
   buffer.in = 0;
   buffer.out = 0;

   for(i=0; i<NUM_PRODSCONS; i++)
   {
      failed = pthread_create(&(producer[i]), NULL, produce, (void*)(long)i);
      if (failed)
      {
         printf("thread_create failed!\n");
         return -1;
      }
   }

   for(i=0; i<NUM_PRODSCONS; i++)
   {
      failed = pthread_create(&consumer[i], NULL,consume,(void*)(long)i);
      if (failed)
      {
         printf("thread_create failed!\n");
         return -1;
      }
   }


   for(i=0; i<NUM_PRODSCONS; i++)
      pthread_join(producer[i], &status);

   for(i=0; i<NUM_PRODSCONS; i++)
      pthread_join(consumer[i], &status);

   pthread_join(terminatorThread, &status);

   pthread_exit(NULL);
}
