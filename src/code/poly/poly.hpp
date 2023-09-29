#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Pldt>
class poly {
  Pldt p;

public:
  using data_type = Pldt;
  using value_type = typename data_type::value_type;

  explicit constexpr poly(size_t sz = 1):
    p(sz) {}
  template <class T>
  explicit constexpr poly(vec<T> const &v):
    p(v) {}

  constexpr friend std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.p.d) is >> val;
    return is;
  }
  constexpr friend std::ostream &operator<<(std::ostream &os, const poly &poly) {
    if (!poly.size()) return os;
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.d.back();
  }

  constexpr size_t size() const { return p.d.size(); }
  constexpr data_type &data() { return p.d; }
  constexpr data_type const &data() const { return p.d; }

  constexpr value_type &operator[](size_t x) { return p.d[x]; }
  constexpr value_type operator[](size_t x) const { return p.d[x]; }
  constexpr value_type operator()(value_type x) const {
    value_type ans = 0;
    for (size_t i = size() - 1; ~i; --i) ans = ans * x + p.d[i];
    return ans;
  }

  template <class F>
  void apply_range(size_t l, size_t r, F f) {
    assert(l <= r && r < size());
    for (size_t i = l; i < r; ++i) f(i, p.d[i]);
  }
  template <class F>
  void apply(F f) { apply_range(0, size(), f); }
  constexpr void resize(size_t size) { p.d.resize(size); }
  constexpr void strip() {
    while (!p.d.empty() && !p.d.back()) p.d.pop_back();
    if (p.d.empty()) p.d.push_back(value_type(0));
  }
  constexpr void reverse() { std::reverse(p.d.begin(), p.d.end()); }

  void conv(poly const &r, size_t ans_size) { p.conv(r, ans_size); }
  void conv(poly const &r) { p.conv(r); }

  constexpr poly operator-() const {
    poly ret = *this;
    ret.apply([]([[maybe_unused]] size_t i, auto &v) { v = -v; });
    return ret;
  }

  constexpr poly &operator*=(value_type c) {
    apply([c]([[maybe_unused]] size_t i, auto &v) { v *= c; });
    return *this;
  }
  constexpr friend poly operator*(poly p, value_type c) { return p *= c; }
  constexpr friend poly operator*(value_type c, poly p) { return p *= c; }

  constexpr poly &operator+=(poly const &r) {
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r]([[maybe_unused]] size_t i, auto &v) { v += r[i]; });
    return *this;
  }
  friend poly operator+(poly l, poly const &r) { return l += r; }

  constexpr poly &operator-=(poly const &r) {
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r]([[maybe_unused]] size_t i, auto &v) { v -= r[i]; });
    return *this;
  }
  friend poly operator-(poly l, poly const &r) { return l -= r; }

  poly &operator*=(poly const &r) {
    p.conv(r);
    return *this;
  }
  friend poly operator*(poly l, poly const &r) { return l *= r; }
};

}  // namespace tifa_libs::math

#endif