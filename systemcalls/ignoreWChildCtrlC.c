#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void ignore(int signo) {
  //printf is not reentrant! So better not to use it in a signal handler
  //printf("Sorry, not done yet!\n"); 
  write(STDOUT_FILENO, "Sorry, not done yet!\n" ,22);
}

int main(char *argc[], int argv) {

  struct sigaction sa, saOld;

  sa.sa_handler = ignore;
  sigaction(SIGINT, &sa, &saOld);
  printf("Try killing us with a CTRL-C whenever you like\n");
  pid_t pid = fork();
  if (pid > 0) {
     pause();
     printf("Child status=%s\n", (WIFSIGNALED(pid) ? "signaled" : "not signaled"));
     printf("Please try again!\n");
     sigaction(SIGINT, &saOld, NULL);
     pause();
     printf("Here you go!\n");
  }
  else if (pid == 0) {
    pause();
    pause();
  }
  else perror("fork");
  return 0;
}

