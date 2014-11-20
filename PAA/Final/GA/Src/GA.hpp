#ifndef GA_HPP
#define GA_HPP

#include <chrono>
#include <random>

#include <vector>
#include <climits>
#include <utility>
#include <algorithm>

class GA{

  private:

    int populationSize, maxGenerations;
    double mutationProb, crossoverProb;
    int k, medians, numPoints, seed;
    
    std::vector< std::vector<int> > pop;
    std::vector< int > fitness;

    class Point{
      public:
        int x;
        int y;
        int capacity;
        int demand;
    };

    //coordenadas x,y e oferta,demanda
    //std::vector< std::pair< std::pair<int,int>,std::pair<int,int> > > points;
    std::vector< Point > points;
    std::vector< std::vector<double> > distances;


    void initPop();


    void crossover(int index1,int index2);
    void mutation(int index);

    int selectParent(int size);

    int randomInt();
    double randomReal();


    void getClosestIndex( int point, std::vector< int > &medians, std::vector< int > &capacities );

    int getCapacity(int pointId){
      return points[pointId].capacity;
    }
    
    int getDemand(int pointId){
      return points[pointId].demand;
    }

    std::vector< int > getPriorityByDemand();
  
  public:

    GA(int popSize, int iterations, double mutProb, double crossProb, int tournamentSize, 
        int p, int randomSeed) : populationSize(popSize), maxGenerations(iterations), 
        mutationProb(mutProb), crossoverProb(crossProb), k(tournamentSize), medians(p), 
        numPoints(0), seed(randomSeed), pop(popSize, std::vector<int> (p) ), fitness(p,INT_MAX), points(), 
        distances() {;}

    inline void insertPoint(int x, int y, int o, int d){
      Point p;
      p.x = x; p.y = y; p.capacity = o; p.demand = d;
      points.push_back(p);
      this->numPoints++;
    }

    void calcDistances();
    void calcFitness(int mode);


};


#endif // GA_HPP
