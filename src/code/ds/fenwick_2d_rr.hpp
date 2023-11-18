#ifndef TIFA_LIBS_DS_FENWICK_2D_RR
#define TIFA_LIBS_DS_FENWICK_2D_RR

#include "fenwick_2d.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick2d_rr {
  fenwick2d<T> a, ax, ay, axy;

 public:
  //! [1, row) * [1, col)
  explicit constexpr fenwick2d_rr(u32 row, u32 col) : a(row, col), ax(row, col), ay(row, col), axy(row, col) {}

  constexpr u32 row() const { return a.size(); }
  constexpr u32 col() const { return a[0].size(); }

  //! [x, row) * [y, col), x > 0, y > 0
  constexpr void add(u32 x, u32 y, T const &val) {
    a.add(x, y, val);
    ax.add(x, y, val * (x - 1));
    ay.add(x, y, val * (y - 1));
    axy.add(x, y, val * (x - 1) * (y - 1));
  }
  //! [xl, xr) * [yl, yr), x > 0, y > 0
  constexpr void add(u32 xl, u32 yl, u32 xr, u32 yr, T const &val) {
    add(xl, yl, val);
    add(xl, yr, -val);
    add(xr, yl, -val);
    add(xr, yr, val);
  }
  //! [1, x) * [1, y), x > 0, y > 0
  constexpr T sum(u32 x, u32 y) { return a.sum(x, y) * x * y - ax.sum(x, y) * y - ay.sum(x, y) * x + axy.sum(x, y); }
  //! (xl, xr] * (yl, yr], x > 0, y > 0
  constexpr T sum(u32 xl, u32 yl, u32 xr, u32 yr) {
    if (xl >= xr || yl >= yr) return 0;
    return sum(xr, yr) - sum(xl, yr) + sum(xl, yl) - sum(xr, yl);
  }
};

}  // namespace tifa_libs::ds

#endif