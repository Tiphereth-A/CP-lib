#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../util/strip.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs::math {

// clang-format off
enum ccore_t { ct_FFT_R2, ct_3NTT, ct_NTT };
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

  CEXPE poly(u32 sz = 1, cT_(val_t) val = val_t{}) NE : data_t(sz, val) {}
  CEXP poly(TPN data_t::const_iterator begin, TPN data_t::const_iterator end) NE : data_t(begin, end) {}
  CEXP poly(vec<val_t> CR v) NE : data_t(v) {}
  CEXP poly(vec<val_t> &&v) NE : data_t(std::move(v)) {}
  CEXP poly(itl<val_t> v) NE : data_t(v) {}
  CEXP poly(spn<val_t> v) NE : data_t(v) {}
  CEXP poly(common_range auto CR v) NE : data_t(v.begin(), v.end()) {}

  friend CEXP auto &operator>>(istream_c auto &is, poly &poly) NE {
    for (auto &val : poly) is >> val;
    return is;
  }
  friend CEXP auto &operator<<(ostream_c auto &os, poly CR poly) NE {
    if (!poly.size()) return os;
    flt_ (u32, i, 1, (u32)poly.size()) os << poly[i - 1] << ' ';
    return os << poly.back();
  }
  CEXP bool is_zero() CNE {
    for (auto &&i : *this)
      if (i != 0) return 0;
    return 1;
  }
  CEXP val_t operator()(val_t x) CNE {
    val_t ans = 0;
    for (u32 i = data_t::size() - 1; ~i; --i) ans = ans * x + data_t::data()[i];
    return ans;
  }
  template <class F>
  requires requires(F f, u32 idx, mint &val) { f(idx, val); }
  CEXP void apply_range(u32 l, u32 r, F &&f) NE {
    assert(l < r && r <= data_t::size());
    flt_ (u32, i, l, r) f(i, data_t::data()[i]);
  }
  template <class F>
  CEXP void apply(F &&f) NE { apply_range(0, (u32)data_t::size(), std::forward<F>(f)); }
  CEXP poly pre(u32 sz) CNE {
    if (sz <= this->size()) return {this->begin(), this->begin() + sz};
    poly _ = *this;
    _.resize(sz);
    return _;
  }
  CEXP void strip() NE {
    auto [_, r] = rstrip_view(*this, [](cT_(mint) x) NE { return x.val() == 0; });
    if (data_t::erase(r, this->end()); data_t::empty()) data_t::push_back(val_t(0));
  }
  friend poly stripped(poly CR p) NE {
    poly ret(rstrip_view(p, [](cT_(mint) x) NE { return x.val() == 0; }));
    if (ret.empty()) return {0};
    return ret;
  }
  CEXP void reverse(u32 n = 0) NE { std::ranges::reverse(data_t::begin(), data_t::begin() + (n ? n : (u32)data_t::size())); }
  CEXP void conv(poly CR r, u32 ans_size = 0) NE { conv_core.conv(*this, r, ans_size); }
  CEXP poly operator-() CNE {
    poly ret = *this;
    ret.apply([](u32, auto &v) NE { v = -v; });
    return ret;
  }
  friend CEXP poly operator+(poly p, val_t c) NE {
    p[0] += c;
    return p;
  }
  friend CEXP poly operator+(val_t c, poly CR p) NE { return p + c; }
  friend CEXP poly operator-(poly p, val_t c) NE {
    p[0] -= c;
    return p;
  }
  friend CEXP poly operator-(val_t c, poly CR p) NE { return p - c; }
  CEXP poly &operator*=(val_t c) NE {
    apply([&c](u32, auto &v) NE { v *= c; });
    return *this;
  }
  friend CEXP poly operator*(poly p, val_t c) NE { return p *= c; }
  friend CEXP poly operator*(val_t c, poly p) NE { return p *= c; }
  CEXP poly &operator+=(poly CR r) NE {
    if (r.empty()) return *this;
    data_t::resize(max(data_t::size(), r.size())), apply_range(0, (u32)r.size(), [&r](u32 i, auto &v) NE { v += r[i]; });
    return *this;
  }
  friend CEXP poly operator+(poly l, poly CR r) NE { return l += r; }

  CEXP poly &operator-=(poly CR r) NE {
    if (r.empty()) return *this;
    data_t::resize(max(data_t::size(), r.size()));
    apply_range(0, (u32)r.size(), [&r](u32 i, auto &v) NE { v -= r[i]; });
    return *this;
  }
  friend CEXP poly operator-(poly l, poly CR r) NE { return l -= r; }

  CEXP poly &operator*=(poly CR r) NE {
    if (r.empty()) {
      data_t::resize(1), *data_t::data() = 0;
      return *this;
    }
    conv(r);
    return *this;
  }
  friend CEXP poly operator*(poly l, poly CR r) NE { return l *= r; }
  CEXP auto operator<=>(poly CR r) CNE {
    auto l_ = stripped(*this), r_ = stripped(r);
    if (l_.size() != r_.size()) return l_.size() <=> r_.size();
    return std::lexicographical_compare_three_way(l_.rbegin(), l_.rend(), r_.rbegin(), r_.rend());
  }
  CEXP bool operator==(poly CR r) CNE { return std::is_eq(*this <=> r); }
};

}  // namespace tifa_libs::math

#endif