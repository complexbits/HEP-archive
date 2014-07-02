#define ariel_aa_cxx
#include "ariel_aa.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include <iostream>

//ofstream myout;

void ariel_aa::Loop()
{

TFile plotz("kpt.root","recreate");


  // Kpt Histograms
  TH1F* kpt_nc = new TH1F("kpt_nc", "Kpt, no cuts",50,0.0,2.0);

  TH1F* kpt_lo = new TH1F("kpt_lo", "0.5<Kpt<1.0",50,0.5,1.0);
  TH1F* kpt_hi = new TH1F("kpt_hi", "Kpt>1.0",50,1.0,1.5);

  TH1F* dl_sig_lo = new TH1F("dl_sig_lo", "dl_sig for 0.5<Kpt<1.0", 50,3.0,6.0);
  TH1F* dl_sig_hi = new TH1F("dl_sig_hi", "dl_sig for Kpt>1.0", 50,3.0,6.0);

  TH1F* coll_lo = new TH1F("coll_lo", "coll for 0.5<Kpt<1.0", 50,0.08,0.95);
  TH1F* coll_hi = new TH1F("coll_hi", "coll for Kpt>1.0", 50,0.08,0.95);

  TH1F* ksmt_lo = new TH1F("ksmt_lo", "ksmt for 0.5<Kpt<1.0", 50,0.0,3.0);
  TH1F* ksmt_hi = new TH1F("ksmt_hi", "ksmt for Kpt>1.0", 50,0.0,3.0);


  if (fChain == 0) return;
   
  int aa = 1000; int nn = 0;

  Int_t nentries = Int_t(fChain->GetEntries());
  //  cout <<"Number of entries  " << nentries   << endl;

  Int_t nbytes = 0, nb = 0;

  Int_t iCountF = 0;
  Int_t flag = 0;

  Float_t dm[10];
  Int_t count_m = 0;

  // for (Int_t jentry=0; jentry<10000;jentry++) {
   for (Int_t jentry=0; jentry<nentries;jentry++) {

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

	if(Kch2<=10 && chi2<10){
	  kpt_nc->Fill(Kpt);
	}
	
	if(Kch2<=10 && chi2<10 && dl_sig>=4.5 && Ksmt>1 && coll>0.95){
	  kpt_lo->Fill(Kpt);
	  kpt_hi->Fill(Kpt);
	}

	if(Kch2<=10 && chi2<10 && BPSIK_kchisq[j]>0.00001 && Kpt>=0.5 && Kpt<=1.0){
	  dl_sig_lo->Fill(dl_sig);
	  ksmt_lo->Fill(Ksmt);
	  coll_lo->Fill(coll);

	}
	if(Kch2<=10 && chi2<10 && Kpt>=1.0){
	  dl_sig_hi->Fill(dl_sig);
	  ksmt_hi->Fill(Ksmt);
	  coll_hi->Fill(coll);

	}
      }
  }
}

  plotz.Write();
  cout << "COMPLETE!";  
}
