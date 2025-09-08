#ifndef TIFALIBS_CONV_CONV_NAIVE_MOD
#define TIFALIBS_CONV_CONV_NAIVE_MOD

#include "../math/mul_mod.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::math {

CEXP inline u32 CONV_NAIVE_MOD_THRESHOLD = 16;
CEXP vecuu conv_naive_mod(spnuu l, spnuu r, u64 mod, u32 ans_size = 0) NE {
  retif_((l.empty() || r.empty()) [[unlikely]], {});
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vecuu ans(ans_size);
  u32 n = (u32)l.size(), m = (u32)r.size();
  auto &&l_ = n < m ? r : l, &&r_ = n < m ? l : r;
  if (n < m) swap(n, m);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, min(m, ans_size - i)) ans[i + j] += mul_mod_u(l_[i], r_[j], mod);
  for (auto &i : ans) i %= mod;
  return ans;
}

}  // namespace tifa_libs::math

#endif