#define jh_052703_cxx
#include "jh_052703.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "iostream.h"

void jh_052703::Loop()
{

TFile plotz("jh_052703_test.root","recreate");

  // My variables

  float minMass = 4.75; float maxMass = 6.0;
  float div = 0.04;
  int nBins = (maxMass - minMass)/div;   
  

  //ID Histograms
  TH1F* id1 = new TH1F("id1", "psiid", 50, 0, 50);
  TH1F* id2 = new TH1F("id2", "jpsi_id", 50, 0, 50);
  TH1F* id3 = new TH1F("id3", "k", 50, 0, 50);
  TH1F* id4 = new TH1F("id4", "j", 50, 0, 50);

  // Muon Eta Histograms
  
  TH1F* mu1eta = new TH1F("mu1eta", "Muon 1 Eta", 50,-10.0,10.0);
  TH1F* mu2eta = new TH1F("mu2eta", "Muon 2 Eta", 50,-10.0,10.0);


  if (fChain == 0) return;
   
  int aa = 1000; int nn = 0;

  Int_t nentries = Int_t(fChain->GetEntries());
  cout <<"Number of entries  " << nentries   << endl;

  Int_t nbytes = 0, nb = 0;


   for (Int_t jentry=0; jentry<30000;jentry++) {
     // for (Int_t jentry=0; jentry<nentries;jentry++) {

    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    	if(jentry/aa>nn) cout << "Event #" << jentry << endl;
      	nn = jentry/aa;

    Int_t iFound = 0;

    if(PV_npv<1 || PV_ntrk[0]<2) continue;

    // Fill histograms with vertex info

    for(int k=0; k<PSI_nvtx; k++){
      int psiid = PSI_id[k];

      if( (PSI_q1[psiid]+PSI_q2[psiid])==0 && PSI_chi2[psiid]<10.0
	  &&
	  PSI_pt1[psiid]>=1.5 && PSI_pt2[psiid]>=1.5 && 
	  PSI_smt1[psiid]>=1 && PSI_smt2[psiid]>=1 &&
	  PSI_mass[psiid]>2.8 && PSI_mass[psiid]<3.3 &&
	  PSI_pt[psiid]>3.) {

	float ppt1 = PSI_pt1[psiid];
	float ppt2 = PSI_pt2[psiid];

	mu1eta->Fill(ppt1);
	mu2eta->Fill(ppt2);

	id1->Fill(psiid);
	id2->Fill(k);

      }
    }
    for(int j=0; j<BPSIK_nvtx; j++) {
      
      int jpsi_id = BPSIK_id[j];

      //require JPSI

      if( (PSI_q1[jpsi_id]+PSI_q2[jpsi_id])==0 && PSI_chi2[jpsi_id]<10.0
	  &&
	  PSI_pt1[jpsi_id]>=1.5 && PSI_pt2[jpsi_id]>=1.5 && 
	  PSI_smt1[jpsi_id]>=1 && PSI_smt2[jpsi_id]>=1 &&
	  PSI_mass[jpsi_id]>2.8 && PSI_mass[jpsi_id]<3.3 &&
	  PSI_pt[jpsi_id]>3.) {
	
	id1->Fill(jpsi_id);
	id2->Fill(j);

	
      }
    }
   }
   plotz->Write();

}
