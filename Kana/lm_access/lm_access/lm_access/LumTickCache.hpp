#ifndef _LM_ACCESS_LUMTICKCACHE_HPP
#define _LM_ACCESS_LUMTICKCACHE_HPP

/* 
 * File: LumTickCache.hpp
 * Package: lm_access
 * Purpose: Class for caching luminosity information for individual ticks
 *
 * Created:  30-Apr-2003 Alexander Kupco
 */

#include "lm_access/lmCache.hpp"
#include "lm_access/LumTickMap.hpp"

typedef lm_access::lmCache<int, LumTickMap> LumTickCache;

#endif /* _LM_ACCESS_LUMTICKCACHE_HPP */
