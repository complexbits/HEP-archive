//
// Primary switches for the semileptonic mode studies
//
// For k factor switch it on
Int_t bcuts = 0;
Int_t kfactor = 0;
Int_t VPDL = 0;

//
// Turn off double gaussian resolution estimates
// for current detector switch off
//
Int_t dSmear = 1;
Double_t tSigmaN = 0.00278/.03;
Double_t tSigmaW = 0.00351/.03;
Double_t fWid = 0.49;

Double_t f1 = 0.3769;
Double_t f2 = 0.4785;
Double_t f3 = 1.-f1-f2;
Double_t tSig1 = 0.002756/.03;
Double_t tSig2 = 0.00545/.03;
Double_t tSig3 = 0.01383/.03;
//*****************************

// Estimate with Layer 0
// Int_t dSmear = 2; 
// Double_t tSigmaN = 0.0019/.03; 
// Double_t tSigmaW = 0.0026/.03; 
// Double_t fWid = 0.46; 
