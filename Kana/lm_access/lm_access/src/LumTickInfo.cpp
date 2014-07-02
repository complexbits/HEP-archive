#include <lm_access/globaldef.hpp>
#include <lm_access/LumTickInfo.hpp>

float LumTickInfo::avgNumInelastic() const {
  return _luminosity * lm_access::avgNcoef;
}
