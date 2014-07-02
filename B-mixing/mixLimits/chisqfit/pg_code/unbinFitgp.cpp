//************************************************
// Use minuit to do an unbinned fit
//
// by P. Gutierrez
// 3-12-04
//************************************************

#include "params.hpp"

void unbinFitgp()
{
  TMinuit *gMinuit = new TMinuit(3);
  gMinuit -> SetFCN(mll_fitg);
  
  Double_t arglist[10];
  Double_t vstart[10];
  Double_t step[10];

  Double_t p0=0, p1=1, p2=2, p3=3;
  Int_t ierflg=0;
 
  Double_t par0, par1, par2, par3;
  Double_t err0, err1, err2, err3;

  // Set to 0.5 for likelihood, 1 for chisquare

  arglist[0] = 0.5;
  gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

  // Set initial values of parameters

  vstart[0] = par0_init;
  vstart[1] = par1_init;
  vstart[2] = par2_init;
  vstart[3] = par3_init;

  step[0] = err0_step;
  step[1] = err1_step;
  step[2] = err2_step;
  step[3] = err3_step;

  gMinuit->mnparm(0, "m0", vstart[0], step[0], min, max, ierflg);
  gMinuit->mnparm(1, "width", vstart[1], step[1], 0., 0., ierflg);
  gMinuit->mnparm(2, "slope", vstart[2], step[2], 0., 0., ierflg);
  gMinuit->mnparm(3, "frac", vstart[3], step[3], 0., 1., ierflg);

  // Do minimization
  arglist[0] = 3000.;
  arglist[1] = 0.1;
  gMinuit->mnexcm("CALL FCN", &p1, 1, ierflg);
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
  gMinuit->mnexcm("CALL FCN", &p3, 1, ierflg);

  // Get parameters 
  gMinuit->GetParameter(0,par0,err0);
  gMinuit->GetParameter(1,par1,err1);
  gMinuit->GetParameter(2,par2,err2);
  gMinuit->GetParameter(3,par3,err3);

  // Include fit function in the histogram
  TF1 *f1 = new TF1("f1", mass_fit, min, max, 4);
  f1->SetParameter(0,par0);
  f1->SetParameter(1,par1);
  f1->SetParameter(2,par2);
  f1->SetParameter(3,par3);

//   f1->SetParName(0,"par0");
//   f1->SetParName(1,"par1");
//   f1->SetParName(2,"par2");
//   f1->SetParName(3,"par3");

  //h1->Fit("mass_fit","+");
  h1->Draw();
  f1->Draw("same");

  delete gMinuit;

}

void mll_fitg(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;
  for (Int_t i=0; i<nEvts; i++){
    Double_t ll1 = nGaus(par[0], par[1], mass[i]);
    Double_t ll2 = nPoly1(par[2], mass[i]);
    Double_t ll = par[3]*ll1 + (1-par[3])*ll2;
    nll -= TMath::Log(ll);
  }
  f = nll;

}
