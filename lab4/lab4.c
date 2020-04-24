#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t pid;

  printf("Main starting, my pid is %d\n\n", getpid());

  pid = fork();

  if (pid == 0) {
    printf("This is the child process, my pid is %d, my parent pid is %d\n\n", getpid(), getppid());
    //exec
    sleep(2);
  }
  else {
    //waitpid()
    wait (0);
    printf("Child finished, main exiting, my pid is %d\n", getpid());
  }
}
