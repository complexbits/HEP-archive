#define ariel_aa_cxx
#include "ariel_aa.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>

ofstream myout;

void ariel_aa::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L ariel_aa.C
  //      Root > ariel_aa t
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
  //
  // My variables
  //
  float minMass = 4.75; float maxMass = 6.0;
  float div = 0.04;
  int nBins = (maxMass - minMass)/div;   

  
  //Histogram for invariant Mass studies
  TH1F* h_mass_1 = new TH1F("h_mass_1","#mu^{+} #mu^{-} mass 1",
			    25,minMass,maxMass);

  TH1F* h_mass_2 = new TH1F("h_mass_2","#mu^{+} #mu^{-} mass 5",
			    25,minMass,maxMass);

  TH1F* h_mass_3 = new TH1F("h_mass_3","#mu^{+} #mu^{-} mass all",
			    25,minMass,maxMass);

 
  if (fChain == 0) return;
   
  int aa = 1000; int nn = 0;

  Int_t nentries = Int_t(fChain->GetEntries());
  cout <<"Number of entries  " << nentries   << endl;

  Int_t nbytes = 0, nb = 0;

  Int_t iCountF = 0;
  Int_t flag = 0;

  Float_t dm[10];
  Int_t count_m = 0;

  for (Int_t jentry=0; jentry<nentries;jentry++) {

    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    Int_t iFound = 0;

    if(PV_npv<1 || PV_ntrk[0]<2) continue;

    // Fill histograms with vertex info

    count_m = 0;

    for(int j=0; j<BPSIK_nvtx; j++) {
      
      int jpsi_id = BPSIK_id[j];

      //require JPSI

      if( (PSI_q1[jpsi_id]+PSI_q2[jpsi_id])==0 && PSI_chi2[jpsi_id]<10.0
	  &&
	  PSI_pt1[jpsi_id]>=1.5 && PSI_pt2[jpsi_id]>=1.5 && 
	  PSI_smt1[jpsi_id]>=1 && PSI_smt2[jpsi_id]>=1 &&
	  PSI_mass[jpsi_id]>2.8 && PSI_mass[jpsi_id]<3.3 &&
	  PSI_pt[jpsi_id]>3.) {
	
	float mass = BPSIK_mass[j];
	float massc1 = BPSIK_massc1[j];
	float massc2 = BPSIK_massc2[j];
	float chi2 = BPSIK_chi2[j];
	float dl   = BPSIK_dl[j];
	float coll = BPSIK_collinearity[j];
	float dl_sig = dl/BPSIK_dlError[j];

	float Kch2 = BPSIK_kchi2vtx[j];
	float Kpt = BPSIK_kpt[j];
	int Ksmt  = BPSIK_khits[j];
	
	int flag =0;

	// 1 GeV pt cuts

// 	if(Kch2<=10 && chi2<20 && dl_sig>4.5 && coll>0.95 && Ksmt>=0 &&
//            Kpt>1.0){
// 	  h_mass_1->Fill(massc1);
// 	  flag =2;
// 	   }

	if(Kch2<=10 && chi2<20 && dl_sig>0.03 && coll>0.9 && Ksmt>=3 &&
           Kpt>1.0){
	  h_mass_1->Fill(massc1);
	  flag =2;
	   }

	// 0.5 -> 1. GeV pt cuts

	if(Kch2<=10 && chi2<10 && dl_sig>5.5 && coll>0.95 && Ksmt>=1 &&
           Kpt>0.5 && BPSIK_kchisq[j]>0.00001){
	  h_mass_2->Fill(massc1);
	  flag = 1;
	}
	if (flag == 2){
	  h_mass_3->Fill(massc1);
      }
    }
  }
}
  plots_as = new TFile("plots_aa_rep_v7_mod.root","recreate"); 
  
  h_mass_1->Write();
  h_mass_2->Write();
  h_mass_3->Write();
  
  plots_as.Close();
  
}
