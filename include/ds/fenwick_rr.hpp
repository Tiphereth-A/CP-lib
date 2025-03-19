#ifndef TIFALIBS_DS_FENWICK_RR
#define TIFALIBS_DS_FENWICK_RR

#include "fenwick.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick_rr {
  fenwick<T> a, ai;

 public:
  //! [1, sz)
  CEXPE fenwick_rr(u32 sz) NE : a(sz), ai(sz) {}

  //! [pos, sz), pos > 0
  CEXP void add(u32 pos, cT_(T) x) NE { a.add(pos, x), ai.add(pos, x * (pos - 1)); }
  //! [l, r], l > 0
  CEXP void add(u32 l, u32 r, cT_(T) x) NE { add(l, x), add(r + 1, -x); }
  //! [1, pos]
  CEXP T sum(u32 pos) NE { return pos * a.sum(pos) - ai.sum(pos); }
  //! [l, r]
  CEXP T sum(u32 l, u32 r) NE { return sum(r) - sum(l - 1); }
};

}  // namespace tifa_libs::ds

#endif