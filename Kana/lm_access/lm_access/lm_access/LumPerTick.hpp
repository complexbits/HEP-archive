#ifndef _LM_ACCESS_LUMPERTICK_HPP
#define _LM_ACCESS_LUMPERTICK_HPP

/* 
 * File: LumPerTick.hpp
 * Package: lm_access
 * Purpose: User end class for accessing luminosity information per tick
 *
 * Created:  30-Apr-2003 Alexander Kupco
 */

#include "lm_access/LumTickCache.hpp"

class LumPerTick {
public:
  LumPerTick(const int cacheSize = 10);
  LumPerTick(const LumPerTick& rhs);
  ~LumPerTick() {};

  LumPerTick& operator=(const LumPerTick& rhs);

  // return true if the tick information exists
  bool isGoodTick(const int lbn, const int tick); 

  // instantaneous luminosity (E30)
  float luminosity(const int lbn, const int tick);  
  float protonHalo(const int lbn, const int tick);  // proton halo (Hz)
  float pbarHalo(const int lbn, const int tick);    // anti-proton halo (Hz)
  // average number of ppbar inelastic interaction per bunch Xing
  float avgNumInelastic(const int lbn, const int tick);   
  
private:
  LumTickCache _cache;
};

#endif /* _LM_ACCESS_LUMPERTICK_HPP */
