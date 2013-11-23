#include <iostream>

#include "BealClient.hpp"

int main(int argc, char *argv[]){
  BealClient client (argv[1], argv[2], (argv[3]));
  client.compute();
  client.disconnect();




  return 0;
}
