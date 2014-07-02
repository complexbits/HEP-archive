#ifndef _LM_ACCESS_LUMFILE_HPP
#define _LM_ACCESS_LUMFILE_HPP

#include <lm_access/globaldef.hpp>
#include <lm_access/TriggerMap.hpp>
#include <lm_access/LumFileRelease.hpp>
#include <lm_access/LumBlkMap.hpp>
#include <list>


/* 
 * File: LumFile.hpp
 * Package: lm_access
 * Purpose: class LumFile holds LumBlkMap that is associated with
 *          the given file
 *
 * Created:  04-May-2001 Alexander Kupco
 * Modified: 14-November-2003 Petr Homola
 * Modified: 29-November-2003 H. Schellman
 */

class LumFile : public LumFileRelease{
public:
  LumFile();
  LumFile(const lm_access::FileType& ftype, const std::string& release,
	  const std::string& parent_release = "");
  LumFile(const LumFile& rhs);
  virtual ~LumFile(){};

  LumFile& operator=(const LumFile& rhs);

  lm_access::LumBlkStatus status(const int& lbn, 
				 const lm_access::TriggerID triggerID, 
				 const lm_access::LmType& type) const;
  int isGoodLBN(const int& lbn, const lm_access::TriggerID triggerID, 
		const lm_access::LmType& type) const;
  double luminosity(const lm_access::TriggerID triggerID,
		    const lm_access::LmType& type, const int ticker) const;
  long acceptsL1(const lm_access::TriggerID triggerID, const lm_access::LmType& type = lm_access::Triggered) const;
  long acceptsL2(const lm_access::TriggerID triggerID, const lm_access::LmType& type = lm_access::Triggered) const;
  long acceptsL3(const lm_access::TriggerID triggerID, const lm_access::LmType& type = lm_access::Recorded) const;

  int downloadLBN(const std::list<int>& lbns, const lm_access::TriggerMap& triggers);
  int downloadLBN(const int lbn, const lm_access::TriggerMap& triggers);
  int disableLBN(const int lbn);
  int downloadLBN(const int lbn_min, const int lbn_max, 
		  const lm_access::TriggerMap& triggers);
  inline void setdebug(const bool debug){_debug = debug;};

  std::list<int> getLBNList()const;

private:
  LumBlkMap _lbn;
  bool _debug;
};

#endif /* _LM_ACCESS_LUMFILE_HPP */


