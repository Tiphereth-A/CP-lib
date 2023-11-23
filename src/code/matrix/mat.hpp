#ifndef TIFA_LIBS_MATH_MAT
#define TIFA_LIBS_MATH_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

#define FOR1_(i, l, r) for (u32 i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_ (i, row_l, row_r)                       \
    FOR1_ (j, col_l, col_r)

template <class T>
class matrix {
  vvec<T> d;

 public:
  using value_type = T;

  matrix(u32 row, u32 col, T const &v = T{}) : d(row, vec<T>(col, v)) { assert(row > 0 && col > 0); }
  explicit matrix(vvec<T> const &data) : d(data) { assert(data.size() > 0 && data[0].size > 0); }

  constexpr u32 const &row() const { return d.size(); }
  constexpr u32 const &col() const { return d[0].size(); }
  constexpr vvec<T> const &data() const { return d; }
  constexpr vvec<T> &data() { return d; }
  constexpr typename vec<T>::reference operator()(u32 r, u32 c) { return d[r][c]; }
  constexpr typename vec<T>::const_reference operator()(u32 r, u32 c) const { return d[r][c]; }

  template <class F>
  void apply(F f) { apply_range(0, row(), 0, col(), f); }
  template <class F>
  void apply_range(u32 row_l, u32 row_r, u32 col_l, u32 col_r, F f) {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    FOR2_ (i, row_l, row_r, j, col_l, col_r) f(i, j, (*this)(i, j));
  }

  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_, j, 0, c_) is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix const &mat) {
    u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_ - 1, j, 0, c_) os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_ (j, 1, c_) os << ' ' << mat(r_ - 1, j);
    return os;
  }

  matrix submat(u32 row_l, u32 row_r, u32 col_l, u32 col_r) const {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    ret.apply_range(0, ret.row(), 0, ret.col(), [this, row_l, row_r](u32 i, u32 j, T &v) { v = (*this)(i + row_l, j + row_r); });
    return ret;
  }

  constexpr void swap_row(u32 r1, u32 r2) {
    assert(r1 < row() && r2 < row());
    if (r1 == r2) return;
    std::swap(d[r1], d[r2]);
  }
  constexpr void swap_col(u32 c1, u32 c2) {
    assert(c1 < col() && c2 < col());
    if (c1 == c2) return;
    FOR1_ (i, 0, row()) std::swap((*this)(i, c1), (*this)(i, c2));
  }

  constexpr matrix operator-() const {
    matrix ret = *this;
    ret.apply_range(0, row(), 0, col(), [](u32, u32, T &v) { v = -v; });
    return ret;
  }

  constexpr friend matrix operator+(matrix l, T const &v) { return l += v; }
  constexpr friend matrix operator+(T const &v, matrix l) { return l += v; }
  constexpr matrix &operator+=(T const &v) {
    apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val += v; });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, T const &v) { return l -= v; }
  constexpr matrix &operator-=(T const &v) {
    apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val -= v; });
    return *this;
  }
  constexpr friend matrix operator*(matrix l, T const &v) { return l *= v; }
  constexpr friend matrix operator*(T const &v, matrix l) { return l *= v; }
  constexpr matrix &operator*=(T const &v) {
    apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val *= v; });
    return *this;
  }

  constexpr friend matrix operator+(matrix l, matrix const &r) { return l += r; }
  constexpr matrix &operator+=(matrix const &r) {
    assert(row() == r.row() && col() == r.col());
    apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, T &val) { val += r(i, j); });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, matrix const &r) { return l -= r; }
  constexpr matrix &operator-=(matrix const &r) {
    assert(row() == r.row() && col() == r.col());
    apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, T &val) { val -= r(i, j); });
    return *this;
  }

  constexpr friend matrix operator*(matrix const &l, matrix const &r) {
    u32 i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    matrix ret(i_, k_);
    FOR1_ (i, 0, i_)
      FOR1_ (j, 0, j_)
        FOR1_ (k, 0, k_) ret(i, k) += l(i, j) * r(j, k);
    return ret;
  }
  constexpr matrix &operator*=(matrix const &r) { return *this = *this * r; }

  vec<T> lproj(vec<T> const &x) const {
    u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    for (u32 i = 0; i < c_; ++i) ret[i] = std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), T{});
    return ret;
  }
};

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs::math

#endif