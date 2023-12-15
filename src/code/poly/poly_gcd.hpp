#ifndef TIFALIBS_POLY_POLY_GCD
#define TIFALIBS_POLY_POLY_GCD

#include "poly_divmod.hpp"
#include "poly_shr.hpp"

namespace tifa_libs::math {

namespace poly_gcd_impl_ {

template <class T>
using pttp = ptt<poly<T>>;

template <class T>
struct matp {
  using Dt = poly<T>;
  Dt a00, a01, a10, a11;

  explicit constexpr matp() {}
  constexpr matp(u64 x00, u64 x01, u64 x10, u64 x11) : a00(1, x00), a01(1, x01), a10(1, x10), a11(1, x11) {}
  constexpr matp(Dt const& a00, Dt const& a01, Dt const& a10, Dt const& a11) : a00(a00), a01(a01), a10(a10), a11(a11) {}

  constexpr matp& operator*=(matp const& r) {
    Dt _00 = a00 * r.a00 + a01 * r.a10,
       _01 = a00 * r.a01 + a01 * r.a11,
       _10 = a10 * r.a00 + a11 * r.a10,
       _11 = a10 * r.a01 + a11 * r.a11;
    _00.strip(), _01.strip(), _10.strip(), _11.strip();
    std::swap(_00, a00), std::swap(_01, a01), std::swap(_10, a10), std::swap(_11, a11);
    return *this;
  }
  constexpr matp operator*(matp const& r) const { return matp(*this) *= r; }
  friend constexpr pttp<T> operator*(matp const& m, pttp<T> const& a) {
    Dt b0 = m.a00 * a.first + m.a01 * a.second, b1 = m.a10 * a.first + m.a11 * a.second;
    b0.strip(), b1.strip();
    return {b0, b1};
  }
};

template <class T>
constexpr void ngcd_(matp<T>& m, pttp<T>& p) {
  auto [q, r] = poly_divmod(p.first, p.second);
  poly<T> b0 = m.a00 - m.a10 * q, b1 = m.a01 - m.a11 * q;
  b0.strip(), b1.strip();
  std::swap(b0, m.a10), std::swap(b1, m.a11), std::swap(b0, m.a00), std::swap(b1, m.a01);
  p = {p.second, r};
}

template <class T>
constexpr matp<T> hgcd_(pttp<T> p) {
  u32 n = (u32)p.first.size(), m = (u32)p.second.size(), k = (n + 1) / 2;
  if (m <= k) return matp<T>(1, 0, 0, 1);
  matp<T> _ = hgcd_(ptt<poly<T>>{poly_shr_strip(p.first, k), poly_shr_strip(p.second, k)});
  p = _ * p;
  if (p.second.size() <= k) return _;
  ngcd_(_, p);
  if (p.second.size() <= k) return _;
  u32 l = (u32)p.first.size() - 1, j = 2 * k - l;
  p.first = poly_shr_strip(p.first, j), p.second = poly_shr_strip(p.second, j);
  return hgcd_(p) * _;
}

template <class T>
constexpr matp<T> pgcd_(poly<T> const& a, poly<T> const& b) {
  pttp<T> p{a, b};
  p.first.strip(), p.second.strip();
  u32 n = (u32)p.first.size(), m = (u32)p.second.size();
  if (n < m) {
    matp<T> mat = pgcd_(p.second, p.first);
    std::swap(mat.a00, mat.a01), std::swap(mat.a10, mat.a11);
    return mat;
  }

  matp<T> res = matp<T>(1, 0, 0, 1);
  while (1) {
    auto _ = hgcd_(p);
    p = _ * p;
    if (p.second.empty()) return _ * res;
    ngcd_(_, p);
    if (p.second.empty()) return _ * res;
    res = _ * res;
  }
}
}  // namespace poly_gcd_impl_

template <class T>
constexpr poly<T> poly_gcd(poly<T> const& f, poly<T> const& g) {
  ptt<poly<T>> p(f, g);
  p = poly_gcd_impl_::pgcd_(f, g) * p;
  if (!p.first.empty()) {
    T _ = p.first.back().inv();
    for (auto& x : p.first) x *= _;
  }
  return p.first;
}

}  // namespace tifa_libs::math

#endif