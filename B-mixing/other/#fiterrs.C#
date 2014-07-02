/*
 * This script generates B-mixing events, fits  Nu - Nm / Nu + Nm (t) to a cos function
 * several times, then gets the cos fit parameter (which should be like generating 
 * parameter dm) and the associated error, and plots the parameters and the error so one 
 * can check that:
 *   - resultant dm dist is centered on input "dm" (with tSigma=0.)
 *   - RMS of result. dist. = mean of error dist.
 * 
 * Jamie Hegarty hegarty@nhn.ou.edu
 */

#include "mcData.cpp"

// ---------- Define global variables: ----------

Double_t min = -4;
Double_t max = 15;
Int_t nEvts = 10000;
Int_t nBins = 100;

Int_t nRuns = 1000;

//vars used in MC:
Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma  = 0.;

Double_t misTag = 0.; // Mistagging rate

// ---------- Define data variables: -------------
Double_t runNo[1000];

Double_t evtNo[10000];
Double_t mass[10000];
Double_t lifetime[10000];
Int_t tag[10000];

// --------- Define fit parameters ----------
Double_t cosfit_par;
Double_t cosfit_err;

//*********************************************************************************


void fiterrs(){
  cout <<"==========================================================="<<endl;
  cout <<"     Starting MC, "<<nRuns<<" Runs, "<<nEvts<<" Each "<<endl<<endl;
  cout <<"==========================================================="<<endl;
  // ---------- Define an array to hold everything: ------------------
  TObjArray fitList(0);

  TH1F *h_cfpar = new TH1F("h_cfpar", "Fit parameter from cos_fit", nBins,0.45,0.6);
  TH1F *h_cferr = new TH1F("h_cferr", "Fit par error from cos_fit", nBins,0.01,0.05);

  fitList.Add(h_cfpar);
  fitList.Add(h_cferr);

  //---------- Run the event generation and fitting nRuns times ------
  for (Int_t k=0; k<nRuns; k++){
    
    // ---------- Define some histograms and fits: ---------------------
    TH1F *h_ltime = new TH1F("h_ltime","Lifetime Dist", nBins, min, max);
    TH1F *h_ltmix = new TH1F("h_ltmix","Lifetime Dist, Mixed", nBins, min, max);       
    TH1F *h_ltunmix = new TH1F("h_ltunmix","Lifetime Dist, Unmixed", nBins, min, max);
        
    // ---------- Generate data using MC (from mcData.cpp): ------------
    // ---------- (makes lifetime data lifetime[i], and tag data tag[i])
    mixmasta_mc();
    
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
    
    TH1F *h_ltmix1 = (TH1F*) h_ltmix->Clone();
    TH1F *h_ltunmix2 = (TH1F*) h_ltunmix->Clone();
    TH1F *h_ltunmix1 = (TH1F*) h_ltunmix->Clone();
    
    TF1 *f_cosfit = new TF1("f_cosfit", "cos([0]*x)",-4.,15.);
    f_cosfit->SetParLimits(0,0.3,0.9);
    
    //------------------- Do fitting --------------------------
    
    // ---- Nu + Nm -------
    h_ltunmix2->Add(h_ltmix);
    
    // ---- Nu - Nm -------
    h_ltmix1->Scale(-1);
    h_ltunmix1->Add(h_ltmix1);
    
    // ---- (Nu - Nm) / (Nu + Nm) -----
    h_ltunmix1->Divide(h_ltunmix2);
    h_ltunmix1->Fit(f_cosfit);

    //----------- Get fit parameters, errors, and fill histograms: -----

    gMinuit->GetParameter(0,cosfit_par,cosfit_err);
    //f_cosfit->

    h_cfpar->Fill(cosfit_par);
    h_cferr->Fill(cosfit_err);
  }

  // ---------- Create a file, write out our array, then close the file: -
  TFile mmmixing("cosfitpars.root","recreate"); 
  fitList.Write();
  mmmixing.Close();
}


//*********************************************************************************

