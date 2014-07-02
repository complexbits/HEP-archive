//************************************************
// Use minuit to do an unbinned fit
//
// by P. Gutierrez
// 3-12-04
//************************************************

#include "params.hpp"

void unbinFitg()
{
  TMinuit *gMinuit = new TMinuit(2);
  gMinuit -> SetFCN(mll_fitg);
  
  Double_t arglist[10];
  Double_t vstart[10];
  Double_t step[10];

  Double_t p0=0, p1=1, p2=2, p3=3;
  Int_t ierflg=0;
 
  // Set to 0.5 for likelihood, 1 for chisquare

  arglist[0] = 0.5;
  gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

  // Set initial values of parameters

  vstart[0] = par0_init;
  vstart[1] = par1_init;

  step[0] = par0_step;
  step[1] = par1_step;

  gMinuit->mnparm(0, "m0", vstart[0], step[0], min, max, ierflg);
  gMinuit->mnparm(1, "width", vstart[1], step[1], 0., 0., ierflg);

  // Do minimization
  arglist[0] = 3000.;
  arglist[1] = 0.1;
  gMinuit->mnexcm("CALL FCN", &p1, 1, ierflg);
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
  gMinuit->mnexcm("CALL FCN", &p3, 1, ierflg);

}

void mll_fitg(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;
  for (Int_t i=0; i<nEvts; i++){
    Double_t ll = nGaus(par[0], par[1], mass[i]);
    Double_t ll = nPoly1(par[0], mass[i]);
    nll -= TMath::Log(ll);
  }
  f = nll;
}