Drawing(){

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

TCanvas* Bmes1 = new TCanvas("Bmes1", "Low Mass Plots", 600, 750, 600, 750);
Bmes1->Divide(2,2);
Bmes1->SetLogy(2);

Bmes1.cd(1);
	m_1_Kpt_0_5.Draw();
Bmes1.cd(1);	
	m_1_Kpt_0_6.Draw("SAME");
Bmes1.cd(1);
	m_1_Kpt_0_7.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_0_8.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_0_9.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_1_0.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_1_1.Draw("SAME");	
Bmes1.cd(1);	
	m_1_Kpt_1_2.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_1_3.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_1_4.Draw("SAME");
Bmes1.cd(1);	
	m_1_Kpt_1_5.Draw("SAME");
	
Bmes1.cd(2);
	m_1_Ksmt0.Draw();
Bmes1.cd(2);
	m_1_Ksmt1.Draw("SAME");		
Bmes1.cd(2);
	m_1_Ksmt2.Draw("SAME");	
Bmes1.cd(2);
	m_1_Ksmt3.Draw("SAME");	
	
Bmes1.cd(3);
	m_1_coll_080.Draw();
Bmes1.cd(3);
	m_1_coll_100.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_125.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_150.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_175.Draw("SAME");

Bmes1.cd(3);
	m_1_coll_200.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_225.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_250.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_275.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_300.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_325.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_350.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_375.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_400.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_425.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_450.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_475.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_500.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_525.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_550.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_575.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_600.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_625.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_650.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_675.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_700.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_725.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_750.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_775.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_800.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_825.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_850.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_875.Draw("SAME");
	
Bmes1.cd(3);
	m_1_coll_900.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_925.Draw("SAME");
Bmes1.cd(3);
	m_1_coll_950.Draw("SAME");
	
Bmes1.cd(4);
	m_1_dlsig_3_0.Draw();
Bmes1.cd(4);								
	m_1_dlsig_3_2.Draw("SAME");
Bmes1.cd(4);								
	m_1_dlsig_3_4.Draw("SAME");	
Bmes1.cd(4);								
	m_1_dlsig_3_6.Draw("SAME");	
Bmes1.cd(4);								
	m_1_dlsig_3_8.Draw("SAME");
Bmes1.cd(4);
	m_1_dlsig_4_0.Draw("SAME");
Bmes1.cd(4);								
	m_1_dlsig_4_2.Draw("SAME");
Bmes1.cd(4);								
	m_1_dlsig_4_4.Draw("SAME");	
Bmes1.cd(4);								
	m_1_dlsig_4_6.Draw("SAME");	
Bmes1.cd(4);								
	m_1_dlsig_4_8.Draw("SAME");
Bmes1.cd(4);
	m_1_dlsig_5_0.Draw("SAME");
Bmes1.cd(4);								
	m_1_dlsig_5_2.Draw("SAME");
Bmes1.cd(4);								
	m_1_dlsig_5_4.Draw("SAME");	
Bmes1.cd(4);								
	m_1_dlsig_5_6.Draw("SAME");	
Bmes1.cd(4);								
	m_1_dlsig_5_8.Draw("SAME");
Bmes1.cd(4);
	m_1_dlsig_5_0.Draw("SAME");
//	}
//Drawing2(){	
	
TCanvas* Bmes2 = new TCanvas("Bmes2", "High Mass Plots", 600, 750, 600, 750);
Bmes2->Divide(2,2);

Bmes2.cd(1);
	m_2_Kpt_0_5.Draw();
Bmes2.cd(1);	
	m_2_Kpt_0_6.Draw("SAME");
Bmes2.cd(1);
	m_2_Kpt_0_7.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_0_8.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_0_9.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_1_0.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_1_1.Draw("SAME");	
Bmes2.cd(1);	
	m_2_Kpt_1_2.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_1_3.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_1_4.Draw("SAME");
Bmes2.cd(1);	
	m_2_Kpt_1_5.Draw("SAME");
	
Bmes2.cd(2);
	m_2_Ksmt0.Draw();
Bmes2.cd(2);
	m_2_Ksmt1.Draw("SAME");		
Bmes2.cd(2);
	m_2_Ksmt2.Draw("SAME");	
Bmes2.cd(2);
	m_2_Ksmt3.Draw("SAME");	
	
Bmes2.cd(3);
	m_2_coll_080.Draw();
Bmes2.cd(3);
	m_2_coll_100.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_125.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_150.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_175.Draw("SAME");

Bmes2.cd(3);
	m_2_coll_200.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_225.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_250.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_275.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_300.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_325.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_350.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_375.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_400.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_425.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_450.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_475.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_500.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_525.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_550.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_575.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_600.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_625.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_650.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_675.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_700.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_725.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_750.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_775.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_800.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_825.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_850.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_875.Draw("SAME");
	
Bmes2.cd(3);
	m_2_coll_900.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_925.Draw("SAME");
Bmes2.cd(3);
	m_2_coll_950.Draw("SAME");
	
Bmes2.cd(4);
	m_2_dlsig_3_0.Draw();
Bmes2.cd(4);								
	m_2_dlsig_3_2.Draw("SAME");
Bmes2.cd(4);								
	m_2_dlsig_3_4.Draw("SAME");	
Bmes2.cd(4);								
	m_2_dlsig_3_6.Draw("SAME");	
Bmes2.cd(4);								
	m_2_dlsig_3_8.Draw("SAME");
Bmes2.cd(4);
	m_2_dlsig_4_0.Draw("SAME");
Bmes2.cd(4);								
	m_2_dlsig_4_2.Draw("SAME");
Bmes2.cd(4);								
	m_2_dlsig_4_4.Draw("SAME");	
Bmes2.cd(4);								
	m_2_dlsig_4_6.Draw("SAME");	
Bmes2.cd(4);								
	m_2_dlsig_4_8.Draw("SAME");
Bmes2.cd(4);
	m_2_dlsig_5_0.Draw("SAME");
Bmes2.cd(4);								
	m_2_dlsig_5_2.Draw("SAME");
Bmes2.cd(4);								
	m_2_dlsig_5_4.Draw("SAME");	
Bmes2.cd(4);								
	m_2_dlsig_5_6.Draw("SAME");	
Bmes2.cd(4);								
	m_2_dlsig_5_8.Draw("SAME");
Bmes2.cd(4);
	m_2_dlsig_5_0.Draw("SAME");
		
	
}			
		
								
