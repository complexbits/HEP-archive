#include "/home/gut/work/research/d0/studies/wrk_in_prgs/pTimeRes/genData.cpp";
#include "/home/gut/work/research/d0/studies/wrk_in_prgs/pTimeRes/dofit.cpp";
#include "/home/gut/work/research/d0/studies/wrk_in_prgs/pTimeRes/bkgerr.cpp";
#include "resoVPDL.cpp";

// Initialize global variables
Int_t    nBins = 30;
Double_t maxLimit = 3.;

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

// Initialize histograms
TH1F *umixht = new TH1F("umixht","Decay Time Unmixed",nBins,0.,maxLimit);
TH1F *mixht  = new TH1F("mixht","Decay Time Mixed",nBins,0.,maxLimit);

ampfit_v3(){

  TFile *f = new TFile("scaleFac_rkv_vpdl.root","READ");
  TH1F *h[50];

  h[1]  = scale1;
  h[2]  = scale2;
  h[3]  = scale3;
  h[4]  = scale4;
  h[5]  = scale5;
  h[6]  = scale6;
  h[7]  = scale7;
  h[8]  = scale8;
  h[9]  = scale9;
  h[10] = scale10;
  h[11] = scale11;
  h[12] = scale12;
  h[13] = scale13;
  h[14] = scale14;
  h[15] = scale15;
  h[16] = scale16;
  h[17] = scale17;
  h[18] = scale18;
  h[19] = scale19;
  h[20] = scale20;
  h[21] = scale21;
  h[22] = scale22;
  h[23] = scale23;
  h[24] = scale24;
  h[25] = scale25;
  h[26] = scale26;
  h[27] = scale27;
  h[28] = scale28;
  h[29] = scale29;

  //f->Close();


  TCanvas *plot = new TCanvas("plot","plot",800,800);
  plot->Divide(2,2);

  plot->cd(1);
  h[10]->Draw();

  plot->cd(2);
  genData(1000);

  // Correct errors for background
  Int_t bkgEcalc = 1;
  if (bkgEcalc == 1){
    for (Int_t iLoop=1; iLoop<11; iLoop++){
      Double_t bCont = umixht->GetBinContent(iLoop);
      Double_t bkgEst = bCont*bkgSig[iLoop-1];
      Double_t bkgE = sigErr(bCont,bkgEst);
      umixht->SetBinError(iLoop, bkgE);

      Double_t bCont = mixht->GetBinContent(iLoop);
      Double_t bkgEst = bCont*bkgSig[iLoop-1];
      Double_t bkgE = sigErr(bCont,bkgEst);
      mixht->SetBinError(iLoop, bkgE);
    }
  }

  asym = umixht->GetAsymmetry(mixht);
  plot->cd(3);
  asym->Draw();

  for (Int_t i=0; i<40; i++){
    Double_t cnt = h[10]->GetBinContent(i);
    cout << "i = " << i << "  count = " << cnt << endl;
  }
  TH1F *fix[50];
  char fname[5];
  for (Int_t iLoop=1; iLoop<20; iLoop++){
    sprintf(fname,"fix%d",iLoop);
    fix[iLoop] = new TH1F(fname,fname,30, 0., 3.);
    TH1F *tmp = new TH1F("tmp","tmp",30, 0., 3.);
    tmp->Divide(asym,h[iLoop]);
    fix[iLoop] = tmp;
    for (Int_t iAsym=1; iAsym < iMax+1; iAsym++){
      asymX[iAsym-1]    = asym->GetBinCenter(iAsym);
      asymData[iAsym-1] = tmp->GetBinContent(iAsym);
      asymErr[iAsym-1] = tmp->GetBinError(iAsym);
    }
    dmtst = iLoop;
    dofit();
    cout << y[iLoop] << "   " << ey[iLoop] << endl;
    plot->cd(4);
    fix[iLoop]->SetMaximum(1.5);
    fix[iLoop]->SetMinimum(-1.5);
    fix[iLoop]->Draw();
  }
  for (Int_t j=0; j<iMax; j++){
    cout << y[j] << "  " << ey[j] << "  "
	 << x[j] << "  " << ex[j] << endl;
  }
  TCanvas *result = new TCanvas("result","result",800,400);
  result->Divide(2,1);
  // Amplitude plot
  TGraphErrors *g1 = new TGraphErrors(20,x,y,ex,ey);
  result->cd(1);
  g1->Draw("AL*");

  // Sensitivity and limit plots
  Double_t sens[200], lim[200];
  for (Int_t j=0; j<20; j++){
    sens[j] = 1.65*ey[j];
    lim[j] = y[j] + 1.65*ey[j];
  }

  TCanvas *Limits = new TCanvas("Limits","Limits",400,400);
  TGraph *g2 = new TGraph(20,x,sens);
  TGraph *g3 = new TGraph(20,x,lim);
  result->cd(2);
  g2->Draw("AL*");
  Limits->cd();
  g2->Draw("AL*");
  //g3->Draw("L*");
}
