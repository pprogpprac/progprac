#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

pthread_mutex_t lock;
pthread_cond_t startCond0, startCond1, startCond2, startCond3, startCond4, startCond5, startCond6, startCond7, startCond8, startCond9;

int start0 = 0;
int start1 = 0;
int start2 = 0;
int start3 = 0;
int start4 = 0;
int start5 = 0;
int start6 = 0;
int start7 = 0;
int start8 = 0;
int start9 = 0;

struct buffer
{
  int idata;
  char cdata[100];
}buf;


void *w0(void *arg)
{
    int w0_idata = 0;
    char w0_cdata[100] = "0";
    pthread_mutex_lock(&lock);
    while(!start0)
    {
        pthread_cond_wait(&startCond0, &lock);
    }
    buf.idata = buf.idata + w0_idata;
    strcat(buf.cdata, w0_cdata);
    pthread_mutex_unlock(&lock);
    //start2 = 1;
    //pthread_cond_signal(&startCond2);
    pthread_exit(NULL);
}


void *w1(void *arg)
{
    int w1_idata = 1;
    char w1_cdata[100] = "1";
    pthread_mutex_lock(&lock);
    while(!start1)
    {
        pthread_cond_wait(&startCond1, &lock);
    }
    buf.idata = buf.idata + w1_idata;
    strcat(buf.cdata, w1_cdata);
    pthread_mutex_unlock(&lock);
    start2 = 1;
    pthread_cond_signal(&startCond2);
    pthread_exit(NULL);
}

void *w2(void *arg)
{
    int w2_idata = 2;
    char w2_cdata[100] = "2";
    pthread_mutex_lock(&lock);
    while(!start2)
    {
        pthread_cond_wait(&startCond2, &lock);
    }
    buf.idata = buf.idata * w2_idata;
    strcat(buf.cdata, w2_cdata);
    printf("t2 says: %d\n(t2 should say 28)\n\n", buf.idata);
    pthread_mutex_unlock(&lock);
    start9 = 1;
    pthread_cond_signal(&startCond9);
    pthread_exit(NULL);
}

void *w3(void *arg)
{
    int w3_idata = 3;
    char w3_cdata[100] = "3";
    pthread_mutex_lock(&lock);
    while(!start3)
    {
        pthread_cond_wait(&startCond3, &lock);
    }
    buf.idata = buf.idata + w3_idata;
    strcat(buf.cdata, w3_cdata);
    pthread_mutex_unlock(&lock);
    start1 = 1;
    pthread_cond_signal(&startCond1);
    pthread_exit(NULL);
}

void *w4(void *arg)
{
    int w4_idata = 4;
    char w4_cdata[100] = "4";
    pthread_mutex_lock(&lock);
    while(!start4)
    {
        pthread_cond_wait(&startCond4, &lock);
    }
    buf.idata = buf.idata / w4_idata;
    strcat(buf.cdata, w4_cdata);
    pthread_mutex_unlock(&lock);
    start5 = 1;
    pthread_cond_signal(&startCond5);
    pthread_exit(NULL);
}

void *w5(void *arg)
{
    int w5_idata = 5;
    char w5_cdata[100] = "5";
    pthread_mutex_lock(&lock);
    while(!start5)
    {
        pthread_cond_wait(&startCond5, &lock);
    }
    buf.idata = buf.idata + w5_idata;
    strcat(buf.cdata, w5_cdata);
    pthread_mutex_unlock(&lock);
    start0 = 1;
    pthread_cond_signal(&startCond0);
    pthread_exit(NULL);
}

void *w6(void *arg)
{
    int w6_idata = 6;
    char w6_cdata[100] = "6";
    pthread_mutex_lock(&lock);
    while(!start6)
    {
        pthread_cond_wait(&startCond6, &lock);
    }
    buf.idata = buf.idata + w6_idata;
    strcat(buf.cdata, w6_cdata);
    pthread_mutex_unlock(&lock);
    start4 = 1;
    pthread_cond_signal(&startCond4);
    pthread_exit(NULL);
}

void *w7(void *arg)
{
    int w7_idata = 7;
    char w7_cdata[100] = "7";
    pthread_mutex_lock(&lock);
    while(!start7)
    {
        pthread_cond_wait(&startCond7, &lock);
    }
    buf.idata = buf.idata + w7_idata;
    strcat(buf.cdata, w7_cdata);
    pthread_mutex_unlock(&lock);
    start8 = 1;
    pthread_cond_signal(&startCond8);
    pthread_exit(NULL);
}

void *w8(void *arg)
{
    int w8_idata = 8;
    char w8_cdata[100] = "8";
    pthread_mutex_lock(&lock);
    while(!start8)
    {
        pthread_cond_wait(&startCond8, &lock);
    }
    buf.idata = buf.idata / w8_idata;
    strcat(buf.cdata, w8_cdata);
    pthread_mutex_unlock(&lock);
    start6 = 1;
    pthread_cond_signal(&startCond6);
    pthread_exit(NULL);
}

void *w9(void *arg)
{
    int w9_idata = 9;
    char w9_cdata[100] = "9";
    pthread_mutex_lock(&lock);
    while(!start9)
    {
        pthread_cond_wait(&startCond9, &lock);
    }
    buf.idata = buf.idata - 28 + w9_idata;
    strcat(buf.cdata, w9_cdata);
    pthread_mutex_unlock(&lock);
    start7 =1;
    pthread_cond_signal(&startCond7);
    pthread_exit(NULL);
}

void main()
{
    buf.idata = 10;
    strcpy(buf.cdata,"main");

    pthread_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
    pthread_mutex_init(&lock, NULL);

    pthread_cond_init(&startCond0, NULL);
    pthread_cond_init(&startCond1, NULL);
    pthread_cond_init(&startCond2, NULL);
    pthread_cond_init(&startCond3, NULL);
    pthread_cond_init(&startCond4, NULL);
    pthread_cond_init(&startCond5, NULL);
    pthread_cond_init(&startCond6, NULL);
    pthread_cond_init(&startCond7, NULL);
    pthread_cond_init(&startCond8, NULL);
    pthread_cond_init(&startCond9, NULL);

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

    start3 = 1;
    pthread_cond_signal(&startCond3);

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
