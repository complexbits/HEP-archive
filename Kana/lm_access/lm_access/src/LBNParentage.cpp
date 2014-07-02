#include "lm_access/LBNParentage.hpp"

namespace lm_access{

  LBNParentage::LBNParentage(){};

  void LBNParentage::load(const int lbn, const int run, const std::string& stream, const std::string & version, const std::string parent_version){
    _LBN = lbn;
    _info.push_back(LBNParentagePrimitive(lbn,run,stream,version,parent_version));
  }

  void LBNParentage::print(std::ostream& o)const{
    std::vector<LBNParentagePrimitive>::const_iterator is;
    for (is = _info.begin(); is != _info.end(); is++){
      is->print(o);
    }
  }

  std::vector<LBNParentagePrimitive> LBNParentage::getLBNParentageVector()const{
    return _info;
  }

  int LBNParentage::getRun(const int i=0)const{
    return _info[i].getRun();
  }

  std::string LBNParentage::getStream(const int i=0)const{
    return _info[i].getStream();
  }

  std::string LBNParentage::getVersion(const int i=0)const{
    return _info[i].getVersion();
  }  
  std::string LBNParentage::getParentVersion(const int i=0)const{
    return _info[i].getParentVersion();
  }  


}
