#include "lm_access/LmFileParentage.hpp"
#include <fstream>


namespace lm_access{

  LmFileParentage::LmFileParentage(){};
  LmFileParentage::LmFileParentage(const std::string& filename,const std::string& tag){
    load(filename,tag);};
  bool LmFileParentage::load(const std::string& filename,const std::string& tag){
    _filename=filename;
    std::string parentage=filename+"."+tag;
    std::ifstream in(parentage.c_str());
    if(!in) {
      cerr << " no parentage file " << parentage << std::endl;
      cerr << " remove this file or make parentage to continue " << std::endl;
      exit(0);
    }      

    int lbn = 0;
    int lbnmax = 0;
    int lbnmin = 99999999;
    int ic = 0;
    int runlbn;
    std::string stream;
    std::string version;
    std::string parent_version;
    std::string rawfile;
    std::string datatier;
    int nevent;
    int lbnlo;
    int lbnhi;

    // in each file read in the lbns , run, stream and version info

    while (in >> lbnlo && in >> lbnhi ){
       if (tag=="lumiDB") {
         in >> rawfile >> stream >> runlbn >> parent_version >> version >> datatier >> nevent;
       } else {
         in >> runlbn >> stream >> parent_version >> version;
       }
       for (int i = lbnlo; i <= lbnhi; i++){
	  std::map<int,LBNParentage>::const_iterator it;
	  if(_parentage.find(i) == end()){
	    _parentage[i]=LBNParentage();
	  }
	  _parentage[i].load(i,runlbn,stream,version,parent_version);
        }
    }
    in.close();
    return 1;
  }

  void LmFileParentage::print(std::ostream &o)const{
    o << _filename << std::endl;
    std::map<int,LBNParentage>::const_iterator it;
    for(it = _parentage.begin(); it != _parentage.end(); it++){
      it->second.print(o);
    }
  }
}
