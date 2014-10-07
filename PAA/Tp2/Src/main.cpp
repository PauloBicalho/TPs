#include "Graph.hpp"
#include <iostream>

int main(int argc, char **argv){
  Graph g (5);

  g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(2,0);
  
  g.addEdge(2,3);

  g.addEdge(3,4);
  g.addEdge(4,3);

  g.findSCCs();
  std::cout << "\n";
  
  int numberOfSCCs = g.getNumberOfSCCs();
  std::cout << g.getNumberOfSCCs() << "\n";
  std::cout << g.getBSCC() << "\n";
  std::cout << g.getSizeOfBSCC() << "\n";



  return 0;
}
