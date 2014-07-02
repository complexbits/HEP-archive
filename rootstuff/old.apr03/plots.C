{
// Remove stat box
gStyle->SetOptStat(kFALSE);
gStyle->SetOptTitle(kFALSE);

// ************************ mass *********************************

// Open first file, calculate normalization, and draw
pl1 = new TFile("plots_aa_rep.root","read");
//c1->SetLogy(0);
h_mass_2->GetXaxis()->SetLabelSize(0.05);
h_mass_2->GetYaxis()->SetLabelSize(0.05);
h_mass_2 -> Draw();

h_mass_1->SetLineStyle(2);
h_mass_1->GetXaxis()->SetLabelSize(0.05);
h_mass_1->GetYaxis()->SetLabelSize(0.05);
h_mass_1 -> Draw("same");

h_mass_2->GetXaxis()->SetLabelSize(0.05);
h_mass_2->GetYaxis()->SetLabelSize(0.05);
h_mass_2 -> Draw();


//pl2 = new TFile("plots_as_old.root","read");
//c1->SetLogy(0);
// h_mass_1->GetXaxis()->SetLabelSize(0.05);
// h_mass_1->GetYaxis()->SetLabelSize(0.05);
// h_mass_1->SetLineStyle(2);
// h_mass_1 -> Draw("same");

//c1->Print("mass_comp_org_crct.eps");

}
