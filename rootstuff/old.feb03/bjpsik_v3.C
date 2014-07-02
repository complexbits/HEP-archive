#define bjpsik_v3_cxx
#include "bjpsik_v3.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

void bjpsik_v3::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L bjpsik_v3.C
//      Root > bjpsik_v3 t
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

// Initialize variables


// Book histograms

   TH1S *dimu_mass_1 = new TH1S("dimu_mass_1", "Di-Muon Mass",120, 0., 12.);
   TH1S *dimu_mass_2 = new TH1S("dimu_mass_2", "Di-Muon Mass",120, 2.5, 3.7);
   TH1S *dimu_mass_3 = new TH1S("dimu_mass_3", "Di-Muon Mass",100, 8, 11);
   TH1S *dimu_mass_4 = new TH1S("dimu_mass_4", "Di-Muon Mass",50, 8, 11);
   TH1S *dimu_num    = new TH1S("dimu_num", "Di-Muon per Event",10, 0., 10.);
   TH1S *dimu_num_mc    = new TH1S("dimu_num_mc",
				   "Di-Muon per Event mass cut 2.8 to 3.4",
				   10, 0., 10.);

   TH1S *psik_hits   = new TH1S("psik_hits", "Hits on K", 25, 0., 25.);
   TH1S *psik_mass   = new TH1S("psik_mass", "J/psi K Mass",30,4.7,5.9);
   TH1S *psik_mass_ct = new TH1S("psik_mass_ct", "J/psi K Mass",30,4.7,5.9);
   TH1S *psik_num    = new TH1S("psik_num", "J/psi K with psi mass cut",
				10, 0., 10.);
   TH1S *psik_num_ct    = new TH1S("psik_num_ct", "J/psi K with psi mass cut",
				10, 0., 10.);


   TH1S *dimu_cft1   = new TH1S("dimu_cft1", "Number of CFT hits #1",20, 0., 20.);
   TH1S *dimu_cft2   = new TH1S("dimu_cft2", "Number of CFT hits #2",20, 0., 20.);
   TH1S *dimu_smt1   = new TH1S("dimu_smt1", "Number of SMT hits #1",20, 0., 20.);
   TH1S *dimu_smt2   = new TH1S("dimu_smt2", "Number of SMT hits #2",20, 0., 20.);


   TH1S *dimu_dlsig  = new TH1S("dimu_dlsig", "Decay length significances", 100, 0., 10.);
   TH1S *dimu_dlsigSB = new TH1S("dimu_dlsigSB", "Decay length significances side band"
				 , 100, 0., 10.);
   TH1S *dimu_PT     = new TH1S("dimu_PT", "J/psi pT", 100, 0., 25.);


   TH1S *PSImassCut = new TH1S("PSImassCut","Di Muon Mass w/cuts",120, 2.5, 3.7);

   TH1S *dimu_dlsig_cl = new TH1S("dimu_dlsig_cl", "Decay length significances and col cut"
				  , 100, 0., 10.);
   TH1S *dimu_dlsigSB_cl = new TH1S("dimu_dlsigSB_cl", "Decay length significances side band and col cut"
				 , 100, 0., 10.);
   TH1S *PSImassCut_cl = new TH1S("PSImassCut_cl","Di Muon Mass w/cuts and col cut",120, 2.5, 3.7);
   TH1S *dimu_PT_cl     = new TH1S("dimu_PT_cl", "J/psi pT and col cut", 100, 0., 25.);

// Gauss + Linear fit to J/psi mass peak

   TF1 *e1 = new TF1("e1","gaus(0)+pol1(3)");
   e1->SetParameter(0,450);
   e1->SetParameter(1,3.1);
   e1->SetParameter(2,.1);

   TF1 *e2 = new TF1("e2","gaus(0)+pol1(3)");
   e2->SetParameter(0,130);
   e2->SetParameter(1,9.4);
   e2->SetParameter(2,.3);


   Int_t nentries = Int_t(fChain->GetEntriesFast());

   cout << "START  Number of events  =  " << nentries << endl;

   Int_t nbytes = 0, nb = 0;
   for (Int_t jentry=0; jentry<nentries;jentry++) {
      Int_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      Int_t psiCount = 0;
      Int_t psiCount_mc = 0;
      Int_t bpsikCount = 0;
      Int_t bpsikCount_ct = 0;

      for (Int_t psiLoop=0; psiLoop<50; psiLoop++){
	if (PSI_mass[psiLoop] > 0.){
	  psiCount++;
	  dimu_mass_1 -> Fill(PSI_mass[psiLoop]);
	  dimu_mass_2 -> Fill(PSI_mass[psiLoop]);
	  dimu_mass_3 -> Fill(PSI_mass[psiLoop]);
	  dimu_mass_4 -> Fill(PSI_mass[psiLoop]);

	  dimu_cft1 -> Fill(PSI_cft1[psiLoop]);
	  dimu_cft2 -> Fill(PSI_cft2[psiLoop]);
	  dimu_smt1 -> Fill(PSI_smt1[psiLoop]);
	  dimu_smt2 -> Fill(PSI_smt2[psiLoop]);

	  if ( PSI_cft1[psiLoop] == 16 && PSI_cft2[psiLoop] == 16
	      && PSI_smt1[psiLoop] >= 6 && PSI_smt2 >= 6){

	    if (PSI_mass[psiLoop] > 2.8 && PSI_mass[psiLoop] < 3.4){

	      psiCount_mc++;

	      Float_t dlsig = PSI_dl[psiLoop]/PSI_dlError[psiLoop];
	      dimu_dlsig -> Fill(dlsig);
	      PSImassCut -> Fill(PSI_mass[psiLoop]);
	      dimu_PT -> Fill(PSI_pt[psiLoop]);

	      if (PSI_collinearity[psiLoop] > .9){
		dimu_dlsig_cl -> Fill(dlsig);
		PSImassCut_cl -> Fill(PSI_mass[psiLoop]);
		dimu_PT_cl -> Fill(PSI_pt[psiLoop]);
	      }
	    }
	    if ( (PSI_mass[psiLoop] > 3.5 && PSI_mass[psiLoop] <3.7) ||
		 (PSI_mass[psiLoop] > 0. && PSI_mass[psiLoop] < 2.7)){
	      Float_t dlsig = PSI_dl[psiLoop]/PSI_dlError[psiLoop];
	      dimu_dlsigSB -> Fill(dlsig);

	      if ( PSI_collinearity[psiLoop] > .9){
		Float_t dlsig = PSI_dl[psiLoop]/PSI_dlError[psiLoop];
		dimu_dlsigSB_cl -> Fill(dlsig);
	      }
	    }
	  }
	}
      }

      dimu_num->Fill(psiCount);
      dimu_num_mc->Fill(psiCount_mc);

   }
}

