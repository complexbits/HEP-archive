
// ---------- Include files: --------------------

#include "mcData.cpp"


// ---------- Set default global variables: ----------  
Double_t min = -4;
Double_t max = 15;
Int_t nEvts = 100000;
Int_t nBins = 100;
/*
//vars used in MC:
Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma = 0.;

Double_t misTag = 0.; // Mistagging rate

// ---------- Define data variables: -------------  
Double_t runNo[100000];
Double_t evtNo[100000];
Double_t mass[100000];
Double_t lifetime[100000];
Int_t tag[100000];
*/
// --------- Define fit parameters ----------  
Int_t nRuns=10;  // number of runs (for statistics in a given tSigma, misTag, and nEvts)
Int_t tsmax=10;  // gives tSigma = 0 -> tSigma=tsmax/10., step 0.1
Int_t mtmax=5;   // gives misTag = 0 -> misTag=mtmax/10., step 0.1
Int_t evtmin=2;  // order of magnitude for min number of events
Int_t evtmax=5;  // order of magnitude for max number of events

// the arrays must have, at least, length nRuns*tsmax*mtmax*(1+evtmax-evtmin)
Double_t t_sig[2000];
Double_t mt_var[2000];
Double_t evt_var[2000];
/*
Double_t cosfit_par[2000];
Double_t cosfit_err[2000];
*/


//*********************************************************************************

void vartsig()
{

  // ---------- Define an array to hold everything -----
  TClonesArray histList(0);  

  // --------- Define a graph with error bars, add it to the array -------
  //TGraphErrors *g_vartsig2 = new TGraphErrors(100);
  //vartsigList.Add(g_vartsig2);

  TH1D *h_ltime;
  Char_t h_lt_name[16];
  Char_t h_lt_title[256];

  TH1D *h_ltmix;
  Char_t h_ltm_name[16];
  Char_t h_ltm_title[256];

  TH1D *h_ltunmix;
  Char_t h_ltu_name[16];
  Char_t h_ltu_title[256];

  Int_t ik=0;
  cout <<"ik    tSigma  misTag  nEvts"<<endl;  
  // ------ do a number of runs for more data points ------
  for (Int_t iloop=0.; iloop<nRuns; iloop++){
    
    for (Int_t mloop=evtmin; mloop<=evtmax; mloop++){

      for (Int_t jloop=0.; jloop<mtmax; jloop++){
	
	// ---------- index to vary tSigma -----
	for (Int_t kloop=0.; kloop<tsmax; kloop++){
	  
	  // ------ vary tSigma -------------
	  
	  t_sig[ik]=kloop/10.;
	  tSigma = t_sig[ik];

	  mt_var[ik]=jloop/10.;
	  misTag = mt_var[ik];

	  evt_var[ik]=pow(10,mloop);
	  nEvts=evt_var[ik];
	  /*
	  // ---------- Generate data using MC (from mcData.cpp): ------------
	  // ---------- (makes lifetime data lifetime[i], and tag data tag[i])
	  mixmasta_mc();
	  */
	  sprintf(h_lt_name, "h_lt_%04d", ik);
	  sprintf(h_lt_title, "Lt Total %04d: tSigma=%.2f misTag=%.2f", ik, t_sig[ik], mt_var[ik]);
	  h_ltime = new TH1D(h_lt_name, h_lt_title, nBins, min, max);
	  histList.Add(h_ltime);
	  
	  sprintf(h_ltm_name, "h_ltmix_%04d", ik);
	  sprintf(h_ltm_title, "Lt Mixed %04d: tSigma=%.2f, misTag=%.2f", ik, t_sig[ik],mt_var[ik]);
	  h_ltmix = new TH1D(h_ltm_name, h_ltm_title, nBins, min, max);
	  histList.Add(h_ltmix);
	  
	  sprintf(h_ltu_name, "h_ltunmix_%04d", ik);
	  sprintf(h_ltu_title, "Lt Unmixed %04d: tSigma=%03.2f, misTag=%03.2f", ik, t_sig[ik],mt_var[ik]);
	  h_ltunmix = new TH1D(h_ltu_name, h_ltu_title, nBins, min, max);
	  histList.Add(h_ltunmix);
	  /*
	  for (Int_t j=0; j<nEvts; j++){
	    h_ltime->Fill(lifetime[j]);
	    if (tag[j] == 1){
	      h_ltmix->Fill(lifetime[j]);
	    }else if(tag[j] == -1){
	      h_ltunmix->Fill(lifetime[j]);
	    }else{
	      cout << "Tag value "<<tag[j]<< " out of range, should be -1 or 1" << endl;
	      break;
	    }
	  }
	  
	  //----- Define some new histograms and functions to use for fitting ----
	  
	  TH1D *h_ltmix1 = (TH1D*) h_ltmix->Clone();
	  TH1D *h_ltunmix2 = (TH1D*) h_ltunmix->Clone();
	  TH1D *h_ltunmix1 = (TH1D*) h_ltunmix->Clone();
	  
	  TF1 *f_cosfit = new TF1("f_cosfit", "cos([0]*x)",min,max);
	  f_cosfit->SetParLimits(0,0.3,0.9);
	  
	  //------------------- Do fitting --------------------------
	  
	  // Nu + Nm -------
	  h_ltunmix2->Add(h_ltmix);
	  
	  // Nu - Nm -------
	  h_ltmix1->Scale(-1);
	  h_ltunmix1->Add(h_ltmix1);
	  
	  // (Nu - Nm) / (Nu + Nm) -----
	  h_ltunmix1->Divide(h_ltunmix2);
	  
	  // ------ Fit to cosine -----------
	  h_ltunmix1->Fit(f_cosfit);
	  
	  // ------- Get fit parameter and error ---------
	  gMinuit->GetParameter(0,cosfit_par[ik],cosfit_err[ik]);
	  
	  // ------------ Fill in the graph points ------------------
	  g_vartsig2->SetPoint(ik,t_sig[ik],cosfit_par[ik]);
	  g_vartsig2->SetPointError(ik,0.,cosfit_err[ik]);
	  
	  // ------ Output to the screen (or log file) -------------
	  cout<<endl;
	  cout<<"        ------------------------------------------------"<<endl;
	  cout  <<"        ik        t_sig          cosfit_par"<<endl; 
	  cout<<"        "<<ik<<"       "<<t_sig[ik]<<"          "<<cosfit_par[ik]<<endl;
	  cout <<"        ------------------------------------------------"<<endl;
	  cout <<endl;
	  
	  f_cosfit->Delete();
	  h_ltmix1->Delete();
	  h_ltunmix1->Delete();
	  h_ltunmix2->Delete();
	  */

	  ik++;
	}
      }
    }
  }
  for (Int_t nloop=0; nloop<ik; nloop++){
    cout <<nloop<<"    "<<t_sig[nloop]<<"    "<<mt_var[nloop]<<"    "<<evt_var[nloop]<<endl;
  }
  /*  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(111111);
  gStyle->SetOptFit(1111);
  
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistFillColor(18);
  
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  
  TCanvas *vartsig2 = new TCanvas("vartsig2","vartsig2",800,600);
  vartsig2->SetFillColor(10);
  vartsig2->SetGrid();
  vartsigList.Add(vartsig2);
  
  g_vartsig2->SetTitle("dm's dependence on tSigma");
  g_vartsig2->GetXaxis()->SetTitle("t_sig  (tSigma)");
  g_vartsig2->GetXaxis()->CenterTitle();
  g_vartsig2->GetYaxis()->SetTitle("cosfit_par  (dm)");
  g_vartsig2->GetYaxis()->CenterTitle();
  g_vartsig2->SetMarkerStyle(21);
  g_vartsig2->Draw("AP");
  g_vartsig2->Fit("gaus");
  
  vartsig2->Print("vartsig2.ps");
  */  
  TFile vart_sig("vartsig.root","recreate"); 
  vartsigList.Write();
  vart_sig.Close();

}


//*********************************************************************************

