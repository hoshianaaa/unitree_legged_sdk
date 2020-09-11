#include <stdio.h>
#include <string.h>
#include "simple_udp.h"
#include <iostream>
simple_udp udp0("192.168.1.233",5555);

int main(int argc, char **argv){
  udp0.udp_bind();
  std::cout << "start" << std::endl;
  while (1){
    std::string rdata;
    if(udp0.udp_recv(rdata))printf("recv:%s\n", rdata.c_str());
  }
  return 0;
}
