#define ariel_aa_cxx
#include "ariel_aa.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>

ofstream myout;

void ariel_aa::Loop()
{

TFile plotz("cuts-testing.root","recreate");

  // My variables

  float minMass = 4.75; float maxMass = 6.0;
  float div = 0.04;
  int nBins = (maxMass - minMass)/div;   

  float acoll = 0.00;
  float asig = 0.00;
  float apt = 0.00;
  float asmt = 0.00;

  // ------------ HISTOGRAMS FOR MASS < 1 GeV ------------------------------------------  



  // dl_sig varied histograms, low mass

  TH1F* m_1_dlsig_3_0 = new TH1F("m_1_dlsig_3_0", "low mass, dlsig 3_0", 40,minMass,maxMass);
  TH1F* m_1_dlsig_3_2 = new TH1F("m_1_dlsig_3_2", "low mass, dlsig 3_2", 40,minMass,maxMass);
  TH1F* m_1_dlsig_3_4 = new TH1F("m_1_dlsig_3_4", "low mass, dlsig 3_4", 40,minMass,maxMass);
  TH1F* m_1_dlsig_3_6 = new TH1F("m_1_dlsig_3_6", "low mass, dlsig 3_6", 40,minMass,maxMass);
  TH1F* m_1_dlsig_3_8 = new TH1F("m_1_dlsig_3_8", "low mass, dlsig 3_8", 40,minMass,maxMass);

  TH1F* m_1_dlsig_4_0 = new TH1F("m_1_dlsig_4_0", "low mass, dlsig 4_0", 40,minMass,maxMass);
  TH1F* m_1_dlsig_4_2 = new TH1F("m_1_dlsig_4_2", "low mass, dlsig 4_2", 40,minMass,maxMass);
  TH1F* m_1_dlsig_4_4 = new TH1F("m_1_dlsig_4_4", "low mass, dlsig 4_4", 40,minMass,maxMass);
  TH1F* m_1_dlsig_4_6 = new TH1F("m_1_dlsig_4_6", "low mass, dlsig 4_6", 40,minMass,maxMass);
  TH1F* m_1_dlsig_4_8 = new TH1F("m_1_dlsig_4_8", "low mass, dlsig 4_8", 40,minMass,maxMass);

  TH1F* m_1_dlsig_5_0 = new TH1F("m_1_dlsig_5_0", "low mass, dlsig 5_0", 40,minMass,maxMass);
  TH1F* m_1_dlsig_5_2 = new TH1F("m_1_dlsig_5_2", "low mass, dlsig 5_2", 40,minMass,maxMass);
  TH1F* m_1_dlsig_5_4 = new TH1F("m_1_dlsig_5_4", "low mass, dlsig 5_4", 40,minMass,maxMass);
  TH1F* m_1_dlsig_5_6 = new TH1F("m_1_dlsig_5_6", "low mass, dlsig 5_6", 40,minMass,maxMass);
  TH1F* m_1_dlsig_5_8 = new TH1F("m_1_dlsig_5_8", "low mass, dlsig 5_8", 40,minMass,maxMass);

  TH1F* m_1_dlsig_6_0 = new TH1F("m_1_dlsig_6_0", "low mass, dlsig 6_0", 40,minMass,maxMass);

 
  if (fChain == 0) return;
   
  int aa = 5000; int nn = 0;

  Int_t nentries = Int_t(fChain->GetEntries());
  cout <<"Number of entries  " << nentries   << endl;

  Int_t nbytes = 0, nb = 0;

  Int_t iCountF = 0;
  Int_t flag = 0;

  Float_t dm[10];
  Int_t count_m = 0;

  //for (Int_t jentry=0; jentry<10000;jentry++) {
  for (Int_t jentry=0; jentry<nentries;jentry++) {

//  cout << "now at event # "<< jentry << endl;

    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
	if(jentry/aa>nn) cout << "Event #" << jentry << endl;
      	nn = jentry/aa;

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


	// Keep kch2, chi2, Ksmt, Kpt, coll constant, vary dl_sig:
      	if(Kch2<=10 && chi2<20 && Ksmt>=0  && Kpt>1.0 && coll>0.95){

 	    if (dl_sig>=3.0){m_1_dlsig_3_0->Fill(massc1);}
 	    if (dl_sig>=3.2){m_1_dlsig_3_2->Fill(massc1);}
 	    if (dl_sig>=3.4){m_1_dlsig_3_4->Fill(massc1);}
 	    if (dl_sig>=3.6){m_1_dlsig_3_6->Fill(massc1);}
  	    if (dl_sig>=3.8){m_1_dlsig_3_8->Fill(massc1);}

 	    if (dl_sig>=4.0){m_1_dlsig_4_0->Fill(massc1);}
 	    if (dl_sig>=4.2){m_1_dlsig_4_2->Fill(massc1);}
 	    if (dl_sig>=4.4){m_1_dlsig_4_4->Fill(massc1);}
 	    if (dl_sig>=4.6){m_1_dlsig_4_6->Fill(massc1);}
  	    if (dl_sig>=4.8){m_1_dlsig_4_8->Fill(massc1);}

 	    if (dl_sig>=5.0){m_1_dlsig_5_0->Fill(massc1);}
 	    if (dl_sig>=5.2){m_1_dlsig_5_2->Fill(massc1);}
 	    if (dl_sig>=5.4){m_1_dlsig_5_4->Fill(massc1);}
 	    if (dl_sig>=5.6){m_1_dlsig_5_6->Fill(massc1);}
  	    if (dl_sig>=5.8){m_1_dlsig_5_8->Fill(massc1);}

 	    if (dl_sig>=6.0){m_1_dlsig_6_0->Fill(massc1);}
     	   
	}



    }
  }
}


  plotz->Write();
  cout << "COMPLETE!";  
}
