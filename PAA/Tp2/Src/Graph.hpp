#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <vector>
#include <stack>

class Graph{
  public:
    enum NodeType{
      DISC,SCC,IN,OUT,TA,TB,TUBE
    };

    Graph(int n): numberOfVertices(n), numberOfSCCs(-1), Adj(n), AdjT(n), 
      nodesType(n,DISC), nodeSCC(n,-1), colors(n), dfs_parent(n){;};

    inline void addEdge(int vFrom,int vTo){
      Adj[vFrom].push_back(vTo);
      AdjT[vTo].push_back(vFrom);
    };

    inline void safeAddEdge(int vFrom, int vTo){

      bool insert=true;
      for(unsigned i=0; i<Adj[vFrom].size(); i++){
        if( Adj[vFrom][i] == vTo ){
          insert=false;
          break;
        }
      }

      if( insert ) Adj[vFrom].push_back(vTo);

      insert=true;
      for(unsigned i=0; i<AdjT[vTo].size(); i++){
        if( AdjT[vTo][i] == vFrom ){
          insert=false;
          break;
        }
      }
      
      if( insert ) AdjT[vTo].push_back(vFrom);
    }

    std::stack<int>* dfs( bool transpose, int start, bool );
    void dfs_visit(int u,std::stack<int> & s,bool transpose, bool);

    void findSCCs();
    void findNodeSCC(int node);

    Graph getCompactGraph();

    inline int getNodeSCC(int node) { return nodeSCC[node]; };
    inline NodeType getNodeType(int node ){ return nodesType[node]; };
    inline int getNumberOfSCCs() { return numberOfSCCs; };
    inline int getSizeOfBSCC() { return sizeBSCC; };
    inline int getBSCC(){ return bSCC; };
    
    inline void setNodeType(int node, NodeType type ){ nodesType[node] = type; };
    inline void setBSCC(int i){ bSCC=i; };


  private:


    int numberOfVertices;
    int numberOfSCCs;
    int sizeBSCC;
    int bSCC;

    std::vector< std::vector<int> > Adj;
    std::vector< std::vector<int> > AdjT;  //transpose graph
    
    std::vector< NodeType > nodesType; 
    std::vector< int > nodeSCC;
    std::vector< int > colors;
    std::vector< int > dfs_parent;

    std::stack< int > * finishStack;

};


#endif // Graph_hpp
