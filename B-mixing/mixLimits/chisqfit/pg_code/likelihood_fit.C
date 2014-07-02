//***********************************************
// Code to do an unbinned likelihood fit
//
// by P. Gutierrez
// 3-12-04
//***********************************************

// Include files

#include "getData.cpp"
//#include "unbinFitosc.cpp"
#include "unbinFitlft.cpp"
#include "func.cpp"

// Define global variables

Double_t min = 4.8;
Double_t max = 5.8;
Int_t nEvts = 50000;
Int_t nBins = 50;


// Define data variables

Double_t runNo[100000];
Double_t evtNo[100000];
Double_t mass[100000];
Double_t lifetime[1000000];
Int_t tag[1000000];


TH1F *h1 = new TH1F("h1","Gaussian Dist",50, 4.8, 5.8);
TH1F *h2 = new TH1F("h2","Lifetime Dist",50, -4., 15.);
TH1F *h3 = new TH1F("h3","Lifetime Dist Mixed",50, -4., 15.);
TH1F *h4 = new TH1F("h4","Lifetime Dist UnMixed",50, -4., 15.);

void likelihood_fit()
{
  TStopwatch timer;

  // Define histogarams

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(111111);

  // Get data

  timer.Start();
  //getDataLft2();
  //getDataCLft();
  //getDataLftDs();
  genDataLft();
  //genDataMs();

  // Do binned fit

  // Do unbinned likelihood fit

  //unbinFitg();
  //unbinFitgp();
  unbinFitlft();
  //unbinFitosc();
  //unbinFitosc_d();

  // stop timer and print results
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  cout << "Real time " << rtime << endl;
  cout << "CPU time  " << ctime << endl;

  // Draw histograms

//   TF1 *f2 = new TF1("f2", lifetime_plt, -4., 15., 2);
//   f2->SetParameter(0,1.);
//   f2->SetParameter(1,1.5);
//   f2->Draw();
  //h1->Draw("same");
}
