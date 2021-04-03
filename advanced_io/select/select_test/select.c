#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>


int main()
{
  while(1) {
    fd_set set;
    FD_ZERO(&set); //初始化清空集合
    FD_SET(0, &set); //将想要监控的文件描述符添加到集合当中
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    printf("Start monitoring\n");
    int ret = select(1, &set, NULL, NULL, &tv); //select在返回时会删除集合中没有就绪的描述符
    if(ret < 0) {
      perror("select");
      return -1;
    }
    else if(ret == 0) {
      printf("Monitoring timeout\n"); //没有描述符就绪的情况下返回就是超时了
      continue;
    }
    printf("Descriptor ready or timeout waiting\n");
    if(FD_ISSET(0, &set)) { //查看哪个描述符还在集合当中，确定谁就绪了什么事件
      printf("Start reading data\n");
      char buf[1024] = {0};
      int fd = read(0, buf, 1023);
      if(fd < 0) {
        perror("read");
        return -1;
      }
      printf("buf : %s\n", buf);
    }
  }

  return 0;
}
