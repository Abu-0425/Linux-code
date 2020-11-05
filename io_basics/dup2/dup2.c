#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd = open("./linux", O_RDWR | O_CREAT, 0664);
  if(fd < 0) {
    perror("open");
    return -1;
  }
  printf("fd = %d\n", fd);
  dup2(fd, 1);

  printf("It's dup2!!!\n");

  return 0;
}
