#include "Graph.hpp"
#include <iostream>

int main(int argc, char **argv){
  Graph g (6);

  g.addEdge(0,1);
  g.addEdge(1,2);
//  g.addEdge(2,0);
  
  g.addEdge(2,3);

  g.addEdge(3,4);
  g.addEdge(4,5);
  g.addEdge(5,2);

  g.findSCCs();
  
  std::cout << g.getNumberOfSCCs() << "\n";
  std::cout << g.getBSCC() << "\n";
  std::cout << g.getSizeOfBSCC() << "\n";


  Graph compact = g.getCompactGraph();
  std::cout << "N Type: " << compact.getNodeType(2) << "\n";



  return 0;
}
