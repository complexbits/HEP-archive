Drawing_1(){

gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetCanvasBorderMode(0);
gStyle->SetFrameBorderMode(0); 
gStyle->SetHistFillColor(0);
gStyle->SetHistFillStyle(0);
gStyle->SetHistLineStyle(1);  
gStyle->SetHistLineWidth(1);

gStyle->SetOptTitle(1);
gStyle->SetOptStat(0);
//gStyle->SetLogy(0);

TFile* lotsa_histos = new TFile("more_histograms_than_you_can_shake_a_stick_at.root", "read");

TCanvas* Kpt_low = new TCanvas("Kpt_low", "Low Mass, Kpt varied", 300, 375, 300, 375);
Kpt_low.SetLogy(1);
	m_1_Kpt_0_5.Draw();
	m_1_Kpt_0_6.Draw("SAME");
	m_1_Kpt_0_7.Draw("SAME");
	m_1_Kpt_0_8.Draw("SAME");
	m_1_Kpt_0_9.Draw("SAME");
	m_1_Kpt_1_0.Draw("SAME");
	m_1_Kpt_1_1.Draw("SAME");	
	m_1_Kpt_1_2.Draw("SAME");
	m_1_Kpt_1_3.Draw("SAME");
	m_1_Kpt_1_4.Draw("SAME");
	m_1_Kpt_1_5.Draw("SAME");

TCanvas* Ksmt_low = new TCanvas("Ksmt_low", "Low Mass, Ksmt varied", 300, 375, 300, 375);
Ksmt_low.SetLogy(1);	
	m_1_Ksmt0.Draw();
	m_1_Ksmt1.Draw("SAME");		
	m_1_Ksmt2.Draw("SAME");	
	m_1_Ksmt3.Draw("SAME");
	
TCanvas* Coll_low = new TCanvas("Coll_low", "Low Mass, Coll varied", 300, 375, 300, 375);
Coll_low.SetLogy(1);	

	m_1_coll_080.Draw();
	m_1_coll_100.Draw("SAME");
	m_1_coll_125.Draw("SAME");
	m_1_coll_150.Draw("SAME");
	m_1_coll_175.Draw("SAME");

	m_1_coll_200.Draw("SAME");
	m_1_coll_225.Draw("SAME");
	m_1_coll_250.Draw("SAME");
	m_1_coll_275.Draw("SAME");
	
	m_1_coll_300.Draw("SAME");
	m_1_coll_325.Draw("SAME");
	m_1_coll_350.Draw("SAME");
	m_1_coll_375.Draw("SAME");
       
	m_1_coll_400.Draw("SAME");
	m_1_coll_425.Draw("SAME");
	m_1_coll_450.Draw("SAME");
	m_1_coll_475.Draw("SAME");
       
	m_1_coll_500.Draw("SAME");
	m_1_coll_525.Draw("SAME");
	m_1_coll_550.Draw("SAME");
	m_1_coll_575.Draw("SAME");
	
	m_1_coll_600.Draw("SAME");
	m_1_coll_625.Draw("SAME");
	m_1_coll_650.Draw("SAME");
	m_1_coll_675.Draw("SAME");
	
	m_1_coll_700.Draw("SAME");
	m_1_coll_725.Draw("SAME");
	m_1_coll_750.Draw("SAME");
	m_1_coll_775.Draw("SAME");
	
	m_1_coll_800.Draw("SAME");
	m_1_coll_825.Draw("SAME");
	m_1_coll_850.Draw("SAME");
	m_1_coll_875.Draw("SAME");
	
	m_1_coll_900.Draw("SAME");
	m_1_coll_925.Draw("SAME");
	m_1_coll_950.Draw("SAME");

TCanvas* dl_sig_low = new TCanvas("dl_sig_low", "Low Mass, dl_sig varied", 300, 375, 300, 375);	
dl_sig_low.SetLogy(1);
	m_1_dlsig_3_0.Draw();		
	m_1_dlsig_3_2.Draw("SAME");
	m_1_dlsig_3_4.Draw("SAME");	
	m_1_dlsig_3_6.Draw("SAME");	
	m_1_dlsig_3_8.Draw("SAME");
	m_1_dlsig_4_0.Draw("SAME");
	m_1_dlsig_4_2.Draw("SAME");
	m_1_dlsig_4_4.Draw("SAME");	
	m_1_dlsig_4_6.Draw("SAME");	
	m_1_dlsig_4_8.Draw("SAME");
	m_1_dlsig_5_0.Draw("SAME");
	m_1_dlsig_5_2.Draw("SAME");
	m_1_dlsig_5_4.Draw("SAME");	
	m_1_dlsig_5_6.Draw("SAME");	
	m_1_dlsig_5_8.Draw("SAME");
	m_1_dlsig_5_0.Draw("SAME");

// ----- plots for mass > .5Gev --------------

TCanvas* Kpt_high = new TCanvas("Kpt_high", "High Mass, Kpt varied", 300, 375, 300, 375);
Kpt_high.SetLogy(1);
	m_2_Kpt_0_5.Draw();
	m_2_Kpt_0_6.Draw("SAME");
	m_2_Kpt_0_7.Draw("SAME");
	m_2_Kpt_0_8.Draw("SAME");
	m_2_Kpt_0_9.Draw("SAME");
	m_2_Kpt_1_0.Draw("SAME");
	m_2_Kpt_1_1.Draw("SAME");	
	m_2_Kpt_1_2.Draw("SAME");
	m_2_Kpt_1_3.Draw("SAME");
	m_2_Kpt_1_4.Draw("SAME");
	m_2_Kpt_1_5.Draw("SAME");

TCanvas* Ksmt_high = new TCanvas("Ksmt_high", "High Mass, Ksmt varied", 300, 375, 300, 375);
Ksmt_high.SetLogy(1);	
	m_2_Ksmt0.Draw();
	m_2_Ksmt1.Draw("SAME");		
	m_2_Ksmt2.Draw("SAME");	
	m_2_Ksmt3.Draw("SAME");
	
TCanvas* Coll_high = new TCanvas("Coll_high", "High Mass, Coll varied", 300, 375, 300, 375);
Coll_high.SetLogy(1);	

	m_2_coll_080.Draw();
	m_2_coll_100.Draw("SAME");
	m_2_coll_125.Draw("SAME");
	m_2_coll_150.Draw("SAME");
	m_2_coll_175.Draw("SAME");

	m_2_coll_200.Draw("SAME");
	m_2_coll_225.Draw("SAME");
	m_2_coll_250.Draw("SAME");
	m_2_coll_275.Draw("SAME");
	
	m_2_coll_300.Draw("SAME");
	m_2_coll_325.Draw("SAME");
	m_2_coll_350.Draw("SAME");
	m_2_coll_375.Draw("SAME");
       
	m_2_coll_400.Draw("SAME");
	m_2_coll_425.Draw("SAME");
	m_2_coll_450.Draw("SAME");
	m_2_coll_475.Draw("SAME");
       
	m_2_coll_500.Draw("SAME");
	m_2_coll_525.Draw("SAME");
	m_2_coll_550.Draw("SAME");
	m_2_coll_575.Draw("SAME");
	
	m_2_coll_600.Draw("SAME");
	m_2_coll_625.Draw("SAME");
	m_2_coll_650.Draw("SAME");
	m_2_coll_675.Draw("SAME");
	
	m_2_coll_700.Draw("SAME");
	m_2_coll_725.Draw("SAME");
	m_2_coll_750.Draw("SAME");
	m_2_coll_775.Draw("SAME");
	
	m_2_coll_800.Draw("SAME");
	m_2_coll_825.Draw("SAME");
	m_2_coll_850.Draw("SAME");
	m_2_coll_875.Draw("SAME");
	
	m_2_coll_900.Draw("SAME");
	m_2_coll_925.Draw("SAME");
	m_2_coll_950.Draw("SAME");

TCanvas* dl_sig_high = new TCanvas("dl_sig_high", "High Mass, dl_sig varied", 300, 375, 300, 375);	
dl_sig_high.SetLogy(1);
	m_2_dlsig_3_0.Draw();		
	m_2_dlsig_3_2.Draw("SAME");
	m_2_dlsig_3_4.Draw("SAME");	
	m_2_dlsig_3_6.Draw("SAME");	
	m_2_dlsig_3_8.Draw("SAME");
	m_2_dlsig_4_0.Draw("SAME");
	m_2_dlsig_4_2.Draw("SAME");
	m_2_dlsig_4_4.Draw("SAME");	
	m_2_dlsig_4_6.Draw("SAME");	
	m_2_dlsig_4_8.Draw("SAME");
	m_2_dlsig_5_0.Draw("SAME");
	m_2_dlsig_5_2.Draw("SAME");
	m_2_dlsig_5_4.Draw("SAME");	
	m_2_dlsig_5_6.Draw("SAME");	
	m_2_dlsig_5_8.Draw("SAME");
	m_2_dlsig_5_0.Draw("SAME");	
}			
		
								
