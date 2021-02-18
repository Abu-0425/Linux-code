#include "../udp.hpp"

#define CHECK_RET(ret) if(ret < 0) {return -1;}

int main(int argc, char *argv[])
{
  if(argc != 3) {
    printf("Please using ./client [ip] [port]\n");
    return -1;
  }

  UdpSvr us;
  CHECK_RET(us.CreateSocket());

  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  struct sockaddr_in peer_addr;
  peer_addr.sin_family = AF_INET;
  peer_addr.sin_addr.s_addr = inet_addr(ip.c_str());
  peer_addr.sin_port = htons(port);

  while(1) {
    std::string data;
    std::cout << "Please enter the msg to server : ";
    fflush(stdout);
    std::cin >> data;
    int ret = us.Sendto(data, &peer_addr);
    if(ret < 0) {
      continue;
    }

    data.clear();
    ret = us.Recvfrom(&data, &peer_addr);
    if(ret < 0) {
      continue;
    }

    std::cout << "Server say : " << data << std::endl;
  } 
  us.Close();
  
  return 0;
}
