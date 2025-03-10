#ifndef TIFALIBS_EDH_GRAY_CODE
#define TIFALIBS_EDH_GRAY_CODE

#include "../util/alias_others.hpp"

namespace tifa_libs {

// k-th n-digit Gray code
CEXP std::bitset<64> gray_code(u32 n, u64 k) NE {
  std::bitset<64> res;
  k ^= k >> 1;
  while (~--n) res.set(n, k >> n & 1);
  return res;
}
// all n-digit Gray code
CEXP vecu gray_code(u32 n) NE {
  vecu ret(1 << n);
  flt_ (u32, i, 0, (u32)ret.size()) ret[i] = i ^ (i >> 1);
  return ret;
}

}  // namespace tifa_libs

#endif