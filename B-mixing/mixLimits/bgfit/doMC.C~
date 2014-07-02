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
Int_t nEvts = 4000.;
Int_t nBins = 50.;


//----- Define vars for MC event gen
Double_t tau = 1.5;
Double_t dm = 1000; 
Double_t tSigma = 0.1;
Double_t nSigma;
Double_t misTag = 0.42;

//----- Define arrays and stuff for fitting:


void doMC()
{

  TStopwatch timer;
  timer.Start();
  // Define histogarams
  

  TH1F *h2 = new TH1F("h2","Lifetime Dist",nBins, min, max);
  TH1F *h3 = new TH1F("h3","Lifetime Dist tag=1",nBins, min, max);
  TH1F *h4 = new TH1F("h4","Lifetime Dist tag=-1",nBins, min, max);
  TH2F *h10 = new TH2F("h10", "RealTime vs SmearedTime", nBins, min, max, nBins, min, max);
  
 
  // Generate events
  
  nSigma = 0.;

  mixmasta_mc();
  
  for (Int_t ja=0; ja<nEvts; ja++){
    h2->Fill(lifetime[ja]);
    h10->Fill(rlftime[ja],lifetime[ja]);
    if (tag[ja] == 1){
      h3->Fill(lifetime[ja]);
    }else if(tag[ja] == -1){
      h4->Fill(lifetime[ja]);
    }else{
      cout << "Tag value "<<tag[ja]<< " out of range, should be -1 or 1" << endl;
      break;
    }
  }
  TH1F *h5 = new TH1F("h5","Lifetime Dist",nBins, min, max);
  TH1F *h6 = new TH1F("h6","Lifetime Dist tag=1",nBins, min, max);
  TH1F *h7 = new TH1F("h7","Lifetime Dist tag=-1",nBins, min, max);
  TH2F *h20 = new TH2F("h20", "RealTime vs SmearedTime", nBins, min, max, nBins, min, max);

  
  // Get data
  
  // Generate events
 
  nSigma=0.163;

  mixmasta_mc();
  
  for (Int_t ja=0; ja<nEvts; ja++){
    h5->Fill(lifetime[ja]);
    h20->Fill(rlftime[ja],lifetime[ja]);
    if (tag[ja] == 1){
      h6->Fill(lifetime[ja]);
    }else if(tag[ja] == -1){
      h7->Fill(lifetime[ja]);
    }else{
      cout << "Tag value "<<tag[ja]<< " out of range, should be -1 or 1" << endl;
      break;
    }
  }
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  
  TCanvas *mchists = new TCanvas("mchists", "mchists", 600,600);
  mchists->Divide(2,2);
  mchists->cd(1);
  h2->Draw();
  mchists->cd(2);
  h3->Draw(); 
  mchists->cd(3);
  h4->Draw();
  mchists->cd(4);
  h10->Draw();

  TCanvas *mchists2 = new TCanvas("mchists2", "mchists2", 600,600);
  mchists2->Divide(2,2);
  mchists2->cd(1);
  h5->Draw();
  mchists2->cd(2);
  h6->Draw(); 
  mchists2->cd(3);
  h7->Draw(); 
  mchists2->cd(4);
  h20->Draw();

  TCanvas *mchists3 = new TCanvas("mchists3", "mchists3", 600,600);
  mchists3->Divide(2,2);
 
  TH1F *h8c = h5->Clone();
  mchists3->cd(1);
  h8c->Divide(h2);
  h8c->Draw();

 TH1F *h9c = h6->Clone();
  mchists3->cd(2);
  h9c->Divide(h3);
  h9c->Draw();

 TH1F *h10c = h7->Clone();
  mchists3->cd(3);
  h10c->Divide(h4);
  h10c->Draw();

  TH2F *h20c = h10->Clone();
  mchists3->cd(4);
  h20c->Divide(h10);
  h20c->Draw();

  

  TObjArray a1(0);

  a1.Add(h2);
  a1.Add(h3);
  a1.Add(h4);
  a1.Add(h10);
  a1.Add(h5);
  a1.Add(h6);
  a1.Add(h7);
  a1.Add(h20);

  TFile var_dm("MChists.root", "recreate");
  a1.Write();
  var_dm.Close();
  
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  
  cout << "Real time " << rtime << endl;
  cout << "CPU time  " << ctime << endl;
  
}
