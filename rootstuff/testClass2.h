//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 29 20:43:09 2004 by ROOT version 4.00/02
// from TTree T/An example of a ROOT tree
// found on file: Event.root
//////////////////////////////////////////////////////////

#ifndef testClass2_h
#define testClass2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxfTracks = 615;

class testClass2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Char_t          fType[20];
   Int_t           fNtrack;
   Int_t           fNseg;
   Int_t           fNvertex;
   UInt_t          fFlag;
   Double32_t      fTemperature;
   Int_t           fMeasures[10];
   Double32_t      fMatrix[4][4];
   Double32_t      fClosestDistance[20];   //[fNvertex]
   Int_t           fEvtHdr_fEvtNum;
   Int_t           fEvtHdr_fRun;
   Int_t           fEvtHdr_fDate;
   Int_t           fTracks_;
   UInt_t          fTracks_fUniqueID[kMaxfTracks];   //[fTracks_]
   UInt_t          fTracks_fBits[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fPx[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fPy[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fPz[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fRandom[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fMass2[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fBx[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fBy[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fMeanCharge[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fXfirst[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fXlast[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fYfirst[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fYlast[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fZfirst[kMaxfTracks];   //[fTracks_]
   Float_t         fTracks_fZlast[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_fCharge[kMaxfTracks];   //[fTracks_]
   Double32_t      fTracks_fVertex[kMaxfTracks][3];   //[fTracks_]
   Int_t           fTracks_fNpoint[kMaxfTracks];   //[fTracks_]
   Short_t         fTracks_fValid[kMaxfTracks];   //[fTracks_]
   Int_t           fTracks_fNsp[kMaxfTracks];   //[fTracks_]
   Double32_t     *fTracks_fPointValue[kMaxfTracks];   //[fTracks_fNsp]
   TBits           fTracks_fTriggerBits[kMaxfTracks];
   TRef            fLastTrack;
   TRef            fWebHistogram;
   UInt_t          fTriggerBits_fUniqueID;
   UInt_t          fTriggerBits_fBits;
   UInt_t          fTriggerBits_fNbits;
   UInt_t          fTriggerBits_fNbytes;
   UChar_t         fTriggerBits_fAllBits[0];   //[fTriggerBits.fNbytes]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_fType;   //!
   TBranch        *b_event_fNtrack;   //!
   TBranch        *b_event_fNseg;   //!
   TBranch        *b_event_fNvertex;   //!
   TBranch        *b_event_fFlag;   //!
   TBranch        *b_event_fTemperature;   //!
   TBranch        *b_event_fMeasures;   //!
   TBranch        *b_event_fMatrix;   //!
   TBranch        *b_fClosestDistance;   //!
   TBranch        *b_event_fEvtHdr_fEvtNum;   //!
   TBranch        *b_event_fEvtHdr_fRun;   //!
   TBranch        *b_event_fEvtHdr_fDate;   //!
   TBranch        *b_event_fTracks_;   //!
   TBranch        *b_fTracks_fUniqueID;   //!
   TBranch        *b_fTracks_fBits;   //!
   TBranch        *b_fTracks_fPx;   //!
   TBranch        *b_fTracks_fPy;   //!
   TBranch        *b_fTracks_fPz;   //!
   TBranch        *b_fTracks_fRandom;   //!
   TBranch        *b_fTracks_fMass2;   //!
   TBranch        *b_fTracks_fBx;   //!
   TBranch        *b_fTracks_fBy;   //!
   TBranch        *b_fTracks_fMeanCharge;   //!
   TBranch        *b_fTracks_fXfirst;   //!
   TBranch        *b_fTracks_fXlast;   //!
   TBranch        *b_fTracks_fYfirst;   //!
   TBranch        *b_fTracks_fYlast;   //!
   TBranch        *b_fTracks_fZfirst;   //!
   TBranch        *b_fTracks_fZlast;   //!
   TBranch        *b_fTracks_fCharge;   //!
   TBranch        *b_fTracks_fVertex;   //!
   TBranch        *b_fTracks_fNpoint;   //!
   TBranch        *b_fTracks_fValid;   //!
   TBranch        *b_fTracks_fNsp;   //!
   TBranch        *b_fTracks_fPointValue;   //!
   TBranch        *b_fTracks_fTriggerBits;   //!
   TBranch        *b_event_fLastTrack;   //!
   TBranch        *b_event_fWebHistogram;   //!
   TBranch        *b_event_fTriggerBits_fUniqueID;   //!
   TBranch        *b_event_fTriggerBits_fBits;   //!
   TBranch        *b_event_fTriggerBits_fNbits;   //!
   TBranch        *b_event_fTriggerBits_fNbytes;   //!
   TBranch        *b_fTriggerBits_fAllBits;   //!

   testClass2(TTree *tree=0);
   ~testClass2();
   Int_t  Cut(Int_t entry);
   Int_t  GetEntry(Int_t entry);
   Int_t  LoadTree(Int_t entry);
   void   Init(TTree *tree);
   void   Loop();
   Bool_t Notify();
   void   Show(Int_t entry = -1);
};

#endif

#ifdef testClass2_cxx
testClass2::testClass2(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Event.root");
      if (!f) {
         f = new TFile("Event.root");
      }
      tree = (TTree*)gDirectory->Get("T");

   }
   Init(tree);
}

testClass2::~testClass2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t testClass2::GetEntry(Int_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t testClass2::LoadTree(Int_t entry)
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

void testClass2::Init(TTree *tree)
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

   fChain->SetBranchAddress("fUniqueID",&fUniqueID);
   fChain->SetBranchAddress("fBits",&fBits);
   fChain->SetBranchAddress("fType[20]",fType);
   fChain->SetBranchAddress("fNtrack",&fNtrack);
   fChain->SetBranchAddress("fNseg",&fNseg);
   fChain->SetBranchAddress("fNvertex",&fNvertex);
   fChain->SetBranchAddress("fFlag",&fFlag);
   fChain->SetBranchAddress("fTemperature",&fTemperature);
   fChain->SetBranchAddress("fMeasures[10]",fMeasures);
   fChain->SetBranchAddress("fMatrix[4][4]",fMatrix);
   fChain->SetBranchAddress("fClosestDistance",fClosestDistance);
   fChain->SetBranchAddress("fEvtHdr.fEvtNum",&fEvtHdr_fEvtNum);
   fChain->SetBranchAddress("fEvtHdr.fRun",&fEvtHdr_fRun);
   fChain->SetBranchAddress("fEvtHdr.fDate",&fEvtHdr_fDate);
   fChain->SetBranchAddress("fTracks",&fTracks_);
   fChain->SetBranchAddress("fTracks.fUniqueID",fTracks_fUniqueID);
   fChain->SetBranchAddress("fTracks.fBits",fTracks_fBits);
   fChain->SetBranchAddress("fTracks.fPx",fTracks_fPx);
   fChain->SetBranchAddress("fTracks.fPy",fTracks_fPy);
   fChain->SetBranchAddress("fTracks.fPz",fTracks_fPz);
   fChain->SetBranchAddress("fTracks.fRandom",fTracks_fRandom);
   fChain->SetBranchAddress("fTracks.fMass2",fTracks_fMass2);
   fChain->SetBranchAddress("fTracks.fBx",fTracks_fBx);
   fChain->SetBranchAddress("fTracks.fBy",fTracks_fBy);
   fChain->SetBranchAddress("fTracks.fMeanCharge",fTracks_fMeanCharge);
   fChain->SetBranchAddress("fTracks.fXfirst",fTracks_fXfirst);
   fChain->SetBranchAddress("fTracks.fXlast",fTracks_fXlast);
   fChain->SetBranchAddress("fTracks.fYfirst",fTracks_fYfirst);
   fChain->SetBranchAddress("fTracks.fYlast",fTracks_fYlast);
   fChain->SetBranchAddress("fTracks.fZfirst",fTracks_fZfirst);
   fChain->SetBranchAddress("fTracks.fZlast",fTracks_fZlast);
   fChain->SetBranchAddress("fTracks.fCharge",fTracks_fCharge);
   fChain->SetBranchAddress("fTracks.fVertex[3]",fTracks_fVertex);
   fChain->SetBranchAddress("fTracks.fNpoint",fTracks_fNpoint);
   fChain->SetBranchAddress("fTracks.fValid",fTracks_fValid);
   fChain->SetBranchAddress("fTracks.fNsp",fTracks_fNsp);
   fChain->SetBranchAddress("fTracks.fPointValue",fTracks_fPointValue);
   fChain->SetBranchAddress("fTracks.fTriggerBits",fTracks_fTriggerBits);
   fChain->SetBranchAddress("fLastTrack",&fLastTrack);
   fChain->SetBranchAddress("fWebHistogram",&fWebHistogram);
   fChain->SetBranchAddress("fTriggerBits.fUniqueID",&fTriggerBits_fUniqueID);
   fChain->SetBranchAddress("fTriggerBits.fBits",&fTriggerBits_fBits);
   fChain->SetBranchAddress("fTriggerBits.fNbits",&fTriggerBits_fNbits);
   fChain->SetBranchAddress("fTriggerBits.fNbytes",&fTriggerBits_fNbytes);
   fChain->SetBranchAddress("fTriggerBits.fAllBits",&fTriggerBits_fAllBits);
   Notify();
}

Bool_t testClass2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_event_fUniqueID = fChain->GetBranch("fUniqueID");
   b_event_fBits = fChain->GetBranch("fBits");
   b_event_fType = fChain->GetBranch("fType[20]");
   b_event_fNtrack = fChain->GetBranch("fNtrack");
   b_event_fNseg = fChain->GetBranch("fNseg");
   b_event_fNvertex = fChain->GetBranch("fNvertex");
   b_event_fFlag = fChain->GetBranch("fFlag");
   b_event_fTemperature = fChain->GetBranch("fTemperature");
   b_event_fMeasures = fChain->GetBranch("fMeasures[10]");
   b_event_fMatrix = fChain->GetBranch("fMatrix[4][4]");
   b_fClosestDistance = fChain->GetBranch("fClosestDistance");
   b_event_fEvtHdr_fEvtNum = fChain->GetBranch("fEvtHdr.fEvtNum");
   b_event_fEvtHdr_fRun = fChain->GetBranch("fEvtHdr.fRun");
   b_event_fEvtHdr_fDate = fChain->GetBranch("fEvtHdr.fDate");
   b_event_fTracks_ = fChain->GetBranch("fTracks");
   b_fTracks_fUniqueID = fChain->GetBranch("fTracks.fUniqueID");
   b_fTracks_fBits = fChain->GetBranch("fTracks.fBits");
   b_fTracks_fPx = fChain->GetBranch("fTracks.fPx");
   b_fTracks_fPy = fChain->GetBranch("fTracks.fPy");
   b_fTracks_fPz = fChain->GetBranch("fTracks.fPz");
   b_fTracks_fRandom = fChain->GetBranch("fTracks.fRandom");
   b_fTracks_fMass2 = fChain->GetBranch("fTracks.fMass2");
   b_fTracks_fBx = fChain->GetBranch("fTracks.fBx");
   b_fTracks_fBy = fChain->GetBranch("fTracks.fBy");
   b_fTracks_fMeanCharge = fChain->GetBranch("fTracks.fMeanCharge");
   b_fTracks_fXfirst = fChain->GetBranch("fTracks.fXfirst");
   b_fTracks_fXlast = fChain->GetBranch("fTracks.fXlast");
   b_fTracks_fYfirst = fChain->GetBranch("fTracks.fYfirst");
   b_fTracks_fYlast = fChain->GetBranch("fTracks.fYlast");
   b_fTracks_fZfirst = fChain->GetBranch("fTracks.fZfirst");
   b_fTracks_fZlast = fChain->GetBranch("fTracks.fZlast");
   b_fTracks_fCharge = fChain->GetBranch("fTracks.fCharge");
   b_fTracks_fVertex = fChain->GetBranch("fTracks.fVertex[3]");
   b_fTracks_fNpoint = fChain->GetBranch("fTracks.fNpoint");
   b_fTracks_fValid = fChain->GetBranch("fTracks.fValid");
   b_fTracks_fNsp = fChain->GetBranch("fTracks.fNsp");
   b_fTracks_fPointValue = fChain->GetBranch("fTracks.fPointValue");
   b_fTracks_fTriggerBits = fChain->GetBranch("fTracks.fTriggerBits");
   b_event_fLastTrack = fChain->GetBranch("fLastTrack");
   b_event_fWebHistogram = fChain->GetBranch("fWebHistogram");
   b_event_fTriggerBits_fUniqueID = fChain->GetBranch("fTriggerBits.fUniqueID");
   b_event_fTriggerBits_fBits = fChain->GetBranch("fTriggerBits.fBits");
   b_event_fTriggerBits_fNbits = fChain->GetBranch("fTriggerBits.fNbits");
   b_event_fTriggerBits_fNbytes = fChain->GetBranch("fTriggerBits.fNbytes");
   b_fTriggerBits_fAllBits = fChain->GetBranch("fTriggerBits.fAllBits");

   return kTRUE;
}

void testClass2::Show(Int_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t testClass2::Cut(Int_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef testClass2_cxx
