#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sockfd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("172.27.40.33");
  addr.sin_port = htons(8080);

  int ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)); 
  if(ret < 0) {
    perror("connect");
    return -1;
  }
  
  while(1) {
    char buf[1024] = { 0 };
    printf("Please enter the msg to server : ");
    fflush(stdout);
    std::cin >> buf;
    ssize_t send_size = send(sockfd, buf, strlen(buf), 0);
    if(send_size < 0) {
      perror("send");
      continue;
    }

    memset(buf, '\0', sizeof(buf));
    ssize_t recv_size = recv(sockfd, buf, sizeof(buf) - 1, 0);
    if(recv_size < 0) {
      perror("recv");
      continue;
    }
    else if(recv_size == 0) {
      printf("Peer shutdown!\n");
      close(sockfd);
      return 0;
    }
    printf("Server say : %s\n", buf);
  }
  close(sockfd);

  return 0;
}
