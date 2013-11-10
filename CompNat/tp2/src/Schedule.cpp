#include "Schedule.h"

Schedule::Schedule( int numMachines, int numJobs ){
  this->machines = std::vector< int > (numMachines, 0);
  this->jobNextOperationMinStart = std::vector< int > (numJobs, 0);
  this->path = std::vector< std::pair< int, int > > ();
  this->makespan = 0;
}

void Schedule::allocate(int job, int machine, int operation, int duration){
  
  this->path.push_back( std::make_pair(job,operation) );

  int startTime = this->machines[machine];
  int minStartTime = this->jobNextOperationMinStart[job];

  if( startTime < minStartTime )
    startTime = minStartTime;

  int machineCurrentTime = startTime + duration;
  this->machines[machine] = machineCurrentTime;
  this->jobNextOperationMinStart[job] = machineCurrentTime;
  
  if( machineCurrentTime > this->makespan )
    this->makespan = machineCurrentTime;
}

int Schedule::getMachineCurrentTime( int machine ) const{
  return this->machines[machine];
}


int Schedule::lazyTimeIfAllocate( int job, int machine) const{
  int delta = this->jobNextOperationMinStart[job]-this->machines[machine];
  return delta >0 ? delta : 0;
}
