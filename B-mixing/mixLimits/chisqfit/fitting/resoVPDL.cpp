void resoVPDL(Double_t x, Double_t rVal[3])
{
//========= Returns resolution for wide and narrow Gaussian and fraction
//========= From Rick Van Kooten

//  Double_t rVal[3];

// Paramters of fit
   Double_t sign, sigw, sigc, frac;
   Double_t p0n, p1n, p2n;
   Double_t p0w, p1w, p2w;
   Double_t p0c, p1c, p2c;

   p0n = 2.12418e-03;
   p1n = 1.50815e-03;
   p2n = 1.87510e+01;
   p0w = 3.26639e-04;
   p1w = 6.55281e-03;
   p2w = 1.16181e+02;
   p0c = 9.34673e-04;
   p1c = 3.49873e-03;
   p2c = 1.36322e+02;

   sign = p0n + p1n/(1+ exp(-1*p2n*x));

   sigc = p0c + p1c/(1+ exp(-1*p2c*x)); 

   sigw = p0w + p1w/(1+ exp(-1*p2w*x));

   frac = (sigc - sign)/(sigw - sign);

   //printf("x = %5.3f  yn = %5.3e  yc = %5.3e  yw = %5.3e  frac = %5.3f\n",
   //	  x, yn[i], yc[i], yw[i], frac);
   
   rVal[0] = sigw;
   rVal[1] = sign;
   rVal[2] = frac;

//    return rVal;

}

