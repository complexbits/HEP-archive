////////////////////////////////////////////////
// Generated Mixing
///////////////////////////////////////////////

void mixmasta_mc()
{
  cout << "Number of events  " << nEvts << endl;

  for (Int_t i=0; i<nEvts; i++){

    // Generate decay time distribution
    // (Insert time smearing to account for reality (mTime))
    Double_t rTime  = gRandom->Exp(tau);
    if (tSigma == 0.){
      Double_t tSmear = 0.;
    }
    else{
      Double_t tSmear = gRandom->Gaus(0., tSigma);
    }
    Double_t mTime = rTime + tSmear;

    // Check for mistagging, and retag if it occurs
    Int_t tagInit=1;          // Mistagging factor: 1=correct, -1=mistagged
    if (misTag != 0.){
      Double_t tagTest = gRandom->Rndm();
      if (tagTest < misTag){
	tagInit = -1;
	
      }
    }
    
    // Compare random stats to "1+cos(dm*t)" to determine mixing
    // (mixed: tag = 1, unmixed: tag = -1; then multiplied by mistagging factor)
    Double_t mixTest = 2.*gRandom->Rndm();
    Double_t isMixed = 1. + TMath::Cos(dm*rTime);

    if(i==50){
      cout<<"for event #50: rTime = "<<rTime<<", isMixed = "<<isMixed<<endl;
    }

    if (mixTest > isMixed){
      tag[i] = tagInit; //mixed
    }else{
      tag[i] = -1*tagInit; //unmixed
    }

    lifetime[i]=mTime;

  }

}
