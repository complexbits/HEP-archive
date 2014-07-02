void loadrootfile(){
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(111111);
  gStyle->SetOptFit(1111);
  
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistFillColor(18);
  
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);

  TFile *fitparms = new TFile("vartsig.root", "read");
  

  TCanvas *vartsig = new TCanvas("vartsig","vartsig",800,1200);

  vartsig->Divide(1,2);
  vartsig->cd(1);

  vartsig->SetFillColor(10);
  vartsig->SetGrid();
  
  g_vartsig->SetTitle("dm vs. tSigma, cosfit -4,15");
  g_vartsig->GetXaxis()->SetTitle("t_sig  (tSigma)");
  g_vartsig->GetXaxis()->CenterTitle();
  g_vartsig->GetYaxis()->SetTitle("cosfit_par2  (dm)");
  g_vartsig->GetYaxis()->CenterTitle();
  g_vartsig->SetMarkerStyle(21);
  g_vartsig->Draw("AP");
  g_vartsig->Fit("gaus");

  g_vtsavg->SetMarkerStyle(22);
  g_vtsavg->SetMarkerSize(2);
  g_vtsavg->SetMarkerColor(4);
  g_vtsavg->SetLineColor(4);
  g_vtsavg->Draw("CP");
  
  vartsig->cd(2);

  vartsig->SetFillColor(10);
  vartsig->SetGrid();
   
  g_vartsig2->SetTitle("dm vs. tSigma, cosfit 0,15");
  g_vartsig2->GetXaxis()->SetTitle("t_sig  (tSigma)");
  g_vartsig2->GetXaxis()->CenterTitle();
  g_vartsig2->GetYaxis()->SetTitle("cosfit_par  (dm)");
  g_vartsig2->GetYaxis()->CenterTitle();
  g_vartsig2->SetMarkerStyle(21);
  g_vartsig2->Draw("AP");
  g_vartsig2->Fit("gaus");

  g_vtsavg2->SetMarkerStyle(22);
  g_vtsavg2->SetMarkerSize(2);
  g_vtsavg2->SetMarkerColor(4);
  g_vtsavg2->SetLineColor(4);
  g_vtsavg2->Draw("CP");
  

}
