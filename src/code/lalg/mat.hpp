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
  using val_t = T;

  CEXP matrix(u32 row, u32 col, cT_(T) v = T{}) NE : d(row, vec<T>(col, v)) { assert(row > 0 && col > 0); }
  CEXPE matrix(cT_(vvec<T>) data) NE : d(data) { assert(data.size() > 0 && data[0].size() > 0); }

  CEXP u32 row() CNE { return (u32)d.size(); }
  CEXP u32 col() CNE { return (u32)d[0].size(); }
  CEXP vvec<T> CR data() CNE { return d; }
  CEXP vvec<T> &data() NE { return d; }
  CEXP TPN vec<T>::reference operator()(u32 r, u32 c) NE { return d[r][c]; }
  CEXP TPN vec<T>::const_reference operator()(u32 r, u32 c) CNE { return d[r][c]; }
  template <class F>
  CEXP void apply(F &&f) NE { apply_range(0, row(), 0, col(), std::forward<F>(f)); }
  template <class F>
  requires requires(F f, u32 i, u32 j, T &val) { f(i, j, val); }
  CEXP void apply_range(u32 row_l, u32 row_r, u32 col_l, u32 col_r, F &&f) NE {
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    T val;
    FOR2_ (i, row_l, row_r, j, col_l, col_r) f(i, j, val = (*this)(i, j)), (*this)(i, j) = val;
  }

  friend std::istream &operator>>(std::istream &is, matrix &mat) NE {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_, j, 0, c_) is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix CR mat) NE {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_ (i, 0, r_ - 1, j, 0, c_) os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_ (j, 1, c_) os << ' ' << mat(r_ - 1, j);
    return os;
  }
  CEXP matrix submat(u32 row_l, u32 row_r, u32 col_l, u32 col_r) CNE {
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    FOR1_ (i, row_l, row_r) std::copy(d[i].begin() + col_l, d[i].begin() + col_r, ret.d[i - row_l].begin());
    return ret;
  }
  CEXP void swap_row(u32 r1, u32 r2) NE {
    if (assert(r1 < row() && r2 < row()); r1 == r2) return;
    swap(d[r1], d[r2]);
  }
  CEXP void swap_col(u32 c1, u32 c2) NE {
    if (assert(c1 < col() && c2 < col()); c1 == c2) return;
    FOR1_ (i, 0, row()) swap((*this)(i, c1), (*this)(i, c2));
  }
  CEXP matrix operator-() CNE {
    if CEXP (std::is_same_v<T, bool>) return *this;
    else {
      matrix ret = *this;
      ret.apply([](u32, u32, T &v) NE { v = -v; });
      return ret;
    }
  }
  friend CEXP matrix operator+(matrix l, cT_(T) v) NE { return l += v; }
  friend CEXP matrix operator+(cT_(T) v, matrix l) NE { return l += v; }
  CEXP matrix &operator+=(cT_(T) v) NE {
    if CEXP (std::is_same_v<T, bool>) apply([&v](u32, u32, auto &val) NE { val = val ^ v; });
    else apply([&v](u32, u32, T &val) NE { val += v; });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, cT_(T) v) NE { return l -= v; }
  CEXP matrix &operator-=(cT_(T) v) NE {
    if CEXP (std::is_same_v<T, bool>) apply([&v](u32, u32, auto &val) NE { val = val ^ v; });
    else apply([&v](u32, u32, T &val) NE { val -= v; });
    return *this;
  }
  friend CEXP matrix operator*(matrix l, cT_(T) v) NE { return l *= v; }
  friend CEXP matrix operator*(cT_(T) v, matrix l) NE { return l *= v; }
  CEXP matrix &operator*=(cT_(T) v) NE {
    if CEXP (std::is_same_v<T, bool>) {
      if (!v)
        for (auto &i : d) std::ranges::fill(i, false);
      return *this;
    } else apply([&v](u32, u32, T &val) NE { val *= v; });
    return *this;
  }
  friend CEXP matrix operator+(matrix l, matrix CR r) NE { return l += r; }
  CEXP matrix &operator+=(matrix CR r) NE {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>) apply([&r](u32 i, u32 j, auto &val) NE { val = val ^ r(i, j); });
    else apply([&r](u32 i, u32 j, T &val) NE { val += r(i, j); });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, matrix CR r) NE { return l -= r; }
  CEXP matrix &operator-=(matrix CR r) NE {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>) apply([&r](u32 i, u32 j, auto &val) NE { val = val ^ r(i, j); });
    else apply([&r](u32 i, u32 j, T &val) NE { val -= r(i, j); });
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
  CEXP matrix &operator*=(matrix CR r) NE { return *this = *this * r; }
  CEXP vec<T> lproj(spn<T> x) CNE {
    const u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    flt_ (u32, i, 0, c_)
      if CEXP (std::is_same_v<T, bool>) ret[i] = std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), false, std::bit_xor<bool>{}, std::bit_and<bool>{});
      else ret[i] = std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), T{});
    return ret;
  }
  CEXP bool operator==(matrix CR r) CNE {
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