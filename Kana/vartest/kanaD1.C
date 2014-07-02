// File is /raid/data/d0/bphysics/kmumu/output_ksmumu_set1.root
#define kana_v2_cxx
#include "kana_v2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void kana_v2::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L kanaD1.C
//      Root > kanaD1 t
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

TStopwatch timer;
  timer.Start();



   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout << "Entries = " << nentries << endl;

   // Histograms

   // K0pipi branch
   TH1F *hpipiN = new TH1F("hpipiN","Number of K0->pipi",10,0.,10.);
   TH1F *hpipiM = new TH1F("hpipiM","Mass pipi",100, 0.24,0.74);
   TH1F *hpipiPx = new TH1F("hpipiPx","K0 Px, K0->pipi",100, -10.,10.);
   TH1F *hpipiPx1 = new TH1F("hpipiPx1","K0 Px1, K0->pipi",100, -10.,10.);
   TH1F *hpipiPx2 = new TH1F("hpipiPx2","K0 Px2, K0->pipi",100, -10.,10.);
   TH1F *hpipiPy = new TH1F("hpipiPy","K0 Py, K0->pipi",100, -10.,10.);
   TH1F *hpipiPy1 = new TH1F("hpipiPy1","K0 Py1, K0->pipi",100, -10.,10.);
   TH1F *hpipiPy2 = new TH1F("hpipiPy2","K0 Py2, K0->pipi",100, -10.,10.);
   TH1F *hpipiPz = new TH1F("hpipiPz","K0 Pz, K0->pipi",100, -10.,10.);
   TH1F *hpipiPz1 = new TH1F("hpipiPz1","K0 Pz1, K0->pipi",100, -10.,10.);
   TH1F *hpipiPz2 = new TH1F("hpipiPz2","K0 Pz2, K0->pipi",100, -10.,10.);
   TH1F *hpipiPt = new TH1F("hpipiPt","K0 Pt, K0->pipi",100, 0.,.);
   TH1F *hpipiPt1 = new TH1F("hpipiPt1","K0 Pt1, K0->pipi",100, 0.,15.);
   TH1F *hpipiPt2 = new TH1F("hpipiPt2","K0 Pt2, K0->pipi",100, 0.,15.);
   TH1F *hpipiE = new TH1F("hpipiE","K0 Eta, K0->pipi",100, -5.,5.);
   TH1F *hpipiE1 = new TH1F("hpipiE1","K0 Eta1, K0->pipi",100, -5.,5.);
   TH1F *hpipiE2 = new TH1F("hpipiE2","K0 Eta2, K0->pipi",100, -5.,5.);
   TH1F *hpipiV = new TH1F("hpipiV","K0 Vxy, K0->pipi",100, 0.,0.01);
   TH1F *hpipiD = new TH1F("hpipiD","K0 Dxy, K0->pipi",100, 0.,10.);
   TH1F *hpipiPid = new TH1F("hpipiPid", "Pi ID, K0->pipi", 20., 0., 20.);
   TH1F *hpipichi2 = new TH1F("hpipichi2","Chi2, K0->pipi",100,0.,30.);
   TH1F *hpipiSMT1 = new TH1F("hpipiSMT1","SMT1, K0->pipi",20,0.,20.);
   TH1F *hpipiSMT2 = new TH1F("hpipiSMT2","SMT2, K0->pipi",20,0.,20.);
   TH1F *hpipiCFT1 = new TH1F("hpipiCFT1","CFT1, K0->pipi",20,0.,20.);
   TH1F *hpipiCFT2 = new TH1F("hpipiCFT2","CFT2, K0->pipi",20,0.,20.);

   //K0mumu branch
   TH1F *hmumuN = new TH1F("hmumuN","Number of K0->mumu",10,0.,10.);
   TH1F *hmumu1 = new TH1F("hmumu1","k0mu1, K0->mumu",10,0.,10.);
   TH1F *hmumu2 = new TH1F("hmumu2","k0mu2, K0->mumu",10,0.,10.);
   TH1F *hmumuM = new TH1F("hmumuM","Mass mumu",100, 0.,0.74);
   TH1F *hmumuPx = new TH1F("hmumuPx","K0 Px, K0->mumu",100, -10.,10.);
   TH1F *hmumuPx1 = new TH1F("hmumuPx1","K0 Px1, K0->mumu",100, -10.,10.);
   TH1F *hmumuPx2 = new TH1F("hmumuPx2","K0 Px2, K0->mumu",100, -10.,10.);
   TH1F *hmumuPy = new TH1F("hmumuPy","K0 Py, K0->mumu",100, -10.,10.);
   TH1F *hmumuPy1 = new TH1F("hmumuPy1","K0 Py1, K0->mumu",100, -10.,10.);
   TH1F *hmumuPy2 = new TH1F("hmumuPy2","K0 Py2, K0->mumu",100, -10.,10.);
   TH1F *hmumuPz = new TH1F("hmumuPz","K0 Pz, K0->mumu",100, -10.,10.);
   TH1F *hmumuPz1 = new TH1F("hmumuPz1","K0 Pz1, K0->mumu",100, -10.,10.);
   TH1F *hmumuPz2 = new TH1F("hmumuPz2","K0 Pz2, K0->mumu",100, -10.,10.);
   TH1F *hmumuPt = new TH1F("hmumuPt","K0 Pt, K0->mumu",100, 0.,15.);
   TH1F *hmumuPt1 = new TH1F("hmumuPt1","K0 Pt1, K0->mumu",100, 0.,15.);
   TH1F *hmumuPt2 = new TH1F("hmumuPt2","K0 Pt2, K0->mumu",100, 0.,15.);
   TH1F *hmumuE = new TH1F("hmumuE","K0 Eta, K0->mumu",100, -5.,5.);
   TH1F *hmumuE1 = new TH1F("hmumuE1","K0 Eta1, K0->mumu",100, -5.,5.);
   TH1F *hmumuE2 = new TH1F("hmumuE2","K0 Eta2, K0->mumu",100, -5.,5.);
   TH1F *hmumuV = new TH1F("hmumuV","K0 Vxy, K0->mumu",100, 0.,0.01);
   TH1F *hmumuD = new TH1F("hmumuD","K0 Dxy, K0->mumu",100, 0.,1.);
   TH1F *hmumuMid = new TH1F("hmumuMid", "Mu ID, K0->mumu", 20., 0., 20.);
   TH1F *hmumuchi2 = new TH1F("hmumuchi2","Chi2, K0->mumu",100,0.,30.);
   TH1F *hmumuSMT1 = new TH1F("hmumuSMT1","SMT1, K0->mumu",20,0.,20.);
   TH1F *hmumuSMT2 = new TH1F("hmumuSMT2","SMT2, K0->mumu",20,0.,20.);
   TH1F *hmumuCFT1 = new TH1F("hmumuCFT1","CFT1, K0->mumu",20,0.,20.);
   TH1F *hmumuCFT2 = new TH1F("hmumuCFT2","CFT2, K0->mumu",20,0.,20.);


   //K0pimu branch
   TH1F *hpimuN = new TH1F("hpimuN","Number of K0->pimu",10,0.,10.);
   TH1F *hpimu1 = new TH1F("hpimu1","k0pmu1, K0->mumu",10,0.,10.);
   TH1F *hpimu2 = new TH1F("hpimu2","k0pmu2, K0->mumu",10,0.,10.);
   TH1F *hpimuPM = new TH1F("hpimuPM","Mass pimuPM",100, 0.,1.);
   TH1F *hpimuMP = new TH1F("hpimuMP","Mass pimuMP",100, 0.,1.);
   TH1F *hpimuPx = new TH1F("hpimuPx","K0 Px, K0->pimu",100, -10.,10.);
   TH1F *hpimuPx1 = new TH1F("hpimuPx1","K0 Px1, K0->pimu",100, -10.,10.);
   TH1F *hpimuPx2 = new TH1F("hpimuPx2","K0 Px2, K0->pimu",100, -10.,10.);
   TH1F *hpimuPy = new TH1F("hpimuPy","K0 Py, K0->pimu",100, -10.,10.);
   TH1F *hpimuPy1 = new TH1F("hpimuPy1","K0 Py1, K0->pimu",100, -10.,10.);
   TH1F *hpimuPy2 = new TH1F("hpimuPy2","K0 Py2, K0->pimu",100, -10.,10.);
   TH1F *hpimuPz = new TH1F("hpimuPz","K0 Pz, K0->pimu",100, -10.,10.);
   TH1F *hpimuPz1 = new TH1F("hpimuPz1","K0 Pz1, K0->pimu",100, -10.,10.);
   TH1F *hpimuPz2 = new TH1F("hpimuPz2","K0 Pz2, K0->pimu",100, -10.,10.);
   TH1F *hpimuPt = new TH1F("hpimuPt","K0 Pt, K0->pimu",100, 0.,15.);
   TH1F *hpimuPt1 = new TH1F("hpimuPt1","K0 Pt1, K0->pimu",100, 0.,15.);
   TH1F *hpimuPt2 = new TH1F("hpimuPt2","K0 Pt2, K0->pimu",100, 0.,15.);
   TH1F *hpimuE = new TH1F("hpimuE","K0 Eta, K0->pimu",100, -5.,5.);
   TH1F *hpimuE1 = new TH1F("hpimuE1","K0 Eta1, K0->pimu",100, -5.,5.);
   TH1F *hpimuE2 = new TH1F("hpimuE2","K0 Eta2, K0->pimu",100, -5.,5.);
   TH1F *hpimuV = new TH1F("hpimuV","K0 Vxy, K0->pimu",100, 0.,0.01);
   TH1F *hpimuD = new TH1F("hpimuD","K0 Dxy, K0->pimu",100, 0.,10.);
   TH1F *hpimuPMid = new TH1F("hpimuPMid", "PiMu ID, K0->pimu", 20., 0., 20.);
   TH1F *hpimuchi2 = new TH1F("hpimuchi2","Chi2, K0->pimu",100,0.,30.);
   TH1F *hpimuSMT1 = new TH1F("hpimuSMT1","SMT1, K0->pimu",20,0.,20.);
   TH1F *hpimuSMT2 = new TH1F("hpimuSMT2","SMT2, K0->pimu",20,0.,20.);
   TH1F *hpimuCFT1 = new TH1F("hpimuCFT1","CFT1, K0->pimu",20,0.,20.);
   TH1F *hpimuCFT2 = new TH1F("hpimuCFT2","CFT2, K0->pimu",20,0.,20.);


   //K0dimu branch
   TH1F *hdimuN = new TH1F("hdimuN","Number of K0->dimu",10,0.,10.);
   TH1F *hdimu1 = new TH1F("hdimu1","k0dmu1, K0->mumu",10,0.,10.);
   TH1F *hdimu2 = new TH1F("hdimu2","k0dmu2, K0->mumu",10,0.,10.);
   TH1F *hdimuM = new TH1F("hdimuM","Mass dimu",100, 0.,20.);
   TH1F *hdimuPx = new TH1F("hdimuPx","K0 Px, K0->dimu",100, -10.,10.);
   TH1F *hdimuPx1 = new TH1F("hdimuPx1","K0 Px1, K0->dimu",100, -10.,10.);
   TH1F *hdimuPx2 = new TH1F("hdimuPx2","K0 Px2, K0->dimu",100, -10.,10.);
   TH1F *hdimuPy = new TH1F("hdimuPy","K0 Py, K0->dimu",100, -10.,10.);
   TH1F *hdimuPy1 = new TH1F("hdimuPy1","K0 Py1, K0->dimu",100, -10.,10.);
   TH1F *hdimuPy2 = new TH1F("hdimuPy2","K0 Py2, K0->dimu",100, -10.,10.);
   TH1F *hdimuPz = new TH1F("hdimuPz","K0 Pz, K0->dimu",100, -10.,10.);
   TH1F *hdimuPz1 = new TH1F("hdimuPz1","K0 Pz1, K0->dimu",100, -10.,10.);
   TH1F *hdimuPz2 = new TH1F("hdimuPz2","K0 Pz2, K0->dimu",100, -10.,10.);
   TH1F *hdimuPt = new TH1F("hdimuPt","K0 Pt, K0->dimu",100, 0.,15.);
   TH1F *hdimuPt1 = new TH1F("hdimuPt1","K0 Pt1, K0->dimu",100, 0.,15.);
   TH1F *hdimuPt2 = new TH1F("hdimuPt2","K0 Pt2, K0->dimu",100, 0.,15.);
   TH1F *hdimuE = new TH1F("hdimuE","K0 Eta, K0->dimu",100, -5.,5.);
   TH1F *hdimuE1 = new TH1F("hdimuE1","K0 Eta1, K0->dimu",100, -5.,5.);
   TH1F *hdimuE2 = new TH1F("hdimuE2","K0 Eta2, K0->dimu",100, -5.,5.);
   TH1F *hdimuV = new TH1F("hdimuV","K0 Vxy, K0->dimu",100, 0.,0.01);
   TH1F *hdimuD = new TH1F("hdimuD","K0 Dxy, K0->dimu",100, 0.,1.); 
   TH1F *hdimuMid = new TH1F("hdimuMid", "Mu ID, K0->dimu", 20., 0., 20.);
   TH1F *hdimuchi2 = new TH1F("hdimuchi2","Chi2, K0->dimu",100,0.,30.);
   TH1F *hdimuSMT1 = new TH1F("hdimuSMT1","SMT1, K0->dimu",20,0.,20.);
   TH1F *hdimuSMT2 = new TH1F("hdimuSMT2","SMT2, K0->dimu",20,0.,20.);
   TH1F *hdimuCFT1 = new TH1F("hdimuCFT1","CFT1, K0->dimu",20,0.,20.);
   TH1F *hdimuCFT2 = new TH1F("hdimuCFT2","CFT2, K0->dimu",20,0.,20.);


   //K0dpimu branch

   TH1F *hdpimuN = new TH1F("hdpimuN","Number of K0->dpimu",10,0.,10.);
   TH1F *hdpimu1 = new TH1F("hdpimu1","k0dpmm1, K0->mumu",10,0.,10.);
   TH1F *hdpimu2 = new TH1F("hdpimu2","k0dpmm2, K0->mumu",10,0.,10.);
   TH1F *hdpimuPM = new TH1F("hdpimuPM","Mass dpimuPM",100, 0.,20.);
   TH1F *hdpimuMP = new TH1F("hdpimuMP","Mass dpimuMP",100, 0.,20.);
   TH1F *hdpimuPx = new TH1F("hdpimuPx","K0 Px, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPx1 = new TH1F("hdpimuPx1","K0 Px1, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPx2 = new TH1F("hdpimuPx2","K0 Px2, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPy = new TH1F("hdpimuPy","K0 Py, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPy1 = new TH1F("hdpimuPy1","K0 Py1, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPy2 = new TH1F("hdpimuPy2","K0 Py2, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPz = new TH1F("hdpimuPz","K0 Pz, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPz1 = new TH1F("hdpimuPz1","K0 Pz1, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPz2 = new TH1F("hdpimuPz2","K0 Pz2, K0->dpimu",100, -10.,10.);
   TH1F *hdpimuPt = new TH1F("hdpimuPt","K0 Pt, K0->dpimu",100, 0.,15.);
   TH1F *hdpimuPt1 = new TH1F("hdpimuPt1","K0 Pt1, K0->dpimu",100, 0.,15.);
   TH1F *hdpimuPt2 = new TH1F("hdpimuPt2","K0 Pt2, K0->dpimu",100, 0.,15.);
   TH1F *hdpimuE = new TH1F("hdpimuE","K0 Eta, K0->dpimu",100, -5.,5.);
   TH1F *hdpimuE1 = new TH1F("hdpimuE1","K0 Eta1, K0->dpimu",100, -5.,5.);
   TH1F *hdpimuE2 = new TH1F("hdpimuE2","K0 Eta2, K0->dpimu",100, -5.,5.);
   TH1F *hdpimuV = new TH1F("hdpimuV","K0 Vxy, K0->dpimu",100, 0.,0.01);
   TH1F *hdpimuD = new TH1F("hdpimuD","K0 Dxy, K0->dpimu",100, 0.,1.);
   TH1F *hdpimuPMid = new TH1F("hdpimuPMid", "Dpimu ID, K0->dpimu", 50., 0., 50.);
   TH1F *hdpimuchi2 = new TH1F("hdpimuchi2","Chi2, K0->dpimu",100,0.,30.);
   TH1F *hdpimuSMT1 = new TH1F("hdpimuSMT1","SMT1, K0->dpimu",20,0.,20.);
   TH1F *hdpimuSMT2 = new TH1F("hdpimuSMT2","SMT2, K0->dpimu",20,0.,20.);
   TH1F *hdpimuCFT1 = new TH1F("hdpimuCFT1","CFT1, K0->dpimu",20,0.,20.);
   TH1F *hdpimuCFT2 = new TH1F("hdpimuCFT2","CFT2, K0->dpimu",20,0.,20.);


   TH1F *htrigc = new TH1F("htrigc","Number of Triggers Fired",10,0.,10.);
   TH1F *htrigw = new TH1F("htrigw","Frequncy Triggers Fired",32,0.,32.);

   Int_t nbytes = 0, nb = 0;
   cout << "Number of entries = " << nentries << endl;
   //for (Long64_t jentry=0; jentry<1000;jentry++) {
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // Trigger info ************************************
      Int_t tCount = 0;
      for (Int_t iTrig=0; iTrig<500; iTrig++){
	if (Info_trig[iTrig] == 1){
	  tCount++;
	  htrigw->Fill(iTrig);
	  //cout << iTrig << "  " << Info_trig[iTrig] << endl;
	}
	//if (iTrig > 32 && Info_trig[iTrig] == 1 && iTrig != 498){
	if (iTrig > 32 && Info_trig[iTrig] == 1){
	  cout << "Trigger Problem " 
	       << ientry << "  " << iTrig << "  " 
	       <<Info_trig[iTrig] << endl;
	}
      }
      //cout << "Trig fired = " << tCount << endl << endl;
      htrigc->Fill(tCount);
      // End trigger info ********************************

      hpipiN->Fill(K0pipi_k0pnum);
      hmumuN->Fill(K0mumu_k0mnum);
      hpimuN->Fill(K0pimu_k0pmnum);
      hdimuN->Fill(K0dimu_k0dmnum);
      hdpimuN->Fill(K0dpimu_k0dpmnum);


      Int_t k0pipi = K0pipi_k0pnum;
      if (k0pipi > 50) k0pipi = 50;

      Int_t k0mumu = K0mumu_k0mnum;
      if (k0mumu > 50) k0mumu = 50;

      Int_t k0pimu = K0pimu_k0pmnum;
      if (k0pimu > 50) k0pimu = 50;

      Int_t k0dimu = K0dimu_k0dmnum;
      if (k0dimu > 50) k0dimu = 50;

      Int_t k0dpimu = K0dpimu_k0dpmnum;

      // Loop over K0's
      Int_t max1 = TMath::Max(k0pipi,k0pimu);
      Int_t max2 = TMath::Max(k0dimu,k0dpimu);
      Int_t max3 = TMath::Max(max1, max2);
      Int_t mLoop = TMath::Max(max3,k0mumu);


      for (Int_t iLoop=0; iLoop<mLoop; iLoop++){


	if (k0pipi>iLoop){
	  //cout <<jentry << "   " << mLoop <<"   " 
	  //     << iLoop << "   " << K0pipi_k0pMass[iLoop] << endl;
	  hpipiM->Fill(K0pipi_k0pMass[iLoop]);
	  hpipiPx->Fill(K0pipi_k0pPx[iLoop]);
	  hpipiPx1->Fill(K0pipi_k0pPx1[iLoop]);
	  hpipiPx2->Fill(K0pipi_k0pPx2[iLoop]);
	  hpipiPy->Fill(K0pipi_k0pPy[iLoop]);
	  hpipiPy1->Fill(K0pipi_k0pPy1[iLoop]);
	  hpipiPy2->Fill(K0pipi_k0pPy2[iLoop]);
	  hpipiPz->Fill(K0pipi_k0pPz[iLoop]);
	  hpipiPz1->Fill(K0pipi_k0pPz1[iLoop]);
	  hpipiPz2->Fill(K0pipi_k0pPz2[iLoop]);
	  hpipiPt->Fill(K0pipi_k0pPt[iLoop]);
	  hpipiPt1->Fill(K0pipi_k0pPt1[iLoop]);
	  hpipiPt2->Fill(K0pipi_k0pPt2[iLoop]);
	  hpipiE->Fill(K0pipi_k0pEta[iLoop]);
	  hpipiE1->Fill(K0pipi_k0pEta1[iLoop]);
	  hpipiE2->Fill(K0pipi_k0pEta2[iLoop]);
	  hpipiV->Fill(K0pipi_k0pvxy[iLoop]);
	  hpipiD->Fill(K0pipi_k0pdxy[iLoop]);
	  hpipiPid->Fill(K0pipi_k0pid[iLoop]);
	  hpipichi2->Fill(K0pipi_k0pchi2[iLoop]);
	  hpipiSMT1->Fill(K0pipi_k0pSMT1[iLoop]);
	  hpipiSMT2->Fill(K0pipi_k0pSMT2[iLoop]);
	  hpipiCFT1->Fill(K0pipi_k0pCFT1[iLoop]);
	  hpipiCFT2->Fill(K0pipi_k0pCFT2[iLoop]);
	}



	if (k0mumu>iLoop){
	  hmumu1->Fill(K0mumu_k0mu1[iLoop]);
	  hmumu2->Fill(K0mumu_k0mu2[iLoop]);
	  hmumuM->Fill(K0mumu_k0mMass[iLoop]);
	  hmumuPx->Fill(K0mumu_k0mPx[iLoop]);
	  hmumuPx1->Fill(K0mumu_k0mPx1[iLoop]);
	  hmumuPx2->Fill(K0mumu_k0mPx2[iLoop]);
	  hmumuPy->Fill(K0mumu_k0mPy[iLoop]);
	  hmumuPy1->Fill(K0mumu_k0mPy1[iLoop]);
	  hmumuPy2->Fill(K0mumu_k0mPy2[iLoop]);
	  hmumuPz->Fill(K0mumu_k0mPz[iLoop]);
	  hmumuPz1->Fill(K0mumu_k0mPz1[iLoop]);
	  hmumuPz2->Fill(K0mumu_k0mPz2[iLoop]);
	  hmumuPt->Fill(K0mumu_k0mPt[iLoop]);
	  hmumuPt1->Fill(K0mumu_k0mPt1[iLoop]);
	  hmumuPt2->Fill(K0mumu_k0mPt2[iLoop]);
	  hmumuE->Fill(K0mumu_k0mEta[iLoop]);
	  hmumuE1->Fill(K0mumu_k0mEta1[iLoop]);
	  hmumuE2->Fill(K0mumu_k0mEta2[iLoop]);
	  hmumuV->Fill(K0mumu_k0mvxy[iLoop]);
	  hmumuD->Fill(K0mumu_k0mdxy[iLoop]);
	  hmumuMid->Fill(K0mumu_k0mid[iLoop]);
	  hmumuchi2->Fill(K0mumu_k0mchi2[iLoop]);
	  hmumuSMT1->Fill(K0mumu_k0mSMT1[iLoop]);
	  hmumuSMT2->Fill(K0mumu_k0mSMT2[iLoop]);
	  hmumuCFT1->Fill(K0mumu_k0mCFT1[iLoop]);
	  hmumuCFT2->Fill(K0mumu_k0mCFT2[iLoop]);
	}



	if (k0pimu>iLoop){
	  hpimu1->Fill(K0pimu_k0pmu1[iLoop]);
	  hpimu2->Fill(K0pimu_k0pmu2[iLoop]);
	  hpimuPM->Fill(K0pimu_k0pmMasspm[iLoop]);
	  hpimuMP->Fill(K0pimu_k0pmMassmp[iLoop]);
	  hpimuPx->Fill(K0pimu_k0pmPx[iLoop]);
	  hpimuPx1->Fill(K0pimu_k0pmPx1[iLoop]);
	  hpimuPx2->Fill(K0pimu_k0pmPx2[iLoop]);
	  hpimuPy->Fill(K0pimu_k0pmPy[iLoop]);
	  hpimuPy1->Fill(K0pimu_k0pmPy1[iLoop]);
	  hpimuPy2->Fill(K0pimu_k0pmPy2[iLoop]);
	  hpimuPz->Fill(K0pimu_k0pmPz[iLoop]);
	  hpimuPz1->Fill(K0pimu_k0pmPz1[iLoop]);
	  hpimuPz2->Fill(K0pimu_k0pmPz2[iLoop]);
	  hpimuPt->Fill(K0pimu_k0pmPt[iLoop]);
	  hpimuPt1->Fill(K0pimu_k0pmPt1[iLoop]);
	  hpimuPt2->Fill(K0pimu_k0pmPt2[iLoop]);
	  hpimuE->Fill(K0pimu_k0pmEta[iLoop]);
	  hpimuE1->Fill(K0pimu_k0pmEta1[iLoop]);
	  hpimuE2->Fill(K0pimu_k0pmEta2[iLoop]);
	  hpimuV->Fill(K0pimu_k0pmvxy[iLoop]);
	  hpimuD->Fill(K0pimu_k0pmdxy[iLoop]);
	  hpimuPMid->Fill(K0pimu_k0pmid[iLoop]);
	  hpimuchi2->Fill(K0pimu_k0pmchi2[iLoop]);
	  hpimuSMT1->Fill(K0pimu_k0pmSMT1[iLoop]);
	  hpimuSMT2->Fill(K0pimu_k0pmSMT2[iLoop]);
	  hpimuCFT1->Fill(K0pimu_k0pmCFT1[iLoop]);
	  hpimuCFT2->Fill(K0pimu_k0pmCFT2[iLoop]);

	}



	if (k0dimu>iLoop){
	  hdimu1->Fill(K0dimu_k0dmu1[iLoop]);
	  hdimu2->Fill(K0dimu_k0dmu2[iLoop]);
	  hdimuM->Fill(K0dimu_k0dmMass[iLoop]);
	  hdimuPx->Fill(K0dimu_k0dmPx[iLoop]);
	  hdimuPx1->Fill(K0dimu_k0dmPx1[iLoop]);
	  hdimuPx2->Fill(K0dimu_k0dmPx2[iLoop]);
	  hdimuPy->Fill(K0dimu_k0dmPy[iLoop]);
	  hdimuPy1->Fill(K0dimu_k0dmPy1[iLoop]);
	  hdimuPy2->Fill(K0dimu_k0dmPy2[iLoop]);
	  hdimuPz->Fill(K0dimu_k0dmPz[iLoop]);
	  hdimuPz1->Fill(K0dimu_k0dmPz1[iLoop]);
	  hdimuPz2->Fill(K0dimu_k0dmPz2[iLoop]);
	  hdimuPt->Fill(K0dimu_k0dmPt[iLoop]);
	  hdimuPt1->Fill(K0dimu_k0dmPt1[iLoop]);
	  hdimuPt2->Fill(K0dimu_k0dmPt2[iLoop]);
	  hdimuE->Fill(K0dimu_k0dmEta[iLoop]);
	  hdimuE1->Fill(K0dimu_k0dmEta1[iLoop]);
	  hdimuE2->Fill(K0dimu_k0dmEta2[iLoop]);
	  hdimuV->Fill(K0dimu_k0dmvxy[iLoop]);
	  hdimuD->Fill(K0dimu_k0dmdxy[iLoop]);
	  hdimuMid->Fill(K0dimu_k0dmid[iLoop]);
	  hdimuchi2->Fill(K0dimu_k0dmchi2[iLoop]);
	  hdimuSMT1->Fill(K0dimu_k0dmSMT1[iLoop]);
	  hdimuSMT2->Fill(K0dimu_k0dmSMT2[iLoop]);
	  hdimuCFT1->Fill(K0dimu_k0dmCFT1[iLoop]);
	  hdimuCFT2->Fill(K0dimu_k0dmCFT2[iLoop]);

	}



	if (k0dpimu>iLoop){
	  hdpimu1->Fill(K0dpimu_k0dpmm1[iLoop]);
	  hdpimu2->Fill(K0dpimu_k0dpmm2[iLoop]);
	  hdpimuPM->Fill(K0dpimu_k0dpmMasspm[iLoop]);
	  hdpimuMP->Fill(K0dpimu_k0dpmMassmp[iLoop]);
	  hdpimuPx->Fill(K0dpimu_k0dpmPx[iLoop]);
	  hdpimuPx1->Fill(K0dpimu_k0dpmPx1[iLoop]);
	  hdpimuPx2->Fill(K0dpimu_k0dpmPx2[iLoop]);
	  hdpimuPy->Fill(K0dpimu_k0dpmPy[iLoop]);
	  hdpimuPy1->Fill(K0dpimu_k0dpmPy1[iLoop]);
	  hdpimuPy2->Fill(K0dpimu_k0dpmPy2[iLoop]);
	  hdpimuPz->Fill(K0dpimu_k0dpmPz[iLoop]);
	  hdpimuPz1->Fill(K0dpimu_k0dpmPz1[iLoop]);
	  hdpimuPz2->Fill(K0dpimu_k0dpmPz2[iLoop]);
	  hdpimuPt->Fill(K0dpimu_k0dpmPt[iLoop]);
	  hdpimuPt1->Fill(K0dpimu_k0dpmPt1[iLoop]);
	  hdpimuPt2->Fill(K0dpimu_k0dpmPt2[iLoop]);
	  hdpimuE->Fill(K0dpimu_k0dpmEta[iLoop]);
	  hdpimuE1->Fill(K0dpimu_k0dpmEta1[iLoop]);
	  hdpimuE2->Fill(K0dpimu_k0dpmEta2[iLoop]);
	  hdpimuV->Fill(K0dpimu_k0dpmvxy[iLoop]);
	  hdpimuD->Fill(K0dpimu_k0dpmdxy[iLoop]);
	  hdpimuPMid->Fill(K0dpimu_k0dpmid[iLoop]);
	  hdpimuchi2->Fill(K0dpimu_k0dpmchi2[iLoop]);
	  hdpimuSMT1->Fill(K0dpimu_k0dpmSMT1[iLoop]);
	  hdpimuSMT2->Fill(K0dpimu_k0dpmSMT2[iLoop]);
	  hdpimuCFT1->Fill(K0dpimu_k0dpmCFT1[iLoop]);
	  hdpimuCFT2->Fill(K0dpimu_k0dpmCFT2[iLoop]);
	}

      }
   }

   // Draw all the histograms

   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(111111);

   TCanvas *cpipi = new TCanvas("cpipi", "K0pipi", 900, 600);
   cpipi->Divide(3,2);
   
   cpipi->cd(1);
   hpipiM->Draw();

   cpipi->cd(2);
   hpipiPx->Draw();

   cpipi->cd(3);
   hpipiPy->Draw();   

   cpipi->cd(4);
   hpipiPt->Draw();

   cpipi->cd(5);
   hpipiE->Draw();

   cpipi->cd(6);
   hpipiV->Draw();

   cpipi->Print("K0pipi.ps");


   TCanvas *cmumu = new TCanvas("cmumu", "K0mumu", 1200, 600);
   cmumu->Divide(4,2);
   
   cmumu->cd(1);
   hmumuM->Draw();

   cmumu->cd(2);
   hmumuPx->Draw();

   cmumu->cd(3);
   hmumuPy->Draw();   

   cmumu->cd(4);
   hmumuPt->Draw();

   cmumu->cd(5);
   hmumuE->Draw();

   cmumu->cd(6);
   hmumuV->Draw();

   cmumu->cd(7);
   hmumu1->Draw();

   cmumu->cd(8);
   hmumu2->Draw();

   cmumu->Print("K0mumu.ps");


   TCanvas *cpimu = new TCanvas("cpimu", "K0pimu", 900, 600);
   cpimu->Divide(3,2);
   
   cpimu->cd(1);
   hpimuMP->Draw();
   hpimuPM->Draw("same");

   cpimu->cd(2);
   hpimuPx->Draw();

   cpimu->cd(3);
   hpimuPy->Draw();   

   cpimu->cd(4);
   hpimuPt->Draw();

   cpimu->cd(5);
   hpimuE->Draw();

   cpimu->cd(6);
   hpimuV->Draw();

   cpimu->Print("K0pimu.ps");


   TCanvas *cdimu = new TCanvas("cdimu", "K0dimu", 900, 600);
   cdimu->Divide(3,2);
   
   cdimu->cd(1);
   hdimuM->Draw();

   cdimu->cd(2);
   hdimuPx->Draw();

   cdimu->cd(3);
   hdimuPy->Draw();   

   cdimu->cd(4);
   hdimuPt->Draw();

   cdimu->cd(5);
   hdimuE->Draw();

   cdimu->cd(6);
   hdimuV->Draw();

   cdimu->Print("K0dimu.ps");


   TCanvas *cdpimu = new TCanvas("cdpimu", "K0dpimu", 900, 600);
   cdpimu->Divide(3,2);

   cdpimu->cd(1);
   hdpimuMP->Draw();
   hdpimuPM->Draw("same");

   cdpimu->cd(2);
   hdpimuPx->Draw();

   cdpimu->cd(3);
   hdpimuPy->Draw();   

   cdpimu->cd(4);
   hdpimuPt->Draw();

   cdpimu->cd(5);
   hdpimuE->Draw();

   cdpimu->cd(6);
   hdpimuV->Draw();

   cdpimu->Print("K0dpimu.ps");


   // Create an Array to hold everything

   TObjArray *a1 = new TObjArray(0);

   a1->Add(hpipiM);
   a1->Add(hpipiPx);
   a1->Add(hpipiPx1);
   a1->Add(hpipiPx2);
   a1->Add(hpipiPy);
   a1->Add(hpipiPy1);
   a1->Add(hpipiPy2);
   a1->Add(hpipiPz);
   a1->Add(hpipiPz1);
   a1->Add(hpipiPz2);
   a1->Add(hpipiPt);
   a1->Add(hpipiPt1);
   a1->Add(hpipiPt2);
   a1->Add(hpipiE);
   a1->Add(hpipiE1);
   a1->Add(hpipiE2);
   a1->Add(hpipiV);
   a1->Add(hpipiD);
   a1->Add(hpipiPid);
   a1->Add(hpipiSMT1);
   a1->Add(hpipiSMT2);
   a1->Add(hpipiCFT1);
   a1->Add(hpipiCFT2);
   a1->Add(hpipichi2);

   a1->Add(cpipi);

   a1->Add(hmumuM);
   a1->Add(hmumuPx);
   a1->Add(hmumuPx1);
   a1->Add(hmumuPx2);
   a1->Add(hmumuPy);
   a1->Add(hmumuPy1);
   a1->Add(hmumuPy2);
   a1->Add(hmumuPz);
   a1->Add(hmumuPz1);
   a1->Add(hmumuPz2);
   a1->Add(hmumuPt);
   a1->Add(hmumuPt1);
   a1->Add(hmumuPt2);
   a1->Add(hmumuE);
   a1->Add(hmumuE1);
   a1->Add(hmumuE2);
   a1->Add(hmumuV);
   a1->Add(hmumuD);
   a1->Add(hmumuMid);
   a1->Add(hmumuSMT1);
   a1->Add(hmumuSMT2);
   a1->Add(hmumuCFT1);
   a1->Add(hmumuCFT2);
   a1->Add(hmumuchi2);
   a1->Add(hmumu1);
   a1->Add(hmumu2);

   a1->Add(cmumu);

   a1->Add(hpimuMP);
   a1->Add(hpimuPM);
   a1->Add(hpimuPx);
   a1->Add(hpimuPx1);
   a1->Add(hpimuPx2);
   a1->Add(hpimuPy);
   a1->Add(hpimuPy1);
   a1->Add(hpimuPy2);
   a1->Add(hpimuPz);
   a1->Add(hpimuPz1);
   a1->Add(hpimuPz2);
   a1->Add(hpimuPt);
   a1->Add(hpimuPt1);
   a1->Add(hpimuPt2);
   a1->Add(hpimuE);
   a1->Add(hpimuE1);
   a1->Add(hpimuE2);
   a1->Add(hpimuV);
   a1->Add(hpimuD);
   a1->Add(hpimuPMid);
   a1->Add(hpimuSMT1);
   a1->Add(hpimuSMT2);
   a1->Add(hpimuCFT1);
   a1->Add(hpimuCFT2);
   a1->Add(hpimuchi2);
   a1->Add(hpimu1);
   a1->Add(hpimu2);

   a1->Add(cpimu);

   a1->Add(hdimuM);
   a1->Add(hdimuPx);
   a1->Add(hdimuPx1);
   a1->Add(hdimuPx2);
   a1->Add(hdimuPy);
   a1->Add(hdimuPy1);
   a1->Add(hdimuPy2);
   a1->Add(hdimuPz);
   a1->Add(hdimuPz1);
   a1->Add(hdimuPz2);
   a1->Add(hdimuPt);
   a1->Add(hdimuPt1);
   a1->Add(hdimuPt2);
   a1->Add(hdimuE);
   a1->Add(hdimuE1);
   a1->Add(hdimuE2);
   a1->Add(hdimuV);
   a1->Add(hdimuD);
   a1->Add(hdimuMid);
   a1->Add(hdimuSMT1);
   a1->Add(hdimuSMT2);
   a1->Add(hdimuCFT1);
   a1->Add(hdimuCFT2);
   a1->Add(hdimuchi2);
   a1->Add(hdimu1);
   a1->Add(hdimu2);

   a1->Add(cdimu);

   a1->Add(hdpimuMP);
   a1->Add(hdpimuPM);
   a1->Add(hdpimuPx);
   a1->Add(hdpimuPx1);
   a1->Add(hdpimuPx2);
   a1->Add(hdpimuPy);
   a1->Add(hdpimuPy1);
   a1->Add(hdpimuPy2);
   a1->Add(hdpimuPz);
   a1->Add(hdpimuPz1);
   a1->Add(hdpimuPz2);
   a1->Add(hdpimuPt);
   a1->Add(hdpimuPt1);
   a1->Add(hdpimuPt2);
   a1->Add(hdpimuE);
   a1->Add(hdpimuE1);
   a1->Add(hdpimuE2);
   a1->Add(hdpimuV);
   a1->Add(hdpimuD);
   a1->Add(hdpimuPMid);
   a1->Add(hdpimuSMT1);
   a1->Add(hdpimuSMT2);
   a1->Add(hdpimuCFT1);
   a1->Add(hdpimuCFT2);
   a1->Add(hdpimuchi2);
   a1->Add(hdpimu1);
   a1->Add(hdpimu2);

   a1->Add(cdpimu);



   // Write the array out to a file

   TFile *f1 = new TFile("histograms.root", "recreate");
   a1->Write();
   f1->Close();
   
   timer.Stop();
   Double_t realTime = timer.RealTime();
   Double_t Hours = realTime/3600.;
   Double_t cpuTime = timer.CpuTime();
   printf("\n\n Real Time= %d ( %d Hours)\n\n", realTime, Hours);
   printf("\n\n CPU Time= %d \n\n", cpuTime);



}
