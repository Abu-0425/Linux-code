#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

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

  int new_sockfd = accept(listen_sockfd, NULL, NULL);
  if(new_sockfd < 0) {
    perror("accept");
    return -1;
  }
  
  while(1) {
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
    printf("Please enter the msg to client : ");
    fflush(stdout);
    std::cin >> buf;
    ssize_t send_size = send(new_sockfd, buf, strlen(buf), 0);
    if(send_size < 0) {
      perror("send");
      continue;
    }
  }
  close(listen_sockfd);
  close(new_sockfd);

  return 0;
}
