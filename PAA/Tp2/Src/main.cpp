#include <iostream>

#include "Graph.hpp"
#include "Io.hpp"

int main(int argc, char **argv){

  Graph g = readGraph(argv[1]);
  g.findSCCs();

  int n = g.getNumberOfVertices();
  print(n, "Number Of Vertices: ");
  
  int bscc = g.getBSCC();
  int size = g.getSizeOfBSCC();
  print(bscc, "Bigest SCC id: ");
  print(size, "Bigest SCC size: ");
  
//  std::cout << g.getNumberOfSCCs() << "\n";
//  std::cout << g.getBSCC() << "\n";
//  std::cout << g.getSizeOfBSCC() << "\n";


  Graph * compact = g.getCompactGraph();
//  std::cout << "N Type: " << compact.getNodeType(2) << "\n";
//
 

  int nc = compact->getNumberOfVertices();
  print(nc, "Compact Number Of Vertices: ");
  print("", "Finding");
  compact->findNodesTypes();

  print("", "Printing");
  printNodesTypes(&g, compact);
  
  delete compact;

  return 0;
}
