#include <iostream>
#include <cstdio>
#include "Graph.hpp"
#include "OptimizeSubGraph.hpp"
#include <cstring>

bool readLine(int & v1,int &v2,int &f,int &d ){
  char line[256];
  std::cin.getline(line,256);
  
  if( strcmp(line,"") == 0 )
    return false;

  sscanf(line,"%d %d %d %d",&v1,&v2,&f,&d);
  
  return true;
}



int main(int argc, char * argv[]){

  Graph * g;
  do{
    g = new Graph();

    int number_of_vertices = -1;
    char line[256]= "-1";

    std::cin.getline(line,256);
    sscanf(line, "%d", &number_of_vertices);

    if( number_of_vertices == -1 ) break;

    g->insertVertices(number_of_vertices);

    int v1, v2, f, d;
    while( readLine(v1,v2,f,d) ){
      g->insertEdge(v1-1,v2-1,f,d);
    }

    OptimizeSubGraph osg (*g);
    float v = osg.optimize();
    printf("%.3f\n", v);

    delete g;
  } while( std::cin );

  

  return 0;
}
