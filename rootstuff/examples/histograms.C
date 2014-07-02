void histograms()
{
  // Set some style options 
  gStyle->SetFrameBorderMode(0); 
  gStyle->SetHistFillColor(10);  // Set the histogram fill color
  gStyle->SetHistLineColor(1); 
  gStyle->SetHistFillStyle(0); 
  gStyle->SetHistLineStyle(1);  
  gStyle->SetHistLineWidth(1);
  gStyle->SetOptStat(111111);   // Turn histogram statistic on or off
  //gStyle->SetOptTitle(0);
  gStyle->SetPadColor(10);     // Make the background white
  gStyle->SetCanvasColor(10);  // Make the background white
  gStyle->SetCanvasBorderMode(0); 

  // Open a new root file here, overwrite it if it exists
  TFile finished_data("randomtest.root","recreate");

  // Declare new Histograms
  TH1F *random1 = new TH1S("random1", "A Random Assortment of Data", 100, -3, 3);
  TH1F *random2 = new TH1S("random2", "A Random Assortment of Data", 100, -3, 3);
  TH1F *random3 = new TH1S("random3", "A Random Assortment of Data", 100, -3, 3);
  TH1F *random4 = new TH1S("random4", "A Random Assortment of Data", 100, -3, 3);
  TH1F *random5 = new TH1S("random5", "A Random Assortment of Data", 100, -3, 3);

  // Fill the Histograms with gaussians (by default, centered on 0)
  random1 -> FillRandom("gaus", 500);
  random2 -> FillRandom("gaus", 1000);
  random3 -> FillRandom("gaus", 5000);
  random4 -> FillRandom("gaus", 10000);
  random5 -> FillRandom("gaus", 50000);


  // Write out the root file
  finished_data.Write();

  // Open a TBrowser window
  TBrowser *browser = new TBrowser();

  // Start a new canvas
  TCanvas *rdCanvas = new TCanvas("rdCanvas","Random Plots",600,750,600,750);
  // Divide the canvas into 4 "pads"
  rdCanvas->Divide(2,2);

  // Switch to each pad, and draw a different histogram on each one

  rdCanvas->cd(1);
  random1->Draw();
  
  rdCanvas->cd(2);
  random3->Draw();
  
  // Draw another histogram on pad 2, with a different line style
  rdCanvas->cd(2);
  gStyle->SetHistLineStyle(2);
  random2->Draw("SAME");
  
  
  rdCanvas->cd(3);
  gStyle->SetHistLineStyle(1);
  random4->Draw();
  
  rdCanvas->cd(4);
  random5->Draw();

  rdCanvas->Print("rdCanvas.ps");

}

void hist_simple(){

TH1F *random5 = new TH1S("random1", "A Random Assortment of Data", 100, -3, 3);
random5 -> FillRandom("gaus", 500);
random5->Draw();

}





