/////////////////////////////////////////////////////////////////////////////
//               Name       : ReadSAMinfo.hpp                              //
//               Created by : Prolay Kumar Mal                             //
//               Purpose    : To read the output of SAM query              //
//                            and craete map for the code,                 //
//                            RecoGen.cpp                                  // 
//               Date       : April 15, 2002                               //
//               Input      : info.txt (generated by Python script         //
//                            after making SQL query to SAM                //
//                            and also uses the ReadSAMinfo.hpp            //
//               Output     : reco_out.txt (in the preferred python        //
//                            dictionary format by Michael) and            //
//                            error_out.txt for errors                     //
//       This code is written based on the suggestions made by             //
//                   Marcos Verzocchi                                      //
//             Many many thanks to Alexander Kupco                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#ifndef _ReadSAMinfo_hpp
#define _ReadSAMinfo_hpp
#include <string>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;
class ReadInfo {
public:
  ReadInfo();
  ReadInfo(const char * filename, const int numfile);
  int ReadLBN(const int LBN) const;
  ~ReadInfo(){};
  void readfile(const char * namefile, const int noffile);
  int numfile;
  map<string, int>_rawnofevnt;
  map<int, string> _nametuple;
  map<int, string> _datastream;
  map<int, string> _version;
  map<int, int> _l1bitmin;
  map<int, int> _l3bitmin;
  map<int, int> _l1bitzero;
  map<int, int> _l3bitzero;
  map<int, int> _runnumb;
  map<string, int> _LBNmaxima;
  map<string, int> _LBNminima;
};

#endif /* _ReadSAMinfo_hpp */
