void graphs()
{
  
  // These are the variable declarations
  Int_t n=20;
  
  Double_t x[20],y[20];

  cout<<"n   x    y"<<endl;

  // This loop fills the variable arrays
  for (Int_t i=0; i<20; i++){
    
    x[i]=i;
    y[i]=x[i]*3;
    cout<<i<<"   "<<x[i]<<"    "<<y[i]<< endl;
 
  }

  // Make the graph object
  TGraph *gr1 = new TGraph(n,x,y);

  // Set the graph properties
  gr1->SetName("graph1");
  gr1->SetTitle("Graph No.1");
  gr1->Draw("AC*");

  // Save the graph in a root file 
  TFile *testfile= new TFile("testfile.root", "recreate");  
  gr1->Write();
  testfile->Write();
}

