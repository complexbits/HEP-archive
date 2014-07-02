#include "lm_access/LumTickMap.hpp"
#include "lm_access/globaldef.hpp"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

LumTickMap::LumTickMap() : _lbn(), _lbnFileExists(false), _tickMap() {};
LumTickMap::LumTickMap(const LumTickMap& rhs) : 
  _lbn(rhs._lbn), _lbnFileExists(rhs._lbnFileExists), _tickMap(rhs._tickMap)
{};

LumTickMap::LumTickMap(const int lbn) : 
  _lbn(lbn), _lbnFileExists(false), _tickMap()
{
  const int str_buffer_length = 20;
  char s_number[str_buffer_length];
  sprintf(s_number, "/%i/%i", lbn/10000, lbn);
  const string fname = lm_access::lbn_dir + string(s_number);
//  if (access(fname.c_str(), R_OK) == 0) {
    _lbnFileExists = true;
//    gz::igzstream f;
//    f.open(fname.c_str());
    if (! LumTickMap::_read(lbn)) {
      _lbnFileExists = false;
      _tickMap = std::map<unsigned char, LumTickInfo>();
    }
//    f.close();
//  }
}

LumTickMap::~LumTickMap(){};

LumTickMap& LumTickMap::operator=(const LumTickMap& rhs) {
  if (this != & rhs) {
    _lbn = rhs._lbn;
    _lbnFileExists = rhs._lbnFileExists;
    _tickMap = rhs._tickMap;
  }
  return *this;
};

bool LumTickMap::isGoodLBN() const {
  return (_lbnFileExists && _tickMap.size());
};
bool LumTickMap::isGoodTick(const int tick) const {
  if (isGoodLBN()) {
    return (_tickMap.find((unsigned char) tick) != _tickMap.end());
  } else return false;
}

float LumTickMap::luminosity(const int tick) const {
  std::map<unsigned char, LumTickInfo>::const_iterator it = _tickMap.find(tick);
  return (it != _tickMap.end()) ? it->second.luminosity() : -1e20;
}
float LumTickMap::protonHalo(const int tick) const {
  std::map<unsigned char, LumTickInfo>::const_iterator it = _tickMap.find(tick);
  return (it != _tickMap.end()) ? it->second.pHalo() : -1e20;
}
float LumTickMap::pbarHalo(const int tick) const {
  std::map<unsigned char, LumTickInfo>::const_iterator it = _tickMap.find(tick);
  return (it != _tickMap.end()) ? it->second.pbarHalo() : -1e20;
}
float LumTickMap::avgNumInelastic(const int tick) const {
  std::map<unsigned char, LumTickInfo>::const_iterator it = _tickMap.find(tick);
  return (it != _tickMap.end()) ? it->second.avgNumInelastic() : -1e20;  
}

double LumTickMap::lumDelivered() const {
    double lum = -1, time = 0;
    map<unsigned char, LumTickInfo>::const_iterator it;
    for(it = _tickMap.begin(); it != _tickMap.end(); it++) {
	lum += it->second.luminosity();
    }
    time = _nb_ticks*(lm_access::bucketsPerTick/lm_access::RF);
    return lum*time;
}

void LumTickMap::print() const {
  cout << "LumTickMap::print() for LBN=" << _lbn << endl
       << "   LBN file " << ( (_lbnFileExists) ? "exists" : " does not exist")
       << endl;
  map<unsigned char, LumTickInfo>::const_iterator it;
  for(it = _tickMap.begin(); it != _tickMap.end(); it++) {
    cout << "   " << (int) it->first
	 << "  " << it->second.luminosity()
	 << "  " << it->second.pHalo()
	 << "  " << it->second.pbarHalo()
	 << "  " << it->second.avgNumInelastic() 
	 << endl;
  }
}


int LumTickMap::_read(gz::igzstream& s) {
  const string B0CABEEF = "0xB0CABEEF";
  string curr;
  bool seek = true;
  bool problem = false;
  bool found = false;
  while (seek) {
    s >> curr;
    if ( s.fail() || (! s) ) {
      seek = false;
      problem = true;
    } else if (curr == B0CABEEF) seek = false;
  }

  int count = 0;
  if (! problem) {
    int i_tick;
    float lm_old_effXsec = -1;
    _nb_ticks = 0;
    double duration;
    s >> duration >> lm_old_effXsec;
    _nb_ticks = long(duration);
    //cout << _nb_ticks << " " << lm_old_effXsec << endl;
    while (s) {
      float luminosity, pHalo, pbarHalo;
      s >> i_tick >> luminosity >> pHalo >> pbarHalo;
      /* luminosity correction from the file read */
      //cout << i_tick << " " << luminosity << " " << pHalo << " " << pbarHalo << endl;
      if (s.fail()) break;
      else if (i_tick) {
        /* luminosity correction from the file read - Remove Feb 03,04 */ 
        // if ((lm_access::effXsec>0) && (lm_old_effXsec != -1))
    	//    luminosity *= (lm_old_effXsec/(lm_access::effXsec*1000));
	LumTickInfo tickInfo(luminosity, pHalo, pbarHalo);    
	_tickMap[(unsigned char) i_tick] = tickInfo;
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
int LumTickMap::_read(int lbn) {
    int status = 1;
    bool debug = 0;
    int count = 0;
    int lbn_max = 0;
    if (debug) cout << "LumTickMap::read: Creating DB interface for LBN = " << lbn << std::endl;
    std::list<string> triggers;
    LmAccessInterface* interface = LmAccessInterface::get_Instance(debug);
    interface->Load(lbn,lbn_max);

    if (!interface->get_status(lbn)) {
       cout <<"LumTickMap::read: BAD Interface status "  << std::endl;
       return 0;
    }
    if (!interface->get_tick_status(lbn)) {
       cout << "LumTickMap::read: BAD Tick map status "  << std::endl;
       return 0;
    }
// The method get_Tick_info() returns a pointer to a map::<int,LmTickList*>,
// where int is the LBN and LmTickList is a list::<LmTickData*>. Because of so
// many pointers one have to de-reference as below to have the iteration properly
// done (it is a pointer to a pointer)
//
    LmTickList tick_info = interface->get_Tick_info(lbn);
    for(LmTickList::const_iterator it = (tick_info).begin(); it!= (tick_info).end(); it++) {
       float ticklum = (it)->get_InstLuminosity();
       float phalo   = (it)->get_pHalo();
       float ahalo   = (it)->get_pbarHalo();
//       LumTickInfo tickInfo(ticklum,phalo,ahalo);
//       _tickMap[(unsigned char) (it)->get_Tick()] = tickInfo;
       count++;
    }
    return count;
}
