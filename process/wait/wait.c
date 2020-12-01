#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork(); //创建子进程
  if(pid < 0) {
    perror("fork");
    return -1;
  }
  else if(pid == 0) {
    printf("I am child, my pid is %p\n", getpid());
    sleep(3);
  }
  else {
    //父进程
    printf("I am father, my pid is %p\n", getpid());
    wait(NULL); //进程等待
    printf("进程等待成功!\n");
  }
  return 0;
}
