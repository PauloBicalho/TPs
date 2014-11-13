#include<iostream>
#include<stdlib.h>
#include<stdio.h>

void gen(char *string, int index, int limit){

  if( index >= limit ){
    std::cout << string << "\n";
    return;
  }

  string[index] = '0';
  gen(string,index+1,limit);

  string[index] = '1';
  gen(string,index+1,limit);

  string[index] = '-';
  gen(string,index+1,limit);

}

int main(int argc, char *argv[]){

  int limit = atoi(argv[1]);
  char *string;

  string = (char *) malloc(limit *sizeof(char) + 1);

  gen(string, 0,limit);



  return 0;
}
