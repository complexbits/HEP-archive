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
  printf("Number of events  %10d\n",nEvts);

  for (Int_t i=0; i<nEvts; i++){

    // Decide whether this should be a signal or background event by
    // generating a random number, then comparing the "percent signal"
    // required by the signal-background ratio
    Double_t dice = gRandom->Rndm();
    Double_t sigpc = sbrat/(sbrat + 1.);

    if (dice <= sigpc){    // signal events -----------------------
       
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
	printf("for event #50: rTime = %8f, isMixed = %8f\n",rTime,isMixed);
      }
      
      if (mixTest > isMixed){
	tag[i] = tagInit; //mixed
      }else{
	tag[i] = -1*tagInit; //unmixed
      }
      
      lifetime[i]=mTime;


    }else{    // background events --------------------------------

      // Generate decay time distribution
      // (Insert time smearing to account for reality (mTime))
      Double_t rTime  = gRandom->Exp(bgtau);
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

      lifetime[i]=mTime;      

    }

  }

}
