#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>

class Schedule{
  private:
    std::vector< int > machines;
    std::vector< int > jobNextOperationMinStart;
    std::vector<std::pair<int,int> > path;
    
    int makespan;

  public:
    Schedule(int numMachines, int numJobs);

    void allocate(int job, int machine, int operation, int duration);
    
    inline int getMachineCurrentTime( int machine ) const;

    inline int getMakespan() const
     { return this->makespan; };

    int lazyTimeIfAllocate( int job, int machine ) const;

    inline std::vector< std::pair<int,int> > getPath() const
      { return this->path; };
};

#endif
