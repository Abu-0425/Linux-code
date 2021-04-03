#include "tcp_test.hpp"
#include "select_test.hpp"

#define CHECK(ret) if(ret < 0) {return -1;}


int main(int argc, char *argv[])
{
  if(argc != 3) {
    printf("Using ./test_select ip port\n");
    return 0;
  }

  TcpSvr ts;
  CHECK(ts.CreateSocket());
  
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  CHECK(ts.Bind(ip, port));

  CHECK(ts.Listen());

  SelectSvr ss;
  ss.AddFd(ts.GetFd());
  while(1) {
    struct timeval *tv;
    tv->tv_sec = 3;
    tv->tv_usec = 0;

    std::vector<TcpSvr> vec;
    int ret = ss.SelectWait(&vec, tv);
    if(ret < 0) {
      return -1;
    }
    else if(ret == 0) {
      continue;
    }

    for(int i = 0; i < ret; i++) {
      if(vec[i].GetFd() == ts.GetFd()) {
        //侦听套接字就绪
        TcpSvr new_ts;
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);
        ts.Accept(&new_ts, &peer_addr, &peer_addr_len);

        printf("Now new_sockfd is %d, peer_ip is %s, peer_port is %d\n", new_ts.GetFd(), inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
        
        ss.AddFd(new_ts.GetFd());
      }
      else {
        //新连接套接字就绪
        TcpSvr new_tcp_svr = vec[i];
        string data = "";
        ssize_t ret =  new_tcp_svr.Recv(&data);
        if(ret < 0) {
          close(new_tcp_svr.GetFd());
          ss.DelFd(new_tcp_svr.GetFd());
          continue;
        }
        else if(ret == 0) {
          close(new_tcp_svr.GetFd());
          ss.DelFd(new_tcp_svr.GetFd());
          continue;
        }

        //接收到了数据
        printf("Recv data : %s\n", data.c_str());
        printf("Say to cli : ");

        data.clear();
        cin >> data;
        new_tcp_svr.Send(data);
      }
    }
  }
  close(ts.GetFd());

  return 0;
}
