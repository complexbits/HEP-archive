void test()
  //#include "complex_io.hh";
  //#include "complex.h"
{

  RooComplex a(2,3);
  RooComplex b(1,3);
  RooComplex c, d;

  c = a + b;
  d = a + b.conj();

  cout << "HELP  " << endl;
  cout << "Test  " << c.re() << "  " << d.im() << endl;

  RooComplex oErf = RooMath::ComplexErrFunc(10,3);
  cout << "Erfi  " << oErf.re() << "  " << oErf.im() << "i" << endl;

  // Likelihood function

  Double_t arg1_re = 2.*t*t0 + s*s*(dm*dm*t0*t0 - 1.);
  Double_t arg1_im = 2*dm*t0*(t*t0 - s*s);

  Double_t arg2_re = dm*s*s*t0;
  Double_t arg2_im = t*t0 - s*s;

  Double_t term1 = TMath::Exp(-arg1_re);
  Double_t term2 = TMath::Cos(arg1_im);
  Double_t term3 = TMath::Sin(arg1_im);

  RooComplex term4 = ComplexErrFunc(arg2_re,arg2_im);
  Double_t term4_re = 1 - term4.re();
  Double_t term4_im = -term.im();

  Double_t func_un = term4_re*term2_im + term4_re*term3;

  Double_t norm = ((1 + dm*dm*t0*t0)/t0)*
    (1./(TMath::Sqrt[TMath::TwoPi]*s));
  Double_t func = norm*func_un;
}
