#include "lm_access/LBNParentagePrimitive.hpp"

namespace lm_access{

  LBNParentagePrimitive::LBNParentagePrimitive(){}

  void LBNParentagePrimitive::load(const int lbn, const int run, const std::string stream,const std::string version, const std::string  parent_version){
    _lbn=lbn;
    _run = run;
    _stream = stream;
    _version = version;
    _parent_version = parent_version;
  }

  LBNParentagePrimitive::LBNParentagePrimitive(const int lbn, const int run, const std::string stream,const std::string version, const std::string  parent_version){
    load(lbn,run,stream,version,parent_version);
  }

  void LBNParentagePrimitive::print(std::ostream& o) const{
    o << _lbn << " " <<  _run << " " <<  _stream <<  " " << _version <<  " " << _parent_version <<std::endl;
  }

}
