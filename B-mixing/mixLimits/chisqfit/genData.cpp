genData(Int_t nEvt){
  // Initialize variables
  Double_t tau = 1.5;
  Double_t dm  = 1000.;

  Double_t tSigma  = 0.16;
  // Double_t tSigmat = 0.19;
  Double_t tSigmat = 0.;
  Int_t kfactor = 1;
  //Double_t dilution = .16;
  Double_t dilution = 0.5;
  Double_t misTag = 0.5*(1.- dilution);

  Int_t nBins = 30;
  Double_t maxLimit = 3;
   

  Int_t msrState;

  // For VPDL resolution
  Int_t VPDL = 1;
  Double_t sigWNF[3], mVpdl;

  //   ofstream out_umix;
  //   ofstream out_mix;

  //   out_umix.open("umix.dat");
  //   out_mix.open("mix.dat");

  cout << tau << "  " << dm << "  " << tSigma << endl;

  // Open file
  //TFile f("scaleFac.root","new");

  // Open K factor file
  TFile k("kfactor.root","READ");
  TH1F *kf;
  kf = hkfac1;


  // Initialize histograms
  //TH1F *umixht = new TH1F("umixht","Decay Time Unmixed",nBins,0.,maxLimit);
  //TH1F *mixht  = new TH1F("mixht","Decay Time Mixed",nBins,0.,maxLimit);
  
  for (Int_t i=0; i<nEvt; i++){
    // Generate decay time distribution
    Double_t rTime  = gRandom->Exp(tau);
    
    if (tSigma == 0.){
      Double_t tSmear = 0.;
    }
    else{
      Double_t tSmear  = gRandom->Gaus(0., tSigma);
    }

    if (tSigmat == 0.){
      Double_t tSmeart = 0.;
    }
    else{
      Double_t tSmeart = gRandom->Gaus(0., tSigmat*rTime);
    }

    Double_t mTimet = rTime + tSmear + tSmeart;

    // K factor (Check whether mTimet correct)
    if (kfactor != 0){
      Double_t kfac = kf->GetRandom();
      mVpdl = rTime/kfac;

      // VPDL dependent smear from RVK for cut data
      if (VPDL == 0){
	Double_t tSmearV = 0;
      }
      else{
	reso(0.03*mVpdl, sigWNF);
	// 	cout << 0.03*mVpdl << "  "
	// 	     << sigWNF[0] << "  "
	// 	     << sigWNF[1] << "  "
	// 	     << sigWNF[2] << endl;

	Double_t ifWide = gRandom->Rndm();
	if (ifWide < sigWNF[2]){
	  Double_t tSmearV = gRandom->Gaus(0., sigWNF[0]/0.03);
	}
	else{
	  Double_t tSmearV = gRandom->Gaus(0., sigWNF[1]/0.03);
	}
      }
      mTimet = rTime/kfac + tSmearV;
    }
    
    // Does it mix unMix = 1 no, unMix = -1 yes
    Double_t mixTest   = 2.*gRandom->Rndm();
    Double_t unMix  = 1. + TMath::Cos(dm*rTime);
    Int_t mixState = 1;
    if (mixTest > unMix){
      mixState = -1;
    }

    if (misTag != 0.){
      Double_t mTag = gRandom->Rndm();
      if (mTag < misTag){
	msrState = -1 * mixState;
      }
      else{
	msrState = mixState;
      }
    }
    else{
      msrState = mixState;
    }

    if (msrState == 1){
      umixht->Fill(mTimet);
    }
    if (msrState == -1){
      mixht->Fill(mTimet);
    }
  }
  // Make asymmetry distribution
  asymt = umixht->GetAsymmetry(mixht);
  asymt->Draw();

  //f.Close();

  
}
