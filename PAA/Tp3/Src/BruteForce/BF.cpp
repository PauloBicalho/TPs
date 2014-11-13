#include "BF.hpp"
#include <cstring>
#include <iostream>

//return 0 = Flase, 1 = True, 2 = Both
int bf(char * string, int index, int size, int zeros, int ones){

  if( index >= size ){
    return 0;
  }
  
//  std::cout <<  "\n\n#####################";
//  std::cout << "String: "<< string << "\n";
//  std::cout << "Index: "<< index << "\n";
  
//  std::cout << "Size: "<< size << "\n";
//  std::cout << "Zeros: "<< zeros << "\n";
//  std::cout << "Ones: "<< ones << "\n";

  char c = string[index];
//  int localzeros = 0, localones = 0;
  while( index < size and c != '-'){ 

    if( c == '0'){
       ones = 0;
 //      localones = 0;
 //      localzeros ++;
       zeros ++;
      if( zeros == 3 ){
        //std::cout << "Result: True\n";
        return 1;
      } 
    }
    else if( c == '1' ){
      zeros = 0;
  //    localzeros = 0;
  //    localones ++;
      ones++;
      if( ones == 5 ){
       // std::cout << "Result: True\n";
        return 1;
      }

    } else {
      std::cout << "Error\n" << index << "\n" << c << "\n";
    }

    index ++;
    c = string[index];
  }


  if( c == '-' ){
    index ++;

    int r0=0, r1=0;

    zeros += 1;
    if( zeros >= 3 ) 
      r0 = 1;
    else
      r0 = bf(string,index,size,zeros,0);

    ones += 1;
    if( ones >= 5 )
      r1 = 1;
    else
      r1 = bf(string,index,size,0,ones);


    if( (r0 == 1 and r1 == 1) ){
      //std::cout << "Result: True\n";
      return 1;
    }
    else if( r0 == 0 and r1 == 0){
      //std::cout << "Result: False\n";
      return 0;
    }
    else{
      //std::cout << "Result: Both\n";
      return 2;
    }
  } 

  return 0;
}

int solve(char * string){
  int size = strlen(string);

  int r = 0;
  r = bf(string,0,size,0,0);
  return r;
}
