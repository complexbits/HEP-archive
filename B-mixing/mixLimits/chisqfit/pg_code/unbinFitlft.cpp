//************************************************
// Use minuit to do an unbinned fit
//
// by P. Gutierrez
// 3-12-04
//************************************************

#include "params.hpp"

void unbinFitlft()
{
  TMinuit *gMinuit = new TMinuit(2);
  gMinuit -> SetFCN(mll_fit);
  
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

  vstart[0] = ltpar0_init;
  vstart[1] = ltpar1_init;

  step[0] = lterr0_step;
  step[1] = lterr1_step;

  gMinuit->mnparm(0, "t0", vstart[0], step[0], 0., 0., ierflg);
  gMinuit->mnparm(1, "sigma", vstart[1], step[1], 0., 0., ierflg);

  // Fix t0 amd sigma
  arglist[0] = 2;
  gMinuit->mnexcm("FIX", arglist, 1, ierflg);

  // Do minimization
  arglist[0] = 3000.;
  arglist[1] = 0.01;
  gMinuit->mnexcm("CALL FCN", &p1, 1, ierflg);
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
  //gMinuit->mnexcm("", arglist, 2, ierflg);
  gMinuit->mnexcm("CALL FCN", &p3, 1, ierflg);

  // Get parameters 
  gMinuit->GetParameter(0,par0,err0);
  gMinuit->GetParameter(1,par1,err1);

  // Include fit function in the histogram
  TF1 *f2 = new TF1("f2", lifetime_plt, -4., 15., 2);
  f2->SetParameter(0,par0);
  f2->SetParameter(1,par1);

  f2->SetParName(0,"par0");
  f2->SetParName(1,"par1");
//   f1->SetParName(2,"par2");
//   f1->SetParName(3,"par3");

  TCanvas* c = new TCanvas("c","c",800,800);
  c->Divide(2,2);
  c->cd(1);
  h2->Draw();
  f2->Draw("same");
  c->cd(2);
  h3->Draw();
  c->cd(3);
  h4->Draw();

  delete gMinuit;

}

void mll_fit(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;
  for (Int_t i=0; i<nEvts; i++){
    Double_t ll = lifetime_fit(par[0], par[1], lifetime[i]);
    nll -= TMath::Log(ll);
  }
  f = nll;

}
