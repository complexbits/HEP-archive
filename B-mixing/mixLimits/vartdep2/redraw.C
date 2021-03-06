void redraw(){

  cout << endl << endl;

  Double_t p1x, p1y;
  Double_t p2x, p2y;

  TCanvas *can1 = new TCanvas("can1", "varfits1", 900, 600);
  can1->Divide(3,3);
  /*
  // ----------- nSig=0.130, tSig=0.1; Sig-fit=W.Avg ----------
  can1->cd(1);
  
  TFile lhns("lhns0130a.root");
  TGraph *g0130a = (TGraph*)lhns.Get("DilErrvsdm");
  g0130a->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=W.Avg");
  lhns.Close();
  
  g0130a->Draw("AP*");
 
  g0130a->GetPoint(18, p1x, p1y);
  g0130a->GetPoint(19, p2x, p2y);

  Double_t ns0130adm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0130adm = "<< ns0130adm << endl;
  */
  // ----------- nSig=0.130, tSig=0.1; Sig-fit=0.296 ----------
  can1->cd(4);
  
  TFile lhns("lhns0130.root");
  TGraph *g0130 = (TGraph*)lhns.Get("DilErrvsdm");
  g0130->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=0.296");
  lhns.Close();
  
  g0130->Draw("AP*");
 
  g0130->GetPoint(18, p1x, p1y);
  g0130->GetPoint(19, p2x, p2y);

  Double_t ns0130dm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0130dm = "<< ns0130dm << endl;
  

   // ----------- nSig=0.130, tSig=0.1; Sig-fit=0.1 ----------
  can1->cd(7);
  
  TFile lhns("lhns0130nf.root");
  TGraph *g0130nf = (TGraph*)lhns.Get("DilErrvsdm");
  g0130nf->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=0.1");
  lhns.Close();
  
  g0130nf->Draw("AP*");
 
  g0130nf->GetPoint(18, p1x, p1y);
  g0130nf->GetPoint(19, p2x, p2y);

  Double_t ns0130nfdm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0130nfdm = "<< ns0130nfdm << endl; 
 

  // ----------- nSig=0.163, tSig=0.1; Sig-fit=W.Avg ----------
  can1->cd(2);
  
  TFile lhns("lhns0163a.root");
  TGraph *g0163a = (TGraph*)lhns.Get("DilErrvsdm");
  g0163a->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=W.Avg");
  lhns.Close();
  
  g0163a->Draw("AP*");
 
  g0163a->GetPoint(17, p1x, p1y);
  g0163a->GetPoint(18, p2x, p2y);

  Double_t ns0163adm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0163adm = "<< ns0163adm << endl;
  

  // ----------- nSig=0.163, tSig=0.1; Sig-fit=0.345 ----------
  can1->cd(5);
  
  TFile lhns("lhns0163.root");
  TGraph *g0163 = (TGraph*)lhns.Get("DilErrvsdm");
  g0163->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.345");
  lhns.Close();
  
  g0163->Draw("AP*");
 
  g0163->GetPoint(17, p1x, p1y);
  g0163->GetPoint(18, p2x, p2y);

  Double_t ns0163dm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0163dm = "<< ns0163dm << endl;
  

   // ----------- nSig=0.163, tSig=0.1; Sig-fit=0.1 ----------
  can1->cd(8);
  
  TFile lhns("lhns0163nf.root");
  TGraph *g0163nf = (TGraph*)lhns.Get("DilErrvsdm");
  g0163nf->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.1");
  lhns.Close();
  
  g0163nf->Draw("AP*");
 
  g0163nf->GetPoint(18, p1x, p1y);
  g0163nf->GetPoint(19, p2x, p2y);

  Double_t ns0163nfdm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0163nfdm = "<< ns0163nfdm << endl; 

 
  // ----------- nSig=0.196, tSig=0.1; Sig-fit=W.Avg ----------
  can1->cd(3);
  
  TFile lhns("lhns0196a.root");
  TGraph *g0196a = (TGraph*)lhns.Get("DilErrvsdm");
  g0196a->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=W.Avg");
  lhns.Close();
  
  g0196a->Draw("AP*");
 
  g0196a->GetPoint(17, p1x, p1y);
  g0196a->GetPoint(18, p2x, p2y);

  Double_t ns0196adm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0196adm = "<< ns0196adm << endl;
   

  // ----------- nSig=0.196, tSig=0.1; Sig-fit=0.393 ----------
  can1->cd(6);
  
  TFile lhns("lhns0196.root");
  TGraph *g0196 = (TGraph*)lhns.Get("DilErrvsdm");
  g0196->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=0.393");
  lhns.Close();
  
  g0196->Draw("AP*");
 
  g0196->GetPoint(17, p1x, p1y);
  g0196->GetPoint(18, p2x, p2y);

  Double_t ns0196dm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0196dm = "<< ns0196dm << endl;
  

  // ----------- nSig=0.196, tSig=0.1; Sig-fit=0.1 ----------
  can1->cd(9);
  
  TFile lhns("lhns0196nf.root");
  TGraph *g0196nf = (TGraph*)lhns.Get("DilErrvsdm");
  g0196nf->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=0.1");
  lhns.Close();
  
  g0196nf->Draw("AP*");
 
  g0196nf->GetPoint(18, p1x, p1y);
  g0196nf->GetPoint(19, p2x, p2y);

  Double_t ns0196nfdm = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  cout << " ns0196nfdm = "<< ns0196nfdm << endl; 
 
  cout << endl << endl; 
 

 // ===================stick everything into a pretty table ========================================

  printf("Significance for Dil=0.16, Sigma Varied: \n\n");
  printf(" nSigma-MC -> |   0.130    |   0.163    |   0.196    | MC \n");
  printf("---------------------------------------------------\n");
  printf("   W.Avg nS   |  %7.5f  |  %7.5f  |  %7.5f  |\n", ns0130adm, ns0163adm, ns0196adm);
  printf("---------------------------------------------------\n");
  printf("  sig at 1.5  |  %7.5f  |  %7.5f  |  %7.5f  |\n", ns0130dm, ns0163dm, ns0196dm);
  printf("-----------------------------------------------\n");
  printf("     0.10     |  %7.5f  |  %7.5f  |  %7.5f  |\n", ns0130nfdm, ns0163nfdm, ns0196nfdm);
  printf("-----------------------------------------------\n");
  printf("     Fit      |\n\n");
 


}
