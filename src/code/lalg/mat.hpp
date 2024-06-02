#ifndef TIFALIBS_LALG_MAT
#define TIFALIBS_LALG_MAT

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

  CEXP matrix(u32 row, u32 col, cT_(T) v = T{}) : d(row, vec<T>(col, v)) { assert(row > 0 && col > 0); }
  explicit CEXP matrix(cT_(vvec<T>) data) : d(data) { assert(data.size() > 0 && data[0].size() > 0); }

  CEXP u32 row() const { return (u32)d.size(); }
  CEXP u32 col() const { return (u32)d[0].size(); }
  CEXP vvec<T> CR data() const { return d; }
  CEXP vvec<T> &data() { return d; }
  CEXP TPN vec<T>::reference operator()(u32 r, u32 c) { return d[r][c]; }
  CEXP TPN vec<T>::const_reference operator()(u32 r, u32 c) const { return d[r][c]; }
  template <class F>
  CEXP void apply(F &&f) { apply_range(0, row(), 0, col(), std::forward<F>(f)); }
  template <class F>
  requires requires(F f, u32 i, u32 j, T &val) { f(i, j, val); }
  CEXP void apply_range(u32 row_l, u32 row_r, u32 col_l, u32 col_r, F &&f) {
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    FOR2_ (i, row_l, row_r, j, col_l, col_r) f(i, j, (*this)(i, j));
  }

  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_, j, 0, c_) is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix CR mat) {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_ - 1, j, 0, c_) os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_ (j, 1, c_) os << ' ' << mat(r_ - 1, j);
    return os;
  }
  CEXP matrix submat(u32 row_l, u32 row_r, u32 col_l, u32 col_r) const {
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    return ret.apply_range(0, ret.row(), 0, ret.col(), [this, row_l, col_l](u32 i, u32 j, T &v) { v = (*this)(i + row_l, j + col_l); }), ret;
  }
  CEXP void swap_row(u32 r1, u32 r2) {
    assert(r1 < row() && r2 < row());
    if (r1 == r2) return;
    swap(d[r1], d[r2]);
  }
  CEXP void swap_col(u32 c1, u32 c2) {
    assert(c1 < col() && c2 < col());
    if (c1 == c2) return;
    FOR1_ (i, 0, row()) swap((*this)(i, c1), (*this)(i, c2));
  }
  CEXP matrix operator-() const {
    if CEXP (std::is_same_v<T, bool>) return *this;
    else {
      matrix ret = *this;
      return ret.apply_range(0, row(), 0, col(), [](u32, u32, T &v) { v = -v; }), ret;
    }
  }
  friend CEXP matrix operator+(matrix l, cT_(T) v) { return l += v; }
  friend CEXP matrix operator+(cT_(T) v, matrix l) { return l += v; }
  CEXP matrix &operator+=(cT_(T) v) {
    if CEXP (std::is_same_v<T, bool>) apply_range(0, row(), 0, col(), [&v](u32, u32, auto &val) { val = val ^ v; });
    else apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val += v; });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, cT_(T) v) { return l -= v; }
  CEXP matrix &operator-=(cT_(T) v) {
    if CEXP (std::is_same_v<T, bool>) apply_range(0, row(), 0, col(), [&v](u32, u32, auto &val) { val = val ^ v; });
    else apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val -= v; });
    return *this;
  }
  friend CEXP matrix operator*(matrix l, cT_(T) v) { return l *= v; }
  friend CEXP matrix operator*(cT_(T) v, matrix l) { return l *= v; }
  CEXP matrix &operator*=(cT_(T) v) {
    if CEXP (std::is_same_v<T, bool>) {
      if (!v)
        for (auto &i : d) i.clear(), i.resize(col());
      return *this;
    } else apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val *= v; });
    return *this;
  }
  friend CEXP matrix operator+(matrix l, matrix CR r) { return l += r; }
  CEXP matrix &operator+=(matrix CR r) {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>) apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, auto &val) { val = val ^ r(i, j); });
    else apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, T &val) { val += r(i, j); });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, matrix CR r) { return l -= r; }
  CEXP matrix &operator-=(matrix CR r) {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>) apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, auto &val) { val = val ^ r(i, j); });
    else apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, T &val) { val -= r(i, j); });
    return *this;
  }
  friend CEXP matrix operator*(matrix CR l, matrix CR r) {
    const u32 i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    matrix ret(i_, k_);
    FOR1_ (i, 0, i_)
      FOR1_ (j, 0, j_)
        FOR1_ (k, 0, k_)
          if CEXP (std::is_same_v<T, bool>) ret(i, k) = ret(i, k) ^ (l(i, j) && r(j, k));
          else ret(i, k) += l(i, j) * r(j, k);
    return ret;
  }
  CEXP matrix &operator*=(matrix CR r) { return *this = *this * r; }
  CEXP vec<T> lproj(vec<T> CR x) const {
    const u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    flt_ (u32, i, 0, c_)
      if CEXP (std::is_same_v<T, bool>) ret[i] = std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), false, std::bit_xor<bool>{}, std::bit_and<bool>{});
      else ret[i] = std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), T{});
    return ret;
  }
  CEXP bool operator==(matrix CR r) const {
    if (row() != r.row() || col() != r.col()) return 0;
    FOR1_ (i, 0, row())
      if (d[i] != r.d[i]) return 0;
    return 1;
  }
};

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs::math

#endif