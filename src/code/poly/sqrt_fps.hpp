#ifndef TIFALIBS_POLY_SQRT_FPS
#define TIFALIBS_POLY_SQRT_FPS

#include "../nt/qresidue.hpp"
#include "inv_fps.hpp"
#include "shl_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

template <class mint, class ccore>
CEXP std::optional<poly<mint, ccore>> sqrt_fps(poly<mint, ccore> p, u32 n = 0) {
  if (!n) n = p.size();
  u32 cnt = u32(std::find_if(p.data().begin(), p.data().begin() + n, [](cT_(mint) x) { return x.val() != 0; }) - p.data().begin());
  if (cnt == n) return p.pre(n);
  if (cnt & 1) return {};
  poly<mint, ccore> ans{0};
  p = shr_fps(p, cnt);
  if (auto qres = qresidue(p[0].val(), mint::mod()); !qres.has_value()) return {};
  else ans[0] = min(qres.value(), mint::mod() - qres.value());
  mint i2 = mint(2).inv();
  for (u32 i = 1; i < n; i *= 2) ans = (ans + p.pre(i * 2) * inv_fps(ans, i * 2)) * i2;
  ans.resize(n);
  return shl_fps(ans, cnt / 2);
}

}  // namespace tifa_libs::math

#endif