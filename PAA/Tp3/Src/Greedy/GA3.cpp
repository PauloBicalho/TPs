#include "GA.hpp"
#include <cstring>
#include<iostream>

char choose(char *string, int size, int index, int window){
  int leftvalue = 0;
  int rightvalue = 0;
  int rightopen = 0;
  
  if( index > 0 and index < size){

    if( string[index-1] == string[index+1] )
      return string[index-1];

    char cleft = string[index-1];
    leftvalue++;
    
    for(int i = index-2; i>=0 and index - i <= 4; i--){
      if( string[i] != cleft )
        break;
        
      leftvalue++;
    }

    char cright = string[index+1];
    rightvalue++;

    if( cright == '-' )
      rightopen++;

    for(int i = index+2; i<size and i-index <= 4; i++){
      if( cright != '-' and string[i] != '-' and string[i] != cright )
        break;

      if( cright == '-' and string[i] != cright )
        cright = string[i];

      if( cright == '-' and string[i] == '-' )
        rightopen++;

      rightvalue++;
    }

    if( cleft == cright )
      return cleft;

    if( cleft == '0' and ( leftvalue == 2 or leftvalue + rightopen >= 2 ) )
      return '0';
    if( cleft == '1' and ( leftvalue == 4 or leftvalue + rightopen >= 4) )
      return '1';

    if( cright == '0' and ( rightvalue == 2 ) )
      return '0';

    if( cright == '1' and ( rightvalue == 4 ) )
      return '1';

    return '0';
  } else if(index == 0 ){

    for( int i = 1; i < size and i <= 5; i++ )
      if( string[i] == '-' ){
        rightopen++;
        if(rightopen == 2)
          return '0';
      }else
        return string[i];

    return '0';
  } else{
    for( int i = size-1; i>=0 and index - i <= 4; i-- )
      if( string[i] != '-' )
        return string[i];

    return '0';
  }

}

int findTrue(char *string){
  int size = strlen(string);

  int zeros=0, ones=0;
  for(int i=0; i<size; i++){
    char c = string[i];

    if( c == '0' ){
      ones = 0;
      zeros++;
      if( zeros == 3 )
        return 1;
    } else if( c == '1' ){
      zeros = 0;
      ones++;
      if( ones == 5 )
        return 1;
  
    } else {
      if( zeros ==  2 ){
        zeros = 0;
        ones++;
      } else if( ones == 4 ){
        ones = 0;
        zeros++;
      } else {
        ones = 0;
        zeros = 0;
      }

    }

  }
  return 2;
}


//return 0= False, 1= True, 2 = both
int solve(char *string){
  int t = findTrue(string);

  if( t == 1 )
    return 1;
  
  int size = strlen(string);
  int zeros=0, ones=0; 
  int ret = 0;

  for(int i=0; i<size; i++){
    char c = string[i];


    if( c == '0' ){
      ones = 0;
      zeros += 1;
      if( zeros == 3 )
        ret = 2;
    }
    else if( c == '1' ){
      zeros = 0;
      ones += 1;
      if( ones == 5 )
        ret = 2;
    } else {
      char r = choose( string, size, i, 4 );
      string[i] = r;

      if( r == '0' ){
        ones = 0;
        zeros += 1;
        if( zeros == 3 )
          ret = 2;
      } else {
        zeros = 0;
        ones += 1;
        if( ones == 5 )
          ret = 2;
      }

    }

  }
  return ret;
}
