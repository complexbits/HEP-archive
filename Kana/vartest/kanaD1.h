//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 14 10:11:45 2005 by ROOT version 4.03/02
// from TTree KTree/K_s -> Mu Mu
// found on file: output_ksmumu_set1.root
//////////////////////////////////////////////////////////

#ifndef kanaD1_h
#define kanaD1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class kanaD1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           K0pipi_k0pnum;
   Int_t           K0pipi_k0pid[50];
   Float_t         K0pipi_k0pMass[50];
   Float_t         K0pipi_k0pPx[50];
   Float_t         K0pipi_k0pPy[50];
   Float_t         K0pipi_k0pPz[50];
   Float_t         K0pipi_k0pPt[50];
   Float_t         K0pipi_k0pEta[50];
   Float_t         K0pipi_k0pdxy[50];
   Float_t         K0pipi_k0pvxy[50];
   Float_t         K0pipi_k0pchi2[50];
   Float_t         K0pipi_k0pPx1[50];
   Float_t         K0pipi_k0pPy1[50];
   Float_t         K0pipi_k0pPz1[50];
   Float_t         K0pipi_k0pPt1[50];
   Float_t         K0pipi_k0pEta1[50];
   Float_t         K0pipi_k0pPx2[50];
   Float_t         K0pipi_k0pPy2[50];
   Float_t         K0pipi_k0pPz2[50];
   Float_t         K0pipi_k0pPt2[50];
   Float_t         K0pipi_k0pEta2[50];
   Int_t           K0pipi_k0pSMT1[50];
   Int_t           K0pipi_k0pSMT2[50];
   Int_t           K0pipi_k0pCFT1[50];
   Int_t           K0pipi_k0pCFT2[50];
   Int_t           K0mumu_k0mnum;
   Int_t           K0mumu_k0mid[50];
   Float_t         K0mumu_k0mMass[50];
   Float_t         K0mumu_k0mPx[50];
   Float_t         K0mumu_k0mPy[50];
   Float_t         K0mumu_k0mPz[50];
   Float_t         K0mumu_k0mPt[50];
   Float_t         K0mumu_k0mEta[50];
   Float_t         K0mumu_k0mdxy[50];
   Float_t         K0mumu_k0mvxy[50];
   Float_t         K0mumu_k0mchi2[50];
   Float_t         K0mumu_k0mPx1[50];
   Float_t         K0mumu_k0mPy1[50];
   Float_t         K0mumu_k0mPz1[50];
   Float_t         K0mumu_k0mPt1[50];
   Float_t         K0mumu_k0mEta1[50];
   Float_t         K0mumu_k0mPx2[50];
   Float_t         K0mumu_k0mPy2[50];
   Float_t         K0mumu_k0mPz2[50];
   Float_t         K0mumu_k0mPt2[50];
   Float_t         K0mumu_k0mEta2[50];
   Int_t           K0mumu_k0mSMT1[50];
   Int_t           K0mumu_k0mSMT2[50];
   Int_t           K0mumu_k0mCFT1[50];
   Int_t           K0mumu_k0mCFT2[50];
   Int_t           K0mumu_k0mu1[50];
   Int_t           K0mumu_k0mu2[50];
   Int_t           K0pimu_k0pmnum;
   Int_t           K0pimu_k0pmid[50];
   Float_t         K0pimu_k0pmMasspm[50];
   Float_t         K0pimu_k0pmMassmp[50];
   Float_t         K0pimu_k0pmPx[50];
   Float_t         K0pimu_k0pmPy[50];
   Float_t         K0pimu_k0pmPz[50];
   Float_t         K0pimu_k0pmPt[50];
   Float_t         K0pimu_k0pmEta[50];
   Float_t         K0pimu_k0pmdxy[50];
   Float_t         K0pimu_k0pmvxy[50];
   Float_t         K0pimu_k0pmchi2[50];
   Float_t         K0pimu_k0pmPx1[50];
   Float_t         K0pimu_k0pmPy1[50];
   Float_t         K0pimu_k0pmPz1[50];
   Float_t         K0pimu_k0pmPt1[50];
   Float_t         K0pimu_k0pmEta1[50];
   Float_t         K0pimu_k0pmPx2[50];
   Float_t         K0pimu_k0pmPy2[50];
   Float_t         K0pimu_k0pmPz2[50];
   Float_t         K0pimu_k0pmPt2[50];
   Float_t         K0pimu_k0pmEta2[50];
   Int_t           K0pimu_k0pmSMT1[50];
   Int_t           K0pimu_k0pmSMT2[50];
   Int_t           K0pimu_k0pmCFT1[50];
   Int_t           K0pimu_k0pmCFT2[50];
   Int_t           K0pimu_k0pmu1[50];
   Int_t           K0pimu_k0pmu2[50];
   Int_t           Info_nTrks;
   Int_t           Info_piQ[500];
   Float_t         Info_piPx[500];
   Float_t         Info_piPy[500];
   Float_t         Info_piPz[500];
   Float_t         Info_piPt[500];
   Float_t         Info_piEta[500];
   Int_t           Info_piSMT[500];
   Int_t           Info_piCFT[500];
   Int_t           Info_run;
   Int_t           Info_evt;
   Float_t         Info_K0PVx;
   Float_t         Info_K0PVy;
   Float_t         Info_K0PVz;
   Int_t           Info_trig[500];
   Int_t           K0dimu_k0dmnum;
   Int_t           K0dimu_k0dmid[50];
   Float_t         K0dimu_k0dmMass[50];
   Float_t         K0dimu_k0dmPx[50];
   Float_t         K0dimu_k0dmPy[50];
   Float_t         K0dimu_k0dmPz[50];
   Float_t         K0dimu_k0dmPt[50];
   Float_t         K0dimu_k0dmEta[50];
   Float_t         K0dimu_k0dmdxy[50];
   Float_t         K0dimu_k0dmvxy[50];
   Float_t         K0dimu_k0dmchi2[50];
   Float_t         K0dimu_k0dmPx1[50];
   Float_t         K0dimu_k0dmPy1[50];
   Float_t         K0dimu_k0dmPz1[50];
   Float_t         K0dimu_k0dmPt1[50];
   Float_t         K0dimu_k0dmEta1[50];
   Float_t         K0dimu_k0dmPx2[50];
   Float_t         K0dimu_k0dmPy2[50];
   Float_t         K0dimu_k0dmPz2[50];
   Float_t         K0dimu_k0dmPt2[50];
   Float_t         K0dimu_k0dmEta2[50];
   Int_t           K0dimu_k0dmSMT1[50];
   Int_t           K0dimu_k0dmSMT2[50];
   Int_t           K0dimu_k0dmCFT1[50];
   Int_t           K0dimu_k0dmCFT2[50];
   Float_t         K0dimu_K0PVx;
   Float_t         K0dimu_K0PVy;
   Float_t         K0dimu_K0PVz;
   Int_t           K0dpimu_k0dpmnum;
   Int_t           K0dpimu_k0dpmid[50];
   Float_t         K0dpimu_k0dpmMasspm[50];
   Float_t         K0dpimu_k0dpmMassmp[50];
   Float_t         K0dpimu_k0dpmPx[50];
   Float_t         K0dpimu_k0dpmPy[50];
   Float_t         K0dpimu_k0dpmPz[50];
   Float_t         K0dpimu_k0dpmPt[50];
   Float_t         K0dpimu_k0dpmEta[50];
   Float_t         K0dpimu_k0dpmdxy[50];
   Float_t         K0dpimu_k0dpmvxy[50];
   Float_t         K0dpimu_k0dpmchi2[50];
   Float_t         K0dpimu_k0dpmPx1[50];
   Float_t         K0dpimu_k0dpmPy1[50];
   Float_t         K0dpimu_k0dpmPz1[50];
   Float_t         K0dpimu_k0dpmPt1[50];
   Float_t         K0dpimu_k0dpmEta1[50];
   Float_t         K0dpimu_k0dpmPx2[50];
   Float_t         K0dpimu_k0dpmPy2[50];
   Float_t         K0dpimu_k0dpmPz2[50];
   Float_t         K0dpimu_k0dpmPt2[50];
   Float_t         K0dpimu_k0dpmEta2[50];
   Int_t           K0dpimu_k0dpmSMT1[50];
   Int_t           K0dpimu_k0dpmSMT2[50];
   Int_t           K0dpimu_k0dpmCFT1[50];
   Int_t           K0dpimu_k0dpmCFT2[50];
   Int_t           K0dpimu_k0dpmm1[50];
   Int_t           K0dpimu_k0dpmm2[50];

   // List of branches
   TBranch        *b_K0pipi;   //!
   TBranch        *b_K0mumu;   //!
   TBranch        *b_K0pimu;   //!
   TBranch        *b_Info;   //!
   TBranch        *b_K0dimu;   //!
   TBranch        *b_K0dpimu;   //!

   kanaD1(TTree *tree=0);
   virtual ~kanaD1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef kanaD1_cxx
kanaD1::kanaD1(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output_ksmumu_set1.root");
      if (!f) {
         f = new TFile("output_ksmumu_set1.root");
      }
      tree = (TTree*)gDirectory->Get("KTree");

   }
   Init(tree);
}

kanaD1::~kanaD1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t kanaD1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t kanaD1::LoadTree(Long64_t entry)
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

void kanaD1::Init(TTree *tree)
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

   fChain->SetBranchAddress("K0pipi",&K0pipi_k0pnum);
   fChain->SetBranchAddress("K0mumu",&K0mumu_k0mnum);
   fChain->SetBranchAddress("K0pimu",&K0pimu_k0pmnum);
   fChain->SetBranchAddress("Info",&Info_nTrks);
   fChain->SetBranchAddress("K0dimu",&K0dimu_k0dmnum);
   fChain->SetBranchAddress("K0dpimu",&K0dpimu_k0dpmnum);
   Notify();
}

Bool_t kanaD1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_K0pipi = fChain->GetBranch("K0pipi");
   b_K0mumu = fChain->GetBranch("K0mumu");
   b_K0pimu = fChain->GetBranch("K0pimu");
   b_Info = fChain->GetBranch("Info");
   b_K0dimu = fChain->GetBranch("K0dimu");
   b_K0dpimu = fChain->GetBranch("K0dpimu");

   return kTRUE;
}

void kanaD1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t kanaD1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef kanaD1_cxx
