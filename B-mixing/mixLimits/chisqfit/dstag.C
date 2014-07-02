/************************************************************
The skeleton for this file (and corresponding header dstag.h)
were generated automatically by ROOT, using: 

TFile *f = new TFile("bs_mixing_MC.root");
dstag->MakeClass("dstag");

Jamie Hegarty 11/30/04
**************************************************************/


#define dstag_cxx
#include "dstag.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

void dstag::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L dstag.C
//      Root > dstag t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
 
  if (fChain == 0) return;
  Int_t nentries = Int_t(fChain->GetEntriesFast());
  Int_t nbytes = 0, nb = 0;
  
  /*********** BEGIN USER-INSERTED CODE ****************/
  
  TH1F *h_unmixed_events = new TH1F("h_unmixed_events", "VPDL, Unmixed Events", 150, 0., 15);
  TH1F *h_mixed_events = new TH1F("h_mixed_events", "VPDL, Mixed Events", 150, 0., 15);
  TH1F *all_events_vpdl = new TH1F("all_events_vpdl", "VPDL, All Events", 150, 0., 15);
  //TH1F *h_tagumok = new TH1F("h_tagumok", "h_tagmuok",2, 0., 2.);

  TH1F *h_lbdiff = new TH1F("h_lbdiff", "VPDL-TrueVPDL, All Events", 40, -2., 2.);
  TH2F *h2_lbdiff = new TH2F("h2_lbdiff", "VPDL-TrueVPDL vs. TrueVPDL, All Events", 40, -2.,2.,40,0., 2.);

  /************* END USER-INSERTED CODE ****************/
    
  for (Int_t jentry=0; jentry<nentries;jentry++) { // Begin Looping over all entries
    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    /*********** BEGIN USER-INSERTED CODE ****************/
 
    // convert the visible proper decay length from cm to ps
    // by dividing out c = 0.03 cm/ps:
    
    Double_t lbps = lb/0.03;
    Double_t lbmcps = lbmc/0.03;
    Double_t lbmctrueps = lbmctrue/0.03;
    
    Double_t lbdiff = lbps - lbmcps;
    
    h_lbdiff->Fill(lbdiff);
    h2_lbdiff->Fill(lbdiff,lbmcps);
    
    
    all_events_vpdl->Fill(lbmctrueps);
    //h_tagumok->Fill(tagmuok);
    
    // check the sign of the muon here vs. opposite muon
    // if they're equal, mixing occurred. otherwise this event is unmixed.
    if (q6 == qmu){
      h_mixed_events->Fill(lbmctrueps);

    }else{
      h_unmixed_events->Fill(lbmctrueps);

    }
    
    
    /************* END USER-INSERTED CODE ****************/
    
  } // End looping over all entries
  /*********** BEGIN USER-INSERTED CODE ****************/ 

  h_asymm = h_unmixed_events->GetAsymmetry(h_mixed_events);
  h_asymm->SetBins(30,0.,3.);
  h_asymm->SetName("h_asymm");
  h_asymm->SetTitle("Asymmetry");


  TGraph *gcos = new TGraph(31);
  
  Double_t asymm[31];
  Double_t x[31];
  ifstream infile;
  infile.open("MMMM");
  for (Int_t i=0.; i<31; i++){
    infile >> x[i] >> asymm[i];
    gcos->SetPoint(i,x[i],asymm[i]);
  }

  // Draw histograms

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(11111);
  gStyle->SetHistFillColor(10);
  TCanvas *c1 = new TCanvas("c1", "Canvas1", 800,600);
  c1->Divide(2,2);
  c1->cd(1);
  h_mixed_events->Draw();
  c1->cd(2);
  h_unmixed_events->Draw();
  c1->cd(3);
  h_asymm->Draw("P*");
  TF1 *f_cos = new TF1("f_cos", "0.1*cos(7*x)",0.,3.);
  //h_unmix1->Fit(f_cos);
  f_cos->Draw("same");
  c1->cd(4);
  all_events_vpdl->Draw();
  
  TCanvas *c2 = new TCanvas("c2", "Canvas2", 800,600);
  c2->Divide(2,2);
  c2->cd(1);
  h_lbdiff->Draw();
  c2->cd(2);
  h2_lbdiff->Draw();  
  c2->cd(3);
  h2_lbdiff->Draw("LEGO2");

  // Save it all in a Root File

  TObjArray *a1 = new TObjArray(0);

  a1->Add(h_unmixed_events);
  a1->Add(h_mixed_events);
  a1->Add(h_asymm);
  a1->Add(all_events_vpdl);
  a1->Add(h_lbdiff);
  a1->Add(h2_lbdiff);
  a1->Add(gcos);
  a1->Add(f_cos);
  a1->Add(c1);
  a1->Add(c2);

  TFile *f1 = new TFile("bs_asymm.root", "recreate");
  a1->Write();
  f1->Close();

  /************* END USER-INSERTED CODE ****************/

}

