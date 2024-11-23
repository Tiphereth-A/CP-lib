#ifndef TIFALIBS_POLY_SQRT_FPS
#define TIFALIBS_POLY_SQRT_FPS

#include "../nt/qresidue.hpp"
#include "inv_fps.hpp"
#include "shl_fps.hpp"
#include "shr_fps.hpp"

namespace tifa_libs::math {

template <template <class... Ts> class ccore, class mint, class... args>
CEXP std::optional<poly<ccore, mint, args...>> sqrt_fps(poly<ccore, mint, args...> p, u32 n = 0) {
  if (!n) n = (u32)p.size();
  const u32 cnt = u32(std::find_if(p.begin(), p.begin() + n, [](cT_(mint) x) { return x.val() != 0; }) - p.begin());
  if (cnt == n) return p.pre(n);
  if (cnt & 1) return {};
  poly<ccore, mint, args...> ans{0};
  p = shr_fps(p, cnt);
  if (auto qres = qresidue(p[0].val(), mint::mod()); !qres.has_value()) return {};
  else ans[0] = min(qres.value(), mint::mod() - qres.value());
  mint i2 = mint(2).inv();
  for (u32 i = 1; i < n; i *= 2) ans = (ans + p.pre(i * 2) * inv_fps(ans, i * 2)) * i2;
  return ans.resize(n), shl_fps(ans, cnt / 2);
}

}  // namespace tifa_libs::math

#endif