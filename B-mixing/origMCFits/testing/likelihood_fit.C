//***********************************************
// Code to do an unbinned likelihood fit
//***********************************************

// ---------- Include files: --------------------

#include "mcData.cpp"
#include "unbinFitosc.cpp"
#include "func.cpp"

// ---------- Define global variables: ----------

Double_t min = -4;
Double_t max = 15;
Int_t nEvts = 1000;
Int_t nBins = 50;

//vars used in MC:
Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma  = 1.;

Double_t misTag = 0.; // Mistagging rate



// ---------- Define data variables: -------------

Double_t runNo[1000];
Double_t evtNo[1000];
Double_t mass[1000];
Double_t lifetime[1000];
Int_t tag[1000];

Double_t fparinit[3];
Double_t fparerr[3];

// ---------- Define fit parameters: --------------
//Double_t fitpar[3];



//*********************************************************************************


void likelihood_fit(){
  

  // ---------- Define an array to hold everything: ------------------
  TObjArray mixList(0);

  // ---------- Define some histograms and fits: ---------------------
  TH1F *h_ltime = new TH1F("h_ltime","Lifetime Dist", nBins, min, max);
  TH1F *h_ltmix = new TH1F("h_ltmix","Lifetime Dist, Mixed", nBins, min, max);       
  TH1F *h_ltunmix = new TH1F("h_ltunmix","Lifetime Dist, Unmixed", nBins, min, max);

    TF1 *f_ltmix = new TF1("f_ltmix", lftmosc_plt, min, max, 4);
    TF1 *f_ltunmix = new TF1("f_ltunmix", lftmosc_plt, min, max, 4);

  TCanvas *mixpix = new TCanvas("mixpix","mixpix",800,600);

  // ---------- Add histograms and fits to the array -----------------
  mixList.Add(h_ltime);
  mixList.Add(h_ltmix);
  mixList.Add(h_ltunmix);

  mixList.Add(f_ltmix);
  mixList.Add(f_ltunmix);

  mixList.Add(mixpix);

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


  // ---------- Do unbinned likelihood fit: -----------------------------
  // ---------- (uses gMinuit to get fit parameters fitpar[j]) ----------
  
  unbinFitosc();

  for (Int_t j=0; j<=2; j++){
    f_ltmix->SetParameter(j,fparinit[j]);
    f_ltunmix->SetParameter(j,fparinit[j]);
    cout << "fparinit["<<j<<"] = "<<fparinit[j]<<endl;
  }
  f_ltmix->SetParameter(3,1.);
  f_ltunmix->SetParameter(3,-1.);

  
  // ---------- Draw histograms and fits: --------------------------------
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(111111);

  mixpix->Divide(2,2);

  mixpix->cd(1);
  h_ltmix->Draw();
  f_ltmix->Draw("same");

  mixpix->cd(2);
  h_ltunmix->Draw();
  f_ltunmix->Draw("same");

  mixpix->cd(3);
  h_ltime->Draw();

  mixpix->cd(4);
  h_ltime->Draw();
  h_ltmix->Draw("same");
  h_ltunmix->Draw("same");
  f_ltmix->Draw("same");
  f_ltunmix->Draw("same");

  // ---------- Create a file, write out our array, then close the file: -
  //TFile mmmixing("mixing2.root","recreate"); 
  //mixList->Write();
  //mmmixing->Close();


}


//*********************************************************************************

