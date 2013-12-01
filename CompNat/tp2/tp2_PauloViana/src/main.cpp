#include <iostream>
#include <string>
#include <stdlib.h>
//#include <stdlib.h>

#include "Constraints.h"
#include "ACO.h"




int main(int argc, char *argv[]){

  if(argc != 8){
    std::cout << "Error\n  Usage: <fileName:string> <numAnts:int> <maxIterations:int> <evaporateRate:double> <alpha:double> <beta:double> <seed:int>" << endl;
    return 1;
  }

  char * fileName = argv[1];
  int numAnts = atoi(argv[2]);
  int maxIterations = atoi(argv[3]);
  double evaporateRate = atof(argv[4]);
  double alpha = atof(argv[5]);
  double beta = atof(argv[6]);
  int seed = atoi(argv[7]);

  const Constraints cons (fileName);

//  std::cout << maxPh << endl;
  ACO aco (cons , numAnts, maxIterations, evaporateRate, alpha, beta, seed );

  aco.execute();
//  std::cout << "BestMakespanEver: " << aco.getBestMakespan() << endl;

//  Solution sol = aco.getBestSolution();

//  std::cout << sol;

  return 0;
}
