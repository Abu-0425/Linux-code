#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int count = 0;
  while(1) {
    int fd = open("./fd_test", O_RDWR | O_CREAT, 0664);
    if(fd < 0) {
      perror("open");
      break;
    }
    count++;
    printf("fd : %d\n", fd);
  }
  //打开文件数目的最大值
  printf("count : %d\n", count);
  return 0;
}
