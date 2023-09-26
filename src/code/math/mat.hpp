#ifndef TIFA_LIBS_MATH_MAT
#define TIFA_LIBS_MATH_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

#define FOR1_(i, l, r) for (size_t i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_(i, row_l, row_r)                        \
    FOR1_(j, col_l, col_r)

template <class T>
class matrix {
  vec<vec<T>> d;

public:
  using value_type = T;

  matrix(size_t row, size_t col, T const &v = T{}):
    d(row, vec<T>(col, v)) { assert(row > 0 && col > 0); }

  constexpr size_t row() const { return d.size(); }
  constexpr size_t col() const { return d[0].size(); }
  constexpr vec<vec<T>> data() const { return d; }
  constexpr vec<vec<T>> &data() { return d; }
  constexpr typename vec<T>::reference operator()(size_t r, size_t c) { return d[r][c]; }
  constexpr typename vec<T>::const_reference operator()(size_t r, size_t c) const { return d[r][c]; }

  template <class F>
  void apply(F f) { apply_range(0, row(), 0, col(), f); }
  template <class F>
  void apply_range(size_t row_l, size_t row_r, size_t col_l, size_t col_r, F f) {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    FOR2_(i, row_l, row_r, j, col_l, col_r) f(i, j, (*this)(i, j));
  }

  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    size_t r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_, j, 0, c_) is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix const &mat) {
    size_t r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_ - 1, j, 0, c_) os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_(j, 1, c_) os << ' ' << mat(r_ - 1, j);
    return os;
  }

  matrix submat(size_t row_l, size_t row_r, size_t col_l, size_t col_r) const {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    ret.apply_range(0, ret.row(), 0, ret.col(), [this, row_l, row_r](size_t i, size_t j, T &v) { v = (*this)(i + row_l, j + row_r); });
    return ret;
  }

  constexpr void swap_row(size_t r1, size_t r2) {
    assert(r1 < row() && r2 < row());
    if (r1 == r2) return;
    std::swap(d[r1], d[r2]);
  }
  constexpr void swap_col(size_t c1, size_t c2) {
    assert(c1 < col() && c2 < col());
    if (c1 == c2) return;
    FOR1_(i, 0, row()) std::swap((*this)(i, c1), (*this)(i, c2));
  }

  constexpr matrix operator-() const {
    matrix ret = *this;
    ret.apply_range(0, row(), 0, col(), []([[maybe_unused]] size_t r, [[maybe_unused]] size_t c, T &v) { v = -v; });
    return ret;
  }

  constexpr friend matrix operator+(matrix l, const T &v) { return l += v; }
  constexpr friend matrix operator+(const T &v, matrix l) { return l += v; }
  constexpr matrix &operator+=(const T &v) {
    apply_range(0, row(), 0, col(), [&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val += v; });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, const T &v) { return l -= v; }
  constexpr friend matrix operator-(const T &v, matrix l) { return l -= v; }
  constexpr matrix &operator-=(const T &v) {
    apply_range(0, row(), 0, col(), [&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val -= v; });
    return *this;
  }
  constexpr friend matrix operator*(matrix l, const T &v) { return l *= v; }
  constexpr friend matrix operator*(const T &v, matrix l) { return l *= v; }
  constexpr matrix &operator*=(const T &v) {
    apply_range(0, row(), 0, col(), [&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val *= v; });
    return *this;
  }

  constexpr friend matrix operator+(matrix l, const matrix &r) { return l += r; }
  constexpr matrix &operator+=(const matrix &r) {
    assert(row() == r.row() && col() == r.col());
    apply_range(0, row(), 0, col(), [&r](size_t i, size_t j, T &val) { val += r(i, j); });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, const matrix &r) { return l -= r; }
  constexpr matrix &operator-=(const matrix &r) {
    assert(row() == r.row() && col() == r.col());
    apply_range(0, row(), 0, col(), [&r](size_t i, size_t j, T &val) { val -= r(i, j); });
    return *this;
  }

  constexpr friend matrix operator*(const matrix &l, const matrix &r) {
    size_t i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    matrix ret(i_, k_);
    FOR1_(i, 0, i_)
      FOR1_(j, 0, j_)
        FOR1_(k, 0, k_) ret(i, k) += l(i, j) * r(j, k);
    return ret;
  }
  constexpr matrix &operator*=(const matrix &r) { return *this = *this * r; }
};

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs::math

#endif