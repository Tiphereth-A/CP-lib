#ifndef TIFA_LIBS_DS_FENWICK_RR
#define TIFA_LIBS_DS_FENWICK_RR

#include "fenwick.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick_rr {
  fenwick<T> a, ai;

 public:
  //! [1, sz)
  explicit constexpr fenwick_rr(u32 sz) : a(sz), ai(sz) {}

  //! [pos, sz), pos > 0
  constexpr void add(u32 pos, T const &x) {
    a.add(pos, x);
    ai.add(pos, x * (pos - 1));
  }
  //! [1, pos)
  constexpr T sum(u32 pos) { return pos * a.sum(pos) - ai.sum(pos); }
};

}  // namespace tifa_libs::ds

#endif