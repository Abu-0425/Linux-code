#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <sstream>

int main()
{
  int listen_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(listen_sockfd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  addr.sin_port = htons(8080);

  int ret = bind(listen_sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if(ret < 0) {
    perror("bind");
    return -1;
  }

  ret = listen(listen_sockfd, 5);
  if(ret < 0) {
    perror("listen");
    return -1;
  }

  int new_sockfd = -1;

  while(1) {
    new_sockfd = accept(listen_sockfd, NULL, NULL);
    if(new_sockfd < 0) {
      perror("accept");
      return -1;
    }

    char buf[1024] = { 0 };
    ssize_t recv_size = recv(new_sockfd, buf, sizeof(buf) - 1, 0);
    if(recv_size < 0) {
      perror("recv");
      continue;
    }
    else if(recv_size == 0) {
      printf("Peer shutdown!\n");
      close(new_sockfd);
      close(listen_sockfd);
      return 0;
    }
    printf("Client say : %s\n", buf);

    memset(buf, '\0', sizeof(buf));

    std::string body = "<html>Http is so easy!</html>";

    std::stringstream ss;

    //ss << "HTTP/1.1 200 OK\r\n";
    //ss << "Content-Type: text/html\r\n";
    //ss << "Content-Length: " << body.size() << "\r\n";
    //ss << "\r\n";

    ss << "HTTP/1.1 302 Location\r\n";
    ss << "Content-Type: text/html\r\n";
    ss << "Content-Length: " << body.size() << "\r\n";
    ss << "Location: https://www.baidu.com/\r\n";
    ss << "\r\n";

    //ss << "HTTP/1.1 404 Page Not Found\r\n";
    //ss << "Content-Type: text/html\r\n";
    //ss << "Content-Length: " << body.size() << "\r\n";
    //ss << "\r\n";
    
    //ss << "HTTP/1.1 502 Bad Gateway\r\n";
    //ss << "Content-Type: text/html\r\n";
    //ss << "Content-Length: " << body.size() << "\r\n";
    //ss << "\r\n";
    
    size_t send_size = send(new_sockfd, ss.str().c_str(), ss.str().size(), 0);
    if(send_size < 0) {
      perror("send");
      continue;
    }

    send_size = send(new_sockfd, body.c_str(), body.size(), 0);
    if(send_size < 0) {
      perror("send");
      continue;
    }
  }

  close(listen_sockfd);
  close(new_sockfd);

  return 0;
}
