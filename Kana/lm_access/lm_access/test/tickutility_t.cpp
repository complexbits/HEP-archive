#include "lm_access/tickutility.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(){
  tickutility * t = tickutility::Instance();
  cout << " integer->index " << t->tickindex(7) << endl;
  cout << " string->index " << t->tickindex(string("146")) << endl;
  cout << " index->integer " << t->ticklist(36) << endl;
  return 0;
}
