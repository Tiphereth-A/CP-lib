#ifndef TIFA_LIBS_UTIL_ENUM_SUPSET
#define TIFA_LIBS_UTIL_ENUM_SUPSET

#include "util.hpp"

namespace tifa_libs::util {

// enumerate x : x \in {n} and x \superset b
inline vec<u32> enum_supset(u32 b, u32 n) {
  vec<u32> res;
  for (u32 i = b; i < (1 << n); i = (i + 1) | b) res.push_back(i);
  return res;
}

}  // namespace tifa_libs::util

#endif