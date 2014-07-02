#ifndef _LM_ACCESS_STRIP_UTIL
#define _LM_ACCESS_STRIP_UTIL

#include "lm_access/LumFileMap.hpp"
#include "TTree.h"
#include <string>

int downloadLBN(LumFileMap& f_map, const std::string& fileID, TTree& lbn_tree);

#endif 		/* _LM_ACCESS_STRIP_UTIL */
