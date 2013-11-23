#ifndef BEALSERVER_H
#define BEALSERVER_H

#include <map>
#include <vector>
#include "MessageType.hpp"
#include <string>

#define DELTA_INTERVAL_1 10
#define DELTA_INTERVAL_2 10

class BealServer{
  public:

    BealServer(int porto);
    
    void start();


  private:
    int sockIn;
    long long begOfNextInterval1;
    long long begOfNextInterval2;

    struct sockaddr_in srv_addr;
    fd_set fdst;
 
    bool receiveMessage(char *, struct sockaddr_in *currentClient);
    bool handleMessage(char *, struct sockaddr_in *clientAddr);

    bool sendNextInterval(std::string clientId);
    bool resendInterval(std::string clientId);

    bool confirmResultReceived(std::string clientId);
    bool disconnectClient(std::string clientId);

    std::map<std::string, MessageType::Type> expectedMsgFromClients;
    
    std::map<std::string, struct sockaddr_in *> connectedClients;
    std::map<std::string, int> connectedClients2;

    std::map<std::string, std::string> intervalSentToClients;

    std::map<std::string, std::vector<std::string> > counterexamplesFound;


};



#endif //SOCKET_H
