#ifndef LMFILEPARENTAGE_HPP
#define LMFILEPARENTAGE_HPP
//
// $Id: LmFileParentage.hpp,v 1.2 2003/02/24 00:50:16 schellma Exp $
//
// File: LmFileParentage.hpp
// Purpose: Header for LmFileParentage.
// this contains a map from LBNs to parentage info
// 
// Created: 15-feb-2002
//
// $Revision: 1.2 $
//
//

#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include "lm_access/filename_util.hpp"
#include "lm_access/LBNParentage.hpp"

namespace lm_access{
  using namespace std;

  typedef std::map<int, LBNParentage>::const_iterator LmFileParentage_const_iterator;

  class LmFileParentage{

  public:
    LmFileParentage();
    LmFileParentage(const std::string& filename,const std::string& tag);
    bool load(const std::string& filename,const std::string& tag);
    void print(std::ostream &o) const;
    LBNParentage getLBNParentage(const int lbn);
    inline std::map<int,LBNParentage>::const_iterator begin()const{return _parentage.begin();};
    inline std::map<int,LBNParentage>::const_iterator end()const{return _parentage.end();};

  private:
    std::map<int,LBNParentage> _parentage;
    std::string _filename;

  };
}

#endif





