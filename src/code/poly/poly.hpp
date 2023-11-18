#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Pldt>
class poly {
  Pldt p;

 public:
  using value_type = typename Pldt::value_type;
  using data_type = vec<value_type>;

  explicit constexpr poly(u32 sz = 1, value_type const &val = value_type{}) : p(sz, val) {}
  constexpr poly(typename data_type::const_iterator begin, typename data_type::const_iterator end) : p(begin, end) {}
  explicit constexpr poly(std::initializer_list<value_type> v) : p(v) {}
  template <class T>
  explicit constexpr poly(vec<T> const &v) : p(v) {}

  constexpr friend std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.p.d) is >> val;
    return is;
  }
  constexpr friend std::ostream &operator<<(std::ostream &os, const poly &poly) {
    if (!poly.size()) return os;
    for (u32 i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.d.back();
  }

  constexpr u32 size() const { return p.d.size(); }
  constexpr data_type &data() { return p.d; }
  constexpr data_type const &data() const { return p.d; }

  constexpr value_type &operator[](u32 x) { return p.d[x]; }
  constexpr value_type operator[](u32 x) const { return p.d[x]; }
  constexpr value_type operator()(value_type x) const {
    value_type ans = 0;
    for (u32 i = size() - 1; ~i; --i) ans = ans * x + p.d[i];
    return ans;
  }

  template <class F>
  void apply_range(u32 l, u32 r, F f) {
    assert(l < r && r <= size());
    for (u32 i = l; i < r; ++i) f(i, p.d[i]);
  }
  template <class F>
  void apply(F f) { apply_range(0, size(), f); }
  constexpr void resize(u32 size) { p.d.resize(size); }
  constexpr poly pre(u32 size) const {
    poly _ = *this;
    _.resize(size);
    return _;
  }
  constexpr void strip() {
    auto it = std::find_if(p.d.rbegin(), p.d.rend(), [](auto const &x) { return x != 0; });
    p.d.resize(p.d.rend() - it);
    if (p.d.empty()) p.d.push_back(value_type(0));
  }
  constexpr void reverse(u32 n = 0) { std::reverse(p.d.begin(), p.d.begin() + (n ? n : size())); }

  void conv(poly const &r, u32 ans_size) { p.conv(r.p, ans_size); }
  void conv(poly const &r) { p.conv(r.p); }

  constexpr poly operator-() const {
    poly ret = *this;
    ret.apply([](u32, auto &v) { v = -v; });
    return ret;
  }

  friend poly operator+(poly p, value_type c) {
    p[0] += c;
    return p;
  }
  friend poly operator+(value_type c, poly const &p) { return p + c; }
  friend poly operator-(poly p, value_type c) {
    p[0] -= c;
    return p;
  }
  friend poly operator-(value_type c, poly const &p) { return p - c; }

  constexpr poly &operator*=(value_type c) {
    apply([&c](u32, auto &v) { v *= c; });
    return *this;
  }
  constexpr friend poly operator*(poly p, value_type c) { return p *= c; }
  constexpr friend poly operator*(value_type c, poly p) { return p *= c; }

  constexpr poly &operator+=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](u32 i, auto &v) { v += r[i]; });
    return *this;
  }
  friend poly operator+(poly l, poly const &r) { return l += r; }

  constexpr poly &operator-=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](u32 i, auto &v) { v -= r[i]; });
    return *this;
  }
  friend poly operator-(poly l, poly const &r) { return l -= r; }

  poly &operator*=(poly const &r) {
    if (!r.size()) {
      resize(1);
      p.d[0] = 0;
      return *this;
    }
    conv(r);
    return *this;
  }
  friend poly operator*(poly l, poly const &r) { return l *= r; }
};

}  // namespace tifa_libs::math

#endif