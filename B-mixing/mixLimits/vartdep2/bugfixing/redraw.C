void redraw(){

  gROOT->SetStyle("Plain");

  cout << endl << endl;

  Double_t p1x, p1y;
  Double_t p2x, p2y;

  TGraph *graph1 = new TGraph(4);
  graph1->SetTitle("Sensitivity vs. Sig-fit");



  TCanvas *can1 = new TCanvas("can1", "varfits1", 1200, 300);
  can1->Divide(4,1);

  // ----------- nsig=0.163, tSig=0.1 Sig-fit=0.1 ----------
  can1->cd(1);
  gPad->SetGrid();
  
  TFile lhns("varsigma_1.root");
  TGraph *gs1 = (TGraph*)lhns.Get("DilErrvsdm");
  gs1->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.1");
  gs1->GetXaxis()->SetTitle("dm");
  gs1->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs1->Draw("AP*");
 
  gs1->GetPoint(4, p1x, p1y);
  gs1->GetPoint(5, p2x, p2y);

  Double_t vs1 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(1,0.1,vs1);

  cout << " vs1 = "<< vs1 << endl;
  

 
  // ----------- nsig=0.163, tSig=0.1 Sig-fit=0.2 ----------
  can1->cd(2);
  gPad->SetGrid();
  
  TFile lhns("varsigma_2.root");
  TGraph *gs2 = (TGraph*)lhns.Get("DilErrvsdm");
  gs2->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.2");
  gs2->GetXaxis()->SetTitle("dm");
  gs2->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs2->Draw("AP*");
 
  gs2->GetPoint(2, p1x, p1y);
  gs2->GetPoint(3, p2x, p2y);

  Double_t vs2 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(2,0.2,vs2);

  cout << " vs2 = "<< vs2 << endl;
  

 
  // ----------- nsig=0.163, tSig=0.1 Sig-fit=0.3 ----------
  can1->cd(3);
  gPad->SetGrid();
  
  TFile lhns("varsigma_3.root");
  TGraph *gs3 = (TGraph*)lhns.Get("DilErrvsdm");
  gs3->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.3");
  gs3->GetXaxis()->SetTitle("dm");
  gs3->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs3->Draw("AP*");
 
  gs3->GetPoint(1, p1x, p1y);
  gs3->GetPoint(2, p2x, p2y);

  Double_t vs3 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(3,0.3,vs3);

  cout << " vs3 = "<< vs3 << endl;
  
 
  // ----------- nsig=0.163, tSig=0.1 Sig-fit=0.4 ----------
  can1->cd(4);
  gPad->SetGrid();
  
  TFile lhns("varsigma_4.root");
  TGraph *gs4 = (TGraph*)lhns.Get("DilErrvsdm");
  gs4->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.4");
  gs4->GetXaxis()->SetTitle("dm");
  gs4->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs4->Draw("AP*");
 
  gs4->GetPoint(1, p1x, p1y);
  gs4->GetPoint(2, p2x, p2y);

  Double_t vs4 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(4,0.4,vs4);

  cout << " vs4 = "<< vs4 << endl;
  
  TCanvas *can2 = new TCanvas("can2", "graph1", 400, 400);
  can2->SetGrid();
  graph1->GetXaxis()->SetTitle("Sigma in fit");
  graph1->GetYaxis()->SetTitle("Sensitivity");
  graph1->Draw("AP*");

}
