void test(){
struct vars_t{
  
  // ---------- Define data variables: -------------  
  Double_t runNo[100000];
  Double_t evtNo[100000];
  Double_t mass[100000];
  Double_t lifetime[100000];
  Int_t tag[100000];
  
  // --------- Define fit parameters ----------  
 
  Double_t cosfit_par[100];
  Double_t cosfit_err[100];
    
  Double_t t_sig[100];


  Double_t lhfit_t0par[100];
  Double_t lhfit_dmpar[100];
  Double_t lhfit_sigpar[100];

  Double_t lhfit_t0err[100];
  Double_t lhfit_dmerr[100];
  Double_t lhfit_sigerr[100];
  
}
vars_t vts;


Double_t fitpar[3];
Double_t min = -4;
Double_t max = 15;
Int_t nEvts = 100000;
Int_t nBins = 100;

//vars used in MC:
Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma = 0.;  

Int_t nRuns=10;
Int_t kmax=10;
Int_t ik=0;


 // ---------- index to vary tSigma -----
  for (Int_t k=0.; k<kmax; k++){
    
    
    // ------ do a number of runs for more data points ------
    for (Int_t i=0.; i<nRuns; i++){
      
      // ---------- Define some histograms and fits: ---------------------
      TH1D *h_ltime = new TH1D("h_ltime","Lifetime Dist", nBins, min, max);
      TH1D *h_ltmix = new TH1D("h_ltmix","Lifetime Dist, Mixed", nBins, min, max);       
      TH1D *h_ltunmix = new TH1D("h_ltunmix","Lifetime Dist, Unmixed", nBins, min, max);
      
      //ik = 10*i + k;
      
      // ------ vary tSigma -------------
      
      t_sig[ik]=k/10.;
      cout <<":::::::::::::::::::: tSigma = "<<t_sig[ik]<<" ::::::::::::::::::::::::::::::::"<<endl;
      
      tSigma = t_sig[ik];
      
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
      
      TH1D *h_ltmix1 = (TH1D*) h_ltmix->Clone();
      TH1D *h_ltunmix2 = (TH1D*) h_ltunmix->Clone();
      TH1D *h_ltunmix1 = (TH1D*) h_ltunmix->Clone();
      
      TF1 *f_cosfit = new TF1("f_cosfit", "cos([0]*x)",-4.,15.);
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

      // ------ Do likelihood fit as well ------------------------
 
      TF1 *f_ltmix = new TF1("f_ltmix", lftmosc_plt, min, max, 4);
      TF1 *f_ltunmix = new TF1("f_ltunmix", lftmosc_plt, min, max, 4);
     
      unbinFitosc();
      
      for (Int_t j=0; j<=2; j++){
	f_ltmix->SetParameter(j,fitpar[j]);
	f_ltunmix->SetParameter(j,fitpar[j]);
	cout << "fitpar["<<j<<"] = "<<fitpar[j]<<endl;
      }
      f_ltmix->SetParameter(3,1.);
      f_ltunmix->SetParameter(3,-1.);

    }
  }

      


}
