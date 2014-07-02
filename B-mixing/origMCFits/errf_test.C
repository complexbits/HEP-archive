/*
  Calculates values for mix() and uNmix() vs. t for varying
  values of tSigma.
  Functions mix() and uNmix() are included at the end.
*/

//------ Initial values:

Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma = 1;

Double_t tsmax=9.;

Double_t umfunc_val;
Double_t mfunc_val;
Double_t umpars[4];
Double_t mpars[4];


void errf_test(){

  //---- Loop over tSigma values
  for (Int_t ts=7; ts<tsmax; ts++){

    tSigma = 1 - (ts/10.);
    
    //---- Make a table header for the list of values
    printf("\n=========[tSigma=%3.1f]=========\n\n",tSigma);
    printf("    lt  umfunc_val   mfunc_val\n");
    printf("  ----------------------------\n");



    //---- Loop over possible lifetime values
    for (Int_t jg=-4.; jg<20.; jg++){

      Float_t jt = jg/2.;
      //---- Run the functions
      umfunc_val = 2*uNmix(jt, tau, dm, tSigma);
      mfunc_val = 2*mix(jt, tau, dm, tSigma);
      
      //---- Output to the table the lifetime value and function result
      printf("  %4.1f   %8.6lf    %8.4lf\n",jt,umfunc_val,mfunc_val);
      
    }

  }


  //  TF1 *f1 = new TF1("f1", "lftmosc_plt(x,[0],[1],[2],[3])",-2,10)
  //f1->SetParameter(
}





//------- THE FUNCTIONS ---------------------------------------
Double_t lftmosc_plt(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func;

  if (tag == -1) func =uNmix(t, t0, dm, s);
  if (tag == 1) func = mix(t, t0, dm, s);

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

  //cout<<"      arg2_re="<<arg2_re<<", arg2_im="<<arg2_im<<endl;
  RooComplex wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);

  Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
  //cout<<"      expwz="<<expwz<<endl;
  Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
  Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

  Double_t wzre =  wz.re();
  Double_t wzim =  wz.im();
  //cout<<"      wzre="<<wzre<<", wzim="<<wzim<<endl;

  // Need to understand sign and real imaginary parts
  Double_t wz_im =   expwz*(wzre*coswz - wzim*sinwz);
  Double_t wz_re =  -expwz*(wzre*sinwz + wzim*coswz);

  // Mixed convoulted time dependent function


  //cout<<"      wz_re="<<wz_re<<", wz_im="<<wz_im<<endl<<endl;

  Double_t func_un = 2.*(expterm - exp1*(wz_re*sin1 + wz_im*cos1));
  Double_t func = norm*func_un;

  return func;
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

  Double_t wz_re =   expwz*(wzre*coswz - wzim*sinwz);
  Double_t wz_im =   expwz*(wzre*sinwz + wzim*coswz);

  // Unmixed convoulted time dependent function

  Double_t func_un = 2.*(expterm + exp1*(wz_re*cos1 - wz_im*sin1));
  Double_t func = norm*func_un;

  return func;
}
