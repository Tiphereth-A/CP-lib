#ifndef TIFALIBS_DS_FENWICK_2D_RR
#define TIFALIBS_DS_FENWICK_2D_RR

#include "fenwick_2d.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick2d_rr {
  fenwick2d<T> a, ax, ay, axy;

 public:
  //! [1, row) * [1, col)
  CEXPE fenwick2d_rr(u32 row, u32 col) : a(row, col), ax(row, col), ay(row, col), axy(row, col) {}

  CEXP u32 row() const { return a.size(); }
  CEXP u32 col() const { return a[0].size(); }
  //! [x, row) * [y, col), x > 0, y > 0
  CEXP void add(u32 x, u32 y, cT_(T) v) { a.add(x, y, v), ax.add(x, y, v * (x - 1)), ay.add(x, y, v * (y - 1)), axy.add(x, y, v * (x - 1) * (y - 1)); }
  //! [xl, xr) * [yl, yr), x > 0, y > 0
  CEXP void add(u32 xl, u32 yl, u32 xr, u32 yr, cT_(T) v) { add(xl, yl, v), add(xl, yr, -v), add(xr, yl, -v), add(xr, yr, v); }
  //! [1, x) * [1, y), x > 0, y > 0
  CEXP T sum(u32 x, u32 y) { return a.sum(x, y) * x * y - ax.sum(x, y) * y - ay.sum(x, y) * x + axy.sum(x, y); }
  //! (xl, xr] * (yl, yr], x > 0, y > 0
  CEXP T sum(u32 xl, u32 yl, u32 xr, u32 yr) {
    if (xl >= xr || yl >= yr) return 0;
    return sum(xr, yr) - sum(xl, yr) + sum(xl, yl) - sum(xr, yl);
  }
};

}  // namespace tifa_libs::ds

#endif