#ifndef _LM_ACCESS_GETLUMINFO_HPP
#define _LM_ACCESS_GETLUMINFO_HPP

/* 
 * File: GetLumInfo.hpp
 * Package: lm_access
 * Purpose: User end class for accessing luminosity information per info
 *
 * Created:  30-Apr-2003 Alexander Kupco
 */

#include "lm_access/LumInfoCache.hpp"

class GetLumInfo {
public:
  GetLumInfo(const int cacheSize = 10);
  GetLumInfo(const GetLumInfo& rhs);
  ~GetLumInfo() {};

  GetLumInfo& operator=(const GetLumInfo& rhs);

  // return true if the info information exists
  bool isGoodTrigger(const int lbn, const std::string trigger); 

  // instantaneous luminosity (E30)
  float prescale(const int lbn, const std::string trigger);  
  
private:
  LumInfoCache _cache;
};

#endif /* _LM_ACCESS_GETLUMINFO_HPP */
