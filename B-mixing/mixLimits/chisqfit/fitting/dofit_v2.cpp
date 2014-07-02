//************************************************
// Use minuit to do a chi^2 fit
//
// by P. Gutierrez
// 3-12-04
//************************************************

void dofit()
{
  TMinuit *gMinuit = new TMinuit(2);
  gMinuit -> SetFCN(chi_fit_int);
  
  Double_t arglist[10];
  Double_t vstart[10];
  Double_t step[10];

  Double_t p0=0, p1=1, p2=2, p3=3;
  Int_t ierflg=0;
 
  Double_t par0, par1, par2, par3;
  Double_t err0, err1, err2, err3;

  // Set to 0.5 for likelihood, 1 for chisquare

  arglist[0] = 1.0;
  gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

  // Set initial values of parameters

  vstart[0] = 0.5;
  vstart[1] = dmtst;
  vstart[2] = maxLimit/nBins;
  cout << "vstart[2] = " << vstart[2] << endl;
  
  step[0] = 0.1;
  step[1] = 0.001;
  step[2] = 0.1;

  gMinuit->mnparm(0, "Amplitude", vstart[0], step[0], 0., 0., ierflg);
  gMinuit->mnparm(1, "Delta M",   vstart[1], step[1], 0., 0., ierflg);
  gMinuit->mnparm(2, "Bin Width", vstart[2], step[2], 0., 0., ierflg);
  //gMinuit->mnparm(2, "Normalization", vstart[2], step[2], 0., 0., ierflg);

  // Fix t0 amd sigma
  arglist[0] = 2;
  arglist[1] = 3;
  gMinuit->mnexcm("FIX", arglist, 2, ierflg);

  // Do minimization
  arglist[0] = 3000.;
  arglist[1] = 0.01;
  gMinuit->mnexcm("CALL FCN", &p1, 1, ierflg);
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
  gMinuit->mnexcm("CALL FCN", &p3, 1, ierflg);

  // Get parameters 
  gMinuit->GetParameter(0,par0,err0);
//   Double_t normFactr = 0.16*TMath::Exp(-.15*.15/2.*dmtst*dmtst);
//   cout << "dmtst = " << dmtst << "  Norm = " << normFactr << endl;
//   normFactr = nrmFac15[dmLoop];
  Int_t dmLoop = dmtst;
  //
  cout << "dmLoop = " << dmLoop << "  par0 = " << par0 
       << "  err0 = " << err0<< endl;
  //
  y[dmLoop] = par0/dilution;                    // /normFactr[dmLoop];
  ey[dmLoop] = err0/dilution;                   // /normFactr[dmLoop];
  x[dmLoop] = dmtst;
  ex[dmLoop] = 0;
  cout << y[dmLoop] << "  " << ey[dmLoop] << endl;
  // Include fit function in the histogram
//   TF1 *f2 = new TF1("f2", lifetime_plt, -4., 15., 2);
//   f2->SetParameter(0,par0);
//   f2->SetParameter(1,par1);

//   f2->SetParName(0,"par0");
//   f2->SetParName(1,"par1");
//   f1->SetParName(2,"par2");
//   f1->SetParName(3,"par3");

//   TCanvas* c = new TCanvas("c","c",800,800);
//   c->Divide(2,2);
//   c->cd(1);
//   h2->Draw();
//   f2->Draw("same");
//   c->cd(2);
//   h3->Draw();
//   c->cd(3);
//   h4->Draw();

  delete gMinuit;

}

void chi_fit(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t chi2 = 0.;
  for (Int_t i=0; i<nBins; i++){
    Double_t arg1 = par[0]*TMath::Cos(par[1]*asymX[i]);
    //cout << arg1 << "  " << asymData[i] << endl;
    Double_t arg2 = (arg1 - asymData[i])/asymErr[i];
    Double_t chi2 = chi2 + arg2*arg2;
  }
  f = chi2;

}

void chi_fit_int(Int_t &npar, Double_t *gin, Double_t &f,
		 Double_t *par, Int_t iflag)
  // par[0] = Amplitude
  // par[1] = Frequency
  // par[2] = Bin width
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;
  cout << "Inside fit " << par[0] << "  "
       << par[1] << "  "
       <<par[2] << endl;

  Double_t chi2 = 0.;
  for (Int_t i=0; i<nBins; i++){
    //Double_t arg1 = par[0]*TMath::Cos(par[1]*asymX[i]);
    Double_t arg1 = 2.*par[0]*TMath::Cos(par[1]*asymX[i])*
      TMath::Sin(par[1]*par[2]/2.)/(par[1]*par[2]);
    //cout << arg1 << "  " << asymData[i] << endl;
    //cout << "Error in  " << asymErr[i] << endl;
    Double_t arg2 = (arg1 - asymData[i])/asymErr[i];
    //cout << arg2 << "  " << asymErr[i] << endl << endl;
    Double_t chi2 = chi2 + arg2*arg2;
  }
  f = chi2;

}
