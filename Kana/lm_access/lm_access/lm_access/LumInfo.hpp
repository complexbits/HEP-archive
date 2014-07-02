#ifndef _LUMINFO_HPP
#define _LUMINFO_HPP

/* 
 * File: LumInfo.hpp
 * Package: lm_access
 * Purpose: Accesses and holds luminosity information for one particular lbn
 *
 * Created:  30-Apr-2003 Alexander Kupco
 */

class LumInfo {
public:
  LumInfo(float prescale=0.):_prescale(prescale) {};
  ~LumInfo(){};

  inline float prescale() const {return _prescale;}

private:
  float _prescale;
};

#endif /* _LUMTICKINFO_HPP */
