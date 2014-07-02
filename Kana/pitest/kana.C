#define kana_cxx
#include "kana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void kana::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L kana.C
//      Root > kana t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

   if (fChain == 0) return;

   //fChain->SetBranchStatus("MC",1); 

   Long64_t nentries = fChain->GetEntriesFast();

   Int_t nbytes = 0, nb = 0;

   /***** BEGIN USER-INSERTED CODE (Prior to event loop) ************************/

   // Tell us how many entries there are

   printf("\n Entries in this roottuple: %12d \n\n\n", nentries);

   // Iniitialize Histograms

   TH1F *pions = new TH1F("pions", "Pion Pythia ID", 100, -215., 215.);
   TH1F *pi_evt = new TH1F("pi_evt", "Pions/Evt", 400, 0, 400.);
   TH1F *pi_3kevt = new TH1F("pi_3kevt", "Pions/Evt w/ Pt > 3Gev, from Kaons", 5, 0, 5);
   TH1F *pi_evt_ratio = new TH1F("pi_evt_ratio", "Ratio of Pi/Evt w/ Pt > 3GeV to total Pi/Evt", 10, 0, 0.04);

   TH1F *pi_pt = new TH1F("pi_pt", "Pion Pt", 100, 3., 13.); 
   TH1F *pi_px = new TH1F("pi_px", "Pion Px", 100, 3., 13.); 
   TH1F *pi_py = new TH1F("pi_py", "Pion Py", 100, 3., 13.); 
   TH1F *pi_pz = new TH1F("pi_pz", "Pion Pz", 100, 3., 13.); 
   TH1F *pi_ptot = new TH1F("pi_ptot", "Pion Total P", 100, 3., 13.);

   TH1F *pi_theta = new TH1F("pi_theta", "Pion Theta", 100, -1.6, 1.6);
   TH1F *pi_eta = new TH1F("pi_eta", "Pion Eta", 100, 0., 1);

   TH1F *kaons = new TH1F("kaons", "Kaon Pythia ID", 100, 300., 315.);
   TH1F *k_evt = new TH1F("k_evt", "Kaons/Evt", 100, 0, 100.);
   TH1F *k_3pievt = new TH1F("k_3pievt", "Kaons/Evt w/ Pi Pt > 3Gev", 4, 0, 4);
   TH1F *k_evt_ratio = new TH1F("k_evt_ratio", "Ratio of K/Evt w/ PiPt > 3GeV to total K/Evt", 10, 0, 0.3);

   TH1F *k_pt = new TH1F("k_pt", "Kaon Pt", 100, 3., 13.); 
   TH1F *k_px = new TH1F("k_px", "Kaon Px", 100, 3., 13.); 
   TH1F *k_py = new TH1F("k_py", "Kaon Py", 100, 3., 13.); 
   TH1F *k_pz = new TH1F("k_pz", "Kaon Pz", 100, 3., 13.); 
   TH1F *k_ptot = new TH1F("k_ptot", "Kaon Total P", 100, 3., 13.);

   TH1F *k_theta = new TH1F("k_theta", "Kaon Theta", 100, -1.6, 1.6);
   TH1F *k_eta = new TH1F("k_eta", "Kaon Eta", 100, 0., 1.);

   // Initialize other variables

   Double_t kpx, kpy, kpz, kpt, kptot, ktheta, keta;
   Double_t kppx, kppy, kppz, kppt, kpptot, kptheta, kpeta;
   Double_t pipx, pipy, pipz, pipt, piptot, pitheta, pieta;
   
   //Initialize Counters
   Int_t pion_counter;
   Int_t kaon_counter;
   Int_t pi3k_counter;
   Int_t k3pi_counter;
   
   // Initialize Kpt Array
   Double_t kpt_array[10];
   
   /***** END USER-INSERTED CODE (Prior to event loop) **************************/
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     
     /***** BEGIN USER-INSERTED CODE (Inside to event loop) ************************/
     
     // Get the number of MC particles in this event:
     
     Int_t npart = MC_n_mc_part; // can't use this (?): arrays only go to 3000, but npart > 3000 for some events
     
     //Initialize Counters
     pion_counter=0;
     kaon_counter=0;
     pi3k_counter=0;
     k3pi_counter=0;

     for (Int_t ja=0; ja<10; ja++){
       kpt_array[ja]=0.;
     }

     // Loop over all particles in the event
     for(Int_t ipart=0; ipart<3000; ipart++){
       
       // Check for Pions (pythia particle id +/-211) which came from Kaons (311)
       if(TMath::Abs(MC_mc_partid[ipart]) == 211){

	 //Count the number of pions per event
	 pion_counter++;

	 // Get the Pt and total P of the pion :
	 pipx = MC_mc_partPx[ipart];
	 pipy = MC_mc_partPy[ipart];
	 pipz = MC_mc_partPz[ipart];
	 
	 pipt = TMath::Sqrt((pipx*pipx)+(pipy*pipy));
	 piptot = TMath::Sqrt((pipx*pipx)+(pipy*pipy)+(pipz*pipz));	 
	 
	 // Only consider pions with Pt > 3GeV
	 if (pipt >=3.0){
	   
	   // Kaons (K0) not available, so check for parents which are K*0 or Ks0:
	   if(MC_mc_parentid[ipart] == 310 || MC_mc_parentid[ipart] == 313){
	     

	     //Count the number of pions per evt w/ Pt > 3GeV, which came from kaons
	     pi3k_counter++;
	     
	     // Get the Pt of the kaon and fill a histogram with it:
	          
	     kppx = MC_mc_parentPx[ipart];
	     kppy = MC_mc_parentPy[ipart];
	     kppz = MC_mc_parentPz[ipart];
	     
	     kppt = TMath::Sqrt((kppx*kppx)+(kppy*kppy));
	     kpptot = TMath::Sqrt((kppx*kppx) + (kppy*kppy) + (kppz*kppz));
	
	     // Store the parent pt in an array for later comparison:
	     kpt_array[pi3k_counter-1]=kppt;
		    
	     // Fill histograms and stuff:
	     pi_px->Fill(pipx);
	     pi_py->Fill(pipy);
	     pi_pz->Fill(pipz);
	     pi_pt->Fill(pipt);
	     pi_ptot->Fill(piptot);
	     
	     if(pipz !=0.){
	       
	       pitheta = atan(pipt/pipz);
	       pieta = -TMath::Log(TMath::Tan(pitheta/2));
	       
	       pi_theta->Fill(pitheta);
	       pi_eta->Fill(pieta);

	     }
	   }
	 }	
       }
     }
     // Fill histograms with pions/evt, pions/evt w/ pipt > 3GeV, and ratio
     pi_evt->Fill(pion_counter);
     pi_3kevt->Fill(pi3k_counter);
     pi_evt_ratio->Fill(float(pi3k_counter)/float(pion_counter));

     // Loop again over all particles in the event:
     for(Int_t ipart=0; ipart<3000; ipart++){
       
       // Check for Kaons (pythia particle id 310 (K*0) or 313 (Ks0))
       if(MC_mc_partid[ipart] == 310 || MC_mc_partid[ipart] == 313){
	 
	 kaon_counter++;
	 
	 // Get the Pt of the kaon:
	 kpx = MC_mc_partPx[ipart];
	 kpy = MC_mc_partPy[ipart];
	 kpz = MC_mc_partPz[ipart];
	 
	 kpt = TMath::Sqrt((kpx*kpx)+(kpy*kpy));
	 kptot = TMath::Sqrt((kpx*kpx) + (kpy*kpy) + (kpz*kpz));	 
	 
	 for(Int_t jpart=0; jpart<10; jpart++){
	   
	   if(kpt == kpt_array[jpart]){
	     
	     k3pi_counter++;
	     
	     kpx = MC_mc_partPx[ipart];
	     kpy = MC_mc_partPy[ipart];
	     kpz = MC_mc_partPz[ipart];
	     
	     kpt = TMath::Sqrt((kpx*kpx)+(kpy*kpy));
	     kptot = TMath::Sqrt((kpx*kpx) + (kpy*kpy) + (kpz*kpz));
	     
	     k_px->Fill(kpx);
	     k_py->Fill(kpy);
	     k_pz->Fill(kpz);
	     k_pt->Fill(kpt);
	     k_ptot->Fill(kptot);
	     
	     if(kpz != 0.){
	       
	       ktheta = atan(kpt/kpz);
	       keta = -TMath::Log(TMath::Tan(ktheta/2));
	       
	       k_theta->Fill(ktheta);
	       k_eta->Fill(keta);
	       
	     }

	     jpart=10;

	   }
	 }
       }
     }     
     // Fill histograms with K/evt, K/evt w/ PiPt > 3GeV, and ratio:
     k_evt->Fill(kaon_counter);
     k_3pievt->Fill(k3pi_counter);
     k_evt_ratio->Fill(float(k3pi_counter)/float(kaon_counter));
     
     // Print progress through events at each 1/7:
     if ( fmod( float(jentry), ( float(nentries)/7. ) ) == 0 ){
       printf("\n\nNow analyzing entry number %12d\n\n", jentry);
     }     
     
     /***** END USER-INSERTED CODE (Inside to event loop) **************************/
     
   }
   
   /***** BEGIN USER-INSERTED CODE (After event loop) ************************/
   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(111111);
   


   TCanvas *kcan = new TCanvas("kcan", "kcan", 1200, 800);
   kcan->Divide(3,2);

   kcan->cd(1);
   k_pt->Draw();

   kcan->cd(2);
   k_ptot->Draw();

   kcan->cd(3);
   k_eta->Draw();

   kcan->cd(4);
   k_evt->Draw();

   kcan->cd(5);
   k_3pievt->Draw();

   kcan->cd(6);
   k_evt_ratio->Draw();

   TCanvas *pican = new TCanvas("pican", "pican", 1200, 800);
   pican->Divide(3,2);

   pican->cd(1);
   pi_pt->Draw();

   pican->cd(2);
   pi_ptot->Draw();

   pican->cd(3);
   pi_eta->Draw();

   pican->cd(4);
   pi_evt->Draw();

   pican->cd(5);
   pi_3kevt->Draw();

   pican->cd(6);
   pi_evt_ratio->Draw();
   
   
   // Save everything in a root file:
   
   TObjArray *a1 = new TObjArray(0);
   a1->Add(kaons);
   a1->Add(k_evt);

   a1->Add(k_pt);
   a1->Add(k_px);
   a1->Add(k_py);
   a1->Add(k_pz);
   a1->Add(k_theta);
   a1->Add(k_eta);

   a1->Add(pions);
   a1->Add(pi_evt);

   a1->Add(pi_pt);
   a1->Add(pi_px);
   a1->Add(pi_py);
   a1->Add(pi_pz);
   a1->Add(pi_theta);
   a1->Add(pi_eta);

   a1->Add(k_ptot);
   a1->Add(pi_ptot);

   a1->Add(pi_3kevt);
   a1->Add(k_3pievt);

   a1->Add(k_evt_ratio);
   a1->Add(pi_evt_ratio);

   a1->Add(kcan);
   a1->Add(pican);

   TFile *f1 = new TFile("kana.root", "recreate");
   a1->Write();
   f1->Close();

   /***** END USER-INSERTED CODE (After event loop) **************************/

}
