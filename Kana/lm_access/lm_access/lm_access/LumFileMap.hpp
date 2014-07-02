#ifndef _LM_ACCESS_LUMFILEMAP_HPP
#define _LM_ACCESS_LUMFILEMAP_HPP


#include <lm_access/globaldef.hpp>
#include <lm_access/TriggerMap.hpp>
#include <lm_access/LumFile.hpp>
#include <lm_access/LmRunQuality.hpp>
#include <lm_access/BadLBNList.hpp>

#include <map>
#include <list>
#include <string>
#include <vector>

//  HMS add disableLBN method 11/29/03


class LumFileMap {
private:
  std::map<std::string, LumFile> _lm_map;
  lm_access::LmType _lm_type;
  lm_access::TriggerMap _triggers;
  bool _debug;
  void _check_lbn_dir() const;
  bool _hasrunquality;
  bool _hasbadlbnlist;
  bool _hasparentagepath;
  const lm_access::LmRunQuality* myrunquality;
  const lm_access::BadLBNList* mybadlbnlist;
  std::string myparentagepath;
  std::string myparentagetag;
  bool removeBadRuns();
  bool removeBadLBNs();
  std::vector<int> _runrangelo;
  std::vector<int> _runrangehi;
  std::set<int> _lbncounter;
  
  
public:

  bool check_lbn_dir()const;

  LumFileMap(int ntriggers = 0, const char* trigger_names[] = 0, 
	     const lm_access::LmType& type = lm_access::Reconstructed);

  LumFileMap(const std::list<std::string>& trigger_list,
	     const lm_access::LmType& type = lm_access::Reconstructed);

  LumFileMap(const LumFileMap& rhs);

  virtual ~LumFileMap() {};

  LumFileMap& operator=(const LumFileMap& rhs);

  LumFile& add(const std::string& fileID, const LumFile& f = LumFile());

  // method which does a complete load including parentage

  bool addAndLoad(const std::string& fileID, const lm_access::FileType ft, lm_access::LmRunQuality* prunquality, const std::string& parentage_path, const std::string& parentage_tag);

  // shorter version that works if parentage has been added

  bool addAndLoad(const std::string& fileID, const lm_access::FileType ft);
  int downloadLBN(const std::string& fileID, int lbn);

  int disableLBN(const std::string& fileID, int lbn);

  int isGoodLBN(const std::string& fileID, int lbn, 
		const std::string& trigger) const;

  lm_access::LmType lm_type() const;

  double luminosity(const std::string& trigger, const int tick=0) const;

  long acceptsL1(const std::string& trigger) const;
  long acceptsL2(const std::string& trigger) const;
  long acceptsL3(const std::string& trigger) const;

  void set_lbn_dir(const std::string new_lbn_dir) const;

  inline int getDuplicateCounter(const int lbn){return _lbncounter.count(lbn);}
  inline void setdebug(const bool debug){_debug=debug;}
  std::list<int>  getLBNList(const std::string& fileID)const;
  bool attachRunRange(const int runlo, const int runhi);
  bool attachBadRunList(const lm_access::LmRunQuality* pRunQuality);
  bool attachBadLBNList(const lm_access::BadLBNList* pBadLBNList);
  bool attachParentage(const std::string& parentage_path, const std::string& parentage_tag);
};

#endif /* _LM_ACCESS_LUMFILEMAP_HPP */
