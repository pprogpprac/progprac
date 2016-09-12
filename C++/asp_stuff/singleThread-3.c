/* #################################### SINGLE THREAD #################################### 
####################### Modified by Naveen Rajaraman Iyer            ##############################
####################### UFID: 60116379                               ##############################
####################### Email: iyernaveenr@gmail.com ; niyer@ufl.edu ##############################
####################### Date: 28th January, 2015                     ##############################*/
#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

//If using line length of more than 2048 or if using block number of more than 3 digits or anything else, please make the change here !
#define LINE_LENGTH 20480
#define MAX_NUM_ARGS 2000
#define MAXLINES 4000
//#define MAX_BLOCK_LENGTH 1

//GLOBAL VARIABLES
int blockSize;
int bufferSize;
int pos, outpos;
int MAX_BLOCK_LENGTH = 1;

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

/* Reads a line and discards the end of line character */
int getLine(char * str, int max, FILE * fp) {
    char * temp;
    if ((temp = fgets(str, max, fp)) != NULL) {
        int len = strlen(str);
        str[len - 1] = '\0';
        return len - 1;
    }
    else return -1;
}

int getArguments(char * str, char * arg[],
    const char * delimeter) {
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

int main(int argc, char **argv) 
{
    FILE *instrfp = fopen(argv[1], "r");
    FILE *infp    = fopen(argv[2], "r");
    FILE *outfp   = fopen(argv[3], "a");

    long inputLines = 0;
    char linebuf[MAXLINES];
    while(fgets(linebuf, MAXLINES, infp) != NULL)
    {
        inputLines++;
    }

    int infd      = open(argv[2], O_RDONLY);
    int outfd     = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC);
    
    blockSize     = atoi(argv[4]);
    bufferSize    = atoi(argv[5]);

    printf("instructionFileName = %s\n", argv[1]);
    printf("inputDataFileName = %s\n", argv[2]);
    printf("outputDataFilename = %s\n", argv[3]);
    printf("blockSize = %d\n", blockSize);
    printf("bufferSize = %d\n", bufferSize);

    int res, intTemp, outintTemp, i, loop;
    
    long inputSize;
    long instrSize = 0;
    
    //Copy the input file content into output buffer without any modifications
    fseek(infp, 0, SEEK_END);
    inputSize = ftell(infp);
    fseek(infp, 0, SEEK_SET);

    //inputSize -= inputLines;
    printf("inputSize = %ld\n", inputSize);
    
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
    char *outbuffer = calloc((inputSize + 1), sizeof(char));
    char *buffer = calloc((inputSize + 1), sizeof(char));
    
    fread(string, inputSize, 1, infp);
    outbuffer = string;
    
    char * tempArguments[MAX_NUM_ARGS];
    char tempLine[LINE_LENGTH + 1];
    
    int iteration = 1;
    int count = 0;
    
    while(fgets(tempLine, LINE_LENGTH, instrfp) != NULL)
    {
        instrSize++;
    }
    
    printf("instrSize = %ld\ninputLines = %ld\n", instrSize, inputLines);

    if(instrSize == 0)
    {
	printf("No instruction found. Copying input data file content into output data file.\n");
    }
    fseek(instrfp, 0, SEEK_SET);

    char history[500];
 
    while(fgets(tempLine, LINE_LENGTH, instrfp) != NULL)
    { 
        if(strlen(tempLine) == 0)
             break;

        printf("\n-----Iteration #%d-----\n", iteration);
  	if(strcmp(tempLine, "\n") == 0)
		break;
    
    	if(res < 0)
	{
        	printf("Nothing else to read\n");
        }

    	int numArgs = getArguments(tempLine, tempArguments, " ");

    	if(!numArgs)
    	{
        	printf("No arguments\n");
    	}

    	intTemp = atoi(tempArguments[1]);
    	pos = ((intTemp - 1) * blockSize);
	
	outintTemp = atoi(tempArguments[2]);
    	outpos = ((outintTemp - 1) * blockSize);

        printf("Input block to manipulate = %s and history = %s\n",tempArguments[1], history);

	char temp[500];

	sprintf(temp, " %s ", tempArguments[1]);

	if(strstr(history, temp) == NULL) //if true then not found
	{
		printf("Block #%s NOT FOUND in the input buffer\n", tempArguments[1]);
		fseek(infp, pos, SEEK_SET);
		fread(&buffer[pos], sizeof (char), blockSize, infp);	    	
		printf("Reading block from input file\n");
		sprintf(history + strlen(history)," %s ", tempArguments[1]);
	}
	else
	{
		printf("Block #%s FOUND in the input buffer\n", tempArguments[1]);
		printf("Reading block #%s from input buffer\n", tempArguments[1]); 
	}
       
        //printf("Input buffer content b4 operation:\n%s\n", &buffer[pos]);  
 
        if((strcmp(tempArguments[0],"revert"))  == 0)
	{
		for(i = 3; i < numArgs; i++)
                {
       	    		revert(&buffer[pos], tempArguments[i]);
	        }
	}
	else if((strcmp(tempArguments[0],"zero"))  == 0)
	{
		for(i = 3; i < numArgs; i++)
       	        {
       	    		zero(&buffer[pos], tempArguments[i]);
	        }
    	}
	else
	{
		printf("Invalid command detected in the instruction file !\n");
		exit(-1);
	}

      
	//sprintf(buffer + strlen(buffer), "\n");
        //printf("Input buffer content after operation:\n%s\n", &buffer[pos]);
	memcpy(&outbuffer[outpos], &buffer[pos], strlen(&buffer[pos]));    
  
	iteration++;
        printf("\n");
    }//while
   
    //Writing to output file
    fwrite(outbuffer, sizeof(char), inputSize, outfp);

    fclose (instrfp);
    fclose (infp);
    fclose (outfp);

    printf("Files closed successfully!\n");
    return 0;
}
