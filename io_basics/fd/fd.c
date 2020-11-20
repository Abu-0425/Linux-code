#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  close(1);
  int fd[3];
  int i = 0;
  for(; i < 3; i++) {
    fd[i] = open("./linux", O_RDWR | O_CREAT, 0664);
    if(fd[i] < 0) {
      perror("open");
      return -1;
    }
    printf("fd[%d] : %d\n", i, fd[i]);
  } 
  fflush(stdout);
  i = 0;
  for(; i < 3; i++) {
    close(fd[i]);
  }

  return 0;
}
