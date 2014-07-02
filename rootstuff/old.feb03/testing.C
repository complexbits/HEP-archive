#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

void testing()
{

gStyle->SetFrameBorderMode(0); 
gStyle->SetHistFillColor(0);
gStyle->SetHistLineColor(1); 
gStyle->SetHistFillStyle(0); 
gStyle->SetHistLineStyle(1);  
gStyle->SetHistLineWidth(1);
gStyle->SetOptStat(0);
//gStyle->SetOptTitle(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetCanvasBorderMode(0); 

TFile finished_data("testing1.root","recreate");

TH1S *random1 = new TH1S("random1", "A Random Assortment of Data", 100, -3, 3);
	random1->SetLineColor(3);
TH1S *random2 = new TH1S("random2", "A Random Assortment of Data", 100, -3, 3);
TH1S *random3 = new TH1S("random3", "A Random Assortment of Data", 100, -3, 3);
TH1S *random4 = new TH1S("random4", "A Random Assortment of Data", 100, -3, 3);
TH1S *random5 = new TH1S("random5", "A Random Assortment of Data", 100, -3, 3);

random1 -> FillRandom("gaus", 500);
random2 -> FillRandom("gaus", 1000);
random3 -> FillRandom("gaus", 5000);
random4 -> FillRandom("gaus", 10000);
random5 -> FillRandom("gaus", 50000);

finished_data.Write();

 TBrowser *browser = new TBrowser();
}
Drawing(){
TCanvas *rdCanvas = new TCanvas("rdCanvas","Random Plots",600,750,600,750);
rdCanvas->Divide(2,2);

rdCanvas->cd(1);
 random1->Draw();

rdCanvas->cd(2);
random3->Draw();

rdCanvas->cd(2);
 gStyle->SetHistLineColor(2);
 random2->Draw("SAME");


rdCanvas->cd(3);
gStyle->SetHistLineColor(3);
random4->Draw();

rdCanvas->cd(4);
random5->Draw();

}




