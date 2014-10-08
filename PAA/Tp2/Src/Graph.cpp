#include "Graph.hpp"

std::vector<int> * Graph::dfs( bool transpose=false, bool undirect=false, std::vector<int> * rOrder=NULL){
 
  int size = numberOfVertices;
  for(int i=0; i<size; i++){
    colors[i] = 0;
    dfsParent[i] = -1;
    dfsDiscoveredId[i] = -1;
  }

  std::vector<int> * finishTime = new std::vector<int> ();

  int dfsId = -1;
  for(int i=0; i<size; i++){
    int node = i;

    if( rOrder != NULL ) { node = rOrder->at( size - i -1); }
    
    if( colors[node] == 0 ){
  //    std::cout << "Dfs a partir de: " << node+1 << "\n";
      dfsId++;
      dfsDiscoveredId[node] = dfsId;
      dfs_visit(dfsId,node, finishTime, transpose, undirect);
    }
  }
  numberOfSCCs = dfsId+1;
  return finishTime;
}

void Graph::dfs_visit(int dfsId, int nodeU, std::vector<int> * finishTime, bool transpose, bool undirect){
  colors[nodeU] = 1;

  if( transpose or undirect){
    for(unsigned j=0; j<AdjT[nodeU].size(); j++){
      int nodeV = AdjT[nodeU][j];
      if( colors[nodeV] == 0 ){
        dfsParent[nodeV] = nodeU;
        dfsDiscoveredId[nodeV] = dfsId;
        dfs_visit(dfsId,nodeV,finishTime,transpose,undirect);
      }
    }
  }
  if( (!transpose) or undirect ){
    for(unsigned j=0; j<Adj[nodeU].size(); j++){
      int nodeV = Adj[nodeU][j];
      if( colors[nodeV] == 0 ){
        dfsParent[nodeV] = nodeU;
        dfsDiscoveredId[nodeV] = dfsId;
        dfs_visit(dfsId,nodeV,finishTime,transpose,undirect);
      }
    }
  }

  colors[nodeU] = 2;
  finishTime->push_back(nodeU);
}

void Graph::findSCCs(){
  this->sizeBSCC = 0;
  this->bSCC = -1;
  this->numberOfSCCs = 0;

  std::vector<int> * finishTime = dfs();
  dfs(true,false,finishTime);
  delete finishTime;


  std::vector<int> sccsSize (numberOfSCCs,0);
  sizeBSCC = 0;
  bSCC = -1;

 // std::cout << "\n";
  for(int i=0; i<numberOfVertices; i++){
    int sccId = dfsDiscoveredId[i];
    nodeSCC[i] = sccId;
   // std::cout << sccId << " ";
    
    sccsSize[sccId]++;

    if( sccsSize[sccId] > sizeBSCC ){
      sizeBSCC = sccsSize[sccId];
      bSCC = sccId;
    }
  }
 // std::cout << "\n";


} 

Graph * Graph::getCompactGraph(){
  Graph * compact = new Graph (numberOfSCCs);

  for(int i=0; i<numberOfVertices; i++){
    int sccI = nodeSCC[i];

    for(unsigned j=0; j<Adj[i].size(); j++){
      int vj = Adj[i][j];

      int sccJ = nodeSCC[vj];

      compact->safeAddEdge(sccI, sccJ);
    }
  }
  compact->setNodeType(bSCC, SCC);
  compact->setBSCC( bSCC );

  std::cout << "\n";

  return compact;
}

bool Graph::markNode(int n, NodeType type){
    if( nodesType[n] == type )
      return false;

    else if( nodesType[n] == DISC )
      nodesType[n] = type;

    else if( nodesType[n] == TA and type == TB )
      nodesType[n] = TUBE;
    
    else if( nodesType[n] == TB and type == TA )
      nodesType[n] = TUBE;
    else
      return false;

    return true;
}

//possivel erro, nao visita todos os nos (problema no if interno)
void Graph::markDfs(NodeType type, int nodeU, bool transpose=false, bool undirect=false){

//  colors[nodeU] = 1;
  if( transpose or undirect){
    for(unsigned j=0; j<AdjT[nodeU].size(); j++){
      int nodeV = AdjT[nodeU][j];
  //    if( colors[nodeV] == 0 and markNode(nodeV,type) ){
      if(  markNode(nodeV,type) ){
        markDfs(type,nodeV,transpose,undirect);
      }  
    }
  }
  if( (!transpose) or undirect ){
    for(unsigned j=0; j<Adj[nodeU].size(); j++){
      int nodeV = Adj[nodeU][j];
      //if( colors[nodeV] == 0 and markNode(nodeV,type) ){
      if(  markNode(nodeV,type) ){
        markDfs(type,nodeV,transpose,undirect);
      }
    }
  }

//  colors[nodeU] = 2;
}

void Graph::resetColors(){
  for(int i=0; i<numberOfVertices; i++)
    colors[i] = 0;
}


void Graph::findNodesTypes(){

  markDfs(OUT, bSCC);
  //resetColors();
  markDfs(IN, bSCC, true);
 // resetColors();

  for(int i=0; i<numberOfVertices; i++){
    if( nodesType[i] == IN ){
      markDfs(TA, i, false, true);
     // resetColors();
    } else if (nodesType[i] == OUT){
      markDfs(TB, i, true, true);
     // resetColors();
    }
  }
  
}

