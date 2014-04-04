#include <iostream>
#include <fstream>

#include "Backend.h"

using namespace std;

int main(int argc, char*argv[]){

  if(argc != 2 ){
    cerr << "Error nos parâmetros\n";
    cerr << "\t" << argv[0] << " <file name>\n";
    exit(-1);
  }

  ifstream in(argv[1]);
    //std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf

  cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
  
  
  Backend back;

  back.program();

  return 0;
}
