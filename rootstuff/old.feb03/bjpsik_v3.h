//////////////////////////////////////////////////////////
//   This class has been automatically generated 
//     (Mon Jan 13 14:29:34 2003 by ROOT version3.04/01)
//   from TChain tree/
//////////////////////////////////////////////////////////


#ifndef chain_h
#define chain_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class chain {
   public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
//Declaration of leaves types
   Int_t           PV_npv;
   Float_t         PV_x[15];
   Float_t         PV_y[15];
   Float_t         PV_z[15];
   Int_t           PV_ntrk[15];
   Float_t         PV_sumPT[15];
   Float_t         PV_sumLogPT[15];
   Float_t         PV_highestPT[15];
   Int_t           TRACKJET_njet;
   Int_t           TRACKJET_mult[20];
   Float_t         TRACKJET_px[20];
   Float_t         TRACKJET_py[20];
   Float_t         TRACKJET_pz[20];
   Float_t         TRACKJET_E[20];
   Float_t         TRACKJET_pt[20];
   Float_t         TRACKJET_eta[20];
   Float_t         TRACKJET_phi[20];
   Float_t         TRACKJET_z[20];
   Float_t         TRACKJET_q025[20];
   Float_t         TRACKJET_q05[20];
   Float_t         TRACKJET_q1[20];
   Float_t         TRACKJET_q2[20];
   Int_t           PSI_nvtx;
   Int_t           PSI_id[50];
   Float_t         PSI_collinearity[50];
   Float_t         PSI_mass[50];
   Float_t         PSI_massError[50];
   Float_t         PSI_dl[50];
   Float_t         PSI_dlError[50];
   Float_t         PSI_lifetime[50];
   Float_t         PSI_lifetimeError[50];
   Float_t         PSI_chi2[50];
   Float_t         PSI_pt[50];
   Float_t         PSI_eta[50];
   Float_t         PSI_phi[50];
   Float_t         PSI_dca1[50];
   Float_t         PSI_dcaerr1[50];
   Float_t         PSI_zca1[50];
   Float_t         PSI_zcaerr1[50];
   Float_t         PSI_pt1[50];
   Float_t         PSI_eta1[50];
   Float_t         PSI_phi1[50];
   Float_t         PSI_z1[50];
   Float_t         PSI_chisq1[50];
   Float_t         PSI_chi2vtx1[50];
   Float_t         PSI_q1[50];
   Int_t           PSI_smt1[50];
   Int_t           PSI_cft1[50];
   Float_t         PSI_dca2[50];
   Float_t         PSI_dcaerr2[50];
   Float_t         PSI_zca2[50];
   Float_t         PSI_zcaerr2[50];
   Float_t         PSI_pt2[50];
   Float_t         PSI_eta2[50];
   Float_t         PSI_phi2[50];
   Float_t         PSI_z2[50];
   Float_t         PSI_chisq2[50];
   Float_t         PSI_chi2vtx2[50];
   Float_t         PSI_q2[50];
   Int_t           PSI_smt2[50];
   Int_t           PSI_cft2[50];
   Int_t           PHI_nvtx;
   Int_t           PHI_id[50];
   Float_t         PHI_collinearity[50];
   Float_t         PHI_mass[50];
   Float_t         PHI_massError[50];
   Float_t         PHI_dl[50];
   Float_t         PHI_dlError[50];
   Float_t         PHI_lifetime[50];
   Float_t         PHI_lifetimeError[50];
   Float_t         PHI_chi2[50];
   Float_t         PHI_pt[50];
   Float_t         PHI_eta[50];
   Float_t         PHI_phi[50];
   Float_t         PHI_dca1[50];
   Float_t         PHI_dcaerr1[50];
   Float_t         PHI_zca1[50];
   Float_t         PHI_zcaerr1[50];
   Float_t         PHI_pt1[50];
   Float_t         PHI_eta1[50];
   Float_t         PHI_phi1[50];
   Float_t         PHI_z1[50];
   Float_t         PHI_chisq1[50];
   Float_t         PHI_chi2vtx1[50];
   Float_t         PHI_q1[50];
   Int_t           PHI_smt1[50];
   Int_t           PHI_cft1[50];
   Float_t         PHI_dca2[50];
   Float_t         PHI_dcaerr2[50];
   Float_t         PHI_zca2[50];
   Float_t         PHI_zcaerr2[50];
   Float_t         PHI_pt2[50];
   Float_t         PHI_eta2[50];
   Float_t         PHI_phi2[50];
   Float_t         PHI_z2[50];
   Float_t         PHI_chisq2[50];
   Float_t         PHI_chi2vtx2[50];
   Float_t         PHI_q2[50];
   Int_t           PHI_smt2[50];
   Int_t           PHI_cft2[50];
   Int_t           BPSIK_nvtx;
   Int_t           BPSIK_id[40];
   Float_t         BPSIK_collinearity[40];
   Float_t         BPSIK_mass[40];
   Float_t         BPSIK_massError[40];
   Float_t         BPSIK_massc1[40];
   Float_t         BPSIK_massc2[40];
   Float_t         BPSIK_dl[40];
   Float_t         BPSIK_dlError[40];
   Float_t         BPSIK_lifetime[40];
   Float_t         BPSIK_lifetimeError[40];
   Float_t         BPSIK_chi2[40];
   Float_t         BPSIK_pt[40];
   Float_t         BPSIK_eta[40];
   Float_t         BPSIK_phi[40];
   Float_t         BPSIK_kdca[40];
   Float_t         BPSIK_kdcaerr[40];
   Float_t         BPSIK_kzca[40];
   Float_t         BPSIK_kzcaerr[40];
   Float_t         BPSIK_kpt[40];
   Float_t         BPSIK_keta[40];
   Float_t         BPSIK_kphi[40];
   Float_t         BPSIK_kz[40];
   Float_t         BPSIK_kchisq[40];
   Float_t         BPSIK_kchi2vtx[40];
   Float_t         BPSIK_kq[40];
   Int_t           BPSIK_khits[40];

//List of branches
   TBranch        *b_PV;   //!
   TBranch        *b_TRACKJET;   //!
   TBranch        *b_PSI;   //!
   TBranch        *b_PHI;   //!
   TBranch        *b_BPSIK;   //!

   chain(TTree *tree=0);
   ~chain();
   Int_t  Cut(Int_t entry);
   Int_t  GetEntry(Int_t entry);
   Int_t  LoadTree(Int_t entry);
   void   Init(TTree *tree);
   void   Loop();
   Bool_t Notify();
   void   Show(Int_t entry = -1);
};

#endif

#ifdef chain_cxx
chain::chain(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("tree");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("tree","");
      chain->Add("bjpsik_tght_v3.root/tree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

chain::~chain()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t chain::GetEntry(Int_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t chain::LoadTree(Int_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Int_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void chain::Init(TTree *tree)
{
//   Set branch addresses
   if (tree == 0) return;
   fChain    = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("PV",&PV_npv);
   fChain->SetBranchAddress("TRACKJET",&TRACKJET_njet);
   fChain->SetBranchAddress("PSI",&PSI_nvtx);
   fChain->SetBranchAddress("PHI",&PHI_nvtx);
   fChain->SetBranchAddress("BPSIK",&BPSIK_nvtx);
   Notify();
}

Bool_t chain::Notify()
{
   // Called when loading a new file.
   // Get branch pointers.
   b_PV = fChain->GetBranch("PV");
   b_TRACKJET = fChain->GetBranch("TRACKJET");
   b_PSI = fChain->GetBranch("PSI");
   b_PHI = fChain->GetBranch("PHI");
   b_BPSIK = fChain->GetBranch("BPSIK");
   return kTRUE;
}

void chain::Show(Int_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t chain::Cut(Int_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef chain_cxx

