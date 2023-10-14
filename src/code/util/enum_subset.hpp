#ifndef TIFA_LIBS_UTIL_ENUM_SUBSET
#define TIFA_LIBS_UTIL_ENUM_SUBSET

#include "util.hpp"

namespace tifa_libs::util {

// enumerate x : x \subset b
inline vec<u32> enum_subset(u32 b) {
  vec<u32> res;
  for (u32 i = b; ~i; --i) res.push_back(i &= b);
  return res;
}

}  // namespace tifa_libs::util

#endif