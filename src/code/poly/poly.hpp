#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../util/util.hpp"

namespace tifa_libs::math {

// clang-format off
enum ccore_t { ct_FFT, ct_3NTT, ct_NTT };
// clang-format on

template <template <class... Ts> class ccore, class mint, class... args>
requires requires(ccore<mint, args...> cc, vec<mint> l, vec<mint> r, u32 sz) {
  { ccore<mint, args...>::ct_cat } -> std::same_as<ccore_t CR>;
  cc.conv(l, r), cc.conv(l, r, sz);
}
struct poly : vec<mint> {
  using val_t = mint;
  using data_t = vec<val_t>;
  using ccore_t = ccore<mint, args...>;
  static inline ccore_t conv_core;

  CEXPE poly(u32 sz = 1, cT_(val_t) val = val_t{}) : data_t(sz, val) {}
  CEXP poly(TPN data_t::const_iterator begin, TPN data_t::const_iterator end) : data_t(begin, end) {}
  CEXP poly(vec<val_t> CR v) : data_t(v) {}
  CEXP poly(vec<val_t> &&v) : data_t(std::move(v)) {}
  CEXP poly(itl<val_t> v) : data_t(v) {}
  CEXP poly(spn<val_t> v) : data_t(v) {}

  friend CEXP std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly) is >> val;
    return is;
  }
  friend CEXP std::ostream &operator<<(std::ostream &os, poly CR poly) {
    if (!poly.size()) return os;
    flt_ (u32, i, 1, (u32)poly.size()) os << poly[i - 1] << ' ';
    return os << poly.back();
  }
  CEXP bool is_zero() const {
    for (auto &&i : *this)
      if (i != 0) return 0;
    return 1;
  }
  CEXP val_t operator()(val_t x) const {
    val_t ans = 0;
    for (u32 i = data_t::size() - 1; ~i; --i) ans = ans * x + data_t::data()[i];
    return ans;
  }
  template <class F>
  requires requires(F f, u32 idx, mint &val) { f(idx, val); }
  CEXP void apply_range(u32 l, u32 r, F &&f) {
    assert(l < r && r <= data_t::size());
    flt_ (u32, i, l, r) f(i, data_t::data()[i]);
  }
  template <class F>
  CEXP void apply(F &&f) { apply_range(0, (u32)data_t::size(), std::forward<F>(f)); }
  CEXP poly pre(u32 size) const {
    poly _ = *this;
    return _.resize(size), _;
  }
  CEXP void strip() {
    auto it = std::find_if(data_t::rbegin(), data_t::rend(), [](cT_(mint) x) { return x.val() != 0; });
    if (data_t::resize(usz(data_t::rend() - it)); data_t::empty()) data_t::push_back(val_t(0));
  }
  friend poly stripped(poly p) { return p.strip(), p; }
  CEXP void reverse(u32 n = 0) { std::reverse(data_t::begin(), data_t::begin() + (n ? n : (u32)data_t::size())); }
  CEXP void conv(poly CR r, u32 ans_size = 0) { conv_core.conv(*this, r, ans_size); }
  CEXP poly operator-() const {
    poly ret = *this;
    return ret.apply([](u32, auto &v) { v = -v; }), ret;
  }
  friend CEXP poly operator+(poly p, val_t c) { return p[0] += c, p; }
  friend CEXP poly operator+(val_t c, poly CR p) { return p + c; }
  friend CEXP poly operator-(poly p, val_t c) { return p[0] -= c, p; }
  friend CEXP poly operator-(val_t c, poly CR p) { return p - c; }
  CEXP poly &operator*=(val_t c) {
    return apply([&c](u32, auto &v) { v *= c; }), *this;
  }
  friend CEXP poly operator*(poly p, val_t c) { return p *= c; }
  friend CEXP poly operator*(val_t c, poly p) { return p *= c; }
  CEXP poly &operator+=(poly CR r) {
    if (r.empty()) return *this;
    data_t::resize(max(data_t::size(), r.size())), apply_range(0, (u32)r.size(), [&r](u32 i, auto &v) { v += r[i]; });
    return *this;
  }
  friend CEXP poly operator+(poly l, poly CR r) { return l += r; }

  CEXP poly &operator-=(poly CR r) {
    if (r.empty()) return *this;
    return data_t::resize(max(data_t::size(), r.size())), apply_range(0, (u32)r.size(), [&r](u32 i, auto &v) { v -= r[i]; }), *this;
  }
  friend CEXP poly operator-(poly l, poly CR r) { return l -= r; }

  CEXP poly &operator*=(poly CR r) {
    if (r.empty()) return data_t::resize(1), *data_t::data() = 0, *this;
    return conv(r), *this;
  }
  friend CEXP poly operator*(poly l, poly CR r) { return l *= r; }
  CEXP auto operator<=>(poly CR r) const { return data_t::operator<=>(stripped(*this), stripped(r)); }
};

}  // namespace tifa_libs::math

#endif