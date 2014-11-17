#include "GA.hpp"

#include <iostream>
#include <math.h>
#include <chrono>
#include <random>
#include <set>

int GA::randomInt(){
  static std::default_random_engine generator (this->seed);
  static std::uniform_int_distribution<int> distribution(0, this->numPoints-1);

  return distribution(generator);
}

double GA::randomReal(){
  static std::default_random_engine generator (seed);
  static std::uniform_real_distribution<double> distribution(0.0,1.0);
  return distribution(generator);
}


void GA::calcDistances(){
  int count = 0;
  for(int i=0; i<numPoints-1; i++){
    std::vector< double > ds;
    for(int j=i+1; j<numPoints; j++){
      int x1 = this->points[i].first.first;
      int y1 = this->points[i].first.second;
      
      int x2 = this->points[j].first.first;
      int y2 = this->points[j].first.second;

      double d = sqrt( pow(x1-x2,2) + pow(y1-y2,2) );

      ds.push_back(d);
      count++;
    }
    distances.push_back(ds);
  }

  std::cout << count << "\n";
}

void GA::initPop(){

  for(int i=0; i<this->populationSize; i++){
    std::set<int> values;

    for(int j=0; j<this->medians; j++){
      int r = randomInt();

      while( values.find(r) != values.end() ){
        r = randomInt();
      }

      this->pop[i][j] = r;
      values.insert(r);
    }
  }

}

void GA::crossover(int index1, int index2){

  for(int i =0; i< this->medians; i++){
    double r = randomReal();
    if( r < crossoverProb){
      int aux = this->pop[index1][i];
      this->pop[index1][i] = this->pop[index2][i];
      this->pop[index2][i] = aux;
    }
  }

}

void GA::mutation(int index){
  std::set<int> values;
  
  for(int i =0; i< this->medians; i++){
    values.insert(this->pop[index][i]);
  }


  for(int i =0; i< this->medians; i++){
    double t = randomReal();
    if( t < crossoverProb){
      int r = randomInt();
      
      while( values.find(r) != values.end() ){
        r = randomInt();
      }
      this->pop[index][i] = r;
      values.insert(r);
    }
  }  

}

int GA::selectParent(int size){
  int minFitness = INT_MAX;
  int bestIndex = -1;

  for(int i=0; i<size; i++){
    int index = randomInt();

    if( this->fitness[index] < minFitness ){
      minFitness = this->fitness[index];
      bestIndex = index;
    }

  }


  return bestIndex;
}


