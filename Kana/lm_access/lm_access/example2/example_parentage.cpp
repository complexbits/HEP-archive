/*
 * File:      example_parentage.cpp
 * Package:   lm_access
 * Purpose:   simple example of calculation of luminosity and cross section 
 *            for EM_MX_SH trigger in derived files
 *            for an explanation see ../doc/example_parentage.html
 *            includes bad run and bad lbn lists
 * Created:   05-May-2002 Alexander Kupco - modified H. Schellman
 */

#include "lm_access/LumFileMap.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <cassert>
#include "lm_access/LmRunQuality.hpp"
#include "lm_access/LmFileParentage.hpp"
#include "lm_access/BadLBNList.hpp"

using namespace std;
using namespace lm_access;




int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 4){
    cout << " Usage: example_parentage filelist parentpath [trigger]" << endl;
    cout << " trigger defaults to EM_HI_SH" << endl;
    cout << " good runs lists should be in ./goodRunsList ./badRunsList" << endl;
    cout << " bad lbn list should be in ./badlbnlist " << endl;
    return 1;
  }
  std::string filelist(argv[1]);
  std::string parentageLocation(argv[2]);
  std::string trigger;
  if(argc == 3) trigger = "E1_SH_20";
  if(argc == 4) trigger = argv[3];

  // do some setup

  int sumlbn = 0;
  int badlbn = 0;
  int badLumlbn = 0;
  int reallybadlbn = 0;
  int reallyreallybadlbn = 0;

  int run_min = 0;
  int run_max = 0;

  bool debug = false;

  // define output files for good and bad lbns

  std::ofstream  goodrecorded("goodRecordedLBNs");
  std::ofstream  goodreconstructed("goodReconstructedLBNs");
  std::ofstream  bad("bad");

  // choose the trigger

 
  std::list<std::string> triggers;

  triggers.push_back(trigger);

  /// make map files to cache lum information for each file - so don't have to reread the lum db for every event.

  // there are 3 maps, one for recorded, one for reconstructed and one for reconstructed with bad lbns from an external list removed.  The 3rd can be made as a copy of the second as it has the same attributes so only make 2 for now.

  LumFileMap delivered_map(triggers, lm_access::Delivered);
  LumFileMap recorded_map(triggers, lm_access::Recorded);
  LumFileMap reconstructedWithBadLBNList_map(triggers, lm_access::Reconstructed);

  // set the debug flags for one of the maps

  reconstructedWithBadLBNList_map.setdebug(debug);

  // set the stage3 location - only needed at remote locations see LumFileMap.html for more info 

  reconstructedWithBadLBNList_map.set_lbn_dir(string("/home/begel/stage3"));
  recorded_map.set_lbn_dir(string("/home/begel/stage3"));

  //get the run quality information

  lm_access::LmRunQuality* norunquality = new lm_access::LmRunQuality();

  lm_access::LmRunQuality* prunquality = new lm_access::LmRunQuality();
 
  // load run quality into one

  prunquality->loadGoodRuns("./goodRunsList");
  prunquality->loadBadRuns("./badRunsList");


  // get a bad lbn list

  lm_access::BadLBNList* pbadlbnlist = new lm_access::BadLBNList();

  pbadlbnlist->loadBadLBNs("./badlbnlist");


  // attach parentage and quality information to the file map

  delivered_map.attachParentage(parentageLocation);
  recorded_map.attachParentage(parentageLocation,"parentage");

  // second argument defaults to "parentage"
  reconstructedWithBadLBNList_map.attachParentage(parentageLocation);
  
 
  // now split off the without badlbn list map
  LumFileMap reconstructedWithoutBadLBNList_map = reconstructedWithBadLBNList_map;

  // bad lbns
  
  reconstructedWithBadLBNList_map.attachBadRunList(prunquality);
 
  reconstructedWithBadLBNList_map.attachBadLBNList(pbadlbnlist);

  // read the input file list

  std::ifstream infile(filelist.c_str());
  std::string fileID;

  // loop over the files

  while(infile >> fileID){
    

    // add the files to the maps

    reconstructedWithBadLBNList_map.addAndLoad(fileID,lm_access::thumbnail);

    reconstructedWithoutBadLBNList_map.addAndLoad(fileID,lm_access::thumbnail);

    recorded_map.addAndLoad(fileID,lm_access::thumbnail);

    delivered_map.addAndLoad(fileID,lm_access::thumbnail);

    // look at each lbn as a check - this would be done in event loop in your code

    // since we're not using events, we get the list from the recorded map

    std::list<int> lbnlist = recorded_map.getLBNList(fileID);     
    std::list<int>::const_iterator it;
    for(it = lbnlist.begin(); it != lbnlist.end(); it++){
      int lbn = (*it);



      if( debug)std::cout << "check lbn " << fileID << "," << lbn << "," << reconstructedWithBadLBNList_map.isGoodLBN(fileID,lbn,trigger) << std::endl;

	
      // count up events and make good lbn lists 

      if(! reconstructedWithBadLBNList_map.isGoodLBN(fileID,lbn,trigger)){
	badlbn++;
      }
      else{
	goodreconstructed << lbn << endl;
      }

      // just to see effect of bad lbn list, count lbns without that cut

      if(! reconstructedWithoutBadLBNList_map.isGoodLBN(fileID,lbn,trigger)){
	badLumlbn++;
      }

      // to see difference between recorded and reconstructed count recorded

      if(! recorded_map.isGoodLBN(fileID,lbn,trigger)){
	bad << lbn << endl;
	reallybadlbn++;
      
      }
      else{
	goodrecorded << lbn << endl;
      } // isgood

      if(! delivered_map.isGoodLBN(fileID,lbn,trigger)){
	reallyreallybadlbn++;
      }
     
      sumlbn++;
    } //end of lbn loop
  } // end of file loop



  // at the end, print a summary
  
  // make the output file

  ofstream lum(string(filelist+"_"+trigger+".sum").c_str());

  /* get luminosity */

  double luminosity = reconstructedWithoutBadLBNList_map.luminosity(trigger);

  double luminosityWithBadLBN = reconstructedWithBadLBNList_map.luminosity(trigger);
  double recorded_lum  = recorded_map.luminosity(trigger);
  double delivered_lum  = delivered_map.luminosity(trigger);

  double rat1 = 0;
  if(delivered_lum > 0)rat1 = 1.- recorded_lum/delivered_lum;
  double rat2 = 0;
  if(recorded_lum > 0)rat2 = 1.- luminosity/recorded_lum;
  double rat3 = 0;
  if(luminosity > 0) rat3 = 1.-luminosityWithBadLBN/luminosity;
  lum
    << "delivered luminosity is : " << delivered_lum/1.E6 << " pb^-1"  
    << endl
    << "processed " << sumlbn << " lbns, of which " << sumlbn-reallyreallybadlbn << " were good " << endl << endl
    << "recorded luminosity is : " << recorded_lum/1.E6 << " pb^-1" << endl
    << "fraction lost was " << rat1
    << endl
    << "processed " << sumlbn << " lbns, of which " << sumlbn-reallybadlbn << " were good " <<  endl << endl
    << "reconstructed luminosity is : " << luminosity/1.E6 << " pb^-1" << endl
 << "fraction lost was " << rat2 
    << endl 
    << "processed " << sumlbn << " lbns, of which " << sumlbn-badLumlbn << " were good " << endl << endl
    << "reconstructed luminosity with bad lbn list is : " << luminosityWithBadLBN/1.E6 << " pb^-1" << endl <<  " fraction lost was " << rat3
    << endl
    << "processed " << sumlbn << " lbns, of which " << sumlbn-badlbn << " were good " << endl <<endl;


  goodreconstructed.close();
  goodrecorded.close();
  lum.close();

  // cleanup

  delete prunquality;
  delete norunquality;
  delete pbadlbnlist;
  return 0;
}


