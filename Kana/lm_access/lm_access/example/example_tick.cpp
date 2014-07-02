#include "lm_access/LumPerTick.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    
  LumPerTick lTick;

  if (argc < 3||argc>4) {
     cout << "Usage: example_tick first_lbn last_lbn [tick_number]" << std::endl;
     cout << "       default tick_number = 7" << std::endl;
     return 1;
  }
  int lbn_i = atoi(argv[1]);
  int lbn_f = atoi(argv[2]);
  int tick = 7;
  if (argc == 4) tick = atoi(argv[3]);

  for(int lbn = lbn_i; lbn <= lbn_f; lbn++) {
    if (lTick.isGoodTick(lbn, tick)) cout << "LBN " << lbn 
					  << ", tick " << tick << " : "
					  << lTick.luminosity(lbn, tick) << ", "
					  << lTick.protonHalo(lbn, tick) << ", "
					  << lTick.pbarHalo(lbn, tick) << ", "
					  << lTick.avgNumInelastic(lbn, tick)
					  << endl;
  }

  return 0;
}
