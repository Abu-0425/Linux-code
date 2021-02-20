#include <iostream>
#include <cstdio>
#include <cstring>

#include "httplib.h"

int g_count = 0;

int main(int argc, char *argv[])
{
  if(argc != 3) {
    printf("Please using ./http_svr [port] [num]\n");
    return -1;
  }

  uint16_t port = atoi(argv[1]);
  std::string num = argv[2];

  httplib::Server svr;
  svr.Get("/xjw", [num](const httplib::Request &req, httplib::Response &resp){
      (void)req;
      char buf[1024] = { 0 };
      snprintf(buf, sizeof(buf) - 1, "<html><h1>i am server : %s, request count : %d<h1></html>", num.c_str(), ++g_count);
      resp.set_content(buf, strlen(buf), "text/html");
      });
  
  svr.listen("0.0.0.0", port);

  return 0;
}
