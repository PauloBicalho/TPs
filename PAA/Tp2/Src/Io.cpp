#include <iostream>
#include <fstream>
#include "Io.hpp"


Graph readGraph(char *fileName){
  int max = 0;

  std::ifstream fin1(fileName);
  while( fin1.good() ){
    int v1, v2;

    fin1 >> v1;

    if( not fin1.good() ) break;

    fin1 >> v2;

    if( v1 > max ) max = v1;
    if( v2 > max ) max = v2;
  }

  //fin.seekg(0, fin.beg);
  fin1.close();
  
  std::ifstream fin(fileName);

  Graph g (max);
  
  while( fin.good() ){
    int v1=-1, v2=-1;

    fin >> v1;

    if( not fin.good() ) break;

    fin >> v2;

    if( v1 != -1 and v2 != -1 )
      g.addEdge(v1-1,v2-1);
  }
  fin.close();

  return g;
}

void printNodesTypes(Graph *g, Graph *compact){
  int n = g->getNumberOfVertices();

  std::ofstream d("disconnected.txt");
  std::ofstream in("in.txt");
  std::ofstream scc("scc.txt");
  std::ofstream out("out.txt");
  std::ofstream ta("tendrils_a.txt");
  std::ofstream tb("tendrils_b.txt");
  std::ofstream tc("tendrils_c.txt");

  for(int i=0; i<n; i++){
    int sccId = g->getNodeSCC(i);
    Graph::NodeType type = compact->getNodeType(sccId);

    switch( type ){
    case Graph::DISC:
      d << i+1 << "\n";
      break;
    case Graph::IN:
      in << i+1 << "\n";
      break;
    case Graph::OUT:
      out << i+1 << "\n";
      break;
    case Graph::SCC:
      scc << i+1 << "\n";
      break;
    case Graph::TA:
      ta << i+1 << "\n";
      break;
    case Graph::TB:
      tb << i+1 << "\n";
      break;
    case Graph::TUBE:
      tc << i+1 << "\n";
      break;
    }
  }

  d.close(); in.close(); scc.close(); out.close();
  ta.close(); tb.close(); tc.close();
}

