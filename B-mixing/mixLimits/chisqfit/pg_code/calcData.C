void calcData()
{
  Double_t lifetime1, mixState;
  Int_t tag1, tag2, tag3;

  Int_t cTag[10];
  Int_t wTag[10];

  Int_t cTagr[10];
  Int_t wTagr[10];
  Int_t count = 0;

  ifstream in_file;
  in_file.open("/home/gut/work/research/d0/studies/mix/pg_mix_code/mc.dat");

  // Zero counters
  for (Int_t i=0; i<10; i++){
    cTag[i] = 0;
    wTag[i] = 0;

    cTagr[i] = 0;
    wTagr[i] = 0;
  }

  while(1){
    in_file >> lifetime1 >> mixState >> tag1 >> tag2 >> tag3;
    if (!in_file.good()) break;
    count++;

    // Start by calculating the dilution and eff of each tagger
    if (tag1 ==  1) cTagr[0]++;
    if (tag1 == -1) wTagr[0]++;

    if (tag2 ==  1) cTagr[1]++;
    if (tag2 == -1) wTagr[1]++;

    if (tag3 ==  1) cTagr[2]++;
    if (tag3 == -1) wTagr[2]++;


    // Tag with 1
    if (tag1 != 0){
      if (tag1 ==  1) cTag[0]++;
      if (tag1 == -1) wTag[0]++;
    }

    // Tag with 2 if not tagged with 1
    if (tag1 == 0){
      if (tag2 ==  1) cTag[1]++;
      if (tag2 == -1) wTag[1]++;
    }

    // Tag with 3 if not tagged with 1 or 2
    if (tag1 == 0 && tag2 == 0){
      if (tag3 ==  1) cTag[2]++;
      if (tag3 == -1) wTag[2]++;      
    }

    // if not tagged with 1
    if (tag1 == 0){
      // if both agree
      if (tag2 ==  1 && tag3 ==  1) cTag[3]++;
      if (tag2 == -1 && tag3 == -1) wTag[3]++;

      // if both disagree use better dilution
      if (tag2 == -1 && tag3 == 1) cTag[4]++;
      if (tag2 == 1 && tag3 == -1) wTag[4]++;

      // if only tagged with 1 tagger
      if (tag2 ==  1 && tag3 ==  0) cTag[5]++;
      if (tag2 == -1 && tag3 ==  0) wTag[5]++;

      if (tag2 ==  0 && tag3 ==  1) cTag[6]++;
      if (tag2 ==  0 && tag3 == -1) wTag[6]++;
    }

    // Tag with all 3 in decreasing order of dilution
    if (tag1 ==  1) cTag[7]++;
    if (tag1 == -1) wTag[7]++;

    if (tag1 ==  0){
      if (tag2 ==  1) cTag[7]++;
      if (tag2 == -1) wTag[7]++;
    }
    if (tag1 == 0 && tag2 == 0){
      if (tag3 ==  1) cTag[7]++;
      if (tag3 == -1) wTag[7]++;
    }

    // Combine tag2 and tag3 if not tagged by tag1
    if (tag1 == 0){
      if (tag2 ==  1 && tag3 ==  1) cTag[8]++;
      if (tag2 == -1 && tag3 == -1) wTag[8]++;
      if (tag2 ==  1 && tag3 ==  0) cTag[8]++;
      if (tag2 == -1 && tag3 ==  0) wTag[8]++;
      if (tag3 ==  1 && tag2 ==  0) cTag[8]++;
      if (tag3 == -1 && tag2 ==  0) wTag[8]++;
    }
  }
  cout << count << endl << endl;
  cout << "Raw numbers" << endl;
  for (Int_t ij=0; ij<3; ij++){
    Int_t nEvts = cTagr[ij] + wTagr[ij];
    Double_t dil = float(cTagr[ij] - wTagr[ij])/nEvts;
    Double_t eff = float(nEvts)/count;
    cout << "Tag = " << ij+1 << "  D = " << dil
	 << "  Eff = " << eff 
	 << "  eD2 = " << eff*dil*dil << endl;
  }
  cout << endl;

  for (Int_t j=0; j<9; j++){
    Int_t nEvts = cTag[j] + wTag[j];
    Double_t dil = float(cTag[j] - wTag[j])/nEvts;
    Double_t eff = float(nEvts)/count;
    cout << "Tag = " << j+1 << "  D = " << dil
	 << "  Eff = " << eff 
	 << "  eD2 = " << eff*dil*dil << endl;
  }
}
