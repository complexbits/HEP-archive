#include "lm_access/LmRunQuality.hpp"
using namespace lm_access;
using namespace std;
int main(){
  LmRunQuality runquality;
  ofstream badfile("badruns");
  ofstream goodfile("goodruns");
  ofstream goodfile2("goodruns2");
  ofstream badfile2("badruns2");
  ofstream log("testlog");
  for(int i = 0; i < 10; i++){
    goodfile << i << endl;
    goodfile2 << i+5 << endl;
  }
  
  for(int i = 0; i < 10; i+=3){
    badfile << i << endl;
    badfile2 << i+2 << endl;
  }
  goodfile.close();
  badfile.close();
  runquality.loadGoodRuns("goodruns");
  runquality.loadBadRuns("badruns");
  runquality.loadBadRuns("non-existent");
  runquality.loadBadRuns("badruns2");
  runquality.loadGoodRuns("goodruns2");
  runquality.addBadRun(3);
  runquality.removeGoodRun(1);
  for(int i = 0; i < 15; i++){
    log << i << " good: " << runquality.isGoodRun(i) << " bad: " << runquality.isBadRun(i) << endl;
  }
  return 0;
}
