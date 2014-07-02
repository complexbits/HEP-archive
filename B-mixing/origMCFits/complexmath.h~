/*******************************************************************************
 * This is a complex class based on the (very) simple "complex" type in CINT's
 * complex.h, RooComplex from the RooFit libraries, and the up-and-coming 
 * standard C++ type "complex" (from my /usr/include/complex.h).
 * 
 * In addition, this class adds seamlessly the ability to use exp(), sqrt(), and
 * abs() just as you would with any other type. 
 * [ie: exp(A), where A is of class Complex_t.]
 * 
 * It also adds arithmetic operations for use with other types, regardless of
 * the order they're called.
 * [ie: Complex_t B = 5.0*A = A*5.0, where A is of class Complex_t] 
 *
 * This file also includes the Complex Error Function of CERNlib and RooFit fame.
 * Notes on the function follow below, where the function is defined.
 * 
 * Jamie Hegarty hegarty@nhn.ou.edu
 *******************************************************************************/


#ifndef __COMPLEX_MATH__
#define __COMPLEX_MATH__

class Complex_t{

public:

  Double_t _re;
  Double_t _im;
  Complex_t () {};
  Complex_t (Double_t, Double_t);
  
  Complex_t& operator= (Complex_t& z) {
    if (&z==this) return *this ;
    this->_re = z._re;
    this->_im = z._im;
    return(*this);
  }

private:

  ClassDef(Complex_t,0) // a non-persistent bare-bones complex class

};

// for instantiation & deletion -----------------

Complex_t::Complex_t (Double_t a, Double_t b) { _re=a; _im=b; }

Complex_t::Complex_t () { _re=0.; _im=0.; }

~Complex_t::Complex_t () { delete _re; delete _im; }


//--- I/O stuff ----------------------------------
ostream& operator << (ostream& ios,Complex_t& z)
{
  ios << "(" << z._re << "," << z._im << ")" ;
  return ios;
}

ostrstream& operator << (ostrstream& ios,Complex_t& z)
{
  ios << "(" << z._re << "," << z._im << ")" ;
  return ios;
}

// unary operators -------------------------------
Complex_t Complex_t::operator- ()  
{
  Complex_t result(-_re,-_im);
  return result;
}

// binary operators ------------------------------
Complex_t Complex_t::operator + (Complex_t& z)  
{
  Double_t real = _re + z._re; 
  Double_t imag = _im + z._im;
  Complex_t result(real, imag);
  return result;
}
Complex_t Complex_t::operator - (Complex_t& z)
{
  Double_t real = _re - z._re;
  Double_t imag = _im - z._im;
  Complex_t result(real,imag);
  return result;
}
Complex_t Complex_t::operator * (Complex_t& z)
{
  Double_t real = _re*z._re - _im*z._im;
  Double_t imag = _re*z._im + _im*z._re;
  Complex_t result(real,imag);
  return result;
}
Complex_t Complex_t::operator / (Complex_t& z)  
{
  Double_t real = (_re*z._re + _im*z._im)/abs2(z);
  Double_t imag = (_im*z._re - _re*z._im)/abs2(z);
  Complex_t result(real,imag);
  return result;
}
Bool_t Complex_t::operator == (Complex_t& other)
{
  return ( _re == other._re &&  _im == other._im );
}

// binary operators for use with other types --------------------
// There are two of each to be sure that they commute properly

Complex_t operator / (Double_t& x, Complex_t& y)
{
  Double_t real = x * y._re / abs2(y);
  Double_t imag = -x * y._im / abs2(y);  
  Complex_t result(real,imag);
  return result;
}
Complex_t operator / (Complex_t& x, Double_t& y)
{
  Double_t real = x._re / y;
  Double_t imag = x._im / y;
  Complex_t result(real,imag);
  return result;
}
Complex_t operator + (Double_t& x, Complex_t& y)
{
  Double_t real = x + y._re;
  Double_t imag = y._im;
  Complex_t result(real,imag);
  return result;
}
Complex_t operator + (Complex_t& x, Double_t& y)
{
  Double_t real = x._re + y;
  Double_t imag = x._im;
  Complex_t result(real,imag);
  return result;
}
Complex_t operator - (Double_t& x, Complex_t& y)
{
  Double_t real = x - y._re;
  Double_t imag = -y._im;
  Complex_t result(real,imag);
  return result;
}
Complex_t operator - (Complex_t& x, Double_t& y)
{
  Double_t real = x._re - y;
  Double_t imag = x._im;
  Complex_t result(real,imag);
  return result;
}
Complex_t operator * (Double_t& x, Complex_t& y)
{
  Double_t real = x * y._re;
  Double_t imag = x * y._im;
  Complex_t result(real,imag);
  return result;
}
Complex_t operator * (Complex_t& x, Double_t& y)
{
  Double_t real = x._re * y;
  Double_t imag = x._im * y;
  Complex_t result(real,imag);
  return result;
}


// unary functions ------------------------------------

// returns the real part

Double_t Complex_t::re() 
{ 
  return _re; 
}
Double_t re(Complex_t& z) 
{ 
  return z.re(); 
}

// returns the imaginary part

Double_t Complex_t::im() 
{ 
  return _im; 
}
Double_t im(Complex_t& z) 
{ 
  return z.im(); 
}

// abs for complex argument

Double_t Complex_t::abs() 
{ 
  return TMath::Sqrt(_re*_re + _im*_im); 
}

// abs2 for complex argument

Double_t Complex_t::abs2() 
{ 
  return _re*_re + _im*_im; 
}
Double_t abs2(Complex_t& z) 
{ 
  return z.abs2(); 
}
// exponent with complex argument

Complex_t Complex_t::exp()
{
  Double_t mag=TMath::Exp(_re);

  Double_t real = mag*TMath::Cos(_im);
  Double_t imag = mag*TMath::Sin(_im);

  Complex_t result(real,imag);
  return result;  
}
Complex_t exp(Complex_t& z) 
{ 
  return z.exp(); 
}
// complex conjugate

Complex_t Complex_t::conj() 
{ 
  return Complex_t(_re,-_im); 
}
Complex_t conj(Complex_t& z) 
{ 
  return z.conj(); 
}
// sqrt with complex argument

Complex_t Complex_t::sqrt()
{
  Double_t arg = atan2(_im,_re)*0.5;
  Double_t mag = TMath::Sqrt(TMath::Sqrt(_re*_re + _im*_im));

  Double_t real = mag*TMath::Cos(arg);
  Double_t imag = mag*TMath::Sin(arg);

  Complex_t result(real,imag);
  return result;
}
Complex_t sqrt(Complex_t& z) 
{ 
  return z.sqrt(); 
}

/*******************************************************************************
 * What follows is an adaptation of the Complex Error Function, as translated 
 * from the CERNlib FORTRAN function CWERF(Z) to C++ in the RooFit library for
 * ComplexErrFunc(z).  This version produces exactly the same results in all
 * quadrants and with the same precision as the ComplexErrFunc(z) from the 
 * RooFit library.
 *
 * The method is Algorithm 363, as referenced in the CERNLib CWERF(Z) 
 * http://wwwasdoc.web.cern.ch/wwwasdoc/shortwrupsdir/c335/top.html
 *******************************************************************************/

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

 
  if ( yabs == 0 ){     // if Z lies on the real axis
    Double_t vre = TMath::Exp(-(xabs*xabs));
    Complex_t wzt(vre,im(wz));
    return wzt;

    
  }else if ( y < 0 ){   // if Z is below the real axis
    Complex_t tmp(xabs,yabs);
    Complex_t wzt = (exp(-tmp*tmp) * 2) - wz;
 
    if ( x > 0 ){       // Z in quadrant 4
      return conj(wzt);
    }else{              // Z in quadrant 3 or X=0  
      return wzt;
    }    


  }else if ( y > 0 ){   // if Z is above the real axis

    if ( x < 0 ){       // Z in quadrant 2
      return conj(wz);
    }else{              // Z in quadrant 1 or X=0
      return wz;
    }
  }
}

#endif
