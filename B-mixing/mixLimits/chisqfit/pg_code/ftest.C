void ftest(){
  Double_t arg2_re = 1.;
  Double_t arg2_im = 70.;
  RooComplex wz = RooMath::ComplexErrFunc(arg2_re,arg2_im);
  cout << "output = " << wz.re() << "  " << wz.im() << endl;
}
