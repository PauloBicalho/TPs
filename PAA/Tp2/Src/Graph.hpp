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

    Graph(int n): numberOfVertices(n), numberOfEdges(0), numberOfSCCs(-1), Adj(n), AdjT(n), 
      nodesType(n,DISC), nodeSCC(n,-1), colors(n), dfsParent(n), dfsDiscoveredId(n,-1) {;};

    inline void addEdge(int vFrom,int vTo){
      Adj[vFrom].push_back(vTo);
      AdjT[vTo].push_back(vFrom);

      numberOfEdges++;
    };

    inline void safeAddEdge(int vFrom, int vTo){

      bool insert=true;
      for(unsigned i=0; i<Adj[vFrom].size(); i++){
        if( Adj[vFrom][i] == vTo ){
          insert=false;
          break;
        }
      }

      if( insert ){ 
        Adj[vFrom].push_back(vTo);
        AdjT[vTo].push_back(vFrom);
        numberOfEdges++;
      }

      /*insert=true;
      for(unsigned i=0; i<AdjT[vTo].size(); i++){
        if( AdjT[vTo][i] == vFrom ){
          insert=false;
          break;
        }
      }
      
      if( insert ) AdjT[vTo].push_back(vFrom);*/
    }

    //std::stack<int>* dfs( bool transpose, int start, bool findSCC, bool undirect );
    //void dfs_visit(int u,std::stack<int> & s,bool transpose, bool findSCC, bool undirect);

    std::vector<int>* dfs( bool transpose, bool undirect, std::vector<int> * rOrder);
    void dfs_visit(int dfsId, int nodeU, std::vector<int> * finishTime, bool transpose, bool undirect);

    void findSCCs();
    void findNodeSCC(int node);


    inline int getNodeSCC(int node) { return nodeSCC[node]; };
    inline NodeType getNodeType(int node ){ return nodesType[node]; };

    inline int getNumberOfVertices() { return numberOfVertices; };
    inline int getNumberOfEdges() { return numberOfEdges; };
    inline int getNumberOfSCCs() { return numberOfSCCs; };
    inline int getSizeOfBSCC() { return sizeBSCC; };
    inline int getBSCC(){ return bSCC; };
    
    inline void setNodeType(int node, NodeType type ){ nodesType[node] = type; };
    inline void setBSCC(int i){ bSCC=i; };


    void resetColors();
    void markDfs(NodeType type, int nodeU, bool transpose, bool undirect);
    bool markNode(int n, NodeType type);
    void findNodesTypes();

    Graph * getCompactGraph();

  private:


    int numberOfVertices;
    int numberOfEdges;
    int numberOfSCCs;
    int sizeBSCC;
    int bSCC;

    std::vector< std::vector<int> > Adj;
    std::vector< std::vector<int> > AdjT;  //transpose graph
    
    std::vector< NodeType > nodesType; 
    std::vector< int > nodeSCC;
    std::vector< int > colors;
    std::vector< int > dfsParent;
    std::vector< int > dfsDiscoveredId;


};


#endif // Graph_hpp
