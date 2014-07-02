//#include "RooComplex/RooMath.cc"


#ifndef __COMPLEX_MATH__
#include "complexmath.h"
#endif

//------ Initial values:

Double_t tau = 1.5;
Double_t dm  = 1000;
Double_t tSigma = 1;

Double_t tsmax=10.;


void errf_test_jh_mac(){

  
  //---- Loop over tSigma values
  for (Int_t ts=0; ts<tsmax; ts++){
    
    tSigma = 1 - (ts/10.);
    

    //---- Make a table header for the list of values
    printf("\n==========[tSigma=%3.1f]================\n",tSigma);
      printf("   lt  | new_umfunc_val new_mfunc_val \n");
      printf(" ------------------------------------\n");


    //---- Loop over possible lifetime values
    for (Int_t jg=-4.; jg<20.; jg++){

      Float_t jt = jg/2.;

      //---- Run the old functions to compare
      Double_t new_umfunc_val = 2.*new_mixing(jt, tau, dm, tSigma,-1);
      Double_t new_mfunc_val = 2.*new_mixing(jt, tau, dm, tSigma,1);


      //---- Output to the table the lifetime value and function result

      printf("  %4.1f |  %8.6lf     %8.6lf\n",jt,new_umfunc_val,new_mfunc_val);
      
    }
    printf("  -------------------------------------\n");

  }
  
 
  
  gROOT->SetStyle("Plain");

  //-----------------------------------------------------------
  tSigma=0.2;


  TF1 *fnew_unmix = new TF1("fnew_unmix", new_lftmosc_plt,-4,7.5,4);
  fnew_unmix->SetParameters(1.5,0.51,tSigma,-1);
  fnew_unmix->SetLineColor(2);
  fnew_unmix->SetLineWidth(10);
  fnew_unmix->SetLineStyle(3);
  fnew_unmix->SetTitle("tSigma = 0.2");


  TF1 *fnew_mix = new TF1("fnew_mix", new_lftmosc_plt,-4,7.5,4);
  fnew_mix->SetParameters(1.5,0.51,tSigma,1); 
  fnew_mix->SetLineColor(2);
  fnew_mix->SetLineWidth(10);
  fnew_mix->SetLineStyle(3);

  //-----------------------------------------------------------
  tSigma=0.4;


  TF1 *fnew_unmix2 = new TF1("fnew_unmix2", new_lftmosc_plt,-4,15,4);
  fnew_unmix2->SetParameters(1.5,0.51,tSigma,-1);
  fnew_unmix2->SetLineColor(2);
  fnew_unmix2->SetTitle("tSigma = 0.4");
  fnew_unmix2->SetLineStyle(3);
  fnew_unmix2->SetLineWidth(10);
   
  TF1 *fnew_mix2= new TF1("fnew_mix2", new_lftmosc_plt,-4,15,4);
  fnew_mix2->SetParameters(1.5,0.51,tSigma,1);
  fnew_mix2->SetLineColor(2);
  fnew_mix2->SetLineStyle(3);
  fnew_mix2->SetLineWidth(10);

  //---------------------------------------------------------
  tSigma=0.6;


  TF1 *fnew_unmix3 = new TF1("fnew_unmix3", new_lftmosc_plt,-4,15,4);
  fnew_unmix3->SetParameters(1.5,0.51,tSigma,-1);
  fnew_unmix3->SetLineColor(2);
  fnew_unmix3->SetTitle("tSigma = 0.6");
  fnew_unmix3->SetLineStyle(3);
  fnew_unmix3->SetLineWidth(10);

  TF1 *fnew_mix3 = new TF1("fnew_mix3", new_lftmosc_plt,-4,15,4);
  fnew_mix3->SetParameters(1.5,0.51,tSigma,1); 
  fnew_mix3->SetLineColor(2);
  fnew_mix3->SetLineWidth(10);
  fnew_mix3->SetLineStyle(3);

  //--------------------------------------------------------
  tSigma=0.8;

  TF1 *fnew_unmix4 = new TF1("fnew_unmix4", new_lftmosc_plt,-4,15,4);
  fnew_unmix4->SetParameters(1.5,0.51,tSigma,-1);
  fnew_unmix4->SetLineColor(2);
  fnew_unmix4->SetTitle("tSigma = 0.8");
  fnew_unmix4->SetLineStyle(3);
  fnew_unmix4->SetLineWidth(10);
   
  TF1 *fnew_mix4= new TF1("fnew_mix4", new_lftmosc_plt,-4,15,4);
  fnew_mix4->SetParameters(1.5,0.51,tSigma,1);
  fnew_mix4->SetLineColor(2);
  fnew_mix4->SetLineStyle(3);
  fnew_mix4->SetLineWidth(10);

  //--------------------------------------------------------
  TCanvas *c2 = new TCanvas("c2","c2",1200,1000);
  c2->Divide(2,2);

  c2->cd(1);

  fnew_unmix->Draw();
  fnew_mix->Draw("SAME");


  c2->cd(2);

  fnew_unmix2->Draw();
  fnew_mix2->Draw("SAME");


  c2->cd(3);

  fnew_unmix3->Draw();
  fnew_mix3->Draw("SAME");


  c2->cd(4);

  fnew_unmix4->Draw();
  fnew_mix4->Draw("SAME");

 

}








//==============THE NEW FUNCTIONS======================================



//------- THE FUNCTIONS ---------------------------------------
Double_t new_lftmosc_plt(Double_t *x, Double_t *par)
{
  Double_t t   = x[0];
  Double_t t0  = par[0];
  Double_t dm  = par[1];
  Double_t s   = par[2];
  Int_t    tag = par[3];

  Double_t func;

  if (tag == -1) func = new_mixing(t, t0, dm, s,tag);
  if (tag == 1) func = new_mixing(t, t0, dm, s,tag);

  return func;

}

Double_t new_mixing(Double_t t, Double_t t0, Double_t dm, Double_t s, Double_t tag)
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

    Complex_t z(cc,-aa);

    Double_t wzreneg=(cxerf(z)).re();    
    Double_t evilterm=TMath::Exp(-(aa*aa))*wzreneg;

  }
  
  Double_t func = 1./(2.*t0)*TMath::Exp(bb)*( 1 + TMath::Erf(aa) - tag*evilterm );
  return func;

}
