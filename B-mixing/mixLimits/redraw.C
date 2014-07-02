void redraw(){

  /* ---- DM SET TO 1000 IN MC --------------------------- */

  TFile vardmf2("vardm2-2.root");
  TGraphErrors *g3 = (TGraphErrors*)vardmf2.Get("Dilvsdm");
  TGraph *g4 = (TGraphErrors*)vardmf2.Get("DilErrvsdm");

  vardmf2.Close();

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(111111);

  TCanvas *vardm2 = new TCanvas("vardm2","vardm2",800,400);
  vardm2->Divide(2,1);
  
  vardm2->cd(1);
  g3->GetXaxis()->SetTitle("dm");
  g3->GetXaxis()->CenterTitle();
  g3->GetYaxis()->SetTitle("Dilution (1-2alpha)");
  g3->GetYaxis()->CenterTitle();
  //g3->SetMarkerStyle(21);
  //g3->SetMarkerSize(1);
  g3->Draw("AP*");

  vardm2->cd(2);
 
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  
  g4->GetXaxis()->SetTitle("dm");
  g4->GetXaxis()->CenterTitle();
  g4->GetYaxis()->SetTitle("Dil. Err");
  g4->GetYaxis()->CenterTitle();
  //g4->SetMarkerStyle(21);
  //g4->SetMarkerSize(1);
  g4->Draw("AP*"); 
  g4->Fit("expo");

  TFile vardmf("vardm-2.root");
  TGraphErrors *g1 = (TGraphErrors*)vardmf.Get("Dilvsdm");
  TGraph *g2 = (TGraphErrors*)vardmf.Get("DilErrvsdm");

  vardmf.Close();

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(111111);
  TCanvas *vardm = new TCanvas("vardm","vardm",800,400);
  vardm->Divide(2,1);
  
  vardm->cd(1);
  g1->GetXaxis()->SetTitle("dm");
  g1->GetXaxis()->CenterTitle();
  g1->GetYaxis()->SetTitle("Dilution (1-2alpha)");
  g1->GetYaxis()->CenterTitle();
  //g1->SetMarkerStyle(21);
  //g1->SetMarkerSize(1);
  g1->Draw("AP*");

  vardm->cd(2);
 
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  
  g2->GetXaxis()->SetTitle("dm");
  g2->GetXaxis()->CenterTitle();
  g2->GetYaxis()->SetTitle("Dil. Err");
  g2->GetYaxis()->CenterTitle();
  //g2->SetMarkerStyle(21);
  //g2->SetMarkerSize(1);
  g2->Draw("AP*"); 
  g2->Fit("expo");





}
