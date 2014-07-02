#ifndef _LUMTICKMAP_HPP
#define _LUMTICKMAP_HPP

/* 
 * File: LumTickMap.hpp
 * Package: lm_access
 * Purpose: Accesses and holds tick luminosity information in one particular LBN
 *
 * Created:  30-Apr-2003 Alexander Kupco
 * Modified: 14-November-2003 Petr Homola
 */

#include "lm_access/LumTickInfo.hpp"
#include "lm_access/gzstream.hpp"
#include "lm_access_interface/LmAccessInterface.hpp"
#include <map>

class LumTickMap {
public:
  LumTickMap();
  LumTickMap(const LumTickMap& rhs);
  LumTickMap(const int lbn);
  ~LumTickMap();

  LumTickMap& operator=(const LumTickMap& rhs);

  bool isGoodLBN() const;                  // true if flat file exists
                                           // and at least tick was downloaded
  bool isGoodTick(const int tick) const;   // true if tick is listed 
                                           // in the flat file

  // instantaneous luminosity (E30)
  float luminosity(const int tick) const;  // (E30)
  float protonHalo(const int tick) const;  // (Hz)
  float pbarHalo(const int tick) const;    // (Hz)
  // average number of ppbar inelastic interaction per bunch Xing
  float avgNumInelastic(const int tick) const;

  double lumDelivered() const;	// delivered luminosity per block

  void print() const;          // prints detailed information about LBN

private:
  int _lbn;
  bool _lbnFileExists;                          /* true if LBN file exists */
  std::map<unsigned char, LumTickInfo> _tickMap;   /* tick map */
  long _nb_ticks; /* number of ticks per LBN */

  int _read(gz::igzstream& s);  // download information for all ticks
                                // from the stream 
                                // return 0 if it fails
  int _read(int lbn);           // idem, from DB
};

#endif /* _LUMTICKMAP_HPP */
