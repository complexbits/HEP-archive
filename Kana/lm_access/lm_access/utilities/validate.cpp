/*
 * File:      validate.cpp
 * Package:   lm_access
 */

#include "lm_access/LumFileMap.hpp"


using namespace std;
using namespace lm_access;

#include <stdio.h>
#include <stdlib.h>

using std::atoi;

int main(int argc, char* argv[]) {
  bool debug = false;

  if (argc < 3 || argc > 4){
    cerr << " must enter LBN number , number of lbns to process,  and optionally trigger - the default trigger is zero_bias_NCU " << endl;
    return 1;
  }
  const int  lbn = atoi(argv[1]);
  const int  nlbn = atoi(argv[2]);
  
  lm_access::TriggerMap triggers;
  char* trigger = "zero_bias_NCU";
  if(argc == 4){
    const char* mytrigger = argv[3];
    triggers[mytrigger] = 1;
    trigger = argv[3];
  }
  else{
    triggers["zero_bias_NCU"] = 1;
  }
  LmAccessInterface::InterfaceType="LmDb";
  LumBlkMap lbn_map;
  
  lbn_map.read(lbn,lbn+nlbn, triggers);
  //lbn_map[lbn].setdebug(debug);
  for (int i = lbn;i<=lbn+nlbn;i++) {
    //     cout << " dump of lbn " << i << " for trigger " << trigger << endl;
     lbn_map[i].print(cout);
     //   cout << std::endl;
  }
  // delete interface;
}
