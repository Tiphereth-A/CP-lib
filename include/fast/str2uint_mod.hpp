#ifndef TIFALIBS_FAST_STR2UINT_MOD
#define TIFALIBS_FAST_STR2UINT_MOD

#include "../nt/barrett.hpp"
#include "../util/alias_others.hpp"
#include "str2uint_si64.hpp"

namespace tifa_libs {

CEXP u64 str2uint_mod(strnv s, u64 mod) NE {
  const u32 n = (u32)s.size();
  retif_((!n) [[unlikely]], 0);
  u64 ans = 0;
  math::barrett<0> brt_1e8(mod, 100000000), brt_10(mod, 10);
  for (u32 i = 0; i + 8 <= n; i += 8) ans = (brt_1e8.reduce(ans) + str2uint_si64(s.data() + i)) % mod;
  for (auto _ = s.data() + (n & u32(-8)); _ < s.data() + n; ++_) ans = (brt_10.reduce(ans) + (*_ & 15)) % mod;
  return ans;
}

}  // namespace tifa_libs

#endif