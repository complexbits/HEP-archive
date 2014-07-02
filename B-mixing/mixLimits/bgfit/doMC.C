//***********************************************
// Code to do an unbinned likelihood fit
//
// by P. Gutierrez
// 3-12-04
//***********************************************

// Include files

#include "mcData.cpp"

//----- Define data variables

Double_t runNo[50000];
Double_t evtNo[50000];
Double_t mass[50000];
Double_t rlftime[50000];
Double_t lifetime[50000];
Int_t tag[50000];

//----- Define global variables

Double_t min = -4.;
Double_t max = 15.;
// set to 4000 for real run
Int_t nEvts = 12000.;
Int_t nBins = 50.;


//----- Define vars for MC event gen
Double_t tau = 1.5;
Double_t dm = 1000; 
Double_t tSigma = 0.1;
Double_t misTag = 0.42;

Double_t nSigma = 0.163;
Double_t bgtau = 0.5*tau;
Double_t sbrat = 0.5;

//----- Define arrays and stuff for fitting:


void doMC()
{

  TStopwatch timer;
  timer.Start();
  // Define histogarams
  

  TH1F *h1 = new TH1F("h1","Lifetime Dist",nBins, min, max);

 
  // Generate events
  
  nSigma = 0.163;

  mixmasta_mc();
  
  for (Int_t ja=0; ja<nEvts; ja++){
    h1->Fill(lifetime[ja]);

  }
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  
  h1->Draw();

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  
  cout << "Real time " << rtime << endl;
  cout << "CPU time  " << ctime << endl;
  
}
