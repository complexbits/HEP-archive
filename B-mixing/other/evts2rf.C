//***********************************************
// Code to do an unbinned likelihood fit
//***********************************************

// ---------- Include files: --------------------

#include "mcData.cpp"


// ---------- Define global variables: ----------

Double_t min = -4;
Double_t max = 15;
Int_t nEvts = 100000;
Int_t nBins = 100;

//vars used in MC:
Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma  = 0.;

Double_t misTag = 0.; // Mistagging rate



// ---------- Define data variables: -------------

Double_t runNo[100000];
Double_t evtNo[100000];
Double_t mass[100000];
Double_t lifetime[100000];
Int_t tag[100000];



//*********************************************************************************


void evts2rf(){
  

  // ---------- Define an array to hold everything: ------------------
  TObjArray mixList(0);

  // ---------- Define some histograms and fits: ---------------------
  TH1F *h_ltime = new TH1F("h_ltime","Lifetime Dist", nBins, min, max);
  TH1F *h_ltmix = new TH1F("h_ltmix","Lifetime Dist, Mixed", nBins, min, max);       
  TH1F *h_ltunmix = new TH1F("h_ltunmix","Lifetime Dist, Unmixed", nBins, min, max);

  // ---------- Add histograms and fits to the array -----------------
  mixList.Add(h_ltime);
  mixList.Add(h_ltmix);
  mixList.Add(h_ltunmix);

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

  // ---------- Create a file, write out our array, then close the file: -
  TFile mmmixing("mixing2.root","recreate"); 
  mixList.Write();
  mmmixing.Close();


}


//*********************************************************************************

