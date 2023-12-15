#ifndef TIFALIBS_UTIL_ENUM_SUPSET
#define TIFALIBS_UTIL_ENUM_SUPSET

#include "util.hpp"

namespace tifa_libs {

// enumerate x : x \in {n} and x \superset b
constexpr vec<u32> enum_supset(u32 b, u32 n) {
  vec<u32> res;
  for (u32 i = b; i < (1u << n); i = (i + 1) | b) res.push_back(i);
  return res;
}

}  // namespace tifa_libs

#endif