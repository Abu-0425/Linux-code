#pragma once

#include <stdio.h>
#include <vector>
#include <unistd.h>

#include "tcp_test.hpp"


class SelectSvr {
  public:
    SelectSvr()
    {
      FD_ZERO(&_readfds);
      _nfds = -1;
    }

    ~SelectSvr()
    {

    }

    void AddFd(int fd)
    {
      FD_SET(fd, &_readfds);
      if(fd > _nfds) {
        _nfds = fd;
      }
    }

    void DelFd(int fd)
    {
      FD_CLR(fd, &_readfds);
      for(int i = _nfds; i >= 0; i--) {
        if(FD_ISSET(i, &_readfds)) {
          _nfds = i;
        }
      }
    }

    int SelectWait(std::vector<TcpSvr> *vec, struct timeval *tv)
    {
      fd_set tmp = _readfds;
      int ret = select(_nfds + 1, &tmp, NULL, NULL, tv);
      if(ret < 0) {
        perror("select");
        return -1;
      }
      else if(ret == 0) {
        printf("Time out!\n");
        return 0;
      }
      for(int i = 0; i <= _nfds; i++) {
        if(FD_ISSET(i, &tmp)) {
          TcpSvr ts;
          ts.SetFd(i);
          vec->push_back(ts);
        }
      } 
      return ret;
    } 

  private:
    fd_set _readfds; //可读事件集合
    int _nfds; //最大描述符
};
