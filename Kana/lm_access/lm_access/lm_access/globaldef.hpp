#ifndef _LM_ACCESS_GLOBALDEF_HPP
#define _LM_ACCESS_GLOBALDEF_HPP

#include <string>

namespace lm_access {
  /* the constant the flat file luminosity has to be multiplied by */
  extern const float effXsec;
  extern const float lmCorrection;
  extern const float avgNcoef;  /* conversion constant between instantenious luminosity
                                   and average number of interaction in one  bunch crossing */

  /* location of the LBN flat files */
  extern std::string lbn_dir;
  extern std::string default_lbn_dir;


  /* constants for correcting for nonlinearity */

  extern  float betaNL;
  extern  float offsetNL;

  extern const float betaNL_val;
  extern const float offsetNL_val;

  extern const float RF;
  extern const int bucketsPerTick; 
 
  // conversion_factor = ((double)lm_access::bucketsPerTick/lm_access::RF)
  extern const double conversion_factor;

  enum FileType {unknown, raw, reconstructed, roottuple, thumbnail};
  enum LmType {Triggered, Recorded, Reconstructed, ReconstructedDontCheckL3, Delivered, unknowntype};
  enum LumBlkStatus {OK, BAD};

  static std::string s_unknown=std::string("unknown");
  static std::string s_raw=std::string("raw");
  static std::string s_reconstructed=std::string("reconstructed");
  static std::string s_roottuple=std::string("roottuple");
  static std::string s_thumbnail=std::string("thumbnail");
  static std::string s_Triggered=std::string("Triggered");
  static std::string s_Recorded=std::string("Recorded");
  static std::string s_Reconstructed=std::string("Reconstructed");
  static std::string s_ReconstructedDontCheckL3=std::string("ReconstructedDontCheckL3");
  static std::string s_Delivered=std::string("Delivered");
//
// added to cope with the differences between reconstructions information on stage3 files
// and the SAM DataTiers table.
  static std::string s_tmb=std::string("tmb");
//
  inline FileType translate_filetype(const std::string& c){
    if(c == s_unknown){return unknown;}
    if(c == s_raw){return raw;}
    if(c == s_reconstructed){return reconstructed;}
    if(c == s_roottuple){return roottuple;}
    if(c == s_thumbnail){return thumbnail;}
    if(c == s_tmb) {return thumbnail;}
    return unknown;
  }
  inline LmType translate_lmtype(const std::string& c){
    if(c == s_Triggered){return Triggered;}
    if(c == s_Recorded){return Recorded;}
    if(c == s_Reconstructed){return Reconstructed;}
    if(c == s_ReconstructedDontCheckL3){return ReconstructedDontCheckL3;}
    if(c == s_Delivered){return Delivered;}
    return unknowntype;
  }


 };

#endif /* _LM_ACCESS_GLOBALDEF_HPP */
