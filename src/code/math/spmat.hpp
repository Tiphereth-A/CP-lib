#ifndef TIFA_LIBS_SPARSE_MAT
#define TIFA_LIBS_SPARSE_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
class spmat {
  using node = std::pair<size_t, T>;
  using data_t = vec<vec<node>>;

  size_t r, c;
  data_t d;

public:
  using value_type = T;

  spmat(size_t row, size_t col):
    r(row), c(col), d(r) { assert(row > 0 && col > 0); }

  constexpr size_t row() const { return r; }
  constexpr size_t col() const { return c; }
  constexpr data_t data() const { return d; }
  constexpr data_t &data() { return d; }
  constexpr node &operator()(size_t r, size_t c) {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    d[r].emplace_back(c, T{});
    return d[r].back().second;
  }
  constexpr const node &operator()(size_t r, size_t c) const {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    return T{};
  }

  constexpr void shrink_row(size_t r) {
    if (!d[r].empty()) d[r].erase(std::remove_if(d[r].begin(), d[r].end(), [](node const &x) { return x.second == T{}; }), d[r].end());
  }
  constexpr void sort_row(size_t r) {
    if (!d[r].empty()) std::sort(d[r].begin(), d[r].end());
  }

  template <class F>
  void apply(F f) {
    for (size_t i = 0; i < r; ++i) {
      if (d[i].empty()) continue;
      for (auto &[j, v] : d[i]) f(i, j, v);
    }
  }
  template <class F>
  friend spmat merge(spmat l, spmat r, F f) {
    size_t r_ = l.row(), c_ = l.col();
    assert(r_ == r.row() && c_ == r.col());
    spmat ret(r_, c_);
    for (size_t i = 0; i < r_; ++i) {
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
          size_t j = std::distance(f1, l.begin());
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
    ret.apply([]([[maybe_unused]] size_t r, [[maybe_unused]] size_t c, T &v) { v = -v; });
    return ret;
  }

  constexpr friend spmat operator+(spmat l, const T &v) { return l += v; }
  constexpr friend spmat operator+(const T &v, spmat l) { return l += v; }
  constexpr spmat &operator+=(const T &v) {
    apply([&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val += v; });
    return *this;
  }
  constexpr friend spmat operator-(spmat l, const T &v) { return l -= v; }
  constexpr friend spmat operator-(const T &v, spmat l) { return l -= v; }
  constexpr spmat &operator-=(const T &v) {
    apply([&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val -= v; });
    return *this;
  }
  constexpr friend spmat operator*(spmat l, const T &v) { return l *= v; }
  constexpr friend spmat operator*(const T &v, spmat l) { return l *= v; }
  constexpr spmat &operator*=(const T &v) {
    apply([&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val *= v; });
    return *this;
  }

  constexpr friend spmat operator+(spmat const &l, spmat const &r) {
    return merge(l, r, []([[maybe_unused]] size_t r, [[maybe_unused]] size_t c, T const &lv, T const &rv) { return lv + rv; });
  }
  constexpr spmat &operator+=(spmat const &r) { return *this = *this + r; }
  constexpr friend spmat operator-(spmat l, const spmat &r) { return l + (-r); }
  constexpr spmat &operator-=(const spmat &r) { return *this = *this - r; }
  constexpr friend spmat operator*(spmat l, const spmat &r) {
    size_t i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    spmat ret(i_, k_);
    for (size_t i = 0; i < i_; ++i) {
      if (l.d[i].empty()) continue;
      for (size_t j = 0; j < j_; ++j) {
        if (r.d[j].empty()) continue;
        for (size_t k = 0; k < k_; ++k) ret(i, k) += l(i, j) * r(j, k);
      }
      ret.shrink_row(i);
    }
    return ret;
  }
  constexpr spmat &operator*=(const spmat &r) { return *this = *this - r; }
};

}  // namespace tifa_libs::math

#endif