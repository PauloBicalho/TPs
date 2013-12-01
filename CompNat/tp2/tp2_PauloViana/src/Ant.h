#ifndef ANT_H
#define ANT_H

#include <vector>
#include <pair>

class Ant{
  private:
    std::vector< std::pair<int,int> > path;

    std::vector< Machine > machines;

    std::vector< Job > jobs;

  public:
    Ant( const Constraints & cons )

}




#endif // ANT_H
