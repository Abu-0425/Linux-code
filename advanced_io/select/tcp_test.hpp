#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

using namespace std;

class TcpSvr {
  public:
    TcpSvr() 
    {
      _socket_fd = -1;
    }

    ~TcpSvr()
    {

    }

    int CreateSocket()
    {
      _socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if(_socket_fd < 0) {
        perror("socket");
        return -1;
      }
      return 0;
    }

    int Bind(const string &ip, const uint16_t port)
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

    int Listen(int backlog = 5)
    {
      int ret = listen(_socket_fd, backlog);
      if(ret < 0) {
        perror("listen");
        return -1;
      }
      return 0;
    }

    int Accept(TcpSvr *ts, struct sockaddr_in *peer_addr, socklen_t *peer_addr_len)
    {
      int new_sockfd = accept(_socket_fd, (struct sockaddr *)peer_addr, peer_addr_len);
      if(new_sockfd < 0) {
        perror("accept");
        return -1;
      }
      ts->SetFd(new_sockfd);
      return 0;
    }
    
    ssize_t Recv(string *data)
    {
      char buf[1024] = {0};
      ssize_t recv_size = recv(_socket_fd, buf, sizeof(buf) - 1, 0);
      if(recv_size < 0) {
        perror("revc");
        return -1;
      }
      else if(recv_size == 0) {
        cout << "Peer ShutDown" << endl;
        return 0;
      }

      data->assign(buf, strlen(buf));
      return recv_size;
    }

    ssize_t Send(const string &data)
    {
      ssize_t send_size = send(_socket_fd, data.c_str(), data.size(), 0);
      if(send_size < 0) {
        perror("send");
        return -1;
      }
      return send_size;
    }

    void SetFd(int fd)
    {
      _socket_fd = fd;
    }

    int GetFd()
    {
      return _socket_fd;
    }

  private:
    int _socket_fd;
};
