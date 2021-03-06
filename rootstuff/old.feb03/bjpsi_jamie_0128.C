#define bjpsi_v6_2_cxx
#include "bjpsi_v6_2.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

void bjpsi_v6_2::Loop()
{

 
TFile finished_data("histograms-filled.root","recreate");

  if (fChain == 0) return;

  // Initialize variables

  Int_t countBp = 0;
  Int_t countBm = 0;

  Int_t countBjpr = 0;
  Int_t countBjpw = 0;
  Int_t countBjmr = 0;
  Int_t countBjmw = 0;

  // Int_t aa = 10000;

  Int_t aa = 100000;
  Int_t nn = 0;

  // Book histograms

  TH1S *dimu_mass = new TH1S("dimu_mass", "Di Muon mass", 120, 2.5, 3.7);
  TH1S *dimu_mass_cut = new TH1S("dimu_mass_cut", "Di Muon mass w/cuts", 120, 2.5, 3.7);
  TH1S *dimu_dksig_cut = new TH1S("dimu_dksig_cut", "Decay length signif.",100, 0., 10.);
  TH1S *dimu_dk = new TH1S("dimu_dk", "psi Decay Length",100,0.,1.);
  TH1S *dimu_col = new TH1S("dimu_col","psi Collinearity",100,-1.,1.);
  TH1S *dimu_dkerr_cut = new TH1S("dimu_dkerr_cut","psi Decay Length Error",100, 0., .5);

  TH1S *dimu_mass_nc = new TH1S("dimu_mass_nc", "Di Muon Mass No Cuts", 120, 2.5, 3.7);
  TH1S *dimu_mass_hc = new TH1S("dimu_mass_hc", "Di Muon Mass Hits Cuts", 120, 2.5, 3.7);

  // Gauss + Linear fit to J/psi mass peak

  TF1 *e1 = new TF1("e1","gaus(0)+pol1(3)");
  e1->SetParameter(0,1000);
  e1->SetParameter(1,3.1);
  e1->SetParameter(2,.1);

  // Gauss + Linear fit to psi K  mass peak

  TF1 *e1 = new TF1("e1","gaus(0)+pol1(3)");
  e1->SetParameter(0,20);
  e1->SetParameter(1,5.3);
  e1->SetParameter(2,.5);

  TH1S *bpsik_mass = new TH1S("bpsik_mass", "J/psi K mass no cuts",30, 4.7, 5.9);
  TH1S *bpsik_mass_nc = new TH1S("bpsik_mass_nc", "J/psi K mass jpsi hits cut",30, 4.7, 5.9);
  TH1S *bpsik_mass_cut = new TH1S("bpsik_mass_cut", "J/psi K mass w/cuts",30, 4.7, 5.9);
  TH1S *bpsik_count = new TH1S("bpsik_count", "Number of Bs per event",40,0., 40.);
  TH1S *bpsik_khit = new TH1S("bpsik_khit", "Hits on K track", 30, 0., 30.);
  TH1S *bpsik_k_cut = new TH1S("bpsik_k_cut", "J/psi K mass with K hits cut", 30, 4.7, 5.9);
  TH1S *bpsik_vtxchi2 = new TH1S("bpsik_vtxchi2", "B chi2", 100, 0., 50.);
  TH1S *bpsik_kpt = new TH1S("bpsik_kpt", "K pt with cuts", 100, 0., 10.);
  TH1S *bpsik_pt = new TH1S("bpsik_pt", "B pt with cuts", 100, 0., 25.);
  TH1S *bpsik_pt_cut = new TH1S("bpsik_pt_cut", "J/psi K mass pt>10",30, 4.7, 5.9);
  TH1S *bpsik_pt_cut_c = new TH1S("bpsik_pt_cut_c", "J/psi K mass pt>10 constraint",30, 4.7, 5.9);
  TH1S *bpsik_dlsig = new TH1S("bpsik_dlsig", "Decay length B", 100, 0., 10.);
  TH1S *bpsik_col = new TH1S("bpsik_col", "psi K Collinearity",100, -1., 1.);
  TH1S *bpsik_dl = new TH1S("bpsik_dl", "psi K Decay Length",100, 0., 1.);

  TH1S *jetpt = new TH1S("jetpt", "Jet pT", 100, 0., 25.);
  TH1S *jetpthi = new TH1S("jetpthi", "Highest Jet pT in event", 100, 0., 25.);
  TH1S *numjet = new TH1S("numjet", "Number of jets per event", 25, 0., 25.);

  TH1S *q025p = new TH1S("q025p", "Jet Charge r < .25 positive", 20, -1.1, 1.1);
  TH1S *q05p = new TH1S("q05p", "Jet Charge r < .5 positive", 20, -1.1, 1.1);
  TH1S *q1p = new TH1S("q1p", "Jet Charge r < 1 positive", 20, -1.1, 1.1);
  TH1S *q2p = new TH1S("q2p", "Jet Charge r < 2 positive", 20, -1.1, 1.1);

  TH1S *q025m = new TH1S("q025m", "Jet Charge r < .25 negative", 20, -1.1, 1.1);
  TH1S *q05m = new TH1S("q05m", "Jet Charge r < .5 negative", 20, -1.1, 1.1);
  TH1S *q1m = new TH1S("q1m", "Jet Charge r < 1 negative", 20, -1.1, 1.1);
  TH1S *q2m = new TH1S("q2m", "Jet Charge r < 2 negative", 20, -1.1, 1.1);
   
  TH1S *winner_bmass = new TH1S("winner_bmass", "Mass of B, final cuts", 30, 4.7, 5.9);
  TH1S *winner_psimass = new TH1S("winner_psimass", "Mass of J/Psi, final cuts", 120, 2.5, 3.7);
  TH1S *winner_bpsik_kpt = new TH1S("winner_bpsik_kpt", "K pt, final cut", 100, 0., 10.);
  TH1S *winner_bpsik_pt = new TH1S("winner_bpsik_pt", "B pt, final cut", 100, 0., 25.);
  TH1S *bpsik_count_good = new TH1S("bpsik_count_good", "# of Reasonable B's for Events w/ at least 1 B", 40,1.,10);
  TH1S *delta_phi = new TH1S("delta_phi", "Phi difference: B - Jet", 40, 0., 5);

  // End my code

  //   Int_t nentries = Int_t(fChain->GetEntriesFast());

  Int_t nentries = Int_t(fChain->GetEntries());

  cout << "START  Number of events  =  " << nentries << endl;

  Int_t nbytes = 0, nb = 0;

  for (Int_t jentry=0; jentry<nentries;jentry++) {

      Int_t ientry = LoadTree(jentry);

      if (ientry < 0) break;

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if (Cut(ientry) < 0) continue;
      //cout << " jentry  " << jentry << " " << aa << " " << nn << endl;

      if(jentry/aa>nn) cout << "Event #" << jentry << endl;
      nn = jentry/aa;

      // Start my code again

      Int_t countB = 0;
      Int_t countBcutJHit =0;
      Int_t countBf =0;

      // initialize nested counters

	Int_t	num_Bs_with_psi[50];

	for (Int_t n=0; n < 50; n++){
		num_Bs_with_psi[n] = 0.;
	}
	
	Int_t	good_B[40];

	for (Int_t a=0; a < 40; a++){
		good_B[a] = 0.;
	}

      Int_t countUnique = 0;
      Int_t countGoodB = 0;
	
      for (Int_t iLoop=0; iLoop < 50; iLoop++){

          // Plot dimuon mass distributions

          dimu_mass_nc -> Fill(PSI_mass[iLoop]);
	
          if (PSI_cft1[iLoop] >= 10 && PSI_cft2[iLoop] >= 10 &&
	     PSI_smt1[iLoop] >= 2 && PSI_smt2[iLoop] >= 2){
	  
	     dimu_mass_hc ->Fill(PSI_mass[iLoop]);
          }

          if (iLoop < 40) {

	     if (BPSIK_mass[iLoop] > 0.){

	        countB++;
	        bpsik_mass -> Fill(BPSIK_mass[iLoop]);
	        Int_t psi_id = BPSIK_id[iLoop];
	        dimu_mass -> Fill(PSI_mass[psi_id]);

	        if (PSI_cft1[psi_id] >= 10 && PSI_cft2[psi_id] >= 10 &&
	           PSI_smt1[psi_id] >= 2 && PSI_smt2[psi_id] >= 2 &&
	           PSI_mass[psi_id] > 2.9 && PSI_mass[psi_id] < 3.25){

	           countBcutJHit++;
	           dimu_mass_cut -> Fill(PSI_mass[psi_id]);
	           bpsik_mass_nc -> Fill(BPSIK_mass[iLoop]);

	           Float_t psi_sig = PSI_dl[psi_id]/PSI_dlError[psi_id];

	           dimu_dksig_cut -> Fill(psi_sig);
	           dimu_dkerr_cut -> Fill(PSI_dlError[psi_id]);
	           dimu_dk -> Fill(PSI_dl[psi_id]);  

	           dimu_col -> Fill(PSI_collinearity[psi_id]);

	           // Changed collin from 0.9 to -1.

	           if (psi_sig > 3. && PSI_collinearity[psi_id] > -1. &&
		      PSI_dl[psi_id] > .1){

	              bpsik_mass_cut -> Fill(BPSIK_mass[iLoop]);
	              bpsik_vtxchi2 -> Fill(BPSIK_chi2[iLoop]);
	              bpsik_khit->Fill(BPSIK_khits[iLoop]);

	              if (BPSIK_khits[iLoop] >= 1 && BPSIK_chi2[iLoop] <10.){

		         bpsik_kpt -> Fill(BPSIK_kpt[iLoop]);
		         bpsik_pt  -> Fill(BPSIK_pt[iLoop]);
		         bpsik_k_cut -> Fill(BPSIK_mass[iLoop]);

		         Float_t psik_dlsig = BPSIK_dl[iLoop]/BPSIK_dlError[iLoop];

		         bpsik_dlsig -> Fill(psik_dlsig);
		         bpsik_col -> Fill(BPSIK_collinearity[iLoop]);
		         bpsik_dl -> Fill(BPSIK_dl[iLoop]);


		         if (BPSIK_pt[iLoop] > 5. &&
		            psik_dlsig>3. && BPSIK_collinearity[iLoop] > 0.9 &&
		            BPSIK_dl[iLoop] > .1){

		            bpsik_pt_cut -> Fill(BPSIK_mass[iLoop]);
		            bpsik_pt_cut_c -> Fill(BPSIK_massc1[iLoop]);

		            countBf++;
		            countGoodB++;
		            num_Bs_with_psi[psi_id]++;	   // Count how many times we find this psi_id for this event
		            good_B[iLoop]++;		   // Should be "1" for any good B, and "0" for any bad B

		            // Start of code to calculate dilution

		            numjet -> Fill(TRACKJET_njet);

		            for (Int_t iJet = 0; iJet < TRACKJET_njet; iJet++){

		                jetpt -> Fill(TRACKJET_pt[iJet]);

		                //cout << "Jet "<< iJet << "  "<< TRACKJET_pt[iJet] << endl;
		            }
		            // cout << " End " << endl;

		            jetpthi -> Fill(TRACKJET_pt[1]);

		            if (BPSIK_kq[iLoop] > 0. &&
		               BPSIK_mass[iLoop] > 5.1 && BPSIK_mass[iLoop] < 5.4
		               && TRACKJET_njet > 0){

		               countBp++;

		               q025p -> Fill(TRACKJET_q025[1]);
		               q05p  -> Fill(TRACKJET_q05[1]);

		               if (TRACKJET_q1[1] != 0.) q1p -> Fill(TRACKJET_q1[1]);

		               if (TRACKJET_q2[1] != 0.) q2p -> Fill(TRACKJET_q2[1]);

		               if (TRACKJET_q1[1] > 0.25){
		                  countBjpr++;
		               }
		               if (TRACKJET_q1[1] < -0.25){
		                  countBjpw++;
		               }

		            }
		            if (BPSIK_kq[iLoop] < 0. &&
		               BPSIK_mass[iLoop] > 5.1 && BPSIK_mass[iLoop] < 5.4
		               && TRACKJET_njet > 0){

		               countBm++;

		               q025m -> Fill(TRACKJET_q025[1]);
		               q05m  -> Fill(TRACKJET_q05[1]);

		               if (TRACKJET_q1[1] != 0.) q1m   -> Fill(TRACKJET_q1[1]);

		               if (TRACKJET_q2[1] != 0.) q2m   -> Fill(TRACKJET_q2[1]);

		               if (TRACKJET_q1[1] < -0.25){
		                  countBjmr++;
		               }
		               if (TRACKJET_q1[1] > 0.25){
		                  countBjmw++;
		               }
		            }
			    if (BPSIK_mass[iLoop] > 5.1 && BPSIK_mass[iLoop] < 5.4){

			    	Int_t jphi = BPSIK_phi[iLoop];
				
				for (Int_t kLoop=0; kLoop < TRACKJET_njet; kLoop++){
				
					dphi = jphi - TRACKJET_phi[kLoop];
					delta_phi -> Fill(dphi);
				
				}
			    }
		         }
	              }
	          }
	      }
	  }
      }
    }
    // Loop through all of the possible psi_id's we may have found
    for (Int_t jLoop=0; jLoop < 50;  jLoop++){                 
	// Continue if and only if the particular psi_id was logged exactly once.      
	if (num_Bs_with_psi[jLoop]==1){			
	   // Loop through *all* the possible B's we may have found	
	   for (Int_t iLoop=0; iLoop < 40; iLoop++){		
	       // Take only the B's which passed all the cuts	      
	       if (good_B[iLoop]==1){				
		  // Continue if, and only if the psi_id for a given good-B is the same 
		  // as the one which had exactly one occurrence.
		  if (jLoop == BPSIK_id[iLoop]){		
				
		      countUnique++;		       // Incriment this each time we have a match 
		      
		      cout << "Unique Entry Found in Event number " << jentry << " :" << endl;
		      cout << "   iLoop: " << iLoop << "  psi_id: " << jLoop << "  countGoodB: " << countGoodB << "  countUnique: " << countUnique << "  num_Bs_with_psi[" << jLoop << "] = " << num_Bs_with_psi[jLoop] << endl << endl;

		      // Fill the histograms :)
					
		      winner_bmass -> Fill(BPSIK_mass[iLoop]);	    
		      winner_psimass -> Fill(PSI_mass[jLoop]);	    
		      winner_bpsik_kpt -> Fill(BPSIK_kpt[iLoop]);  
		      winner_bpsik_pt  -> Fill(BPSIK_pt[iLoop]);    
		  }
	       }
	   }
	}
	
    }
    bpsik_count -> Fill(countB);
    bpsik_count_good -> Fill(countGoodB);
  }
  cout << "Positive Bs  "<< countBp <<"  Negative Bs  "<< countBm << endl;
  cout << "Positive Bs  good tags  "  << countBjpr << "  bad tags  " << countBjpw << endl;
  cout << "Negative Bs  good tags  "  << countBjmr << "  bad tags  " << countBjmw << endl;

finished_data.Write();
}




