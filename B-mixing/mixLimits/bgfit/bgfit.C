/* --------------
   Fit some data 
   -------------- */


Int_t nBins = 50.;
Double_t min = -4.;
Double_t max = 15.;

Int_t nEvts = 50728.;
Double_t mass[100000];
Double_t lifetime[100000];

Double_t bgp[9];
Double_t C1,C2,C3,A1,A2,M1,M2,S1,S2;

void bgfit()
{

  TH1F *hlt = new TH1F("hlt","Lifetime", nBins, min, max);
  TH1F *hm = new TH1F("hm","Mass", nBins, 1.6, 2.2);

  TH1F *hlt_cuts = new TH1F("hlt_cuts","Lifetime w/ cuts", nBins, 0.5, 8.);
  TH1F *hm_cuts = new TH1F("hm_cuts","Mass w/ cuts", nBins, 1.9, 2.05);  


  ifstream infile;
  infile.open("data.txt");

  for(Int_t i=0.; i<nEvts; i++)
  {
    infile >> mass[i] >> lifetime[i];
    
    hlt->Fill(lifetime[i]);
    hm->Fill(mass[i]);

    if (mass[i] > 1.9 && mass[i] < 2.05){
          hlt_cuts->Fill(lifetime[i]);
	  hm_cuts->Fill(mass[i]);
    }

  }

  infile.close();

  
  TF1 *fit1 = new TF1("fit1", "[0]+[1]*x+[2]*x*x + [3]*TMath::Gaus(x,[4],[5]) + [6]*TMath::Gaus(x,[7],[8])",1.6,2.2);
  // location of the first signal
  fit1->SetParLimits(4,1.85,1.87);
  fit1->SetParLimits(5,0.02,0.08);
  // location of the second signal
  fit1->SetParLimits(7,1.93,1.98);
  fit1->SetParLimits(8,0.03,0.07);


  gStyle->SetOptFit(1100);

  TCanvas *ltdata = new TCanvas("ltdata","ltdata",1200,900);
  ltdata->Divide(2,2);
  ltdata->cd(1);
  hlt->Draw();

  ltdata->cd(2);
  hm->Draw();
  hm->Fit("fit1");

  fit1->GetParameters(bgp);

  /*
    TF1 *back = new TF1("back", "bgp[0]+bgp[1]*x+bgp[2]*x*x",1.6,2.2,0);
    
    TF1 *gaus1 = new TF1("gaus1","bgp[3]*TMath::Gaus(x,bgp[4],bgp[5])" ,1.6,2.2,0);
    TF1 *gaus2 = new TF1("gaus2", "bgp[6]*TMath::Gaus(x,bgp[7],bgp[8])",1.6,2.2,0);
    
    back->SetLineColor(3);
    back->Draw("SAME");
    gaus1->Draw("SAME");
    gaus2->Draw("SAME");
  */

  ltdata->cd(3);
  hlt_cuts->Draw();
  hlt_cuts->Fit("expo");

  ltdata->cd(4);
  hm_cuts->Draw();

}



