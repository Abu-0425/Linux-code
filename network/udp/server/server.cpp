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

  //绑定地址信息
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("172.27.40.33");
  addr.sin_port = htons(8080);
  int ret = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
  if(ret < 0) {
    perror("bind");
    return -1;
  }
  while(1) {
    //接收对端发送的数据
    char buf[1024] = { 0 };
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);
    ssize_t recv_size = recvfrom(socket_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&peer_addr, &peer_addr_len);
    if(recv_size < 0) {
      perror("recvfrom");
      continue;
    }
    printf("client say : %s\n", buf);

    //组织要返回给发送方的数据，并且调用sendto
    std::string s;
    std::cin >> s;
    ssize_t send_size = sendto(socket_fd, s.c_str(), s.size(), 0, (struct sockaddr *)&peer_addr, peer_addr_len);
    if(send_size < 0) {
      perror("sendto");
      continue;
    }
  
  }
  close(socket_fd);

  return 0;
}
