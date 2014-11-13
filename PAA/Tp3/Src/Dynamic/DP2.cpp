#include "DP.hpp"
#include <vector>
#include <cstring>

//std::vector< std::vector<int> > matrix (10, std::vector<int> (size+1,0) );

int matrix[10][1000];

int solve(char *string){
  int size = strlen(string);

  //std::vector< std::vector<int> > matrix (10, std::vector<int> (size+1,0) );
  memset(matrix,0,sizeof(matrix));

  //std::vector< std::vector< std::vector<int> > > matrix (4, std::vector<std::vector<int> > (6, std::vector<int> (size+1,0) ) );

  for(int i=size; i >= 0; i-- ){
    matrix[3][i] = 1;
    matrix[9][i] = 1;
  }

  for(int k=size-1; k >= 0; k-- ){
    char c = string[k];

    for(int i=0; i<10; i++){
      if( i==3 or i==9 )
        continue;

      switch (c){
        case '0':
          //if reading a sequence of 0's increase the sequence, else start the sequence
          ( i<3 ) ? matrix[i][k] = matrix[i+1][k+1] : matrix[i][k] = matrix[1][k+1];
          break;
        case '1':
          ( i>3 ) ? matrix[i][k] = matrix[i+1][k+1] : matrix[i][k] = matrix[5][k+1];
          break;
        case '-':
          if( i<3 ){
            if( matrix[i+1][k+1] == 1 and matrix[5][k+1] == 1 )
              matrix[i][k] = 1;
            else if( matrix[i+1][k+1] == 0 and matrix[5][k+1] == 0 )
              matrix[i][k] = 0;
            else
              matrix[i][k] = 2;
          } else {
            if( matrix[i+1][k+1] == 1 and matrix[1][k+1] == 1 )
              matrix[i][k] = 1;
            else if( matrix[i+1][k+1] == 0 and matrix[1][k+1] == 0 )
              matrix[i][k] = 0;
            else
              matrix[i][k] = 2;
          }
          break;
      }
    }
  }
  
  return matrix[0][0];
}
