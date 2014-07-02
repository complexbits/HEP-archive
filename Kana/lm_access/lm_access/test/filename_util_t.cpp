#include "lm_access/filename_util.hpp"

int main(){
  std::string path = lm_access::filename_expand(std::string("$SRT_PRIVATE_CONTEXT/test"));
  std::string name = lm_access::filename_only(std::string("$SRT_PRIVATE_CONTEXT/test"));
}
