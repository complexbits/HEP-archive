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


// Define some free parameters to use 
Double_t t = 2;
Double_t tau = 1.51;
Double_t dm = 0.51; 
Double_t sig = 0.1;
Double_t tag = 1;

void testmix(){

  gSystem->Load("libRooFitCore.so");
  gSystem->Load("libRooFitModels.so");

  TCanvas *c1 = new TCanvas("c1", "c1", 1000,1200);
  c1->Divide(2,3);

  c1->cd(1);
  //func of 2 vars: t, sigma
  TF2 *test2 = new TF2("test2", lftmosc_plt2, -4, 15, 0.1, 1., 3);
  test2->SetParameters(tau, dm, tag);
  test2->Draw("lego2");

  c1->cd(2);
  //func of 2 vars: t, dm
  TF2 *test3 = new TF2("test3", lftmosc_plt3, -4, 15, 0.51, 1., 3);
  test3->SetParameters(tau, sig, tag);
  test3->Draw("lego2");

  c1->cd(3);
  //func of 2 vars: t, sigma
  TF2 *test4 = new TF2("test4", lftmosc_plt4, -4, 15, 0.1, 1., 3);
  test4->SetParameters(tau, dm, tag);
  test4->Draw("lego2");

  c1->cd(4);
  //func of 2 vars: t, dm
  TF2 *test5 = new TF2("test5", lftmosc_plt5, -4, 15, 0.51, 1., 3);
  test5->SetParameters(tau, sig, tag);
  test5->Draw("lego2");


  c1->cd(5);
  TF2 *test6 = new TF2("test6", func_compare2, -4, 15, 0.1, 1., 3);
  test6->SetParameters(tau, dm, tag);
  test6->Draw("lego2");

  c1->cd(6);
  TF2 *test7 = new TF2("test7", func_compare3, -4, 15, 0.51, 1., 3);
  test7->SetParameters(tau, sig, tag);
  test7->Draw("lego2");

}

//compare functions; var t only
Double_t func_compare(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func1 = mixing(t, t0, dm, s, tag);
  Double_t func2 = mix_old(t, t0, dm, s, tag);
  
  Double_t funcd = func1/func2;

  return funcd;

}

//compare functions; var t, sigma
Double_t func_compare2(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = x[1];
  Int_t    tag = par[2];

  Double_t func1 = mixing(t, t0, dm, s, tag);
  Double_t func2 = mix_old(t, t0, dm, s, tag);
  
  Double_t funcd = func1-func2;

  return funcd;

}

//compare functions; var t, dm
Double_t func_compare3(Double_t *x, Double_t *par)
{

  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = x[1];
  Double_t s   = par[1];
  Int_t    tag = par[2];

  Double_t func1 = mixing(t, t0, dm, s, tag);
  Double_t func2 = mix_old(t, t0, dm, s, tag);
  
  Double_t funcd = func1-func2;

  return funcd;

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

  Double_t func = mixing(t, t0, dm, s, tag);
  
  return func;

}
//func of 2 vars: t, sigma
Double_t lftmosc_plt2(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = x[1];
  Int_t    tag = par[2];

  Double_t func = mixing(t, t0, dm, s, tag);
  
  return func;

}
//func of 2 vars: t, dm
Double_t lftmosc_plt3(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = x[1];
  Double_t s   = par[1];
  Int_t    tag = par[2];

  Double_t func = mixing(t, t0, dm, s, tag);
  
  return func;

}
//func of 2 vars: t, sigma
//calls mixing w/ roocomplex
Double_t lftmosc_plt4(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = x[1];
  Int_t    tag = par[2];

  Double_t func = mix_old(t, t0, dm, s, tag);
  
  return func;

}
//func of 2 vars: t, dm
//calls mixing w/ roocomplex
Double_t lftmosc_plt5(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = x[1];
  Double_t s   = par[1];
  Int_t    tag = par[2];

  Double_t func = mix_old(t, t0, dm, s, tag);
  
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

Double_t mix_old(Double_t t, Double_t t0, Double_t dm, Double_t s,Int_t tag)
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
    RooComplex wz = RooMath::ComplexErrFunc(cc,-aa);
    Double_t wzreneg = wz.re();    
    Double_t evilterm=TMath::Exp(-(aa*aa))*wzreneg;
  }

  Double_t func = 1./(2.*t0)*TMath::Exp(bb)*( 1 + TMath::Erf(aa) - tag*evilterm );

  return func;
}
