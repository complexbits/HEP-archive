/*
 * File:      file_luminosity.cpp
 * Package:   lm_access
 * Purpose:   simple example of calculation of luminosity 
 *            for a file
 *            for an explanation see ../doc/example_xsec.html
 * Created:   05-May-2002 Alexander Kupco - modified H. Schellman
 */

#include "lm_access/LumFileMap.hpp"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <cassert>
#include "lm_access/LmRunQuality.hpp"
#include "lm_access/LmFileParentage.hpp"

using namespace std;
using namespace lm_access;



int main(int argc, char* argv[]) {

  if (argc < 2 || argc > 3){
    cerr << " must enter filename and optionally trigger " << endl;
    return 1;
  }
  const char*  cfilename = argv[1];

  // do some setup

  int sumlbn = 0;
  int badlbn = 0;
  int reallybadlbn = 0;
  
  bool debug = false;

  // define output files for good and bad lbns

  std::ofstream  goodrecorded("goodRecordedLBNs");
  std::ofstream  goodreconstructed("goodReconstructedLBNs");
  std::ofstream  bad("bad");

  // choose the trigger

  std::string trigger;

  if(argc == 3){

    trigger=std::string(argv[2]);  /* specify your trigger */

  }
  else {
    trigger = std::string("2EM_HI");
  }
  std::list<std::string> triggers;

  triggers.push_back(trigger);

  /// make map files to store lum information

  LumFileMap g_map(triggers, lm_access::Recorded);
  LumFileMap f_map(triggers, lm_access::Reconstructed);

  // set the stage2a location - only needed at remote locations see LumFileMap.html for more info

  f_map.set_lbn_dir(string("/home/begel/stage2a"));

  // make a runquality object even though we don't plan to cut

  lm_access::LmRunQuality* prunquality = new lm_access::LmRunQuality();


  std::string fileID(cfilename);

  // test the file if it exists


    
  // load the information

  f_map.addAndLoad(fileID,lm_access::thumbnail,prunquality,".","parentage");
  g_map.addAndLoad(fileID,lm_access::thumbnail,prunquality,".","parentage");

  // look at it as a check - this would be done in event loop in your code
   
  std::list<int> lbnlist = f_map.getLBNList(fileID);
  std::list<int>::const_iterator it;

  for(it = lbnlist.begin(); it != lbnlist.end(); it++){
    int lbn = (*it);

    if( debug)std::cerr << "check lbn " << fileID << "," << lbn << "," << f_map.isGoodLBN(fileID,lbn,trigger) << std::endl;

	
    // count up events and make good lbn lists

    if(! f_map.isGoodLBN(fileID,lbn,trigger)){
      badlbn++;
    }
    else{
      goodreconstructed << lbn << endl;
    }
    

    if(! g_map.isGoodLBN(fileID,lbn,trigger)){
      bad << lbn << endl;
      reallybadlbn++;
      
    }
    else{
	goodrecorded << lbn << endl;
    } // isgood

      
    sumlbn++;
  } //end of lbn loop



  // at the end, print a summary
  
  // make the output file

  std::string outputfilename(cfilename);
  outputfilename += ".sum";
  ofstream lum(outputfilename.c_str());

  /* get luminosity */
  double luminosity = f_map.luminosity(trigger);
  double glum = g_map.luminosity(trigger);

  /* calculate cross section */
  lum
    << "recorded luminosity is : " << glum << " ub^-1" 
    << endl
    << "processed " << sumlbn << " lbns, of which " << sumlbn-reallybadlbn << " were good " << endl
    << "reconstructed luminosity is : " << luminosity << " ub^-1" 
    << endl
    << "processed " << sumlbn << " lbns, of which " << sumlbn-badlbn << " were good " << endl;
  //       << ((luminosity) ? (N_trigger / luminosity) : 0) << " ub" << endl;
  lum.close();

  // cleanup
  std::cout << glum << " ub^-1 " << fileID << " " << trigger <<  std::endl;
  delete prunquality;
  return 0;
}



