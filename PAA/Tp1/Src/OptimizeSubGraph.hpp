#ifndef Optimize_Sub_Graph
#define Optimize_Sub_Graph

#include <algorithm>
#include "Graph.hpp"
#include "DisjointSetForest.hpp"

typedef std::pair< float, std::pair<int,int> > WeightEdge;
class OptimizeSubGraph{
  public:
    OptimizeSubGraph(Graph & graph) : g(graph) {};

    float optimize();

  private:
    Graph & g;

    std::pair<float,float> findMaxMinRatio(std::vector<Edge> & e);
    float MKruskal( std::vector<WeightEdge> );
    std::vector<WeightEdge>& transformEdges(std::vector<Edge> e, float r);
}



#endif // Optimize_Sub_Graph
