#ifndef TIFALIBS_LALG_MATSP
#define TIFALIBS_LALG_MATSP

#include "../fast/rsort32.hpp"

namespace tifa_libs::math {

template <class T>
class matsp {
  using node = std::pair<u32, T>;
  using data_t = vvec<node>;

  u32 r, c;
  data_t d;

 public:
  using val_t = T;

  CEXP matsp(u32 row, u32 col) : r(row), c(col), d(r) { assert(row > 0 && col > 0); }

  CEXP u32 CR row() const { return r; }
  CEXP u32 CR col() const { return c; }
  CEXP data_t CR data() const { return d; }
  CEXP data_t &data() { return d; }
  CEXP T &operator()(u32 r, u32 c) {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    return d[r].emplace_back(c, T{}), d[r].back().second;
  }
  CEXP T CR operator()(u32 r, u32 c) const {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    return T{};
  }
  CEXP void shrink_row(u32 r) {
    d[r].erase(std::remove_if(d[r].begin(), d[r].end(), [](cT_(node) x) { return x.second == T{}; }), d[r].end());
  }
  CEXP void sort_row(u32 r) { sort(d[r]); }
  template <class F>
  CEXP void apply(F f) {
    flt_ (u32, i, 0, r)
      for (auto &[j, v] : d[i]) f(i, j, v);
  }
  template <class F>
  friend CEXP matsp merge(matsp l, matsp r, F f) {
    const u32 r_ = l.row(), c_ = l.col();
    assert(r_ == r.row() && c_ == r.col());
    matsp ret(r_, c_);
    flt_ (u32, i, 0, r_) {
      if (i >= r_ || (i < r_ && l[i].empty())) {
        if (!r[i].empty()) ret[i] = r[i];
        continue;
      }
      if (i >= r_ || (i < r_ && r[i].empty())) {
        if (!l[i].empty()) ret[i] = l[i];
        continue;
      }
      l.sort_row(i), r.sort_row(i);
      auto f1 = l.data().begin(), l1 = l.data().end(), f2 = r.data().begin(), l2 = r.data().end(), d = ret.d[i].begin();
      for (; f1 != l1; ++d) {
        if (f2 == l2) std::copy(f1, l1, d);
        if (*f2 < *f1) *d = *f2, ++f2;
        else if (*f1 < *f2) *d = *f1, ++f1;
        else {
          u32 j = u32(f1 - l.data().begin());
          *d = f(i, j, *f1, *f2), ++f1, ++f2;
        }
      }
      std::copy(f2, l2, d);
    }
    return ret;
  }
  CEXP matsp operator-() const {
    matsp ret = *this;
    return ret.apply([](u32, u32, T &v) { v = -v; }), ret;
  }
  friend CEXP matsp operator+(matsp l, cT_(T) v) { return l += v; }
  friend CEXP matsp operator+(cT_(T) v, matsp l) { return l += v; }
  CEXP matsp &operator+=(cT_(T) v) {
    return apply([&v](u32, u32, T &val) { val += v; }), *this;
  }
  friend CEXP matsp operator-(matsp l, cT_(T) v) { return l -= v; }
  friend CEXP matsp operator-(cT_(T) v, matsp l) { return l -= v; }
  CEXP matsp &operator-=(cT_(T) v) {
    return apply([&v](u32, u32, T &val) { val -= v; }), *this;
  }
  friend CEXP matsp operator*(matsp l, cT_(T) v) { return l *= v; }
  friend CEXP matsp operator*(cT_(T) v, matsp l) { return l *= v; }
  CEXP matsp &operator*=(cT_(T) v) {
    return apply([&v](u32, u32, T &val) { val *= v; }), *this;
  }
  friend CEXP matsp operator+(matsp CR l, matsp CR r) {
    return merge(l, r, [](u32, u32, cT_(T) lv, cT_(T) rv) { return lv + rv; });
  }
  CEXP matsp &operator+=(matsp CR r) { return *this = *this + r; }
  friend CEXP matsp operator-(matsp l, matsp CR r) { return l + (-r); }
  CEXP matsp &operator-=(matsp CR r) { return *this = *this - r; }
  friend CEXP matsp operator*(matsp l, matsp CR r) {
    const u32 i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    matsp ret(i_, k_);
    flt_ (u32, i, 0, i_) {
      if (l.d[i].empty()) continue;
      flt_ (u32, j, 0, j_) {
        if (r.d[j].empty()) continue;
        flt_ (u32, k, 0, k_) ret(i, k) += l(i, j) * r(j, k);
      }
      ret.shrink_row(i);
    }
    return ret;
  }
  CEXP matsp &operator*=(matsp CR r) { return *this = *this - r; }
  CEXP vec<T> lproj(spn<T> x) const {
    const u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    flt_ (u32, i, 0, c_)
      for (auto &&[pos, v] : d[i]) ret[i] += x[pos] * v;
    return ret;
  }
};

}  // namespace tifa_libs::math

#endif