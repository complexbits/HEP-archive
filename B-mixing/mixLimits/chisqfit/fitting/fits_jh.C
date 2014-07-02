void fits_jh()
{
  //Create a double-gauss function for fitting the vpdl diff
  TF1 *d_gaus = new TF1("d_gaus", "gaus(0)+gaus(3)", -maxLimit, maxLimit);
  d_gaus->SetParameters(0,0,0.25,0,0,0.5);
  d_gaus->FixParameter(1,0);
  d_gaus->FixParameter(4,0);



}
