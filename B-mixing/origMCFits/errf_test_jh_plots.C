//#include "RooComplex/RooMath.cc"

//------ Initial values:

Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma = 1;

Double_t tsmax=10.;

Double_t t0=tau;
Double_t s=tSigma;



void errf_test_jh_plots(){

  TGraph *umrat = new TGraph(10);
  umrat->SetName("umrat");
  umrat->SetTitle("UnMix Ratio times tSigma, vs. tSigma");
  TGraph *umrat2 = new TGraph(10);

  TGraph *umrat3 = new TGraph(10);

  TGraph *mrat = new TGraph(10);
  mrat->SetName("mrat");
  mrat->SetTitle("Mix Ratio at t=tSigma+2 vs tSigma");

  for (Int_t ts=0; ts<tsmax; ts++){

    tSigma = 1 - (ts/10.);

      //---- Run the functions
      Double_t umfunc_val =mixing(0, tau, dm, tSigma,-1);
      Double_t mfunc_val = mixing(tSigma, tau, dm, tSigma,1);

      //---- Run the old functions to compare
      Double_t old_umfunc_val = tSigma*old_uNmix(0, tau, dm, tSigma);
      Double_t old_mfunc_val = tSigma*old_mix(tSigma, tau, dm, tSigma); 

      Double_t umrat_val = old_umfunc_val/umfunc_val;
      umrat->SetPoint(ts,tSigma,umrat_val);
      umrat2->SetPoint(ts,tSigma,umrat_val);
      umrat3->SetPoint(ts,tSigma,umrat_val);

      Double_t mrat_val = old_mfunc_val/mfunc_val;
      mrat->SetPoint(ts,tSigma,mrat_val);

      cout<<tSigma<<"  "<<umrat_val<<"  "<<mrat_val<<endl;endl;

  }
  Double_t t=tSigma+2;
  Double_t aa = (t/(TMath::Sqrt(2.)*s)) - (s/TMath::Sqrt(2.)*t0);  
  Double_t bb = (s*s/(2.*t0*t0)) - t/t0;
  Double_t cc = s*dm/(TMath::Sqrt(2.));


  //TF1 *umrf = new TF1("umrf","2*cos(2*((2+x)/(1.41*x)-x/2.12)*x*0.354)*exp(0.9*x)",0.1,2);
  //TF1 *umrf = new TF1("umrf","[0]*cos(x/[1]-3.14)+[2])",0.1,1);
  //umrf->SetParameters(4,1.5,5);
  //TF1 *mrf = new TF1("mrf","[0]*cos(x*[1]-[2])+[3]",0.1,2);
  //mrf->SetParameter(2,6.28);
  //gStyle->SetOptFit(1111);
  gStyle->SetCanvasColor(1);
  gStyle->SetTextColor(10);
  gStyle->SetLabelColor(10);
  gStyle->SetTitleColor(10);
  TCanvas *c3 = new TCanvas("c3","c3",600,400);

  c3->SetGrid();

  umrat->GetXaxis()->SetTitle("tSigma");
  umrat->GetXaxis()->CenterTitle();
  umrat->GetXaxis()->SetAxisColor(10);
  umrat->GetYaxis()->SetTitle("umrat_val * tSigma");
  umrat->GetYaxis()->CenterTitle();
  umrat->GetYaxis()->SetTitleColor(10);
  umrat->GetYaxis()->SetAxisColor(10);
  umrat->GetYaxis()->SetLabelColor(10);
  umrat->SetMarkerSize(3);
  umrat->SetMarkerStyle(20);
  umrat->SetMarkerColor(1);
  umrat->SetLineColor(14);
  umrat->SetLineStyle(1);
  umrat->SetLineWidth(2);
  umrat->Draw("ALP");


  umrat2->SetMarkerSize(2);
  umrat2->SetMarkerStyle(29);
  umrat2->SetMarkerColor(51);
  umrat2->Draw("P");

  umrat3->SetMarkerSize(3);
  umrat3->SetMarkerStyle(24);
  umrat3->SetMarkerColor(14);
  umrat3->Draw("P");

  //umrat->Fit(umrf);
  //umrf->Draw("SAME");

  TCanvas *c4 = new TCanvas("c4","c4",600,400);
  c4->SetGrid();
  mrat->GetXaxis()->SetTitle("tSigma");
  mrat->GetXaxis()->CenterTitle();
  mrat->GetXaxis()->SetAxisColor(10);
  mrat->GetYaxis()->SetTitle("mrat_val");
  mrat->GetYaxis()->CenterTitle();
  mrat->GetYaxis()->SetTitleColor(10);
  mrat->GetYaxis()->SetAxisColor(10);
  mrat->GetYaxis()->SetLabelColor(10);
  mrat->SetLineStyle(1);
  mrat->SetLineColor(71);
  mrat->SetMarkerSize(3);
  mrat->SetMarkerStyle(29);
  mrat->SetMarkerColor(51);
  mrat->Draw("ALP");
  
}


//------- THE FUNCTIONS ---------------------------------------
Double_t lftmosc_plt(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func;

  if (tag == -1) func=mixing(t, t0, dm, s,tag);
  if (tag == 1) func=mixing(t, t0, dm, s,tag);

  return func;

}

Double_t mixing(Double_t t, Double_t t0, Double_t dm, Double_t s, Double_t tag)
{
  Double_t aa = (t/(TMath::Sqrt(2.)*s)) - (s/(TMath::Sqrt(2.)*t0));  
  Double_t bb = (s*s/(2.*t0*t0)) - t/t0;
  Double_t cc = s*dm/(TMath::Sqrt(2.));

  //--where aa gets large enough to make Exp(aa) outrageous.
  Double_t tcompare = 5.6*TMath::Sqrt(2.)*s - s*s/t0;
  
  if(t >= tcompare){
    //cout<<"approximation in effect"<<endl;
    Double_t evilterm=TMath::Exp(-(cc*cc))*2*TMath::Cos(2*aa*cc);
    
  }else if(t <= -tcompare){ 
    //cout<<"approximation in effect"<<endl;   
    Double_t evilterm=0;
    
  }else{

    RooComplex wz = RooMath::ComplexErrFunc(cc,-aa);
    Double_t wzreneg=wz.re();    
    Double_t evilterm=TMath::Exp(-(aa*aa))*wzreneg;

  }

  Double_t func = 1./(2.*t0)*TMath::Exp(bb)*( 1 + TMath::Erf(aa) - tag*evilterm );

  return func;

}





//==============THE OLD FUNCTIONS======================================



//------- THE FUNCTIONS ---------------------------------------
Double_t old_lftmosc_plt(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func;

  if (tag == -1) func =old_uNmix(t, t0, dm, s);
  if (tag == 1) func = old_mix(t, t0, dm, s);

  return func;

}
Double_t old_mix(Double_t t, Double_t t0, Double_t dm, Double_t s)
{
    // Normalization

  //Double_t norm = (1.+ dm*dm * t0*t0)/(8.*t0 + 4.*dm*dm * t0*t0*t0);
  Double_t norm = 1./(2*t0);

  // Exponential decay term

  Double_t argexp = (s*s - 2.*t*t0)/(2.*t0*t0);
  Double_t argerf = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);
  Double_t expterm = TMath::Exp(argexp)*(1+TMath::Erf(argerf));

  // Complex exponential term

  Double_t arg1_re = (2.*t*t0 + s*s*(dm*dm*t0*t0 - 1.))/(2.*t0*t0);
  Double_t arg1_im = (dm*(t*t0 - s*s))/t0;

  Double_t exp1 = TMath::Exp(-arg1_re);
  Double_t cos1 = TMath::Cos(-arg1_im);
  Double_t sin1 = TMath::Sin(-arg1_im);

  //Complex error function term

  Double_t arg2_re = dm*s/(TMath::Sqrt(2.));
  Double_t arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);


  RooComplex wz = RooMath::ComplexErrFunc(-arg2_re,-arg2_im);
  Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
  Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
  Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

  Double_t wzre =  wz.re();
  Double_t wzim =  wz.im();

  // Need to understand sign and real imaginary parts
  Double_t wz_im =   expwz*(wzre*coswz - wzim*sinwz);
  Double_t wz_re =  -expwz*(wzre*sinwz + wzim*coswz);

  // Mixed convoulted time dependent function

  Double_t func_un = (expterm - exp1*(wz_re*sin1 + wz_im*cos1));
  Double_t func = norm*func_un;

  return func;
}


Double_t old_uNmix(Double_t t, Double_t t0, Double_t dm, Double_t s)
{
    // Normalization

  //Double_t norm = (1.+ dm*dm * t0*t0)/(8.*t0 + 4.*dm*dm * t0*t0*t0);
  Double_t norm = 1./(2.* t0);

  // Exponential decay term

  Double_t argexp = (s*s - 2.*t*t0)/(2.*t0*t0);
  Double_t argerf = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);
  Double_t expterm = TMath::Exp(argexp)*(1+TMath::Erf(argerf));

  // Complex exponential term

  Double_t arg1_re = (2.*t*t0 + s*s*(dm*dm*t0*t0 - 1.))/(2.*t0*t0);
  Double_t arg1_im = (dm*(t*t0 - s*s))/t0;

  Double_t exp1 = TMath::Exp(-arg1_re);
  Double_t cos1 = TMath::Cos(-arg1_im);
  Double_t sin1 = TMath::Sin(-arg1_im);

  //Complex error function term

  Double_t arg2_re = dm*s/(TMath::Sqrt(2.));
  Double_t arg2_im = (t*t0 - s*s)/(TMath::Sqrt(2.)*s*t0);

  RooComplex wz = RooMath::ComplexErrFunc(arg2_re,-arg2_im);
  Double_t expwz = TMath::Exp(arg2_re*arg2_re - arg2_im*arg2_im);
  Double_t coswz = TMath::Cos(2.*arg2_re*arg2_im);
  Double_t sinwz = TMath::Sin(2.*arg2_re*arg2_im);

  Double_t wzre = wz.re();
  Double_t wzim = wz.im();

  Double_t wz_re =   expwz*(wzre*coswz - wzim*sinwz);
  Double_t wz_im =   expwz*(wzre*sinwz + wzim*coswz);

  // Unmixed convoulted time dependent function

  Double_t func_un = (expterm + exp1*(wz_re*cos1 - wz_im*sin1));
  Double_t func = norm*func_un;

  return func;
}
