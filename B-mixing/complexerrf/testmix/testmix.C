/*******************************************************
This file tests the Complex_t function cxerf(), as it is
used in the function mixing().

Plan: 
     Plot mixing from -4 < t < 15, with
     t0 = 1.51
     0 < dm < 1000 with s = 0.1, 
     0.01 < s < 0.2 with dm = 0.51
         
********************************************************/

#ifndef "__COMPLEX_MATH__"
#include "complexmath.h"
#endif

#include "mcData.cpp"

// Define some free parameters to use 

Double_t tau = 1.51;
Double_t dm = 0.51; 
Double_t tSigma = 0.3;
Double_t nSigma = 0.;
Double_t unmixed = -1.;
Double_t mixed = 1.;
Double_t sbrat = 1000000000;
Double_t misTag = 0.;

//Define stuff for the MC:

Double_t nEvts = 500000;
Double_t lifetime[500000];
Double_t tag[500000];
Double_t min = -4;
Double_t max = 15;
Double_t nBins = 100;

void testmix(){

  //Generate lots of Bs:
  /*
  mixmasta_mc();

  TH1D *test1_h = new TH1D("test1_h", "test1_h", nBins, min, max);

  for(Int_t i=0.; i<nEvts; i++){
    if(tag[i] == -1){
      test1_h->Fill(lifetime[i]);
    }
  }
  */

  Double_t norm=0.5*nEvts*(max-min)/nBins;

  TF1 *test1 = new TF1("test1", lftmosc_plt, min, max, 4);
  test1->SetParameters(tau, dm, tSigma, unmixed);
  test1->SetTitle("Lifetime Distribution of 500,000 Bs's");

  test1->GetXaxis()->SetTitle("Time (1/GeV)");

 TF1 *test1m = new TF1("test1m", lftmosc_plt, min, max, 4);
  test1m->SetParameters(tau, dm, tSigma, mixed);
  test1m->SetTitle("Lifetime Distribution of 500,000 Bs's");
 
  test1m->GetXaxis()->SetTitle("Time (1/GeV)");


  gROOT->SetStyle("Plain");
  TCanvas *c1 = new TCanvas("c1", "c1", 500,500);
  c1->SetGrid();
  test1->SetLineColor(4);
  test1->Draw();
  test1m->SetLineColor(2);
  test1m->Draw("same");
  //test1_h->Draw("same");

  TCanvas *c2 = new TCanvas("c2", "c2", 500,500);
  c2->SetLogy();
  c2->SetGrid();
  test1->SetLineColor(4);
  test1->Draw();
  //test1_h->Draw("same");
  test1m->SetLineColor(2);
  test1m->Draw("same");

 

}



//----------------------------------------------------------
//func of t only
Double_t lftmosc_plt(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func = 0.5*nEvts*(max-min)/nBins*mixing(t, t0, dm, s, tag);
  
  return func;

}

//------------------------------------------------------------------------
Double_t mixing(Double_t t, Double_t t0, Double_t dm, Double_t s,Int_t tag)
{
  Double_t aa = (t/(TMath::Sqrt(2.)*s)) - (s/(TMath::Sqrt(2.)*t0));  
  Double_t bb = (s*s/(2.*t0*t0)) - t/t0;
  Double_t cc = s*dm/(TMath::Sqrt(2.));

  //--where aa gets large enough to make Exp(aa) outrageous.
  Double_t tcompare = 5.6*TMath::Sqrt(2.)*s - s*s/t0;
  
  if(t >= tcompare){
    Double_t evilterm=TMath::Exp(-(cc*cc))*2*TMath::Cos(2*aa*cc);    
  }else if(t<= -tcompare){    
    Double_t evilterm=0;    
  }else{
    Complex_t wz = cxerf(cc,-aa);
    Double_t wzreneg = re(wz);    
    Double_t evilterm=TMath::Exp(-(aa*aa))*wzreneg;
  }

  Double_t func = 1./(2.*t0)*TMath::Exp(bb)*( 1 + TMath::Erf(aa) - tag*evilterm );

  return func;
}

