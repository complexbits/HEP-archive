void tst_cwerf(){

  Double_t dm = 100.;
  Double_t t0 = 1.5;
  Double_t s  = 0.1;
  Double_t t  = 0.0;

  for (t=-2.; t<10.; t=t+.1){
    Double_t arg2_re = dm*s/(TMath::Sqrt(2.));
    Double_t arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);

    Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
    Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
    Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

    
    RooComplex wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);
    cout << t << "  " 
	 << arg2_re << "  " << arg2_im << "  "
	 << expwz << "  "
	 << wz.re() << "  " << wz.im() 
	 << "  " << expwz*wz.re() << "  " << expwz*wz.im()
	 << endl;
    cout << t << "  " << expwz*(wz.re()*coswz - wz.im()*sinwz)
	 << "  " << expwz*(wz.re()*sinwz + wz.im()*coswz)
	 << endl << endl;
  }
}
