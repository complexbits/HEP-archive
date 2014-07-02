#include <lm_access/LumFileRelease.hpp>
#include <lm_access/string_util.hpp>

LumFileRelease::LumFileRelease() : _ftype(lm_access::unknown), _release(), 
  _parent_release() {};
LumFileRelease::LumFileRelease(const lm_access::FileType& ftype, 
			       const std::string& release,
			       const std::string& parent_release) :
  _ftype(ftype), _release(release), _parent_release(parent_release) {};
LumFileRelease::LumFileRelease(const std::string& stringID) : 
  _ftype(lm_access::unknown), _release(), _parent_release(){
  std::vector<std::string> s = split(stringID);
  if (! s.size()) return;
  if (s[0] == "raw") _ftype = lm_access::raw;
  else if (s[0] == "reco") _ftype = lm_access::reconstructed;
  else if (s[0] == "recoA") _ftype = lm_access::roottuple;
  else if (s[0] == "tmb") _ftype = lm_access::thumbnail;
  else if (s[0] == "thumbnail") _ftype = lm_access::thumbnail; // added because of SAM DataTierName
  else _ftype = lm_access::unknown;
  int last_index = s.size() - 1;
  if (last_index > 0) _release = s[last_index];
  for (int i = 1; i < last_index; i++) _parent_release += s[i] + " ";
  _parent_release = strip(_parent_release);
  return;
}
LumFileRelease::LumFileRelease(const LumFileRelease& rhs) : 
  _ftype(rhs._ftype), _release(rhs._release), 
  _parent_release(rhs._parent_release) {};

LumFileRelease& LumFileRelease::operator=(const LumFileRelease& rhs) {
  if (this != &rhs) {
    _ftype = rhs._ftype;
    _release = rhs._release;
    _parent_release = rhs._parent_release;
  }
  return *this;
}

std::string LumFileRelease::str() const {
  std::string result = "";
  switch (_ftype) {
  case lm_access::raw: result += "raw "; break;
  case lm_access::reconstructed: result += "reco "; break;
  case lm_access::roottuple: result += "recoA "; break;
  case lm_access::thumbnail: result += "tmb "; break;
  case lm_access::unknown:
  default: result += "unknown ";
  };
  result += _parent_release + " " + _release;
  return result;
}
bool operator<(const LumFileRelease& a, const LumFileRelease& b) {
  if (a._ftype < b._ftype) return 1;
  if (a._ftype > b._ftype) return 0;
  if (a._release < b._release) return 1;
  if (a._release > b._release) return 0;
  return (a._parent_release < b._parent_release);
}

bool operator==(const LumFileRelease& a, const LumFileRelease& b) {
  return ((a._ftype == b._ftype) && (a._release == b._release) && 
	  (a._parent_release == b._parent_release));
}
