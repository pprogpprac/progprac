#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(char *argv[], int arg) {
   int i;

   printf("Hello world!\n");
   printf("Ever wondered which syscalls are issued by a simple program like this?\n");
   printf("Make sure to have gcc realHelloWorld.c -o helloWorld in the current working directory\n");
   printf("Press a key to continue \n");
   getchar();
   pid_t pid = fork();
   if (pid == 0) {
      execlp("strace", "strace", "./helloWorld", NULL);
      perror("execve");
      return 1;
   }
   else {
     int status;
     wait(&status);
     if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        printf("Hope you liked it!\n");
     else 
       printf("Oops..something went wrong!\n");
   }
}
