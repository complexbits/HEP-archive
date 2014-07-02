  
void test_hists()
{

  TH1F *h_test[50]; //Array of new histograms
  TObjArray a1(0);  //Object array to hold everything you want to write to disk later

  TFile *f = new TFile("test_mk.root", "READ");  //File to read old histograms from
  TIter next(f->GetListOfKeys());  //See Root Manual (Section "I/O: TFile and TKey")
  TKey *key;                       //See Root Manual (Section "I/O: TFile and TKey")

  Int_t k=0, i=1;
  char nametmp [25], name [25], title [100];

  while ((key = (TKey*)next())){  //Loops through the available keys in f.

    // do f->GetListOfKeys()->Print() in a root window to determine 
    // key pattern to match ... only needed if f contains more than
    // just the histograms you want.

    if (k/((3*i)-2) == 1.){

      //Get the name of the current key, then get that hist from the 
      // file and copy it to the new histogram:
      sprintf(nametmp, "%s", key->GetName());  
      h_test[i] = (TH1F*)f->Get(nametmp);      

      //Set the name of the new histogram to h(i):
      sprintf(name, "h%d", i);                 
      h_test[i]->SetName(name);

      //Give the new histogram a useful title (edit as necc.)
      sprintf(title, "%s (h%d)", key->GetName(), i);  
      h_test[i]->SetTitle(title);

      //Add the new histograms to an array so they can be written out later
      a1.Add(h_test[i]);


      // test to make sure this is actually copying histograms from f to h_test
      /***
	  if(i==5){
	  TCanvas *c1 = new TCanvas("c1", "c1", 800, 400);
	  c1->Divide(2,1);
	  c1->cd(1);
	  f->Get(nametmp)->Draw();
	  c1->cd(2);
	  h_test[i]->Draw();
	  }
      ***/


      i++;
    }
    k++;
  }
  
  //Make a new file and write out everything in your array
  TFile *f_2 = new TFile("test_hists.root", "recreate"); 
  a1.Write();
  f_2->Close(); 


}
