#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct data {
  int tid;
  char buffer[100];
} tdata1, tdata2;

/* If acquired, guarantees mutual exclusive access to shared data */
/* Should be released when done */
pthread_mutex_t lock;

/* Can represent conditions to wait on */
pthread_cond_t startCond;

/* Shared data */
int start = 0;
int totalMessageLength = 0;

/* Main function of pthreads */
void *worker(void *tdata) {
   struct data *d = (struct data*) tdata;
   printf("thread %d says %s\n", d->tid, d->buffer);
   pthread_mutex_lock(&lock);
   //while (!start)
   {
      printf("thread %d  sleeps until we can start\n", d->tid);
      pthread_cond_wait(&startCond, &lock);
   }
   totalMessageLength += strlen(d->buffer);
   pthread_mutex_unlock(&lock);
   pthread_exit(NULL);
}

/* Executed by the main thread */
int main(char *argc[], int argv) {
   int failed;
   pthread_t thread1, thread2;
   void *status1, *status2;
   pthread_mutex_init(&lock, NULL);
   pthread_cond_init(&startCond, NULL);

   /* Creates first thread */
   tdata1.tid = 1;
   strcpy(tdata1.buffer, "hello");
   failed = pthread_create(&thread1, NULL, worker, (void*)&tdata1);
   if (failed) {
      printf("thread_create failed!\n");
      return -1;
   }

   /* Creates second thread */
   tdata2.tid = 2;
   strcpy(tdata2.buffer, "world");
   failed = pthread_create(&thread2, NULL, worker, (void*)&tdata2);
   if (failed) {
      printf("thread_create failed!\n");
      return -1;
   }

   printf("Main thread is sleeping\n");
   sleep(1);
   printf("Main thread woke up!\n");


   /* Tell the threads that they can go ahead and update shared data */
   //pthread_mutex_lock(&lock);
   //start = 1;
   //pthread_cond_signal(&startCond);
   // pthread_cond_signal(&startCond);
   /* Or, a better way is to replace the above signals with a broadcast */
   /* if you really want to wake up all  waiting on the condition variale */
   pthread_cond_broadcast (&startCond);

   //pthread_mutex_unlock(&lock);


   /* Wait until thread 1 terminates */
   pthread_join(thread1, &status1);

   /* Wait until thread 2 terminates */
   pthread_join(thread2, &status2);

   printf("Total message length %d\n", totalMessageLength);
   pthread_exit(NULL);
}
