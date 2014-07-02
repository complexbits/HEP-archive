//************************************************
// Use minuit to do an unbinned fit
//
// Fits for lifetime, dm, sigma, dilution
//
// by P. Gutierrez
// 3-12-04
//************************************************

#include "params.hpp"

void unbinFitamp()
{
  TMinuit *gMinuit = new TMinuit(4);
  gMinuit -> SetFCN(mll_fit_d);
  
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

  vstart[0] = oscpar0_init;
  vstart[1] = oscpar1_init;
  vstart[2] = oscpar2_init;
  vstart[3] = oscpar3_init;

  step[0] = oscerr0_step;
  step[1] = oscerr1_step;
  step[2] = oscerr2_step;
  step[3] = oscerr3_step;

  gMinuit->mnparm(0, "t0", vstart[0], step[0], 0., 0., ierflg);
  gMinuit->mnparm(1, "dm", vstart[1], step[1], 0., 0., ierflg);
  gMinuit->mnparm(2, "sigma", vstart[2], step[2], 0., 0., ierflg);
  gMinuit->mnparm(3, "mistag", vstart[3], step[3], 0., 0., ierflg);
  // Fix t0 amd sigma
  arglist[0] = 1;
  arglist[1] = 3;
  arglist[2] = 2;
  gMinuit->mnexcm("FIX", arglist, 3, ierflg);

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

  dmFreq[mainLoop-1] = par1;
  etaFound[mainLoop-1] = par3;
  etaFoundErr[mainLoop-1] = err3;

  // Include fit function in the histogram
  TF1 *f3 = new TF1("f3", lftmosc_plt_d, -4., 15., 5);
  f3->SetParameter(0,par0);
  f3->SetParameter(1,par1);
  f3->SetParameter(2,par2);
  f3->SetParameter(3,par3);
  f3->SetParameter(4,1.);

  TF1 *f4 = new TF1("f4", lftmosc_plt_d, -4., 15., 5);
  f4->SetParameter(0,par0);
  f4->SetParameter(1,par1);
  f4->SetParameter(2,par2);
  f4->SetParameter(3,par3);
  f4->SetParameter(4,-1.);

//  f2->SetParName(0,"par0");
//  f2->SetParName(1,"par1");
//  f1->SetParName(2,"par2");
//  f1->SetParName(3,"par3");

  RooComplex ct = RooMath::ComplexErrFunc(2.,1.);
  cout << "ct  " << ct.re() << "  " << ct.im() << endl;

//   TCanvas* c = new TCanvas("c","c",800,400);
//   c->Divide(2,1);
//   c->cd(1);
//   h3->Draw();
//   f3->Draw("same");
//   c->cd(2);
//   h4->Draw();
//   f4->Draw("same");

  delete gMinuit;

}

void mll_fit(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;

  for (Int_t i=0; i<nEvts; i++){
    
    Double_t ll = lifetime_osc(tag[i], par[0], par[1], par[2], lifetime[i]);
    nll -= TMath::Log(ll);

  }
  f = nll;

}

void mll_fit_d(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;

  for (Int_t i=0; i<nEvts; i++){
    if (tag[i] == -1){
      Double_t ll1 = lifetime_osc(1, par[0], par[1], par[2], lifetime[i]);
      Double_t ll2 = lifetime_osc(-1, par[0], par[1], par[2], lifetime[i]);
      Double_t ll = (1-par[3])*ll1 + par[3]*ll2;
    }

    if (tag[i] == 1){
      Double_t ll1 = lifetime_osc(-1, par[0], par[1], par[2], lifetime[i]);
      Double_t ll2 = lifetime_osc(1, par[0], par[1], par[2], lifetime[i]);
      Double_t ll = (1-par[3])*ll1 + par[3]*ll2;
    }

    nll -= TMath::Log(ll);

  }
  f = nll;

}
