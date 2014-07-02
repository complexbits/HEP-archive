#include <lm_access/LumFile.hpp>

//---------------------------------------------------------------

LumFile::LumFile() : LumFileRelease(), _lbn() {};

//---------------------------------------------------------------

LumFile::LumFile(const lm_access::FileType& ftype, const std::string& release,
		 const std::string& parent_release) : 
  LumFileRelease(ftype, release, parent_release), _lbn() {};

//---------------------------------------------------------------

LumFile::LumFile(const LumFile& rhs) : 
  LumFileRelease(rhs), _lbn(rhs._lbn) {}

//---------------------------------------------------------------

LumFile& LumFile::operator=(const LumFile& rhs) {
  if (this != &rhs) {
    ((LumFileRelease*) this)->operator=(rhs);
    _lbn = rhs._lbn;
  }
  return *this;
}

//---------------------------------------------------------------

lm_access::LumBlkStatus LumFile::status(const int& lbn, 
					const lm_access::TriggerID triggerID,
					const lm_access::LmType& type) const {
  return (isGoodLBN(lbn, triggerID, type)) ? 
    lm_access::OK : lm_access::BAD;
}

//---------------------------------------------------------------

int LumFile::isGoodLBN(const int& lbn, const lm_access::TriggerID triggerID, 
		       const lm_access::LmType& type) const {
  
  LumBlkMap::const_iterator it_lbn = _lbn.find(lbn);
  if(_debug){
    std::cout << "LumFile::isGoodLBN start " << lbn << " " << triggerID << std::endl;
  }
  if (it_lbn == _lbn.end()){
    if(_debug){
      std::cout << "LumFile::isGoodLBN could not find lbn " <<  lbn << std::endl;
    }
    return 0;
  }
  const LumBlkInfo& lm_info = it_lbn->second;
  if (_debug) lm_info.print();
  int result =  lm_info.status(triggerID,type,*this);
  if(_debug){
    std::cout << "LumFile::isGoodLBN result " << lbn << " " << result << std::endl;
  }
  return result;
}

std::list<int> LumFile::getLBNList()const{
  std::list<int> lbnlist;
  LumBlkMap::const_iterator it_lbn;
  for(it_lbn = _lbn.begin(); it_lbn != _lbn.end(); it_lbn++){
    lbnlist.push_back(it_lbn->first);
  }
  return lbnlist;
}

//---------------------------------------------------------------

double LumFile::luminosity(const lm_access::TriggerID triggerID, 
			   const lm_access::LmType& type, const int tick) const {
  double res = 0;
  LumBlkMap::const_iterator it_lbn;
  
  for(it_lbn = _lbn.begin(); it_lbn != _lbn.end(); it_lbn++) {
    const LumBlkInfo& lm_info = it_lbn->second;
    if (this->isGoodLBN(it_lbn->first, triggerID, type)) {
      res += lm_info.luminosity(triggerID, type,tick);
    }
  }

  return res;
}

//---------------------------------------------------------------

long LumFile::acceptsL1(const lm_access::TriggerID triggerID, const lm_access::LmType& type) const {
  long res = 0;
  LumBlkMap::const_iterator it_lbn;
  
  for(it_lbn = _lbn.begin(); it_lbn != _lbn.end(); it_lbn++) {
    const LumBlkInfo& lm_info = it_lbn->second;
    if (this->isGoodLBN(it_lbn->first, triggerID, type)) {
      res += lm_info.acceptsL1(triggerID);
    }
  }

  return res;
}

//---------------------------------------------------------------

long LumFile::acceptsL2(const lm_access::TriggerID triggerID, const lm_access::LmType& type) const {
  long res = 0;
  LumBlkMap::const_iterator it_lbn;
  
  for(it_lbn = _lbn.begin(); it_lbn != _lbn.end(); it_lbn++) {
    const LumBlkInfo& lm_info = it_lbn->second;
    if (this->isGoodLBN(it_lbn->first, triggerID, type)) {
      res += lm_info.acceptsL2(triggerID);
    }
  }

  return res;
}

//---------------------------------------------------------------

long LumFile::acceptsL3(const lm_access::TriggerID triggerID, const lm_access::LmType& type) const {
  long res = 0;
  LumBlkMap::const_iterator it_lbn;
  
  for(it_lbn = _lbn.begin(); it_lbn != _lbn.end(); it_lbn++) {
    const LumBlkInfo& lm_info = it_lbn->second;
    if (this->isGoodLBN(it_lbn->first, triggerID, type)) {
      res += lm_info.acceptsL3(triggerID);
    }
  }

  return res;
}

//---------------------------------------------------------------

int LumFile::downloadLBN(const int lbn, 
			 const lm_access::TriggerMap& triggers) {
  if ( ! _lbn.has(lbn) ) {
    int status = _lbn.read(lbn, lbn, triggers);
    _lbn[lbn].setdebug(_debug);
    return status;
  } else return 0;
    
}

//---------------------------------------------------------------

int LumFile::downloadLBN(const int lbn_min, const int lbn_max, 
			 const lm_access::TriggerMap& triggers) {
  int status = _lbn.read(lbn_min, lbn_max, triggers);
  for(int lbn = lbn_min; lbn <= lbn_max; lbn++) _lbn[lbn].setdebug(_debug);
  return status;
}
//---------------------------------------------------------------

int LumFile::downloadLBN(const std::list<int>& lbns, 
			 const lm_access::TriggerMap& triggers) {
  int status = _lbn.read(lbns, triggers);
  for(std::list<int>::const_iterator it=lbns.begin();it!=lbns.end(); it++) _lbn[*it].setdebug(_debug);
  return status;
}

//---------------------------------------------------------------


int LumFile::disableLBN(const int lbn) {
  if (_debug) std::cout << "disabling lbn " << lbn  << std::endl; 
  if ( _lbn.has(lbn) ) _lbn.erase(lbn);
  return 0;
    
}
