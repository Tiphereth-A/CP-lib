#ifndef TIFA_LIBS_MATH_CANTOR
#define TIFA_LIBS_MATH_CANTOR

#include "../ds/fenwick.hpp"
#include "fact_mod_gen.hpp"

namespace tifa_libs::math {

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
inline vec<u32> cantor_seq(vec<u32> const &p) {
  size_t n = p.size();
  ds::fenwick<u32> tr(n + 1);
  vec<u32> s(n);
  for (size_t i = n - 1; ~i; --i) {
    s[i] = tr.sum(p[i]);
    tr.add(p[i], 1);
  }
  return s;
}

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
inline u64 cantor_val(vec<u32> const &p, u64 mod = (u64)-1) {
  size_t n = p.size();
  vec<u64> fact = fact_mod_gen(n + 1, mod);
  vec<u32> s = cantor_seq(p);
  u64 ret = 1;
  for (u64 i = 0; i < n; ++i) (ret += mul_mod_u(s[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}

}  // namespace tifa_libs::math

#endif