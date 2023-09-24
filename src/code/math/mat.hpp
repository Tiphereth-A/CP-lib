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
  std::valarray<T> data() const { return d; }
  std::valarray<T> &data() { return d; }
  T &operator()(size_t r, size_t c) { return data()[r * col_size() + c]; }
  T operator()(size_t r, size_t c) const { return data()[r * col_size() + c]; }

  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    for (auto &i : mat.data()) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const matrix &mat) {
    for (size_t i = 0; i < mat.row_size() - 1; ++i)
      for (size_t j = 0; j < mat.col_size(); ++j) os << mat(i, j) << " \n"[j == mat.col_size() - 1];
    os << mat(mat.row_size() - 1, 0);
    for (size_t j = 1; j < mat.col_size(); ++j) os << ' ' << mat(mat.row_size() - 1, j);
    return os;
  }

  std::slice_array<T> row(size_t r) { return data()[std::slice(r * col_size(), col_size(), 1)]; }
  std::valarray<T> crow(size_t r) const { return data()[std::slice(r * col_size(), col_size(), 1)]; }

  std::slice_array<T> col(size_t c) { return data()[std::slice(c, row_size(), col_size())]; }
  std::valarray<T> ccol(size_t c) const { return data()[std::slice(c, row_size(), col_size())]; }

  std::slice_array<T> diag(ptrdiff_t d) {
    if (d >= 0) {
      assert((size_t)d < col_size());
      return data()[std::slice((size_t)d, std::min(row_size(), col_size() - (size_t)d), col_size() + 1)];
    } else {
      assert((size_t)(-d) < row_size());
      return data()[std::slice((size_t)(-d) * row_size(), std::min(col_size(), row_size() - (size_t)(-d)), col_size() + 1)];
    }
  }
  std::valarray<T> cdiag(ptrdiff_t d) const {
    if (d >= 0) {
      assert((size_t)d < col_size());
      return data()[std::slice((size_t)d, std::min(row_size(), col_size() - (size_t)d), col_size() + 1)];
    } else {
      assert((size_t)(-d) < row_size());
      return data()[std::slice((size_t)(-d) * row_size(), std::min(col_size(), row_size() - (size_t)(-d)), col_size() + 1)];
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

  friend matrix operator+(matrix lhs, const T &val) { return lhs += val; }
  matrix &operator+=(const T &val) {
    d += val;
    return *this;
  }

  friend matrix operator+(matrix lhs, const matrix &rhs) { return lhs += rhs; }
  matrix &operator+=(const matrix &rhs) {
    assert(row_size() == rhs.row_size() && col_size() == rhs.col_size());
    d += rhs.data();
    return *this;
  }

  friend matrix operator-(matrix lhs, const T &val) { return lhs -= val; }
  matrix &operator-=(const T &val) {
    d -= val;
    return *this;
  }

  friend matrix operator-(matrix lhs, const matrix &rhs) { return lhs -= rhs; }
  matrix &operator-=(const matrix &rhs) {
    assert(row_size() == rhs.row_size() && col_size() == rhs.col_size());
    d -= rhs.data();
    return *this;
  }

  friend matrix operator*(matrix lhs, const T &val) { return lhs *= val; }
  matrix &operator*=(const T &val) {
    d *= val;
    return *this;
  }

  friend matrix operator*(const matrix &lhs, const matrix &rhs) {
    assert(lhs.col_size() == rhs.row_size());
    matrix ret(lhs.row_size(), rhs.col_size());
    for (size_t i = 0; i < ret.row_size(); ++i) {
      auto &&r_ = lhs.crow(i);
      for (size_t j = 0; j < ret.col_size(); ++j) ret(i, j) = (r_ * rhs.ccol(j)).sum();
    }
    return ret;
  }
  matrix &operator*=(const matrix &rhs) { return *this = *this * rhs; }
};

}  // namespace tifa_libs::math

#endif