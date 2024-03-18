#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../util/util.hpp"

namespace tifa_libs::math {

// clang-format off
enum ccore_t { ct_FFT, ct_3NTT, ct_NTT, ct_CNTT };
// clang-format on

template <class mint, class ccore>
requires requires(ccore cc, vec<mint> l, vec<mint> const &r, u32 sz) {
  { ccore::ct_cat } -> std::same_as<ccore_t const &>;
  cc.conv(l, r);
  cc.conv(l, r, sz);
}
class poly {
  vec<mint> d;

 public:
  using value_type = mint;
  using data_type = vec<value_type>;
  using ccore_type = ccore;
  static inline ccore_type conv_core;

  explicit constexpr poly(u32 sz = 1, value_type const &val = value_type{}) : d(sz, val) {}
  constexpr poly(typename data_type::const_iterator begin, typename data_type::const_iterator end) : d(begin, end) {}
  explicit constexpr poly(std::initializer_list<value_type> v) : d(v) {}
  template <class T>
  explicit constexpr poly(vec<T> const &v) : d(v) {}

  friend constexpr std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.d) is >> val;
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, poly const &poly) {
    if (!poly.size()) return os;
    for (u32 i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.d.back();
  }

  constexpr u32 size() const { return (u32)d.size(); }
  constexpr bool empty() const {
    for (auto &&i : d)
      if (i != 0) return 0;
    return 1;
  }
  constexpr data_type &data() { return d; }
  constexpr data_type const &data() const { return d; }

  constexpr value_type &operator[](u32 x) { return d[x]; }
  constexpr value_type const &operator[](u32 x) const { return d[x]; }
  constexpr value_type operator()(value_type x) const {
    value_type ans = 0;
    for (u32 i = size() - 1; ~i; --i) ans = ans * x + d[i];
    return ans;
  }

  template <class F>
  requires requires(F f, u32 idx, mint &val) {
    f(idx, val);
  }
  constexpr void apply_range(u32 l, u32 r, F &&f) {
    assert(l < r && r <= size());
    for (u32 i = l; i < r; ++i) f(i, d[i]);
  }
  template <class F>
  constexpr void apply(F &&f) { apply_range(0, size(), std::forward<F>(f)); }
  constexpr void resize(u32 size) { d.resize(size); }
  constexpr poly pre(u32 size) const {
    poly _ = *this;
    _.resize(size);
    return _;
  }
  constexpr void strip() {
    auto it = std::find_if(d.rbegin(), d.rend(), [](auto const &x) { return x != 0; });
    d.resize(usz(d.rend() - it));
    if (d.empty()) d.push_back(value_type(0));
  }
  constexpr void reverse(u32 n = 0) { std::reverse(d.begin(), d.begin() + (n ? n : size())); }
  constexpr void conv(poly const &r, u32 ans_size = 0) { conv_core.conv(d, r.d, ans_size); }

  constexpr poly operator-() const {
    poly ret = *this;
    ret.apply([](u32, auto &v) { v = -v; });
    return ret;
  }

  friend constexpr poly operator+(poly p, value_type c) {
    p[0] += c;
    return p;
  }
  friend constexpr poly operator+(value_type c, poly const &p) { return p + c; }
  friend constexpr poly operator-(poly p, value_type c) {
    p[0] -= c;
    return p;
  }
  friend constexpr poly operator-(value_type c, poly const &p) { return p - c; }

  constexpr poly &operator*=(value_type c) {
    apply([&c](u32, auto &v) { v *= c; });
    return *this;
  }
  friend constexpr poly operator*(poly p, value_type c) { return p *= c; }
  friend constexpr poly operator*(value_type c, poly p) { return p *= c; }

  constexpr poly &operator+=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](u32 i, auto &v) { v += r[i]; });
    return *this;
  }
  friend constexpr poly operator+(poly l, poly const &r) { return l += r; }

  constexpr poly &operator-=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](u32 i, auto &v) { v -= r[i]; });
    return *this;
  }
  friend constexpr poly operator-(poly l, poly const &r) { return l -= r; }

  constexpr poly &operator*=(poly const &r) {
    if (!r.size()) {
      resize(1);
      d[0] = 0;
      return *this;
    }
    conv(r);
    return *this;
  }
  friend constexpr poly operator*(poly l, poly const &r) { return l *= r; }
};

}  // namespace tifa_libs::math

#endif