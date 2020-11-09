#include <stdio.h>
#include <unistd.h>

#if 0
//通过main函数的第三个参数获取环境变量
int main(int argc, char *argv[], char *env[])
{
  //argc:程序运行时参数的个数
  //argv:参数的具体内容
  //env:环境变量
  for(int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  for(int i = 0; env[i]; i++) {
    printf("[%d]:%s\n", i, env[i]);
  }
  return 0;
}
#endif

#if 0
//通过libc库中提供的变量来获取
int main()
{
  extern char **environ;
  for(int i = 0; environ[i]; i++) {
    printf("[%d]:%s\n", i, environ[i]);
  }
  return 0;
}
#endif

#include <stdlib.h>
int main()
{
  //通过libc库中提供的函数getenv来获取某一个环境变量具体的值
  char *PATH = getenv("PATH");
  printf("PATH = %s\n", PATH);
  return 0;
}
