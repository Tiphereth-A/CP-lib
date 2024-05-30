#ifndef TIFALIBS_DS_FENWICK_2D
#define TIFALIBS_DS_FENWICK_2D

#include "../bit/lowbit.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick2d {
  vvec<T> a;

 public:
  //! [1, row) * [1, col)
  explicit CEXP fenwick2d(u32 row, u32 col) : a(row, vec<T>(col)) { assert(row > 1 && col > 1); }

  CEXP u32 row() const { return a.size(); }
  CEXP u32 col() const { return a[0].size(); }

  //! [x, row) * [y, col), x > 0, y > 0
  CEXP void add(u32 x, u32 y, cT_(T) v) {
    if (!x || !y || x >= row() || y >= col()) return;
    for (; x < row(); x += bit::lowbit(x))
      for (u32 j = y; j < col(); j += bit::lowbit(j)) a[x][j] += v;
  }
  //! [xl, xr) * [yl, yr), x > 0, y > 0
  CEXP void add(u32 xl, u32 yl, u32 xr, u32 yr, cT_(T) v) { add(xl, yl, v), add(xl, yr, -v), add(xr, yl, -v), add(xr, yr, v); }
  //! [1, x) * [1, y), x > 0, y > 0
  CEXP T sum(u32 x, u32 y) {
    T ret = 0;
    for (x = min(x, row() - 1); x; x -= bit::lowbit(x))
      for (u32 j = min(y, col() - 1); j; j -= bit::lowbit(j)) ret += a[x][j];
    return ret;
  }
  //! [xl, xr) * [yl, yr), x > 0, y > 0
  CEXP T sum(u32 xl, u32 yl, u32 xr, u32 yr) {
    if (xl >= xr || yl >= yr) return 0;
    return sum(xr, yr) - sum(xl, yr) + sum(xl, yl) - sum(xr, yl);
  }
};

}  // namespace tifa_libs::ds

#endif