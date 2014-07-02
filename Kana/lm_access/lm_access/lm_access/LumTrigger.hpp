#ifndef _LM_ACCESS_LUMTRIGGER_HPP
#define _LM_ACCESS_LUMTRIGGER_HPP

class LumTrigger {
protected:
  float _LumL1;         /* L1 luminosity */
  float _LumRaw;        /* Recorded luminosity */
  int _hasL2;          /* (1=true (L2 problem), 0=false, -1=error) */
  long _acceptsL1;	/* number of L1 accepts */
  long _acceptsL2;	/* number of L2 accepts */
  long _acceptsL3;	/* number of L3 accepts */

public:
  LumTrigger(const float& lm_l1 = -1, const float& lm_raw = -1, 
	     const int& hasL2 = -1, const long& aL1 = 0, const long& aL2 = 0,
	     const long& aL3 = 0);
  LumTrigger(const LumTrigger& rhs);
  ~LumTrigger(){};

  LumTrigger& operator=(const LumTrigger& rhs);

  inline float luml1() const {return _LumL1;};
  inline float lumraw() const {return _LumRaw;};
  inline int hasL2() const {return _hasL2;};

  inline long acceptsL1() const {return _acceptsL1;};
  inline long acceptsL2() const {return _acceptsL2;};
  inline long acceptsL3() const {return _acceptsL3;};

  inline void set_acceptsL1(long aL1) {_acceptsL1 = aL1;};
  inline void set_acceptsL2(long aL2) {_acceptsL2 = aL2;};
  inline void set_acceptsL3(long aL3) {_acceptsL3 = aL3;};

  inline void set_luml1(float lumL1) {_LumL1 = lumL1;};
  inline void set_lumraw(float lumRaw) {_LumRaw = lumRaw;};
  inline void set_hasL2(int hasL2) {_hasL2 = hasL2;};
};

#endif /* _LM_ACCESS_LUMTRIGGER_HPP */




