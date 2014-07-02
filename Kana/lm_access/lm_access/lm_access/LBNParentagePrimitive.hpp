#ifndef LBNParentagePrimitive_HPP
#define LBNParentagePrimitive_HPP
//
// $Id: LBNParentagePrimitive.hpp,v 1.1 2003/02/16 22:40:19 schellma Exp $
//
// File: LBNParentagePrimitive.hpp
// Purpose: Header for LBNParentagePrimitive
// this contains parentage and stream info about a stream for a single lbn
// 
// Created: 16-feb-2002
//
// $Revision: 1.1 $
//
//

#include <string>
#include <iostream>

namespace lm_access{
  class LBNParentagePrimitive{
  public:

    LBNParentagePrimitive();

    LBNParentagePrimitive(const int lbn, const int run, const std::string stream,const std::string version, const std::string  parent_version);

    void load(const int lbn, const int run, const std::string stream,const std::string version, const std::string  parent_version);

    void print(std::ostream& o) const; 

    inline int getRun()const{return _run;};
    inline std::string getStream()const{return _stream;};
    inline std::string getVersion()const{return _version;};
    inline std::string getParentVersion()const{return _parent_version;} 
  private:
    int _format;
    int _lbn;
    int _run;
    std::string _stream;
    std::string _version;
    std::string _parent_version;
  };
};
#endif
