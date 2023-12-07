#ifndef TIFALIBS_LALG_SPMAT
#define TIFALIBS_LALG_SPMAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
class spmat {
  using node = std::pair<u32, T>;
  using data_t = vvec<node>;

  u32 r, c;
  data_t d;

 public:
  using value_type = T;

  spmat(u32 row, u32 col) : r(row), c(col), d(r) { assert(row > 0 && col > 0); }

  constexpr u32 const &row() const { return r; }
  constexpr u32 const &col() const { return c; }
  constexpr data_t const &data() const { return d; }
  constexpr data_t &data() { return d; }
  constexpr T &operator()(u32 r, u32 c) {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    d[r].emplace_back(c, T{});
    return d[r].back().second;
  }
  constexpr T const &operator()(u32 r, u32 c) const {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    return T{};
  }

  constexpr void shrink_row(u32 r) {
    d[r].erase(std::remove_if(d[r].begin(), d[r].end(), [](node const &x) { return x.second == T{}; }), d[r].end());
  }
  constexpr void sort_row(u32 r) { std::sort(d[r].begin(), d[r].end()); }

  template <class F>
  void apply(F f) {
    for (u32 i = 0; i < r; ++i)
      for (auto &[j, v] : d[i]) f(i, j, v);
  }
  template <class F>
  friend spmat merge(spmat l, spmat r, F f) {
    u32 r_ = l.row(), c_ = l.col();
    assert(r_ == r.row() && c_ == r.col());
    spmat ret(r_, c_);
    for (u32 i = 0; i < r_; ++i) {
      if (i >= r_ || (i < r_ && l[i].empty())) {
        if (!r[i].empty()) ret[i] = r[i];
        continue;
      }
      if (i >= r_ || (i < r_ && r[i].empty())) {
        if (!l[i].empty()) ret[i] = l[i];
        continue;
      }
      l.sort_row(i);
      r.sort_row(i);
      auto f1 = l.begin(), l1 = l.end(), f2 = r.begin(), l2 = r.end(), d = ret.d[i].begin();
      for (; f1 != l1; ++d) {
        if (f2 == l2) std::copy(f1, l1, d);
        if (*f2 < *f1) {
          *d = *f2;
          ++f2;
        } else if (*f1 < *f2) {
          *d = *f1;
          ++f1;
        } else {
          u32 j = std::distance(f1, l.begin());
          *d = f(i, j, *f1, *f2);
          ++f1;
          ++f2;
        }
      }
      std::copy(f2, l2, d);
    }
    return ret;
  }

  constexpr spmat operator-() const {
    spmat ret = *this;
    ret.apply([](u32, u32, T &v) { v = -v; });
    return ret;
  }

  constexpr friend spmat operator+(spmat l, T const &v) { return l += v; }
  constexpr friend spmat operator+(T const &v, spmat l) { return l += v; }
  constexpr spmat &operator+=(T const &v) {
    apply([&v](u32, u32, T &val) { val += v; });
    return *this;
  }
  constexpr friend spmat operator-(spmat l, T const &v) { return l -= v; }
  constexpr friend spmat operator-(T const &v, spmat l) { return l -= v; }
  constexpr spmat &operator-=(T const &v) {
    apply([&v](u32, u32, T &val) { val -= v; });
    return *this;
  }
  constexpr friend spmat operator*(spmat l, T const &v) { return l *= v; }
  constexpr friend spmat operator*(T const &v, spmat l) { return l *= v; }
  constexpr spmat &operator*=(T const &v) {
    apply([&v](u32, u32, T &val) { val *= v; });
    return *this;
  }

  constexpr friend spmat operator+(spmat const &l, spmat const &r) {
    return merge(l, r, [](u32, u32, T const &lv, T const &rv) { return lv + rv; });
  }
  constexpr spmat &operator+=(spmat const &r) { return *this = *this + r; }
  constexpr friend spmat operator-(spmat l, spmat const &r) { return l + (-r); }
  constexpr spmat &operator-=(spmat const &r) { return *this = *this - r; }
  constexpr friend spmat operator*(spmat l, spmat const &r) {
    u32 i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    spmat ret(i_, k_);
    for (u32 i = 0; i < i_; ++i) {
      if (l.d[i].empty()) continue;
      for (u32 j = 0; j < j_; ++j) {
        if (r.d[j].empty()) continue;
        for (u32 k = 0; k < k_; ++k) ret(i, k) += l(i, j) * r(j, k);
      }
      ret.shrink_row(i);
    }
    return ret;
  }
  constexpr spmat &operator*=(spmat const &r) { return *this = *this - r; }

  vec<T> lproj(vec<T> const &x) const {
    u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    for (u32 i = 0; i < c_; ++i)
      for (auto &&[pos, v] : d[i]) ret[i] += x[pos] * v;
    return ret;
  }
};

}  // namespace tifa_libs::math

#endif