#ifndef TIFALIBS_EDH_CANTOR
#define TIFALIBS_EDH_CANTOR

#include "../ds/fenwick.hpp"

namespace tifa_libs {

//! [0, n)
//! p \in [1, n], a_i == a_j \iff i == j
CEXP vecu cantor_seq(vecu CR p) {
  const u32 n = (u32)p.size();
  ds::fenwick<u32> tr(n + 1);
  vecu s(n);
  for (u32 i = n - 1; ~i; --i) {
    s[i] = tr.sum(p[i]);
    tr.add(p[i], 1);
  }
  return s;
}

}  // namespace tifa_libs

#endif