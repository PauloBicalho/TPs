#include "ACO.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>

#define A 1
#define B 2


ACO::ACO(const Constraints &_cons, int numAnts, int maxIteration, double maxPh,
  double minPh, double evaporateRate, double alpha, double beta, int seed) : 
  cons(_cons),
  bestSchedule(_cons.getNumMachines(), _cons.getNumJobs()){

  this->numAnts = numAnts;
  this->numJobs = cons.getNumJobs();
  this->numMachines = cons.getNumMachines();
  this->maxIteration = maxIteration;
  this->numOperations = cons.getNumMachines();
  this->maxPh = maxPh;
  this->minPh = minPh;
  this->evaporateRate = evaporateRate;
  this->alpha = alpha;
  this->beta = beta;

  this->counterOperation = std::vector<int> (this->numJobs, this->numOperations);
  this->totalOperations = this->numJobs * this->numOperations;

  this->grafo = std::vector< std::vector<double> > (this->totalOperations+1,
      std::vector<double> (this->totalOperations+1,50) );

  //std::cout << "\n---" <<  this->grafo[1][1] << "\n" <<  endl;
  srand(seed);
}

double ACO::getPh(int job1, int op1, int job2, int op2) const{
  int pos1 = (job1 * this->numOperations) + op1 + 1;
  int pos2 = (job2 * this->numOperations) + op2 + 1;

  return 1.0 / this->grafo[pos1][pos2];
//  return this->grafo[pos1][pos2];
}

void ACO::increasePh(int job1, int op1, int job2, int op2, double delta){
  int pos1 = (job1 * this->numOperations) + op1 +1;
  int pos2 = (job2 * this->numOperations) + op2 +1;

  this->grafo[pos1][pos2] += delta;
  //this->grafo[pos2][pos1] += delta;

  if( this->grafo[pos1][pos2] > this->maxPh )
    this->grafo[pos1][pos2] = this->maxPh;
  //if( this->grafo[pos2][pos1] > this->maxPh )
  //  this->grafo[pos2][pos1] = this->maxPh;
}

void ACO::decreasePh(int job1, int op1, int job2, int op2, double delta){
  int pos1 = (job1 * this->numOperations) + op1 + 1;
  int pos2 = (job2 * this->numOperations) + op2 + 1;

  this->grafo[pos1][pos2] *= delta;
  this->grafo[pos2][pos1] *= delta;
  
  if( this->grafo[pos1][pos2] < this->minPh )
    this->grafo[pos1][pos2] += this->minPh;
  if( this->grafo[pos2][pos1] < this->minPh )
    this->grafo[pos2][pos1] += this->minPh;
}


int ACO::getJobNextOperation(int job) const {

  int remainingOperations = this->counterOperation[job];
  
  if(remainingOperations == 0)
    return -1;
  
  int nextJobOperation = this->numOperations - remainingOperations;
  return nextJobOperation;
}

//criar vetor de ph e duration e normalizar
std::vector<double> ACO::calcProbabilities(int currentJob,
    int currentJobOperation, Schedule currentSchedule) const{

  std::vector<double> probs = std::vector<double>(this->numJobs,0.0);
  std::vector<double> aux = std::vector<double>(this->numJobs,0.0);
  double sumProbs = 0.0;
  for(int nextJob=0; nextJob < this->numJobs; nextJob++){
    int nextJobOperation = this->getJobNextOperation(nextJob);

    if(nextJobOperation == -1)
      continue;

    double ph = this->getPh(currentJob, currentJobOperation, nextJob, nextJobOperation);
//    double dsb = this->getDsb(nextJob, nextJobOperation, currentSchedule);

    int nextOperationMach = this->cons.getIdMachine(nextJob, nextJobOperation);
    double lazyTime =  (double) currentSchedule.lazyTimeIfAllocate(nextJob, nextOperationMach);
    lazyTime += 1;
    double dsb = 1.0 / lazyTime;

//    std::cout << "{" << ph << "-" << lazyTime  << "-" << dsb << "} ";

    double prob = pow(ph,this->alpha) * pow(dsb,this->beta);

    aux[nextJob] = prob;
    sumProbs += prob;
  }
//  std::cout << "\n";

  double acum = 0.0;
  for(int i=0; i<this->numJobs; i++){
//    std::cout << "[" << aux[i] << "-";
    double temp = aux[i] / sumProbs;
//    std::cout << temp << "] ";  
    probs[i] = (acum + temp);
    acum += temp;
  }
//  std::cout << "\n\n";
  
  return probs;
}


int ACO::getWinnerJob(const std::vector<double> probs) const{
  double r = rand() / double(RAND_MAX);

  for(int i=0; i<this->numJobs; i++){
    if( r <= probs[i] ){
      return i;
    }
  }
  return -1;
}

/*int ACO::evaluatePath( const std::vector< std::pair<int,int> > path ) const{
  int makespan = 0;

  std::vector<int> machineTime (this->numMachines, 0 );
  std::vector<int> jobsLastOperationFinishTime (this->numJobs,0);

  for( std::vector< std::pair<int,int> >::const_iterator it = path.begin(); it != path.end(); ++it ){
    int job = it->first;
    int operation = it->second;

  //  std::cout << job << "-" << operation << endl;
    int machine = this->cons.getIdMachine(job,operation);
    int duration = this->cons.getDuration(job,operation);
    
    int jobLastOperationFinishTime = jobsLastOperationFinishTime[job];
    int machineCurrentTime = machineTime[machine];

    int startTime = machineCurrentTime;
    if( jobLastOperationFinishTime > machineCurrentTime )
      startTime = jobLastOperationFinishTime;

    int endTime = startTime + duration;

    machineTime[machine] = endTime;
    jobsLastOperationFinishTime[job] = endTime;

    if( endTime > makespan )
      makespan = endTime;
  }

  return makespan;
}*/

void ACO::updatePh( const std::vector< std::pair<int,int> > path, int makespan ) {

  //double invMakespan = 1.0/ (double) makespan;

  int currentJob = 0, currentJobOperation = -1;

  std::vector< std::pair<int,int> >::const_iterator it;
  for( it = path.begin(); it != path.end(); ++it ){
    int nextJob = it->first;
    int nextJobOperation = it->second;

    double delta = .1 * (double) makespan;
//    std::cout << "mk" << makespan <<  " inv " << delta << endl;
    //double delta = this->alpha * invMakespan;

    this->increasePh(currentJob, currentJobOperation, nextJob, nextJobOperation, delta);
    currentJob = nextJob;
    currentJobOperation = nextJobOperation;
  }
}

void ACO::evaporatePh(){
  for(int i=0; i<this->totalOperations + 1; i++){
    for(int j=0; j<this->totalOperations+1; j++){
      double ph = this->grafo[i][j];
      double delta = this->evaporateRate * ph;

      double total = ph - delta;

      if( total < this->minPh )
        total = this->minPh;

      this->grafo[i][j] = total;
    }
  }
}

void ACO::nextIteration(int k){
 
  double meanMakespan = .0;

  std::vector< std::pair<int,Schedule> > paths; 
  int bestMakespan = 999999999, bestAnt = -1;
  int worstMakespan = 0.0, worstAnt = -1;
  for(int ant=0; ant< this->numAnts; ant++ ){
//    std::cout << "+++ ANT " << ant << " ++++\n";

    //Resentando valores a cada iteracao
    for(int i=0; i<this->numJobs; i++)
      this->counterOperation[i] = this->numOperations;

    //defininido conifiguracao inicial (nada alocado);
    int currentJob=0, currentJobOperation=-1;

    Schedule currentSchedule (this->numMachines, this->numJobs);
    for(int i=0; i<this->totalOperations; i++){
//      std::cout << "\n";

      std::vector<double> probs = this->calcProbabilities(currentJob,
          currentJobOperation, currentSchedule);
      int nextJob = this->getWinnerJob(probs);
      int nextJobOperation = this->getJobNextOperation(nextJob);
      
      int machine = this->cons.getIdMachine(nextJob, nextJobOperation);
      int duration = this->cons.getDuration(nextJob, nextJobOperation);

      //aloca a operacao do job 
      currentSchedule.allocate(nextJob, machine, nextJobOperation, duration);
      this->counterOperation[nextJob] --;

      currentJob = nextJob;
      currentJobOperation = nextJobOperation;
    }

    int makespan = currentSchedule.getMakespan();
    paths.push_back( std::make_pair (makespan, currentSchedule) );

    meanMakespan += makespan;
  
    if( worstAnt == -1 || worstMakespan < makespan ){
      worstAnt = ant;
      worstMakespan = makespan;
    }
    
    if( bestAnt == -1 || bestMakespan > makespan ){
      bestAnt = ant;
      bestMakespan = makespan;

      if( bestSchedule.getMakespan() == 0 || bestMakespan < bestSchedule.getMakespan() )
        bestSchedule = currentSchedule ;
    }
  }

// std::cout << "BestMakespan: " << bestMakespan << endl;

//  if(k+1%100000 == 0){
//  std::cout << "\n-------------------Grafo Antes ---------------------------\n";
//  this->showGrafo();
//  std::cout << "------------------------------------------------------------\n";
//  }

  for(unsigned int i=0; i<paths.size(); i++)
    this->updatePh(paths[i].second.getPath(), paths[i].first);
//    this->updatePh(paths[bestAnt].second.getPath(), bestMakespan);
  
  this->updatePh(bestSchedule.getPath(),bestSchedule.getMakespan());
  
//  if(k+1%100000 == 0){
//  std::cout << "\n-------------------Grafo Depois ---------------------------\n";
//  this->showGrafo();
//  std::cout << "------------------------------------------------------------\n";
//  }

  meanMakespan /= (double) this->numAnts;
  std::cout << "Iteration: " << k << "\t" << this->getBestMakespan() <<  "\t" << bestMakespan << "\t" << meanMakespan << "\t" << worstMakespan << endl;

//  if( k % 10 == 0 ){
//    mean /= (this->numAnts * 100.);
    
//    std::cout << "BestMakespan " << k << ": " << paths[bestAnt].second.getMakespan() 
//       << "-" << this->getBestMakespan() << " || " << mean << endl;
//    mean = 0.0;
//    std::cout << "###################################\n";
//    this->showGrafo();
//    std::cout << "###################################\n";
//  }


//  for(unsigned i=0; i<paths[bestAnt].second.getPath().size(); i++)
//    std::cout << "" << paths[bestAnt].second.getPath()[i].first << "-"
//      << paths[bestAnt].second.getPath()[i].second << "]";
//  std::cout << endl;


//  this->updatePh(paths[bestAnt].second.getPath(), bestMakespan);
  this->evaporatePh();
}

void ACO::showGrafo(){
  for(int i=0; i<this->totalOperations+1; i++){
    for(int j=0; j<this->totalOperations+1; j++){
      std::cout << this->grafo[i][j] << " ";

    }
    std::cout << endl;
  }
}

int ACO::getBestMakespan(){
  return this->bestSchedule.getMakespan();
}

void ACO::execute(){
  for(int i=0; i<this->maxIteration; i++){
//      std::cout << "\n-----------------Iteration: " << i << endl;
    this->nextIteration(i);

//    if( i % 100 == 0 )
//      std::cout << "BestMakespan - " << i << ": " << this->getBestMakespan() << endl;
  }

}
