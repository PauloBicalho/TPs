#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstring>

#include "BealServer.hpp"
#include "MessageType.hpp"
#include <iostream>

BealServer::BealServer(int porto): begOfNextInterval1(1),begOfNextInterval2(2){
  std::cout << "Iniciando servidor no porto: " << porto << std::endl;

  /* Inicializando socket */
  this->sockIn = socket(AF_INET, SOCK_DGRAM, 0);

  if( this->sockIn < 0 ){
    perror("Falha ao criar o socket");
    exit(-1);
  }

  /* Setando socket para ser reutilizavel */
  int enable = 1;
  int rc = setsockopt(this->sockIn, SOL_SOCKET, 
      SO_REUSEADDR, (char *)&enable, sizeof(enable) );

  if( rc < 0 ){
    perror("Falha ao fazer o socket reutilizável");
    close(this->sockIn);
    exit(-1);
  }

  /* Setando socket para ser nao blocante */
  rc = ioctl(this->sockIn, FIONBIO, (char *)&enable);
  if( rc < 0 ){
    perror("Falha ao setar o socket como não blocante");
    close(this->sockIn);
    exit(-1);
  }

  /* Inicializando estrutura de endereço */
  memset(&(this->srv_addr),0, sizeof( (this->srv_addr) ));
  this->srv_addr.sin_family = AF_INET;
  this->srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  this->srv_addr.sin_port = htons(porto);

  /* Bind do socketo no endereco local */
  rc = bind(this->sockIn, (struct sockaddr *)&(this->srv_addr),
      sizeof( (this->srv_addr) ));
  if( rc < 0 ){
    perror("Falha no bind");
    close(this->sockIn);
    exit(-1);
  }

  /* Inicializando estrutura para o select */
  FD_ZERO(&(this->fdst));
  FD_SET(this->sockIn, &(this->fdst));

}

void BealServer::start(){

  int rc, maxFd = this->sockIn;

  timeval time;


  do{
    time.tv_sec = 3*60;
    time.tv_usec = 0;

  //  std::cout << "Select ...";
    //rc = select(maxFd+1, &(fdst), NULL, NULL, NULL);
    rc = select(maxFd+1, &(fdst), NULL, NULL, &time);
  //  std::cout << "Rc: " << rc << "\tSock: " << this->sockIn << "\n";

    if( rc < 0 ){

      perror("Erro no select");
      exit(-1);

    } else if( rc == 0 ){

      std::cout << "Tempo máximo de espera do select atingido\n";
      break;

    } else if( FD_ISSET(this->sockIn, &fdst) ){
      char msg[512];

      struct sockaddr_in *clientAddr = 
        (struct sockaddr_in *) malloc ( sizeof(struct sockaddr_in) );

      bzero(clientAddr, sizeof(*clientAddr));
      
      this->receiveMessage(msg,clientAddr);
      this->handleMessage(msg,clientAddr); 
    }

  } while (true);

}

bool BealServer::sendNextInterval(std::string clientId){
    
  struct sockaddr_in *clientAddr = this->connectedClients[clientId];

  char msg[1024];
  char _interval[512];
  
  sprintf(_interval,"%lld-%lld_%lld-%lld",
      this->begOfNextInterval1, begOfNextInterval1 + DELTA_INTERVAL_1,
      this->begOfNextInterval2, begOfNextInterval2 + DELTA_INTERVAL_2);

  sprintf(msg,"%d | %s", MessageType::SEND_INTERVAL, _interval);

  this->begOfNextInterval1 += DELTA_INTERVAL_1;
  this->begOfNextInterval2 += DELTA_INTERVAL_2;

  sendto(this->sockIn, msg, 1024, 0, 
    (struct sockaddr*) clientAddr, sizeof(*clientAddr));

  std::string interval(_interval);
  this->intervalSentToClients[clientId] = interval;

  return true;

}

bool BealServer::resendInterval(std::string clientId){
    
  struct sockaddr_in *clientAddr = this->connectedClients[clientId];

  char msg[1024];

  sprintf(msg,"%d | %s", MessageType::SEND_INTERVAL,
      this->intervalSentToClients[clientId].c_str());

  sendto(this->sockIn, msg, 1024, 0, 
    (struct sockaddr*) clientAddr, sizeof(*clientAddr));

  return true;
}


bool BealServer::handleMessage(char *msg, struct sockaddr_in *clientAddr){
  char _clientId[50] = "\0", _value[450] = "\0";
  MessageType::Type msgReceiveType;

  sscanf(msg, "%s | %d | %s", _clientId,(int *) &msgReceiveType, _value);

  std::string clientId (_clientId);
  std::string value (_value);


  std::cout << "Cliente id: " << clientId << "\n";
  std::cout << "Message Type: " << msgReceiveType << "\n";
  std::cout << "Value Size : " << value.size() << "\n";


  if( connectedClients.find(clientId) == connectedClients.end() ){
    std::cout << "\nNovo Cliente Conectado: " << clientId << "\n";
    connectedClients[clientId] = clientAddr;
    expectedMsgFromClients[clientId] = MessageType::SEND_ID;
  }

  MessageType::Type expectedMsgFromClient = this->expectedMsgFromClients[clientId];

  switch(expectedMsgFromClient){
    case MessageType::SEND_ID:
      
      if( msgReceiveType == MessageType::SEND_ID ){
        this->sendNextInterval(clientId);
        std::cout << "Intervalo enviado\n";
        this->expectedMsgFromClients[clientId] = MessageType::CONFIRM_INTERVAL;
      }
      break;

    case MessageType::CONFIRM_INTERVAL:

      switch(msgReceiveType){
        case MessageType::SEND_ID:
          connectedClients[clientId] = clientAddr;
          this->resendInterval(clientId);
          std::cout << "Intervalo reenviado\n";
          break;

        case MessageType::CONFIRM_INTERVAL:
          this->expectedMsgFromClients[clientId] = MessageType::SEND_RESULT;
          std::cout << "Intervalo recebido pelo cliente\n";
          break;

        default:
          break;
      }
      break;

    case MessageType::SEND_RESULT:

      switch(msgReceiveType){
        case MessageType::CONFIRM_INTERVAL:
          break;

        case MessageType::SEND_RESULT:
          std::cout << "Resultado Recebido\n";
          this->confirmResultReceived(clientId);
          if( value.size() > 0 ){
            std::cout << "Contra exemplo encontrado: " << value << "\n";
            counterexamplesFound[clientId].push_back(value);
          }
          else{
            this->disconnectClient(clientId);
            std::cout << "Cliente desconectado\n";
          }
          break;
        default:
          break;

      }

      break;
      default:
        break;
  }
  return true;
}

bool BealServer::confirmResultReceived(std::string clientId){
  struct sockaddr_in *clientAddr = this->connectedClients[clientId];

  char msg[1024];

  sprintf(msg,"%d | OK ", MessageType::CONFIRM_RESULT);

  sendto(this->sockIn, msg, 1024, 0, 
    (struct sockaddr*) clientAddr, sizeof(*clientAddr));

  return true;
}

bool BealServer::disconnectClient(std::string clientId){
  this->expectedMsgFromClients.erase(clientId);
  this->intervalSentToClients.erase(clientId);
  this->connectedClients.erase(clientId);

  return true;
}

bool BealServer::receiveMessage(char *msg, struct sockaddr_in *currentClient){
  socklen_t cliLen = sizeof(*currentClient);
  
  
  int len = recvfrom(this->sockIn, msg, 1024, 0, 
      (struct sockaddr*) currentClient, &cliLen);
  msg[len] = '\0';

  std::cout << "Raw msg: " << msg << "\n\n";

  return true;
}
  
