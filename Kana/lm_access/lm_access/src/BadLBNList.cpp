#include "lm_access/BadLBNList.hpp"
#include <iostream>

namespace lm_access{

  //  using namespace std;

BadLBNList::BadLBNList(){
  _somebad=0;
}







bool BadLBNList::loadBadLBNs(std::string filename){
  filename=filename_expand(filename);
  int count = 0;
  ifstream badfilestream(filename.c_str());
  if(!badfilestream){
    cerr << "No bad lbns specified by " << filename << " , don't add any bad lbns to existing list" << endl;
    if(_somebad != 1) _somebad = 0;
    return 0;
  }
  int run;
  while(badfilestream >> run){
    badlbns.insert(run);
    count++;
  }
  badfilestream.close();
  _somebad=1;
  cout << count << " bad lbns loaded from " << filename << endl;
  return 1;
}    

 

bool BadLBNList::isBadLBN(int lbn)const {
  return (_somebad && badlbns.count(lbn));
}


void BadLBNList::addBadLBN(int lbn){
  badlbns.insert(lbn);
}
    

void BadLBNList::removeBadLBN(int lbn){
  badlbns.erase(lbn);
}
}
