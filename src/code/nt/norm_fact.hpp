#ifndef TIFALIBS_MATH_NORM_FACT
#define TIFALIBS_MATH_NORM_FACT

#include "../math/gint.hpp"
#include "../math/qpow.hpp"
#include "../math/qpow_mod.hpp"
#include "pfactors.hpp"

namespace tifa_libs::math {
namespace norm_fact_impl_ {
CEXP gint<i128, -1> nfp(u64 p) {
  if (p % 4 == 3) return {-1, -1};
  if (p == 2) return {1, 1};
  i64 x = 1;
  while (1)
    if (u64 z = qpow_mod(u64(++x), (p - 1) / 4, p); mul_mod_u(z, z, p) == p - 1) {
      x = (i64)z;
      break;
    }
  i64 y = 1, k = i64(((i128)x * x + 1) / p);
  while (k > 1) {
    i64 b = x % k, d = y % k;
    if (b < 0) b += k;
    if (b * 2 > k) b -= k;
    if (d < 0) d += k;
    if (d * 2 > k) d -= k;
    i64 xx = i64(((i128)x * b + (i128)y * d) / k), yy = i64(((i128)x * d - (i128)y * b) / k);
    x = xx, y = yy, k = i64(((i128)x * x + (i128)y * y) / p);
  }
  return {x, y};
}
CEXP vec<gint<i128, -1>> nfpp(u64 p, u32 e) {
  using G = gint<i128, -1>;
  if (p % 4 == 3) return {e & 1 ? 0 : (i64)qpow(p, e / 2)};
  if (p == 2) return {qpow(G{1, 1}, e)};
  G _ = nfp(p);
  vec<G> pows(e + 1), ret(e + 1);
  pows[0] = 1;
  flt_ (u32, i, 1, e + 1) pows[i] = pows[i - 1] * _;
  flt_ (u32, i, 0, e + 1) ret[i] = pows[i] * conj(pows[e - i]);
  return ret;
}
CEXP vec<gint<i128, -1>> nf(u64 n) {
  using G = gint<i128, -1>;
  if (!n) return {{}};
  auto const pe = pf_exp(n);
  for (auto CR[p, e] : pe)
    if (p % 4 == 3 && (e & 1)) return {};
  vec<G> ret{G{1}};
  for (auto CR[p, e] : pe) {
    vec<G> now = nfpp(p, e), nxt;
    for (auto CR g1 : ret)
      for (auto CR g2 : now) nxt.push_back(g1 * g2);
    ret = nxt;
  }
  for (auto& g : ret)
    while (g.real() <= 0 || g.imag() < 0) g = {-g.imag(), g.real()};
  return ret;
}
}  // namespace norm_fact_impl_

// find all non-negative integer pair (x, y) s.t. $x^2+y^2=n$ in lexicographic order
CEXP vecptuu norm_fact(u64 n) {
  if (!n) return {{0, 0}};
  vecptuu ans;
  for (auto& g : norm_fact_impl_::nf(n))
    if (ans.emplace_back(g.real(), g.imag()); !g.imag()) ans.emplace_back(g.imag(), g.real());
  return std::ranges::sort(ans), ans;
}

}  // namespace tifa_libs::math

#endif