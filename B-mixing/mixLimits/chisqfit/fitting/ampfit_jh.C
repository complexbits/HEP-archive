#include "dofit_v2.cpp";
//#include "bkgerr.cpp";
//#include "resoVPDL.cpp";

// Initialize fit parameters
#include "semiL.h";

#include "unbinFitosc_d.cpp"
#include "unbinFitlftm.C"

#ifndef __FUNC_CPP__
#include "func.cpp"
#endif

#ifndef __PARAMETERS__
#include "parameters.h"
#endif

Double_t resScl = 1.;


//Double_t nLimit = 1.65; // 95% CL
Double_t nLimit = 1.65;
Double_t tau = 1.5;
Double_t dm  = 1000.;

//---- Set to dilution as calculated by dstag.C
Double_t dilution=0.68;


Double_t asymData[200];
Double_t asymErr[200];
Double_t asymX[200];

Double_t y[200];
Double_t ey[200];
Double_t x[200];
Double_t ex[200];

Double_t iMax = 10;
Double_t dmtst;

 
ampfit_jh(){

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
  /*****************************************************************************/
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

  lbtot=(TH1F*)f1->Get("all_events_vpdl");
  lbtot->SetBins(binN, min, max);
  lbtot->SetTitle("all events VPDL");
  a1.Add(lbtot);

  asym = (TH1F*)f1->Get("h_asymm");
  asym->SetBins(nBins,0.,maxLimit);
  a1.Add(asym);


  hmix = (TH1F*)f1->Get("h_mixed_events");
  hmix->SetBins(binN, min, max);
  a1.Add(hmix);

  hunmix = (TH1F*)f1->Get("h_unmixed_events");
  hunmix->SetBins(binN, min, max);
  a1.Add(hunmix);
  /******************************************************************************/
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

    cout << endl << endl << "iLoop = "<< iLoop << endl << endl;

    sprintf(fname,"fix%d",iLoop);
    fix[iLoop] = new TH1F(fname,fname,nBins, 0., maxLimit);
    
    //divide the asymmetry histogram by each template
    fix[iLoop]->Divide(asym,h[iLoop]);
    
    for (Int_t iAsym=0; iAsym < nBins; iAsym++){
      
      asymX[iAsym] = asym->GetBinCenter(iAsym+1);
      asymData[iAsym] = fix[iLoop]->GetBinContent(iAsym+1);
      asymErr[iAsym] = fix[iLoop]->GetBinError(iAsym+1);
      
    }
    cout << "IMAX = " << iMax << endl;
    // Graph result of division by h[2] (scale2):      
    if (iLoop == 2){     
      TGraphErrors *gtst = new TGraphErrors(20,asymX,asymData, 0, asymErr);
      gtst->SetTitle("asymm/scale2 vs. lftm");
    }
    dmtst = iLoop;
   
    // run fitting code in dofit_v2.cpp
    dofit();


    fix[iLoop]->SetMaximum(1.5);
    fix[iLoop]->SetMinimum(-1.5);

  }

  for (Int_t j=0; j<iMax; j++){
    // x[j] = template number
    // y[j] = amplitude (from fit) / dilution
    cout << y[j] << "  " << ey[j] << "  "
	 << x[j] << "  " << ex[j] << endl;
  }

  // Create Sensitivity and limit plots
  Double_t sens[200], lim[200];
  for (Int_t j=0; j<28; j++){
    sens[j] = nLimit*ey[j]; // 95% CL of the Amplitude/dilution
    lim[j] = y[j] + nLimit*ey[j]; // Max Amp/dil value with 95% CL
  }

  TGraphErrors *g1 = new TGraphErrors(10,x,y,ex,ey);
  g1->SetTitle("Ampl./dil. vs. dm");

  TGraph *g2 = new TGraph(11,x,sens);
  g2->SetTitle("Sensitivity vs. Template # (red)");
  g2->SetLineColor(2);

  TGraph *g3 = new TGraph(11,x,lim);
  g3->SetTitle("Limit (blue), Sensitivity (red)");
  g3->SetLineColor(4);

  a1.Add(g1);
  a1.Add(g2);
  a1.Add(g3);

  TF1 *d_gaus = new TF1("d_gaus", "gaus(0)+gaus(3)", -maxLimit, maxLimit);
  d_gaus->SetParameters(0,0,0.25,0,0,0.5);
  d_gaus->FixParameter(1,0);
  d_gaus->FixParameter(4,0);

  /****************************************************************
   * Do Unbinned Likelihood Fitting
   ****************************************************************/
  // do unbinned fit with Minuit
  unbinFitosc_d();

  // create functions to draw the fits
  TF1 *ubfit1 = new TF1("ubfit1", lftmosc_plt_d, min, max, 5);
  TF1 *ubfit2 = new TF1("ubfit2", lftmosc_plt_d, min, max, 5);
  
  // set the parameters of the functions to the ones from the fit
  for (Int_t j=0; j<4; j++){
    ubfit1->SetParameter(j,fitpar[j]);
    ubfit2->SetParameter(j,fitpar[j]);
  }
  ubfit1->SetParameter(4,1);
  ubfit2->SetParameter(4,-1);

  unbinFitlftm();
  TF1 *ubfit3 = new TF1("ubfit3", lifetime_fit_d, min, max, 2);
     
  for (Int_t j=0; j<2; j++){
    ubfit3->SetParameter(j,fitlpar[j]);
  }


  cout << "done with unbinned fitting" << endl << endl;

  // Plot everything

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);
  gStyle->SetHistFillColor(10);

  TCanvas *plot = new TCanvas("plot","plot",1200,800);
  plot->Divide(3,2);

  plot->cd(1);
  lbdiff->Draw();
  lbdiff->Fit(d_gaus);

  plot->cd(2);
  asym->Draw();
  TF1 *f_cos = new TF1("f_cos", "0.4*cos(7*x)",0.,3.);
  f_cos->Draw("same");

  plot->cd(3);
  gPad->SetGrid();
  g1->Draw("AL*");


  plot->cd(4);
  lbtot->Draw();
  ubfit3->Draw("same");
  //  lbtot->Fit("expo");


  plot->cd(5);
  hmix->Draw();
  ubfit1->Draw("same");


  plot->cd(6);
  hunmix->Draw();
  ubfit2->Draw("same");

  a1.Add(plot);

  // Output all of this stuff to a root file

  TFile fout ("ampfit.root","recreate");
  a1.Write();
  fout.Close();
}
