#ifndef TIFALIBS_EDH_CANTOR_INV
#define TIFALIBS_EDH_CANTOR_INV

#include "../ds/weighted_segtree.hpp"

namespace tifa_libs {

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
CEXP vecu cantor_inv_seq(spnu s) {
  const u32 n = (u32)s.size();
  ds::weighted_segtree tr(n + 1);
  flt_ (u32, i, 1, n + 1) tr.ins(i);
  vecu p(n);
  flt_ (u32, i, 0, n) tr.del(p[i] = tr.kth_min(s[i] + 1));
  return p;
}

}  // namespace tifa_libs

#endif