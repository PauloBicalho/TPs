#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

#include "BealServer.hpp"

int main(int argc, char *argv[]){

  BealServer server (3033);

  server.start();

  return 0;
}
