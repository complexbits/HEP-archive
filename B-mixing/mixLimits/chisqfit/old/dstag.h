//////////////////////////////////////////////////////////
//   This class has been automatically generated 
//     (Tue Nov 30 15:23:12 2004 by ROOT version3.05/07)
//   from TTree dstagTree/AA Ds
//   found on file: aadstagmc15423.root
//////////////////////////////////////////////////////////


#ifndef dstag_h
#define dstag_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class dstag {
   public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
//Declaration of leaves types
   Int_t           run;
   Int_t           evt;
   Int_t           qmu;
   Int_t           q5;
   Double_t        lv;
   Double_t        vlv;
   Double_t        lxy;
   Double_t        vlxy;
   Double_t        mkk;
   Double_t        mds;
   Double_t        cxyds;
   Double_t        lxyB;
   Double_t        vlxyB;
   Double_t        lxyBD;
   Double_t        vlxyBD;
   Double_t        xmb;
   Double_t        cxyB;
   Double_t        cmud;
   Double_t        ptmu;
   Double_t        ptB;
   Double_t        ptBs;
   Double_t        ptotB;
   Double_t        lb;
   Double_t        pt6;
   Double_t        pto6;
   Double_t        coBtxy;
   Double_t        c26;
   Double_t        coBt;
   Double_t        ptDsMu;
   Double_t        lbmc;
   Int_t           nSMT6;
   Int_t           nCFT6;
   Int_t           q6;
   Int_t           nseg6;
   Int_t           tagmuok;
   Int_t           matchBs;

//List of branches
   TBranch        *b_run;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_qmu;   //!
   TBranch        *b_q5;   //!
   TBranch        *b_lv;   //!
   TBranch        *b_vlv;   //!
   TBranch        *b_lxy;   //!
   TBranch        *b_vlxy;   //!
   TBranch        *b_mkk;   //!
   TBranch        *b_mds;   //!
   TBranch        *b_cxyds;   //!
   TBranch        *b_lxyB;   //!
   TBranch        *b_vlxyB;   //!
   TBranch        *b_lxyBD;   //!
   TBranch        *b_vlxyBD;   //!
   TBranch        *b_xmb;   //!
   TBranch        *b_cxyB;   //!
   TBranch        *b_cmud;   //!
   TBranch        *b_ptmu;   //!
   TBranch        *b_ptB;   //!
   TBranch        *b_ptBs;   //!
   TBranch        *b_ptotB;   //!
   TBranch        *b_lb;   //!
   TBranch        *b_pt6;   //!
   TBranch        *b_pto6;   //!
   TBranch        *b_coBtxy;   //!
   TBranch        *b_c26;   //!
   TBranch        *b_coBt;   //!
   TBranch        *b_ptDsMu;   //!
   TBranch        *b_lbmc;   //!
   TBranch        *b_nSMT6;   //!
   TBranch        *b_nCFT6;   //!
   TBranch        *b_q6;   //!
   TBranch        *b_nseg6;   //!
   TBranch        *b_tagmuok;   //!
   TBranch        *b_matchBs;   //!

   dstag(TTree *tree=0);
   ~dstag();
   Int_t  Cut(Int_t entry);
   Int_t  GetEntry(Int_t entry);
   Int_t  LoadTree(Int_t entry);
   void   Init(TTree *tree);
   void   Loop();
   Bool_t Notify();
   void   Show(Int_t entry = -1);
};

#endif

#ifdef dstag_cxx
dstag::dstag(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("aadstagmc15423.root");
      if (!f) {
         f = new TFile("aadstagmc15423.root");
      }
      tree = (TTree*)gDirectory->Get("dstagTree");

   }
   Init(tree);
}

dstag::~dstag()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dstag::GetEntry(Int_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t dstag::LoadTree(Int_t entry)
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

void dstag::Init(TTree *tree)
{
//   Set branch addresses
   if (tree == 0) return;
   fChain    = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run",&run);
   fChain->SetBranchAddress("evt",&evt);
   fChain->SetBranchAddress("qmu",&qmu);
   fChain->SetBranchAddress("q5",&q5);
   fChain->SetBranchAddress("lv",&lv);
   fChain->SetBranchAddress("vlv",&vlv);
   fChain->SetBranchAddress("lxy",&lxy);
   fChain->SetBranchAddress("vlxy",&vlxy);
   fChain->SetBranchAddress("mkk",&mkk);
   fChain->SetBranchAddress("mds",&mds);
   fChain->SetBranchAddress("cxyds",&cxyds);
   fChain->SetBranchAddress("lxyB",&lxyB);
   fChain->SetBranchAddress("vlxyB",&vlxyB);
   fChain->SetBranchAddress("lxyBD",&lxyBD);
   fChain->SetBranchAddress("vlxyBD",&vlxyBD);
   fChain->SetBranchAddress("xmb",&xmb);
   fChain->SetBranchAddress("cxyB",&cxyB);
   fChain->SetBranchAddress("cmud",&cmud);
   fChain->SetBranchAddress("ptmu",&ptmu);
   fChain->SetBranchAddress("ptB",&ptB);
   fChain->SetBranchAddress("ptBs",&ptBs);
   fChain->SetBranchAddress("ptotB",&ptotB);
   fChain->SetBranchAddress("lb",&lb);
   fChain->SetBranchAddress("pt6",&pt6);
   fChain->SetBranchAddress("pto6",&pto6);
   fChain->SetBranchAddress("coBtxy",&coBtxy);
   fChain->SetBranchAddress("c26",&c26);
   fChain->SetBranchAddress("coBt",&coBt);
   fChain->SetBranchAddress("ptDsMu",&ptDsMu);
   fChain->SetBranchAddress("lbmc",&lbmc);
   fChain->SetBranchAddress("nSMT6",&nSMT6);
   fChain->SetBranchAddress("nCFT6",&nCFT6);
   fChain->SetBranchAddress("q6",&q6);
   fChain->SetBranchAddress("nseg6",&nseg6);
   fChain->SetBranchAddress("tagmuok",&tagmuok);
   fChain->SetBranchAddress("matchBs",&matchBs);
   Notify();
}

Bool_t dstag::Notify()
{
   // Called when loading a new file.
   // Get branch pointers.
   b_run = fChain->GetBranch("run");
   b_evt = fChain->GetBranch("evt");
   b_qmu = fChain->GetBranch("qmu");
   b_q5 = fChain->GetBranch("q5");
   b_lv = fChain->GetBranch("lv");
   b_vlv = fChain->GetBranch("vlv");
   b_lxy = fChain->GetBranch("lxy");
   b_vlxy = fChain->GetBranch("vlxy");
   b_mkk = fChain->GetBranch("mkk");
   b_mds = fChain->GetBranch("mds");
   b_cxyds = fChain->GetBranch("cxyds");
   b_lxyB = fChain->GetBranch("lxyB");
   b_vlxyB = fChain->GetBranch("vlxyB");
   b_lxyBD = fChain->GetBranch("lxyBD");
   b_vlxyBD = fChain->GetBranch("vlxyBD");
   b_xmb = fChain->GetBranch("xmb");
   b_cxyB = fChain->GetBranch("cxyB");
   b_cmud = fChain->GetBranch("cmud");
   b_ptmu = fChain->GetBranch("ptmu");
   b_ptB = fChain->GetBranch("ptB");
   b_ptBs = fChain->GetBranch("ptBs");
   b_ptotB = fChain->GetBranch("ptotB");
   b_lb = fChain->GetBranch("lb");
   b_pt6 = fChain->GetBranch("pt6");
   b_pto6 = fChain->GetBranch("pto6");
   b_coBtxy = fChain->GetBranch("coBtxy");
   b_c26 = fChain->GetBranch("c26");
   b_coBt = fChain->GetBranch("coBt");
   b_ptDsMu = fChain->GetBranch("ptDsMu");
   b_lbmc = fChain->GetBranch("lbmc");
   b_nSMT6 = fChain->GetBranch("nSMT6");
   b_nCFT6 = fChain->GetBranch("nCFT6");
   b_q6 = fChain->GetBranch("q6");
   b_nseg6 = fChain->GetBranch("nseg6");
   b_tagmuok = fChain->GetBranch("tagmuok");
   b_matchBs = fChain->GetBranch("matchBs");
   return kTRUE;
}

void dstag::Show(Int_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dstag::Cut(Int_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef dstag_cxx

