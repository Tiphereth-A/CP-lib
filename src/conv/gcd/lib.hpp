#pragma once

#include "../trans/zmt_multiple/lib.hpp"

namespace tifa_libs {

template <class T>
CEXP vec<T> conv_gcd(vec<T> l, vec<T> r) NE {
  assert(l.size() == r.size());
  const auto pf = prime_seq((u32)l.size() - 1);
  zt_multiple(l, pf), zt_multiple(r, pf);
  flt_ (u32, i, 0, (u32)l.size()) l[i] *= r[i];
  mt_multiple(l, pf);
  return l;
}

}  // namespace tifa_libs
