#include "Graph.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv){

  int max = 0;

  std::ifstream fin (argv[1]);
  while( true ){
    int v1, v2;
    fin >> v1;

    if( fin.eof() )
      break;

    fin >> v2;

    if( v1 > max ) max = v1;
    if( v2 > max ) max = v2;
  }
  fin.close()

  Graph g (max);

  std::ifstream fin (argv[1]);
  while( true ){
    int v1, v2;
    fin >> v1;

    if( fin.eof() )
      break;

    fin >> v2;

    g.addEdge(v1,v2);
  }

/*
  g.addEdge(0,1);
  g.addEdge(1,2);
//  g.addEdge(2,0);
  
  g.addEdge(2,3);

  g.addEdge(3,4);
  g.addEdge(4,5);
  g.addEdge(5,2);
*/
  g.findSCCs();
  
  std::cout << g.getNumberOfSCCs() << "\n";
  std::cout << g.getBSCC() << "\n";
  std::cout << g.getSizeOfBSCC() << "\n";


  Graph compact = g.getCompactGraph();
  std::cout << "N Type: " << compact.getNodeType(2) << "\n";



  return 0;
}
