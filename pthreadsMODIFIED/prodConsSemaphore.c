#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>

#define N 20
#define NUM_ITERATIONS 100
#define NUM_PRODSCONS 2
#define DONE (totalItems == NUM_ITERATIONS * NUM_PRODSCONS)

struct buffer_t {
  char data[N];
  int in;
  int out;
  pthread_mutex_t mutex;
  sem_t empty;
  sem_t full;
} buffer;

int totalItems = 0;

pthread_t producer[NUM_PRODSCONS], consumer[NUM_PRODSCONS];

void *produce(void *tid) {

  int i;
  for(i=0; i<NUM_ITERATIONS; i++) {
     sem_wait(&(buffer.full));
     pthread_mutex_lock(&(buffer.mutex));
     buffer.data[buffer.in] = rand();
     printf("producer %ld inserted an item: %d\n", (long)tid, buffer.data[buffer.in]);
     buffer.in = (buffer.in + 1) % N;
     sem_post(&(buffer.empty));
     pthread_mutex_unlock(&(buffer.mutex));
  }
  pthread_exit(NULL);
}

void *consume(void *tid) {

  int done = 0;
  int i;
  while(1) {
     sem_wait(&(buffer.empty));
     pthread_mutex_lock(&(buffer.mutex));
     if (DONE) {
        done = 1;
        pthread_mutex_unlock(&(buffer.mutex));
     }
     else {
       printf("consumer %ld removing an item: %d\n", (long)tid, buffer.data[buffer.out]);
       buffer.out = (buffer.out + 1) % N;
       totalItems++;
       sem_post(&(buffer.full));
       // Am I the lucky one to remove the very last item?
       // If so, I should be a responsible citizen :)
       if (DONE) {
	 done = 1;
          for(i=0; i < NUM_PRODSCONS - 1; i++)
	    sem_post(&(buffer.empty));
       }
       pthread_mutex_unlock(&(buffer.mutex));
     }
     if (done) break;
  }
  pthread_exit(NULL);
}




int main(char *argc[], int argv) {

   int failed, i;
   void *status;

   srand(time(NULL));

   pthread_mutex_init(&(buffer.mutex), NULL);
   sem_init(&(buffer.empty), 0, 0);
   sem_init(&(buffer.full), 0, N);
   buffer.in = 0;
   buffer.out = 0;

   for(i=0; i<NUM_PRODSCONS; i++) {
     failed = pthread_create(&(producer[i]), NULL,produce, (void*)(long)i);
      if (failed) {
         printf("thread_create failed!\n");
         return -1;
      }
   }

   for(i=0; i<NUM_PRODSCONS; i++) {
     failed = pthread_create(&consumer[i], NULL,consume,(void*)(long)i);
      if (failed) {
         printf("thread_create failed!\n");
         return -1;
      }
   }

   for(i=0; i<NUM_PRODSCONS; i++)
      pthread_join(producer[i], &status);

   for(i=0; i<NUM_PRODSCONS; i++)
      pthread_join(consumer[i], &status);

   pthread_exit(NULL);
}
