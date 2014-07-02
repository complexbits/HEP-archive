#include "lm_access/LumPerTick.hpp"

#include <iostream>

using namespace std;


int ticks[36]= {7,10,13,16,19,22,25,28,31,34,37,40,60,63,66,69,72,75,78,81,84,90,93,113,116,119,122,125,128,131,134,137,140,143,146};

int main() {
    
  LumPerTick lTick;

  cout << "LBN, ";
  for(int index = 0; index < 36; index++){
    cout << ticks[index] << ",";
  }
  cout << endl;
  
  for(int lbn = 3038040; lbn <= 3039040; lbn++) {
    cout << lbn << ",";
    for(int index  = 0; index < 36; index++){
      int tick = ticks[index];

      if (lTick.isGoodTick(lbn, tick)) cout 
	<< lTick.luminosity(lbn, tick) << ", ";
    }
    cout <<endl;
  }
  return 0;
}
