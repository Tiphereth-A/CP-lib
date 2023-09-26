#ifndef TIFA_LIBS_SPARSE_MAT
#define TIFA_LIBS_SPARSE_MAT

#include "../util/util.hpp"
#include <iterator>

namespace tifa_libs::math {

template <class T>
class spmat {
  using node = std::pair<size_t, T>;
  using data_t = vec<vec<node>>;

  size_t r, c;
  T initv_;
  data_t d;

public:
  using value_type = T;

  spmat(size_t row, size_t col, T const &v = T{}):
    r(row), c(col), initv_(v), d() { assert(row > 0 && col > 0); }

  constexpr size_t row() const { return r; }
  constexpr size_t col() const { return c; }
  constexpr const T &init_val() const { return initv_; }
  constexpr T &init_val() { return initv_; }
  constexpr data_t data() const { return d; }
  constexpr data_t &data() { return d; }
  constexpr node &operator()(size_t r, size_t c) {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    d[r].emplace_back(c, initv_);
    return d[r].back().second;
  }
  constexpr const node &operator()(size_t r, size_t c) const {
    for (auto &[c_, v] : d[r])
      if (c == c_) return v;
    return initv_;
  }

  constexpr void shrink() {
    for (auto &r : d)
      if (!d.empty()) d.erase(std::remove_if(d.begin(), d.end(), [](node const &x) { return x.second == T{}; }), d.end());
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
    spmat ret(std::max(l.row(), r.row()), std::max(l.col(), r.col()));
    size_t r_ = ret.row(), lr_ = l.row(), rr_ = r.row();
    for (size_t i = 0; i < r_; ++i) {
      if (i >= lr_ || (i < rr_ && l[i].empty())) {
        if (!r[i].empty()) ret[i] = r[i];
        continue;
      }
      if (i >= rr_ || (i < lr_ && r[i].empty())) {
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
};

}  // namespace tifa_libs::math

#endif