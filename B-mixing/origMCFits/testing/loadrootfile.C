void loadrootfile(){

fitfile = new TFile("cosfitpars.root", "read");

  fitparms = new TCanvas("fitparms", "fitparms", 800,400);

  fitparms->Divide(1,2);

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(111111);

  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistFillColor(18);

  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);


  fitparms->cd(1);
  h_cfpar->Draw();

  fitparms->cd(2);
  h_cferr->Draw();


  fitparms->Print("cosfitpars.ps");

}
