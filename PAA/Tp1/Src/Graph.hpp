#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <utility>


typedef std::pair<  std::pair<int,int>,std::pair<int,int> >  Edge;

class Graph{
  public:

   Graph() {};

    inline void insertVertices(const int size){
      for(int i = 0; i < size; i++)
        vertices.push_back(i);
    };

    inline void insertEdge(const int v1,const int v2,const int friendship,const int distance){
      Edge e = std::make_pair( std::make_pair(v1,v2),std::make_pair(friendship,distance) );
      edges.push_back(e);
    };

    inline const std::vector<Edge>& getEdges(){
      return edges;
    };

    inline int getNumberOfVertices(){
      return (int) vertices.size();
    };


  private:

    std::vector<int> vertices;
    std::vector< Edge > edges;
    

};









#endif //Graph_hpp
