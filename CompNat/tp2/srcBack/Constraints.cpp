#include "Constraints.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Constraints::Constraints( const char* fileName ){
  FILE * file;

  file = fopen(fileName, "r");

  fscanf(file, "%d %d", &(this->numJobs), &(this->numMachines));

  for(int i=0; i<this->numJobs; i++){
    this->jobs.push_back( vector< pair<int,int> > () );

    for(int j=0; j<this->numMachines; j++){
      this->jobs[i].push_back( pair<int,int> (0,0) );
      fscanf(file, "%d %d", &(this->jobs[i][j].first), &(this->jobs[i][j].second) );
    }
  }

  fclose(file);

}

void Constraints::show() const{
  cout << this->numJobs << " " << this->numMachines << "\n";

  for(int i=0; i<this->numJobs; i++){
    for(int j=0; j<this->numMachines; j++){
      printf("%d %d ", (this->jobs[i][j].first), (this->jobs[i][j].second) );
    }
    printf("\n");
  }



}

