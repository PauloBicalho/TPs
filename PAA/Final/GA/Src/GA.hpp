#ifndef GA_HPP
#define GA_HPP

#include <chrono>
#include <random>

#include <vector>
#include <climits>
#include <utility>

class GA{

  public:

    GA(int popSize, int iterations, double mutProb, double crossProb, int tournamentSize, 
        int p, int randomSeed) : populationSize(popSize), maxGenerations(iterations), 
        mutationProb(mutProb), crossoverProb(crossProb), k(tournamentSize), medians(p), 
        numPoints(0), seed(randomSeed), pop(popSize, std::vector<int> (p) ), fitness(p,INT_MAX), points(), 
        distances() {;}




    inline void insertPoint(int x, int y, int o, int d){
      points.push_back( std::make_pair(std::make_pair(x,y),std::make_pair(o,d)) );
      this->numPoints++;
    }

    void calcDistances();

  private:

    int populationSize, maxGenerations;
    double mutationProb, crossoverProb;
    int k, medians, numPoints, seed;
    
    std::vector< std::vector<int> > pop;
    std::vector< int > fitness;

    //coordenadas x,y e oferta,demanda
    std::vector< std::pair< std::pair<int,int>,std::pair<int,int> > > points;
    std::vector< std::vector<double> > distances;


    void initPop();
    void calcFitness();
    void crossover(int index1,int index2);
    void mutation(int index);

    int selectParent(int size);

    int randomInt();
    double randomReal();

};


#endif // GA_HPP
