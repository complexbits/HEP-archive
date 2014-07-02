#ifndef _LUMBLKINFO_HPP
#define _LUMBLKINFO_HPP

/* 
 * File: LumBlkInfo.hpp
 * Package: lm_access
 * Purpose: Store luminosity block information
 *
 * Created:  09-Oct-2001 Alexander Kupco
 * Modified: 14-November-2003 Petr Homola
 */

#include "lm_access/globaldef.hpp"
#include "lm_access/TriggerMap.hpp"
#include "lm_access/LumFileRelease.hpp"
#include "lm_access/LumTrigger.hpp"
#include "lm_access/gzstream.hpp"
#include "lm_access/tickutility.hpp"
#include <iostream>
#include <map>

#include "lm_access_interface/LmAccessInterface.hpp"

class  LumBlkInfo{
public:
  LumBlkInfo();
  LumBlkInfo(const LumBlkInfo& rhs);
  LumBlkInfo(gz::igzstream& s, const lm_access::TriggerMap& triggers);
  LumBlkInfo(int lbn,const lm_access::TriggerMap& triggers);
  ~LumBlkInfo(){};

  LumBlkInfo& operator=(const LumBlkInfo& rhs);

  double luml1(const lm_access::TriggerID& triggerID, const int ticker=0) const;
  double lumraw(const lm_access::TriggerID& triggerID,const int ticker=0) const;
  double lumDelivered(const int ticker=0) const;
  double luminosity(const lm_access::TriggerID& triggerID,
		    const lm_access::LmType& type, const int ticker=0) const;
  long acceptsL1(const lm_access::TriggerID& triggerID) const;
  long acceptsL2(const lm_access::TriggerID& triggerID) const;
  long acceptsL3(const lm_access::TriggerID& triggerID) const;
  int lbn_file_status() const;
  int trigger_status(const lm_access::TriggerID triggerID, 
		     const lm_access::LmType& type, int keepL2) const;
  int release_status(const LumFileRelease& lm_release, int& keepL2) const;
  int status(const lm_access::TriggerID triggerID, 
	     const lm_access::LmType& type,
	     const LumFileRelease& lm_release) const;

  void print(std::ostream& s = std::cout) const;
  inline void setdebug(const bool debug){_debug = debug;};
  inline void setlbn(const int lbn){_lbn = lbn;};
private:
  float _corrNL[37];
  bool _debug;
  int _lbn_file;    /* true if LBN file exists */
  std::map<lm_access::TriggerID, LumTrigger> _triggers;
  std::map<LumFileRelease, int> _good_releases;
  double _lumDelivered[37];
  int _lbn;
  tickutility* tickmap;

};

#endif /* _LUMBLKINFO_HPP */
