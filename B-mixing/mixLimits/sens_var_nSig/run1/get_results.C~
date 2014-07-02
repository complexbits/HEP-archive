void get_results(){
  
  gROOT->SetStyle("Plain");
  
  printf("\n");
  printf(" ---------------------------------------------------------------------------\n");
  printf("                Sensitivity vs. nSig and Sigma in Fit\n");
  printf(" ---------------------------------------------------------------------------\n");
  printf(" nSig / SigFit--> |    0.1   |   0.2   |   0.3   |   0.4   |  W. Avg  (val) \n");
  printf(" ---------------------------------------------------------------------------\n");

  
  Double_t p1x, p1y;
  Double_t p2x, p2y;
  Double_t ix, iy;
  
  TObjArray *a1 = new TObjArray(0);
  
  TGraph *graph0130 = new TGraph(5);
  graph0130->SetTitle("Sensitivity vs. Sig-fit");
  graph0130->SetName("graph0130");
  
  TGraph *graph1 = new TGraph(5);
  graph1->SetTitle("Sensitivity vs. Sig-fit");
  graph1->SetName("graph1");
  
  TGraph *graph0196 = new TGraph(5);
  graph0196->SetTitle("Sensitivity vs. Sig-fit");
  graph0196->SetName("graph0196");
  
  TCanvas *can1 = new TCanvas("can1", "varfits1", 1500, 900);
  can1->Divide(5,3);
  
  /***************************************************************************
     nSig = 0.130							      
   ****************************************************************************/
  
  // =================== nsig=0.130, tSig=0.1 Sig-fit=0.1 ==================
  can1->cd(1);
  gPad->SetGrid();
  
  TFile lhns("varsig0130_1.root");
  TGraph *gs130_1 = (TGraph*)lhns.Get("DilErrvsdm");
  gs130_1->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=0.1");
  gs130_1->SetName("gs130_1");
  gs130_1->GetXaxis()->SetTitle("dm");
  gs130_1->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs130_1->Draw("AP*");
  
  gs130_1->GetPoint(16, p1x, p1y);
  gs130_1->GetPoint(17, p2x, p2y);
  
  Double_t vs130_1 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);
  
  graph0130->SetPoint(0,0.1,vs130_1);
  
  a1.Add(gs130_1);
  
  // =================== nsig=0.130, tSig=0.1 Sig-fit=0.2 ==================
  can1->cd(2);
  gPad->SetGrid();
  
  TFile lhns("varsig0130_2.root");
  TGraph *gs130_2 = (TGraph*)lhns.Get("DilErrvsdm");
  gs130_2->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=0.2");
  gs130_2->SetName("gs130_2");
  gs130_2->GetXaxis()->SetTitle("dm");
  gs130_2->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs130_2->Draw("AP*");
  
  gs130_2->GetPoint(14, p1x, p1y);
  gs130_2->GetPoint(15, p2x, p2y);
  
  Double_t vs130_2 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);
  
  graph0130->SetPoint(1,0.2,vs130_2);
  
  a1.Add(gs130_2);
  
  // =================== nsig=0.130, tSig=0.1 Sig-fit=0.3 ====================
  can1->cd(3);
  gPad->SetGrid();
  
  TFile lhns("varsig0130_3.root");
  TGraph *gs130_3 = (TGraph*)lhns.Get("DilErrvsdm");
  gs130_3->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=0.3");
  gs130_3->SetName("gs130_3");
  gs130_3->GetXaxis()->SetTitle("dm");
  gs130_3->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs130_3->Draw("AP*");
  
  gs130_3->GetPoint(10, p1x, p1y);
  gs130_3->GetPoint(11, p2x, p2y);
  
  Double_t vs130_3 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);
  
  graph0130->SetPoint(2,0.3,vs130_3);
  
  a1.Add(gs130_3);
  
  // =================== nsig=0.130, tSig=0.1 Sig-fit=0.4 ====================
  can1->cd(4);
  gPad->SetGrid();
  
  TFile lhns("varsig0130_4.root");
  TGraph *gs130_4 = (TGraph*)lhns.Get("DilErrvsdm");
  gs130_4->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=0.4");
  gs130_4->SetName("gs130_4");
  gs130_4->GetXaxis()->SetTitle("dm");
  gs130_4->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs130_4->Draw("AP*");
  
  gs130_4->GetPoint(13, p1x, p1y);
  gs130_4->GetPoint(14, p2x, p2y);
  
  Double_t vs130_4 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);
  
  graph0130->SetPoint(3,0.4,vs130_4);
  
  a1.Add(gs130_4);
  
  // =================== nsig=0.130, tSig=0.1 Sig-fit=Avg =====================
  can1->cd(5);
  gPad->SetGrid();
  
  TFile lhns("varsig0130_a.root");
  TGraph *gs130_a = (TGraph*)lhns.Get("DilErrvsdm");
  gs130_a->SetTitle("nSig=0.130, tSig=0.1, Sig-fit=Avg");
  gs130_a->SetName("gs130_a");
  gs130_a->GetXaxis()->SetTitle("dm");
  gs130_a->GetYaxis()->SetTitle("95% CL");

  TGraph *gs130_sf = (TGraph*)lhns.Get("SigFit");
  gs130_sf->SetTitle("Sigma_Avg in Fit vs. dm , nSig=0.130");
  gs130_sf->SetName("gs130_sf");
  gs130_sf->GetXaxis()->SetTitle("dm");
  gs130_sf->GetYaxis()->SetTitle("Sigma in Fit");
  
  lhns.Close();
  
  gs130_a->Draw("AP*");
  
  gs130_a->GetPoint(12, p1x, p1y);
  gs130_a->GetPoint(13, p2x, p2y);
  
  Double_t vs130_a = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph0130->SetPoint(4,0.270111,vs130_a);

  a1.Add(gs130_a);
  a1.Add(gs130_sf);

  printf("       0.130      |  %5.3f  |  %5.3f  |  %5.3f  |  %5.3f  |  %5.3f (0.270) \n",vs130_1,vs130_2,vs130_3,vs130_4,vs130_a);

   //----------- plot the sig-fit vs. dm; histogram sig-fit  ----- 
  TCanvas *c0130sf = new TCanvas("Sigfit_vs_dm_0130", "graph0130sf", 800, 400);
  c0130sf->Divide(2,1);
  c0130sf->cd(1);
  gPad->SetGrid();
  gs130_sf->Draw("AP*");
  
  c0130sf->cd(2);
  TH1F *hs0130_sf = new TH1F("hs0130_sf", "SigFit spread, nSig=0.130", 10, 0.26, 0.28);
  for (Int_t i=0.; i<20.; i++){
    gs130_sf->GetPoint(i,ix,iy);
    //cout << i << ", "<< ix << ", "<< iy <<endl;
    hs0130_sf->Fill(iy);
  }
  gPad->SetGrid();
  hs0130_sf->Draw();

  a1.Add(hs0130_sf);
  a1.Add(c0130sf);
  //--------------- plot the sensitivity vs sig-fit -----------
  TCanvas *c0130 = new TCanvas("Sens_vs_sigfit_0130", "graph0130", 400, 400);
  c0130->SetGrid();
  graph0130->GetXaxis()->SetTitle("Sigma in fit");
  graph0130->GetYaxis()->SetTitle("Sensitivity");
  graph0130->Draw("AP*");

  a1.Add(graph0130);
  a1.Add(c0130);

 
  /***************************************************************************
	nSig = 0.163								      
   **************************************************************************/

  //  ================== nsig=0.163, tSig=0.1 Sig-fit=0.1 ==================
  can1->cd(6);
  gPad->SetGrid();
  
  TFile lhns("varsigma_1.root");
  TGraph *gs1 = (TGraph*)lhns.Get("DilErrvsdm");
  gs1->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.1");
  gs1->SetName("gs1");
  gs1->GetXaxis()->SetTitle("dm");
  gs1->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs1->Draw("AP*");
 
  gs1->GetPoint(16, p1x, p1y);
  gs1->GetPoint(17, p2x, p2y);

  Double_t vs1 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(0,0.1,vs1);
 
  a1.Add(gs1);
 
  //  ================== nsig=0.163, tSig=0.1 Sig-fit=0.2 ==================
  can1->cd(7);
  gPad->SetGrid();
  
  TFile lhns("varsigma_2.root");
  TGraph *gs2 = (TGraph*)lhns.Get("DilErrvsdm");
  gs2->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.2");
  gs2->SetName("gs2");
  gs2->GetXaxis()->SetTitle("dm");
  gs2->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs2->Draw("AP*");
 
  gs2->GetPoint(14, p1x, p1y);
  gs2->GetPoint(15, p2x, p2y);

  Double_t vs2 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(1,0.2,vs2);

  a1.Add(gs2);
 
  //  ================== nsig=0.163, tSig=0.1 Sig-fit=0.3 ==================
  can1->cd(8);
  gPad->SetGrid();
  
  TFile lhns("varsigma_3.root");
  TGraph *gs3 = (TGraph*)lhns.Get("DilErrvsdm");
  gs3->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.3");
  gs3->SetName("gs3");
  gs3->GetXaxis()->SetTitle("dm");
  gs3->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs3->Draw("AP*");
 
  gs3->GetPoint(10, p1x, p1y);
  gs3->GetPoint(11, p2x, p2y);

  Double_t vs3 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(2,0.3,vs3);
  
   a1.Add(gs3);

  // ================== nsig=0.163, tSig=0.1 Sig-fit=0.4 ==================
  can1->cd(9);
  gPad->SetGrid();
  
  TFile lhns("varsigma_4.root");
  TGraph *gs4 = (TGraph*)lhns.Get("DilErrvsdm");
  gs4->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=0.4");
  gs4->SetName("gs4");
  gs4->GetXaxis()->SetTitle("dm");
  gs4->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs4->Draw("AP*");
 
  gs4->GetPoint(13, p1x, p1y);
  gs4->GetPoint(14, p2x, p2y);

  Double_t vs4 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(3,0.4,vs4);
  
  a1.Add(gs4);

  // ================== nsig=0.163, tSig=0.1 Sig-fit=Avg ==================
  can1->cd(10);
  gPad->SetGrid();
  
  TFile lhns("varsigma_a.root");
  TGraph *gsa = (TGraph*)lhns.Get("DilErrvsdm");
  gsa->SetTitle("nSig=0.163, tSig=0.1, Sig-fit=Avg");
  gsa->SetName("gsa");
  gsa->GetXaxis()->SetTitle("dm");
  gsa->GetYaxis()->SetTitle("95% CL");

  TGraph *gs_sf = (TGraph*)lhns.Get("SigFit");
  gs_sf->SetTitle("Sigma_Avg in Fit vs. dm , nSig=0.163");
  gs_sf->SetName("gs_sf");
  gs_sf->GetXaxis()->SetTitle("dm");
  gs_sf->GetYaxis()->SetTitle("Sigma in Fit");

  lhns.Close();
  
  gsa->Draw("AP*");
 
  gsa->GetPoint(11, p1x, p1y);
  gsa->GetPoint(12, p2x, p2y);

  Double_t vsa = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph1->SetPoint(4,0.313349,vsa);
 
   a1.Add(gsa);
   a1.Add(gs_sf);

  printf("       0.163      |  %5.3f  |  %5.3f  |  %5.3f  |  %5.3f  |  %5.3f (0.313) \n",vs1,vs2,vs3,vs4,vsa);

   //----------- plot the sig-fit vs. dm; histogram sig-fit  ----- 
  TCanvas *csf = new TCanvas("Sigfit_vs_dm_0163", "graphsf", 800, 400);
  csf->Divide(2,1);
  csf->cd(1);
  gPad->SetGrid();
  gs_sf->Draw("AP*");
  
  csf->cd(2);
  TH1F *hs_sf = new TH1F("hs_sf", "SigFit spread, nSig=0.163", 10, 0.3, 0.325);
  for (Int_t i=0.; i<20.; i++){
    gs_sf->GetPoint(i,ix,iy);
    //cout << i << ", "<< ix << ", "<< iy <<endl;
    hs_sf->Fill(iy);
  }
  gPad->SetGrid();
  hs_sf->Draw();

  a1.Add(hs_sf);
  a1.Add(csf);

  //--------------- plot the sensitivity vs sig-fit -----------
  TCanvas *can2 = new TCanvas("Sens_vs_sigfit_0163", "graph1", 400, 400);
  can2->SetGrid();
  graph1->GetXaxis()->SetTitle("Sigma in fit");
  graph1->GetYaxis()->SetTitle("Sensitivity");
  graph1->Draw("AP*");

   a1.Add(graph1);
   a1.Add(can2);

  /***************************************************************************
	nSig = 0.196								      
   **************************************************************************/

  //  ================== nsig=0.196, tSig=0.1 Sig-fit=0.1 ==================
  can1->cd(11);
  gPad->SetGrid();
  
  TFile lhns("varsig0196_1.root");
  TGraph *gs196_1 = (TGraph*)lhns.Get("DilErrvsdm");
  gs196_1->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=0.1");
  gs196_1->SetName("gs196_1");
  gs196_1->GetXaxis()->SetTitle("dm");
  gs196_1->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs196_1->Draw("AP*");
 
  gs196_1->GetPoint(16, p1x, p1y);
  gs196_1->GetPoint(17, p2x, p2y);

  Double_t vs196_1 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph0196->SetPoint(0,0.1,vs196_1);

  a1.Add(gs196_1);

  // ================== nsig=0.196, tSig=0.1 Sig-fit=0.2 ====================
  can1->cd(12);
  gPad->SetGrid();
  
  TFile lhns("varsig0196_2.root");
  TGraph *gs196_2 = (TGraph*)lhns.Get("DilErrvsdm");
  gs196_2->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=0.2");
  gs196_2->SetName("gs196_2");
  gs196_2->GetXaxis()->SetTitle("dm");
  gs196_2->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs196_2->Draw("AP*");
 
  gs196_2->GetPoint(14, p1x, p1y);
  gs196_2->GetPoint(15, p2x, p2y);

  Double_t vs196_2 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph0196->SetPoint(1,0.2,vs196_2);

  a1.Add(gs196_2);

  // ================== nsig=0.196, tSig=0.1 Sig-fit=0.3 ==================
  can1->cd(13);
  gPad->SetGrid();
  
  TFile lhns("varsig0196_3.root");
  TGraph *gs196_3 = (TGraph*)lhns.Get("DilErrvsdm");
  gs196_3->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=0.3");
  gs196_3->SetName("gs196_3");
  gs196_3->GetXaxis()->SetTitle("dm");
  gs196_3->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs196_3->Draw("AP*");
 
  gs196_3->GetPoint(10, p1x, p1y);
  gs196_3->GetPoint(11, p2x, p2y);

  Double_t vs196_3 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph0196->SetPoint(2,0.3,vs196_3);

  a1.Add(gs196_3);

  // ================== nsig=0.196, tSig=0.1 Sig-fit=0.4 ==================
  can1->cd(14);
  gPad->SetGrid();
  
  TFile lhns("varsig0196_4.root");
  TGraph *gs196_4 = (TGraph*)lhns.Get("DilErrvsdm");
  gs196_4->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=0.4");
  gs196_4->SetName("gs196_4");
  gs196_4->GetXaxis()->SetTitle("dm");
  gs196_4->GetYaxis()->SetTitle("95% CL");
  lhns.Close();
  
  gs196_4->Draw("AP*");
 
  gs196_4->GetPoint(13, p1x, p1y);
  gs196_4->GetPoint(14, p2x, p2y);

  Double_t vs196_4 = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph0196->SetPoint(3,0.4,vs196_4);

  a1.Add(gs196_4);

  // ================== nsig=0.196, tSig=0.1 Sig-fit=Avg ==================
  can1->cd(15);
  gPad->SetGrid();
  
  TFile lhns("varsig0196_a.root");
  TGraph *gs196_a = (TGraph*)lhns.Get("DilErrvsdm");
  gs196_a->SetTitle("nSig=0.196, tSig=0.1, Sig-fit=Avg");
  gs196_a->SetName("gs196_a");
  gs196_a->GetXaxis()->SetTitle("dm");
  gs196_a->GetYaxis()->SetTitle("95% CL");

  TGraph *gs196_sf = (TGraph*)lhns.Get("SigFit");
  gs196_sf->SetTitle("Sigma(Avg) in Fit vs. dm (nSig=0.196)");
  gs196_sf->SetName("gs196_sf");
  gs196_sf->GetXaxis()->SetTitle("dm");
  gs196_sf->GetYaxis()->SetTitle("Sigma in Fit");
  lhns.Close();
  
  gs196_a->Draw("AP*");
 
  gs196_a->GetPoint(10, p1x, p1y);
  gs196_a->GetPoint(11, p2x, p2y);

  Double_t vs196_a = (((1-p1y)/(1-p2y))*p2x - p1x)/(((1-p1y)/(1-p2y))-1);

  graph0196->SetPoint(4,0.356301,vs196_a);

  a1.Add(gs196_a);
  a1.Add(gs196_sf);

  printf("       0.196      |  %5.3f  |  %5.3f  |  %5.3f  |  %5.3f  |  %5.3f (0.270) \n",vs196_1,vs196_2,vs196_3,vs196_4,vs196_a);

   //----------- plot the sig-fit vs. dm; histogram sig-fit  ----- 
  TCanvas *c0196sf = new TCanvas("Sigfit_vs_dm_0196", "graph0196sf", 800, 400);
  c0196sf->Divide(2,1);
  c0196sf->cd(1);
  gPad->SetGrid();
  gs196_sf->Draw("AP*");
  
  c0196sf->cd(2);
  TH1F *hs0196_sf = new TH1F("hs0196_sf", "SigFit spread, nSig=0.196", 10, 0.34, 0.37);
  for (Int_t i=0.; i<20.; i++){
    gs196_sf->GetPoint(i,ix,iy);
    //cout << i << ", "<< ix << ", "<< iy <<endl;
    hs0196_sf->Fill(iy);
  }
  gPad->SetGrid();
  hs0196_sf->Draw();

  a1.Add(hs0196_sf);
  a1.Add(c0196sf);

  //--------------- plot the sensitivity vs sig-fit -----------
  TCanvas *c0196 = new TCanvas("Sens_vs_sigfit_0196", "graph0196", 400, 400);
  c0196->SetGrid();
  graph0196->GetXaxis()->SetTitle("Sigma in fit");
  graph0196->GetYaxis()->SetTitle("Sensitivity");
  graph0196->Draw("AP*");

  a1.Add(graph0196);
  a1.Add(c0196);

  a1.Add(can1);
  can1->Close();

  /***************************************************************************
   **************************************************************************/

  printf(" ---------------------------------------------------------------------------\n");
  printf("\n");

  TCanvas *combined = new TCanvas("Sens_vs_dm_combined", "combined", 400, 400);
  combined->SetGrid();
  graph0130->SetMarkerColor(4);
  graph0130->SetMarkerStyle(4);
  graph0130->Draw("AP");
  graph1->SetMarkerColor(2);
  graph1->SetMarkerStyle(22);
  graph1->Draw("P");
  graph0196->SetMarkerColor(8);
  graph0196->SetMarkerStyle(28);
  graph0196->Draw("P");

  a1.Add(combined);

  TFile file1("get_results.root", "recreate");
  a1.Write();
  file1.Close();

  }
