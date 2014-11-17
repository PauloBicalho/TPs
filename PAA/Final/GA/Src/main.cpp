#include <iostream>
#include <fstream>
#include "GA.hpp"


int main(int argc, char *argv[]){
  std::ifstream fin (argv[1]);

  int numPoints=0, numMedians=0; 
  
  fin >> numPoints;
  fin >> numMedians;

  GA ga(1,1,0.5,0.5,3,numMedians,1);

  for(int i=0; i<numPoints; i++){
    int x=0, y=0, capacity=0, demand=0; 
    
    fin >> x;
    fin >> y;
    fin >> capacity;
    fin >> demand;

    ga.insertPoint(x,y,capacity,demand);
  }

  ga.calcDistances();

  
  return 0;
}
