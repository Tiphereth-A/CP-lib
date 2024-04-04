#ifndef TIFALIBS_POLY_GCD_FPS
#define TIFALIBS_POLY_GCD_FPS

#include "divmod_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

namespace gcd_impl__fps {

template <class mint, class ccore>
using pttp = ptt<poly<mint, ccore>>;

template <class mint, class ccore>
struct matp {
  using poly_t = poly<mint, ccore>;
  poly_t a00, a01, a10, a11;

  explicit constexpr matp() {}
  constexpr matp(u64 x00, u64 x01, u64 x10, u64 x11) : a00(1, x00), a01(1, x01), a10(1, x10), a11(1, x11) {}
  constexpr matp(poly_t const& a00, poly_t const& a01,
                 poly_t const& a10, poly_t const& a11) : a00(a00), a01(a01), a10(a10), a11(a11) {}

  constexpr matp& operator*=(matp const& r) {
    poly_t _00 = a00 * r.a00 + a01 * r.a10, _01 = a00 * r.a01 + a01 * r.a11,
           _10 = a10 * r.a00 + a11 * r.a10, _11 = a10 * r.a01 + a11 * r.a11;
    _00.strip(), _01.strip(), _10.strip(), _11.strip();
    std::swap(_00, a00), std::swap(_01, a01), std::swap(_10, a10), std::swap(_11, a11);
    return *this;
  }
  constexpr matp operator*(matp const& r) const { return matp(*this) *= r; }
  friend constexpr pttp<mint, ccore> operator*(matp const& m, pttp<mint, ccore> const& a) {
    poly_t b0 = m.a00 * a.first + m.a01 * a.second, b1 = m.a10 * a.first + m.a11 * a.second;
    b0.strip(), b1.strip();
    return {b0, b1};
  }
};

template <class mint, class ccore>
constexpr void ngcd_(matp<mint, ccore>& m, pttp<mint, ccore>& p) {
  auto [q, r] = divmod_fps(p.first, p.second);
  poly<mint, ccore> b0 = m.a00 - m.a10 * q, b1 = m.a01 - m.a11 * q;
  b0.strip(), b1.strip();
  std::swap(b0, m.a10), std::swap(b1, m.a11), std::swap(b0, m.a00), std::swap(b1, m.a01);
  p = {p.second, r};
}

template <class mint, class ccore>
constexpr matp<mint, ccore> hgcd_(pttp<mint, ccore> p) {
  u32 n = (u32)p.first.size(), m = (u32)p.second.size(), k = (n + 1) / 2;
  if (m <= k) return matp<mint, ccore>(1, 0, 0, 1);
  matp<mint, ccore> _ = hgcd_(pttp<mint, ccore>{shr_strip_fps(p.first, k), shr_strip_fps(p.second, k)});
  p = _ * p;
  if (p.second.size() <= k) return _;
  ngcd_(_, p);
  if (p.second.size() <= k) return _;
  u32 l = (u32)p.first.size() - 1, j = 2 * k - l;
  p.first = shr_strip_fps(p.first, j), p.second = shr_strip_fps(p.second, j);
  return hgcd_(p) * _;
}

template <class mint, class ccore>
constexpr matp<mint, ccore> pgcd_(poly<mint, ccore> const& a, poly<mint, ccore> const& b) {
  pttp<mint, ccore> p{a, b};
  p.first.strip(), p.second.strip();
  u32 n = (u32)p.first.size(), m = (u32)p.second.size();
  if (n < m) {
    matp<mint, ccore> mat = pgcd_(p.second, p.first);
    std::swap(mat.a00, mat.a01), std::swap(mat.a10, mat.a11);
    return mat;
  }

  matp<mint, ccore> res = matp<mint, ccore>(1, 0, 0, 1);
  while (1) {
    auto _ = hgcd_(p);
    p = _ * p;
    if (p.second.empty()) return _ * res;
    ngcd_(_, p);
    if (p.second.empty()) return _ * res;
    res = _ * res;
  }
}
}  // namespace gcd_impl__fps

template <class mint, class ccore>
constexpr poly<mint, ccore> gcd_fps(poly<mint, ccore> const& f, poly<mint, ccore> const& g) {
  ptt<poly<mint, ccore>> p(f, g);
  p = gcd_impl__fps::pgcd_(f, g) * p;
  if (!p.first.empty()) {
    poly<mint, ccore> _ = p.first.back().inv();
    for (auto& x : p.first) x *= _;
  }
  return p.first;
}

}  // namespace tifa_libs::math

#endif