////////////////////////////////////////////////
// Generated Mixing
///////////////////////////////////////////////

/* 
   User-set variables which need to be initialized:
   
   Int_t nEvts;       // total events to generate
 
   Double_t tau;      // lifetime of B0
   Double_t tSigma;   // detector time resolution smearing
   Double_t nSigma;   // unmeasured neutrinos smearing
   Double_t dm;       // mass diff btw B0/B0bar
   Double_t misTag;   // mistagging rate

   Double_t bgtau;    // lifetime of background
   Double_t sbrat;    // signal-background ratio

*/
// set sbrat to 10,000,000+ to force pure-signal generation //



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
      
      // Smearing to account for (unmeasured) neutrinos in the decay
      if (nSigma == 0.){
	Double_t nSmear = 0.;
      }
      else{
	Double_t nSmear = gRandom->Gaus(0.,(nSigma*rTime));
      }
      
      Double_t mTime = rTime + tSmear + nSmear;
      
      // Check for mistagging, and retag if it occurs
      Int_t tagInit=1;          // Mistagging factor: 1=correct, -1=mistagged
      if (misTag != 0.){
	Double_t tagTest = gRandom->Rndm();
	if (tagTest < misTag){
	  tagInit = -1;
	  
	}
      }
      
      // Compare random stats to "1+cos(dm*t)" to determine mixing ...
      // mixed: tag = 1, unmixed: tag = -1
      // result is multiplied by mistagging factor
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
