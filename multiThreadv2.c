/* ######################################### MULTITHREAD VERSION ####################################
####################### Modified by Naveen Rajaraman Iyer            ################################
####################### UFID: 60116379                               ################################
####################### Email: iyernaveenr@gmail.com ; niyer@ufl.edu ################################
####################### Date: 28th January, 2015                     ##############################*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


//----------------------------------------------  #DEFINE  --------------------------------------------

//If using line length of more than 2048 or if using block number of more than 3 digits or anything else, please make the change here !
#define LINE_LENGTH 2048
#define MAX_NUM_ARGS 200
#define MAXLINES 400
#define MAXARGLENGTH 100
#define SEM_COUNT 5
#define HUNDRED 100


//----------------------------------------------  MUTEX & CONDS  -------------------------------------------
/* If acquired, guarantees mutual exclusive access to shared data */
/* Should be released when done */
sem_t empty;
sem_t full;
pthread_mutex_t lock;

sem_t empty1;
sem_t full1;
pthread_mutex_t lock1;


//----------------------------------------------  SHARED DATA  -------------------------------------------
/* Shared/Global data */
FILE *instrfp;
char *arg2;
char *arg3;

char * tempArguments[MAX_NUM_ARGS];
char **bitnos[30];
int iteration = 1;
int blockSize;
int bufferSize;
int MAX_BLOCK_LENGTH = 1;

int numArgs;

long instrSize;
long inputSize;
long inputLines;
char linebuf[MAXLINES];

char *buffer;

char history[500];

int intTemp[HUNDRED], outintTemp[HUNDRED];
int pos[HUNDRED], outpos[HUNDRED];
int currNumArgs[12];
char *currOp[HUNDRED]; //operation list
char *currLine[HUNDRED]; //instructions list
char *outcontent;


//------------------------------------------  REGULAR FUNCTIONS  ----------------------------------------
void revert(char *tempBuffer, char *temptempArgs)
{
     int i;
     int kernel = 1 << atoi(temptempArgs);
     for(i = 0; i < blockSize; i++)
     {
         tempBuffer[i] ^= kernel;
     }
}

void zero(char *tempBuffer, char *temptempArgs)
{
     int i;
     int kernel = 1 << atoi(temptempArgs);
     for(i = 0; i < blockSize; i++)
     {
      tempBuffer[i] &= (~kernel);
     }
}

int getArguments(char * str, char * arg[], const char * delimeter) {
    char * temp = NULL;
    int i = 0;
    temp = strtok(str, delimeter);
    while (temp != NULL) {
        arg[i++] = temp;
        temp = strtok(NULL, delimeter);
    }
    arg[i] = NULL;
    return i;
}

//----------------------------------------------  FUNCTIONS OF THREADS  ----------------------------------
/* **************************** FUNCTION OF READER THREAD ***************************** */
void *readerfunc(void *arg)
{
    int i = 0;

    FILE *infp    = fopen(arg2, "r");
    int infd      = open(arg2, O_RDONLY);

    //printf("Inside reader function\n");
    while(fgets(linebuf, MAXLINES, infp) != NULL)
    {
        inputLines++;
    }

    //obtain the inputSize
    fseek(infp, 0, SEEK_END);
    inputSize = ftell(infp);
    fseek(infp, 0, SEEK_SET);

    //inputSize -= inputLines;
    printf("inputSize = %ld\n", inputSize);
    printf("inputLines = %ld\n", inputLines);

    if(inputSize == 0)
    {
        printf("Empty Input File!\n");
        exit(-1);
    }

    if(inputSize <= blockSize)
    {
        printf("Input data less than blocksize, truncating blocksize to input size!\n");
        blockSize = inputSize - 1;
    }

    char *string = calloc((inputSize + 1), sizeof(char));
    fread(string, inputSize, 1, infp);
    outcontent = string;
    fseek(infp, 0, SEEK_SET);

    char temp[500];

    // Perform as many read operations as the number of instructions
    for(i = 0; i < instrSize; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&lock);

        printf("Reader thread woke up !\n");

        printf("Input block to manipulate = %d\nHistory = %s\n", intTemp[i], history);

        sprintf(temp, " %d ", intTemp[i]);

        printf("Now checking history !\n");

        if(strstr(history, temp) == NULL) //if true then not found
        {
            printf("Block #%d NOT FOUND in the buffer\n", intTemp[i]);
            printf("Reading block from input file\n\n");
            //memcpy(&buffer[pos], &outcontent[pos], blockSize);
            fseek(infp, pos[i], SEEK_SET);
            fread(&buffer[pos[i]], sizeof (char), blockSize, infp);
            sprintf(history + strlen(history)," %d ", intTemp[i]);
        }
        else
        {
            printf("Block #%d FOUND in the buffer\n", intTemp[i]);
            printf("Reading block #%d from buffer\n\n", intTemp[i]);
        }
        sem_post(&(empty));
        pthread_mutex_unlock(&lock);
    }
   fclose(infp);
   pthread_exit(NULL);
}

/* **************************** FUNCTION OF PROCESSING THREAD ***************************** */
void *processingfunc(void *arg)
{
    int i = 0, j = 0;

    for(i = 0; i < instrSize; i++)
    {
        sem_wait(&(empty));
        pthread_mutex_lock(&lock);

        printf("Processing thread woke up\n");

        if((strcmp(currOp[i],"revert"))  == 0)
        {
            printf("revert function called\n");
            for(j = 3; j < currNumArgs[i]; j++)
            {
                revert(&buffer[pos[i]], bitnos[i][j-3]);
                //printf("In process!! bitnos[%d][%d] %s\n", i, (j-3), bitnos[i][j-3]);
            }
        }
        else if((strcmp(currOp[i],"zero"))  == 0)
        {
            printf("zero function called\n");
            for(j = 3; j < currNumArgs[i]; j++)
            {
                zero(&buffer[pos[i]], bitnos[i][j-3]);
                //printf("In process!! bitnos[%d][%d] %s\n", i, (j-3), bitnos[i][j-3]);
            }
        }
        else
        {
            printf("Invalid command detected in the instruction file !\n");
            exit(-1);
        }

        printf("Processing func unlocked !\n\n");
        sem_post(&(full));
        pthread_mutex_unlock(&lock);

        //Send data block to writer thread
        //sem_wait(&full1);
        //pthread_mutex_lock(&lock1);
        //not sending anything, everything's understood
        sem_post(&(empty1));
        //pthread_mutex_unlock(&(lock1));
    }//for loop
    pthread_exit(NULL);
}

/* **************************** FUNCTION OF WRITER THREAD ***************************** */
void *writerfunc(void *arg)
{
    int i = 0;
    FILE *outfp   = fopen(arg3, "a");
    int outfd     = open(arg3, O_WRONLY | O_CREAT | O_TRUNC);

    for(i = 0; i < instrSize; i++)
    {
      sem_wait(&(empty1));
      pthread_mutex_lock(&(lock1));

      printf("Writer thread woke up\n");
      memcpy(&outcontent[outpos[i]], &buffer[pos[i]], strlen(&buffer[pos[i]]));
      //fwrite(&buffer[pos[i]], sizeof(char), blockSize, &outcontent[outpos[i]]);

      sem_post(&(full1));
      pthread_mutex_unlock(&lock1);
    }
    fwrite(outcontent, sizeof(char), inputSize, outfp);
    fclose(outfp);
    pthread_exit(NULL);
}

//----------------------------------------------  MAIN  -------------------------------------------
/* Executed by the main thread */
int main(int argc, char *argv[])
{
    arg2 = calloc(MAXARGLENGTH, sizeof(char));
    arg3 = calloc(MAXARGLENGTH, sizeof(char));
    int i;

    if(argc == 6)
    {
        instrfp = fopen(argv[1], "r");
        arg2 = argv[2];
        arg3 = argv[3];
        blockSize     = atoi(argv[4]);
        bufferSize    = atoi(argv[5]);
    }
    else
    {
        printf("Please enter total 6 command line arguments\n");
        exit(1);
    }

    if(bufferSize < 1)
    {
        printf("Buffer size should be greater than zero. Note that buffer size = # of blocks.\n");
        exit(1);
    }

    buffer = calloc((bufferSize * blockSize + 1), sizeof(char));
    outcontent = calloc((inputSize + 1), sizeof(char));

    printf("instructionFileName = %s\n", argv[1]);
    printf("inputDataFileName = %s\n", argv[2]);
    printf("outputDataFilename = %s\n", argv[3]);
    printf("blockSize = %d\n", blockSize);
    printf("bufferSize = %d blocks\n", bufferSize);

    void *status = malloc(sizeof(void) * 1000);

    pthread_mutex_init(&(lock), NULL);
    sem_init(&(empty), 0, 0);
    sem_init(&(full), 0, SEM_COUNT);

    pthread_mutex_init(&(lock1), NULL);
    sem_init(&(empty1), 0, 0);
    sem_init(&(full1), 0, SEM_COUNT);

    char tempLine[LINE_LENGTH + 1];

    while(fgets(tempLine, LINE_LENGTH, instrfp) != NULL)
    {
        instrSize++;
    }

    printf("instrSize = %ld\n", instrSize);

    if(instrSize == 0)
    {
        printf("No instruction found. Copying input data file content into output data file.\n");
    }
    fseek(instrfp, 0, SEEK_SET);

    int k = 0;

    for(i = 0; i < instrSize; i++)
    {
        currOp[i] = calloc(10, sizeof(char));
        currLine[i] = calloc(30, sizeof(char));
        bitnos[i] = calloc(100, sizeof(char));
        for(k = 0; k < instrSize; k++)
            bitnos[i][k] = calloc(80, sizeof(char));
    }

    i = 0;
    k = 0;


    while(fgets(tempLine, LINE_LENGTH, instrfp) != NULL)
    {
        printf("Mains while loop iteration number %d\n", i+1);
        if(i >= instrSize)
            break;

        numArgs = getArguments(tempLine, tempArguments, " ");

        if(!numArgs)
        {
            printf("No arguments\n");
        }

        for(k = 3; k < numArgs; k++)
        {
            if(tempArguments[k] == NULL)
                break;

            memcpy(bitnos[i][k-3], tempArguments[k], strlen(tempArguments[k]));
            //bitnos[i][k - 3] = tempArguments[k];
            printf("bitnos[%d][%d] = %s\n", i, k-3, bitnos[i][k-3]);
        }

        currNumArgs[i] = numArgs;

        intTemp[i] = atoi(tempArguments[1]);
        pos[i] = ((intTemp[i] - 1) * blockSize);

        outintTemp[i] = atoi(tempArguments[2]);
        outpos[i] = ((outintTemp[i] - 1) * blockSize);

        strcpy(currOp[i], tempArguments[0]);
        strcpy(currLine[i], tempLine);
        i++;
    }

    int rjoin, pjoin, wjoin;
    int failed;
    pthread_t readert, writert, processingt;

    /* Creates reader thread */
    failed = pthread_create(&readert, NULL, readerfunc, NULL);
    if (failed) {
      printf("thread_create failed!\n");
      return -1;
    }

    /* Creates processing thread */
    failed = pthread_create(&processingt, NULL, processingfunc, NULL);
    if (failed) {
      printf("thread_create failed!\n");
      return -1;
   }

    /* Creates writer thread */
    failed = pthread_create(&writert, NULL, writerfunc, NULL);
    if (failed) {
       printf("thread_create failed!\n");
       return -1;
    }

    //Wait for reader thread to terminate
    rjoin = pthread_join(readert, &status);
    if(rjoin != 0)
    {
        perror("can't rjoin");
    }

    //Wait for processing thread to terminate
    pjoin = pthread_join(processingt, &status);
    if(pjoin != 0)
    {
        perror("can't pjoin");
    }

    //Wait for writer thread to terminate
    wjoin = pthread_join(writert, &status);
    if(wjoin != 0)
    {
        perror("can't wjoin");
    }
    ///////////////////////////////////////////////////////////////////////////////////

   fclose (instrfp);
   printf("Files closed successfully!\n");
   pthread_exit(NULL);
   return 0;
}
