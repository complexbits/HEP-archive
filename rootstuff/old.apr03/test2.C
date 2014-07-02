void test2(){

 float cval[2];
 float cratio[2];
 float b;

 b = 6-3;

 for(int i=0, i<=1, i++){
   cval[i]=b+1
     }

 cratio[0]= 4;
 cratio[1]= 11;

 TGraph* g_1_dlsig = new TGraph(2,cval,cratio);

		TCanvas *c_1_dlsig = new TCanvas("c_1_dlsig", "S/B Ratio, m<0.5GeV, dlsig var", 300, 375, 300, 375);
		g_1_dlsig->Draw("AC");
}
