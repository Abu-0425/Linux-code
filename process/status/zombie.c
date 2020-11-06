#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork(); //创建子进程
  if(pid < 0) {
    perror("fork");
    return -1;
  }
  else if(pid == 0) {
    //子进程
    printf("I'm child,pid is %d\n", getpid());
    exit(0); //子进程先退出
  }
  else {
    //父进程
    sleep(20);
    printf("I'm father,pid is %d\n", getpid());
  }

  return 0;
}

