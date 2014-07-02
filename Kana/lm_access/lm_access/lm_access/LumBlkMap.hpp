#ifndef _LUMBLKMAP_HPP
#define _LUMBLKMAP_HPP

/* 
 * File: LumBlkMap.hpp
 * Package: lm_access
 * Purpose: class LumBlkMap contains all inforamtion necessary for
 *          calculation of luminosity in the data analysis
 *
 * Created:  09-Oct-2001 Alexander Kupco
 * Modified: 05-May-2002 Alexander Kupco
 */

#include <lm_access/globaldef.hpp>
#include <lm_access/TriggerMap.hpp>
#include <lm_access/LumBlkInfo.hpp>
#include <map>

class LumBlkMap : public std::map<int, LumBlkInfo>{
private:

  bool _debug;

public:
  LumBlkMap();
  LumBlkMap(const LumBlkMap& rhs);
  virtual ~LumBlkMap() {};

  int read(const int lbn_min, const int lbn_max, 
	   const lm_access::TriggerMap& triggers);

  int read(const std::list<int>& lbns,const lm_access::TriggerMap& triggers);

  int has(const int LumID) const;
  inline void setdebug(const bool debug){_debug = debug;};


};

#endif /* _LUMBLKMAP_HPP */
