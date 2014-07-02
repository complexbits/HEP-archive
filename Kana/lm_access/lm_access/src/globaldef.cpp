#include <lm_access/globaldef.hpp>

namespace lm_access {
  
  const float effXsec = 46;      // luminosity constant [mb]
  static const float inelXsec = 58.8;   // ppbar inelastic cross section [mb]
  const float RF = 53.104e6;     // accelerator radio frequency [Hz]
  const int bucketsPerTick = 7; 
  static const int tickPerTurn = 159;

  const float lmCorrection = 1.0;
  const float avgNcoef = inelXsec * 1000 * bucketsPerTick * tickPerTurn / RF;

  const double conversion_factor= ((double)lm_access::bucketsPerTick)/lm_access::RF;
  std::string default_lbn_dir("/prj_root/500/com/offline/stage3"); 
  std::string lbn_dir(default_lbn_dir);

  float betaNL = 0;
  float offsetNL = 0;

  // nonlinearity factor in L measurement determined 8-04
  // correction to the previous efficiency  (form (1-beta*lum)/(1+offsetNL)) due to nonlinearity and finite <L> of around 20 in sample used

  const float betaNL_val = 10.23E-4;
  const float offsetNL_val = 0.021175;

}

