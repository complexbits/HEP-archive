void limits_plt()
{
  Double_t dm[100], mTag[100], err[100];
  Double_t dilN[100], errD[100], lim95[100];
  Double_t noErr[100];
  Int_t n;
  
  ifstream input;
  input.open("dm_10_ampout.dat");

  Int_t i=0;
  while(1){
    input >> dm[i] >> mTag[i] >> err[i];
    dilN[i] = -(1. - 2.*mTag[i])/.16;
    errD[i] = 2.*1.65*err[i]/0.16;
    lim95[i] = dilN[i] + 1.65*errD[i];
    noErr[i] = 0.;
    cout << i << "  " << dm[i] << "  " 
	 << mTag[i] << "  " << errD[i]
	 << endl;
    if (!input.good()){
      cout << "Break 1" << endl;
      break;
    }
    n = i++;
  }

  // Find limit
  Double_t x1, x2, y1, y2;
  Double_t slp = 999999.;
  Double_t xSig;

  // Change n to get nice plot
  n = 20;
  for  (i=0; i<n; i++){
    if (errD[i] < 1.){
      x1 = dm[i];
      y1 = errD[i];
    }
    if (errD[i] > 1. && slp == 999999.){
      x2 = dm[i];
      y2 = errD[i];
      slp = (y2-y1)/(x2-x1);
      xSig = (1. - (y1 - slp*x1))/slp;
      cout << x1 << "  " << x2 << "  " << y1 << "  " << y2 << endl;
      cout << "Significance = " << xSig << endl;
    }    
  }
  cout << "Significance = " << xSig << endl;

  //------- ADDED BY JAMIE FOR /STYLE/ :) ----------
  gROOT->SetStyle("Plain");

  gStyle->SetPadBorderSize(0);

  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.12);

  gStyle->SetTitleFontSize(0.07);
  gStyle->SetLabelSize(0.07,axis="xy");
  gStyle->SetTitleXSize(0.07);
  gStyle->SetTitleYSize(0.07);

  //------ END OF JAMIE'S /STYLE/ ADDITIONS --------

  TCanvas* limit = new TCanvas("limit","Limit",800,200);
  limit->Divide(2,1);
  TGraphErrors *gr1 = new TGraphErrors(n, dm, dilN, noErr, errD);
  TGraph *gr2 = new TGraph(n, dm, errD);

  Double_t xL[2] = {0., 22.};
  Double_t yL[2] = {1., 1.};
  TGraph *gr3 = new TGraph(2,xL,yL);
  gr3->SetLineColor(4);
  gr3->SetLineStyle(2);

  TGraph *gr4 = new TGraph(n, dm, lim95);
  
  limit->cd(1);
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerColor(2);
  gr1->SetLineColor(2);
  gr1->SetLineWidth(2);
  gr1->SetTitle("Amplitude");
  gr1->GetXaxis()->SetTitle("Delta Ms(ps-1)");
  gr1->GetYaxis()->SetTitle("Normalized Amplitde");
  gr1->Draw("LPA");

  limit->cd(2);
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerColor(2);
  gr2->SetLineColor(2);
  gr2->SetLineWidth(2);
  gr2->SetTitle("95% CL Sensitivity");
  gr2->SetMaximum(1.5);
  gr2->GetXaxis()->SetTitle("Delta Ms(ps-1)");
  gr2->GetYaxis()->SetTitle("95% CL");
  gr2->Draw("ALP");
  gr3->Draw("L");

  gr4->SetMarkerStyle(22);
  gr4->SetMarkerColor(4);
  gr4->SetLineColor(4);
  gr4->SetLineWidth(2);

  //gr4->Draw("LP");

  limit->Print("/home/gut/work/research/d0/studies/wrk_in_prgs/amplitude/docs/talk_8-5-04/figs/unbin_amp_fnd.eps");
}
