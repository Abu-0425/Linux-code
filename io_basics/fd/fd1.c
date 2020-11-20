#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  close(1);
  int fd = open("./myfile", O_RDWR | O_CREAT, 0664);
  if(fd < 0) {
    perror("open");
    return -1;
  }
  printf("fd = %d\n", fd);
  printf("Linux is cool!\n");
  return 0;
}
