/*
 * File:      example_xsec.cpp
 * Package:   lm_access
 * Purpose:   simple example of calculation of luminosity and cross section 
 *            for JT_HI_4CJT5 trigger in few root-tuple files
 *            for an explanation see ../doc/example_xsec.html
 * Created:   05-May-2002 Alexander Kupco
 */

#include "lm_access/LumFileMap.hpp"

#include <iostream>
#include <stdlib.h>

#include <TROOT.h>
#include <TBranch.h>
#include <TFile.h>
#include <TLeaf.h>
#include <TTree.h>

using namespace std;

void triggername(Int_t* L3names, int l3bit, char* l3name);

TROOT root("example_xsec", "example_xsec");

int main(int argc, char* argv[]) {

  char* trigger = "JT_HI_4CJT5";  /* specify your trigger */
  char* triggers[] = {trigger};
  LmAccessInterface::InterfaceType="stage3";
  LumFileMap f_map(1, triggers, lm_access::Reconstructed);

  // only need to set lbn dir offsite - just here as an example

  f_map.set_lbn_dir("/prj_root/500/com/offline/stage3");

  int N_trigger = 0;        /* number of events that passed the trigger */
  
  /* loop over the root tuple files*/

  for(int i_file = 1; i_file < argc;  i_file++) {
    char* fileID = argv[i_file];
    f_map.add(fileID, LumFile(lm_access::roottuple, "p10.14.01", "p10.14.01"));

    cout << "Opening file " << fileID << endl << flush;
    TFile f(fileID, "READ");
    TTree& data = *((TTree*) f.Get("Global"));
    data.SetBranchStatus("*", 0);
    data.SetBranchStatus("EVENT", 1);

    /* Event branch */
    TBranch *Event = data.GetBranch("EVENT");
    TLeaf* L_L3bits = Event->GetLeaf("L3bits");
    int* L3bits = new int[L_L3bits->GetNdata()];
    L_L3bits->SetAddress(L3bits);
    TLeaf* L_L3names = Event->GetLeaf("L3names");
    int* L3names = new int[L_L3names->GetNdata()];
    L_L3names->SetAddress(L3names);
    int LumBlk;
    TLeaf* L_lumblk = Event->GetLeaf("lumblk");
    L_lumblk->SetAddress(&LumBlk);

    /* find out number of events in file */
    Stat_t nEnt = data.GetEntries();
    cout << "Number of entries: " << nEnt << endl << flush;

    /* loop over the events */
	
    for(int i = 0; i < nEnt; i++) {
      data.GetEntry(i);

      f_map.downloadLBN(fileID, LumBlk);
      if (f_map.isGoodLBN(fileID, LumBlk, trigger)) {

        /*  
	 *  checking whether the event passed the trigger
         *  this part is based on code described in D0 news 10998
         *  http://www-d0.fnal.gov/cgi-bin/d0news?read__GENERAL__10998
	 *  There is no warranty that the way how to access the trigger 
	 *  information will not change.
	 */

	char name[32];
	
	for (Int_t l3bit=0; l3bit<128; l3bit++) {
	  if (L3bits[l3bit] == 1) {
	    triggername(L3names, l3bit, name);
	    if (strcmp(trigger, name) == 0) N_trigger++;
	  }
	}
	
      }
    } /* end of loop over the events */

    delete [] L3bits;
    delete [] L3names;
    f.Close();
  }

  /* get luminosity */
  double luminosity = f_map.luminosity(trigger);

  /* calculate cross section */
  cout << "Number of events that passed trigger " << trigger 
       << " : " << N_trigger << endl
       << "reconstructed luminosity is : " << luminosity << " ub^-1" 
       << endl
       << "cross section is : "
       << ((luminosity) ? (N_trigger / luminosity) : 0) << " ub" << endl;

  return 0;
}

void triggername(Int_t* L3names, int l3bit, char* l3name)
/*
 *  this part is based on code described in D0 news 10998
 *  http://www-d0.fnal.gov/cgi-bin/d0news?read__GENERAL__10998
 *  There is no warranty that the way how to access the trigger 
 *  information will not change.
 */
{
        
  bool endofname = false;
  l3name[0] = '\0';
  for (Int_t ichar=0; ichar<32 && !endofname; ichar++) {
    int arrayidx = l3bit*32+ichar;
    char thischar=(char) L3names[arrayidx];
    if (thischar != '\0') l3name[ichar]=thischar;
    else {
      l3name[ichar] = thischar;
      endofname = true;
    }
  }
  
}
