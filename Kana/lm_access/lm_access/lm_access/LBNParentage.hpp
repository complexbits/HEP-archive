#ifndef LBN_PARENTAGE_HPP
#define LBN_PARENTAGE_HPP
//
// $Id: LBNParentage.hpp,v 1.1 2003/02/16 22:40:19 schellma Exp $
//
// File: LBNParentage.hpp
// Purpose: Header for LBNParentage
// this contains parentage and stream info about a single lbn
// some info is stored in a vector as a single lbn can contain multiple streams/runs
// Created: 16-feb-2002
//
// $Revision: 1.1 $
//
//
#include <string>
#include <iostream>
#include <vector>
#include "lm_access/LBNParentagePrimitive.hpp"

/// class to contain the parentage info for an lbn

namespace lm_access{

  class LBNParentage{
  public:
    LBNParentage();

    void load(const int lbn, const int run, const std::string& stream, const std::string & version, const std::string parent_version);

    void print(std::ostream& o)const;

    inline int size()const{return _info.size();}
    int  getRun(const int i)const;
    std::string getStream(const int i)const;
    std::string getVersion(const int i)const; 
    std::string getParentVersion(const int i)const;
    std::vector<LBNParentagePrimitive> getLBNParentageVector() const;
      
private:
    int _format;
    int _LBN;
    std::vector<LBNParentagePrimitive> _info;
  };
}
#endif
