void sample(){
  
  gROOT->SetStyle("Plain");
  
  Double_t p1x, p1y;
  Double_t p2x, p2y;
  Double_t ix, iy;
  
  TObjArray *a1 = new TObjArray(0);
    
  TCanvas *can1 = new TCanvas("sample", "sample", 400, 400);
  
  can1->SetGrid();
  
  TFile lhns("samplefit.root");
  TGraph *gs_1 = (TGraph*)lhns.Get("DilErrvsdm");
  gs_1->SetTitle("Sample Sensitivity Calculation");
  gs_1->SetName("gs_1");
  gs_1->GetXaxis()->SetTitle("dm");
  gs_1->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs_1->Draw("AP*");
  
  gs_1->GetPoint(7, p1x, p1y);
  gs_1->GetPoint(8, p2x, p2y);
  
  Double_t vs_1 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);
  
  a1.Add(gs_1);
  printf("vs1 = %8.4f\n",vs_1);

  TFile file1("sample.root", "recreate");
  a1.Write();
  file1.Close();

  }
