#include "lm_access/BadLBNList.hpp"
using namespace lm_access;
using namespace std;
int main(){
  BadLBNList lbnquality;
  ofstream badlbnfile("badlbns");
  ofstream badlbnfile2("badlbns2");
  ofstream log("lbntestlog");
  
  for(int i = 0; i < 10; i+=3){
    badlbnfile << i << endl;
    badlbnfile2 << i+2 << endl;
  }
  badlbnfile.close();
  badlbnfile2.close();
  lbnquality.loadBadLBNs("badlbns");
  lbnquality.loadBadLBNs("non-existent");
  lbnquality.loadBadLBNs("badlbns2");
  lbnquality.addBadLBN(3);
 for(int i = 0; i < 15; i++){
    log << i  << " bad: " << lbnquality.isBadLBN(i) << endl;
  }
  return 0;
}










