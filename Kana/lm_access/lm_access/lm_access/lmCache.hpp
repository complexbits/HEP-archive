#ifndef _LM_ACCESS_LMCACHE_HPP
#define _LM_ACCESS_LMCACHE_HPP

/* 
 * File: lmCache.hpp
 * Package: lm_access
 * Purpose: Template class for caching mechanism
 *          Constructor V(K) responsible for downloading the information
 *          must exists!
 *
 * Created:  30-Apr-2003 Alexander Kupco
 * Modified: 29-Nov-2003 H. Schellman
 *           add a typedef for the map iterator because GCC insists
 */

#include <map>
#include <vector>

namespace lm_access {
  template<class K, class V> 
  class lmCache {
  public:
    lmCache(const int size = 1);
    lmCache(const lmCache<K, V>& rhs);
    ~lmCache(){};

    lmCache& operator=(const lmCache<K, V>& rhs);

    V* Get(const K& key);

  private:
    bool _isCacheFull() const;
    K nextKeyToRemove();

    int _size;
    int _curr;
    std::map<K, V> _map;
    std::vector<K> _keyIndex;
  };
} // namespace lm_access 

//   ----    definitions    -------

#include <iostream>

using namespace std;

namespace lm_access {

  template<class K, class V>
  lmCache<K, V>::lmCache(const int size) : _size(size), _curr(0), _map(), 
					   _keyIndex(size)
  {
    if (_size < 1) {
      cerr << "lmCache::lmCache(int) - wrong cache size ("
	   << size << ", default value is used instead of it"
	   << endl;
      _size = 1;
      _keyIndex = vector<K>(size);
    }
  }
  template<class K, class V>
  lmCache<K, V>::lmCache(const lmCache<K, V>& rhs) : 
    _size(rhs._size), _curr(rhs._curr), _map(rhs._map), _keyIndex(rhs._keyIndex) {};
  
  template<class K, class V>
  lmCache<K,V>& lmCache<K, V>::operator=(const lmCache<K, V>& rhs) {
    if (this != &rhs) {
      _size = rhs._size;
      _curr = rhs._curr;
      _map = rhs._map;
      _keyIndex = rhs._keyIndex;
    }
    return *this;
  }
  
  template<class K, class V>
  V* lmCache<K, V>::Get(const K& key) {
    typename    map<K, V>::iterator it ;
    it = _map.find(key);
    if (it == _map.end()) {
      if ( _isCacheFull() ) _map.erase(nextKeyToRemove());
      _keyIndex[_curr] = key;
      _map[key] = V(key);
    }
    it = _map.find(key);
    return &(it->second);
  }
  
  template<class K, class V>
  bool lmCache<K, V>::_isCacheFull() const {
    return (_map.size() >= _size);
  };
  
  template<class K, class V>
  K lmCache<K, V>::nextKeyToRemove() {
    K toRemove = _keyIndex[_curr++];
    _curr = _curr % _size;
    return toRemove;
  }

} // namespace lm_access


#endif // _LM_ACCESS_LMCACHE_HPP
