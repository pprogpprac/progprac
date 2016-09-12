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
pthread_cond_t workerCond;
pthread_cond_t lolCond;
pthread_cond_t chuCond;

/* Shared data */
int var = 0;
int lolstate = 0;
int chustate = 0;
int workerstate = 0;


void *workerfunc(void *arg)
{
    pthread_mutex_lock(&lock);
    while(workerstate == 0)
    {
    printf("Worker thread waiting on workerCond\n");
    pthread_cond_wait(&workerCond, &lock);
    }
    printf("Worker thread woke up ! Making var = 1\n");
    var = 1;
    //printf("Worker thread Updated: var = %d \n", var);

    //pthread_cond_signal(&lolCond);
    //lolstate = 1;

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}


void *chufunc(void *arg)
{
    pthread_mutex_lock(&lock);
    while(chustate == 0)
    {
    printf("Chu thread waiting on chuCond\n");
    pthread_cond_wait(&chuCond, &lock);
    }

    printf("Chu thread woke up ! Multiplying existing var with 2\n");
    var *= 2;
    //printf("Chu thread Updated: var = %d \n", var);

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}


void *lolfunc(void *arg)
{
   pthread_mutex_lock(&lock);

   while(lolstate == 0)
   {
    printf("Lol thread waiting on lolCond\n");
    pthread_cond_wait(&lolCond, &lock);
    }
   printf("lol thread woke up ! Adding existing var with 3\n");
   var += 3;
   //printf("Lol thread Updated: var = %d \n", var);

   //pthread_cond_signal(&chuCond);
   //chustate = 1;

   pthread_mutex_unlock(&lock);
   pthread_exit(NULL);
}


/* Executed by the main thread */
int main(int argc, char **argv)
{

   int failed;
   pthread_t workert, lolt, chut;
   void *status1, *status2, *status3;

   pthread_mutex_init(&lock, NULL);

   pthread_cond_init(&workerCond, NULL);
   pthread_cond_init(&lolCond, NULL);
   pthread_cond_init(&chuCond, NULL);

   printf("Main thread: Creating threads !\nvar = %d\n", var);

   /* Creates first thread */
   failed = pthread_create(&workert, NULL, workerfunc, NULL);
   if (failed) {
      printf("worker_thread_create failed!\n");
      return -1;
   }

   /* Creates second thread */
   failed = pthread_create(&lolt, NULL, lolfunc, NULL);
   if (failed) {
      printf("lol_thread_create failed!\n");
      return -1;
   }

   /* Creates third thread */
   failed = pthread_create(&chut, NULL, chufunc, NULL);
   if (failed) {
      printf("chu_thread_create failed!\n");
      return -1;
   }

   //printf("\n\n************* Main thread sleeping...!\n\n");
   printf("\n\n************* Main thread woke up! *************\nvar = %d\n", var);

   pthread_mutex_lock(&lock);
   pthread_cond_signal(&workerCond);
   workerstate = 1;
   lolstate = 0;
   chustate = 0;
   pthread_mutex_unlock(&lock);
   pthread_join(workert, &status1);
   printf("worker thread joined ! var = %d\n", var);

   pthread_mutex_lock(&lock);
   pthread_cond_signal(&lolCond);
   lolstate = 1;
   workerstate = 0;
   chustate = 0;
   pthread_mutex_unlock(&lock);
   pthread_join(lolt, &status2);
   printf("lol thread joined ! var = %d\n", var);

   pthread_mutex_lock(&lock);
   pthread_cond_signal(&chuCond);
   chustate = 1;
   lolstate = 0;
   workerstate = 0;
   pthread_mutex_unlock(&lock);
   pthread_join(chut, &status3);
   printf("chu thread joined ! var = %d\n", var);

   /*pthread_join(workert, &status1);
   printf("worker thread joined !\n");
   pthread_join(lolt, &status2);
   printf("lol thread joined !\n");
   pthread_join(chut, &status3);
   printf("chu thread joined !\n");*/

   printf("Value of var = %d\n", var);
   pthread_exit(NULL);
}
