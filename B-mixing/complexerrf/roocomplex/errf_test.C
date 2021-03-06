#include "complexmath.h"

//------ Initial values:

Double_t t0 = 1.5;
Double_t dm  = .51;
Double_t s = 1;

void errf_test()
{
  Double_t t, aa, bb, cc, tcompare;
  Double_t wzreneg, wzreneg2, wzrat;

  gSystem->Load("$HOME/lib/libRooFitCore.so");
  gSystem->Load("$HOME/lib/libRooFitModels.so");

  for(Int_t j=1; j<11; j++){

    s = j/10.;

    printf("\n  ====================[s=%3.1f]====================\n",s);
      printf("   t   |   wzreneg      |   wzreneg2     | wzrat\n");    
      printf("  -----------------------------------------------\n");
    
    for(Int_t n=-4.; n<31.; n++){
      
      t = n/2.;
      aa = (t/(TMath::Sqrt(2.)*s)) - (s/(TMath::Sqrt(2.)*t0));  
      cc = s*dm/(TMath::Sqrt(2.));
      tcompare = 5.6*TMath::Sqrt(2.)*s - s*s/t0;
      
      if((t <= tcompare) && (t >= -tcompare)){
	
	RooComplex wz = RooMath::ComplexErrFunc(cc,-aa);
	//cout << cc << " " << -aa << endl;
	wzreneg=wz.re(); 
	
	//cout << z.re() << " " << z.im() << endl;
	wzreneg2 = re(cxerf(cc,-aa)); 
	
	wzrat = wzreneg/wzreneg2;

	printf(" %5.1f |%14.6e  |%14.6e  |%6.3f \n",t, wzreneg, wzreneg2,wzrat);
	//printf(" %5.1f |%14.6e  |%14.6e  \n",t, wzreneg, wzreneg2);
	
      }
     
    }
      printf("  -----------------------------------------------\n");
  }

}
