#define bjpsik_tght_v3_cxx
#include "bjpsik_tght_v3.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

void bjpsik_tght_v3::Loop()
{

   if (fChain == 0) return;

// Initialize variables

// Book histograms

   TH1S *dimu_mass = new TH1S("dimu_mass", "Di Muon mass", 120, 2.5, 3.7);
   TH1S *dimu_mass_cut = new TH1S("dimu_mass_cut", "Di Muon mass w/cuts", 120, 2.5, 3.7);
   TH1S *dimu_dksig_cut = new TH1S("dimu_dksig_cut", "Decay length signif.",100, 0., 10.);

   TH1S *bpsik_mass = new TH1S("bpsik_mass", "J/psi K mass no cuts",30, 4.7, 5.9);
   TH1S *bpsik_mass_nc = new TH1S("bpsik_mass_nc", "J/psi K mass jpsi hits cut",30, 4.7, 5.9);
   TH1S *bpsik_mass_cut = new TH1S("bpsik_mass_cut", "J/psi K mass w/cuts",30, 4.7, 5.9);
   TH1S *bpsik_count = new TH1S("bpsik_count", "Number of Bs per event",40,0., 40.);
   TH1S *bpsik_khit = new TH1S("bpsik_khit", "Hits on K track", 30, 0., 30.);
   TH1S *bpsik_k_cut = new TH1S("bpsik_k_cut", "J/psi K mass with K hits cut", 30, 4.7, 5.9);
   TH1S *bpsik_vtxchi2 = new TH1S("bpsik_vtxchi2", "VTX chi2 w/K", 100, 0., 50.);
   TH1S *bpsik_kpt = new TH1S("bpsik_kpt", "K pt with cuts", 100, 0., 10.);
   TH1S *bpsik_pt = new TH1S("bpsik_pt", "B pt with cuts", 100, 0., 25.);
   TH1S *bpsik_pt_cut = new TH1S("bpsik_pt_cut", "J/psi K mass pt>10",30, 4.7, 5.9);
   TH1S *bpsik_dlsig = new TH1S("bpsik_dl", "Decay length B", 100, 0., 10.);
   
   TH1S *winner_bmass = new TH1S("winner_bmass", "Mass of B, final cuts", 30, 4.7, 5.9);
   TH1S *winner_psimass = new TH1S("winner_psimass", "Mass of J/Psi, final cuts", 120, 2.5, 3.7);
   TH1S *winner_bpsik_kpt = new TH1S("winner_bpsik_kpt", "K pt, final cut", 100, 0., 10.);
   TH1S *winner_bpsik_pt = new TH1S("winner_bpsik_pt", "B pt, final cut", 100, 0., 25.);

   Int_t nentries = Int_t(fChain->GetEntriesFast());
   
//   cout << "TESTING with 5000 events..." << endl;


   cout << "START  Number of events  =  " << nentries << endl;

   Int_t nbytes = 0, nb = 0;
//   for (Int_t jentry=0; jentry<5000;jentry++) {
   for (Int_t jentry=0; jentry<nentries;jentry++) {
      Int_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	
	Int_t	num_Bs_with_psi[50];
	for (Int_t n=0; n < 50; n++){
		num_Bs_with_psi[n] = 0.;
	}
	
	Int_t	good_B[40];
	for (Int_t a=0; a < 40; a++){
		good_B[a] = 0.;
	}
	
      Int_t countB = 0;
      Int_t countBcutJHit =0;
      Int_t countUnique = 0;
      Int_t countGoodB = 0;
      for (Int_t iLoop=0; iLoop < 40; iLoop++){

	if (BPSIK_mass[iLoop] > 0.){
	  countB++;
	  bpsik_mass -> Fill(BPSIK_mass[iLoop]);
	  Int_t psi_id = BPSIK_id[iLoop];
	  dimu_mass -> Fill(PSI_mass[psi_id]);
	  
	  if (PSI_cft1[psi_id] >= 16 && PSI_cft2[psi_id] >= 16 &&
	      PSI_smt1[psi_id] >= 6 && PSI_smt2[psi_id] >= 6 &&
	      PSI_mass[psi_id] > 2.9 && PSI_mass[psi_id] < 3.25){

	    countBcutJHit++;
	    dimu_mass_cut -> Fill(PSI_mass[psi_id]);
	    bpsik_mass_nc -> Fill(BPSIK_mass[iLoop]);

	    Float_t psi_sig = PSI_dl[psi_id]/PSI_dlError[psi_id];
	    dimu_dksig_cut -> Fill(psi_sig);

	    if (psi_sig > 3. && PSI_collinearity[psi_id] > 0.9 &&
		PSI_dl[psi_id] > .0){
	      bpsik_mass_cut -> Fill(BPSIK_mass[iLoop]);
	      bpsik_vtxchi2 -> Fill(BPSIK_kchi2vtx[iLoop]);

	      bpsik_khit->Fill(BPSIK_khits[iLoop]);
	      
	      if (BPSIK_khits[iLoop] > 2 && BPSIK_kchi2vtx[iLoop] <10.){
	      
		bpsik_kpt -> Fill(BPSIK_kpt[iLoop]);
		bpsik_pt  -> Fill(BPSIK_pt[iLoop]);
		bpsik_k_cut -> Fill(BPSIK_mass[iLoop]);
		Float_t psik_dlsig = BPSIK_dl[iLoop]/BPSIK_dlError[iLoop];
		bpsik_dlsig -> Fill(psik_dlsig);
		
		if (BPSIK_pt[iLoop] > 5. &&
		    psik_dlsig>3. && BPSIK_collinearity[iLoop] > 0.9 &&
		    BPSIK_dl[iLoop] > .0){
		    
		  bpsik_pt_cut -> Fill(BPSIK_mass[iLoop]);
		  
		  countGoodB++;
		  num_Bs_with_psi[psi_id]++;	     // Count how many times we find this psi_id for this event
		  good_B[iLoop]++;		     // Should be "1" for any good B, and "0" for any bad B
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
		  // Continue if, and only if the psi_id for a given good-B is the same as the one which had exactly one occurrence.
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
   }
}
   TPostScript dimu_mass("dimu_mass.ps",111);
   dimu_mass.Range(10,8);
   dimu_mass->Draw();
   dimu_mass.Close();
   
    TPostScript dimu_mass_cut("dimu_mass_cut.ps",111);
   dimu_mass_cut.Range(10,8);
   dimu_mass_cut->Draw();
   dimu_mass_cut.Close();
   
      TPostScript dimu_dksig_cut("dimu_dksig_cut.ps",111);
   dimu_dksig_cut.Range(10,8);
   dimu_dksig_cut->Draw();
   dimu_dksig_cut.Close();
   
      TPostScript bpsik_mass("bpsik_mass.ps",111);
   bpsik_mass.Range(10,8);
   bpsik_mass->Draw();
   bpsik_mass.Close();
   
      TPostScript bpsik_mass("bpsik_mass.ps",111);
   bpsik_mass.Range(10,8);
   bpsik_mass->Draw();
   bpsik_mass.Close();
   
      TPostScript bpsik_mass_nc("bpsik_mass_nc.ps",111);
   bpsik_mass_nc.Range(10,8);
   bpsik_mass_nc->Draw();
   bpsik_mass_nc.Close();
 
 // finish replacing the following with histograms to test:
   
      TPostScript bpsik_mass_cut("bpsik_mass_cut.ps",111);
   bpsik_mass_cut.Range(10,8);
   bpsik_mass_cut->Draw();
   bpsik_mass_cut.Close();
   
      TPostScript bjpsik_count("bjpsik_count.ps",111);
   bjpsik_count.Range(10,8);
   bjpsik_count->Draw();
   bjpsik_count.Close();
 
      TPostScript bpsik_mass_cut("bpsik_mass_cut.ps",111);
   bpsik_mass_cut.Range(10,8);
   bpsik_mass_cut->Draw();
   bpsik_mass_cut.Close();
   
      TPostScript bjpsik_count("bjpsik_count.ps",111);
   bjpsik_count.Range(10,8);
   bjpsik_count->Draw();
   bjpsik_count.Close();      TPostScript bpsik_mass_cut("bpsik_mass_cut.ps",111);
   bpsik_mass_cut.Range(10,8);
   bpsik_mass_cut->Draw();
   bpsik_mass_cut.Close();
   
      TPostScript bjpsik_count("bjpsik_count.ps",111);
   bjpsik_count.Range(10,8);
   bjpsik_count->Draw();
   bjpsik_count.Close();
