/* 
   Calculates dm based on the cosine relationship between 
   mixed and unmixed ( Nu - Nm )/( Nu + Nm ) = cos(dm*t)

   run this file after (or include it after) filling histograms
   h_ltmix and h_ltunmix.
*/

void cos_fit(){


// ---- Open a file to update it ------
TFile* mixfile = new TFile("mixing2.root", "update");


// ------- Define a new array ---------
 TObjArray mixList2(0);

 //----- Define some new histograms and functions to use for fitting ----

 TH1F *h_ltmix1 = (TH1F*) h_ltmix->Clone();

 TH1F *h_ltunmix3 = (TH1F*) h_ltunmix->Clone();
 TH1F *h_ltunmix2 = (TH1F*) h_ltunmix->Clone();

 TH1F *h_ltunmix1 = (TH1F*) h_ltunmix->Clone();

 TF1 *f_cosfit = new TF1("f_cosfit", "cos([0]*x)",-4.,15.);
 f_cosfit->SetParLimits(0,0.3,0.9);

  mixpix = new TCanvas("mixpix", "mixpix", 800,600);
  mixpix->Divide(2,3);

  //----- Add all the stuff to the array -------
  mixList2.Add(h_ltmix1);
  mixList2.Add(h_ltunmix1);
  mixList2.Add(h_ltunmix2);
  mixList2.Add(h_ltunmix3);
  mixList2.Add(f_cosfit);
  mixList2.Add(mixpix);


  //---- Define some style stuff ------
  gStyle->SetOptStat(111111);

  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistFillColor(18);

  gStyle->SetPadColor(7);
  gStyle->SetCanvasColor(10);

  //---- Draw everything -------
  mixpix->cd(1);
  h_ltmix->Draw();
  //  f_ltmix->Draw("same");

  mixpix->cd(2);
  h_ltunmix->Draw();
  // f_ltunmix->Draw("same");

  mixpix->cd(3);
  h_ltime->Draw();
  h_ltunmix->Draw("same");
  h_ltmix->Draw("same");

  // f_ltmix->Draw("same");
  // f_ltunmix->Draw("same");

  mixpix->cd(4);
  //Do Nu + Nm:
  h_ltunmix2->Add(h_ltmix);
  h_ltunmix2->Draw();

  mixpix->cd(5);
  //Do Nu - Nm:
  h_ltmix1->Scale(-1);
  h_ltunmix1->Add(h_ltmix1);
  h_ltunmix3->Add(h_ltmix1);
  h_ltunmix3->Draw();

  mixpix->cd(6);
  //Do (Nu - Nm) / (Nu + Nm)
  h_ltunmix1->Divide(h_ltunmix2);
  h_ltunmix1->Draw();

  h_ltunmix1->Fit(f_cosfit);
  f_cosfit->Draw("same");

  mixpix->Print("mixpix.ps");

  //------ Write out and close the file -----
  mixList2.Write();
  //mixfile.CLose();

}
