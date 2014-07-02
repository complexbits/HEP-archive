void treetest()
{
  TFile testfile("testfile.root", "recreate");
  TTree testtree("testtree", "Test Tree");
  cout<<"0"<<endl;

  //TClonesArray *histList = new TClonesArray("TH1D",10000);
  //TClonesArray *parlist = new TCLonesArray("TObject",10000);
  TObjArray stuffList(0);
  TObjArray stuffList2(0);

  cout<<"1"<<endl;

  TH1D *h1 = new TH1D("h1", "histogram 1", 100, -1,1);
  TH1D *h2 = new TH1D("h2", "histogram 2", 100, -1,1);

  Double_t par[3];
  
  //histList->AddFirst(&h1);
  //histList->AddAfter(&h1, &h2);

  stuffList.Add(h1);
  stuffList.Add(h2);
  //stuffList2.Add(par);

  cout<<"2"<<endl;

  testtree.Branch("Stuff","TObject", &h1:&h2:&par);
  cout<<"3"<<endl;

 for (Int_t j=0.; j<3; j++){
    par[j]=gRandom->Gaus(0,5000);
  }

  h1->FillRandom("gaus",500);
  h2->FillRandom("gaus",5000);
  cout<<"4"<<endl;

  testtree.Fill();
  cout<<"5"<<endl;

  testtree.Write();
  cout<<"6"<<endl;

  testfile.Write();
}
