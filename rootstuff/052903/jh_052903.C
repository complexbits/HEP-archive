#define jh_052903_cxx
#include "jh_052903.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "iostream.h"

void jh_052903::Loop()
{

TFile plotz("jh_052903.root","recreate");

  // My variables

  float minMass = 4.75; float maxMass = 6.0;
  float div = 0.04;
  int nBins = (maxMass - minMass)/div;   


  // ------------ HISTOGRAMS FOR MASS < 1 GeV ------------------------------------------  
  
  TH1F* m_lo_coll_080 = new TH1F("m_lo_coll_080", "low mass, coll 080", 40,minMass,maxMass);
  TH1F* m_lo_coll_100 = new TH1F("m_lo_coll_100", "low mass, coll 100", 40,minMass,maxMass);
  TH1F* m_lo_coll_125 = new TH1F("m_lo_coll_125", "low mass, coll 125", 40,minMass,maxMass);
  TH1F* m_lo_coll_150 = new TH1F("m_lo_coll_150", "low mass, coll 150", 40,minMass,maxMass);
  TH1F* m_lo_coll_175 = new TH1F("m_lo_coll_175", "low mass, coll 175", 40,minMass,maxMass);
  TH1F* m_lo_coll_200 = new TH1F("m_lo_coll_200", "low mass, coll 200", 40,minMass,maxMass);
  TH1F* m_lo_coll_225 = new TH1F("m_lo_coll_225", "low mass, coll 225", 40,minMass,maxMass);
  TH1F* m_lo_coll_250 = new TH1F("m_lo_coll_250", "low mass, coll 250", 40,minMass,maxMass);
  TH1F* m_lo_coll_275 = new TH1F("m_lo_coll_275", "low mass, coll 275", 40,minMass,maxMass);

  TH1F* m_lo_coll_300 = new TH1F("m_lo_coll_300", "low mass, coll 300", 40,minMass,maxMass);
  TH1F* m_lo_coll_325 = new TH1F("m_lo_coll_325", "low mass, coll 325", 40,minMass,maxMass);
  TH1F* m_lo_coll_350 = new TH1F("m_lo_coll_350", "low mass, coll 350", 40,minMass,maxMass);
  TH1F* m_lo_coll_375 = new TH1F("m_lo_coll_375", "low mass, coll 375", 40,minMass,maxMass);

  TH1F* m_lo_coll_400 = new TH1F("m_lo_coll_400", "low mass, coll 400", 40,minMass,maxMass);
  TH1F* m_lo_coll_425 = new TH1F("m_lo_coll_425", "low mass, coll 425", 40,minMass,maxMass);

  TH1F* m_lo_coll_450 = new TH1F("m_lo_coll_450", "low mass, coll 450", 40,minMass,maxMass);
  TH1F* m_lo_coll_475 = new TH1F("m_lo_coll_475", "low mass, coll 475", 40,minMass,maxMass);

  TH1F* m_lo_coll_500 = new TH1F("m_lo_coll_500", "low mass, coll 500", 40,minMass,maxMass);
  TH1F* m_lo_coll_525 = new TH1F("m_lo_coll_525", "low mass, coll 525", 40,minMass,maxMass);
  TH1F* m_lo_coll_550 = new TH1F("m_lo_coll_550", "low mass, coll 550", 40,minMass,maxMass);
  TH1F* m_lo_coll_575 = new TH1F("m_lo_coll_575", "low mass, coll 575", 40,minMass,maxMass);

  TH1F* m_lo_coll_600 = new TH1F("m_lo_coll_600", "low mass, coll 600", 40,minMass,maxMass);
  TH1F* m_lo_coll_625 = new TH1F("m_lo_coll_625", "low mass, coll 625", 40,minMass,maxMass);

  TH1F* m_lo_coll_650 = new TH1F("m_lo_coll_650", "low mass, coll 650", 40,minMass,maxMass);
  TH1F* m_lo_coll_675 = new TH1F("m_lo_coll_675", "low mass, coll 675", 40,minMass,maxMass);

  TH1F* m_lo_coll_700 = new TH1F("m_lo_coll_700", "low mass, coll 700", 40,minMass,maxMass);
  TH1F* m_lo_coll_725 = new TH1F("m_lo_coll_725", "low mass, coll 725", 40,minMass,maxMass);
  TH1F* m_lo_coll_750 = new TH1F("m_lo_coll_750", "low mass, coll 750", 40,minMass,maxMass);
  TH1F* m_lo_coll_775 = new TH1F("m_lo_coll_775", "low mass, coll 775", 40,minMass,maxMass);

  TH1F* m_lo_coll_800 = new TH1F("m_lo_coll_800", "low mass, coll 800", 40,minMass,maxMass);
  TH1F* m_lo_coll_825 = new TH1F("m_lo_coll_825", "low mass, coll 825", 40,minMass,maxMass);
  TH1F* m_lo_coll_850 = new TH1F("m_lo_coll_850", "low mass, coll 850", 40,minMass,maxMass);
  TH1F* m_lo_coll_875 = new TH1F("m_lo_coll_875", "low mass, coll 875", 40,minMass,maxMass);

  TH1F* m_lo_coll_900 = new TH1F("m_lo_coll_900", "low mass, coll 900", 40,minMass,maxMass);
  TH1F* m_lo_coll_925 = new TH1F("m_lo_coll_925", "low mass, coll 925", 40,minMass,maxMass);
  TH1F* m_lo_coll_950 = new TH1F("m_lo_coll_950", "low mass, coll 950", 40,minMass,maxMass);

  // dl_sig varied histograms, low mass

  TH1F* m_lo_dlsig_3_0 = new TH1F("m_lo_dlsig_3_0", "low mass, dlsig 3_0", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_3_2 = new TH1F("m_lo_dlsig_3_2", "low mass, dlsig 3_2", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_3_4 = new TH1F("m_lo_dlsig_3_4", "low mass, dlsig 3_4", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_3_6 = new TH1F("m_lo_dlsig_3_6", "low mass, dlsig 3_6", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_3_8 = new TH1F("m_lo_dlsig_3_8", "low mass, dlsig 3_8", 40,minMass,maxMass);

  TH1F* m_lo_dlsig_4_0 = new TH1F("m_lo_dlsig_4_0", "low mass, dlsig 4_0", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_4_2 = new TH1F("m_lo_dlsig_4_2", "low mass, dlsig 4_2", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_4_4 = new TH1F("m_lo_dlsig_4_4", "low mass, dlsig 4_4", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_4_6 = new TH1F("m_lo_dlsig_4_6", "low mass, dlsig 4_6", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_4_8 = new TH1F("m_lo_dlsig_4_8", "low mass, dlsig 4_8", 40,minMass,maxMass);

  TH1F* m_lo_dlsig_5_0 = new TH1F("m_lo_dlsig_5_0", "low mass, dlsig 5_0", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_5_2 = new TH1F("m_lo_dlsig_5_2", "low mass, dlsig 5_2", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_5_4 = new TH1F("m_lo_dlsig_5_4", "low mass, dlsig 5_4", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_5_6 = new TH1F("m_lo_dlsig_5_6", "low mass, dlsig 5_6", 40,minMass,maxMass);
  TH1F* m_lo_dlsig_5_8 = new TH1F("m_lo_dlsig_5_8", "low mass, dlsig 5_8", 40,minMass,maxMass);

  TH1F* m_lo_dlsig_6_0 = new TH1F("m_lo_dlsig_6_0", "low mass, dlsig 6_0", 40,minMass,maxMass);

  // Ksmt varied histograms, low mass

  TH1F* m_lo_Ksmt0 = new TH1F("m_lo_Ksmt0", "low mass, Ksmt 0", 40,minMass,maxMass);
  TH1F* m_lo_Ksmt1 = new TH1F("m_lo_Ksmt1", "low mass, Ksmt 1", 40,minMass,maxMass);
  TH1F* m_lo_Ksmt2 = new TH1F("m_lo_Ksmt2", "low mass, Ksmt 2", 40,minMass,maxMass);
  TH1F* m_lo_Ksmt3 = new TH1F("m_lo_Ksmt3", "low mass, Ksmt 3", 40,minMass,maxMass);
 
  // Kpt varied histograms, low mass

  TH1F* m_lo_Kpt_0_5 = new TH1F("m_lo_Kpt_0_5", "low mass, Kpt 0_5", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_0_6 = new TH1F("m_lo_Kpt_0_6", "low mass, Kpt 0_6", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_0_7 = new TH1F("m_lo_Kpt_0_7", "low mass, Kpt 0_7", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_0_8 = new TH1F("m_lo_Kpt_0_8", "low mass, Kpt 0_8", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_0_9 = new TH1F("m_lo_Kpt_0_9", "low mass, Kpt 0_9", 40,minMass,maxMass);

  TH1F* m_lo_Kpt_1_0 = new TH1F("m_lo_Kpt_1_0", "low mass, Kpt 1_0", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_1_1 = new TH1F("m_lo_Kpt_1_1", "low mass, Kpt 1_1", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_1_2 = new TH1F("m_lo_Kpt_1_2", "low mass, Kpt 1_2", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_1_3 = new TH1F("m_lo_Kpt_1_3", "low mass, Kpt 1_3", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_1_4 = new TH1F("m_lo_Kpt_1_4", "low mass, Kpt 1_4", 40,minMass,maxMass);
  TH1F* m_lo_Kpt_1_5 = new TH1F("m_lo_Kpt_1_5", "low mass, Kpt 1_5", 40,minMass,maxMass);
  
  // ------------ HISTOGRAMS FOR MASS > 1 GeV ------------------------------------------

  // coll varied histograms, high mass

  TH1F* m_hi_coll_080 = new TH1F("m_hi_coll_080", "high mass, coll 080", 40,minMass,maxMass);
  TH1F* m_hi_coll_100 = new TH1F("m_hi_coll_100", "high mass, coll 100", 40,minMass,maxMass);
  TH1F* m_hi_coll_125 = new TH1F("m_hi_coll_125", "high mass, coll 125", 40,minMass,maxMass);
  TH1F* m_hi_coll_150 = new TH1F("m_hi_coll_150", "high mass, coll 150", 40,minMass,maxMass);
  TH1F* m_hi_coll_175 = new TH1F("m_hi_coll_175", "high mass, coll 175", 40,minMass,maxMass);
  TH1F* m_hi_coll_200 = new TH1F("m_hi_coll_200", "high mass, coll 200", 40,minMass,maxMass);
  TH1F* m_hi_coll_225 = new TH1F("m_hi_coll_225", "high mass, coll 225", 40,minMass,maxMass);
  TH1F* m_hi_coll_250 = new TH1F("m_hi_coll_250", "high mass, coll 250", 40,minMass,maxMass);
  TH1F* m_hi_coll_275 = new TH1F("m_hi_coll_275", "high mass, coll 275", 40,minMass,maxMass);

  TH1F* m_hi_coll_300 = new TH1F("m_hi_coll_300", "high mass, coll 300", 40,minMass,maxMass);
  TH1F* m_hi_coll_325 = new TH1F("m_hi_coll_325", "high mass, coll 325", 40,minMass,maxMass);
  TH1F* m_hi_coll_350 = new TH1F("m_hi_coll_350", "high mass, coll 350", 40,minMass,maxMass);
  TH1F* m_hi_coll_375 = new TH1F("m_hi_coll_375", "high mass, coll 375", 40,minMass,maxMass);

  TH1F* m_hi_coll_400 = new TH1F("m_hi_coll_400", "high mass, coll 400", 40,minMass,maxMass);
  TH1F* m_hi_coll_425 = new TH1F("m_hi_coll_425", "high mass, coll 425", 40,minMass,maxMass);

  TH1F* m_hi_coll_450 = new TH1F("m_hi_coll_450", "high mass, coll 450", 40,minMass,maxMass);
  TH1F* m_hi_coll_475 = new TH1F("m_hi_coll_475", "high mass, coll 475", 40,minMass,maxMass);

  TH1F* m_hi_coll_500 = new TH1F("m_hi_coll_500", "high mass, coll 500", 40,minMass,maxMass);
  TH1F* m_hi_coll_525 = new TH1F("m_hi_coll_525", "high mass, coll 525", 40,minMass,maxMass);
  TH1F* m_hi_coll_550 = new TH1F("m_hi_coll_550", "high mass, coll 550", 40,minMass,maxMass);
  TH1F* m_hi_coll_575 = new TH1F("m_hi_coll_575", "high mass, coll 575", 40,minMass,maxMass);

  TH1F* m_hi_coll_600 = new TH1F("m_hi_coll_600", "high mass, coll 600", 40,minMass,maxMass);
  TH1F* m_hi_coll_625 = new TH1F("m_hi_coll_625", "high mass, coll 625", 40,minMass,maxMass);

  TH1F* m_hi_coll_650 = new TH1F("m_hi_coll_650", "high mass, coll 650", 40,minMass,maxMass);
  TH1F* m_hi_coll_675 = new TH1F("m_hi_coll_675", "high mass, coll 675", 40,minMass,maxMass);

  TH1F* m_hi_coll_700 = new TH1F("m_hi_coll_700", "high mass, coll 700", 40,minMass,maxMass);
  TH1F* m_hi_coll_725 = new TH1F("m_hi_coll_725", "high mass, coll 725", 40,minMass,maxMass);
  TH1F* m_hi_coll_750 = new TH1F("m_hi_coll_750", "high mass, coll 750", 40,minMass,maxMass);
  TH1F* m_hi_coll_775 = new TH1F("m_hi_coll_775", "high mass, coll 775", 40,minMass,maxMass);

  TH1F* m_hi_coll_800 = new TH1F("m_hi_coll_800", "high mass, coll 800", 40,minMass,maxMass);
  TH1F* m_hi_coll_825 = new TH1F("m_hi_coll_825", "high mass, coll 825", 40,minMass,maxMass);
  TH1F* m_hi_coll_850 = new TH1F("m_hi_coll_850", "high mass, coll 850", 40,minMass,maxMass);
  TH1F* m_hi_coll_875 = new TH1F("m_hi_coll_875", "high mass, coll 875", 40,minMass,maxMass);

  TH1F* m_hi_coll_900 = new TH1F("m_hi_coll_900", "high mass, coll 900", 40,minMass,maxMass);
  TH1F* m_hi_coll_925 = new TH1F("m_hi_coll_925", "high mass, coll 925", 40,minMass,maxMass);
  TH1F* m_hi_coll_950 = new TH1F("m_hi_coll_950", "high mass, coll 950", 40,minMass,maxMass);

  // dl_sig varied histograms, high mass

  TH1F* m_hi_dlsig_3_0 = new TH1F("m_hi_dlsig_3_0", "high mass, dlsig 3_0", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_3_2 = new TH1F("m_hi_dlsig_3_2", "high mass, dlsig 3_2", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_3_4 = new TH1F("m_hi_dlsig_3_4", "high mass, dlsig 3_4", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_3_6 = new TH1F("m_hi_dlsig_3_6", "high mass, dlsig 3_6", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_3_8 = new TH1F("m_hi_dlsig_3_8", "high mass, dlsig 3_8", 40,minMass,maxMass);

  TH1F* m_hi_dlsig_4_0 = new TH1F("m_hi_dlsig_4_0", "high mass, dlsig 4_0", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_4_2 = new TH1F("m_hi_dlsig_4_2", "high mass, dlsig 4_2", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_4_4 = new TH1F("m_hi_dlsig_4_4", "high mass, dlsig 4_4", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_4_6 = new TH1F("m_hi_dlsig_4_6", "high mass, dlsig 4_6", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_4_8 = new TH1F("m_hi_dlsig_4_8", "high mass, dlsig 4_8", 40,minMass,maxMass);

  TH1F* m_hi_dlsig_5_0 = new TH1F("m_hi_dlsig_5_0", "high mass, dlsig 5_0", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_5_2 = new TH1F("m_hi_dlsig_5_2", "high mass, dlsig 5_2", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_5_4 = new TH1F("m_hi_dlsig_5_4", "high mass, dlsig 5_4", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_5_6 = new TH1F("m_hi_dlsig_5_6", "high mass, dlsig 5_6", 40,minMass,maxMass);
  TH1F* m_hi_dlsig_5_8 = new TH1F("m_hi_dlsig_5_8", "high mass, dlsig 5_8", 40,minMass,maxMass);

  TH1F* m_hi_dlsig_6_0 = new TH1F("m_hi_dlsig_6_0", "high mass, dlsig 6_0", 40,minMass,maxMass);

  // Ksmt varied histograms, high mass

  TH1F* m_hi_Ksmt0 = new TH1F("m_hi_Ksmt0", "high mass, Ksmt 0", 40,minMass,maxMass);
  TH1F* m_hi_Ksmt1 = new TH1F("m_hi_Ksmt1", "high mass, Ksmt 1", 40,minMass,maxMass);
  TH1F* m_hi_Ksmt2 = new TH1F("m_hi_Ksmt2", "high mass, Ksmt 2", 40,minMass,maxMass);
  TH1F* m_hi_Ksmt3 = new TH1F("m_hi_Ksmt3", "high mass, Ksmt 3", 40,minMass,maxMass);
 
  // Kpt varied histograms, high mass

  TH1F* m_hi_Kpt_0_5 = new TH1F("m_hi_Kpt_0_5", "high mass, Kpt 0_5", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_0_6 = new TH1F("m_hi_Kpt_0_6", "high mass, Kpt 0_6", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_0_7 = new TH1F("m_hi_Kpt_0_7", "high mass, Kpt 0_7", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_0_8 = new TH1F("m_hi_Kpt_0_8", "high mass, Kpt 0_8", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_0_9 = new TH1F("m_hi_Kpt_0_9", "high mass, Kpt 0_9", 40,minMass,maxMass);

  TH1F* m_hi_Kpt_1_0 = new TH1F("m_hi_Kpt_1_0", "high mass, Kpt 1_0", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_1_1 = new TH1F("m_hi_Kpt_1_1", "high mass, Kpt 1_1", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_1_2 = new TH1F("m_hi_Kpt_1_2", "high mass, Kpt 1_2", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_1_3 = new TH1F("m_hi_Kpt_1_3", "high mass, Kpt 1_3", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_1_4 = new TH1F("m_hi_Kpt_1_4", "high mass, Kpt 1_4", 40,minMass,maxMass);
  TH1F* m_hi_Kpt_1_5 = new TH1F("m_hi_Kpt_1_5", "high mass, Kpt 1_5", 40,minMass,maxMass);

  // Kpt Histograms
  TH1F* kpt_nc = new TH1F("kpt_nc", "Kpt, no cuts",50,0.0,2.0);

  TH1F* kpt_lo = new TH1F("kpt_lo", "0.5<Kpt<1.0",50,0.5,1.0);
  TH1F* kpt_hi = new TH1F("kpt_hi", "Kpt>1.0",50,1.0,1.5);

  TH1F* dl_sig_lo = new TH1F("dl_sig_lo", "dl_sig for 0.5<Kpt<1.0", 50,3.0,6.0);
  TH1F* dl_sig_hi = new TH1F("dl_sig_hi", "dl_sig for Kpt>1.0", 50,3.0,6.0);

  TH1F* coll_lo = new TH1F("coll_lo", "coll for 0.5<Kpt<1.0", 50,0.08,0.95);
  TH1F* coll_hi = new TH1F("coll_hi", "coll for Kpt>1.0", 50,0.08,0.95);

  TH1F* ksmt_lo = new TH1F("ksmt_lo", "ksmt for 0.5<Kpt<1.0", 50,0.0,3.0);
  TH1F* ksmt_hi = new TH1F("ksmt_hi", "ksmt for Kpt>1.0", 50,0.0,3.0);
  
  // Muon Eta Histograms
  TH1F* mu1eta = new TH1F("mu1eta", "Muon 1 Eta", 100,-4.0,4.0);
  TH1F* mu2eta = new TH1F("mu2eta", "Muon 2 Eta", 100,-4.0,4.0);
  TH1F* mu1pt = new TH1F("mu1pt", "Muon 1 pt", 100,0.0,20.0);
  TH1F* mu2pt = new TH1F("mu2pt", "Muon 2 pt", 100,0.0,20.0);

  TH1F* mu3eta = new TH1F("mu3eta", "Muon 1 Eta", 100,-4.0,4.0);
  TH1F* mu4eta = new TH1F("mu4eta", "Muon 2 Eta", 100,-4.0,4.0);
  TH1F* mu3pt = new TH1F("mu3pt", "Muon 1 pt", 100,0.0,20.0);
  TH1F* mu4pt = new TH1F("mu4pt", "Muon 2 pt", 100,0.0,20.0);

  if (fChain == 0) return;
   
  int aa = 1000; int nn = 0;

  Int_t nentries = Int_t(fChain->GetEntries());
  cout <<"Number of entries  " << nentries   << endl;

  Int_t nbytes = 0, nb = 0;


  //   for (Int_t jentry=0; jentry<30000;jentry++) {
   for (Int_t jentry=0; jentry<nentries;jentry++) {

    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    	if(jentry/aa>nn) cout << "Event #" << jentry << endl;
      	nn = jentry/aa;

    Int_t iFound = 0;

    if(PV_npv<1 || PV_ntrk[0]<2) continue;

    // Fill histograms with vertex info


    //------------muon pt stuff------------

    for(int kent1=0; kent1<PSI_nvtx; kent1++){
      // int psiid = PSI_id[kent1];

           if( (PSI_q1[kent1]+PSI_q2[kent1])==0 && PSI_chi2[kent1]<10.0
        &&
	  PSI_pt1[kent1]>=1.5 && PSI_pt2[kent1]>=1.5 && 
        PSI_smt1[kent1]>=1 && PSI_smt2[kent1]>=1 &&
        PSI_mass[kent1]>2.8 && PSI_mass[kent1]<3.3 
	  && PSI_pt[kent1]>3.) {
           
	float eta1 = PSI_eta1[kent1];
	float eta2 = PSI_eta2[kent1];

	float ppt1 = PSI_pt1[kent1];
	float ppt2 = PSI_pt2[kent1];

	mu1eta->Fill(eta1);
	mu2eta->Fill(eta2);

	mu1pt->Fill(ppt1);
	mu2pt->Fill(ppt2);

	    }
    }
    for(int kent2=0; kent2<PSI_nvtx; kent2++){
      int psiid = PSI_id[kent2];

          if( (PSI_q1[psiid]+PSI_q2[psiid])==0 && PSI_chi2[psiid]<10.0
          &&
	  PSI_pt1[psiid]>=1.5 && PSI_pt2[psiid]>=1.5 && 
        PSI_smt1[psiid]>=1 && PSI_smt2[psiid]>=1 &&
        PSI_mass[psiid]>2.8 && PSI_mass[psiid]<3.3 
	      && PSI_pt[psiid]>3.) {
           
	float eta3 = PSI_eta1[psiid];
	float eta4 = PSI_eta2[psiid];

	float ppt3 = PSI_pt1[psiid];
	float ppt4 = PSI_pt2[psiid];

	mu3eta->Fill(eta3);
	mu4eta->Fill(eta4);

	mu3pt->Fill(ppt3);
	mu4pt->Fill(ppt4);
	    }
    }


    for(int j=0; j<BPSIK_nvtx; j++) {
      
      int jpsi_id = BPSIK_id[j];

      //require JPSI

      if( (PSI_q1[jpsi_id]+PSI_q2[jpsi_id])==0 && PSI_chi2[jpsi_id]<10.0
	  &&
	  PSI_pt1[jpsi_id]>=1.5 && PSI_pt2[jpsi_id]>=1.5 && 
	  PSI_smt1[jpsi_id]>=1 && PSI_smt2[jpsi_id]>=1 &&
	  PSI_mass[jpsi_id]>2.8 && PSI_mass[jpsi_id]<3.3 &&
	  PSI_pt[jpsi_id]>3.) {
	
	float mass = BPSIK_mass[j];
	float massc1 = BPSIK_massc1[j];
	float massc2 = BPSIK_massc2[j];
	float chi2 = BPSIK_chi2[j];
	float dl   = BPSIK_dl[j];
	float coll = BPSIK_collinearity[j];
	float dl_sig = dl/BPSIK_dlError[j];

	float Kch2 = BPSIK_kchi2vtx[j];
	float Kpt = BPSIK_kpt[j];
	int Ksmt  = BPSIK_khits[j];
	
	int flag =0;

	// FILL THE KPT HISTOGRAMS ---------------------------------

	if(Kch2<=10 && chi2<10){
	  kpt_nc->Fill(Kpt);
	}
	
	if(Kch2<=10 && chi2<10 && dl_sig>=4.5 && Ksmt>1 && coll>0.95){
	  kpt_lo->Fill(Kpt);
	  kpt_hi->Fill(Kpt);
	}

	if(Kch2<=10 && chi2<10 && BPSIK_kchisq[j]>0.00001 && Kpt>=0.5 && Kpt<=1.0){
	  dl_sig_lo->Fill(dl_sig);
	  ksmt_lo->Fill(Ksmt);
	  coll_lo->Fill(coll);

	}
	if(Kch2<=10 && chi2<10 && Kpt>=1.0){
	  dl_sig_hi->Fill(dl_sig);
	  ksmt_hi->Fill(Ksmt);
	  coll_hi->Fill(coll);

	}

	// ----- 0.5 -> 1. GeV pt cuts --------------------------------
      
	//      	if(Kch2<=10 && chi2<10 && dl_sig>5.5 && coll>0.95 && Ksmt>=1 &&
	// Kpt>0.5 && Kpt < 1.0 && BPSIK_kchisq[j]>0.00001){
	//      h_mass_2->Fill(massc1);
	// flag = 2;
      	//}

	// Keep kch2, chi2, dl_sig, Ksmt, Kpt constant, vary coll:

      	if(Kch2<=10 && chi2<10 && dl_sig>5.5 && Ksmt>=1 &&
          Kpt>0.5 && BPSIK_kchisq[j]>0.00001 && coll>=0.08){

	     m_lo_coll_080->Fill(massc1);

	     if (coll>=0.100){
	       m_lo_coll_100->Fill(massc1);
	       if (coll>=0.125){
		 m_lo_coll_125->Fill(massc1);
		 if (coll>=0.150){
		   m_lo_coll_150->Fill(massc1);
		   if (coll>=0.175){
		     m_lo_coll_175->Fill(massc1);

		     if (coll>=0.200){
		       m_lo_coll_200->Fill(massc1);
		       if (coll>=0.225){
			 m_lo_coll_225->Fill(massc1);
			 if (coll>=0.250){
			   m_lo_coll_250->Fill(massc1);
			   if (coll>=0.275){
			     m_lo_coll_275->Fill(massc1);

			     if (coll>=0.300){
			       m_lo_coll_300->Fill(massc1);
			       if (coll>=0.325){
				 m_lo_coll_325->Fill(massc1);
				 if (coll>=0.350){
				   m_lo_coll_350->Fill(massc1);
				   if (coll>=0.375){
				     m_lo_coll_375->Fill(massc1);

				     if (coll>=0.400){
				       m_lo_coll_400->Fill(massc1);
				       if (coll>=0.425){
					 m_lo_coll_425->Fill(massc1);
					 if (coll>=0.450){
					   m_lo_coll_450->Fill(massc1);
					   if (coll>=0.475){
					     m_lo_coll_475->Fill(massc1);

					     if (coll>=0.500){
					       m_lo_coll_500->Fill(massc1);
					       if (coll>=0.525){
						 m_lo_coll_525->Fill(massc1);
						 if (coll>=0.550){
						   m_lo_coll_550->Fill(massc1);
						   if (coll>=0.575){
						     m_lo_coll_575->Fill(massc1);
	     
						     if (coll>=0.600){
						       m_lo_coll_600->Fill(massc1);
						       if (coll>=0.625){
							 m_lo_coll_625->Fill(massc1);
							 if (coll>=0.650){
							   m_lo_coll_650->Fill(massc1);
							   if (coll>=0.675){
							     m_lo_coll_675->Fill(massc1);
	     
							     if (coll>=0.700){
							       m_lo_coll_700->Fill(massc1);
							       if (coll>=0.725){
								 m_lo_coll_725->Fill(massc1);
								 if (coll>=0.750){
								   m_lo_coll_750->Fill(massc1);
								   if (coll>=0.775){
								     m_lo_coll_775->Fill(massc1);

								     if (coll>=0.800){
								       m_lo_coll_800->Fill(massc1);
								       if (coll>=0.825){
									 m_lo_coll_825->Fill(massc1);
									 if (coll>=0.850){
									   m_lo_coll_850->Fill(massc1);
									   if (coll>=0.875){
									     m_lo_coll_875->Fill(massc1);

									     if (coll>=0.900){
									       m_lo_coll_900->Fill(massc1);
									       if (coll>=0.925){
										 m_lo_coll_925->Fill(massc1);
										 if (coll>=0.950){
										   m_lo_coll_950->Fill(massc1);
										 }
									       }
									     }
									   } 
									 }
								       }
								     }
								   }
								 }
							       }
							     }
							   }
							 }
						       }
						     }
						   }
						 }
					       }
					     }
					   }
					 }
				       }
				     }
				   }
				 }
			       }
			     }
			   }
			 }
		       }
		     }
		   }
		 }
	       }
	     }
	}

	// Keep kch2, chi2, dl_sig, Ksmt, coll constant, vary Kpt:

      	if(Kch2<=10 && chi2<10 && dl_sig>5.5 && coll>0.95 && Ksmt>=1 &&
	   BPSIK_kchisq[j]>0.00001 && Kpt>=0.5){

	      m_lo_Kpt_0_5->Fill(massc1);
	      if (Kpt>=0.6){
		m_lo_Kpt_0_6->Fill(massc1);
		if (Kpt>=0.7){
		  m_lo_Kpt_0_7->Fill(massc1);
		  if (Kpt>=0.8){
		    m_lo_Kpt_0_8->Fill(massc1);
		    if (Kpt>=0.9){
		      m_lo_Kpt_0_9->Fill(massc1);

		      if (Kpt>=1.0){
			m_lo_Kpt_1_0->Fill(massc1);
			if (Kpt>=1.1){
			  m_lo_Kpt_1_1->Fill(massc1);
			  if (Kpt>=1.2){
			    m_lo_Kpt_1_2->Fill(massc1);
			    if (Kpt>=1.3){
			      m_lo_Kpt_1_3->Fill(massc1);
			      if (Kpt>=1.4){
				m_lo_Kpt_1_4->Fill(massc1);
				if (Kpt>=1.5){
				  m_lo_Kpt_1_5->Fill(massc1);
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	      	

	}

	// Keep kch2, chi2, dl_sig, Kpt, coll constant, vary Ksmt:
      	if(Kch2<=10 && chi2<10 && dl_sig>5.5 && coll>0.95 &&
          Kpt>0.5 && BPSIK_kchisq[j]>0.00001 && Ksmt>=0){ 
  
	       m_lo_Ksmt0->Fill(massc1);
	       if (Ksmt>=1){
		 m_lo_Ksmt1->Fill(massc1);
		 if (Ksmt>=2){
		   m_lo_Ksmt2->Fill(massc1);
		   if (Ksmt>=3){
		     m_lo_Ksmt3->Fill(massc1);
		   }
		 }
	       }
	}

	// Keep kch2, chi2, Ksmt, Kpt, coll constant, vary dl_sig:
      	if(Kch2<=10 && chi2<10 && coll>0.95 && Ksmt>=1 &&
          Kpt>0.5  && BPSIK_kchisq[j]>0.00001 && dl_sig>=3.0){ 
 
	  m_lo_dlsig_3_0->Fill(massc1);
 	  if (dl_sig>=3.2){
	    m_lo_dlsig_3_2->Fill(massc1);
 	    if (dl_sig>=3.4){
	      m_lo_dlsig_3_4->Fill(massc1);
	      if (dl_sig>=3.6){
		m_lo_dlsig_3_6->Fill(massc1);
		if (dl_sig>=3.8){
		  m_lo_dlsig_3_8->Fill(massc1);

		  if (dl_sig>=4.0){
		    m_lo_dlsig_4_0->Fill(massc1);
		    if (dl_sig>=4.2){
		      m_lo_dlsig_4_2->Fill(massc1);
		      if (dl_sig>=4.4){
			m_lo_dlsig_4_4->Fill(massc1);
			if (dl_sig>=4.6){
			  m_lo_dlsig_4_6->Fill(massc1);
			  if (dl_sig>=4.8){
			    m_lo_dlsig_4_8->Fill(massc1);

			    if (dl_sig>=5.0){
			      m_lo_dlsig_5_0->Fill(massc1);
			      if (dl_sig>=5.2){
				m_lo_dlsig_5_2->Fill(massc1);
				if (dl_sig>=5.4){
				  m_lo_dlsig_5_4->Fill(massc1);
				  if (dl_sig>=5.6){
				    m_lo_dlsig_5_6->Fill(massc1);
				    if (dl_sig>=5.8){
				      m_lo_dlsig_5_8->Fill(massc1);

				      if (dl_sig>=6.0){
					m_lo_dlsig_6_0->Fill(massc1);
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }

	}

	// ------- 1 GeV pt cuts -----------------------------------------


	// Keep kch2, chi2, dl_sig, Ksmt, Kpt constant, vary coll:

    	if(Kch2<=10 && chi2<20 && dl_sig>4.5 && Ksmt>=0 && Kpt>1.0 && coll>=0.08){

	     m_hi_coll_080->Fill(massc1);

	     if (coll>=0.100){
	       m_hi_coll_100->Fill(massc1);
	       if (coll>=0.125){
		 m_hi_coll_125->Fill(massc1);
		 if (coll>=0.150){
		   m_hi_coll_150->Fill(massc1);
		   if (coll>=0.175){
		     m_hi_coll_175->Fill(massc1);

		     if (coll>=0.200){
		       m_hi_coll_200->Fill(massc1);
		       if (coll>=0.225){
			 m_hi_coll_225->Fill(massc1);
			 if (coll>=0.250){
			   m_hi_coll_250->Fill(massc1);
			   if (coll>=0.275){
			     m_hi_coll_275->Fill(massc1);

			     if (coll>=0.300){
			       m_hi_coll_300->Fill(massc1);
			       if (coll>=0.325){
				 m_hi_coll_325->Fill(massc1);
				 if (coll>=0.350){
				   m_hi_coll_350->Fill(massc1);
				   if (coll>=0.375){
				     m_hi_coll_375->Fill(massc1);

				     if (coll>=0.400){
				       m_hi_coll_400->Fill(massc1);
				       if (coll>=0.425){
					 m_hi_coll_425->Fill(massc1);
					 if (coll>=0.450){
					   m_hi_coll_450->Fill(massc1);
					   if (coll>=0.475){
					     m_hi_coll_475->Fill(massc1);

					     if (coll>=0.500){
					       m_hi_coll_500->Fill(massc1);
					       if (coll>=0.525){
						 m_hi_coll_525->Fill(massc1);
						 if (coll>=0.550){
						   m_hi_coll_550->Fill(massc1);
						   if (coll>=0.575){
						     m_hi_coll_575->Fill(massc1);
	     
						     if (coll>=0.600){
						       m_hi_coll_600->Fill(massc1);
						       if (coll>=0.625){
							 m_hi_coll_625->Fill(massc1);
							 if (coll>=0.650){
							   m_hi_coll_650->Fill(massc1);
							   if (coll>=0.675){
							     m_hi_coll_675->Fill(massc1);
	     
							     if (coll>=0.700){
							       m_hi_coll_700->Fill(massc1);
							       if (coll>=0.725){
								 m_hi_coll_725->Fill(massc1);
								 if (coll>=0.750){
								   m_hi_coll_750->Fill(massc1);
								   if (coll>=0.775){
								     m_hi_coll_775->Fill(massc1);

								     if (coll>=0.800){
								       m_hi_coll_800->Fill(massc1);
								       if (coll>=0.825){
									 m_hi_coll_825->Fill(massc1);
									 if (coll>=0.850){
									   m_hi_coll_850->Fill(massc1);
									   if (coll>=0.875){
									     m_hi_coll_875->Fill(massc1);

									     if (coll>=0.900){
									       m_hi_coll_900->Fill(massc1);
									       if (coll>=0.925){
										 m_hi_coll_925->Fill(massc1);
										 if (coll>=0.950){
										   m_hi_coll_950->Fill(massc1);
										 }
									       }
									     }
									   } 
									 }
								       }
								     }
								   }
								 }
							       }
							     }
							   }
							 }
						       }
						     }
						   }
						 }
					       }
					     }
					   }
					 }
				       }
				     }
				   }
				 }
			       }
			     }
			   }
			 }
		       }
		     }
		   }
		 }
	       }
	     }
     	   
	}

	// Keep kch2, chi2, dl_sig, Ksmt, coll constant, vary Kpt:

      	if(Kch2<=10 && chi2<20 && dl_sig>4.5 && Ksmt>=0 && coll>0.95 && Kpt>=0.5){

	      m_hi_Kpt_0_5->Fill(massc1);
	      if (Kpt>=0.6){
		m_hi_Kpt_0_6->Fill(massc1);
		if (Kpt>=0.7){
		  m_hi_Kpt_0_7->Fill(massc1);
		  if (Kpt>=0.8){
		    m_hi_Kpt_0_8->Fill(massc1);
		    if (Kpt>=0.9){
		      m_hi_Kpt_0_9->Fill(massc1);

		      if (Kpt>=1.0){
			m_hi_Kpt_1_0->Fill(massc1);
			if (Kpt>=1.1){
			  m_hi_Kpt_1_1->Fill(massc1);
			  if (Kpt>=1.2){
			    m_hi_Kpt_1_2->Fill(massc1);
			    if (Kpt>=1.3){
			      m_hi_Kpt_1_3->Fill(massc1);
			      if (Kpt>=1.4){
				m_hi_Kpt_1_4->Fill(massc1);
				if (Kpt>=1.5){
				  m_hi_Kpt_1_5->Fill(massc1);
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }

	}

	// Keep kch2, chi2, dl_sig, Kpt, coll constant, vary Ksmt:

      	if(Kch2<=10 && chi2<20 && dl_sig>4.5 && Kpt>1.0 && coll>0.95 && Ksmt>=0){
	
	     m_hi_Ksmt0->Fill(massc1);
	     if (Ksmt>=1){
	       m_hi_Ksmt1->Fill(massc1);
	       if (Ksmt>=2){
		 m_hi_Ksmt2->Fill(massc1);
		 if (Ksmt>=3){m_hi_Ksmt3->Fill(massc1);}
	       }
	     }

	}
	// Keep kch2, chi2, Ksmt, Kpt, coll constant, vary dl_sig:
      	if(Kch2<=10 && chi2<20 && Ksmt>=0  && Kpt>1.0 && coll>0.95 && dl_sig>=3.0){

	  m_hi_dlsig_3_0->Fill(massc1);
 	  if (dl_sig>=3.2){
	    m_hi_dlsig_3_2->Fill(massc1);
 	    if (dl_sig>=3.4){
	      m_hi_dlsig_3_4->Fill(massc1);
	      if (dl_sig>=3.6){
		m_hi_dlsig_3_6->Fill(massc1);
		if (dl_sig>=3.8){
		  m_hi_dlsig_3_8->Fill(massc1);

		  if (dl_sig>=4.0){
		    m_hi_dlsig_4_0->Fill(massc1);
		    if (dl_sig>=4.2){
		      m_hi_dlsig_4_2->Fill(massc1);
		      if (dl_sig>=4.4){
			m_hi_dlsig_4_4->Fill(massc1);
			if (dl_sig>=4.6){
			  m_hi_dlsig_4_6->Fill(massc1);
			  if (dl_sig>=4.8){
			    m_hi_dlsig_4_8->Fill(massc1);

			    if (dl_sig>=5.0){
			      m_hi_dlsig_5_0->Fill(massc1);
			      if (dl_sig>=5.2){
				m_hi_dlsig_5_2->Fill(massc1);
				if (dl_sig>=5.4){
				  m_hi_dlsig_5_4->Fill(massc1);
				  if (dl_sig>=5.6){
				    m_hi_dlsig_5_6->Fill(massc1);
				    if (dl_sig>=5.8){
				      m_hi_dlsig_5_8->Fill(massc1);

				      if (dl_sig>=6.0){
					m_hi_dlsig_6_0->Fill(massc1);
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }

	}



    }
  }
}

  plotz.Write();
  cout << "COMPLETE!"; 

}
