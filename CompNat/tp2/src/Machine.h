#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include <pair>

class Machine{

  private:
    std::vector< std::pair<int,int> > freeTimes;

    std::vector< std::pair<int, std::pair<int,int> > busyTimes;

    int currentTime;

    std::pair<int,int> getFit( int minStartTime, int duration ) const;

  public:
    Machine();

    int allocate(int job, int minStartTime, int duration);
    inline int getCurrentTime() const { return this->currentTime };
    int deltaTimeIfAllocate(int job, int minStartTime, int duration) const;


};


#endif
