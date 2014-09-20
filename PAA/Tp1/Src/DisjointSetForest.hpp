#ifndef Disjoint_Set_Forest
#define Disjoint_Set_Forest

#include <iostream>
#include <vector>


class DisjointSetForest{
  public:
    DisjointSetForest() : setCount(0) {}
    
    DisjointSetForest(const int size) : setCount(0){
      for(int i = 0; i < size; i++){
        makeSet(i);
      }
    }

    inline void makeSet(const int i){
      elements_parent.push_back(i);
      elements_rank.push_back(0);
      setCount++;
    }

    inline void unionSet(const int x, const int y){
      int rootIdX = findSet(x);
      int rootIdY = findSet(y);

      link(rootIdX, rootIdY);
    }

    inline int findSet(int i){
      int& parent = elements_parent[i];

      if( parent != i )
        parent = findSet(parent);

      return parent;
    }

    inline int getSetCount(){
      return setCount;
    }

      
  private:
    std::vector<int> elements_parent;
    std::vector<int> elements_rank;

    int setCount;

    inline void link(int x, int y){
      int xRank = elements_rank[x];
      int yRank = elements_rank[y];

      if(xRank > yRank){
        elements_parent[y] = x;
      } else {
        elements_parent[x] = y;

        if(xRank == yRank)
          elements_rank[y]++;

      }
      setCount--;
    }

};



#endif //Disjoint Set Forest
