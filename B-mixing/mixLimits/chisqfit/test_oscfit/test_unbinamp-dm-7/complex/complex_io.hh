/**************************************************************************
* iostream
**************************************************************************/
ostream& operator <<(ostream& ios,RooComplex& a)
{
        ios << "(" << a.re << "," << a.im << ")" ;
        return(ios);
}

ostrstream& operator <<(ostrstream& ios,RooComplex& a)
{
        ios << "(" << a.re << "," << a.im << ")" ;
        return(ios);
}

istream& operator >>(istream& ios,RooComplex& a)
{
        ios >> a.re >> b.re ;
        return(ios);
}

istrstream& operator >>(istrstream& ios,RooComplex& a)
{
  ios >> a.re >> b.re ;
  return(ios);
}

//#ifdef __CINT__
int G__ateval(const RooComplex& x) {
  cout << "(complex)" << x << endl;
  return(1);
}
//#endif
