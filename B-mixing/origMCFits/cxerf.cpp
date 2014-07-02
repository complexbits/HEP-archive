/*

This is an adaptation of the CernLib Complex Error Function CWERF, 
based on the translation included with the RooFit libraries.
This version is a little more C++ified and readable, so that if there
are discrepancies with other calculations for w(z), they're easier to 
find and fix.

The include file "complexmath.h" contains all of the double-precision
complex operations required for the calculations.


*/
#ifndef __COMPLEX_MATH__
#include "complexmath.h"
#endif

Complex_t cxerf(Double_t re, Double_t im)
{
  return cxerf(Complex_t(re,im));
}

Complex_t cxerf(Complex_t& z)
{
  Complex_t wz,T,S;

  Complex_t R[38];
  Complex_t zero(0.,0.);

  //Double_t twosqrtpi =  2 / TMath::Sqrt(TMath::Pi());
  Double_t twosqrtpi = 1.128379167095512558560699289955664426088333129883;

  Double_t x=re(z);
  Double_t y=im(z);
  Double_t xabs=fabs(x);
  Double_t yabs=fabs(y);

  Complex_t zh1(yabs+1.6, xabs);
  Complex_t zh2(yabs, xabs);

  if ((yabs < 7.4) && (xabs < 8.3)){
    R[37] = zero;
    for (Int_t j = 36; j > 0; j--){
        T = zh1 + (conj(R[j+1]) * j);
        R[j] = (T * 0.5) / abs2(T); 
    } 
    for (Int_t j = 33; j > 0; j--){
        S = R[j] * ( S + pow(3.2,j-1) );    
    } 
    wz = S * twosqrtpi;


  }else{
    R[1] = zero;
    for (Int_t j = 9; j > 0, j--){
        T = zh2 + ( conj(R[1]) * j );
        R[j] = ( T * 0.5 ) / abs2(T);      
    }
    wz = R[1] * twosqrtpi;
  } 

 
  if ( yabs == 0 ){        // if Z lies on the real axis
    Double_t vre = TMath::Exp(-(xabs*xabs));
    Complex_t wzt(vre,im(wz));
    return wzt;

    
  }else if ( y < 0 ){  // if Z is below the imaginary axis
    Complex_t tmp(xabs,yabs);
    Complex_t wzt = (exp(-tmp*tmp) * 2) - wz;
 
    if ( x > 0 ){     // Z in quadrant 4
      return conj(wzt);
    }else{            // Z in quadrant 3 or X=0  
      return wzt;
    }    


  }else if ( y > 0 ){   // if Z is above the imaginary axis

    if ( x < 0 ){       // Z in quadrant 2
      return conj(wz);
    }else{              // Z in quadrant 1 or X=0
      return wz;
    }
  }
}










