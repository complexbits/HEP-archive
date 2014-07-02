//#include "RooComplex/RooMath.cc"

//------ Initial values:

Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma = 1;

Double_t tsmax=10.;


void errf_test_jh(){
  
  //---- Loop over tSigma values
  for (Int_t ts=0; ts<tsmax; ts++){
    
    tSigma = 1 - (ts/10.);
    
    //tSigma = 0.1;

    //---- Make a table header for the list of values
    printf("\n=======================[tSigma=%3.1f]============================\n",tSigma);
      printf("   lt  | umfunc_val old_umfunc_val |  mfunc_val old_mfunc_val\n");
      printf("  ------------------------------------------------------------\n");


    //---- Loop over possible lifetime values
    for (Int_t jg=-4.; jg<20.; jg++){

      Float_t jt = jg/2.;

      //---- Run the functions
      Double_t umfunc_val = 2.*mixing(jt, tau, dm, tSigma,-1);
      Double_t mfunc_val = 2.*mixing(jt, tau, dm, tSigma,1);

      //---- Run the old functions to compare
      Double_t old_umfunc_val = 2.*old_uNmix(jt, tau, dm, tSigma);
      Double_t old_mfunc_val = 2.*old_mix(jt, tau, dm, tSigma);


      //---- Output to the table the lifetime value and function result

      printf("  %4.1f |  %8.6lf     %8.6lf    |  %8.6lf    %8.6lf\n",jt,umfunc_val,old_umfunc_val,mfunc_val,old_mfunc_val);
      
    }
    printf("  --------------------------------------------------------------\n");

  }
  

  
  gROOT->SetStyle("Plain");

  //-----------------------------------------------------------
  tSigma=0.2;

  TF1 *funmix = new TF1("funmix", lftmosc_plt,-4,15,4);
  funmix->SetParameters(1.5,0.51,tSigma,-1);
  
  TF1 *fmix = new TF1("fmix", lftmosc_plt,-4,15,4);
  fmix->SetParameters(1.5,0.51,tSigma,1);

  TF1 *fold_unmix = new TF1("fold_unmix", old_lftmosc_plt,-4,7.5,4);
  fold_unmix->SetParameters(1.5,0.51,tSigma,-1);
  fold_unmix->SetLineColor(2);
  fold_unmix->SetLineWidth(10);
  fold_unmix->SetLineStyle(3);
  fold_unmix->SetTitle("tSigma = 0.2");


  TF1 *fold_mix = new TF1("fold_mix", old_lftmosc_plt,-4,7.5,4);
  fold_mix->SetParameters(1.5,0.51,tSigma,1); 
  fold_mix->SetLineColor(2);
  fold_mix->SetLineWidth(10);
  fold_mix->SetLineStyle(3);

  //-----------------------------------------------------------
  tSigma=0.4;

  TF1 *funmix2 = new TF1("funmix2", lftmosc_plt,-4,15,4);
  funmix2->SetParameters(1.5,0.51,tSigma,-1);
  
  TF1 *fmix2 = new TF1("fmix2", lftmosc_plt,-4,15,4);
  fmix2->SetParameters(1.5,0.51,tSigma,1); 

  TF1 *fold_unmix2 = new TF1("fold_unmix2", old_lftmosc_plt,-4,15,4);
  fold_unmix2->SetParameters(1.5,0.51,tSigma,-1);
  fold_unmix2->SetLineColor(2);
  fold_unmix2->SetTitle("tSigma = 0.4");
  fold_unmix2->SetLineStyle(3);
  fold_unmix2->SetLineWidth(10);
   
  TF1 *fold_mix2= new TF1("fold_mix2", old_lftmosc_plt,-4,15,4);
  fold_mix2->SetParameters(1.5,0.51,tSigma,1);
  fold_mix2->SetLineColor(2);
  fold_mix2->SetLineStyle(3);
  fold_mix2->SetLineWidth(10);

  //---------------------------------------------------------
  tSigma=0.6;

  TF1 *funmix3 = new TF1("funmix3", lftmosc_plt,-4,15,4);
  funmix3->SetParameters(1.5,0.51,tSigma,-1);
  
  TF1 *fmix3 = new TF1("fmix3", lftmosc_plt,-4,15,4);
  fmix3->SetParameters(1.5,0.51,tSigma,1);

  TF1 *fold_unmix3 = new TF1("fold_unmix3", old_lftmosc_plt,-4,15,4);
  fold_unmix3->SetParameters(1.5,0.51,tSigma,-1);
  fold_unmix3->SetLineColor(2);
  fold_unmix3->SetTitle("tSigma = 0.6");
  fold_unmix3->SetLineStyle(3);
  fold_unmix3->SetLineWidth(10);

  TF1 *fold_mix3 = new TF1("fold_mix3", old_lftmosc_plt,-4,15,4);
  fold_mix3->SetParameters(1.5,0.51,tSigma,1); 
  fold_mix3->SetLineColor(2);
  fold_mix3->SetLineWidth(10);
  fold_mix3->SetLineStyle(3);

  //--------------------------------------------------------
  tSigma=0.8;

  TF1 *funmix4 = new TF1("funmix4", lftmosc_plt,-4,15,4);
  funmix4->SetParameters(1.5,0.51,tSigma,-1);
  
  TF1 *fmix4 = new TF1("fmix4", lftmosc_plt,-4,15,4);
  fmix4->SetParameters(1.5,0.51,tSigma,1); 

  TF1 *fold_unmix4 = new TF1("fold_unmix4", old_lftmosc_plt,-4,15,4);
  fold_unmix4->SetParameters(1.5,0.51,tSigma,-1);
  fold_unmix4->SetLineColor(2);
  fold_unmix4->SetTitle("tSigma = 0.8");
  fold_unmix4->SetLineStyle(3);
  fold_unmix4->SetLineWidth(10);
   
  TF1 *fold_mix4= new TF1("fold_mix4", old_lftmosc_plt,-4,15,4);
  fold_mix4->SetParameters(1.5,0.51,tSigma,1);
  fold_mix4->SetLineColor(2);
  fold_mix4->SetLineStyle(3);
  fold_mix4->SetLineWidth(10);

  //--------------------------------------------------------
  TCanvas *c2 = new TCanvas("c2","c2",1200,1000);
  c2->Divide(2,2);

  c2->cd(1);

  fold_unmix->Draw();
  fold_mix->Draw("SAME");
  funmix->Draw("SAME");
  fmix->Draw("SAME");


  c2->cd(2);
  fold_unmix2->Draw();
  fold_mix2->Draw("SAME");
  funmix2->Draw("SAME");
  fmix2->Draw("SAME");


  c2->cd(3);

  fold_unmix3->Draw();
  fold_mix3->Draw("SAME");
  funmix3->Draw("SAME");
  fmix3->Draw("SAME");


  c2->cd(4);

  fold_unmix4->Draw();
  fold_mix4->Draw("SAME");
  funmix4->Draw("SAME");
  fmix4->Draw("SAME");

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

  if (tag == -1) func = mixing(t, t0, dm, s,tag);
  if (tag == 1) func = mixing(t, t0, dm, s,tag);

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
