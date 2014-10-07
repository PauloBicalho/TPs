#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <stack>

class Graph{
  public:

    Graph(int n): Adj(n), AdjT(n), nodesType(n,0), nodeSCC(n,-1) numberOfVertices(n), numberOFSCC(-1) {
      finishStack = new std::stack<int> ();
    }

    inline void addEdge(int vFrom,int vTo){
      Adj[vFrom].push_back(vTo);
      AdjT[vTo].push_back(vFrom);
    };

    inline std::stack<int> dfs( bool transpose=false, int start=-1 ){
      std::stack<int> s = new std::stack<int> ();
      
      for( int i=0; i<numberOfVertices; i++ ){
        colors[i] = 0;
        dfs_parent[i] = -1;
      }
      
      if(start == -1){
        for( int i=0; i<numberOfVertices; i++ ){
          if( colors[i] == 0 )
            dfs_visit(i,s,transpose);
        }
      }
      else{
        dfs_visit(start,s,transpose);
      }
      return s;
    }
    
    inline void dfs_visit(int u,std::stack<int> & s,bool transpose=false){
      colors[u] = 1;
      
      if(transpose){
        for(int j =0; j<AdjT[u].size(); j++){
          int v = AdjT[u][j];
          if( colors[v] == 0 ){
            dfs_parent[v] = u;
            dfs_visit(v);
          }
        }
      } else {
        for(int j =0; j<Adj[u].size(); j++){
          int v = Adj[u][j];
          if( colors[v] == 0 ){
            dfs_parent[v] = u;
            dfs_visit(v);
          }
        }
      }
    
      colors[node] = 2;
      s->push(u);
    }

    inline void findSCCs(){
      this->sizeBSCC = 0;
      this-bSCC = -1;
      this->numberOfSCCs = -1;
      finishStack = dfs(false);

      for( int i = 0; i<finishStack->size(), i++ ){
        int node = finishStack->top();
        finishStack->pop();

        if( nodeSCC[node] == -1 )
          findNodeSCC(node);
      }

    }

    inline void findNodeSCC(int node){
      this->numberOfSCCs++;
      std::stack<int> * scc = dfs(true,node);
      int size = scc->size();

      if( size > this->sizeBSCC ){
        this->bSCC = this->numberOfSCCs;
        this->sizeBSCC = size;
      }

      for( int i = 0; i<size; i++ ){
        int n = scc->top();
        scc->pop();
        nodeSCC[n] = this->numberOfSCCs;
      }
    }

    inline int getNodeSCC(int node) { return nodeSCC[node]; }
    
    inline void setNodeType(int node,int type){ nodeSCC[node] = type; }

    

  private:

    int numberOfVertices;
    int numberOfSCCs;
    int sizeBSCC;

    std::vector< int > colors;
    std::vector< int > dfs_parent;
    std::vector< int > nodeSCC;
    std::vector< int > nodesType; 
    std::vector< std::vector<int> > Adj;
    std::vector< std::vector<int> > AdjT;  //transpose graph

    std::stack< int > * finishStack;

};



#endif // Graph_hpp
