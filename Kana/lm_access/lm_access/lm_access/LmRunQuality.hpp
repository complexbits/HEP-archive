#ifndef LMRUNQUALITY_HPP
#define LMRUNQUALITY_HPP
//
// $Id: LmRunQuality.hpp,v 1.4 2004/01/01 22:30:36 schellma Exp $
//
// File: LmRunQuality.hpp
// Purpose: Header for LmRunQuality.
// this contains a list of good and bad runs
// 
// Created: 16-jan-2002
//
// $Revision: 1.4 $
//
//

#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "lm_access/filename_util.hpp"


namespace lm_access{
  using namespace std;

  class LmRunQuality{

  public:

    LmRunQuality();

    bool loadGoodRuns(std::string goodfilename);
    bool loadBadRuns(std::string badfilename);
    bool isGoodRun(int run)const;
    bool isBadRun(int run)const;
    void addGoodRun(int run);
    void addBadRun(int run);
    void removeGoodRun(int run);
    void removeBadRun(int run);

  private:

    set<int> goodruns;
    set<int> badruns;
    bool _allgood;
    bool _somebad;
  };
}

#endif





