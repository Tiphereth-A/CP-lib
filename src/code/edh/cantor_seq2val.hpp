#ifndef TIFALIBS_EDH_CANTOR_SEQ2VAL
#define TIFALIBS_EDH_CANTOR_SEQ2VAL

#include "../comb/gen_fact.hpp"

namespace tifa_libs {

CEXP u64 cantor_seq2val(vecu CR s, vecu64 CR fact, u64 mod = -1_u64) {
  const u32 n = (u32)s.size();
  u64 ret = 1;
  flt_ (u32, i, 0, n) (ret += math::mul_mod_u(s[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}
CEXP u64 cantor_seq2val(vecu CR s, u64 mod = -1_u64) { return cantor_seq2val(s, math::gen_fact((u32)s.size(), mod), mod); }

}  // namespace tifa_libs

#endif