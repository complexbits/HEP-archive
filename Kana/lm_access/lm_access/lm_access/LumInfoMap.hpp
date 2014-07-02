#ifndef _LUMINFOMAP_HPP
#define _LUMINFOMAP_HPP

/* 
 * File: LumInfoMap.hpp
 * Package: lm_access
 * Purpose: Accesses and holds info luminosity information in one particular LBN
 *
 * Created:  30-Apr-2003 Alexander Kupco
 * Modified: 14-November-2003 Petr Homola
 */

#include "lm_access/LumInfo.hpp"
#include "lm_access/gzstream.hpp"
#include "lm_access_interface/LmAccessInterface.hpp"
#include <map>

class LumInfoMap {
public:
  LumInfoMap();
  LumInfoMap(const LumInfoMap& rhs);
  LumInfoMap(const int lbn);
  ~LumInfoMap();

  LumInfoMap& operator=(const LumInfoMap& rhs);

  bool isGoodLBN() const;                  // true if flat file exists
                                           // and at least info was downloaded
  bool isGoodTrigger(const std::string trigger) const;   // true if info is listed 
                                           // in the flat file

  float prescale(const std::string trigger)const;

  void print() const;          // prints detailed information about LBN

private:
  int _lbn;
  bool _lbnFileExists;                          /* true if LBN file exists */
  std::map<const std::string , LumInfo> _infoMap;   /* info map */
  long _nb_infos; /* number of infos per LBN */

  int _read(gz::igzstream& s);  // download information for all infos
                                // from the stream 
                                // return 0 if it fails
  int _read(int lbn);           // idem, from DB
};

#endif /* _LUMINFOMAP_HPP */





