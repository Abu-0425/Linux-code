#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

int main()
{
  //创建套接字
  int socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(socket_fd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in svr_addr;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = inet_addr("172.27.40.33");
  svr_addr.sin_port = htons(8080);
  
  while(1) {
    //发送数据到服务端
    std::string s;
    std::cin >> s;
    ssize_t send_size = sendto(socket_fd, s.c_str(), s.size(), 0, (struct sockaddr *)&svr_addr, sizeof(svr_addr));
    if(send_size < 0) {
      perror("sendto");
      continue;
    }

    //接收服务端返回的数据
    char buf[1024] = { 0 };
    ssize_t recv_size = recvfrom(socket_fd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    if(recv_size < 0) {
      perror("recvfrom");
      continue;
    }
    printf("server say : %s\n", buf);

  }
  close(socket_fd);

  return 0;
}
