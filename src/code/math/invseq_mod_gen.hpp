#ifndef TIFA_LIBS_MATH_INVSEQ_MOD_GEN
#define TIFA_LIBS_MATH_INVSEQ_MOD_GEN

#include "../util/util.hpp"

#include "inverse.hpp"
#include "mul_mod_u.hpp"

namespace tifa_libs::math {

// i^{-1} for i in v
inline std::vector<u64> invseq_mod_gen(const std::vector<u64> &v, u64 mod) {
  assert(mod > 1);
  size_t sz = v.size();
  std::vector<u64> ans(sz);
  ans[0] = v[1];
  for (size_t i = 1; i < sz; ++i) ans[i] = mul_mod_u(ans[i - 1], v[i], mod);
  u64 _ = inverse(ans.back(), mod);
  for (size_t i = sz - 1; i; --i) {
    ans[i] = mul_mod_u(_, ans[i - 1], mod);
    _ = mul_mod_u(_, v[i], mod);
  }
  ans[0] = _;
  return ans;
}

}  // namespace tifa_libs::math

#endif