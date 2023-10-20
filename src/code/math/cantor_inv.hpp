#ifndef TIFA_LIBS_MATH_CANTOR_INV
#define TIFA_LIBS_MATH_CANTOR_INV

#include "../ds/weighted_segtree.hpp"

namespace tifa_libs::math {

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
inline vec<u32> cantor_inv_seq(vec<u32> const &s) {
  usz n = s.size();
  ds::weighted_segtree tr(n + 1);
  for (usz i = 1; i <= n; ++i) tr.ins(i);
  vec<u32> p(n);
  for (usz i = 0; i < n; ++i) tr.del(p[i] = (u32)tr.kth_min(s[i] + 1));
  return p;
}

}  // namespace tifa_libs::math

#endif