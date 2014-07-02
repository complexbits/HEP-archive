#include "lm_access/LumInfoMap.hpp"
#include "lm_access/globaldef.hpp"
#include "lm_access_interface/LmAccessInterface.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

LumInfoMap::LumInfoMap() : _lbn(), _lbnFileExists(false), _infoMap() {};

LumInfoMap::LumInfoMap(const LumInfoMap& rhs) : 
  _lbn(rhs._lbn), _lbnFileExists(rhs._lbnFileExists), _infoMap(rhs._infoMap)
{};

LumInfoMap::LumInfoMap(const int lbn) : 
  _lbn(lbn), _lbnFileExists(false), _infoMap()
{
  LmAccessInterface *interface = LmAccessInterface::get_Instance();
  interface->Load(lbn,lbn);
  if (interface->get_status(lbn)) {
     _lbnFileExists = true;
    if (! LumInfoMap::_read(lbn)) {
      _lbnFileExists = false;
      _infoMap = std::map<const std::string, LumInfo>();
    }
  }
}

LumInfoMap::~LumInfoMap(){};

LumInfoMap& LumInfoMap::operator=(const LumInfoMap& rhs) {
  if (this != & rhs) {
    _lbn = rhs._lbn;
    _lbnFileExists = rhs._lbnFileExists;
    _infoMap = rhs._infoMap;
  }
  return *this;
};

bool LumInfoMap::isGoodLBN() const {
  return (_lbnFileExists && _infoMap.size());
};
bool LumInfoMap::isGoodTrigger(const std::string trigger) const {
  if (isGoodLBN()) {
    return (_infoMap.find(trigger) != _infoMap.end());
  } else return false;
}

float LumInfoMap::prescale(const std::string trigger) const {
  std::map<const std::string, LumInfo>::const_iterator it = _infoMap.find(trigger);
  return (it != _infoMap.end()) ? it->second.prescale() : 1.e-20;
}



void LumInfoMap::print() const {
  cout << "LumInfoMap::print() for LBN=" << _lbn << endl
       << "   LBN file " << ( (_lbnFileExists) ? "exists" : " does not exist")
       << endl;
  map<const std::string , LumInfo>::const_iterator it;
  for(it = _infoMap.begin(); it != _infoMap.end(); it++) {
    cout << "   " <<  it->first
	 << "  " << it->second.prescale()
	 << endl;
  }
}


int LumInfoMap::_read(gz::igzstream& s) {
  const string B0CABEEF = "0xB0CABEEF";
  string curr;
  bool seek = true;
  bool problem = false;
  bool found = false;
  /*
  while (seek) {
    s >> curr;
    if ( s.fail() || (! s) ) {
      seek = false;
      problem = true;
    } else if (curr == B0CABEEF) seek = false;
  }
  */

  int count = 0;
  if (! problem) {
    std::string s_trigger;
     while (s) {
       int dummy;
       float prescale;
       float dummy2;
       s >> s_trigger >> dummy2 >> dummy2 >> dummy >> dummy >> dummy >> prescale >> dummy >> dummy >> dummy;
      if (s.fail()) break;
      if (s_trigger == "0xDEADBEEF") break;
      else{
	LumInfo triggerInfo(prescale);    
	_infoMap[ s_trigger] = triggerInfo;
	count++;
      }
    }
  }

  if (problem) {
    cerr << "Format of the stream for LBN=" << _lbn 
	 << " is not correct." << endl;
    return 0;
  } else return count;
}
int LumInfoMap::_read(int lbn) {
    int status = 1;
    int count = 0;
    int lbn_max=0;
    bool debug = 0;
    std::list<string> triggers;
    LmAccessInterface* interface = LmAccessInterface::get_Instance(debug);
    interface->Load(lbn,lbn_max);
    if (!interface->get_status(lbn)) {
       cout <<"LumTickMap::read: BAD Interface status "  << std::endl;
       return 0;
    }
    if (!interface->get_trigger_status(lbn)) {
       cout << "LumTickMap::read: BAD Trigger map status "  << std::endl;
       return 0;
    }
    LmTriggerList trig_info = interface->get_Trigger_info(lbn,triggers);
    for (LmTriggerList::const_iterator it=(trig_info).begin(); it!=(trig_info).end();it++) {
          LumInfo triggerInfo((it)->Prescale());    
          _infoMap[(it)->Trigger()] = triggerInfo;
          count++;
    }
    return count;
}
