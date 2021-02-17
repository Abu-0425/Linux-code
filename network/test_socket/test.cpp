#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
  int socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(socket_fd < 0) {
    perror("socket");
    return -1;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("172.27.40.33");
  addr.sin_port = htons(19999);
  int ret = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
  if(ret < 0) {
    perror("bind");
    return -1;
  }
  while(1) {
    sleep(1);
  }
  return 0;
}
