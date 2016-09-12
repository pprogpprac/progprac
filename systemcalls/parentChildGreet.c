#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main(char *argc[], int argv)
{
  char buffer[BUFFER_SIZE];
  int fd[2];
  pipe(fd);
  pid_t pid = fork();
  if (pid == 0) { // child
     close(fd[1]);
     int num = read(fd[0], buffer, BUFFER_SIZE);
     if (num > 0)
        printf("CHILD: My parent %d says %s\n", getppid(), buffer);
     close(fd[0]);
     printf("CHILD: Now pausing, just don't forget to kill me=%d\n", getpid());
     pause();
     return 0;
  }
  else if (pid < 0) { // parent (error in fork)
  }
  else { // parent
     int status;
     close(fd[0]);
     printf("PARENT: Before greeting my child let me check on it..\n");
     printf("PARENT: Looks like it has %s\n", (!waitpid(pid, &status, WNOHANG) ? "not exited" : "exited"));
     sprintf(buffer, "PARENT: Hello???, child %d\n", pid);
     write(fd[1], buffer, sizeof(buffer));
     close(fd[1]);
     return 0;
  }

}
