#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../util/util.hpp"

namespace tifa_libs::math {

// clang-format off
enum ccore_t { ct_FFT, ct_3NTT, ct_NTT };
// clang-format on

template <class mint, class ccore>
requires requires(ccore cc, vec<mint> l, vec<mint> r, u32 sz) {
  { ccore::ct_cat } -> std::same_as<ccore_t CR>;
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

  CEXPE poly(u32 sz = 1, cT_(value_type) val = value_type{}) : d(sz, val) {}
  CEXP poly(TPN data_type::const_iterator begin, TPN data_type::const_iterator end) : d(begin, end) {}
  CEXP poly(itl<value_type> v) : d(v) {}
  CEXP poly(spn<value_type> v) : d(v.begin(), v.end()) {}

  friend CEXP std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.d) is >> val;
    return is;
  }
  friend CEXP std::ostream &operator<<(std::ostream &os, poly CR poly) {
    if (!poly.size()) return os;
    flt_ (u32, i, 1, (u32)poly.size()) os << poly[i - 1] << ' ';
    return os << poly.d.back();
  }
  CEXP u32 size() const { return (u32)d.size(); }
  CEXP bool empty() const {
    for (auto &&i : d)
      if (i != 0) return 0;
    return 1;
  }
  CEXP data_type &data() { return d; }
  CEXP data_type CR data() const { return d; }
  CEXP value_type &operator[](u32 x) { return d[x]; }
  CEXP value_type CR operator[](u32 x) const { return d[x]; }
  CEXP value_type operator()(value_type x) const {
    value_type ans = 0;
    for (u32 i = size() - 1; ~i; --i) ans = ans * x + d[i];
    return ans;
  }
  template <class F>
  requires requires(F f, u32 idx, mint &val) { f(idx, val); }
  CEXP void apply_range(u32 l, u32 r, F &&f) {
    assert(l < r && r <= size());
    flt_ (u32, i, l, r) f(i, d[i]);
  }
  template <class F>
  CEXP void apply(F &&f) { apply_range(0, size(), std::forward<F>(f)); }
  CEXP void resize(u32 size) { d.resize(size); }
  CEXP poly pre(u32 size) const {
    poly _ = *this;
    return _.resize(size), _;
  }
  CEXP void strip() {
    auto it = std::find_if(d.rbegin(), d.rend(), [](cT_(mint) x) { return x.val() != 0; });
    if (d.resize(usz(d.rend() - it)); d.empty()) d.push_back(value_type(0));
  }
  friend poly stripped(poly p) { return p.strip(), p; }
  CEXP void reverse(u32 n = 0) { std::reverse(d.begin(), d.begin() + (n ? n : size())); }
  CEXP void conv(poly CR r, u32 ans_size = 0) { conv_core.conv(d, r.d, ans_size); }
  CEXP poly operator-() const {
    poly ret = *this;
    return ret.apply([](u32, auto &v) { v = -v; }), ret;
  }
  friend CEXP poly operator+(poly p, value_type c) { return p[0] += c, p; }
  friend CEXP poly operator+(value_type c, poly CR p) { return p + c; }
  friend CEXP poly operator-(poly p, value_type c) { return p[0] -= c, p; }
  friend CEXP poly operator-(value_type c, poly CR p) { return p - c; }
  CEXP poly &operator*=(value_type c) {
    return apply([&c](u32, auto &v) { v *= c; }), *this;
  }
  friend CEXP poly operator*(poly p, value_type c) { return p *= c; }
  friend CEXP poly operator*(value_type c, poly p) { return p *= c; }
  CEXP poly &operator+=(poly CR r) {
    if (!r.size()) return *this;
    resize(max(size(), r.size())), apply_range(0, r.size(), [&r](u32 i, auto &v) { v += r[i]; });
    return *this;
  }
  friend CEXP poly operator+(poly l, poly CR r) { return l += r; }

  CEXP poly &operator-=(poly CR r) {
    if (!r.size()) return *this;
    return resize(max(size(), r.size())), apply_range(0, r.size(), [&r](u32 i, auto &v) { v -= r[i]; }), *this;
  }
  friend CEXP poly operator-(poly l, poly CR r) { return l -= r; }

  CEXP poly &operator*=(poly CR r) {
    if (!r.size()) return resize(1), d[0] = 0, *this;
    return conv(r), *this;
  }
  friend CEXP poly operator*(poly l, poly CR r) { return l *= r; }
  CEXP auto operator<=>(poly CR r) const { return stripped(*this).d <=> stripped(r).d; }
  CEXP bool operator==(poly CR r) const { return stripped(*this).d == stripped(r).d; }
};

}  // namespace tifa_libs::math

#endif