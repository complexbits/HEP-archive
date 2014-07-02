// Initial global parameters
Double_t tau = 1.5;
//Double_t dm  = 10.;
Double_t tSigmat = 0.;

//
// dSmear = 0 Don't use constant resolution
// dSmear = 1 Conatant resolution set by tSigma
// dSmear = 2 Double gauss resolution tSingmaW wide sigma,
//            tSigmaN narrow sigma, fWid fraction using
//            wide sigma

Int_t dSmear = 2;
Double_t tSigma  = 0.18;

Double_t fWid = 0.49;
Double_t tSigmaN = 0.00278;
Double_t tSigmaW = 0.00351;

// Triple gauss
// Double_t f1 = 0.210493;
// Double_t f2 = 0.480845;
// Double_t f3 = 0.308662;
// Double_t tSig1 = 0.0026;
// Double_t tSig2 = 0.0056;
// Double_t tSig3 = 0.0141;

Double_t f1 = 0.3769;
Double_t f2 = 0.4785;
Double_t f3 = 1.-f1-f2;
Double_t tSig1 = 0.002756/.03;
Double_t tSig2 = 0.00545/.03;
Double_t tSig3 = 0.01383/.03;
//*************
Double_t dilution = 1.;
Double_t misTag = 0.5*(1.- dilution);
Int_t nEvt = 10000000;
//Int_t nEvt = 1000000;

//Int_t nBins = 30;
//Double_t maxLimit = 3;
Int_t nBins = 6;
Double_t maxLimit = 2.;

//
// kfactor = 0 (1) don't (do) ues k factor
// VPDL = 0 (1) don't (do) use VPDL resolution associated
// with biased cuts.
//
Int_t kfactor = 1;
Int_t VPDL = 0;
Double_t resScl = 1.;  // Scale resolutions by this

char ScaleFile[50] ="test_mk.root";
