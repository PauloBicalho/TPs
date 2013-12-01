#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <vector>
#include <string>

using namespace std;

class Constraints{
  private:
    int numJobs, numMachines;
    vector< vector< pair<int,int> > > jobs;
    //vector< vector< pair<int,int>* >* > jobs;


  public:
//    Constraints();
    Constraints( const char* fileName );
//virtual ~Constraints();

    inline int getNumJobs() const { return this->numJobs; }
    inline int getNumMachines() const { return this->numMachines; }

    inline int getIdMachine( int job, int operation ) const 
      { return this->jobs[job][operation].first; }

    inline int getDuration( int job, int operation ) const 
      { return this->jobs[job][operation].second; }

    void show() const;
};


#endif
