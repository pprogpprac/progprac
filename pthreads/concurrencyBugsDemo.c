#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct data {
  int tid;
  char buffer[100];
} tdata1, tdata2;


pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_cond_t cond1;
pthread_cond_t cond2;

/* Shared data */
int mySharedCounter = 0;
int go1 = 0;
int go2 = 0;

void helper(void *tdata, pthread_mutex_t *l1, pthread_cond_t *c1, int *goP1, pthread_mutex_t *l2, pthread_cond_t *c2, int *goP2) {
   struct data *d = (struct data*) tdata;
   pthread_mutex_lock(l1);
   while (!(*goP1)) {
     printf("thread %d  sleeps until condition %lu set\n", d->tid, (long)goP1);
      pthread_cond_wait(c1, l1); 
   }
   sleep(5);
   pthread_mutex_lock(l2);
   while (!(*goP2)) {
     printf("thread %d  sleeps until condition %lu set \n", d->tid, (long)goP2);
      pthread_cond_wait(c2, l2); 
   } 
   mySharedCounter++;
   printf("thread %d performed its critical region and exiting ..\n", d->tid);
   pthread_mutex_unlock(l2);
   pthread_mutex_unlock(l1);
   pthread_exit(NULL);  
}


void *worker1(void *tdata) {
   struct data *d = (struct data*) tdata;
   printf("thread %d says %s\n", d->tid, d->buffer); 
   helper(d, &lock1, &cond1, &go1, &lock2, &cond2, &go2);
   pthread_exit(NULL);
}

void *worker2(void *tdata) {
   struct data *d = (struct data*) tdata;
   printf("thread %d says %s\n", d->tid, d->buffer); 
   helper(d, &lock2, &cond2, &go2, &lock1, &cond1, &go1);
   pthread_exit(NULL);
}

/* Executed by the main thread */
int main(char *argc[], int argv) {
   int failed;
   pthread_t thread1, thread2;
   void *status1, *status2;
   pthread_mutex_init(&lock1, NULL);   
   pthread_mutex_init(&lock2, NULL);

   /* Creates first thread */
   tdata1.tid = 1;
   strcpy(tdata1.buffer, "hello");     
   failed = pthread_create(&thread1, NULL, worker1, (void*)&tdata1);
   if (failed) {
      printf("thread_create failed!\n");
      return -1;
   }

   /* Creates second thread */ 
   tdata2.tid = 2;
   strcpy(tdata2.buffer, "world");
   failed = pthread_create(&thread2, NULL, worker2, (void*)&tdata2);
   if (failed) {
      printf("thread_create failed!\n");
      return -1;
   }

   printf("Main thread is sleeping\n");
   sleep(5);
   printf("Main thread woke up!\n");


   /* Tell the threads that they can go ahead and update shared data */
   pthread_mutex_lock(&lock1);
   go1 = 1;
   pthread_cond_broadcast (&cond1); 
   pthread_mutex_unlock(&lock1);
   pthread_mutex_lock(&lock2);
   go2 = 1;
   pthread_cond_broadcast (&cond2); 
   pthread_mutex_unlock(&lock2);

   /* Wait until thread 1 terminates */
   pthread_join(thread1, &status1);

   /* Wait until thread 2 terminates */
   pthread_join(thread2, &status2);

   printf("If you see this message, we were lucky!\n");

   pthread_exit(NULL);
}

