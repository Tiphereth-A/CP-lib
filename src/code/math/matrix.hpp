#ifndef TIFA_LIBS_MATH_MATRIX
#define TIFA_LIBS_MATH_MATRIX

#include "../util/util.hpp"

#include "abs_constexpr.hpp"

namespace tifa_libs::math {

template <class T, class Isz = std::function<bool(T)>>
class matrix {
  using self = matrix<T, Isz>;

protected:
  constexpr bool gauss_swapr__(size_t &row_, size_t row_pre_, size_t col_, size_t row_end) {
    row_ = row_pre_;
    for (size_t j = row_ + 1; j < row_end; ++j)
      if (abs((*this)(j, col_)) > abs((*this)(row_, col_))) row_ = j;
    if (row_ != row_pre_) {
      swap_row(row_, row_pre_);
      return true;
    }
    return false;
  }

  size_t r_sz, c_sz;
  Isz iszero;
  std::valarray<T> data;

public:
  matrix(size_t row, size_t col, Isz iszero_func, const T &val = T{}):
    r_sz(row), c_sz(col), iszero(iszero_func), data(val, row * col) { assert(row > 0 && col > 0); }
  matrix(size_t row, size_t col, Isz iszero_func, const std::valarray<T> &data_):
    r_sz(row), c_sz(col), iszero(iszero_func), data(data_) { assert(row > 0 && col > 0); }
  constexpr size_t row_size() const { return r_sz; }
  constexpr size_t col_size() const { return c_sz; }
  constexpr Isz iszero_func() const { return iszero; }
  std::valarray<T> view() const { return data; }
  T &operator()(size_t r, size_t c) { return data[r * col_size() + c]; }
  T operator()(size_t r, size_t c) const { return data[r * col_size() + c]; }
  friend std::istream &operator>>(std::istream &is, self &mat) {
    for (auto &i : mat.data) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &mat) {
    for (size_t i = 0; i < mat.row_size(); ++i)
      for (size_t j = 0; j < mat.col_size(); ++j) os << mat(i, j) << " \n"[j == mat.col_size() - 1];
    return os;
  }
#define SLICE__(name, para1_t, para1, ...) [[nodiscard]] [[nodiscard]] std::slice_array<T> name(para1_t para1) __VA_ARGS__ [[nodiscard]] std::valarray<T> name##_const(para1_t para1) const __VA_ARGS__
  SLICE__(row, size_t, r, { return data[std::slice(r * col_size(), col_size(), 1)]; })
  SLICE__(col, size_t, c, { return data[std::slice(c, row_size(), col_size())]; })
  SLICE__(diag, ptrdiff_t, d, {
    if (d >= 0) {
      assert((size_t)d < col_size());
      return data[std::slice((size_t)d, std::min(row_size(), col_size() - (size_t)d), col_size() + 1)];
    } else {
      assert((size_t)(-d) < row_size());
      return data[std::slice((size_t)(-d) * row_size(), std::min(col_size(), row_size() - (size_t)(-d)), col_size() + 1)];
    }
  })
#undef SLICE__
  [[nodiscard]] self submatrix(size_t row_l, size_t row_r, size_t col_l, size_t col_r) const { return self(row_r - row_l, col_r - col_l, iszero, data[std::gslice(row_l * col_size() + col_l, {row_r - row_l, col_r - col_l}, {col_size(), 1})]); }
  // [lhs] [rhs] -> [lhs rhs]
  friend self merge_lr(const self &lhs, const self &rhs) {
    assert(lhs.row_size() == rhs.row_size());
    self ret(lhs.row_size(), lhs.col_size() + rhs.col_size(), lhs.iszero, T{});
    ret.data[std::gslice(0, {lhs.row_size(), lhs.col_size()}, {ret.col_size(), 1})] = lhs.view();
    ret.data[std::gslice(lhs.col_size(), {rhs.row_size(), rhs.col_size()}, {ret.col_size(), 1})] = rhs.view();
    return ret;
  }
  // [lhs] [rhs] -> [lhs; rhs]
  friend self merge_ud(const self &lhs, const self &rhs) {
    assert(lhs.col_size() == rhs.col_size());
    self ret(lhs.row_size() + rhs.row_size(), lhs.col_size(), lhs.iszero, T{});
    ret.data[std::slice(0, lhs.row_size() * lhs.col_size(), 1)] = lhs.view();
    ret.data[std::slice(lhs.row_size() * lhs.col_size(), rhs.row_size() * rhs.col_size(), 1)] = rhs.view();
    return ret;
  }
#define OP__(op)                                                                \
  friend self operator op(self lhs, const T &val) { return lhs op## = val; }    \
  self &operator op##=(const T &val) {                                          \
    data op## = val;                                                            \
    return *this;                                                               \
  }                                                                             \
  friend self operator op(self lhs, const self &rhs) { return lhs op## = rhs; } \
  self &operator op##=(const self &rhs) {                                       \
    assert(row_size() == rhs.row_size() && col_size() == rhs.col_size());       \
    data op## = rhs.data;                                                       \
    return *this;                                                               \
  }
  OP__(+)
  OP__(-)
  OP__(%)
#undef OP__
#define OPF__(op, ...)                                                       \
  friend self operator op(self lhs, const T &val) { return lhs op## = val; } \
  self &operator op##=(const T &val) {                                       \
    data op## = val;                                                         \
    return *this;                                                            \
  }                                                                          \
  friend self operator op(const self &lhs, const self &rhs) __VA_ARGS__ self &operator op##=(const self &rhs) { return *this = *this op rhs; }
  OPF__(*, {
    assert(lhs.col_size() == rhs.row_size());
    self ret(lhs.row_size(), rhs.col_size(), lhs.iszero, T{});
    for (size_t i = 0; i < ret.row_size(); ++i) {
      auto &&r_ = lhs.row_const(i);
      for (size_t j = 0; j < ret.col_size(); ++j) ret(i, j) = (r_ * rhs.col_const(j)).sum();
    }
    return ret;
  })
  OPF__(/, { return lhs * rhs.inverse().value(); })
#undef OPF__
  constexpr void swap_row(size_t r1, size_t r2) {
    if (r1 == r2) return;
    std::valarray<T> __ = row(r1);
    row(r1) = row(r2);
    row(r2) = __;
  }
  constexpr void swap_col(size_t c1, size_t c2) {
    if (c1 == c2) return;
    std::valarray<T> __ = col(c1);
    col(c1) = col(c2);
    col(c2) = __;
  }
  constexpr void swap_diag(size_t d1, size_t d2) {
    if (d1 == d2) return;
    std::valarray<T> __ = diag(d1);
    diag(d1) = diag(d2);
    diag(d2) = __;
  }
  virtual i64 do_gauss_range(size_t row_start, size_t row_end, bool clear_all = true) {
    assert(row_start < row_end && row_end <= row_size());
    u64 rk = 0;
    bool neg = false;
    for (size_t i = row_start, now_row; i < std::min(row_end, col_size()); ++i) {
      neg ^= gauss_swapr__(now_row, rk, i, row_end);
      if (iszero((*this)(rk, i))) continue;
      std::valarray<T> tmp_ = data[std::slice(rk * col_size() + i + 1, col_size() - i - 1, 1)];
      for (u64 j = clear_all ? 0 : rk + 1; j < row_end; ++j) {
        if (j == rk || iszero((*this)(j, i))) continue;
        T &&_ = (*this)(j, i) / (*this)(rk, i);
        (*this)(j, i) = 0;
        data[std::slice(j * col_size() + i + 1, col_size() - i - 1, 1)] -= tmp_ * _;
      }
      ++rk;
    }
    return neg ? -((i64)rk) : (i64)rk;
  }
  i64 do_gauss(bool clear_all = true) { return do_gauss_range(0, row_size(), clear_all); }
  [[nodiscard]] self transpose() const {
    self ret(col_size(), row_size(), iszero, T{});
    for (size_t i = 0; i < row_size(); ++i) ret.col(i) = row_const(i);
    return ret;
  }
  [[nodiscard]] std::optional<self> inverse() const {
    assert(row_size() == col_size());
    self ret(row_size(), col_size(), iszero, T{});
    ret.diag(0) = 1;
    if ((size_t)abs((ret = merge_lr(*this, ret)).do_gauss()) != row_size()) return {};
    for (size_t i = 0; i < row_size(); ++i) ret.data[std::slice((i * 2 + 1) * col_size(), col_size(), 1)] /= std::valarray<T>(ret(i, i), col_size());
    ret = ret.submatrix(0, row_size(), col_size(), col_size() * 2);
    return ret;
  }
  [[nodiscard]] T trace() const { return diag(0).sum(); }
  [[nodiscard]] size_t rank() const { return abs(self(*this).do_gauss(false)); }
  [[nodiscard]] T det() const {
    assert(row_size() == col_size());
    if (row_size() == 0) return 1;
    self tmp_(*this);
    i64 rk_ = tmp_.do_gauss(false);
    if ((u64)abs(rk_) != row_size()) return T{};
    T ret = tmp_(0, 0);
    for (size_t i = 1; i < row_size(); ++i) ret *= tmp_(i, i);
    return rk_ < 0 ? -ret : ret;
  }
};

}  // namespace tifa_libs::math

#endif