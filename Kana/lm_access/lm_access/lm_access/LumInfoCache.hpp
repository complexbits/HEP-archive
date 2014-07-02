#ifndef _LM_ACCESS_LUMINFOCACHE_HPP
#define _LM_ACCESS_LUMINFOCACHE_HPP

/* 
 * File: LumInfoCache.hpp
 * Package: lm_access
 * Purpose: Class for caching luminosity information 
 *
 * Created:  30-Apr-2003 Alexander Kupco
 */

#include "lm_access/lmCache.hpp"
#include "lm_access/LumInfoMap.hpp"

typedef lm_access::lmCache<int, LumInfoMap> LumInfoCache;

#endif /* _LM_ACCESS_LUMINFOCACHE_HPP */
