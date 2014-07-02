//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 15 08:40:46 2005 by ROOT version 4.03/02
// from TTree BTree/B->J/psi + K* + pi
// found on file: output_bd2gev.root
//////////////////////////////////////////////////////////

#ifndef kana_h
#define kana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class kana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           JPSI_run;
   Int_t           JPSI_evt;
   Float_t         JPSI_psiMass;
   Float_t         JPSI_psiPx;
   Float_t         JPSI_psiPy;
   Float_t         JPSI_psiPz;
   Float_t         JPSI_psiPt;
   Float_t         JPSI_psiEta;
   Float_t         JPSI_psiPx1;
   Float_t         JPSI_psiPy1;
   Float_t         JPSI_psiPz1;
   Float_t         JPSI_psiPt1;
   Float_t         JPSI_psiEta1;
   Float_t         JPSI_psiPx2;
   Float_t         JPSI_psiPy2;
   Float_t         JPSI_psiPz2;
   Float_t         JPSI_psiPt2;
   Float_t         JPSI_psiEta2;
   Float_t         JPSI_psidxy;
   Float_t         JPSI_psivxy;
   Float_t         JPSI_psichi2;
   Float_t         JPSI_psiPVx;
   Float_t         JPSI_psiPVy;
   Float_t         JPSI_psiPVz;
   Float_t         JPSI_psiPVvx;
   Float_t         JPSI_psiPVvy;
   Float_t         JPSI_psiPVvz;
   Float_t         JPSI_psinPV;
   Float_t         JPSI_psintPV;
   Int_t           JPSI_psiSMT1;
   Int_t           JPSI_psiSMT2;
   Int_t           JPSI_psiCFT1;
   Int_t           JPSI_psiCFT2;
   Int_t           K0_k0num;
   Int_t           K0_k0id[20];
   Float_t         K0_k0Mass[20];
   Float_t         K0_k0Px[20];
   Float_t         K0_k0Py[20];
   Float_t         K0_k0Pz[20];
   Float_t         K0_k0Pt[20];
   Float_t         K0_k0Eta[20];
   Float_t         K0_k0dxy[20];
   Float_t         K0_k0vxy[20];
   Float_t         K0_k0chi2[20];
   Float_t         K0_k0Px1[20];
   Float_t         K0_k0Py1[20];
   Float_t         K0_k0Pz1[20];
   Float_t         K0_k0Pt1[20];
   Float_t         K0_k0Eta1[20];
   Float_t         K0_k0Px2[20];
   Float_t         K0_k0Py2[20];
   Float_t         K0_k0Pz2[20];
   Float_t         K0_k0Pt2[20];
   Float_t         K0_k0Eta2[20];
   Int_t           K0_k0SMT1[20];
   Int_t           K0_k0SMT2[20];
   Int_t           K0_k0CFT1[20];
   Int_t           K0_k0CFT2[20];
   Int_t           Kstr_nks;
   Int_t           Kstr_k0pnt[300];
   Int_t           Kstr_pipnt[300];
   Float_t         Kstr_ksmass[300];
   Float_t         Kstr_kschi2[300];
   Float_t         Kstr_ksPx[300];
   Float_t         Kstr_ksPy[300];
   Float_t         Kstr_ksPz[300];
   Int_t           Tracks_nTrks;
   Int_t           Tracks_piQ[500];
   Float_t         Tracks_piPx[500];
   Float_t         Tracks_piPy[500];
   Float_t         Tracks_piPz[500];
   Float_t         Tracks_piPt[500];
   Float_t         Tracks_piEta[500];
   Int_t           Tracks_piSMT[500];
   Int_t           Tracks_piCFT[500];
   Int_t           Bs_nBs;
   Int_t           Bs_idKs[300];
   Int_t           Bs_idPi[300];
   Float_t         Bs_mass[300];
   Float_t         Bs_Bschi2[300];
   Float_t         Bs_Bscxy[300];
   Float_t         Bs_BsPx[300];
   Float_t         Bs_BsPy[300];
   Float_t         Bs_BsPz[300];
   Int_t           Test_nPi1;
   Int_t           Test_nPi2;
   Int_t           MC_n_mc_part;
   Int_t           MC_dauID;
   Int_t           MC_n_mc_dau[3000];
   Int_t           MC_mc_partid[3000];
   Float_t         MC_mc_partPx[3000];
   Float_t         MC_mc_partPy[3000];
   Float_t         MC_mc_partPz[3000];
   Int_t           MC_mc_parentid[3000];
   Float_t         MC_mc_parentPx[3000];
   Float_t         MC_mc_parentPy[3000];
   Float_t         MC_mc_parentPz[3000];
   Int_t           Bplus_nBplus;
   Int_t           Bplus_idKs[300];
   Float_t         Bplus_massBp[300];
   Float_t         Bplus_Bpchi2[300];
   Float_t         Bplus_Bpcxy[300];
   Float_t         Bplus_BpPx[300];
   Float_t         Bplus_BpPy[300];
   Float_t         Bplus_BpPz[300];

   // List of branches
   TBranch        *b_JPSI;   //!
   TBranch        *b_K0;   //!
   TBranch        *b_Kstr;   //!
   TBranch        *b_Tracks;   //!
   TBranch        *b_Bs;   //!
   TBranch        *b_Test;   //!
   TBranch        *b_MC;   //!
   TBranch        *b_Bplus;   //!

   kana(TTree *tree=0);
   virtual ~kana();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef kana_cxx
kana::kana(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output_bd2gev.root");
      if (!f) {
         f = new TFile("output_bd2gev.root");
      }
      tree = (TTree*)gDirectory->Get("BTree");

   }
   Init(tree);
}

kana::~kana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t kana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t kana::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void kana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("JPSI",&JPSI_run);
   fChain->SetBranchAddress("K0",&K0_k0num);
   fChain->SetBranchAddress("Kstr",&Kstr_nks);
   fChain->SetBranchAddress("Tracks",&Tracks_nTrks);
   fChain->SetBranchAddress("Bs",&Bs_nBs);
   fChain->SetBranchAddress("Test",&Test_nPi1);
   fChain->SetBranchAddress("MC",&MC_n_mc_part);
   fChain->SetBranchAddress("Bplus",&Bplus_nBplus);
   Notify();
}

Bool_t kana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_JPSI = fChain->GetBranch("JPSI");
   b_K0 = fChain->GetBranch("K0");
   b_Kstr = fChain->GetBranch("Kstr");
   b_Tracks = fChain->GetBranch("Tracks");
   b_Bs = fChain->GetBranch("Bs");
   b_Test = fChain->GetBranch("Test");
   b_MC = fChain->GetBranch("MC");
   b_Bplus = fChain->GetBranch("Bplus");

   return kTRUE;
}

void kana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t kana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef kana_cxx
