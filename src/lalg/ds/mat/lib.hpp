#pragma once

#include "../../../util/traits/others/lib.hpp"

namespace tifa_libs {

#define FOR1_(i, l, r) for (u32 i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_ (i, row_l, row_r)                       \
    FOR1_ (j, col_l, col_r)

template <class T>
class matrix {
  vec<T> d;
  u32 r_, c_;

 public:
  using val_t = T;

  CEXP matrix(u32 row, u32 col, cT_(T) v = T{}) NE : d(row* col, v), r_(row), c_(col) { assert(row > 0 && col > 0); }
  CEXP matrix(u32 row, u32 col, spn<T> data) NE : d(data), r_(row), c_(col) { assert(row > 0 && col > 0 && d.size() == row * col); }
  CEXP matrix(vvec<T> CR data) NE : d(data.size() * data[0].size()), r_((u32)data.size()), c_((u32)data[0].size()) {
    assert(data.size() > 0 && data[0].size() > 0);
    FOR1_ (i, 1, r_) assert((u32)data[i].size() == c_);
    FOR2_ (i, 0, r_, j, 0, c_) (*this)(i, j) = data[i][j];
  }

  CEXP u32 row() CNE { return r_; }
  CEXP u32 col() CNE { return c_; }
  CEXP vec<T> CR data() CNE { return d; }
  CEXP vec<T>& data() NE { return d; }
  CEXP TPN vec<T>::reference operator()(u32 r, u32 c) NE { return d[r * c_ + c]; }
  CEXP TPN vec<T>::const_reference operator()(u32 r, u32 c) CNE { return d[r * c_ + c]; }
  template <class F>
  CEXP void apply(F&& f) NE { apply_range(0, row(), 0, col(), std::forward<F>(f)); }
  template <class F>
  requires requires(F f, u32 i, u32 j, T& val) { f(i, j, val); }
  CEXP void apply_range(u32 row_l, u32 row_r, u32 col_l, u32 col_r, F&& f) NE {
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    T val;
    FOR2_ (i, row_l, row_r, j, col_l, col_r) f(i, j, val = (*this)(i, j)), (*this)(i, j) = val;
  }

  friend auto& operator>>(istream_c auto& is, matrix& mat) NE {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_, j, 0, c_) is >> mat(i, j);
    return is;
  }
  friend auto& operator<<(ostream_c auto& os, matrix CR mat) NE {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_ - 1, j, 0, c_) os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_ (j, 1, c_) os << ' ' << mat(r_ - 1, j);
    return os;
  }
  CEXP matrix submat(u32 row_l, u32 row_r, u32 col_l, u32 col_r) CNE {
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    FOR2_ (i, row_l, row_r, j, col_l, col_r) ret(i - row_l, j - col_l) = (*this)(i, j);
    return ret;
  }
  CEXP void swap_row(u32 r1, u32 r2) NE {
    if (assert(r1 < row() && r2 < row()); r1 == r2) return;
    FOR1_ (j, 0, col()) swap((*this)(r1, j), (*this)(r2, j));
  }
  CEXP void swap_col(u32 c1, u32 c2) NE {
    if (assert(c1 < col() && c2 < col()); c1 == c2) return;
    FOR1_ (i, 0, row()) swap((*this)(i, c1), (*this)(i, c2));
  }
  CEXP matrix operator-() CNE {
    if CEXP (std::is_same_v<T, bool>) return *this;
    else {
      matrix ret = *this;
      ret.apply([](u32, u32, T& v) NE { v = -v; });
      return ret;
    }
  }
  friend CEXP matrix operator+(matrix l, cT_(T) v) NE { return l += v; }
  friend CEXP matrix operator+(cT_(T) v, matrix l) NE { return l += v; }
  CEXP matrix& operator+=(cT_(T) v) NE {
    if CEXP (std::is_same_v<T, bool>) apply([&v](u32, u32, auto& val) NE { val = val ^ v; });
    else apply([&v](u32, u32, T& val) NE { val += v; });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, cT_(T) v) NE { return l -= v; }
  CEXP matrix& operator-=(cT_(T) v) NE {
    if CEXP (std::is_same_v<T, bool>) apply([&v](u32, u32, auto& val) NE { val = val ^ v; });
    else apply([&v](u32, u32, T& val) NE { val -= v; });
    return *this;
  }
  friend CEXP matrix operator*(matrix l, cT_(T) v) NE { return l *= v; }
  friend CEXP matrix operator*(cT_(T) v, matrix l) NE { return l *= v; }
  CEXP matrix& operator*=(cT_(T) v) NE {
    if CEXP (std::is_same_v<T, bool>) {
      if (!v) fill(begin(d), end(d), false);
      return *this;
    } else apply([&v](u32, u32, T& val) NE { val *= v; });
    return *this;
  }
  friend CEXP matrix operator+(matrix l, matrix CR r) NE { return l += r; }
  CEXP matrix& operator+=(matrix CR r) NE {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>) apply([&r](u32 i, u32 j, auto& val) NE { val = val ^ r(i, j); });
    else apply([&r](u32 i, u32 j, T& val) NE { val += r(i, j); });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, matrix CR r) NE { return l -= r; }
  CEXP matrix& operator-=(matrix CR r) NE {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>) apply([&r](u32 i, u32 j, auto& val) NE { val = val ^ r(i, j); });
    else apply([&r](u32 i, u32 j, T& val) NE { val -= r(i, j); });
    return *this;
  }
  friend CEXP matrix operator*(matrix CR l, matrix CR r) NE {
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
  CEXP matrix& operator*=(matrix CR r) NE { return *this = *this * r; }
  CEXP vec<T> lproj(spn<T> x) CNE {
    const u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    FOR1_ (j, 0, c_)
      if CEXP (std::is_same_v<T, bool>) {
        bool v = false;
        FOR1_ (i, 0, r_) v = v ^ ((*this)(i, j) && x[i]);
        ret[j] = v;
      } else {
        T v{};
        FOR1_ (i, 0, r_) v += (*this)(i, j) * x[i];
        ret[j] = v;
      }
    return ret;
  }
  CEXP bool operator==(matrix CR r) CNE {
    if (row() != r.row() || col() != r.col()) return 0;
    return d == r.d;
  }
};

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs
