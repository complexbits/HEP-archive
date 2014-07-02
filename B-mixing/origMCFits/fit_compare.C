#include "func.cpp"
#include "mcData.cpp"

// ---------- Define global variables: ----------  
Double_t min = -4;
Double_t max = 15;
Int_t nEvts = 1000;
Int_t nBins = 100;
Int_t nRuns=3.;

//vars used in MC:
Double_t tau = 1.5;
Double_t dm  = .51;
Double_t tSigma = 0.1;

Double_t misTag = 0.; // Mistagging rate

// ---------- Define data variables: -------------  
Double_t runNo[1000];
Double_t evtNo[1000];
Double_t mass[1000];
Double_t lifetime[1000];
Int_t tag[1000];

// --------- Define fit parameters ----------  

Double_t t_sig[100];

Double_t lhparams[3];
Double_t lhparerr[3];

Double_t lh_t0_par[100];
Double_t lh_t0_err[100];

Double_t t0_par_avg[10];
Double_t t0_err_avg[10];

Double_t lh_dm_par[100];
Double_t lh_dm_err[100];

Double_t dm_par_avg[10];
Double_t dm_err_avg[10];

Double_t lh_sig_par[100];
Double_t lh_sig_err[100];

Double_t sig_par_avg[10];
Double_t sig_err_avg[10];


//--------UnbinFit start vars ---------

Double_t oscpar0_init = 1.51515;
Double_t oscpar1_init = 0.51;
Double_t oscpar2_init = 0.5;

Double_t oscerr0_step = 0.1;
Double_t oscerr1_step = 0.1;
Double_t oscerr2_step = 0.1;
//------------------------------------


void fit_compare()
{
  TGraphErrors *g_lhfit = new TGraphErrors(100);
  g_lhfit->SetName("g_lhfit");
  g_lhfit->SetTitle("g_lhfit");

  TGraphErrors *g_lhfavg = new TGraphErrors(10);
  g_lhfavg->SetName("g_lhfavg");
  g_lhfavg->SetTitle("g_lhfavg");

  Int_t ik=0;

  Int_t avindx;

  for (Int_t k=3.;k<13;k++){

    avindx=k-3;    

    for(Int_t i=0;i<nRuns;i++){

      TH1D *h_ltime = new TH1D("h_ltime","Lifetime Dist", nBins, min, max);
      TH1D *h_ltmix = new TH1D("h_ltmix","Lifetime Dist, Mixed", nBins, min, max);       
      TH1D *h_ltunmix = new TH1D("h_ltunmix","Lifetime Dist, Unmixed", nBins, min, max);
      
      // ------ vary tSigma -------------
      
      t_sig[ik]=(k+1)/10.;
      //t_sig[ik]=0.9;
      tSigma = t_sig[ik];
      
      // ---------- Generate data using MC (from mcData.cpp): ------------
      // ---------- (makes lifetime data lifetime[i], and tag data tag[i])
      mixmasta_mc();
      
      for (Int_t ja=0; ja<nEvts; ja++){
	h_ltime->Fill(lifetime[ja]);
	if (tag[ja] == 1){
	  h_ltmix->Fill(lifetime[ja]);
	}else if(tag[ja] == -1){
	  h_ltunmix->Fill(lifetime[ja]);
	}else{
	  cout << "Tag value "<<tag[ja]<< " out of range, should be -1 or 1" << endl;
	  break;
	}
      }
      
      //================= Do unbinned likelihood fit, plot dm. vs. tSigma ================
      
      oscpar2_init = t_sig[ik];
      
      TF1 *f_ltunmix = new TF1("f_ltunmix", lftmosc_plt, -4., 15., 4);
      
      unbinFit(); 
      
      for (Int_t jb=0; jb<=2; jb++){
	f_ltunmix->SetParameter(jb,lhparams[jb]);
	cout << "lhparams["<<jb<<"] = "<<lhparams[jb]<<endl;
      }
      
      f_ltunmix->SetParameter(3,-1.);
      
      cout << "done with likelihood fit" <<endl;
      
      //------ Get final fit parameters and errors --------
      lh_t0_par[ik] = lhparams[0];
      lh_dm_par[ik] = lhparams[1]; 
      lh_sig_par[ik] =  lhparams[2];
      
      lh_t0_err[ik] = lhparerr[0]; 
      lh_dm_err[ik] = lhparerr[1];
      lh_sig_err[ik] = lhparerr[2];
      
      //---- Stick the fit parameters into a lovely graph ----
      g_lhfit->SetPoint(ik,lh_sig_par[ik],lh_dm_par[ik]);
      g_lhfit->SetPointError(ik,lh_sig_err[ik],lh_dm_err[ik]);
      
      
      // ================= Output to the screen (or log file)========================
      cout<<endl;
      cout<<"    ----------------------------------------------------------"<<endl;
      cout  <<"    ik t_sig   lh_sig     lh_sig_err   lh_dm       lh_dm_err"<<endl; 
      cout<<"    "<<ik<<"  "<<t_sig[ik]<<"    "<<lh_sig_par[ik]<<"    "<<lh_sig_err[ik]<<"            "<<lh_dm_par[ik]<<"    "<<lh_dm_err[ik]<<endl;
      cout <<"    ----------------------------------------------------------"<<endl;
      cout <<endl;
      
      ik++;
      
      //------ Delete objects that were created within the loop ----
      delete h_ltime;
      delete h_ltmix;
      delete h_ltunmix;
      
      delete f_ltunmix;

      //--- Increment things for average calculations -----


      dm_par_avg[avindx]=dm_par_avg[avindx]+lh_dm_par[ik];     
      dm_err_avg[avindx]=dm_err_avg[avindx]+lh_dm_err[ik];

      sig_par_avg[avindx]=sig_par_avg[avindx]+lh_sig_par[ik];     
      sig_err_avg[avindx]=sig_err_avg[avindx]+lh_sig_err[ik];

    }

    dm_par_avg[avindx]=dm_par_avg[avindx]/nRuns;
    dm_err_avg[avindx]=dm_err_avg[avindx]/nRuns;

    sig_par_avg[avindx]=sig_par_avg[avindx]/nRuns;
    sig_err_avg[avindx]=sig_err_avg[avindx]/nRuns;

    g_lhfavg->SetPoint(avindx,sig_par_avg[avindx],dm_par_avg[avindx]);
    g_lhfavg->SetPointError(avindx,sig_err_avg[avindx],dm_err_avg[avindx]);
    
  }
  
  //gStyle->SetOptFit(1111);
  
TCanvas *vartsig2 = new TCanvas("vartsig2","vartsig2",600,400);
  vartsig2->Divide(1,2);
  
  vartsig2->cd(1);
  gStyle->SetOptFit(1111);
  g_lhfit->SetTitle("dm vs. tSigma, lhfit -4,15");
  g_lhfit->GetXaxis()->SetTitle("lh_sig  (tSigma)");
  g_lhfit->GetXaxis()->CenterTitle();
  g_lhfit->GetYaxis()->SetTitle("lh_dm (dm)");
  g_lhfit->GetYaxis()->CenterTitle();
  g_lhfit->SetMarkerStyle(21);
  g_lhfit->SetMarkerSize(1);
  g_lhfit->Draw("AP"); 
  g_lhfit->Fit("f_lh_avg");

  vartsig2->cd(2);
  gStyle->SetOptFit(1111);
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  vartsig2->SetGrid();
  g_lhfavg->SetTitle("dm vs. tSigma, lhfit -4,15");
  g_lhfavg->GetXaxis()->SetTitle("lh_sig  (tSigma)");
  g_lhfavg->GetXaxis()->CenterTitle();
  g_lhfavg->GetYaxis()->SetTitle("lh_dm (dm)");
  g_lhfavg->GetYaxis()->CenterTitle();
  g_lhfavg->SetMarkerStyle(21);
  g_lhfavg->SetMarkerSize(1);
  g_lhfavg->Draw("AP");  
  g_lhfavg->Fit("f_lh_avg");
  
}     



/************************************************************************************
                            Support Functions
 ************************************************************************************/ 

void unbinFit()
{
  TMinuit *gMinuit = new TMinuit(3);
  gMinuit -> SetFCN(mll_fit);
  
  Double_t arglist[10];

  Double_t p0=0, p1=1, p2=2, p3=3;
  Int_t ierflg=0;
 
  // Set to 0.5 for likelihood, 1 for chisquare

  arglist[0] = 0.5;
  gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

  // Set initial values of parameters

  gMinuit->mnparm(0, "t0", oscpar0_init, oscerr0_step, 0., 0., ierflg);
  gMinuit->mnparm(1, "dm", oscpar1_init, oscerr1_step, 0., 0., ierflg);
  gMinuit->mnparm(2, "sigma", oscpar2_init, oscerr2_step, 0., 0., ierflg);

  // Do minimization
  arglist[0] = 3000.;
  arglist[1] = 0.1;
  gMinuit->mnexcm("CALL FCN", &p1, 1, ierflg);
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);
  gMinuit->mnexcm("CALL FCN", &p3, 1, ierflg);

  // Get parameters 
  for (Int_t q=0;q<=2;q++){
  gMinuit->GetParameter(q,lhparams[q],lhparerr[q]);
  }
  RooComplex ct = RooMath::ComplexErrFunc(2.,1.);
  cout << "ct  " << ct.re() << "  " << ct.im() << endl;

  delete gMinuit;
}




void mll_fit(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  if (iflag == 1) cout << "iflag  " << iflag << endl;
  if (iflag == 3) cout << "iflag  " << iflag << endl;

  Double_t nll = 0;

  for (Int_t i=0; i<nEvts; i++){
    
    Double_t ll = lifetime_osc(tag[i], par[0], par[1], par[2], lifetime[i]);
    nll -= TMath::Log(ll);

  }
  f = nll;

}
