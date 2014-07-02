/*************************************************
Use MINUIT for unbinned likelihood fitting to a
gaussian smeared with an exponential.

Set fixparam to 1 to FIX t0, or 2 to FIX sigma.

Set dofix to 0 (and fixparam to anything) to turn
off fixing and fit for everything simultaneously.
Otherwise, dofix should always be set to 1.

Jamie Hegarty jhegarty@ou.edu
07.01.05
*************************************************/
#ifndef __FUNC_CPP__
#include "func.cpp"
#endif

unbinFitlftm(Int_t fixparam, Int_t dofix)
{
  TMinuit *gMinuit = new TMinuit(2);
  gMinuit -> SetFCN(fit_lftm);
  
  Double_t arglist[10];
  Double_t vstart[10];
  Double_t step[10];

  Double_t p0=0, p1=1;
  Int_t ierflg=0;
 
  Double_t par_t0, par_sigma;
  Double_t err_t0, err_sigma;

  // Set to 0.5 for likelihood, 1 for chisquare

  arglist[0] = 0.5;
  gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

  // Set initial values of parameters 
  //(same t0, sigma as used for fitting mixed, unmixed separately)

  vstart[0] = t0_init;
  vstart[1] = sigma_init;

  step[0] = t0_step;
  step[1] = sigma_step;

  gMinuit->mnparm(0, "t0", vstart[0], step[0], 0., 0., ierflg);
  gMinuit->mnparm(1, "sigma", vstart[1], step[1], 0., 0., ierflg);

  // Fix one parameter and fit for the other
  arglist[0] = fixparam;
  gMinuit->mnexcm("FIX", arglist, dofix, ierflg);

  // Do minimization
  arglist[0] = 3000.;
  arglist[1] = 0.1;
  gMinuit->mnexcm("CALL FCN", &p0, 1, ierflg);
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
  gMinuit->mnexcm("CALL FCN", &p1, 1, ierflg);

  // Get parameters 
  gMinuit->GetParameter(0,par_t0,err_t0);
  gMinuit->GetParameter(1,par_sigma,err_sigma);

  // Export the fitted parameters so we can graph them.

  fitlpar[0]=par_t0;
  fitlpar[1]=par_sigma;

  fitlerr[0]=err_t0;
  fitlerr[1]=err_sigma;

  delete gMinuit;

}

void fit_lftm(Int_t &npar, Double_t *gin, Double_t &f,
	     Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;

  for (Int_t i=0; i<ecount; i++){
    
    Double_t ll = lifetime_fit(par[0], par[1], lifetime[i]);
    nll -= TMath::Log(ll);

  }
  f = nll;

}

