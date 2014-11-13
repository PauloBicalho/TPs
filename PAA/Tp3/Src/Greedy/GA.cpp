#include "GA.hpp"
#include <cstring>


char choose(char *string, int index, int window){
  int lzeros=0, rzeros=0;
  int lones=0, rones=0;

  int lindex = index-1;

  if( lindex >= 0 ){
    char llast = string[lindex];

    if( llast == '0' )
      lzeros += 1;
    else( llast == '1' )
      lones += 1;

    lindex-=1;
    while( lindex >= 0 and string[lindex] == llast ){
      if( llast == '0' )
        lzeros +=1;
      else if ( llast == '1' )
        lones += 1;
    }

  }

  
  char llast = string[index-1];

  if( llast == '0' ){
    lzeros+=1;
    for( int

  }


  for( int i=index-2; i>=l; i-- ){
    char c = string[i];
    if( c == '0' )
      lzeros++;
    else if( c == 1 )
  }

}


//return 0= False, 1= True, 2 = both
int solve(char *string){
  int size = strlen(string);


  int zeros=0; ones=0;
  int realzeros=0; realones=0;
  for(int i=0; i<size; i++){
    char c = string[i];


    if( c == '0' ){
      ones = 0;
      realones = 0;
      realzeros += 1;
      zeros += 1;
      if( realzeros == 3 )
        return 1;
    }
    else if( c == '1' ){
      zeros = 0;
      realzeros = 0;
      realones += 1;
      ones += 1;

      if( realones == 5 )
        return 1;
    } else {
      realzeros = 0;
      realones = 0;
      char r = choose( string, i, 4 );
      string[i] = r;

      if( r == '0' ){
        ones = 0;
        zeros += 1;
      } else {
        zeros = 0;
        ones += 1;
      }


    }

  }


}
