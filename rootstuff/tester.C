#define tester_cxx
#include "tester.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "iostream.h"

void tester::Loop()
{

   if (fChain == 0) return;
  int aa = 1000; int nn = 0;
   Int_t nentries = Int_t(fChain->GetEntriesFast());

   Int_t nbytes = 0, nb = 0;
   for (Int_t jentry=0; jentry<=10000;jentry++) {
     //   for (Int_t jentry=0; jentry<nentries;jentry++) {
      Int_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
    	if(jentry/aa>nn) cout << "Event #" << jentry << endl;
      	nn = jentry/aa;
   }
   cout << "complete";
}
