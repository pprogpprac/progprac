#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define BUFFER_SIZE 100

pid_t pid; 
int finished = 0;
int woken = 0;

void child_handler(int signo) 
{
   if (signo == SIGUSR1)
   {
      woken = 1;
      printf("Time to wake up\n");
   }
   else printf("Wasn't prepared to handle %s\n", strsignal(signo));
}

void parent_handler(int signo)
{
   if (signo == SIGPIPE) 
   {
      finished = 1;
      kill(pid, SIGUSR1);
   }
}

int main(char *argc[], int argv) 
{
  char buffer[BUFFER_SIZE];
  int fd[2];
  struct sigaction sa1, sa2;
  sa1.sa_handler = child_handler;
  sigaction(SIGUSR1, &sa1, NULL);
  sa2.sa_handler = parent_handler;
  sigaction(SIGPIPE, &sa2, NULL);
  pipe(fd);
  pid = fork();
  if (pid == 0) { // child
     close(fd[1]);
     int num = read(fd[0], buffer, BUFFER_SIZE);
     if (num > 0)  
        printf("My parent %d says %s\n", getppid(), buffer);
     close(fd[0]);
     printf("Now I'll rest for a while.. What a confusing world!!!\n"); 
     if (!woken)
        pause();
     return 0;
  } 
  else if (pid < 0) { // parent (error in fork)
  }
  else { // parent
     int status;
     close(fd[0]);
     printf("Before greeting my child let me check on it..\n");
     printf("Looks like it has %s\n", (!waitpid(pid, &status, WNOHANG) ? "not exited" : "exited"));
     sprintf(buffer, "Hello???, child %d\n", pid);
     do 
       write(fd[1], buffer, sizeof(buffer));
     while (!finished);
     close(fd[1]);
     return 0;  
  }

}
