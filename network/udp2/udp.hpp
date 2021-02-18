#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

class UdpSvr {
  public:
    UdpSvr()
    {
      _socket_fd = -1;
    }

    //创建套接字
    int CreateSocket() 
    {
      _socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
      if(_socket_fd < 0) {
        perror("socket");
        return -1;
      }
      return 0;
    }

    //绑定地址信息
    int Bind(const std::string &ip, uint16_t port)
    {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int ret = bind(_socket_fd, (struct sockaddr *)&addr, sizeof(addr));
      if(ret < 0) {
        perror("bind");
        return -1;
      }
      return 0;
    }

    //发送消息
    int Sendto(const std::string &data, struct sockaddr_in *dest_addr)
    {
      ssize_t size = sendto(_socket_fd, data.c_str(), data.size(), 0, (struct sockaddr *)dest_addr, sizeof(struct sockaddr_in));
      if(size < 0) {
        perror("sendto");
        return -1;
      }
      return size;
    }

    //接收信息
    int Recvfrom(std::string *data, struct sockaddr_in *peer_addr)
    {
      char buf[1024] = { 0 };
      socklen_t peer_addr_len = sizeof(struct sockaddr_in);
      ssize_t size = recvfrom(_socket_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)peer_addr, &peer_addr_len);
      if(size < 0) {
        perror("recvfrom");
        return -1;
      }
      data->assign(buf, strlen(buf));
      return size;
    }

    void Close()
    {
      close(_socket_fd);
    }
  private:
    int _socket_fd;
};
