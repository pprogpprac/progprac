#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void ignore(int signo) {
  // printf is not reentrant! So better not to use it in a signal handler
  //printf("Sorry, not done yet!\n");
  write(STDOUT_FILENO, "Sorry, not done yet!\n",22);
}

int main(char *argc[], int argv) {

  struct sigaction sa, saOld;

  sa.sa_handler = ignore;
  printf("Try killing me with a CTRL-C whenever you like\n");
  sigaction(SIGINT, &sa, &saOld);
  //printf("Try killing me with a CTRL-C whenever you like\n");
  pause();
  printf("Please try again!\n");
  sigaction(SIGINT, &saOld, NULL);
  pause();
  printf("Here you go!\n");
  return 0;
}
