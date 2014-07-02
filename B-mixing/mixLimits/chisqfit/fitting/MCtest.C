#include "unbinFitosc_d.cpp"

#ifndef __FUNC_CPP__
#include "func.cpp"
#endif

#include "mcData.cpp"

//----- Used for testing with mcData.cpp (toy MC):

Double_t tau=1.8667;      // lifetime of B0
Double_t tSigma=0.3749;   // detector time resolution smearing
Double_t nSigma=0.;   // unmeasured neutrinos smearing
Double_t dm=7.;       // mass diff btw B0/B0bar
Double_t misTag=0.1;   // mistagging rate

Double_t bgtau=0.;
Double_t sbrat=10000000;    // signal-background ratio

Double_t rTime[50000];
Double_t nsm[50000];
Double_t lt_sm1[50000];
Double_t tsm[50000];

//----- Define data variables

Double_t runNo[50000];
Double_t evtNo[50000];
Double_t mass[50000];
Double_t lifetime[50000];
Int_t tag[50000];

//----- Define binning and normalization parameters:

Int_t    nBins = 20;
Double_t maxLimit = 2.;

Int_t nEvts = 1000;

Double_t min = -2.;
Double_t max = 11.;
Double_t binWidth=0.1;
Int_t binN = (max-min)/binWidth;

//----- Define arrays and stuff for fitting:

Double_t t0_init = 1.8667; //t0
Double_t dm_init = 7.; //dm
Double_t sigma_init = 0.3749; //sigma
Double_t mistag_init = 0.1; //mistag

Double_t t0_step = 0.1;
Double_t dm_step = 0.01;
Double_t sigma_step = 0.01;
Double_t mistag_step = 0.01;

Double_t fitpar[4];
Double_t fiterr[4];

Double_t fitlpar[2];
Double_t fitlerr[2];

void MCtest()
{

  /***************************************************************
   * Vary dm to see how it affects mistag fit (test with toy MC)
   ***************************************************************/

  // Create a graph to use for the comparison
  
  TGraphErrors *g_amp_test = new TGraphErrors(20);
  g_amp_test->SetName("DilvsDm(MC)");
  g_amp_test->SetTitle("Dilution vs. dm (toy MC)");
  
  TGraph *g_amp_err_test = new TGraph(20);
  g_amp_err_test->SetName("DilErrvsDm(MC)");
  g_amp_err_test->SetTitle("Dilution Error vs. dm (toy MC)");

  TH1F *h_mixed = new TH1F("h_mixed", "Toy MC Mixed Events", nBins, min, max);
  TH1F *h_unmixed = new TH1F("h_unmixed", "Toy MC Unmixed Events", nBins, min, max);  

  mixmasta_mc();
  
  for(Int_t j=0; j<nEvts; j++){
    if (tag[j]==1){
      h_mixed->Fill(lifetime[j]);
    }else if(tag[j]=-1){
      h_unmixed->Fill(lifetime[j]);
    }else{
      break;
    }
  }


  for (Int_t j=0; j<20; j++){

    dm_init = j + 1;

    unbinFitosc_d();

    g_amp_test->SetPoint(j, fitpar[1], -(1-2*fitpar[3])/0.8);
    g_amp_test->SetPointError(j, 0, 1.65*2*fiterr[3]/0.8);

    g_amp_err_test->SetPoint(j, fitpar[1], 1.65*2*fiterr[3]/0.8);
    
  }  

/****************************************************************/
  // Draw histograms
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(11111);
  gStyle->SetHistFillColor(10);
  TCanvas *c1 = new TCanvas("c1", "Canvas1", 800,300);
  c1->Divide(2,1);
  
 
  c1->cd(1);
  gPad->SetGrid();
  g_amp_test->Draw("AP*");
  

  c1->cd(2);
  gPad->SetGrid();
  g_amp_err_test->Draw("AP*"); 

  TObjArray *a1 = new TObjArray(0);

  a1->Add(h_mixed);
  a1->Add(h_unmixed);
  a1->Add(g_amp_test);
  a1->Add(g_amp_err_test);
  a1->Add(c1);

  TFile *f1 = new TFile("MCtest.root", "recreate");
  a1->Write();
  f1->Close();

}
