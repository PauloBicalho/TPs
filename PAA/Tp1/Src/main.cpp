#include <iostream>
#include "Graph.hpp"

int main(int argc, char * argv[]){



  /* Graph Text --- Ok !
  Graph g;

  g.insertVertices(10);
  g.insertEdge(1,2,2000,10);
  g.insertEdge(1,3,20,1);
  g.insertEdge(5,8,100,50);

  std::cout << g.getNumberOfVertices() << std::endl;

  std::vector<Edge> e = g.getEdges();
  std::cout << e.size() << std::endl;

  for(std::vector<Edge>::iterator it = e.begin(); it != e.end(); ++ it){
    std::cout << it->first.first << " - " << it->first.second << " = ";
    std::cout << "(" <<  it->second.first << "," << it->second.second << ")";
    std::cout << std::endl;
  }
  
 // */
  
  /* DisjointSetFores Test --  OK!
  DisjointSetForest dsf (10);

  std::cout << dsf.getSetCount() << std::endl;

  dsf.unionSet(1,2);
  dsf.unionSet(1,4);
  dsf.unionSet(2,5);

  std::cout<< dsf.findSet(1) << " - " << dsf.findSet(2) << std::endl;
  std::cout<< dsf.findSet(4) << " - " << dsf.findSet(5) << std::endl;
  std::cout<< dsf.findSet(3) << " - " << dsf.findSet(6) << std::endl;
  std::cout << dsf.getSetCount() << std::endl;
  */


  return 0;
}
