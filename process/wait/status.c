#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0) {
    perror("fork");
    return -1;
  }
  else if(pid == 0) {
    //子进程
    printf("I am child, pid is %p\n", getpid());
    sleep(3);
    exit(20); //退出子进程并将其退出码设置为20
  }
  else {
    printf("I am father, pid is %p\n", getpid());
    int status; //定义status，让操作系统为其赋值
    waitpid(-1, &status, 0); //这种传参方式的waitpid和wait几乎没有区别
    printf("进程等待成功!\n");
    //低7位为全0则表示正常退出
    if((status & 0x7F) == 0) {
      printf("正常退出!\n");
      printf("exitcode = %d\n", (status >> 8) & 0xFF);
    }
    else {
      printf("异常提出!\n");
      printf("core dump flag = %d\n", (status >> 7) & 0x1);
    }
  }
  return 0;
}
