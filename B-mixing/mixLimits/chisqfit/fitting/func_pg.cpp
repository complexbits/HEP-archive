//**********************************************************
Double_t nGaus(Double_t mean, Double_t sigma, Double_t x)
{
  Double_t expArg = (x - mean)/sigma;
  Double_t gNorm = TMath::Sqrt(TMath::TwoPi())*sigma;

  Double_t ng = 1/(gNorm)*
    TMath::Exp(-expArg*expArg/2.);

  return ng;
}

Double_t nPoly1(Double_t slope, Double_t x)
{
  Double_t pNorm = slope/2.*(max*max - min*min) +
    max - min;
  Double_t np = (slope*x + 1)/pNorm;
  return np;
}

Double_t uNmix(Double_t t, Double_t t0, Double_t dm, Double_t s)
{
    // Normalization

  //Double_t norm = (1.+ dm*dm * t0*t0)/(8.*t0 + 4.*dm*dm * t0*t0*t0);
  Double_t norm = 1./(8.* t0);

  // Exponential decay term

  Double_t argexp = (s*s - 2.*t*t0)/(2.*t0*t0);
  Double_t argerf = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);
  Double_t expterm = TMath::Exp(argexp)*(1+TMath::Erf(argerf));

  // Complex exponential term

  Double_t arg1_re = (2.*t*t0 + s*s*(dm*dm*t0*t0 - 1.))/(2.*t0*t0);
  Double_t arg1_im = (dm*(t*t0 - s*s))/t0;

  Double_t exp1 = TMath::Exp(-arg1_re);
  Double_t cos1 = TMath::Cos(-arg1_im);
  Double_t sin1 = TMath::Sin(-arg1_im);

  //Complex error function term

  Double_t arg2_re = dm*s/(TMath::Sqrt(2.));
  Double_t arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);

  RooComplex wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);
  Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
  Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
  Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

  Double_t wzre = wz.re();
  Double_t wzim = wz.im();

  if (arg2_im > 26.){
    Double_t wz_re = 2.0;
    Double_t wz_im = 0.0;
  }
  else{
    Double_t wz_re =   expwz*(wzre*coswz - wzim*sinwz);
    Double_t wz_im =   expwz*(wzre*sinwz + wzim*coswz);
  }

  // Unmixed convoulted time dependent function

  Double_t func_un = 2.*(expterm + exp1*(wz_re*cos1 - wz_im*sin1));
  Double_t func = norm*func_un;

  return func;
}

Double_t mix(Double_t t, Double_t t0, Double_t dm, Double_t s)
{
    // Normalization

  //Double_t norm = (1.+ dm*dm * t0*t0)/(8.*t0 + 4.*dm*dm * t0*t0*t0);
  Double_t norm = 1./(8.*t0);

  // Exponential decay term

  Double_t argexp = (s*s - 2.*t*t0)/(2.*t0*t0);
  Double_t argerf = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);
  Double_t expterm = TMath::Exp(argexp)*(1+TMath::Erf(argerf));

  // Complex exponential term

  Double_t arg1_re = (2.*t*t0 + s*s*(dm*dm*t0*t0 - 1.))/(2.*t0*t0);
  Double_t arg1_im = (dm*(t*t0 - s*s))/t0;

  Double_t exp1 = TMath::Exp(-arg1_re);
  Double_t cos1 = TMath::Cos(-arg1_im);
  Double_t sin1 = TMath::Sin(-arg1_im);

  //Complex error function term

  Double_t arg2_re = dm*s/(TMath::Sqrt(2.));
  Double_t arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);

  RooComplex wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);
  //RooComplex wz = RooMath::ComplexErrFunc(arg2_re,arg2_im);
  Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
  Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
  Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

  Double_t wzre =  wz.re();
  Double_t wzim =  wz.im();

  if (arg2_im > 26.){
    Double_t wz_re = 0.0;
    Double_t wz_im = 2.0;
  }
  else{
    Double_t wz_im =   expwz*(wzre*coswz - wzim*sinwz);
    Double_t wz_re =  -expwz*(wzre*sinwz + wzim*coswz);
  }

  // Mixed convoulted time dependent function

  Double_t func_un = 2.*(expterm - exp1*(wz_re*sin1 + wz_im*cos1));
  Double_t func = norm*func_un;

  return func;
}

Double_t mass_fit(Double_t *x, Double_t *par)
{
  Double_t m0 = par[0];
  Double_t sigma = par[1];
  Double_t slope = par[2];
  Double_t frac = par[3];

  Double_t func_1 = nGaus(m0, sigma, x[0]);
  Double_t func_2 = nPoly1(slope, x[0]);
  Double_t func   = float(nEvts)/nBins*(frac*func_1 + (1.-frac)*func_2);

  return func;
}

Double_t lifetime_fit(Double_t t0, Double_t sigma, Double_t t)
{

  Double_t lNorm = 1./(2.*t0);
  Double_t arg1 = (sigma*sigma - 2.*t0*t)/(2.*t0*t0);
  Double_t arg2 = (t*t0 - sigma*sigma)/(TMath::Sqrt(2.)*sigma*t0);

  Double_t func1=TMath::Exp(arg1);
  Double_t func2=TMath::Erf(arg2);

//   cout << "t0 = " << t0 << "  sigma = " << sigma
//        << "  func1(" << arg1 << ") = " << func1 << "  and  "
//        << "func2(" << arg2 << ") = " << func2 << endl;

  Double_t func = func1*(1.+func2)/(2.*t0);

  return func;
}

Double_t lifetime_plt(Double_t *x, Double_t *par)
{
  Double_t t0 = par[0];
  Double_t sigma = par[1];
  Double_t t = x[0];


  Double_t lNorm = 1./(2.*t0);
  Double_t arg1 = (sigma*sigma - 2.*t0*t)/(2.*t0*t0);
  Double_t arg2 = (t*t0 - sigma*sigma)/(TMath::Sqrt(2.)*sigma*t0);

  Double_t func1=TMath::Exp(arg1);
  Double_t func2=TMath::Erf(arg2);

  Double_t func = nEvts*19./50.*func1*(1.+func2)/(2.*t0);

  return func;
}

Double_t lifetime_osc(Int_t tag, Double_t t0,
		      Double_t dm, Double_t s, Double_t t)
{

  Double_t ll;

  if (tag == 0) ll = 1.;
  if (tag == -1) ll = uNmix(t, t0, dm, s);
  if (tag == 1) ll = mix(t, t0, dm, s);
  
  return ll;
}

Double_t lftmosc_plt(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func;

  if (tag == -1) func = nEvts*19./50.* uNmix(t, t0, dm, s);
  if (tag == 1) func = nEvts*19./50.* mix(t, t0, dm, s);

  return func;

}

Double_t lftmosc_plt_d(Double_t *x, Double_t *par)
{
  Double_t t       = x[0];
  Double_t t0      = par[0];
  Double_t dm      = par[1];
  Double_t s       = par[2];
  Double_t alpha   = par[3];
  Int_t    tag     = par[4];

  Double_t func;

  if (tag == -1) func = nEvts*19./50.* ((1.-alpha)*uNmix(t, t0, dm, s) +
			       alpha*mix(t, t0, dm, s));
  if (tag == 1) func = nEvts*19./50.* ((1.-alpha)*mix(t, t0, dm, s) +
			      alpha*uNmix(t, t0, dm, s));

  return func;

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Double_t lftmosc_plt_old(Double_t *x, Double_t *par)
{

  Double_t t = x[0];
  //Double_t t = 2.8;
  Double_t t0 = par[0];
  Double_t dm = par[1];
  Double_t s  = par[2];

  // Normalization

  Double_t norm = (1.+ dm*dm * t0*t0)/(8.*t0 + 4.*dm*dm * t0*t0*t0);

  // Exponential decay term

  Double_t argexp = (s*s - 2.*t*t0)/(2.*t0*t0);
  Double_t argerf = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);
  Double_t expterm = TMath::Exp(argexp)*(1+TMath::Erf(argerf));

  // Complex exponential term

  Double_t arg1_re = (2.*t*t0 + s*s*(dm*dm*t0*t0 - 1.))/(2.*t0*t0);
  Double_t arg1_im = (dm*(t - s*s))/t0;

  Double_t exp1 = TMath::Exp(-arg1_re);
  Double_t cos1 = TMath::Cos(-arg1_im);
  Double_t sin1 = TMath::Sin(-arg1_im);

  //Complex error function term

  Double_t arg2_re = dm*s/(TMath::Sqrt(2.));
  Double_t arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);

  RooComplex wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);
  Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
  Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
  Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

  Double_t wz_re =  expwz*(wz.re()*coswz - wz.im()*sinwz);
  Double_t wz_im =  expwz*(wz.re()*sinwz + wz.im()*coswz);

  // Unmixed convoulted time dependent function

  Double_t func_un = 2.*(expterm + exp1*(wz_re*cos1 - wz_im*sin1));
  Double_t func = norm*func_un;

  return func;
}
