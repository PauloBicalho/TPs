#ifndef BEALCLIENT_HPP
#define BEALCLIENT_HPP
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <netdb.h>

#include "MessageType.hpp"

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

#define WAITING_TIME 5

class BealClient{
  public:
    BealClient(char *_id, char *serverIP, char * serverPort);

//    void connect();

    void compute();

    void disconnect();

  private:
    char *id;

    long long lowerLimit1, upperLimit1;
    long long lowerLimit2, upperLimit2;

    //int a, b, c, x, y, z;
    //int v1, v2, v3; //a^x b^x c^z
    cpp_int a, b, c, x, y, z;
    cpp_int v1, v2, v3; //a^x b^x c^z
//    unsigned __int128 a, b, c, x, y, z;
//    unsigned __int128 v1, v2, v3; //a^x b^x c^z
//    unsigned long long int  a, b, c, x, y, z;
//    unsigned long long int v1, v2, v3; //a^x b^x c^z

    int sockOut;
    struct sockaddr_in serverAddr, selfAddr;
    struct addrinfo addrInfo, *result, *rp;
    fd_set fdst;

    bool sendMsgAndWaitConfirmation(char *msg_out, MessageType::Type confirm);
    bool receiveMessage(char *msg);
    bool handleMessage(char *msg, MessageType::Type confirm);

    bool verify();

};



#endif // BEALCLIENT_HPP
