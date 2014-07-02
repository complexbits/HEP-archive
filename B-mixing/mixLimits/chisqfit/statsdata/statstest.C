#define statstest_cxx
#include "statstest.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void statstest::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L statstest.C
//      Root > statstest t
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

   Long64_t nentries = fChain->GetEntriesFast();

   Int_t nbytes = 0, nb = 0;


   /********************************************************/

   TH1F *h_mass1 = new TH1F("h_mass1", "Reconstructd mass of Bs: 2.6-3.6", 40, 2.6, 3.6);
   TH1F *h_mass2 = new TH1F("h_mass2", "Reconstructed mass of Bs: 3.6-4.6", 40, 3.6, 4.6);
   TH1F *h_mom1 = new TH1F("h_mom1", "Total momentum of Bs: 10-40", 40, 10, 40);
   TH1F *h_mom2 = new TH1F("h_mom2", "Transverse momentum of Reco Bs: 10-40", 40, 10, 40);
   TH1F *h_mom3 = new TH1F("h_mom3", "Transverse momentum of MC Bs: 10-40", 40, 10, 40);
   TH1F *h_cos1 = new TH1F("h_cos1", "Cos of angle between mu and Ds: 0.8-1", 40, 0.8, 1);
   TH1F *h_mom4 = new TH1F("h_mom4", "Transverse momentum of tagging muon: 2-6", 40, 2, 6);
   TH1F *h_lt = new TH1F("h_lt", "Lifetime of Bs: 0-0.2", 40, 0, 0.2); 

   /********************************************************/



   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      /********************************************************/
      //Fill the histograms with the data//

      h_mass1->Fill(xmb);
      h_mass2->Fill(xmb);
      h_mom1->Fill(ptotB);
      h_mom2->Fill(ptB);
      h_mom3->Fill(ptBs);
      h_cos1->Fill(cmud);
      h_mom4->Fill(ptmu);
      h_lt->Fill(lb);
      
      /********************************************************/

   }

   /********************************************************/

   //Draw the histograms//
   gROOT->SetStyle("Plain");
   TCanvas *c1 = new TCanvas("c1", "c1", 1200, 600);
   c1->Divide(4,2);
   c1->cd(1);
   h_mass1->Draw("P*");
   c1->cd(2);
   h_mass2->Draw("P*");
   c1->cd(3);
   h_mom1->Draw("P*");
   c1->cd(4);
   h_mom2->Draw("P*");
   c1->cd(5);
   h_mom3->Draw("P*");
   c1->cd(6);
   h_cos1->Draw("P*");
   c1->cd(7);
   h_mom4->Draw("P*");
   c1->cd(8);
   h_lt->Draw("P*");


   //Put the data in a table to stick it into something else//
   Double_t mass1x[40];
   Double_t mass1y[40];

   Double_t mass2x[40];
   Double_t mass2y[40];

   printf("-------Bs Mass Histogram Data Points -----------\n");
   printf("  i  x(GeV)  y(evts)  |    i  x(GeV)  y(evts)\n");
   printf("------------------------------------------------\n");
   for (Int_t i=0; i<40; i++){
   mass1x[i]=h_mass1->GetBinCenter(i);
   mass1y[i]=h_mass1->GetBinContent(i);

   mass2x[i]=h_mass2->GetBinCenter(i);
   mass2y[i]=h_mass2->GetBinContent(i);

   printf("%3d  %6.2f  %6d    |   %3d  %6.2f  %6d\n",i,mass1x[i],mass1y[i],i,mass2x[i],mass2y[i]);
   }
   printf("--------------------------------------------------\n");

   Double_t mom1x[40];
   Double_t mom1y[40];

   Double_t mom2x[40];
   Double_t mom2y[40];

   printf("-----Bs Total Momentum------Bs Transverse Momentum--\n");
   printf("  i  x(GeV/ps^2) y(evts) |   i  x(GeV/ps^2) y(evts)\n");
   printf("----------------------------------------------------\n");
   for (Int_t i=0; i<40; i++){
   mom1x[i]=h_mom1->GetBinCenter(i);
   mom1y[i]=h_mom1->GetBinContent(i);

   mom2x[i]=h_mom2->GetBinCenter(i);
   mom2y[i]=h_mom2->GetBinContent(i);

   printf("%3d    %6.2f  %6d    |  %3d   %6.2f   %6d\n",i,mom1x[i],mom1y[i],i,mom2x[i],mom2y[i]);
   }
   printf("----------------------------------------------------\n");

   Double_t mom3x[40];
   Double_t mom3y[40];

   Double_t cos1x[40];
   Double_t cos1y[40];

   printf("-----Bs Reco Trans Mom--------Cos of Mu-Ds Angle----\n");
   printf("  i  x(GeV/ps^2) y(evts) |   i    x(UL)   y(evts)\n");
   printf("----------------------------------------------------\n");
   for (Int_t i=0; i<40; i++){
   mom3x[i]=h_mom3->GetBinCenter(i);
   mom3y[i]=h_mom3->GetBinContent(i);

   cos1x[i]=h_cos1->GetBinCenter(i);
   cos1y[i]=h_cos1->GetBinContent(i);

   printf("%3d    %6.2f  %6d    |  %3d   %6.2f   %6d\n",i,mom3x[i],mom3y[i],i,cos1x[i],cos1y[i]);
   }
   printf("----------------------------------------------------\n");


   Double_t mom4x[40];
   Double_t mom4y[40];

   Double_t ltx[40];
   Double_t lty[40];

   printf("-----Tag Muon Trans Mom-----------Lifetime of Bs----\n");
   printf("  i  x(GeV/ps^2) y(evts) |   i    x(ps)   y(evts)\n");
   printf("----------------------------------------------------\n");
   for (Int_t i=0; i<40; i++){
   mom4x[i]=h_mom4->GetBinCenter(i);
   mom4y[i]=h_mom4->GetBinContent(i);

   ltx[i]=h_lt->GetBinCenter(i);
   lty[i]=h_lt->GetBinContent(i);

   printf("%3d    %6.2f  %6d    |  %3d   %6.2f   %6d\n",i,mom4x[i],mom4y[i],i,ltx[i],lty[i]);
   }
   printf("----------------------------------------------------\n");

   /********************************************************/

}
