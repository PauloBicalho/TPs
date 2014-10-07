#include "OptimizeSubGraph.hpp"

float OptimizeSubGraph::optimize(){

  const std::vector<Edge>& e = g.getEdges();
  std::pair<float,float> maxMin = findMaxMinRatio( e );

  float max = maxMin.first + 1;
  float min = 0;
  float guess = min + ( (max - min) / 2.0 );

  float bestValue = min;

  while( max - min > 0.0001   ){
    //std::cout << "(Max,Min) = " << max << "," << min << std::endl;

    guess = min + ( (max - min) / 2.0 );

    std::vector<WeightEdge> weightEdges = transformEdges(e,guess);

    float verify = MKruskal(weightEdges);
    //std::cout << guess << " = " << verify << std::endl;

    if(verify == -1.000)
      return verify;

    if( verify >= 0 ){
      min = guess;
      bestValue = guess;
    }
    else
      max = guess;

  }

  return bestValue;
}

float OptimizeSubGraph::MKruskal( std::vector<WeightEdge> edges){

  DisjointSetForest dsf (g.getNumberOfVertices());
  std::sort(edges.begin(), edges.end());  //ascending order

  float value = 0.0;
  for(int i=edges.size()-1; i >= 0; i--){
    int v1 = edges[i].second.first;
    int v2 = edges[i].second.second;
    float w =  edges[i].first;

    int v1Set = dsf.findSet(v1);
    int v2Set = dsf.findSet(v2);

    if( v1Set != v2Set ){

      value += w;
      dsf.unionSet(v1,v2);

      edges.erase(edges.begin() + i);
      i++;
    }
  }

  if( dsf.countSets() > 1 )
    value = -1.000;
  else{
    for(std::vector<WeightEdge>::iterator it=edges.begin(); it != edges.end(); ++it ){
      if( it->first > 0 )
        value += it->first;
    }
  }

  return value;
}


std::vector<WeightEdge> OptimizeSubGraph::transformEdges(std::vector<Edge> e, float r){
  std::vector<WeightEdge> te; 

  for(std::vector<Edge>::iterator it = e.begin(); it != e.end(); ++ it){
    float w = it->second.first - ( r * it->second.second );
    te.push_back( std::make_pair(w, it->first) );
  }

  return te;
}

std::pair<float,float> OptimizeSubGraph::findMaxMinRatio(const std::vector<Edge>& e){
  float max = 0,min = 9999999 ;

  for(std::vector<Edge>::const_iterator it=e.begin(); it != e.end(); ++it){
    float ratio = it->second.first / (float) it->second.second;

    if( ratio > max )
      max = ratio;
    if( ratio < min )
      min = ratio;
  }

  return std::make_pair(max,min);
}
