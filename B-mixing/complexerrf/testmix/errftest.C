/*****************************************
This script computes the mixing function 
using the Roofit Complex Error Function and 
Jamie's ComplexMath Cxerf.

Gets time for computing each (over 20 runs)
and plots the results.
*******************************************/

#ifndef "__COMPLEX_MATH__"
#include "complexmath.h"
#endif

void errftest()
{
  
  gSystem->Load("libRooFitCore.so");
  gSystem->Load("libRooFitModels.so");
  
  // Define some free parameters to use 
  Double_t t = 2;
  Double_t t0 = 1.51;
  Double_t dm = 0.51; 
  Double_t s = 0.5;
  Double_t tag = 1;
  
  //Define the timers
  Double_t timer1R[20]=0;
  Double_t timer1C[20]=0;
  Double_t timer2R[20]=0;
  Double_t timer2C[20]=0;
  Double_t xi[20]=0;
  
  //Declare everything so we don't have to redeclare in loop
  Double_t tcompare,aa,bb,cc,evilterm1,evilterm2,wzreneg1,wzreneg2,func1,func2;
  Complex_t wz1;
  RooComplex wz2;
  
  //loop over t
  for (Int_t ij = 0.; ij<20; ij++){
    
    // do the test!!!
    //complexmath calculation
    TStopwatch *time1 = new TStopwatch();
    time1.Start();
    
    for(Int_t n = 0.; n<50; n++){
      
      t = -4 + 0.36*n;
      
      aa = (t/(TMath::Sqrt(2.)*s)) - (s/(TMath::Sqrt(2.)*t0));  
      bb = (s*s/(2.*t0*t0)) - t/t0;
      cc = s*dm/(TMath::Sqrt(2.));
      
      if(t >= tcompare){
	evilterm1=TMath::Exp(-(cc*cc))*2*TMath::Cos(2*aa*cc);
	evilterm2=TMath::Exp(-(cc*cc))*2*TMath::Cos(2*aa*cc);   
      }else if(t<= -tcompare){    
	evilterm1=0;
	evilterm2=0;    
      }else{
	
	wz1 = cxerf(cc,-aa);
	wzreneg1 = re(wz1);    
	evilterm1=TMath::Exp(-(aa*aa))*wzreneg1;
	func1 = 1./(2.*t0)*TMath::Exp(bb)*( 1 + TMath::Erf(aa) - tag*evilterm1 );
      }
    }
    
    time1.Stop();
    timer1R[ij] = time1.RealTime();
    timer1C[ij] = time1.CpuTime();
    
    //roomath calculation
    TStopwatch *time2 = new TStopwatch();
    time2.Start();
    
    for(Int_t n = 0.; n<50; n++){
      
      t = -4 + 0.36*n;
      
      aa = (t/(TMath::Sqrt(2.)*s)) - (s/(TMath::Sqrt(2.)*t0));  
      bb = (s*s/(2.*t0*t0)) - t/t0;
      cc = s*dm/(TMath::Sqrt(2.));
      
      if(t >= tcompare){
	evilterm1=TMath::Exp(-(cc*cc))*2*TMath::Cos(2*aa*cc);
	evilterm2=TMath::Exp(-(cc*cc))*2*TMath::Cos(2*aa*cc);   
      }else if(t<= -tcompare){    
	evilterm1=0;
	evilterm2=0;    
      }else{
	
	wz2 = RooMath::ComplexErrFunc(cc,-aa);
	wzreneg2 = wz2.re();    
	evilterm2=TMath::Exp(-(aa*aa))*wzreneg2;
	func2 = 1./(2.*t0)*TMath::Exp(bb)*( 1 + TMath::Erf(aa) - tag*evilterm2 );
      }
    }
    time2.Stop();
    timer2R[ij] = time2.RealTime();
    timer2C[ij] = time2.CpuTime();  
    xi[ij]=ij;
  }

  gROOT->SetStyle("Plain");

  TCanvas *realtime = new TCanvas("realtime", "realtime_compare", 500,500);
  realtime->SetGrid();

  TGraph *complextestRT = new TGraph(20,xi,timer1R);
  complextestRT->SetName("complextest-RT");
  complextestRT->SetTitle("Complexmath Test: Real Time");
  complextestRT->SetMarkerStyle(30);
  complextestRT->SetMarkerSize(2);
  complextestRT->Draw("ALP");
  
  TGraph *roofittestRT = new TGraph(20,xi,timer2R);
  roofittestRT->SetName("roofittest-RT");
  roofittestRT->SetMarkerStyle(29);
  roofittestRT->SetMarkerSize(1);
  roofittestRT->SetMarkerColor(4);
  roofittestRT->Draw("LP");
  
  TCanvas *cputime = new TCanvas("cputime", "cputime_compare", 500,500);
  cputime->SetGrid(); 

  TGraph *complextestCT = new TGraph(20,xi,timer1C);
  complextestCT->SetName("complextest-CT");
  complextestCT->SetTitle("Complexmath Test: CPU Time");
  complextestCT->SetMarkerStyle(30);
  complextestCT->SetMarkerSize(2);
  complextestCT->Draw("ALP");
  
  TGraph *roofittestCT = new TGraph(20,xi,timer2C);
  roofittestCT->SetName("roofittest-CT");
  roofittestCT->SetMarkerStyle(29);
  roofittestCT->SetMarkerSize(1);
  roofittestCT->SetMarkerColor(4);
  roofittestCT->Draw("LP");
  
}
