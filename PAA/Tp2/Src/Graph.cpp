#include "Graph.hpp"

std::stack<int> * Graph::dfs(bool transpose=false, int start=-1, bool findSCC=false){
  std::stack<int> * s = new std::stack<int> ();
  
  for( int i=0; i<numberOfVertices; i++ ){
    colors[i] = 0;
    dfs_parent[i] = -1;
  }
        
  if(start == -1){
    for( int i=0; i<numberOfVertices; i++ ){
      if( colors[i] == 0 )
        dfs_visit(i,*s,transpose,findSCC);
    }
  } else{
    dfs_visit(start,*s,transpose,findSCC);
  }
  
  return s;
}

void Graph::dfs_visit(int u,std::stack<int> & s,bool transpose=false,bool findSCC=false){
  colors[u] = 1;
  
  if(transpose){
    for(unsigned j =0; j<AdjT[u].size(); j++){
      int v = AdjT[u][j];
      if( colors[v] == 0 and (not findSCC or nodeSCC[v] == -1 ) ){
        dfs_parent[v] = u;
        dfs_visit(v, s, transpose);
      } 
    } 
  } else {
    for(unsigned j =0; j<Adj[u].size(); j++){
      int v = Adj[u][j];
      //if( colors[v] == 0 ){
      if( colors[v] == 0 and ( !findSCC or nodeSCC[v] == -1 ) ){
        dfs_parent[v] = u;
        dfs_visit(v, s, transpose);
      } 
    } 
  } 
  
  colors[u] = 2;
  s.push(u);
}

void Graph::findSCCs(){
  this->sizeBSCC = 0;
  this->bSCC = -1;
  this->numberOfSCCs = 0;

  finishStack = dfs(false);

  for(int i=0; i<numberOfVertices; i++)
    nodeSCC[i] = -1;

  int size = finishStack->size();
  for( int i = 0; i<size; i++ ){
    int node = finishStack->top();
    finishStack->pop();
    
    if( nodeSCC[node] == -1 )
      findNodeSCC(node); 
  }   
  
  std::cout << "\n";
  for(unsigned i=0; i<nodeSCC.size(); i++)
    std::cout << nodeSCC[i] << " ";
  std::cout << "\n";
} 

void Graph::findNodeSCC(int node){
  this->numberOfSCCs++;
  std::stack<int> * scc = dfs(true,node,true);
  int size = scc->size();
  
  if( size > this->sizeBSCC ){
    this->bSCC = this->numberOfSCCs-1;
    this->sizeBSCC = size;
  } 
    
  for( int i = 0; i<size; i++ ){
    int n = scc->top();
    scc->pop();
    nodeSCC[n] = this->numberOfSCCs-1;
  } 
    
}   


Graph Graph::getCompactGraph(){
  Graph compact (numberOfSCCs);

  for(int i=0; i<numberOfVertices; i++){
    int sccI = nodeSCC[i];

    for(int j=0; j<Adj[i].size(); j++){
      int vj = Adj[i][j];

      int sccJ = nodeSCC[vj];

      compact.safeAddEdge(sccI, sccJ);
    }
  }
  compact.setNodeType(bSCC, SCC);
  compact.setBSCC( bSCC );

  std::cout << "\n";

  return compact;
}

void Graph::markNodes( std::stack< int > * nodes, NodeType type ){
  int size = nodes->size();
  for(int i=0; i<size; i++){
    int n = nodes->top();
    nodes->pop();

    if( nodesTypes[n] == type )
      continue;

    else if( nodesTypes[n] == DISC )
      nodesTypes[n] = type;

    else if( nodesTypes[n] == TA and type == TB )
      nodesTypes[n] = TUBE;
    
    else if( nodesTypes[n] == TB and type == TA )
      nodesTypes[n] = TUBE;
      
  }
}

void Graph::findNodesTypes(){
  std::stack< int > * reached = dfs(false,bSCC, false);
  markNodes( reached, OUT );

  std::stack< int > * reaches = dfs(true ,bSCC, false);
  markNodes( reaches, IN );

  for(int i=0; i<nuberOfVertices; i++){
    if( nodesTypes[i] == IN ){
      std::stack< int > * reachedFromIn = dfs(false,i, false);
      markNodes( reachedFromIn, TA );
    }
    
    if( nodesTypes[i] == OUT ){
      std::stack< int > * reachesOut = dfs(false,i, false);
      markNodes( reachesOut, TB );
    }
  }

}
