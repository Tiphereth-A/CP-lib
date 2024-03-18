#ifndef TIFALIBS_EDH_CANTOR_SEQ2VAL
#define TIFALIBS_EDH_CANTOR_SEQ2VAL

#include "../comb/gen_fact.hpp"

namespace tifa_libs {

constexpr u64 cantor_seq2val(vec<u32> const &s, vec<u64> const &fact, u64 mod = -1_u64) {
  u32 n = (u32)s.size();
  u64 ret = 1;
  for (u32 i = 0; i < n; ++i) (ret += math::mul_mod_u(s[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}
constexpr u64 cantor_seq2val(vec<u32> const &s, u64 mod = -1_u64) { return cantor_seq2val(s, math::gen_fact((u32)s.size(), mod), mod); }

}  // namespace tifa_libs

#endif