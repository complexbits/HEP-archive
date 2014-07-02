/*
 * File:      runrange_luminosity.cpp
 * Package:   lm_access
 * Purpose:   simple example of calculation of luminosity and cross section 
 *            provides the luminosity for a data runrange contained in a list 
 *            of files.
 *
 * Created:   05-May-2002 Alexander Kupco - modified H. Schellman
 */

#include "lm_access/LumFileMap.hpp"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <set>
#include <cassert>
#include "lm_access/LmRunQuality.hpp"
#include "lm_access/LmFileParentage.hpp"
#include "lm_access/BadLBNList.hpp"
#include "lm_access/globaldef.hpp"
#include "lm_access/tickutility.hpp"
#include "lm_access_interface/LmAccessInterface.hpp"

#include <time.h>

using namespace std;
using namespace lm_access;


// make the singleton tick information class

float deliveredByTick[37];
float recordedByTick[37];
float recordedBadLBNByTick[37];
float reconstructedByTick[37];

std::string stage3("/prj_root/500/com/offline/stage3");
int main(int argc, char* argv[]) {
  float itime = clock();
  //----------------- Help information ----------------------------

  if (argc < 4 || argc > 4){
    cout << " Usage: runrange_parentage filelist parentpath runrangelist\n"
         << endl;

    cout << "filelist should be a file in the current directory which "
         << "contains a list of the files you want to get lum for" << endl;
    cout << "parentpath should be a directory inside the current directory "
         << "which contains the parentage files"<<endl;
    cout << "runrangelist should be a file in the current directory with"
         << " 'trigger runlo runhi' on each line" <<endl;
    
    cout << " good runs lists should be in ./goodRunsList ./badRunsList"
         << endl;
    cout << " bad lbn list should be in ./badLBNList " << endl;
    cout << endl << "This processes 1 run every few seconds so may take up "
         << "to an hour for a large sample " << endl;
    return 1;
  }

  bool debug = false;
  bool fix_NL = false;
  bool reject_duplicates = true;
  

  // ---------------- Initialization ------------------------------

  LumFileMap* delivered_map = 0;
  LumFileMap* recordedWithoutBadLBNList_map = 0;
  LumFileMap* recordedWithBadLBNList_map = 0;
  LumFileMap* reconstructedWithBadLBNList_map = 0;
  LmAccessInterface::InterfaceType = "stage3";  // setup a stage3 interface type when get_Instance() is called
  LmAccessInterface* interface = LmAccessInterface::get_Instance(debug);
  std::string parentage_tag = interface->getParentageTag();

  // this applies a fix for the nonlinearity observed until August 04

  tickutility * tickmap = tickutility::Instance();

  tickmap->Init();
  
  std::string filelist(argv[1]);
  std::string parentageLocation(argv[2]);
  std::string trigger;
  std::string runrangename;
  string srunlo;
  string srunhi;
  int runlo;
  int runhi;

  if(argc == 4) runrangename = string(argv[3]);

  //get the run quality information
  
  lm_access::LmRunQuality* prunquality = new lm_access::LmRunQuality();
 
  // load run quality into one

  prunquality->loadGoodRuns("./goodRunsList");
  prunquality->loadBadRuns("./badRunsList");

  // get a bad lbn list

  lm_access::BadLBNList* pbadlbnlist = new lm_access::BadLBNList();

  pbadlbnlist->loadBadLBNs("./badLBNList");


  // see if there is an NL correction;
  std::string corr;
  if (fix_NL){ 
    corr = "NLCorr_";
  }
  else{
    corr = "";
  }


  ifstream runrange(runrangename.c_str());

  // now loop over the run ranges and triggers

  while(runrange >> trigger){

    if(!(runrange >> srunlo)) cout << " error reading runrange file" << endl;
    if(!(runrange >> srunhi)) cout << " error reading runrange file" << endl;

    if(debug)
      cout << " look at the following sample " << trigger << " " << srunlo
	   << "-" << srunhi << endl;
    // do some setup
    std::set<int> lbnalreadyseen;
    ofstream badoutputlist(string("reconstructed_"+corr+filelist+"_"+trigger+"_"+srunlo+"-"+srunhi+".badlbns").c_str());
    ofstream badrecordedoutputlist(string("recorded_"+corr+filelist+"_"+trigger+"_"+srunlo+"-"+srunhi+".badlbns").c_str());
    ofstream duplicatelbnlist(string("duplicate_"+corr+filelist+"_"+trigger+"_"+srunlo+"-"+srunhi+".badlbns").c_str());
    std::istringstream lo(srunlo,istringstream::out);
    std::istringstream hi(srunhi,istringstream::out);
    lo >> runlo;
    hi >> runhi;
    
    int sumlbn = 0;
    int duplbn = 0;
    int rejduplbn = 0;
    int badlbn = 0;
    int badrecordedwithbadlbn = 0;
    int badrecordedlbn = 0;
    int baddeliveredlbn = 0;
    
    int run_min = 0;
    int run_max = 0;

  // choose the trigger
 
    std::list<std::string> triggers;

    triggers.push_back(trigger);

  /// make map files to cache lum information for each file - so don't have to reread the lum db for every event.

  // there are 4 maps, one for delivered, one for recorded, two for
  // reconstructed and one for reconstructed with bad lbns from an external
  // list removed.  The 4th  can be made as a copy of the second as it has 
  // the same attributes so only make 3 for now.

    double luminosityWithBadLBN=0;
    double recorded_without_bad_L3=0;
    double recorded_L3=0;
    double reconstructed_L3=0;
    double delivered_lum=0;
    double recorded_without_bad=0;
    double recorded_lum=0;
    for(int i=0;i<37;i++) {
       deliveredByTick[i] = 0;
       recordedByTick[i] = 0;
       recordedBadLBNByTick[i]= 0;
       reconstructedByTick[i] = 0;
    }
  //------------------------ Loop over files ---------------------------


  // loop over the files
    std::ifstream infile(filelist.c_str());
    std::string fileID;

    while(infile >> fileID){

      delivered_map = new LumFileMap(triggers, lm_access::Delivered);
      recordedWithoutBadLBNList_map = new LumFileMap(triggers,lm_access::Recorded);
      recordedWithBadLBNList_map = new LumFileMap(triggers, lm_access::Recorded);
      reconstructedWithBadLBNList_map = new LumFileMap(triggers, lm_access::Reconstructed);

      // set the debug flags for one of the maps

      reconstructedWithBadLBNList_map->setdebug(debug);

  // attach parentage and quality information to the file map

      delivered_map->attachParentage(parentageLocation,parentage_tag);
      recordedWithBadLBNList_map->attachParentage(parentageLocation,parentage_tag);
      recordedWithoutBadLBNList_map->attachParentage(parentageLocation,parentage_tag);
      reconstructedWithBadLBNList_map->attachParentage(parentageLocation,parentage_tag);
 
      delivered_map->attachRunRange(runlo,runhi);
      recordedWithBadLBNList_map->attachRunRange(runlo,runhi);
      recordedWithoutBadLBNList_map->attachRunRange(runlo,runhi);
      reconstructedWithBadLBNList_map->attachRunRange(runlo,runhi);


  // bad lbns and runs

      recordedWithBadLBNList_map->attachBadRunList(prunquality);
      recordedWithBadLBNList_map->attachBadLBNList(pbadlbnlist);
      reconstructedWithBadLBNList_map->attachBadRunList(prunquality);
      reconstructedWithBadLBNList_map->attachBadLBNList(pbadlbnlist);

  // read the input file list

    // add the files to the maps

      bool test1 = delivered_map->addAndLoad(fileID,lm_access::thumbnail);
    //    assert(test1);
      bool test2 = reconstructedWithBadLBNList_map->addAndLoad(fileID,lm_access::thumbnail);
    //assert(test2);
      bool test3 = recordedWithoutBadLBNList_map->addAndLoad(fileID,lm_access::thumbnail);
    // assert(test3);
      bool test4 = recordedWithBadLBNList_map->addAndLoad(fileID,lm_access::thumbnail);
    //assert(test4);

    // look at each lbn as a check - this would be done in event loop in your code

    // since we're not using events, we get the list from the delivered map

      std::list<int> lbnlist = delivered_map->getLBNList(fileID);     
      std::list<int>::const_iterator it;


      for(it = lbnlist.begin(); it != lbnlist.end(); it++){
	int lbn = (*it);
      // check for duplicates within a filemap

      // check for duplicates between filemaps

	int a = lbnalreadyseen.count(lbn);
      
	if (a > 0 ){
	  duplicatelbnlist << lbn << endl;
	  if(debug)cout << "This is a duplicate lbn between two files " << lbn << fileID
			<< endl;
	  if(reject_duplicates){
	    delivered_map->disableLBN(fileID,lbn);
	    recordedWithBadLBNList_map->disableLBN(fileID,lbn);
	    recordedWithoutBadLBNList_map->disableLBN(fileID,lbn);
	    reconstructedWithBadLBNList_map->disableLBN(fileID,lbn);
	    rejduplbn++;
	  }
	  duplbn++;
	  continue;
	}
      
	lbnalreadyseen.insert(lbn);
	if( debug)
	  std::cout << "check lbn " << fileID << "," << lbn << ","
		    << reconstructedWithBadLBNList_map->isGoodLBN(fileID,lbn,trigger)
		    << std::endl;
	
	// count up events and make good lbn lists 

	if(! reconstructedWithBadLBNList_map->isGoodLBN(fileID,lbn,trigger)){
	  badlbn++;
	  badoutputlist << lbn << std::endl;
	}

      // just to see effect of bad lbn list, count lbns without that cut

	if(! recordedWithoutBadLBNList_map->isGoodLBN(fileID,lbn,trigger))
	  badrecordedlbn++;

      // to see difference between bad/good recorded 

	if(! recordedWithBadLBNList_map->isGoodLBN(fileID,lbn,trigger)){
	  badrecordedwithbadlbn++;
	  badrecordedoutputlist << lbn << std::endl;
	}

	if(! delivered_map->isGoodLBN(fileID,lbn,trigger)){
	  baddeliveredlbn++;
	}
     
	sumlbn++;
      } //end of lbn loop
      delivered_lum += delivered_map->luminosity(trigger);
      recorded_without_bad += recordedWithoutBadLBNList_map->luminosity(trigger);
      recorded_lum  += recordedWithBadLBNList_map->luminosity(trigger);
      for ( int i = 0; i <37; i++){
	int tick = tickmap->ticklist(i);

	deliveredByTick[i]+=delivered_map->luminosity(trigger,tick);
	recordedByTick[i]+=recordedWithoutBadLBNList_map->luminosity(trigger,tick);
	recordedBadLBNByTick[i]+=recordedWithBadLBNList_map->luminosity(trigger,tick);
	reconstructedByTick[i]+= reconstructedWithBadLBNList_map->luminosity(trigger,tick);
      }
      luminosityWithBadLBN += reconstructedWithBadLBNList_map->luminosity(trigger);
      recorded_without_bad_L3 += recordedWithoutBadLBNList_map->acceptsL3(trigger);
      recorded_L3  += recordedWithBadLBNList_map->acceptsL3(trigger);
      reconstructed_L3 += reconstructedWithBadLBNList_map->acceptsL3(trigger);
      if (delivered_map)                   delete delivered_map;
      if (recordedWithoutBadLBNList_map)   delete recordedWithoutBadLBNList_map;
      if (recordedWithBadLBNList_map)      delete recordedWithBadLBNList_map;
      if (reconstructedWithBadLBNList_map) delete reconstructedWithBadLBNList_map;
    } // end of file loop

  // ------------------------------end section -----------------------

  // at the end, print a summary
  
  // make the output file

    string outputfilename(filelist+corr+"_"+trigger+"_"+srunlo+"-"+srunhi+".sum");
    if(debug) cout << " write the lum to " << outputfilename << endl;
    ofstream lum(outputfilename.c_str());
  /* get luminosity */

    for ( int i = 0; i <37; i++){
      int tick = tickmap->ticklist(i);
      lum << "By Tick:\t" << tick << "\t" 
	  << deliveredByTick[i]/1.E6 << "\t" 
	  << recordedByTick[i]/1.E6 << "\t"
	  << recordedBadLBNByTick[i]/1.E6 << "\t"
	  << reconstructedByTick[i]/1.E6 << "\t pb-1" << endl;
    }
    double rat1 = 0;
    if(delivered_lum > 0)rat1 = 1.- recorded_without_bad/delivered_lum;
    double rat2 = 0;
    if(recorded_without_bad > 0)rat2 = 1.- recorded_lum/recorded_without_bad;
    double rat3 = 0;
    if(recorded_lum > 0) rat3 = 1.-luminosityWithBadLBN/recorded_lum;
    std::string label = " for runs "+srunlo+"-"+srunhi+" and trigger "+trigger+" " ;
    std::string labeld = " for runs "+srunlo+"-"+srunhi+" " ; 
    cout <<  duplbn << " lbns were identified and " << rejduplbn 
	 << " were rejected as duplicates " << endl;
    lum <<  duplbn << " lbns were identified and " << rejduplbn 
	<< " were rejected as duplicates " << endl;
    
    cout
      << "delivered luminosity "<<labeld << "is : " << delivered_lum/1.E6 << " pb^-1"  
      << endl
      << "processed " << sumlbn << " lbns, of which " << sumlbn-baddeliveredlbn
      << " were good " << endl << endl

      << "recorded luminosity "<<label << "is : " << recorded_without_bad/1.E6 
      << " pb^-1" << " L3 accepts = " << recorded_without_bad_L3 << endl
      << "fraction lost was " << rat1
      << endl
      << "processed " << sumlbn << " lbns, of which " << sumlbn-badrecordedlbn 
      << " were good " <<  endl << endl

      << "recorded luminosity "<<label << "with bad lbn list is : " << recorded_lum/1.E6 
      << " pb^-1" << " L3 accepts = " << recorded_L3 << endl
      << "fraction lost was " << rat2 << endl 
      << "processed " << sumlbn << " lbns, of which " << sumlbn-badrecordedwithbadlbn 
      << " were good " << endl << endl
      << "reconstructed luminosity"<<label << " with bad lbn list is : " 
      << luminosityWithBadLBN/1.E6 << " pb^-1"  <<  " L3 accepts = " << reconstructed_L3 
      << endl <<  " fraction lost was " << rat3 << endl
      << "processed " << sumlbn << " lbns, of which " << sumlbn-badlbn << " were good " 
      << endl <<endl
      << "WARNING - reconstructed information depends on offline checks and is often "
      << "not available for recent data - use recorded instead for studies" << endl;  

    lum
      << "delivered luminosity "<<labeld << "is : " << delivered_lum/1.E6 << " pb^-1"  
      << endl
      << "processed " << sumlbn << " lbns, of which " << sumlbn-baddeliveredlbn 
      << " were good " << endl << endl

      << "recorded luminosity "<<label << "is : " << recorded_without_bad/1.E6 
      << " pb^-1" << " L3 accepts = " << recorded_without_bad_L3 << endl
      << "fraction lost was " << rat1
      << endl
      << "processed " << sumlbn << " lbns, of which " << sumlbn-badrecordedlbn 
      << " were good " <<  endl << endl
      
      << "recorded luminosity "<<label << "with bad lbn list is : " << recorded_lum/1.E6 
      << " pb^-1" << " L3 accepts = " << recorded_L3 << endl
      << "fraction lost was " << rat2 << endl 
      << "processed " << sumlbn << " lbns, of which " << sumlbn-badrecordedwithbadlbn 
      << " were good " << endl << endl

      << "reconstructed luminosity"<<label << " with bad lbn list is : "
      << luminosityWithBadLBN/1.E6 << " pb^-1"  <<  " L3 accepts = " << reconstructed_L3
      << endl <<  " fraction lost was " << rat3 << endl
      << "processed " << sumlbn << " lbns, of which " << sumlbn-badlbn << " were good "
      << endl <<endl 

      << "WARNING - reconstructed information depends on offline checks and is often "
      << "not available for recent data - use recorded instead for studies" << endl;  


    infile.close();
    lum.close();
    duplicatelbnlist.close();
 
    badrecordedoutputlist.close();
    badoutputlist.close();
  }
  //--------------------------- cleanup ---------------------------------

  delete prunquality;
  delete pbadlbnlist;
  cout << "Total time :  " << (clock()-itime)/1000000 << std::endl;
  delete interface;
  return 0;
}

