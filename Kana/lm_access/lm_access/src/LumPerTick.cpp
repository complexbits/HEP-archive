#include "lm_access/LumPerTick.hpp"

LumPerTick::LumPerTick(const int cacheSize) : _cache(cacheSize) {};
LumPerTick::LumPerTick(const LumPerTick& rhs) : _cache(rhs._cache) {};

LumPerTick& LumPerTick::operator=(const LumPerTick& rhs) {
  if (this != &rhs) _cache = rhs._cache;
  return *this;
}

bool LumPerTick::isGoodTick(const int lbn, const int tick) {
  return _cache.Get(lbn)->isGoodTick(tick);
}

float LumPerTick::luminosity(const int lbn, const int tick) {
  return _cache.Get(lbn)->luminosity(tick);
}
float LumPerTick::protonHalo(const int lbn, const int tick) {
  return _cache.Get(lbn)->protonHalo(tick);
}
float LumPerTick::pbarHalo(const int lbn, const int tick) {
  return _cache.Get(lbn)->pbarHalo(tick);
}
float LumPerTick::avgNumInelastic(const int lbn, const int tick) {
  return _cache.Get(lbn)->avgNumInelastic(tick);
}
