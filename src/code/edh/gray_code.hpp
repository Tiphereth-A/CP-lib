#ifndef TIFALIBS_EDH_GRAY_CODE
#define TIFALIBS_EDH_GRAY_CODE

#include "../util/util.hpp"

namespace tifa_libs {

// k-th n-digit Gray code
CEXP std::bitset<64> gray_code(u32 n, u64 k) {
  std::bitset<64> res;
  k ^= k >> 1;
  while (~--n) res.set(n, k >> n & 1);
  return res;
}

// all n-digit Gray code
CEXP vecu gray_code(u32 n) {
  vecu ret(1 << n);
  for (u32 i = 0; i < ret.size(); ++i) ret[i] = i ^ (i >> 1);
  return ret;
}

}  // namespace tifa_libs

#endif