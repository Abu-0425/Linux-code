#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
  //以读写方式打开文件，若不存在则创建，文件权限为rw-rw-r--
  int fd = open("./linux", O_RDWR | O_CREAT, 0664);
  if(fd < 0) {
    perror("open");
    return -1;
  }
  printf("%d\n", O_RDWR | O_CREAT);
  printf("ret = %d\n", fd);

  char buf[] = "Linux is cool!";
  write(fd, buf, strlen(buf));//写入文件

  lseek(fd, 0, SEEK_SET);//使文件指针偏移到头部
  memset(buf, 0, sizeof(buf));//清空字符串

  printf("read_before_buf:%s\n", buf);
  read(fd, buf, sizeof(buf) - 1);//将文件中的内容读到buf中
  printf("read_after_buf:%s\n", buf);

  close(fd);//关闭文件

  return 0; 
}
