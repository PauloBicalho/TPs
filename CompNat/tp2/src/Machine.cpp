#include "Machine.h"



Machine::Machine(){
//  this->freeTimes.push_back( std::pair<int,int> (0,INT_MAX) );
  this->currentTime = 0;
}

/*int Machine::allocate(int job, int minStartTime, int duration){
  
  std::vector< std::pair<int,int> >::iterator it = this->freeTimes.begin()
  for( ; it != this->freeTimes.end(); ++it){
    if( it->first <= minStartTime && (minStartTime+duration) < it->second ){
        //fragmenta o espaco
      this->busyTimes.push_back( std::pair<int, std::pair<int,int> > (job, std::<pair<int,int> (minStartTime,minStartTime+duration)) );
    } else if( it->first > minStartTime && (it->first+duration) < it->second ){
      //fragmenta o espaco
      this->busyTimes.push_back( std::pair<int, std::pair<int,int> > (job, std::<pair<int,int> (it->first,it->first+duration)) );
    } else {
      std::cout<< "ERROR: Machine";  
      exit(1);
    }
  
  }

}*/

int Machine::allocate(int job, int minStartTime, int duration){
  int startTime = this->currentTime;

  if( startTime < minStartTime )
    startTime = minStartTime;

  this->currentTime = startTime + duration;

}
