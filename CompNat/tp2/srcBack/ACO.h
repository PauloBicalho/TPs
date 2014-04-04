#ifndef ACO_H
#define ACO_H

#include "Constraints.h"
#include "vector"
#include "Schedule.h"

class ACO{

  private:
    int numAnts, numJobs, numMachines, maxIteration;
    int numOperations,totalOperations;

    double maxPh, minPh;
    double evaporateRate, alpha, beta;

    const Constraints &cons;


    // cada linha da matriz apresenta um caminho (solucao do JSS) valida 
    std::vector< std::vector<int> > paths;
    
    
    //contador de operacoes ainda nao alocadas de cada job
    // counterOperation[0] = 4  --> o job 0 possui 4 operacoes nao alocadas
    std::vector<int> counterOperation;

    std::vector< std::vector<double> > grafo;

    Schedule bestSchedule;

    inline double getPh(int job1, int op1, int job2, int op2) const;
    inline void increasePh(int job1, int op1, int job2, int op2, double delta);
    inline void decreasePh(int job1, int op1, int job2, int op2, double delta);

    int getJobNextOperation(int job) const;

    std::vector<double> calcProbabilities(int currentJob, int currentJobOperation,
        Schedule currentSchedule) const;
    
    int getWinnerJob(const std::vector<double> probs) const;
    int evaluatePath(std::vector< std::pair<int,int> > path) const;

    void updatePh( const std::vector< std::pair<int,int> > path, int makespan );
    void evaporatePh();

    void nextIteration(int k);
    
    void showGrafo();

  public:
//    ACO(const Constraints & _cons, int numAnts, int maxIteration, int seed );
    ACO(const Constraints &_cons, int numAnts, int maxIteration, double maxPh, 
        double minPh, double evaporateRate, double alpha, double beta, int seed);

    void execute();
    int getBestMakespan();

    //Solution getBestSolution();

};


#endif // ACO_H
