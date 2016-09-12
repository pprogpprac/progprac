#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

pthread_mutex_t lock;
//sem_t empty;
//sem_t full;
sem_t start0, start1, start2, start3, start4, start5, start6, start7, start8, start9;

struct buffer
{
  int idata;
  char cdata[100];
}buf;


void *w0(void *arg)
{
    int w0_idata = 0;
    char w0_cdata[100] = "0";
    sem_wait(&start0);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata + w0_idata;
    strcat(buf.cdata, w0_cdata);
    //sem_post(NULL);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}


void *w1(void *arg)
{
    int w1_idata = 1;
    char w1_cdata[100] = "1";
    sem_wait(&start1);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata + w1_idata;
    strcat(buf.cdata, w1_cdata);
    sem_post(&start2);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w2(void *arg)
{
    int w2_idata = 2;
    char w2_cdata[100] = "2";
    sem_wait(&start2);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata * w2_idata;
    strcat(buf.cdata, w2_cdata);
    printf("t2 says: %d\n(t2 should say 28)\n\n", buf.idata);
    sem_post(&start9);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w3(void *arg)
{
    int semcheck;
    int w3_idata = 3;
    char w3_cdata[100] = "3";
    sem_wait(&start3);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata + w3_idata;
    strcat(buf.cdata, w3_cdata);
    sem_post(&start1);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w4(void *arg)
{
    int w4_idata = 4;
    char w4_cdata[100] = "4";
    sem_wait(&start4);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata / w4_idata;
    strcat(buf.cdata, w4_cdata);
    sem_post(&start5);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w5(void *arg)
{
    int w5_idata = 5;
    char w5_cdata[100] = "5";
    sem_wait(&start5);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata + w5_idata;
    strcat(buf.cdata, w5_cdata);
    sem_post(&start0);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w6(void *arg)
{
    int w6_idata = 6;
    char w6_cdata[100] = "6";
    sem_wait(&start6);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata + w6_idata;
    strcat(buf.cdata, w6_cdata);
    sem_post(&start4);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w7(void *arg)
{
    int w7_idata = 7;
    char w7_cdata[100] = "7";
    sem_wait(&start7);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata + w7_idata;
    strcat(buf.cdata, w7_cdata);
    sem_post(&start8);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w8(void *arg)
{
    int w8_idata = 8;
    char w8_cdata[100] = "8";
    sem_wait(&start8);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata / w8_idata;
    strcat(buf.cdata, w8_cdata);
    sem_post(&start6);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *w9(void *arg)
{
    int w9_idata = 9;
    char w9_cdata[100] = "9";
    sem_wait(&start9);
    pthread_mutex_lock(&lock);
    buf.idata = buf.idata - 28 + w9_idata;
    strcat(buf.cdata, w9_cdata);
    sem_post(&start7);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void main()
{
    buf.idata = 10;
    strcpy(buf.cdata, "main");

    pthread_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
    pthread_mutex_init(&lock, NULL);
    //sem_init(&empty, 0, 0);
    //sem_init(&full, 0, 0);
    sem_init(&start0, 0, 0);
    sem_init(&start1, 0, 0);
    sem_init(&start2, 0, 0);
    sem_init(&start3, 0, 0);
    sem_init(&start4, 0, 0);
    sem_init(&start5, 0, 0);
    sem_init(&start6, 0, 0);
    sem_init(&start7, 0, 0);
    sem_init(&start8, 0, 0);
    sem_init(&start9, 0, 0);

    pthread_create(&t0, NULL, w0, NULL);
    pthread_create(&t1, NULL, w1, NULL);
    pthread_create(&t2, NULL, w2, NULL);
    pthread_create(&t3, NULL, w3, NULL);
    pthread_create(&t4, NULL, w4, NULL);
    pthread_create(&t5, NULL, w5, NULL);
    pthread_create(&t6, NULL, w6, NULL);
    pthread_create(&t7, NULL, w7, NULL);
    pthread_create(&t8, NULL, w8, NULL);
    pthread_create(&t9, NULL, w9, NULL);

    sem_post(&start3);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);
    pthread_join(t9, NULL);

    printf("buf.idata = %d\n", buf.idata);
    printf("buf.cdata = %s\n", buf.cdata);
    if(buf.idata == 7 && strcmp(buf.cdata, "main3129786450") == 0)
    {
        printf("Synchronization successful !\n");
    }
    else
    {
        printf("Synchronization failed.\n");
    }
    pthread_exit(NULL);
}
