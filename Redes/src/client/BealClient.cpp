#include "BealClient.hpp"
#include <arpa/inet.h>
#include <math.h>

BealClient::BealClient(char *_id, char * serverIP, char * serverPort): 
  id(_id), lowerLimit1(0), upperLimit1(0), lowerLimit2(0), upperLimit2(0),
  a(0), b(0), c(0), x(0), y(0), z(0){

    this->sockOut = socket(AF_INET, SOCK_DGRAM, 0);

    if( this->sockOut < 0 ){
      perror("Falha ao criar o socket");
      exit(-1);
    }

    /* Setando socket para ser reutilizavel */
    int enable = 1;
    int rc = setsockopt(this->sockOut, SOL_SOCKET,
        SO_REUSEADDR, (char *)&enable, sizeof(enable) );

    if( rc < 0 ){
      perror("Falha ao fazer o socket reutilizável");
      close(this->sockOut);
      exit(-1);
    }

    /* Setando socket para ser nao blocante */
    rc = ioctl(this->sockOut, FIONBIO, (char *)&enable);
    if( rc < 0 ){
      perror("Falha ao setar o socket como não blocante");
      close(this->sockOut);
      exit(-1);
    }

    struct sockaddr_in selfAddr;
    bzero(&selfAddr, sizeof(selfAddr));
    selfAddr.sin_family = AF_INET;
    selfAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    selfAddr.sin_port = htons(0);


    bzero(&(this->serverAddr), sizeof(this->serverAddr));
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    this->serverAddr.sin_port = htons(atoi(serverPort));

    rc = bind(this->sockOut, (struct sockaddr *)&(selfAddr),
            sizeof( selfAddr ));
    if( rc < 0 ){
        perror("Falha no bind");
        close(this->sockOut);
        exit(-1);
    }

    rc = connect(this->sockOut, (struct sockaddr *) &this->serverAddr, 
        sizeof(this->serverAddr));

    if( rc < 0 ){
      perror("Falha no connect: ");
      exit(-1);
    }

    char msg[1024];
    sprintf(msg, "%s | %d | ", id, MessageType::SEND_ID);

    /* Inicializando estrutura para o select */
    FD_ZERO(&(this->fdst));
    FD_SET(this->sockOut, &(this->fdst));

    while(not this->sendMsgAndWaitConfirmation(msg, MessageType::SEND_INTERVAL) );

    sprintf(msg, "%s | %d | ", id,(int) MessageType::CONFIRM_INTERVAL);
    write(this->sockOut, msg, strlen(msg) + 1);
}

cpp_int myPow(cpp_int base, cpp_int exp){
  cpp_int result = base;
  for(int i=1; i<exp; i++)
    result *= base;

  return result;
}

void BealClient::disconnect(){
  char msg[1024];
  sprintf(msg,"%s | %d | ", this->id, MessageType::SEND_RESULT);

  while(not this->sendMsgAndWaitConfirmation(msg, MessageType::CONFIRM_RESULT) );
}


void BealClient::compute(){

  long long i, j, k, l, m, n;

  long long couter = 0;

  for(i=lowerLimit1; i<upperLimit1; i++ ){
    this->a = i;
    for(j=lowerLimit1; j<upperLimit1; j++ ){
      this->b = j;
      for(k=lowerLimit1; k<upperLimit1; k++ ){
        this->c = k;
        for(l=lowerLimit2; l<upperLimit2; l++ ){
          this->x = l;
          for(m=lowerLimit2; m<upperLimit2; m++ ){
            this->y = m;
            for(n=lowerLimit2; n<upperLimit2; n++ ){
              this->z = n;

              v1 = myPow(a,x);
            //  std::cout << a << "^" << x << "=" << v1 << "\n";

              v2 = myPow(b,y);
              v3 = myPow(c,z);

              if( v1 + v2 == v3 ){
                std::cout << i << "^" << l << " + "
                  << j << "^" << m << " = "
                  << k << "^" << n << "\n";
 //               if( this->verify() )
              }
                  
            }
          }
        }
      }
    }
  }
}

bool BealClient::sendMsgAndWaitConfirmation(char *msg_out, MessageType::Type confirm){
  
  int rc, maxFd = this->sockOut;


  bool sent = false;
  do{
    timeval time;
    time.tv_sec = WAITING_TIME;
    time.tv_usec = 0;
    
    std::cout << "Sending message: " << msg_out << "\n";
//    sendto(this->sockOut, msg_out, strlen(msg_out)+1, 0, (struct sockaddr*) &(this->serverAddr),
//        sizeof(this->serverAddr));

    write(this->sockOut, msg_out, strlen(msg_out) + 1);

    rc = select(maxFd+1, &(fdst), NULL, NULL, &time);

    if( rc < 0 ){
      perror("Erro no select");
      exit(-1);

    } else if( rc == 0 ){
      std::cout << "Reenviando mensagem\n";
    } else if( FD_ISSET(this->sockOut, &fdst) ){
      char msg_in[1024];
      
      this->receiveMessage( msg_in );
      if ( this->handleMessage( msg_in, confirm) )
        sent = true;
    }


  } while (not sent);

  return true;
}

bool BealClient::handleMessage(char *msg, MessageType::Type confirm){
  char _value[450] = "\0";
  MessageType::Type msgReceiveType;

  sscanf(msg, "%d | %s",(int *) &msgReceiveType, _value);

  std::cout << "Mensagem do tipo " << msgReceiveType << ": " << _value << "\n";

  bool ret = false;
  
  if( msgReceiveType == confirm ){
    ret = true;

    std::cout << "Confirmacao Recebida\n";
    if( msgReceiveType == MessageType::SEND_INTERVAL ){
      sscanf(_value, "%lld-%lld_%lld-%lld", &(this->lowerLimit1), 
          &(this->upperLimit1),  &(this->lowerLimit2), &(this->upperLimit2) );

    }
  }

  return ret;
}
  
                    

bool BealClient::receiveMessage( char *msg ){

  int len = recvfrom(this->sockOut, msg, 1024, 0, NULL, NULL);
  msg[len] = '\0';

  std::cout << "Raw msg: " << msg << "\n\n";

  return true;
}

