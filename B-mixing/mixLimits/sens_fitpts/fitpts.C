//***********************************************
// Code to do an unbinned likelihood fit
//
// by P. Gutierrez
// 3-12-04
//***********************************************

// Include files

#include "mcData.cpp"
#include "unbinFitosc_pts.cpp"
#include "func.cpp"


//----- Define data variables

Double_t runNo[50000];
Double_t evtNo[50000];
Double_t mass[50000];
Double_t lifetime[50000];
Int_t tag[50000];
Double_t rTime[50000];

//----- Define global variables

Double_t min = -4.;
Double_t max = 15.;
// set to 4000 for real run
Int_t nEvts = 4000.;
Int_t nBins = 50.;


//---- Define dilution for MC and fit:
Double_t dilmc = 0.160;
Double_t dilfit = 0.160;

//----- Define vars for MC event gen:
Double_t tau = 1.5;
Double_t tSigma = 0.10;
Double_t nSigma = 0.163;
Double_t misTag = 0.5*(1-dilmc);
Double_t dm = 1000; 

Double_t bgtau = tau;
Double_t sbrat = 1000000;

//----- Define arrays and stuff for fitting:

Double_t dm_fit=10;
Double_t oscpar0_init = 0.5*(1-dilfit);
Double_t oscerr0_step = 0.1;

Double_t fitpar;
Double_t fiterr;

void fitpts()
{

  TStopwatch timer;
  timer.Start();
  // Define histogarams
  
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(111111);
  
  TGraphErrors *g1 = new TGraphErrors(20);
  g1->SetName("Dilvsdm");
  g1->SetTitle("Dilution vs. dm");
  
  TGraph *g2 = new TGraph(20);
  g2->SetName("DilErrvsdm");
  g2->SetTitle("Dil Err vs. dm");
  
  for(Int_t i=0.;i<20.;i++){


    dm_fit = 10+(0.5*i);

    printf("\n============== dm fixed at %5.1f ====================\n", dm_fit);

    //TH1F *h1 = new TH1F("h1","Gaussian Dist",50, 4.8, 5.8);
    TH1F *h2 = new TH1F("h2","Lifetime Dist",nBins, min, max);
    TH1F *h3 = new TH1F("h3","Lifetime Dist tag=1",nBins, min, max);
    TH1F *h4 = new TH1F("h4","Lifetime Dist tag=-1",nBins, min, max);
    
    // Get data
    
    // Generate events
    
    mixmasta_mc();
    
    for (Int_t ja=0; ja<nEvts; ja++){
      h2->Fill(lifetime[ja]);
      if (tag[ja] == 1){
	h3->Fill(lifetime[ja]);
      }else if(tag[ja] == -1){
	h4->Fill(lifetime[ja]);
      }else{
	printf("Tag value %5.3f out of range, should be -1 or 1\n",tag[ja]);
	break;
      }
    }
    
    // Do unbinned likelihood fit
           
    unbinFitosc_pts();
        
    g1->SetPoint(i,dm_fit,-(1-2*fitpar)/dilfit);
    g1->SetPointError(i,0,2*fiterr/dilfit);
    
    g2->SetPoint(i,dm_fit,1.65*2*fiterr/dilfit);
    
    delete h2;
    delete h3;
    delete h4;

  }
  
  TCanvas *vardm = new TCanvas("fitpts","fitpts",800,400);
  vardm->Divide(2,1);
  
  vardm->cd(1);
  g1->GetXaxis()->SetTitle("dm");
  g1->GetXaxis()->CenterTitle();
  g1->GetYaxis()->SetTitle("Dilution (1-2alpha)");
  g1->GetYaxis()->CenterTitle();
  //g1->SetMarkerStyle(21);
  //g1->SetMarkerSize(1);
  g1->Draw("AP*"); 
  
  
  vardm->cd(2);
  
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  vardm->SetGrid();
  
  g2->GetXaxis()->SetTitle("dm");
  g2->GetXaxis()->CenterTitle();
  g2->GetYaxis()->SetTitle("Dil. Err");
  g2->GetYaxis()->CenterTitle();
  //g2->SetMarkerStyle(21);
  //g2->SetMarkerSize(1);
  g2->Draw("AP*");  
  
  TObjArray a1(0);
  a1.Add(g1);
  a1.Add(g2);
  a1.Add(vardm);
  
  TFile var_dm("fitpts.root", "recreate");
  a1.Write();
  var_dm.Close();
  
  timer.Stop();
  Double_t realtime = timer.RealTime();
  Double_t cputime = timer.CpuTime();
  
  printf("Real time %7f\n", realtime);
  printf("CPU time  %7f\n", cputime);
  
}
