#ifndef TIFA_LIBS_MATH_MAT
#define TIFA_LIBS_MATH_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
class matrix {
  size_t r_sz, c_sz;
  std::valarray<T> d;

public:
  matrix(size_t row, size_t col):
    r_sz(row), c_sz(col), d(T{}, row * col) { assert(row > 0 && col > 0); }
  matrix(size_t row, size_t col, std::valarray<T> const &data):
    r_sz(row), c_sz(col), d(data) { assert(row > 0 && col > 0 && data.size() == row * col); }

  constexpr size_t row_size() const { return r_sz; }
  constexpr size_t col_size() const { return c_sz; }
  constexpr std::valarray<T> data() const { return d; }
  constexpr std::valarray<T> &data() { return d; }
  constexpr T &operator()(size_t r, size_t c) { return d[r * col_size() + c]; }
  constexpr T operator()(size_t r, size_t c) const { return d[r * col_size() + c]; }

  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    for (auto &i : mat.data()) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix const &mat) {
    for (size_t i = 0; i < mat.row_size() - 1; ++i)
      for (size_t j = 0; j < mat.col_size(); ++j) os << mat(i, j) << " \n"[j == mat.col_size() - 1];
    os << mat(mat.row_size() - 1, 0);
    for (size_t j = 1; j < mat.col_size(); ++j) os << ' ' << mat(mat.row_size() - 1, j);
    return os;
  }

  constexpr std::slice_array<T> row(size_t r) { return d[std::slice(r * col_size(), col_size(), 1)]; }
  constexpr std::valarray<T> crow(size_t r) const { return d[std::slice(r * col_size(), col_size(), 1)]; }

  constexpr std::slice_array<T> col(size_t c) { return d[std::slice(c, row_size(), col_size())]; }
  constexpr std::valarray<T> ccol(size_t c) const { return d[std::slice(c, row_size(), col_size())]; }

  constexpr std::slice_array<T> diag(ptrdiff_t d) {
    if (d >= 0) {
      assert((size_t)d < col_size());
      return this->d[std::slice((size_t)d, std::min(row_size(), col_size() - (size_t)d), col_size() + 1)];
    } else {
      assert((size_t)(-d) < row_size());
      return this->d[std::slice((size_t)(-d) * row_size(), std::min(col_size(), row_size() - (size_t)(-d)), col_size() + 1)];
    }
  }
  constexpr std::valarray<T> cdiag(ptrdiff_t d) const {
    if (d >= 0) {
      assert((size_t)d < col_size());
      return this->d[std::slice((size_t)d, std::min(row_size(), col_size() - (size_t)d), col_size() + 1)];
    } else {
      assert((size_t)(-d) < row_size());
      return this->d[std::slice((size_t)(-d) * row_size(), std::min(col_size(), row_size() - (size_t)(-d)), col_size() + 1)];
    }
  }

  matrix submat(size_t row_l, size_t row_r, size_t col_l, size_t col_r) const { return matrix(row_r - row_l, col_r - col_l, d[std::gslice(row_l * col_size() + col_l, {row_r - row_l, col_r - col_l}, {col_size(), 1})]); }

  constexpr void swap_row(size_t r1, size_t r2) {
    if (r1 == r2) return;
    auto __ = crow(r1);
    row(r1) = row(r2);
    row(r2) = __;
  }
  constexpr void swap_col(size_t c1, size_t c2) {
    if (c1 == c2) return;
    auto __ = ccol(c1);
    col(c1) = col(c2);
    col(c2) = __;
  }

  constexpr friend matrix operator+(matrix l, const T &v) { return l += v; }
  constexpr matrix &operator+=(const T &v) {
    d += v;
    return *this;
  }

  constexpr friend matrix operator+(matrix l, const matrix &r) { return l += r; }
  constexpr matrix &operator+=(const matrix &r) {
    assert(row_size() == r.row_size() && col_size() == r.col_size());
    d += r.d;
    return *this;
  }

  constexpr friend matrix operator-(matrix l, const T &v) { return l -= v; }
  constexpr matrix &operator-=(const T &v) {
    d -= v;
    return *this;
  }

  constexpr friend matrix operator-(matrix l, const matrix &r) { return l -= r; }
  constexpr matrix &operator-=(const matrix &r) {
    assert(row_size() == r.row_size() && col_size() == r.col_size());
    d -= r.d;
    return *this;
  }

  constexpr friend matrix operator*(matrix l, const T &v) { return l *= v; }
  constexpr matrix &operator*=(const T &v) {
    d *= v;
    return *this;
  }

  constexpr friend matrix operator*(const matrix &l, const matrix &r) {
    assert(l.col_size() == r.row_size());
    matrix ret(l.row_size(), r.col_size());
    for (size_t i = 0; i < ret.row_size(); ++i) {
      auto &&r_ = l.crow(i);
      for (size_t j = 0; j < ret.col_size(); ++j) ret(i, j) = (r_ * r.ccol(j)).sum();
    }
    return ret;
  }
  constexpr matrix &operator*=(const matrix &r) { return *this = *this * r; }
};

}  // namespace tifa_libs::math

#endif