#include "OptimizeSubGraph.hpp"

float OptimizeSubGraph::optimize(){

  Edges& e = g.getEdges();
  std::pair<float,float> maxMin = findMaxMinRatio( e );

  float max = maxMin.first;
  float min = maxMin.second;
  float guess = min + ( (max - min) / 2.0 );

  float value = guess -1;


  while( value < guess ){

    std::vector<WeightEdge>& weightEdges = transformEdges(e,guess);
    value = MKruskal(weightEdges);

    max = value;
  }

  return value;
}

float OptimizeSubGraph::MKruskal( std::vector<WeightEdge> edges){

  DisjointSetForest dsf (g.getNumberOfVertices);
  std::sort(edges.begin(), edges.end());  //ascending order

  float value = 0.0;
  for(int i=edges.size()-1; i >= 0; i--){
    int v1 = edges[i].second.first;
    int v2 = edges[i].second.first;
    float w edges[i].first;

    v1Set = dsf.findSet(v1);
    v2Set = dsf.findSet(v2);

    if( v1 != v2 ){
      value += w;
      dsf.unionSet(v1,v2);

      edges.erase(edges.begin() + i);
      i++;
    }
  }

  if( dsf.countSets() > 1 )
    value = -1.000
  else{
    for(std::vector<WeightEdge>::iterator it=edges.begin(); it != edges.end(); ++it ){
      if( it.first > 0 )
        value += it.first;
    }
  }

  return value;
}


std::vector<WeightEdge>& OptimizeSubGraph::transformEdges(std::vector<Edge> e, float r){
  std::vector<WeightEdge> te; 

  for(std::vector<Edge>::iterator it = e.begin(); it != e.end(); ++ it){
    float w = it->second.first - ( r * it->second.second );
    te.push_back( std::make_pair(w, it->first) );
  }

  return te;
}

std::pair<float,float> OptimizeSubGraph::findMaxMinRatio(std::vector<Edge>& e){
  float max = 0,min = 9999999 ;

  for(std::vector<Edge>::iterator it=e.begin(); it != e.end(); ++it){
    float ratio = it->second.first / (float) it->second.second;

    if( ratio > max )
      max = ratio;
    if( ratio < min )
      min = ratio;
  }

  return std::make_pair(max,min);
}
