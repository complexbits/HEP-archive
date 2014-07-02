/* 
   Tests values of various part of function uNmix to determine 
   when it gets unreasonable to calculate.
 */

void cerftest(){

  Double_t dm=0.51;
  Double_t t0=1.5;
  Double_t t;
  Double_t s;

  Double_t arg2_re;
  Double_t arg2_im;

  Double_t wzre;  
  Double_t wzim;

  Double_t expwz;
  Double_t coswz;
  Double_t sinwz;

  Double_t wz_im;
  Double_t wz_re;

  RooComplex wz;



  for (Int_t j=0.;j<5.;j++){
  cout<<endl;
  printf("   s    t  arg2_re arg2_im       wzre       wzim      coswz      sinwz     expwz     small       wz_re      wz_im\n");
  printf("-----------------------------------------------------------------------------------------------------------------");
    cout<<endl;
    s = 0.5 - (j/10.);

    for (Int_t k=0.;k<30.;k++){
    
      t = -2 + (k/2.);
      
      arg2_re = dm*s/(TMath::Sqrt(2.));
      arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);
      
      wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);
      
      wzre = wz.re();
      wzim = wz.im();
      
      expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
      coswz = TMath::Cos(2.*arg2_re*arg2_im);
      sinwz = TMath::Sin(2.*arg2_re*arg2_im);
      
      wz_re =  -expwz*(wzre*sinwz + wzim*coswz);
      small=(wzre*coswz - wzim*sinwz);
      wz_im =   expwz*(wzre*coswz - wzim*sinwz);
      
      printf("%4.2f %4.1f  %7.3f %7.2f %10.2e %10.2e %10.2e %10.2e %10.2e %10.2e %10.2e %10.2e\n",s,t,arg2_re,arg2_im,wzre,wzim,coswz,sinwz,expwz,small,wz_re,wz_im);
      
    }
  }
}
