//***********************************************
// Code to do an unbinned likelihood fit
//
// by P. Gutierrez
// 3-12-04
//***********************************************

// Include files

#include "mcData.cpp"
//#include "unbinFitosc_pts.cpp"
//#include "func.cpp"


//----- Define data variables

Double_t runNo[50000];
Double_t evtNo[50000];
Double_t mass[50000];
Double_t lifetime[50000];
Int_t tag[50000];
Double_t rTime[50000];


Double_t tsm[50000];
Double_t lt_sm1[50000];
Double_t nsm[50000];
Double_t lt_sm2[50000];


//----- Define global variables

Double_t min = -4.;
Double_t max = 15.;
// set to 4000 for real run
Int_t nEvts = 50000.;
Int_t nBins = 50.;


//---- Define dilution for MC and fit:
Double_t dilmc = 0.160;
Double_t dilfit = 0.160;

//----- Define vars for MC event gen:
Double_t tau = 1.5;
Double_t tSigma = 0.30;
Double_t nSigma = 0.163;
Double_t misTag=0.01;
//Double_t misTag = 0.5*(1-dilmc);
//Double_t dm = 1000; 
Double_t dm=0.5;


Double_t bgtau = tau;
Double_t sbrat = 1000000;

//----- Define arrays and stuff for fitting:

Double_t dm_fit=10;
Double_t oscpar0_init = 0.5*(1-dilfit);
Double_t oscerr0_step = 0.1;

Double_t fitpar;
Double_t fiterr;

void demo()
{

  TStopwatch timer;
  timer.Start();
  // Define histogarams
  
  // gStyle->SetOptFit(1111);
  //gStyle->SetOptStat(111111);
  
  gROOT->SetStyle("Plain");
  




    //TH1F *h1 = new TH1F("h1","Gaussian Dist",50, 4.8, 5.8);
    TH1F *raw = new TH1F("raw","Raw Exponential Decay Dist", 100, -2, 10);
    TH1F *drs = new TH1F("drs","Detector Resolution Smearing", 100, -1, 1);
    TH1F *ltsm1 = new TH1F("ltsm1","Smeared Lifetime", 100, -2, 10);
    TH1F *n_sm = new TH1F("n_sm","Neutrino Smearing", 100, -1, 1);
    TH1F *ltsm2 = new TH1F("ltsm2","Twice Smeared Lifetime", 100, -2, 10);
    TH1F *lt_mix = new TH1F("lt_mix","Lifetime Dist: Mixed", 100, -2, 10);
    TH1F *lt_unmix = new TH1F("lt_unmix","Lifetime Dist: Unmixed", 100, -2, 10);    


    // Get data
    
    // Generate events
    
    mixmasta_mc();
    
    for (Int_t ja=0; ja<nEvts; ja++){

      raw->Fill(rTime[ja]); //raw exponential dist
      drs->Fill(tsm[ja]); //detector rest (plain gaussian)
      ltsm1->Fill(lt_sm1[ja]); //exp smeared with gauss
      n_sm->Fill(nsm[ja]); //gauss with time-dep sigma
      ltsm2->Fill(lifetime[ja]); //lifetime dist, smeared twice, combined
      
      if (tag[ja] == 1){
	lt_mix->Fill(lifetime[ja]); //mixed events
      }else if(tag[ja] == -1){
	lt_unmix->Fill(lifetime[ja]); //unmixed events
      }else{
	printf("Tag value %5.3f out of range, should be -1 or 1\n",tag[ja]);
	break;
      }
    }
    
    //TCanvas *vardm = new TCanvas("demo","demo",800,400);
    //vardm->Divide(2,1);
  
    

    TCanvas *craw = new TCanvas("raw", "raw", 400, 400);
    raw->SetLineColor(1);
    raw->SetLineWidth(2);
    raw->SetLineStyle(1);
    raw->SetXTitle("Lifetime t (ps)");
    raw->SetYTitle("Num. of Events");
    raw->SetStats(0);
    raw->Draw();
    
    TCanvas *cdrs =  new TCanvas("cdrs", "cdrs", 400,400);
    drs->SetLineColor(1);
    drs->SetLineWidth(2);
    drs->SetLineStyle(1);
    drs->SetXTitle("Time Smear (ps)");
    drs->SetYTitle("Num. of Events");
    drs->SetStats(0);
    drs->Draw();
    
    TCanvas *cltsm1 = new TCanvas("cltsm1", "cltsm1", 400,400);
    ltsm1->SetLineColor(2);
    ltsm1->SetLineWidth(2);
    ltsm1->SetLineStyle(1);
    ltsm1->SetXTitle("Lifetime t (ps)");
    ltsm1->SetYTitle("Num. of Events");
    ltsm1->SetStats(0);
    raw->Draw();
    ltsm1->Draw("same");


    TCanvas *cnsm = new TCanvas("cnsm", "cnsm", 400,400);
    n_sm->SetLineColor(1);
    n_sm->SetLineWidth(2);
    n_sm->SetLineStyle(1);
    n_sm->SetXTitle("Neutrino Time-Dep Smear (ps)");
    n_sm->SetYTitle("Num. of Events");
    n_sm->SetStats(0);
    n_sm->Draw();
    
    TCanvas *cltsm2 = new TCanvas("cltsm2", "cltsm2", 400,400);
    ltsm1->Draw();
    ltsm2->Draw("same");

    TCanvas *cltmix = new TCanvas("cltmix", "cltmix", 400,400);
    lt_mix->Draw();
    lt_unmix->Draw("SAME");
  
  TObjArray a1(0);

  //a1.Add(vardm);
  a1.Add(raw);
  a1.Add(drs);
  a1.Add(ltsm1);
  a1.Add(n_sm);
  a1.Add(ltsm2);
  a1.Add(lt_mix);
  a1.Add(lt_unmix);
  
  TFile var_dm("demo.root", "recreate");
  a1.Write();
  var_dm.Close();
  
  timer.Stop();
  Double_t realtime = timer.RealTime();
  Double_t cputime = timer.CpuTime();
  
  printf("Real time %7f\n", realtime);
  printf("CPU time  %7f\n", cputime);


}
