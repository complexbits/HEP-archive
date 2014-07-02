#ifndef BADLBNLIST_HPP
#define BADLBNLIST_HPP
//
// $Id: BadLBNList.hpp,v 1.3 2004/01/01 22:30:36 schellma Exp $
//
// File: BadLBNList.hpp
// Purpose: Header for BadLBNList.
// this contains a list of  bad lbns
// 
// Created: 11-nov-2003
//
// $Revision: 1.3 $
//
//

#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "lm_access/filename_util.hpp"


namespace lm_access{
  using namespace std;

  class BadLBNList{

  public:

    BadLBNList();

    bool loadBadLBNs(std::string badfilename);
    bool isBadLBN(int lbn)const;
    void addBadLBN(int lbn);
    void removeBadLBN(int lbn);

  private:

    set<int> badlbns;
    bool _somebad;
  };
}

#endif





