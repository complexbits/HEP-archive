#include "cxerf.cpp"
#include "complexmath.h"

//------ Initial values:

Double_t t0 = 1.5;
Double_t dm  = .51;
Double_t s = 1;
Double_t t, aa, bb, cc, tcompare;

Double_t tsmax=10.;


void errf_test2()
{
  gSystem->Load("libRooFitCore.so");
  gSystem->Load("libRooFitModels.so");

  for(Int_t j=1; j<4; j++){

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
	Double_t wzreneg=wz.re(); 
	
	Complex_t z (cc,-aa);
	//cout << z.re() << " " << z.im() << endl;
	Double_t wzreneg2=(cxerf(z)).re(); 
	
	Double_t wzrat = wzreneg/wzreneg2;

	printf(" %5.1f |%14.6e  |%14.6e  |%6.3f \n",t, wzreneg, wzreneg2,wzrat);

	
      }
     
    }
      printf("  -----------------------------------------------\n");
  }

}
