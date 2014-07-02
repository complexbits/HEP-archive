#include "lm_access/LumTrigger.hpp"
#include <iostream>
using namespace std;

LumTrigger::LumTrigger(const float& lm_l1, const float& lm_raw, 
		       const int& hasL2, const long& aL1, const long& aL2,
	     const long& aL3) : 
  _LumL1(lm_l1), _LumRaw(lm_raw), _hasL2(hasL2), _acceptsL1(aL1), _acceptsL2(aL2), _acceptsL3(aL3) {};

LumTrigger::LumTrigger(const LumTrigger& rhs) : 
   _LumL1(rhs._LumL1), _LumRaw(rhs._LumRaw), _hasL2(rhs._hasL2), _acceptsL1(rhs._acceptsL1), _acceptsL2(rhs._acceptsL2), _acceptsL3(rhs._acceptsL3) {};

LumTrigger& LumTrigger::operator=(const LumTrigger& rhs) {
  _LumL1 = rhs._LumL1;
  _LumRaw = rhs._LumRaw;
  _hasL2 = rhs._hasL2;
  _acceptsL1 = rhs._acceptsL1;
  _acceptsL2 = rhs._acceptsL2;
  _acceptsL3 = rhs._acceptsL3;

  return *this;
}
