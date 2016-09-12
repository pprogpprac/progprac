/* #################################### EXTREMELY SIMPLE SHELL #################################### 
####################### Modified by Naveen Rajaraman Iyer            ##############################
####################### UFID: 60116379                               ##############################
####################### Email: iyernaveenr@gmail.com ; niyer@ufl.edu ##############################
####################### Date: 19th January, 2015                     ##############################*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Additional header files
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define COMMAND_LINE_LENGTH 200
#define COMMAND_LENGTH 10
#define MAX_NUM_ARGS 10

//Global variable
int fd[2]; //file descriptor

/* Breaks the string pointed by str into words and stores them in the arg array*/
int getArguments(char *,char *[]);

/* Reads a line and discards the end of line character */
int getLine(char *str,int max);

int createChild(char *arg[], int dirn, char *opFile[])
{
      pid_t pid = fork();
      switch (pid)
      {
          case 0: /* Executed by the child process only */ 
                  
                  if(dirn == 1) //dirn, that is, direction is to the left of delimiter
		  {
                      close(fd[0]);
                      dup2(fd[1],1);
                  }
                  else  //dirnection is to the right hand side of delimiter
		  {
                      close(fd[1]);
                      dup2(fd[0],0);
                      
		      //for the output.txt file and its permissions
                      int fileD = open(opFile[0], O_WRONLY | O_CREAT, 0644); //0644 = file permissions
		      /*rwx oct   meaning
			--- ---   -------
			001 1   = execute
			010 2   = write
			011 3   = write & execute
			100 4   = read
			101 5   = read & execute
			110 6   = read & write
			111 7   = read & write & execute
			So 0644 is:
	
			* (owning) User: read & write
			* Group: read
			* Other: read*/
                      dup2(fileD, 1);
                  }
                  execvp(arg[0],arg);
                  perror("Exec error\n");
                  exit(1);

          case -1: /* Executed only when the fork system call fails */
                  perror("Fork error\n");
                  return -1;
                  break;

          default: /* Executed by parent process only  */
                  //wait(&status);
                  return 0;
                  break;        
      } 
}


/* Simulates a shell, i.e., gets command names and executes them */
int main(int argc, char *argv[])
{

  char commandLine[COMMAND_LINE_LENGTH+1]; 
  char *args1[MAX_NUM_ARGS];
  char *args2[MAX_NUM_ARGS];
  char *args3[MAX_NUM_ARGS];
  char *arguments[MAX_NUM_ARGS];
  
  printf("Welcome to Extremely Simple Shell\n");

  do { 
      int status, m = 0, countredir = 0, countpipe = 0;
      char *temp = NULL;
      
      /* Prints the command prompt */
      printf("\n$ ");
      
      /* Reads the command line and stores it in array commandLine */
      getLine(commandLine,COMMAND_LINE_LENGTH+1);
      //printf("You entered the following string in command line:\n%s\n", commandLine);
      
      /* Break the string entered in command line into 3 tokens, viz., cmd1Str, cmd2Str and cmd3Str */
      char * cmd1Str;	// cmd1Str = Command 1 String
      char * cmd2Str;	// cmd2Str = Command 2 String
      char * cmd3Str;	// cmd3Str = Command 3 String
	
      /* For breaking the string entered in command line specifically at output file command delimiter*/
      char * token;

      /* The user did not enter any commands */
        if (!strcmp(commandLine,""))
           continue;
      	
      /* Check validity/compatibility/feasibility of the string entered at command line */
      for(m=0; m<strlen(commandLine); m++)
      {
	if(commandLine[m] == '>')
	{
		countredir++;
	}
	if(commandLine[m] == '|')
	{
		countpipe++;
	}
      }
      printf("countredir = %d\tcountpipe = %d\n", countredir, countpipe);
 
      /* When the string entered on command line is a single command without redirection */
      if((countredir < 1) && (countpipe < 1))
      {
	printf("You didn't enter any delimiter\n");
	printf("First and only command  : %s \n", commandLine);
	/* Breaks the command line into arguments and stores the arguments in arguments array */
        int numArgs1 = getArguments(commandLine, arguments);
	int pid = fork();
      	switch (pid)
      	{
          case 0: /* Executed by the child process only */ 
                  execvp(arguments[0],arguments);
                  perror("Exec error\n");
                  exit(1);
          case -1: /* Executed only when the fork system call fails */
                  perror("Fork error\n");
		  return -1;
                  break;
          default: /* Executed by parent process only  */
                  wait(&status);
		  return 0;
                  break;        
        }//switch
      }

      /* When the string entered on command line contains multiple commands with redirection */
      else if((countredir > 0) && (countpipe > 0))
      { 
	printf("You entered 2 valid delimiters\n");
	/* Break the string entered in command line at the delimiter ">" */
      	char delimiter[] = ">";

	temp = strtok(commandLine,delimiter); //Create token from beginning until delimiter reached
	token = temp;			      //Update "token" with the token
     	
        temp = strtok(NULL,delimiter);	      //Create token from where the previous one was left until delimiter reached
        cmd3Str = temp;
	
	/* Next, break the "token" string entered in command line at the delimiter "|" */
        strcpy(delimiter, "|");
    
        temp = strtok(token,delimiter);
        cmd1Str = temp; 			//cmd1Str is the string to the left of the delimiter

        temp = strtok(NULL,delimiter);
        cmd2Str = temp;				//cmd2Str is the string to the right of the delimiter
     		
 	printf("First command  : %s \n", cmd1Str);
        printf("Second command : %s \n", cmd2Str);
        printf("Output file    : %s \n", cmd3Str);
      
        /* Breaks the command line into arguments and stores the arguments in arguments array */
        int numArgs = getArguments(cmd1Str,args1); // update "args1" (stores all arguments of the command into args1)
     	    numArgs = getArguments(cmd2Str,args2); // update "args2"
            numArgs = getArguments(cmd3Str,args3); // update "args3"
      
        /* Terminates the program when the user types exit or quit */
        if (!strcmp(args1[0],"quit") || !strcmp(args1[0],"exit"))
           break;
      
        //pipe before fork !
        pipe(fd);     
      
        createChild(args1, 1, args3); //dirn, that is, direction is to the left of delimiter
        createChild(args2, 0, args3); //direction is to the right hand side of delimiter
      }
	
      else if(countpipe > 0)
      {
	printf("You entered only one valid delimiter\n");
	char delimiter[] = "|";

        temp = strtok(commandLine,delimiter); //Create token from beginning until delimiter reached
	cmd1Str = temp;
     	
        temp = strtok(NULL,delimiter);	      //Create token from where the previous one was left until delimiter reached
        cmd2Str = temp;
     		
 	printf("First command  : %s \n", cmd1Str);
        printf("Second command : %s \n", cmd2Str);

	/* Breaks the command line into arguments and stores the arguments in arguments array */
        int numArgs = getArguments(cmd1Str,args1); // update "args1" (stores all arguments of the command into args1)
     	    numArgs = getArguments(cmd2Str,args2); // update "args2"
      
        /* Terminates the program when the user types exit or quit */
        if (!strcmp(args1[0],"quit") || !strcmp(args1[0],"exit"))
           break;
      
        //pipe before fork !
        pipe(fd);     

	pid_t pid1 = fork();

      	if(pid1 == 0)
      	{
		printf("Executing first command\n");
                close(fd[0]);
                dup2(fd[1],1);
		execvp(args1[0], args1);
                perror("Exec error\n");
                exit(1);       
        }
	else if(pid1 < 0)
		perror("Couldn't create 1st child\n");
	else
	{
		wait(&status);
		//waitpid(pid1, &status, -1);
	}

	printf("Executing second command\n");
	close(fd[1]);
        dup2(fd[0],0);
	execvp(args2[0], args2);
        perror("Exec error\n");
        exit(1);
     }//else if
     else
     {
	printf("Commands you entered were not the ones expected :P \n");
	break;
     }
  }while (1); /* Use int values to represent boolean in C language: 0 denotes false, non-zero denotes true */
  return 0;
}


/* Breaks the string pointed by str into words and stores them in the arg array*/
int getArguments(char *str, char *arg[])
{
     char delimiter[] = " ";
     char *temp = NULL;
     int i=0;
     temp = strtok(str,delimiter);
     while (temp != NULL)
     {
           arg[i++] = temp;                   
           temp = strtok(NULL,delimiter);
     }
     arg[i] = NULL;     
     return i;
}

/* Reads a line and discards the end of line character */
int getLine(char *str,int max)
{
    char *temp;
    if ((temp = fgets(str,max,stdin)) != NULL)
    {
       int len = strlen(str);
       str[len-1] = '\0';
       return len-1;
    }   
    else return 0;
}
