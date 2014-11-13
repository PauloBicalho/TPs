#include "GA.hpp"
#include <cstring>
#include<iostream>

char choose(char *string, int size, int index, int window){
  int leftvalues[2] = {0,0};
  int rightvalues[2] = {0,0};
  

  if( index > 0 and index <= size){

    if( string[index-1] == string[index+1] )
      return string[index-1]+20;

    char llast = string[index-1];
      leftvalues[ llast % 2 ]++;

      for(int i = index-2; i>=0 and index - i <= 4; i--){
        if( (string[i] % 2) != (llast % 2) )
          break;
        
        leftvalues[ string[i] % 2 ]++;
    }

    char rlast = string[index+1];
    if( rlast != '-' ){
      rightvalues[ rlast % 2 ]++;
      
      for(int i = index+2; i<size and i-index <= 4; i++){
        if( ( (string[i] % 2) != (rlast % 2) ) or string[i] == '-' )
          break;
        
        rightvalues[ string[i] % 2 ]++;
      }
    }

//    std::cout << llast << " - " << leftvalues[0] << "\n";
//    std::cout << rlast << " - " << rightvalues[1] << "\n";
    if( (llast == '0' and leftvalues[0] == 2) and (rlast=='1' and rightvalues[1]==4) )
      return '2';
    
    if( (llast == '1' and leftvalues[1] == 4) and (rlast=='0' and rightvalues[0]==2) )
      return '2';


    if( leftvalues[llast % 2] > rightvalues[rlast % 2] )
      return (llast < 50 ) ? llast + 20 : llast;
    else if( leftvalues[llast % 2] < rightvalues[rlast % 2] )
      return (rlast < 50) ? rlast +20 : rlast;
    else
      return '0'+20;
    
  } else if(index == 0 ){
    for( int i = 1; i < size and i <= 5; i++ )
      if( string[i] != '-' )
        return string[i]+20;

    return '0'+20;
  } else{
    for( int i = size-1; i>=0 and index - i <= 4; i-- )
      if( string[i] != '-' )
        return ( string[i] < 50 )? string[i]+20: string[i];

    return '0'+20;

  }
  

}



//return 0= False, 1= True, 2 = both
int solve(char *string){
  int size = strlen(string);


  int zeros=0, ones=0;
  int realzeros=0, realones=0;
  
  int ret = 0;

  for(int i=0; i<size; i++){
    char c = string[i];


    if( c == '0' ){
      ones = 0;
      realones = 0;
      realzeros += 1;
      zeros += 1;
      if( realzeros == 3 )
        return 1;
      if( zeros == 3 )
        ret = 2;
    }
    else if( c == '1' ){
      zeros = 0;
      realzeros = 0;
      realones += 1;
      ones += 1;

      if( realones == 5 )
        return 1;
      if( ones == 5 )
        ret = 2;
    } else {
      realzeros = 0;
      realones = 0;
      
      char r = choose( string, size, i, 4 );
      string[i] = r;

      if( r == '2' ){
        return 1;
      }
      
      if( r % 2 == 0 ){
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
