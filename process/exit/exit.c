#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
  printf("我要退出了！");//没有\n
  fflush(NULL);//刷新缓冲区
  _exit(1);
  printf("应该不会打印我了！\n");
  return 0;
}
