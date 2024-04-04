#ifndef TIFALIBS_EDH_CANTOR_INV
#define TIFALIBS_EDH_CANTOR_INV

#include "../ds/weighted_segtree.hpp"

namespace tifa_libs {

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
constexpr vecu cantor_inv_seq(vecu const &s) {
  u32 n = (u32)s.size();
  ds::weighted_segtree tr(n + 1);
  for (u32 i = 1; i <= n; ++i) tr.ins(i);
  vecu p(n);
  for (u32 i = 0; i < n; ++i) tr.del(p[i] = (u32)tr.kth_min(s[i] + 1));
  return p;
}

}  // namespace tifa_libs

#endif