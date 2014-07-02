#include "complexmath.h"
#include "cxerf.cpp"

void testing()
{
  
  gSystem->Load("libRooFitCore.so");
  gSystem->Load("libRooFitModels.so");
  
  printf("\n RooComplex operations: \n");

  RooComplex cx1(1.,-2);
  RooComplex cx2(3.,4.);

  Double_t d1 = 5.;
  printf("\n    cx1 = %2i + %2ii           | 1 + -2i\n",cx1.re(),cx1.im());
    printf("    cx2 = %2i + %2ii           | 3 + 4i\n",cx2.re(),cx2.im());
  printf("     d1 = %2i                 | 5\n",d1);
  printf("cx1*cx2 = %2i + %2ii          | 11 + -2i\n",(cx1*cx2).re(),(cx1*cx2).im());
  printf("cx1/cx2 = %4.1f + %4.1f        | -0.2 + -0.4i\n",(cx1/cx2).re(),(cx1/cx2).im());
  printf("cx1+cx2 = %2i + %2ii           | 4 + 2i\n",(cx1+cx2).re(),(cx1+cx2).im());
  printf("cx1-cx2 = %2i + %2ii           | -2 + -6i\n",(cx1-cx2).re(),(cx1-cx2).im());
  printf("cx1*cx2 = %2i + %2ii          | 11 + -2i\n",(cx1*cx2).re(),(cx1*cx2).im());
  printf(" cx1*d1 = %2i + %2ii           | 5 + -10i\n",(cx1*d1).re(),(cx1*d1).im());
  printf(" cx1/d1 = %4.1f + %4.1fi       | 0.33 + -0.5i\n",(cx1/d1).re(),(cx1/d1).im());
  printf(" cx1.exp() = %4.1f + %4.1fi    |\n",(cx1.exp()).re(),(cx1.exp()).im());
  printf(" cx1.abs() = %4.1f            | \n",cx1.abs());
  printf(" cx1.abs2() = %4.1f           | \n",cx1.abs2());
  printf(" cx1.conj() = %4.1f + %4.1fi   | \n",(cx1.conj()).re(),(cx1.conj()).im());
  printf(" cx1.sqrt() = %4.1f + %4.1fi   | \n",(cx1.sqrt()).re(),(cx1.sqrt()).im());
  printf(" ComplexErrFunc(cx1) = %4.1f + %4.1fi |\n\n",(RooMath::ComplexErrFunc(cx1)).re(), (RooMath::ComplexErrFunc(cx1)).im());

  printf("\n Jamie's complex operations: \n");

  Complex_t cx3(1.,-2);
  Complex_t cx4(3.,4.);
  Complex_t cx5 = cxerf(cx3);
  cout << cx5.re() << endl;

  Double_t d1 = 5.;
  printf("\n    cx3 = %2i + %2ii           | 1 + -2i\n",cx3.re(),cx3.im());
  printf("    cx4 = %2i + %2ii           | 3 + 4i\n",cx4.re(),cx4.im());
   printf("     d1 = %2i                 | 5\n",d1);
  printf("cx3*cx4 = %2i + %2ii          | 11 + -2i\n",(cx3*cx4).re(),(cx3*cx4).im());
  printf("cx3/cx4 = %4.1f + %4.1fi        | -0.2 + -0.4i\n",(cx3/cx4).re(),(cx3/cx4).im());
  printf("cx3+cx4 = %2i + %2ii           | 4 + 2i\n",(cx3+cx4).re(),(cx3+cx4).im());
  printf("cx3-cx4 = %2i + %2ii           | -2 + -6i\n",(cx3-cx4).re(),(cx3-cx4).im());
  printf("cx3*cx4 = %2i + %2ii          | 11 + -2i\n",(cx3*cx4).re(),(cx3*cx4).im());
  printf(" cx3*d1 = %2i + %2ii           | 5 + -10i\n",(cx3*d1).re(),(cx3*d1).im());
  printf(" cx3/d1 = %4.1f + %4.1fi        | 0.2 + -0.4i\n",(cx3/d1).re(),(cx3/d1).im());
  printf(" cx3.exp() = %4.1f + %4.1fi     |\n",(cx3.exp()).re(),(cx3.exp()).im());
  printf(" cx3.abs() = %4.1f            | \n",cx3.abs());
  printf(" cx3.abs2() = %4.1f           | \n",cx3.abs2());
  printf(" cx3.conj() = %4.1f + %4.1fi   | \n",(cx3.conj()).re(),(cx3.conj()).im());
  printf(" cx3.sqrt() = %4.1f + %4.1fi   | \n",(cx3.sqrt()).re(),(cx3.sqrt()).im());
  printf(" cxerf(cx3) = %4.1f + %4.1fi   | \n\n", cx5.re(), cx5.im());
  printf(" exp(cx3) = %4.1f + %4.1fi     |\n",(exp(cx3)).re(),(exp(cx3)).im());

  Complex_t cx6(2.,0.);
  Double_t d2 = 2.;
  printf(" cxerf(cx6) = %4.3e + %4.3ei, exp(-d2*d2) = %4.3e | \n", re(cxerf(cx6)), im(cxerf(cx6)), TMath::Exp(-(d2*d2)));
  
}
