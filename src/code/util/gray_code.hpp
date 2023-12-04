#ifndef TIFALIBS_UTIL_GRAY_CODE
#define TIFALIBS_UTIL_GRAY_CODE

#include "util.hpp"

namespace tifa_libs::util {

// k-th n-digit Gray code
inline std::bitset<64> gray_code(u32 n, u64 k) {
  std::bitset<64> res;
  k ^= k >> 1;
  while (~--n) res.set(n, k >> n & 1);
  return res;
}

// all n-digit Gray code
inline vec<u32> gray_code(u32 n) {
  vec<u32> ret(1 << n);
  for (u32 i = 0; i < ret.size(); ++i) ret[i] = i ^ (i >> 1);
  return ret;
}

}  // namespace tifa_libs::util

#endif