//*************************************************
// Get data to fit
//
// by P. Gutierrez
// 3-12-04
//
//*************************************************

void genDataMs()
{
// Define variables

  Double_t mean = 5.28;
  Double_t sigma = 0.026;
  Double_t frac = 0.8;
  Double_t min = 4.8;
  Double_t max = 5.8;
// Code

  for (int i=0; i<nEvts; i++){
    float f = gRandom->Rndm();
    if (f > frac){
      float g = gRandom->Gaus(mean, sigma);}
    else{
      float g = min + gRandom->Rndm();
    }

    h1->Fill(g);

    mass[i] = g;
  }
}

//**********************************************
// Get lifetime data
//
// P. Gutierrez
// 3-17-04
//**********************************************
void getDataLft()
{
  ifstream in_file1;
  ifstream in_file2;

  //in_file1.open("b0b0_smeared2.out");    // mixed
  //in_file2.open("b0b0bar_smeared2.out"); // unmixed

  in_file1.open("mix.dat");    // mixed
  in_file2.open("umix.dat"); // unmixed

  Double_t lifetime1, lifetime2;
  Int_t flg;

  // mixed

  Int_t i=0;
  while(1){
    in_file1 >> lifetime1 >> flg;
    if (!in_file1.good()) break;

    h2->Fill(lifetime1);
    h3->Fill(lifetime1);

    lifetime[i] = lifetime1;
    tag[i++] = 1;
  }

  // unmixed

  while(1){
    in_file2 >> lifetime2 >> flg;
    if (!in_file2.good()) break;

    h2->Fill(lifetime2);
    h4->Fill(lifetime2);

    lifetime[i]=lifetime2;
    tag[i++] = -1;
  }
  nEvts = i;
  cout << "Number of events  " << i << endl;
  //  h2->Draw();
}

//**********************************************
// Get lifetime data for combined tag study
//
// P. Gutierrez
// 5-7-04
//**********************************************
void getDataCLft()
{
  ifstream in_file;

  //in_file1.open("b0b0_smeared2.out");    // mixed
  //in_file2.open("b0b0bar_smeared2.out"); // unmixed

  in_file.open("/home/gut/work/research/d0/studies/mix/pg_mix_code/mc_10K.dat");

  Double_t lifetime1;

  Int_t cTag1=0, cTag2=0, cTag3=0, cTagw=0;
  Int_t wTag1=0, wTag2=0, wTag3=0, wTagw=0;
  Int_t tag1, tag2, tag3;
  Int_t mixState;

  Int_t whatTag;

  // Read events

  Int_t count = 0;
  Int_t i=0;

  //which tag to use
  Int_t useTag = 1;
  cout << "Using tag = " << useTag << endl;
  while(1){
    in_file >> lifetime1 >> mixState >> tag1 >> tag2 >> tag3;
    if (!in_file.good()) break;
//     cout << lifetime1 << "  " << mixState 
// 	 <<"  " << tag1 << "  " 
// 	 << tag2 << "  " << tag3 << endl;

    h2->Fill(lifetime1);

    // Determine if event is used
    // TAG 1
    if (useTag == 1){
      whatTag = 0;
      if (tag1 != 0) whatTag = tag1;
    }

    //TAG 2
    if (useTag == 2){
      whatTag = 0;
      if (tag1 == 0){
	whatTag = tag2;
      }
    }

    //Tag 3
    if (useTag == 3){
      whatTag = 0;
      if (tag1 == 0 && tag2 == 0){
	whatTag = tag3;
      }
    }

    //Tag 4
    if (useTag == 4){
      whatTag = 0;
      if (tag1 == 0){
	if (tag2 ==  1 && tag3 ==  1) whatTag = tag2;
	if (tag2 == -1 && tag3 == -1) whatTag = tag2;
      }
    }

    //Tag 6
    if (useTag == 6){
      whatTag = 0;
      if (tag1 == 0 && tag3 == 0){
	if (tag2 == 1 || tag2 == -1) whatTag=tag2;
      }
    }

    //Tag 8
    if (useTag == 8){
      whatTag = 0;
      if (tag1 != 0) whatTag = tag1;
      if (tag1 == 0 && tag2 != 0) whatTag = tag2;
      if (tag1 == 0 && tag2 == 0 && tag3 != 0) whatTag = tag3;
    }
//     if (tag1 != 0 || tag3 != 0){
//       whatTag = 0;
//     }
//     else{
//       whatTag = tag2;
//     }
//     whatTag = 0;
//     if (tag1 != 0) whatTag = tag1;
//     else if (tag3 != 0) whatTag = tag3;
//     else if (tag2 != 0) whatTag = tag2;

//     whatTag = 0;
//     if (tag1 == 0){
//       if (tag3 != 0) whatTag = tag3;
//       else if (tag2 != 0) whatTag = tag2;
//     }

    // ms is the measured state including mistag
    Int_t ms = 0;
    if (whatTag != 0){
      ms = mixState*whatTag;
    }
    if (ms != 0){
      lifetime[i] = lifetime1;
      if (ms == 1) h4->Fill(lifetime1);
      if (ms == -1) h3->Fill(lifetime1);
      
      // To determine the mix state with dilution, multiply
      // by tagn 1=SLT, 2=SST, 3=JETQ
      tag[i++] = ms;
    }

    // Count mistags
    if (tag1 ==  1) cTag1++;
    if (tag1 == -1) wTag1++;
    if (tag2 ==  1) cTag2++;
    if (tag2 == -1) wTag2++;
    if (tag3 ==  1) cTag3++;
    if (tag3 == -1) wTag3++;
    if (whatTag ==  1) cTagw++;
    if (whatTag == -1) wTagw++;

    count++;
  }

  nEvts = i;
  cout << count << endl;
  cout << "Number of events  " << i << endl;
  cout << "D1 = " << float(cTag1-wTag1)/(cTag1+wTag1) << " Eff = " << float(cTag1+wTag1)/count << endl;
  cout << "D2 = " << float(cTag2-wTag2)/(cTag2+wTag2) << " Eff = " << float(cTag2+wTag2)/count << endl;
  cout << "D3 = " << float(cTag3-wTag3)/(cTag3+wTag3) << " Eff = " << float(cTag3+wTag3)/count << endl;
  cout << "DW = " << float(cTagw-wTagw)/(cTagw+wTagw) << " Eff = " << float(cTagw+wTagw)/count << endl;
  //  h2->Draw();
}

void getDataLft2()
{
  ifstream in_file;

  in_file.open("/home/gut/work/research/d0/studies/mix/pg_mix_code/mc.dat");

  Double_t lifetime1;

  Int_t cTag1=0, cTag2=0, cTag3=0, cTagw=0;
  Int_t wTag1=0, wTag2=0, wTag3=0, wTagw=0;
  Int_t tag1, tag2, tag3;
  Int_t mixState;

  Int_t whatTag;

  // Read events

  Int_t count = 0;
  Int_t i=0;
  while(1){
    in_file >> lifetime1 >> mixState >> tag1 >> tag2 >> tag3;
    if (!in_file.good()) break;
    
    h2->Fill(lifetime1);

    lifetime[i] = lifetime1;
    i++;
  }

  nEvts = i;
}

//**********************************************
// Get lifetime data
//
// P. Gutierrez
// 3-17-04
//**********************************************
void getDataLftDs()
{
  ifstream in_file1;
  ifstream in_file2;

  //in_file1.open("b0b0_smeared2.out");    // mixed
  //in_file2.open("b0b0bar_smeared2.out"); // unmixed

  in_file1.open("/misc/raid/data/d0/bphysics/data/bs_data/unmixed.txt");    // mixed
  in_file2.open("/misc/raid/data/d0/bphysics/data/bs_data/mixed.txt"); // unmixed

  Double_t lifetime1, lifetime2;
  Double_t mass1, mass2;
  Int_t flg;

  // mixed

  Int_t i=0;
  while(1){
    in_file1 >> mass1 >> lifetime1;
    if (!in_file1.good()) break;

    h2->Fill(lifetime1);
    h3->Fill(lifetime1);

    lifetime[i] = lifetime1;
    mass[i]     = mass1;
    tag[i++]    = 1;
  }

  // unmixed

  while(1){
    in_file2 >> mass2 >> lifetime2;
    if (!in_file2.good()) break;

    h2->Fill(lifetime2);
    h4->Fill(lifetime2);

    lifetime[i]=lifetime2;
    mass[i]    = mass2;
    tag[i++]   = -1;
  }
  nEvts = i;
  cout << "Number of events  " << i << endl;
  //  h2->Draw();
}

//*************************************************
// Generate lifetime data
//
// by P. Gutierrez
// 3-12-04
//
//*************************************************

void genDataLft()
{
// Define variables

  Double_t t0    = 1.5;
  Double_t mean  = 0.0;
  Double_t sigma = 0.1;

  Int_t i = 0;
// Code

  while (i<nEvts){
    Double_t f = gRandom->Exp(t0);
    Double_t g = gRandom->Gaus(mean, sigma);
    if (f+g > -10000000.){
      lifetime[i++] = f + g;
      h2->Fill(f+g);
    }
  }
}

//*************************************************
// Generate mixing data
//
// by P. Gutierrez
// 8-27-04
//
//*************************************************

void genMix()
{
  // Initialize variables
  Double_t tau = 1.8667;
  Double_t dm  = 7.;
  Double_t tSigma  = 0.3749;
  //Double_t misTag = 0.3;
  Double_t dilution = 0.16;
  Double_t misTag = 0.5*(1. - dilution);
  Int_t nEvt = 602;

  Int_t msrState;

  ofstream out_umix;
  ofstream out_mix;

  out_umix.open("umix.dat");
  out_mix.open("mix.dat");

  // Initialize histograms
  TH1F *h1 = new TH1F("h1","Decay time",140, -7, 7.);
  TH1F *h2 = new TH1F("h2","Decay time unmixed",140, -7, 7.);
  TH1F *h3 = new TH1F("h3","Decay time mixed",140, -7., 7.);

  for (Int_t i=0; i<nEvt; i++){
    // Generate decay time distribution
    Double_t rTime  = gRandom->Exp(tau);
    
    if (tSigma == 0.){
      Double_t tSmear = 0.;
    }
    else{
      Double_t tSmear = gRandom->Gaus(0., tSigma);
    }

    Double_t mTime  = rTime + tSmear;
    
    // Does it mix unMix = 1 no, unMix = -1 yes
    Double_t mixTest   = 2.*gRandom->Rndm();
    Double_t unMix  = 1. + TMath::Cos(dm*rTime);
    Int_t mixState = 1;
    if (mixTest > unMix){
      mixState = -1;
    }

    if (misTag != 0.){
      Double_t mTag = gRandom->Rndm();
      if (mTag < misTag){
	msrState = -1 * mixState;
      }
      else{
	msrState = mixState;
      }
    }
    else{
      msrState = mixState;
    }

    h1->Fill(mTime);
    if (msrState == 1){
      h2->Fill(mTime);
      out_umix << mTime << "  " << -1 << endl;
      lifetime[i] = mTime;
      tag[i] = -1;
    }
    if (msrState == -1){
      h3->Fill(mTime);
      out_mix << mTime << "  " << 1 << endl;
      lifetime[i] = mTime;
      tag[i] = 1;
    }
  }
  h1->Draw();
  h2->SetLineColor(2);
  h2->Draw("same");
  h3->SetLineColor(3);
  h3->Draw("same");

}
