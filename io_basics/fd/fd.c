#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  close(0);
  int fd = open("./test", O_RDWR | O_CREAT, 0664);
  if(fd < 0) {
    perror("open");
    return -1;
  }
  printf("O_RDWR | O_CREAT = %d\n", O_RDWR | O_CREAT);
  printf("fd = %d\n", fd);
  //文件描述符的分配原则为最小未占用原则

  return 0;
}
