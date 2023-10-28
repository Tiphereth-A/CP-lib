#ifndef TIFA_LIBS_DS_FENWICK_2D
#define TIFA_LIBS_DS_FENWICK_2D

#include "../bit/lowbit.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick2d {
  vvec<T> a;

 public:
  //! [1, row) * [1, col)
  explicit constexpr fenwick2d(usz row, usz col) : a(row, vec<T>(col)) { assert(row > 1 && col > 1); }

  constexpr usz row() const { return a.size(); }
  constexpr usz col() const { return a[0].size(); }

  //! [x, row) * [y, col), x > 0, y > 0
  constexpr void add(usz x, usz y, T const &val) {
    if (!x || !y || x >= row() || y >= col()) return;
    for (; x < row(); x += bit::lowbit(x))
      for (usz j = y; j < col(); j += bit::lowbit(j)) a[x][j] += val;
  }
  //! [xl, xr) * [yl, yr), x > 0, y > 0
  constexpr void add(usz xl, usz yl, usz xr, usz yr, T const &val) {
    add(xl, yl, val);
    add(xl, yr, -val);
    add(xr, yl, -val);
    add(xr, yr, val);
  }
  //! [1, x) * [1, y), x > 0, y > 0
  constexpr T sum(usz x, usz y) {
    T ret = 0;
    for (x = std::min(x, row() - 1); x; x -= bit::lowbit(x))
      for (usz j = std::min(y, col() - 1); j; j -= bit::lowbit(j)) ret += a[x][j];
    return ret;
  }
  //! [xl, xr) * [yl, yr), x > 0, y > 0
  constexpr T sum(usz xl, usz yl, usz xr, usz yr) {
    if (xl >= xr || yl >= yr) return 0;
    return sum(xr, yr) - sum(xl, yr) + sum(xl, yl) - sum(xr, yl);
  }
};

}  // namespace tifa_libs::ds

#endif