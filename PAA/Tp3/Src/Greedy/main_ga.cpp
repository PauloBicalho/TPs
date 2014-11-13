#include <iostream>
#include <fstream>
#include "GA.hpp"



int main(int argc,char **argv){

  std::ifstream fin(argv[1]);

  int size;
  fin >> size;

  for(int i=0; i<size; i++){
    char line[2000];
    fin >> line;
    //std::cout << line << "\n";

    int r = solve(line);
    //std::cout << line << "\n";

    if( r == 0 )
      std::cout << "false\n";
    else if( r == 1 )
      std::cout << "true\n";
    else
      std::cout << "both\n";

  }

}
