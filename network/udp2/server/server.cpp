#include "../udp.hpp"

#define CHECK_RET(ret) if(ret < 0) {return -1;}


int main(int argc, char *argv[])
{
  if(argc != 3) {
    printf("Please using ./server [ip] [port]!\n");
    return -1;
  } 

  UdpSvr us;

  CHECK_RET(us.CreateSocket());

  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  CHECK_RET(us.Bind(ip, port)); 

  while(1) {
    std::string data;
    struct sockaddr_in peer_addr;
    int ret = us.Recvfrom(&data, &peer_addr);
    if(ret < 0) {
      continue;
    }
    std::cout << "Client say : " << data << std::endl;

    data.clear();
    std::cout << "Please enter the msg to client : ";
    fflush(stdout);
    std::cin >> data;

    ret = us.Sendto(data, &peer_addr);
    if(ret < 0) {
      continue;
    }
  }
  us.Close();

  return 0;
}
