#ifndef Io_hpp
#define Io_hpp

#include "Graph.hpp"
#include <iostream>

Graph readGraph(char *fileName);

void printNodesTypes(Graph *g, Graph *compact);

template<typename T>
void print(T s, const char *prefix = ""){
  std::cout << prefix << s << std::endl; 
}

#endif //io.hpp
