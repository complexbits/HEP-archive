genData(Int_t nEvt){

  ofstream ptimes;
  ptimes.open("ptimes.out");

  cout << "genData nEvts = " << nEvt << endl;
  // Initialize variables
  //  Double_t tau = 1.5;
  //  Double_t dm  = 1000.;

  //  Int_t bcuts = 0;

  Double_t tSigma  = 0.18;
  Double_t tSigmat = 0.;
  //  Int_t kfactor = 1;
  //Double_t dilution = .16;
  //  Double_t dilution = 0.5;
  Double_t misTag = 0.5*(1.- dilution);

  //  Int_t nBins = 30;
  //  Double_t maxLimit = 3;
   

  Int_t msrState;

  // Initialize internal variables
  Double_t rTime;

  Double_t cut;
  Double_t fcut;
  
  // For VPDL resolution
  //  Int_t VPDL = 1;
  Double_t sigWNF[3], mVpdl;
  //  Double_t resScl = 1.0;

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
    // Generate decay time distribution if bcuts is nonzero
    // applies a scale factor for baised cuts
    if (bcuts == 0){
      rTime  = gRandom->Exp(tau);
    }
    else{
      cut = 100.;
      fcut= 0.;
      while (cut > fcut){
	rTime = gRandom->Exp(tau);
	fcut = .7654 - .6955*TMath::Exp(-71.38*rTime*.03);
	cut  = gRandom->Rndm();
      }
    }
    //cout << "DSMEAR = " << dSmear << endl;
    if (dSmear == 0){
      Double_t tSmear = 0.;
    }
    else if (dSmear == 1){
      tSmear  = gRandom->Gaus(0., tSigma);
      }
    else if (dSmear == 2){
      cout << "WHY AM I HERE" << endl;
      Double_t rndNrw = gRandom->Rndm();
      if (rndNrw > fWid){
	tSmear  = gRandom->Gaus(0., tSigmaN);
      }
      else{
	cout << "OK" << endl;
	tSmear  = gRandom->Gaus(0., tSigmaW);
      }
    }
    //**Triple gaussian*****************************
    else if (dSmear == 3){
      //cout << "YES i BELONG HERE" << endl;
      rndNrw = gRandom->Rndm();
      //cout << "RND  " << rndNrw << endl;
      if (rndNrw < f1){
	tSmear  = gRandom->Gaus(0., tSig1);
	//cout << 1 << endl;
      }
      if (rndNrw >= f1 && rndNrw < f1+f2){
	tSmear  = gRandom->Gaus(0., tSig2);
	//cout << f1 << "  " << 2 << endl;
      }
      if (rndNrw >= f1+f2){
	tSmear  = gRandom->Gaus(0., tSig3);
	//cout << f1+f2 << "  " << 3 << endl;
      }
    }
    //************************************************
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
	resoVPDL(0.03*mVpdl, sigWNF);
	sigWNF[0] = sigWNF[0]*resScl;
	sigWNF[1] = sigWNF[1]*resScl;

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
      hrTime->Fill(rTime);
      hmTime->Fill(mTimet);
      hKfacr->Fill(kfac);
      hSmear->Fill(tSmearV);
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
    ptimes << mTimet << "   " << msrState << endl;
  }
  // Make asymmetry distribution
  asymt = umixht->GetAsymmetry(mixht);
  asymt->Draw();

  //f.Close();

  
}
