#include "lm_access/GetLumInfo.hpp"

#include <iostream>

#include <string>
using namespace std;

int main() {
    
  GetLumInfo lTrigger;

  std::string trigger = "min_bias";
  std::string trigger2 = "EM_HI_SH";
  for(int lbn = 1800000; lbn < 1809999; lbn++) {
    if (lTrigger.isGoodTrigger(lbn, trigger)) cout << "LBN " << lbn 
					  << ", trigger " << trigger << " : "
						   << lTrigger.prescale(lbn, trigger) ;
    if (lTrigger.isGoodTrigger(lbn, trigger2)) cout  
					  << ", trigger " << trigger2 << " : "
					  << lTrigger.prescale(lbn, trigger2) 
					  << endl;
  }

  return 0;
}
