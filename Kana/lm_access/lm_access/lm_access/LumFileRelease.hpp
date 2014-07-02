#ifndef _LM_ACCESS_LUMFILERELEASE_HPP
#define _LM_ACCESS_LUMFILERELEASE_HPP

#include "lm_access/globaldef.hpp"
#include <string>
#include <iostream>

class LumFileRelease{
private:
  lm_access::FileType _ftype;
  std::string _release;
  std::string _parent_release;
public:
  LumFileRelease();
  LumFileRelease(const lm_access::FileType& ftype, const std::string& release,
		 const std::string& parent_release);
  LumFileRelease(const std::string& stringID);
  LumFileRelease(const LumFileRelease& rhs);
  virtual ~LumFileRelease(){};

  LumFileRelease& operator=(const LumFileRelease& rhs);

  lm_access::FileType type() const {return _ftype;};
  std::string release() const {return _release;};
  std::string parent_release() const {return _parent_release;};
  std::string str() const;
  void print(std::ostream & o=std::cout) const {o << "LumFileRelease::FileType   : " << _ftype << std::endl;
                                                o << "LumFileRelease::Release    : " << _release << std::endl;
                                                o << "LumFileRelease::Parent Rel.: " << _parent_release
                                                  <<std::endl;
                                               };
  
  friend bool operator==(const LumFileRelease& a, const LumFileRelease& b);
  friend bool operator<(const LumFileRelease& a, const LumFileRelease& b);
};

bool operator<(const LumFileRelease& a, const LumFileRelease& b);
bool operator==(const LumFileRelease& a, const LumFileRelease& b);

#endif /* _LM_ACCESS_LUMFILERELEASE_HPP */
