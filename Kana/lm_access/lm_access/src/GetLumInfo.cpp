#include "lm_access/GetLumInfo.hpp"

#include <string>

GetLumInfo::GetLumInfo(const int cacheSize) : _cache(cacheSize) {};
GetLumInfo::GetLumInfo(const GetLumInfo& rhs) : _cache(rhs._cache) {};

GetLumInfo& GetLumInfo::operator=(const GetLumInfo& rhs) {
  if (this != &rhs) _cache = rhs._cache;
  return *this;
}

bool GetLumInfo::isGoodTrigger(const int lbn, const std::string trigger) {
  return _cache.Get(lbn)->isGoodTrigger(trigger);
}

float GetLumInfo::prescale(const int lbn, const std::string trigger) {
  return _cache.Get(lbn)->prescale(trigger);
}
