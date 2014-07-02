#include <iostream>

#include <string>
#include <unistd.h>
#include "lm_access/gzstream.hpp"
#include "lm_access/globaldef.hpp"

using std::cerr;
using std::endl;
using std::cout;
using std::string;

int main(int argc, char* argv[]) {
  bool debug = true;
  char curr[1000];
  if (argc < 2 || argc > 2){
    cerr << " must enter LBN number " << endl;
    return 1;
  }
  const int  lbn = atoi(argv[1]);
  
  bool _lbnFileExists;

  const int str_buffer_length = 20;
  char s_number[str_buffer_length];
  sprintf(s_number, "/%i/%i", lbn/10000, lbn);
  const string fname = lm_access::lbn_dir + string(s_number);
  if (access(fname.c_str(), R_OK) == 0) {
    _lbnFileExists = true;
    gz::igzstream s;
    s.open(fname.c_str());
    bool seek=true;
    bool problem = false;
    while (seek) {
      s.getline(curr,1000);
      if ( s.fail() || (! s) ) {
	seek = false;
	problem = true;
      }// else if (curr == B0CABEEF) seek = false;
      cout << curr;
      cout << endl;
    }
    
    s.close();
  }
}
