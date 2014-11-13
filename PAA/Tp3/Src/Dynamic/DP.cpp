#include "DP.hpp"
#include <vector>
#include <cstring>

//std::vector< std::vector<int> > matrix (10, std::vector<int> (size+1,0) );

int matrix[1000][10];

int solve(char *string){
  int size = strlen(string);

  //std::vector< std::vector<int> > matrix (10, std::vector<int> (size+1,0) );
  memset(matrix,0,sizeof(matrix));

  //std::vector< std::vector< std::vector<int> > > matrix (4, std::vector<std::vector<int> > (6, std::vector<int> (size+1,0) ) );

  for(int i=size; i >= 0; i-- ){
    matrix[i][3] = 1;
    matrix[i][9] = 1;
  }

  for(int k=size-1; k >= 0; k-- ){
    char c = string[k];

    for(int i=0; i<10; i++){
      if( i==3 or i==9 )
        continue;

      switch (c){
        case '0':
          //if reading a sequence of 0's increase the sequence, else start the sequence
          ( i<3 ) ? matrix[k][i] = matrix[k+1][i+1] : matrix[k][i] = matrix[k+1][1];
          break;
        case '1':
          ( i>3 ) ? matrix[k][i] = matrix[k+1][i+1] : matrix[k][i] = matrix[k+1][5];
          break;
        case '-':
          if( i<3 ){
            if( matrix[k+1][i+1] == 1 and matrix[k+1][5] == 1 )
              matrix[k][i] = 1;
            else if( matrix[k+1][i+1] == 0 and matrix[k+1][5] == 0 )
              matrix[k][i] = 0;
            else
              matrix[k][i] = 2;
          } else {
            if( matrix[k+1][i+1] == 1 and matrix[k+1][1] == 1 )
              matrix[k][i] = 1;
            else if( matrix[k+1][i+1] == 0 and matrix[k+1][1] == 0 )
              matrix[k][i] = 0;
            else
              matrix[k][i] = 2;
          }
          break;
      }
    }
  }
  
  return matrix[0][0];
}
