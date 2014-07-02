#ifndef LM_ACCESS_FILENAME_UTIL_HPP
#define LM_ACCESS_FILENAME_UTIL_HPP

#include <string>

namespace lm_access{
  /// expand environmentals to get a real path
  std::string filename_expand(const std::string& filename);

  /// strip off the filename itself from the path
  std::string filename_only(const std::string& filename);
}

#endif
