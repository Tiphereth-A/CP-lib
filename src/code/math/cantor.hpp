#ifndef TIFA_LIBS_MATH_CANTOR
#define TIFA_LIBS_MATH_CANTOR

#include "../ds/fenwick.hpp"
#include "fact_mod_gen.hpp"

namespace tifa_libs::math {

//! [0, n)
//! a \in [1, n], a_i == a_j \iff i == j
inline u64 cantor(vec<u32> const &a, u64 mod = (u64)-1) {
  size_t n = a.size();
  ds::fenwick<u64> tr(n + 1);
  vec<u64> fact = fact_mod_gen(n + 1, mod);
  u64 ret = 1;
  vec<u64> p(n);
  for (size_t i = n - 1; ~i; --i) {
    p[i] = tr.sum(a[i]);
    tr.add(a[i], 1);
  }
  for (u64 i = 0; i < n; ++i) (ret += mul_mod_u(p[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}

}  // namespace tifa_libs::math

#endif