#include "dofit_v2.cpp";
#include "bkgerr.cpp";
#include "resoVPDL.cpp";

// Initialize fit parameters
#include "semiL.h";

Double_t resScl = 1.;

//Int_t nEvts = 500;
Int_t nEvts = 425;
//Int_t nEvts = 100000;
//Double_t nLimit = 1.65; // 95% CL
Double_t nLimit = 1.65;

Double_t tau = 1.5;
//Double_t dm  = 5.;
Double_t dm  = 1000.;
//Double_t dm  = 6.;

// For k factor
// Int_t bcuts = 0;
// Int_t kfactor = 0;
// Int_t VPDL = 0;

//Double_t dilution = 0.4;
Double_t dilution = 0.4;

// For no k factor
// Int_t dSmear = 2;
// Double_t tSigmaN = 0.00278/.03;
// Double_t tSigmaW = 0.00351/.03;
// Double_t fWid = 0.49;

// Initialize global variables
//Int_t    nBins = 30;
//Double_t maxLimit = 3.;
Int_t    nBins = 20;
Double_t maxLimit = 2.;

Double_t asymData[200];
Double_t asymErr[200];
Double_t asymX[200];

Double_t y[200];
Double_t ey[200];
Double_t x[200];
Double_t ex[200];

Double_t iMax = 10;
Double_t dmtst;

// Background to signal
Double_t bkgSig[10]={5.6886, 4.62235, 3.8314, 3.1397, 3.54177, 3.97965, 4.27143,3.39745, 4.6566, 3.24586};

// Initialize histograms (filled in genData)
TH1F *umixed = new TH1F("umixht","Decay Time Unmixed",nBins,0.,maxLimit); 
TH1F *mixed  = new TH1F("mixht","Decay Time Mixed",nBins,0.,maxLimit); 



ampfit_v5(){

  gRandom->SetSeed(0);

  // Start an array of histograms and fill them with the templates
  // generated in by scaleFac:

  TH1F *h[50]; 
  TObjArray a1(0);  

  TFile *f = new TFile("test_mk.root", "READ");  
  TIter next(f->GetListOfKeys()); 
  TKey *key;                      

  Int_t k=0, i=1;
  char nametmp [25], name [25], title [100];

  while ((key = (TKey*)next())){ 

    if (k/((3*i)-2) == 1.){

      sprintf(nametmp, "%s", key->GetName());  
      h[i] = (TH1F*)f->Get(nametmp);      

      sprintf(name, "h%d", i);                 
      h[i]->SetName(name);

      sprintf(title, "%s (h%d)", key->GetName(), i);  
      h[i]->SetTitle(title);
 
      a1.Add(h[i]);

      i++;
    }
    k++;
  }

  h[30] = real1;
  h[31] = smer1;
  a1.Add(h[30]);
  a1.Add(h[31]);

  // Get the relevant histograms created by dstag:
  TFile *f1 = new TFile("bs_asymm.root", "READ");

  /**

     In bs_asymm.root:

     h_unmixed_events = histogram with lbmctrue/0.03 for unmixed events
     h_mixed_events = histogram with lbmctrue/0.03 for mixed events
     h_asymm = asymmetry using h_unmixed_events and h_mixed_events
     all_events_vpdl = histogram with lbmctrue/0.03, all events
     h_lbdiff = histogram with lb/0.03 - lbmc/0.03, all events

   **/
  lbdiff = (TH1F*)f1->Get("h_lbdiff");
  lbdiff->SetBins(2*nBins, -maxLimit, maxLimit);
  lbdiff->SetTitle("Reco Time - MC Time, all events");
  a1.Add(lbdiff);

  asym = (TH1F*)f1->Get("h_asymm");
  asym->SetBins(nBins,0.,maxLimit);
  a1.Add(asym);

  // Do fitting:

  for (Int_t i=0; i<40; i++){
    Double_t hcnt = h[1]->GetBinContent(i);
    Double_t hcnt1 = h[30]->GetBinContent(i);
    Double_t hcnt2 = h[31]->GetBinContent(i);
    cout << "i = " << i << "  count = " << hcnt 
	 << "  real = " << hcnt1 
	 << "  smer = " << hcnt2 
      //<< "  ratio = " cnt2/cnt1 
	 << endl;
  }
  TH1F *fix[50];
  char fname[5];
  for (Int_t iLoop=1; iLoop<28; iLoop++){
    sprintf(fname,"fix%d",iLoop);
    fix[iLoop] = new TH1F(fname,fname,nBins, 0., maxLimit);
    TH1F *tmp = new TH1F("tmp","tmp",nBins, 0., maxLimit);
    tmp->Divide(asym,h[iLoop]);
    fix[iLoop] = tmp;
    for (Int_t iAsym=1; iAsym < nBins+1; iAsym++){
      asymX[iAsym-1]    = asym->GetBinCenter(iAsym);
      asymData[iAsym-1] = tmp->GetBinContent(iAsym);
      asymErr[iAsym-1] = tmp->GetBinError(iAsym);
    }
    cout << "IMAX = " << iMax << endl;
    if (iLoop == 2){
      TGraph *gtst = new TGraph(20,asymX,asymData);
    }
    dmtst = iLoop;
    dofit();
    cout << y[iLoop] << "   " << ey[iLoop] << endl;

    fix[iLoop]->SetMaximum(1.5);
    fix[iLoop]->SetMinimum(-1.5);
    fix[iLoop]->Draw();
  }
  for (Int_t j=0; j<iMax; j++){
    cout << y[j] << "  " << ey[j] << "  "
	 << x[j] << "  " << ex[j] << endl;
  }


  // Create Sensitivity and limit plots
  Double_t sens[200], lim[200];
  for (Int_t j=0; j<28; j++){
    sens[j] = nLimit*ey[j];
    lim[j] = y[j] + nLimit*ey[j];
  }

  TGraphErrors *g1 = new TGraphErrors(10,x,y,ex,ey);
  TGraph *g2 = new TGraph(11,x,sens);
  TGraph *g3 = new TGraph(11,x,lim);

  a1.Add(g1);
  a1.Add(g2);
  a1.Add(g3);

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(11111);
  gStyle->SetHistFillColor(10);

  TCanvas *plot = new TCanvas("plot","plot",1200,800);
  plot->Divide(3,2);

  plot->cd(1);
  h[10]->Draw();

  plot->cd(2);
  lbdiff->Draw();

  plot->cd(4);
  asym->Draw();

  plot->cd(5);
  gPad->SetGrid();
  gtst->Draw("AL*");

  plot->cd(3);
  gPad->SetGrid();
  g2->SetLineColor(2);
  g3->SetLineColor(4);
  g3->Draw("AL*");
  g2->Draw("L*");

  plot->cd(6);
  gPad->SetGrid();
  gPad->SetGrid();
  g2->Draw("AL*");
  g3->Draw("L*");  





 



  TFile fout ("ampfit.root","recreate");
  a1->Write();
  fout.Close();
}
