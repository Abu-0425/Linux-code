#include <stdio.h>
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
    sleep(10);
  }
  else {
    printf("I am father, pid is %p\n", getpid());
    while(waitpid(pid, NULL, WNOHANG) == 0); //循环调用waitpid，直到其返回值不为0
    printf("进程等待成功!\n");
  }
  return 0;
}
