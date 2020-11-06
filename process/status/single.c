#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0) {
    perror("fork");
    return -1;
  }
  else if(pid == 0) {
    //child
    printf("I'm child,pid is %d\n", getpid());
    while(1) {
      sleep(1);
    }
  }
  else {
    //parent
    printf("I'm parent,pid is %d\n", getpid());
    sleep(20);
    exit(0);
  }
  return 0;
}
