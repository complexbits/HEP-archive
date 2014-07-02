/*
 * File:      example_parentage.cpp
 * Package:   lm_access
 * Purpose:   simple example of calculation of luminosity and cross section 
 *            for EM_MX_SH trigger in derived files
 *            for an explanation see ../doc/example_xsec.html
 * Created:   30-Jul-2003 - Petr Homola
 * Modified:  16-Nov-2003 - Petr Homola
 */

#include "lm_access/LumFileMap.hpp"
#include "lm_access_interface/LmAccessInterface.hpp"

using namespace std;
using namespace lm_access;

#include <stdio.h>
#include <stdlib.h>

using std::atoi;

int main(int argc, char* argv[]) {
  bool debug = false;

  if (argc < 2 || argc > 3){
    cerr << " must enter LBN number and optionally trigger - the default trigger is EM_HI_SH " << endl;
    return 1;
  }
  const int  lbn = atoi(argv[1]);
  
  lm_access::TriggerMap triggers;
  char* trigger = "EM_HI_SH";
  if(argc == 3){
    const char* mytrigger = argv[2];
    triggers[mytrigger] = 1;
    trigger = argv[2];
  }
  else{
    triggers["EM_HI_SH"] = 1;
  }
  LmAccessInterface::InterfaceType="stage3";
  LumBlkMap lbn_map;
  
  
  lbn_map.read(lbn,lbn, triggers);
  cout << " dump of lbn " << lbn << " for trigger " << trigger << endl;
  //lbn_map[lbn].setdebug(debug);
  lbn_map[lbn].print(cout);

}
