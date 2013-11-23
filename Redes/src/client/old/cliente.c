#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int main( int argc, char * argv[] ){
  
  int sockCli;                                  /* Socket do Clente */ 
  
  struct sockaddr_in servAddr;                  /* Informacoes de endereco servidor */

  char * servTcpAddr = argv[1];

  short servTcpPort = atoi(argv[2]);

  char * string_in = NULL,                      /* String recebida pelo socket */
       * string_out = NULL;                     /* String a ser enviada pelo socket */

  int rc;
  
  pid_t pid;



  struct addrinfo addrInfo;                     /* Informacoes de endereco do servidor */
  struct addrinfo *result,                      /* Ponteiros para iterar sobre os possiveis tipos de endereco */
                 *rp;

  int addrInfoStatus = 0,
     socketS = 0;

  if( argc < 3 ){
   printf("Cliente: Erro nos parametros");
   exit(1);
  }

  memset(&addrInfo, 0, sizeof(struct addrinfo));

  /*
  *Preenche a estrutura addrInfo
  *Esta estrutura ira armazenar os possiveis
  *tipos de endereco. Suporta ipv6 e ipv4 
  */
  addrInfo.ai_family = AF_UNSPEC;               /* Permite IPV4 e IPV6 */
  addrInfo.ai_socktype = SOCK_DGRAM;           /* Socket UDP */
  addrInfo.ai_flags = 0;
  addrInfo.ai_protocol = 0;                     /* Qualquer protocolo */

  addrInfoStatus = getaddrinfo(argv[1],argv[2], &addrInfo, &result);
  if(addrInfoStatus != 0){
   printf("Cliente: Erro no getaddrinfo\n");
   exit(1);
  }

  /*
  *gataddrinfo retorna uma lista de estruturas de enderecos.
  *Este loop percorre estas estruturas, tentando criar um
  *socket e conecta-lo ao servidor. No primeiro sucesso
  *para o loop e o descritor do socket encontra-se no
  *inteiro socketS.
  */
  for(rp = result; rp != NULL; rp = rp->ai_next){
   socketS = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

   if(socketS == -1)
     continue;

   if( connect(socketS, rp->ai_addr, rp->ai_addrlen) != -1 ){
     if(rp->ai_family == AF_INET6)
       printf("Cliente: Usando IPV6\n");
     else if(rp->ai_family == AF_INET)
       printf("Cliente: Usando IPV4\n");
     break;
   }

   close(socketS);
  }

  /*
  *Se nao foi possivel criar e conectar um socket com
  *nenhuma das estruturas retornadas por getaddrinfo,
  *gera um erro e termina o programa.
  */
  if( rp == NULL ){
   printf("Cliente: Erro ao conectar\n");
   exit(1);
  }

  sockCli = socketS;
                  
  printf("Cliente: Conectado.\n");
  
  
  /* 
   * A funcao fork duplica o processo
   * e retorna para o processo pai o 
   * PID do filho e para o processo
   * filho retorna 0.
   */

  /*
   * A primeira parte do if-else sera
   * executada pelo filho e e responsavel
   * por receber as mensagens do cliente.
   * A parte do else e executada pelo pai
   * e e responsavel por enviar mensagens
   * para o cliente 
   */

  if( (pid = fork() ) != 0 ){
    for(;;){
      string_in = (char *) malloc (1024 * sizeof(char));
      rc = read(sockCli, string_in, 1024);
       
      if(rc > 0){
        printf("\033[0m--->\033[32m %s \033[0m \n", string_in);
      
      } else {
        free(string_in);
        kill(pid, SIGTERM);
        break;
      }

      free(string_in);
    }
  } else {
    for(;;){
      string_out = (char *) malloc (1024 * sizeof(char));
      gets(string_out);
      fflush(stdin);

      printf("\033[1A");
      printf("\033[K");
      printf("\b\b\b\b<---\033[0;37m %s \033[0m \n", string_out);

      write(sockCli, string_out, strlen(string_out) + 1);
      free(string_out);
       
    }
  }

  close(sockCli);
  printf("Cliente: Conexao finalaizada pelo servidor.\n");
}
