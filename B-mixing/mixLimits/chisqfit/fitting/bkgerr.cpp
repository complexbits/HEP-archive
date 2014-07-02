Double_t sigErr(Double_t sig, Double_t bkg)
{
  // Code to estimate the error due to fitting a guassian
  // with flat background
  // Inputs are:
  //            sig = number of signal events
  //            bkg = number of background events in signal
  //                  region (+/- 3*sigma)

  //cout << "sig = " << sig << "  bkg = " << bkg << endl;

  // Bin width and error matrix
  Double_t binW=4./80.;
  Double_t emat[5][5];

  // Book histogram and fitting/generating function
  TH1F *serr = new TH1F("serr","mass dist",80,0.,4.);
  TF1  *f1   = new TF1("f1","gaus(0)+pol1(3)");

  // Calculate the amplitude of the Gaussian and fill in the
  // parameters of the Gaussian to fill it
  Double_t amp = sig*binW/(TMath::Sqrt(2*TMath::Pi())*0.25);
  f1->SetParameter(0,amp);
  f1->SetParameter(1,2.);
  f1->SetParameter(2,.25);

  // Calculate the height of the flat background and set the
  // fill parameter
  Double_t hgt = bkg*binW/1.5;
  f1->SetParameter(3,hgt);
  f1->SetParameter(4,0.);

  Double_t nEvts = sig + bkg*4./1.5;

  serr->FillRandom("f1",nEvts);
  serr->Fit("f1","LQN");

  // Get fit parameters
  Double_t norm = f1->GetParameter(0);
  Double_t mean = f1->GetParameter(1);
  Double_t sigm = f1->GetParameter(2);

  // Calculate number of signal events
  Double_t numSig = norm*TMath::Sqrt(2.*TMath::Pi())*sigm/binW;

  // Get error matrix
  gMinuit->mnemat(&emat[0][0],5);

  // Calculate error on the number of signal events
  Double_t a1=emat[0][0]/(norm*norm);
  Double_t b1=emat[2][2]/(sigm*sigm);
  Double_t c1=2.*emat[0][2]/(norm*sigm);

  // Fractional error
  Double_t facErr = TMath::Sqrt(a1+b1+c1);
  Double_t err = numSig*facErr;

  //cout << numSig << endl;

  // Delete histogram and function
  delete serr;
  delete f1;
  return err;
}
