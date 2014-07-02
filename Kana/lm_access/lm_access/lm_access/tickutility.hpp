#ifndef tickutility_h
#define tickutility_h
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using std::atoi;

// make this guy a singleton as we only need one.

class tickutility{

public:

  static tickutility* Instance();


  // initialize with constants, only do nonlinearity correction if fixNL is true
  void Init(const bool fixNL=0);

  // convert from tick string to index

  int tickindex(const std::string& tick)const;

  // convert from tick number to index

  int tickindex( const int tick)const;

  // convert from index to tick number int
  
  int ticklist(const int index)const;

  float beta(const int tick)const;

  float offset(const int tick)const;

protected:

  tickutility();

  
private:
    
  int _list[37];
  int _inverse[160];
  float _beta[12];
  float _offset[12];
};
#endif
