#ifndef _LUMTICKINFO_HPP
#define _LUMTICKINFO_HPP

/* 
 * File: LumTickInfo.hpp
 * Package: lm_access
 * Purpose: Accesses and holds luminosity information for one particular tick
 *
 * Created:  30-Apr-2003 Alexander Kupco
 */

class LumTickInfo {
public:
  LumTickInfo(float luminosity = 0, float pHalo = 0, float pbarHalo = 0) : 
    _luminosity(luminosity), _pHalo(pHalo), _pbarHalo(pbarHalo) {};
  ~LumTickInfo(){};

  float luminosity() const {return _luminosity;};
  float pHalo() const {return _pHalo;};
  float pbarHalo() const {return _pbarHalo;};
  
  // average number of ppbar inelastic interaction per bunch Xing
  float avgNumInelastic() const;

private:
  float _luminosity;       // instantenios luminosity (E30)
  float _pHalo;            // proton halo  (Hz)
  float _pbarHalo;         // anti-proton halo  (Hz)
};

#endif /* _LUMTICKINFO_HPP */
