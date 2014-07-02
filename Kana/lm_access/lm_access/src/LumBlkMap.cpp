#include <lm_access/LumBlkMap.hpp>
#include <lm_access/gzstream.hpp>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fstream>

#include "lm_access_interface/LmAccessInterface.hpp"

using namespace std;

LumBlkMap::LumBlkMap() : std::map<int, LumBlkInfo>(),_debug(0) {};
LumBlkMap::LumBlkMap(const LumBlkMap& rhs) : std::map<int, LumBlkInfo>(rhs),_debug(0) {};

int LumBlkMap::read(const int lbn_min, const int lbn_max, 
		    const lm_access::TriggerMap& triggers) {
  /*
   *  Purpose: read information about good luminosity block (status 0x0) 
   *           from text files (stage 2)
   *
   *  Variables:
   *     lbn_min, lbn_max: interval of luminosity block numbers
   *                       that should be downloaded
   *     triggers: triggers for which the information are requested
   */
  int count_good_lbn = 0;
//  const int str_buffer_length = 20;
//  char s_number[str_buffer_length];
  LmAccessInterface* interf = LmAccessInterface::get_Instance(_debug);
//  interf->set_debug(_debug);
  interf->Load(lbn_min,lbn_max);

  for(int i = lbn_min; i <= lbn_max; i++) {
//    if (! this->has(i)) if (sprintf(s_number, "/%i/%i", i/10000, i) >= 0) {
//      string fname = lm_access::lbn_dir + string(s_number);
//      if (access(fname.data(), R_OK) == 0) {
//      gz::igzstream f;
//	f.open(fname.data());
     if (this->has(i)) continue;
     if (interf->get_status(i)) {
        this->operator[](i) = LumBlkInfo(i, triggers);
        this->operator[](i).setlbn(i);
        count_good_lbn++;
     } else this->operator[](i)=LumBlkInfo(); /* if there is no LBN file add empty 
        			   *  LumBlkInfo */
  }
  return count_good_lbn++;
}

int LumBlkMap::read(const std::list<int>& lbns, const lm_access::TriggerMap& triggers) {
  /*
   *  Purpose: read information about good luminosity block (status 0x0) 
   *           from Database
   */
  int count_good_lbn = 0;
  LmAccessInterface* interf = LmAccessInterface::get_Instance(_debug);
  interf->Load(lbns);

  for(std::list<int>::const_iterator it = lbns.begin();it!=lbns.end(); it++) {
     if (this->has(*it)) continue;
     if (interf->get_status(*it)) {
        this->operator[](*it) = LumBlkInfo(*it, triggers);
        this->operator[](*it).setlbn(*it);
        count_good_lbn++;
     } else this->operator[](*it); /* if there is no LBN file add empty 
        			   *  LumBlkInfo */
  }
  return count_good_lbn++;
}

int LumBlkMap::has(const int LumID) const{
  LumBlkMap::const_iterator it = this->find(LumID);
  return (it != this->end());
}
