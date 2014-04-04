#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
  
  if(argc != 4){
    cerr << "Erro nos parâmetros\n";
    cerr << "\t" << argv[0] << " arquivo_font saida_front saida_back\n";
  }

  char cmd1[1024];
  char cmd2[1024];

  sprintf(cmd1,"front/frontend %s  > %s",argv[1],argv[2]);
  sprintf(cmd2,"back/backend %s  > %s",argv[2],argv[3]);

  cout << cmd1 << "\n";
  cout << cmd2 << "\n";

  system(cmd1);
  system(cmd2);


  return 0;
}
